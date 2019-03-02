#include "static_code_len/static_code_len.h"
#include "huffman/huffman.h"


int main(int argc,char** argv) {
    huffman::compress("../data","../out");
//    static_code::decompress("../out","../decompressed_data");
    return 0;
}


