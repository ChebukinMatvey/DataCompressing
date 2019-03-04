#include "bitset.h"
#include <math.h>
#include <assert.h>
#include <cstring>


namespace utils {

unsigned int mask[8] = {0b00000001, 0b00000011,0b00000111,0b00001111,0b00011111,0b00111111,0b01111111,0b11111111};

    bitset::bitset(int len) {
        this->len = len;
        this->bits = new byte[len];
        for (int i = 0; i <len; ++i) {
            bits[i] = 0b00000000;
        }
    }

    bitset::bitset(char *data, int length) {
        this->len = length;
        this->bits = reinterpret_cast<byte *>(data); // pointer initialization
    }

    void bitset::push(byte b,byte code_len) {

        byte available_bits = 8 - current_bit_index;

        if(code_len > available_bits){ // bit overflow   000 0_01 01| 0
            bits[current_byte_index] |= ( b >> (code_len - available_bits));
            current_byte_index++;
            bits[current_byte_index] |= ( b <<( 8 - (code_len - available_bits)));
            current_bit_index = code_len - available_bits;
        }

        else{
            bits[current_byte_index] |= ( b << (available_bits - code_len));
            current_bit_index = code_len + 8 - available_bits;
            if(current_bit_index == 8 ){
                current_byte_index++;
                current_bit_index=0;
            }
        }

        assert(current_byte_index<=len);
    }



    char bitset::pop(byte code_len) {
        char b = 0;

        if(pop_bit_index + code_len > 8 )
        {
            byte difference = static_cast<byte>(code_len - (8 - pop_bit_index));
            b = ( mask[code_len-1] >> difference ) & ( bits[pop_byte_index++]);
            b <<= difference;
            b |= ( bits[pop_byte_index] >> ( 8 - difference));
            pop_bit_index = (difference);
        }

        else
        {
            b =  mask[code_len - 1] &  ( bits[pop_byte_index] >> (8 - pop_bit_index - code_len));
            pop_bit_index += code_len;
            if(pop_bit_index == 8){
                pop_bit_index = 0;
                pop_byte_index++;
            }
        }
        return b;
    }


    byte *bitset::bytes() {
        return bits;
    }


    void bitset::print_state() {
        std::cout<< std::bitset<8>(bits[pop_byte_index])<<std::endl;
    }


    void bitset::print() {
        for (int i = 0; i <=current_byte_index ; ++i) {
            std::cout<< std::bitset<8>(bits[i])<<" ";
        }
        std::cout<<"\n";
        std::cout.flush();
    }


    bool bitset::end() {
        if(pop_byte_index <= len-1)
            return false;
        else
            return true;
    }

    bitset::~bitset() {
        delete bits;
    }
}
