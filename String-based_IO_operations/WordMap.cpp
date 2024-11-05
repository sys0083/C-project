//
// Created by 孙宇石 on 2024/11/5.
//

#include "WordMap.h"

bool WordMap::wordmap_add(std::string s) {
    this->map_1[Word(s)] ++;
    return true;
}
void WordMap::show() {
    for (auto it = this->map_1.begin(); it != map_1.end(); ++ it) {
        std::cout << it->first.getWord() << "出现了"<< it->second << "次！"<< std::endl;
    }
}