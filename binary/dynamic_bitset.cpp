#include "dynamic_bitset.h"
#include <bitset>
#include <iostream>
#include <cstring>


dynamic_bitset::dynamic_bitset::dynamic_bitset() {
    this->bits = new std::vector<byte>();
}


dynamic_bitset::dynamic_bitset::dynamic_bitset(char *data,size_t size) {
    this->bits = new std::vector<byte>(size);
    memcpy(&(*this->bits)[0],data,size);
}


void dynamic_bitset::dynamic_bitset::push(byte value, byte code_len) {
    if(current_push_byte_index >= bits->size())
        bits->push_back(0);

    byte available_bits = 8 - current_push_bit_index;

    if(code_len > available_bits){ // bit overflow   000 0_01 01| 0
        (*bits)[current_push_byte_index] |= ( value >> (code_len - available_bits));
        current_push_byte_index++;
        bits->push_back(0);
        (*bits)[current_push_byte_index] |= ( value <<( 8 - (code_len - available_bits)));
        current_push_bit_index = code_len - available_bits;
    }

    else{
        (*bits)[current_push_byte_index] |= ( value << (available_bits - code_len));
        current_push_bit_index= code_len + 8 - available_bits;
        if(current_push_bit_index == 8 ){
            current_push_byte_index++;
            current_push_bit_index = 0;
        }
    }
}

unsigned char mask[8] = {0b00000001, 0b00000011,0b00000111,0b00001111,0b00011111,0b00111111,0b01111111,0b11111111};


dynamic_bitset::byte dynamic_bitset::dynamic_bitset::pop(byte code_len) {
    char b = 0;

    if(current_pop_bit_index + code_len > 8 )
    {
        byte difference = static_cast<byte>(code_len - (8 - current_pop_bit_index));
        b = ( mask[code_len-1] >> difference ) & ( (*bits)[current_pop_byte_index++]);
        b <<= difference;
        b |= ( (*bits)[current_pop_byte_index] >> ( 8 - difference));
        current_pop_bit_index = (difference);
    }

    else
    {
        b =  mask[code_len - 1] &  ( (*bits)[current_pop_byte_index] >> (8 - current_pop_bit_index - code_len));
        current_pop_bit_index += code_len;
        if(current_pop_bit_index == 8){
            current_pop_bit_index = 0;
            current_pop_byte_index++;
        }
    }
    return b;
}


dynamic_bitset::dynamic_bitset::~dynamic_bitset() {
    delete bits;
}


void dynamic_bitset::dynamic_bitset::print_current_byte_state() {
    std::cout<< std::bitset<8>(bits->at(current_push_byte_index));
}


void dynamic_bitset::dynamic_bitset::print_bytes() {
    using namespace std;
    for(auto b : *bits)
        cout<< bitset<8>(b)<<"-";
}


dynamic_bitset::byte *dynamic_bitset::dynamic_bitset::bytes() {
    return this->bits->data();
}

size_t dynamic_bitset::dynamic_bitset::size() {
    return this->bits->size();
}
