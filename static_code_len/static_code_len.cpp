#include <utility>
#include "static_code_len.h"
#include <memory>
void read_data(std::string,byte**,int*);
dictionary* create_dict(byte*,int);


void static_code::compress(std::string file_input, std::string file_output) {

    byte *data;
    int length;
    read_data(file_input, &data, &length);

    dictionary *dict = create_dict(data, length);
    byte code_length = static_cast<byte>(ceil(log2(dict->size()))); // Shannon

    int bits_count = static_cast<int>(ceil((double) length / 8 * code_length));

    byte* bytes = new byte[bits_count];
    auto *bits = new utils::bitset(bytes,bits_count);

    for (int i = 0; i < length; i++) {
        bits->push(static_cast<utils::byte>(dict->get_code(data[i])), static_cast<utils::byte>(code_length));
    }

    // [file_size][length_dict - 1 byte ][dict[0]....dict[length-1]][bits]
    std::ofstream out(file_output);
    char dict_size =dict->size();
    out.write((char*)(&length), sizeof(length));
    out.write(&dict_size, sizeof(dict_size));
    out.write(dict->data(),dict->size());
    out.write(bytes, bits_count);
    out.close();

    // Free memory usage to avoid leeks
    delete []bytes;
    delete []data;
    delete dict;
}


void static_code::decompress(std::string file_in, std::string file_out) {
    int length;
    byte *data;
    utils::bitset* bits;
    char* dict = new char[1]; // init pointer for memory copy
    char* text;
    unsigned char dict_size;
    int bits_count;
    int text_length;
    short code_length;

    read_data(std::move(file_in), &data, &length);
    memcpy(&text_length,&data[0], 4);
    dict_size = static_cast<unsigned char>(data[4]);
    code_length = static_cast<byte>(ceil(log2(dict_size)));
    bits_count = length - dict_size - 5;
    text = new char[text_length];

    memcpy(dict, &data[1 + 4], static_cast<size_t>(dict_size));


    bits = new utils::bitset(&data[dict_size + 1 + 4],bits_count);


    for(int i = 0 ; i < text_length; i++){
        int index =bits->pop(static_cast<utils::byte>(code_length));
        text[i] = dict[index];
    }


    std::ofstream out(file_out);
    out.write(text,text_length);
    out.close();

    delete dict;
    delete data;
    delete text;
}


void read_data(std::string filename, byte **data, int *length) {
    std::ifstream in(filename, std::ios_base::ate | std::ios_base::binary);
    assert(in.is_open());
    *length = in.tellg();
    byte* buff = new byte[*length];
    in.seekg(std::ios_base::beg);
    for (int i = 0; !in.eof(); i++) {
        in.read(&buff[i * claster], claster);
    }
    *data = buff;
    in.close();
}


dictionary* create_dict(byte *data, int length) {
    dictionary *dict = new dictionary();
    for (int i = 0; i < length; i++)
        dict->push(data[i]);
    return dict;
}