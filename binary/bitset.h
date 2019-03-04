#ifndef __bitset__
#define __bitset__

#include <iostream>
#include <bitset>
#include <vector>


/*
 * Bits store algorithm
 *      Data[65,66,65,66,67,68,69] -> Dictionary d[65,66,67,68,69]
 *      code_len = 3 bit    [000,001,010,011,100]
 *      bits_array.len = ceil(8/3) = 2.6 = 3 bytes
 *
 *      1) current_byte_position = current_bit_position = 0
 *
 *      2) available_bits = 8 - current_bit_index
 *
 *      3) code_len > available_bits  ????
 *          Yes:
 *              bits[current_byte_index] |= ( b >> (code_len - available_bits))     ~ push firs part of code to the low bits
 *              current_byte_index++                                                ~ increment current byte index
 *              bits[current_byte_index] |= ( b << 8 - (code_len - available_bits));~ add second part of code to the ahead bits
 *              current_bit_index = code_len - available_bits;                      ~ set bit position in the byte
 *          No:
 *              bits[current_byte_index] |= ( b << (available_bits - code_len));    ~ push code to current byte
 *              current_bit_index = code_len + 8 - available_bits;                  ~ set current bit position in the byte
 *              if current_bit_index == 8
 *                 current_bit_index = 0
 *                 current_byte_index ++
 */


namespace utils{
typedef unsigned char byte;

class bitset{

private:
    int current_bit_index = 0;  // current index to push
    int current_byte_index = 0; // current byte index
    int len;                    // bits count
    byte* bits;                 // bits array
    int pop_byte_index = 0;     // index for pop
    int pop_bit_index = 0;      // index for pop


public:
    bitset(int len);
    bitset(char *, int);
    void push(byte,byte);
    byte pop(byte);
    byte* bytes();
    void print_state();
    void print();
    bool end();
    ~bitset();
};
}
#endif