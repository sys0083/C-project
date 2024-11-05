//
// Created by 孙宇石 on 2024/11/5.
//

#ifndef STRING_BASED_IO_OPERATIONS_WORD_H
#define STRING_BASED_IO_OPERATIONS_WORD_H
#include <iostream>

class Word {
private:
    std::string s;

public:
    Word(std::string s);
    std::string getWord() const;
    bool operator < (const Word& a) const;
    bool operator == (std::string s) const;

};


#endif //STRING_BASED_IO_OPERATIONS_WORD_H
