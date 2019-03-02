#include <iostream>
#include "huffman.h"
#include<map>
#include <vector>
#include <fstream>

// char -> frequency
std::map<char,int> table;

std::vector<char> read_data(std::string);



void huffman::compress(std::string file_in,std::string file_out){

}




std::vector<char> read_data(std::string filename){
    std::ifstream input(filename,std::ios_base::binary);
     
}
