//
// Created by 孙宇石 on 2024/10/18.
//

#ifndef MYPROJECT_BIGINT_H
#define MYPROJECT_BIGINT_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>


class BigInt {
private:
    std::string number = "0"; // 所有数字按照倒序存储
    bool neg = false; // 默认无参构造为0,0的负号为false
public:
    BigInt(){}

    // 拷贝构造函数
    BigInt(const BigInt& other);

    // 利用整型构造
    BigInt(int number);

    // 利用长整型
    BigInt(long long int number);

    // 利用无符号长整型
    BigInt(unsigned long long int number);

    // 利用字符数组
    BigInt(const char *number);

    // 利用字符串
    BigInt(std::string number);

    friend bool operator == (BigInt first, BigInt second);

    friend bool operator != (BigInt first, BigInt second);

    friend bool operator < (BigInt first, BigInt second);

    friend bool operator <= (BigInt first, BigInt second);

    friend bool operator > (BigInt first, BigInt second);

    friend bool operator >= (BigInt first, BigInt second);

    // 直接输入大整型
    friend std::istream& operator >> (std::istream& in, BigInt &bigint);

    friend std::ostream& operator << (std::ostream& out, const BigInt &bigint);

    // abs不是模版函数，所以要封装一下
    friend BigInt abs(BigInt bigint);
    friend void swap(BigInt &first, BigInt &second);
    int size();

    // 加法重载
    // 双目运算符
    friend BigInt operator + (BigInt first, BigInt second);
    // 单目运算符
    friend BigInt operator + (BigInt bigInt);

    // 减法重载
    // 双目运算符
    friend BigInt operator - (BigInt first, BigInt second);
    // 单目运算符
    friend BigInt operator - (BigInt second);

    // 乘法
    friend BigInt operator * (BigInt first, BigInt second);

    // 除法
    friend BigInt operator / (BigInt first, BigInt second);

    // 取模
    friend BigInt operator % (BigInt first, BigInt second);

    // 幂指数
    friend BigInt pow(BigInt x, BigInt y, BigInt mod);

    // 按位与
    friend BigInt operator & (BigInt first, BigInt second);

    // 按位或
    friend BigInt operator | (BigInt first, BigInt second);

    // 按位异或
    friend BigInt operator ^ (BigInt first, BigInt second);

    // 将个位数大小的高精度整型数转为int
    int to_int(BigInt bigint);

    // 将高精度整型转化为base进制的数
    std::string int_to_base(int base);

    // 将base进制的数转化为高精度整型
    BigInt base_to_int(std::string str, int base);

    // 左移
    friend BigInt operator << (BigInt first, BigInt second);

    // 右移
    friend BigInt operator >> (BigInt first, BigInt second);

    void operator ++ (){*(this) = *(this) + 1;}
    void operator -- (){*(this) = *(this) - 1;}

    // 其他一些赋值运算符
    void operator += (BigInt bigint){*(this) = *(this) + bigint;}
    void operator -= (BigInt bigint){*(this) = *(this) - bigint;}

    void operator *= (BigInt bigint){*(this) = *(this) * bigint;}
    void operator /= (BigInt bigint){*(this) = *(this) / bigint;}
    void operator %= (BigInt bigint){*(this) = *(this) % bigint;}

//    void operator &= (BigInt bigint){*(this) = *(this) & bigint;}
//    void operator |= (BigInt bigint){*(this) = *(this) | bigint;}
//    void operator ^= (BigInt bigint){*(this) = *(this) ^ bigint;}
//
//    void operator <<= (BigInt bigint){*(this) = *(this) << bigint;}
//    void operator >>= (BigInt bigint){*(this) = *(this) >> bigint;}
};


#endif //MYPROJECT_BIGINT_H
