#include <vector>




namespace dynamic_bitset{

    typedef char byte;

    class dynamic_bitset{
    private:
        std::vector<byte>*bits;
        int current_push_byte_index;
        int current_push_bit_index;
        int current_pop_byte_index;
        int current_pop_bit_index;

    public:
        dynamic_bitset();
        dynamic_bitset(char*,size_t);
        void push(byte,byte);
        byte pop(byte);
        void print_current_byte_state();
        void print_bytes();
        byte* bytes();
        size_t size();
        ~dynamic_bitset();
    };


}