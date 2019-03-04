#include<string>

/*
 *  Huffman compression algorithm
 *
 *      Structure node -  node for huffman tree
 *
 *
 * */


namespace huffman {


    struct node{
        char character;
        char code;
        unsigned char code_len;
        int weight;
        node *left = nullptr, *right = nullptr;


        node(){}

        node(char c, int w){
            this->character = c;
            this->weight = w;
        }

        node(node* l, node* r){
            this->weight = l->weight + r->weight;
            this->left = l;
            this->right = r;
        }
    };

    struct unit{
        char character;
        char code;
        unsigned char code_len;
    };

    void compress(std::string*, std::string*);

    void decompress(std::string*, std::string*);
}



