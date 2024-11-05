//
// Created by 孙宇石 on 2024/11/5.
//

#ifndef STRING_BASED_IO_OPERATIONS_WORD_SET_H
#define STRING_BASED_IO_OPERATIONS_WORD_SET_H
#include <set>
#include <iostream>
#include "Word.h"

// 统计单词种类
class Word_set {
private:
    std::set<Word> set_1;
public:

    bool wordset_add(std::string s);
    void show();
};


#endif //STRING_BASED_IO_OPERATIONS_WORD_SET_H
