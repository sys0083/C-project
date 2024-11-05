//
// Created by 孙宇石 on 2024/11/5.
//

#ifndef STRING_BASED_IO_OPERATIONS_WORDMAP_H
#define STRING_BASED_IO_OPERATIONS_WORDMAP_H
#include "Word.h"
#include <map>
#include <iostream>

class WordMap {
private:
    std::map<Word, int> map_1;
public:
    bool wordmap_add(std::string s);
    void show();
};


#endif //STRING_BASED_IO_OPERATIONS_WORDMAP_H
