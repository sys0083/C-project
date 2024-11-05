//
// Created by 孙宇石 on 2024/11/5.
//

#include "Word.h"

Word::Word(std::string s) :s(s){}

std::string Word::getWord() const {
    return this->s;
}

bool Word::operator==(std::string s) const {
    return this->s == s;
}

bool Word::operator < (const Word& a) const {
    return this->s < a.s;
}