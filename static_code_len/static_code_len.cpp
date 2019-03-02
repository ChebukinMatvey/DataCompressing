#include <utility>

#include "static_code_len.h"


void read_data(std::string,byte**,int*);
dictionary* create_dict(byte*,int);


void static_code::compress(std::string file_input, std::string file_output) {

    byte *data;
    int length;

    read_data(file_input, &data, &length);

    dictionary *dict = create_dict(data, length);
    byte code_length = static_cast<byte>(ceil(log2(dict->size()))); // Shannon

    int bits_count = static_cast<int>(ceil((double) length / 8 * code_length));

    auto *bits = new utils::bitset(bits_count);

    for (int i = 0; i < length; i++) {
        bits->push(static_cast<utils::byte>(dict->get_code(data[i])), static_cast<utils::byte>(code_length));
    }


    // [length dict - 1 byte ][dict[0]....dict[length-1]][bits]
    std::ofstream out(file_output, std::ios_base::binary);
    char dict_size =dict->size();
    out.write(&dict_size, sizeof(char));
    out.write(dict->data(),dict->size());
    out.write((const char*)(bits->bytes()), bits_count);
    out.close();

    // Free memory usage to avoid leeks
    delete data;
    delete bits;
    delete dict;
}


void static_code::decompress(std::string file_in, std::string file_out) {
    int length;
    byte *data;
    utils::bitset* bits;
    byte *dict = new char[1]; // init pointer for memory copy
    byte* text;
    byte dict_size;
    int bits_count;
    int text_length;
    byte code_length;

    read_data(std::move(file_in), &data, &length);
    dict_size = data[0];
    code_length = static_cast<byte>(ceil(log2(dict_size)));
    bits_count= length - dict_size - 1;
    text_length = static_cast<int>(floor(bits_count * 8 / (double)code_length));
    text = new char[text_length];
    memcpy(dict, &data[1], static_cast<size_t>(dict_size));
    bits = new utils::bitset(&data[dict_size+1],bits_count);

    for(int i = 0 ; i < text_length; i++){
        text[i] = dict[bits->pop(static_cast<utils::byte>(code_length))];
    }

    std::ofstream out(file_out,std::ios_base::binary);
    out.write(text,text_length);
    out.close();

    delete text;
    delete dict;
    delete data;
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


dictionary *create_dict(byte *data, int length) {
    dictionary *dict = new dictionary();
    for (int i = 0; i < length; i++)
        dict->push(data[i]);
    return dict;
}
