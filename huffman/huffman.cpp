#include <iostream>
#include "huffman.h"
#include<map>
#include <vector>
#include <fstream>
#include <assert.h>


# define claster 4096

// char -> how much
std::map<char,int> table;

std::vector<char>* read_data(std::string);



void huffman::compress(std::string file_in,std::string file_out){
    std::vector<char>* data = read_data(file_in);

}




std::vector<char>* read_data(std::string filename){
    std::ifstream file(filename,std::ios_base::binary | std::ios_base::ate);
    long length = file.tellg();
    file.seekg(std::ios_base::beg);
    assert(file.is_open());
    char* buff = new char[length]; // init pointer
    auto * data = new std::vector<char>();
    for(int i=0;!file.eof();i++){
        file.read(&buff[i*claster],claster);
    }
    data->assign(buff,buff+length);

    delete buff;
    return data;
}
