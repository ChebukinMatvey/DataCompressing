#include "static_code_len/static_code_len.h"



int main(int argc,char** argv) {
    static_code::compress("../data","../out");
    static_code::decompress("../out","../decompressed_data");
    return 0;
}


