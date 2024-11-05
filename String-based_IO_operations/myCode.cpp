//
// Created by 孙宇石 on 2024/11/5.
//

#include "myCode.h"

Word_set s1;
WordMap m1;

void showData() {
    cout<< "单词集合为:" << endl;
    s1.show();
    cout << endl;
    cout <<"单词集合以及每个单词出现次数:" << endl;
    m1.show();
    cout << endl;
}

void dataProcessing() {
    string s = " ";
    string delimet = ".,?!";
    int pos = 0;
    // 把 data.txt 内容直接展示出来
//    ifstream input1("F:\\Desktop\\c++\\Cpp_project\\String-based_IO_operations\\data.txt");
    ifstream ifs1;
    ifs1.open("data.txt", ios::in);
    char ch;
    while (ifs1.peek() != EOF) {
        ifs1.read(&ch, 1);
        cout << ch;
    }
    ifs1.close();

    // 把 data.txt 文件里的单词进行分割，装入set和map
    ifstream ifs2;
    ifs2.open("data.txt", ios::in);
    while (! ifs2.eof()) {
        getline(ifs2, s);
        // 1. 先处理不合法的地方
        if (s == " ") {
            continue;
        }
        pos = 0;
        while ((pos = s.find_first_of(delimet, pos)) != string::npos) { // 一个符号一个符号的找违禁词
            s.replace(pos, 1, " "); // 将不合法的词改成空格
        }
        // 2. 利用sstream
        istringstream iss(s);
        while (!iss.eof()) {
            iss >> s;
            if (iss.fail()) {
                break;
            }
            if (s == " " || s == "") {
                continue;
            }
            s1.wordset_add(s);
            m1.wordmap_add(s);
        }
    }

    ifs2.close();
}