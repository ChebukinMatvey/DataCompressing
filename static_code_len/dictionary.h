#ifndef __dict__
#define __dict__

#include <vector>
#include <algorithm>

typedef char byte;

class dictionary {

private:
    std::vector<char> characters;

public:
    bool exist(char c) {
        return find(characters.begin(), characters.end(), c) != characters.end();
    }

    void push(char c) {
        if (exist(c))
            return;
        characters.push_back(c);
    }

    byte get_code(char c) {
        for (unsigned int i = 0; i < characters.size(); ++i) {
            if (characters[i] == c)
                return i;
        }
        throw "Not existing character in dictionary";
    }

    char get_char(byte code) {
        return characters[code];
    }

    int size() {
        return characters.size();
    }

    const char *data() {
        return characters.data();
    }
};
#endif