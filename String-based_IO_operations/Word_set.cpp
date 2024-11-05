//
// Created by 孙宇石 on 2024/11/5.
//

#include "Word_set.h"

bool Word_set::wordset_add(std::string s) {
    this->set_1.insert(Word(s));
    return true;
}

void Word_set::show() {
    for (auto it = this->set_1.begin(); it != set_1.end(); ++ it) {
        std::cout << it->getWord() << " ";
    }
    std::cout << std::endl;
}