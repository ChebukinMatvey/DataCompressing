#include "static_code_len/static_code_len.h"
#include "huffman/huffman.h"


int main(int argc,char** argv) {
//    using namespace huffman;
//
//    unit u;
//    node n;
//    n.character='c';
//    n.code_len = 10;
//    n.code=6;
//    memcpy(&u,&n, sizeof(unit));
//
//    std::cout<< sizeof(unit);
//    return 0;

    std::string input = "../data";
    std::string output =  "../out";
    std::string decompressed = "../decompressed_data";
    huffman::compress(&input,&output);
    huffman::decompress(&output,&decompressed);
    return 0;
}


