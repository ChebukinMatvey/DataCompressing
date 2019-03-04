#include <iostream>
#include "huffman.h"
#include<map>
#include <list>
#include <vector>
#include <fstream>
#include <assert.h>
#include<bitset>

# define claster 4096


// list of tree leaves for fast access after feel codes
std::list<huffman::node*> threaded_tree;


std::vector<char> *read_data(std::string *);
void feel_codes(huffman::node*);


/**
 * Compress function takes filenames for input and output
 * Create map character-> count in text
 * Create huffman tree
 * Feel codes for character and add node to list for fast access in the future
 * Create bitset of charcodes
 * Write bytes in the file
 *
 * @param:file_in input file
 * @param:file_out compressed file
 * @return: void
 *
 * */
void huffman::compress(std::string *file_in, std::string *file_out) {

    std::vector<char> *data = read_data(file_in);
    std::map<char, int> pf;
    std::list<node *> tree;

    for (char c : *data)
        pf[c]++;

    for (auto pair : pf)
        tree.push_back(new node(pair.first, pair.second));

    auto cmp = [](node *left, node *rigth) { return left->weight < rigth->weight; };

    while (tree.size() != 1) {
        tree.sort(cmp);
        node *left = tree.front();
        tree.pop_front();
        node *right = tree.front();
        tree.pop_front();
        tree.push_back(new node(left, right));
    }

    feel_codes(tree.front());

    for (auto _node : threaded_tree) {
        std::cout<< _node->character <<" - "<<std::bitset<8>(_node->code)<< " code len = "<< static_cast<unsigned short>(_node->code_len)<<std::endl;
    }
}



/**
 * Recursive tree following
 * Takes root, than add for every tree leave charcode and charcode length
 * If node is tree leave add this node to the threaded tree for fast access in the future
 *
 * @param: current_code - global variable for current charcode
 * @param: depth - global variable for charcode length or tree depth
 * @param: node - current processing node
 * @return: void
 */
char current_code ;
short depth ;
void feel_codes(huffman::node* _node){
    using namespace huffman;
    using namespace std;

    if (_node->left != nullptr){
        depth++;
        current_code<<=1;
        feel_codes(_node->left);
    }
    if (_node->right != nullptr){
        depth++;
        current_code <<=1;
        current_code |=1;
        feel_codes(_node->right);
    }
    if(_node->left == nullptr && _node->right == nullptr){
        _node->code_len=depth;
        _node->code=current_code;
//        cout<<"Char - "<<_node->character<< " set code "<<bitset<8>(current_code)<<" code len = "<<depth<<endl;
        threaded_tree.push_back(_node);
    }
    current_code >>=1;
    depth--;
}


/**
 * Read data from file
 *
 * @param:filename
 * @return:vector<char> - text
 * */
std::vector<char> *read_data(std::string *filename) {
    std::ifstream file(*filename, std::ios_base::binary | std::ios_base::ate);
    long length = file.tellg();
    file.seekg(std::ios_base::beg);
    assert(file.is_open());
    char *buff = new char[length]; // init pointer
    auto *data = new std::vector<char>();
    for (int i = 0; !file.eof(); i++) {
        file.read(&buff[i * claster], claster);
    }
    data->assign(buff, buff + length);

    delete buff;
    return data;
}
