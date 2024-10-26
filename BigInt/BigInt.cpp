//
// Created by 孙宇石 on 2024/10/18.
//

#include "BigInt.h"


BigInt::BigInt(const BigInt& other) {
    this->number = other.number;
    this->neg = other.neg;
}

BigInt::BigInt(int number) {
    // 先处理0和负数的情况
    if (number < 0) {
        this->neg = true;
        number *= -1;
    }
    if (number == 0) {
        this->number = "0";
        return;
    }
    this->number = "";
    while (number) {
        this->number += number % 10 + '0';  // 整数转化为对应字符
        number /= 10;
    }
}

// 利用长整型
BigInt::BigInt(long long int number) {
    // 先处理0和负数的情况
    if (number < 0) {
        this->neg = true;
        number *= -1;
    }
    if (number == 0) {
        this->number = "0";
        return;
    }
    this->number = "";
    while (number) {
        this->number += number % 10 + '0';  // 整数转化为对应字符
        number /= 10;
    }
}

// 利用无符号长整型
BigInt::BigInt(unsigned long long int number) {
    if (number == 0) {
        this->number = "0";
        return;
    }
    this->number = "";
    while (number) {
        this->number += number % 10 + '0';  // 整数转化为对应字符
        number /= 10;
    }
}

// 利用字符数组
BigInt::BigInt(const char *number) {
    // 直接转为string，利用string的构造函数去赋值
    std::string num(number);
    *(this) = num;
}

// 利用字符串
BigInt::BigInt(std::string number) {
    // 去除前导负号，一般只有一个
    while(number[0] == '-') {
        this->neg = !this->neg;
        number.erase(0, 1);
    }

    reverse(number.begin(), number.end());
    // 去除前导零
    while(number.size() > 1 && number[number.size() - 1] == '0')
        number.erase(number.size() - 1, number.size());

    // 空字符串视为0
    if (number == "") {
        number = "0";
    }
    this->number = number;
    if (number == "0") {
        this->neg = false;
    }
}

bool operator == (BigInt first, BigInt second) {
    return first.neg == second.neg && first.number == second.number;
}

bool operator != (BigInt first, BigInt second) {
    return first.neg != second.neg || first.number != second.number;
}

bool operator < (BigInt first, BigInt second) {
    // 先排除特殊情况
    // 1. 一正一负
    if (first.neg && !second.neg) return true;
    if (!first.neg && second.neg) return false;

    // 2. 同时为负，转化为 > 问题求解
    if(first.neg && second.neg){
        first.neg = false;
        second.neg = false;

        return first > second;
    }
    // 3. 同时为负
    if (first.number.size() < second.number.size()) return true;
    if (first.number.size() > second.number.size()) return false;
    // 长度相同，按位比较
    std::string temp1 = first.number; reverse(temp1.begin(), temp1.end());
    std::string temp2 = first.number; reverse(temp2.begin(), temp2.end());

    for (int i = 0; i < temp1.size(); ++ i) {
        if (temp1[i] > temp2[i]) return false;
        else if (temp1[i] < temp2[i]) return true;
    }
    return false;
}

bool operator <= (BigInt first, BigInt second) {
    return first < second || first == second;
}

bool operator > (BigInt first, BigInt second) {
    // 先排除特殊情况
    // 1. 一正一负
    if (first.neg && !second.neg) return false;
    if (!first.neg && second.neg) return true;

    // 2. 同时为负，转化为 < 问题求解
    if(first.neg && second.neg){
        first.neg = false;
        second.neg = false;

        return first < second;
    }
    // 3. 同时为负
    if (first.number.size() < second.number.size()) return false;
    if (first.number.size() > second.number.size()) return true;
    // 长度相同，按位比较
    std::string temp1 = first.number; reverse(temp1.begin(), temp1.end());
    std::string temp2 = first.number; reverse(temp2.begin(), temp2.end());

    for (int i = 0; i < temp1.size(); ++ i) {
        if (temp1[i] > temp2[i]) return true;
        else if (temp1[i] < temp2[i]) return false;
    }
    return false;
}

bool operator >= (BigInt first, BigInt second) {
    return first > second || first == second;
}

std::istream& operator >> (std::istream& in, BigInt &bigint) {
    std::string number; in >> number;

    bigint.neg = false;

    while(number[0] == '-'){
        bigint.neg = !bigint.neg;
        number.erase(0, 1);
    }

    reverse(number.begin(), number.end());

    while(number.size() > 1 && number[number.size() - 1] == '0')
        number.erase(number.size() - 1, number.size());

    bigint.number = number;

    if(number == "0")
        bigint.neg = false;

    return in;
}

std::ostream& operator << (std::ostream& out, const BigInt &bigint) {
    std::string number = bigint.number;
    reverse(number.begin(), number.end());

    if(bigint.neg)
        number = '-' + number;

    out << number;

    return out;
}

BigInt abs(BigInt bigint){
    bigint.neg = false;

    return bigint;
}

void swap(BigInt &first, BigInt &second) {
    BigInt temp = first;
    first = second;
    second = temp;
}

int BigInt::size(){
    return this -> number.size();
}

BigInt operator + (BigInt first, BigInt second){
    // 分为四种情况 ++，+-，-+，--
    // 1. +- 转化为减法
    if(!first.neg && second.neg){
        second.neg = false;
        return first - second;
    }
    // 2. -+ 转化为减法
    if(first.neg && !second.neg){
        first.neg = false;
        return second - first;
    }

    bool neg = false; // 标记 正数加法还是负数加法
    // 3. -- 转化为正数加法
    if(first.neg && second.neg){
        neg = true;
        first.neg = second.neg = false;
    }

    // 4. ++ 正整数加法
    int n = first.size();
    int m = second.size();

    int carry = 0; // 进位器：保留结果和下一位进位情况

    std::string result;

    for(int i = 0; i < std::max(n, m); i++){
        if(i < n) carry += first.number[i] - '0';
        if(i < m) carry += second.number[i] - '0';

        result += carry % 10 + '0';
        carry /= 10;
    }

    if(carry != 0)
        result += carry + '0';

    reverse(result.begin(), result.end());

    BigInt result_(result);
    result_.neg = neg;

    return result_;
}

BigInt operator + (BigInt bigInt) {
    return bigInt;
}

BigInt operator - (BigInt first, BigInt second){
    // 1. second 为负数，转化为加法。若为+-，转化为++；若为--，转化为-+，经过加法转化为两个正数作差
    if(second.neg){
        second.neg = false;
        return first + second;
    }
    // 2. 若first为负，经过上面的处理，这里second一定不为负，直接转化为加法 --
    if(first.neg){
        second.neg = true;
        return first + second;
    }

    bool neg = false; // 标记
    // 3. 结果为剩下的只有 ++ 减法
    if (first < abs(second)) {
        neg = true;
        swap(first, second);
        first = abs(first); // 这里面包含++，--
    }

    int n = first.size();
    int m = second.size();

    int carry = 0;

    std::string result;

    for(int i = 0; i < std::max(n, m); i++){
        int add = carry;

        if(i < n) add += first.number[i] - '0';
        if(i < m) add -= second.number[i] - '0';

        if(add < 0){
            carry = -1;
            result += add + 10 + '0';
        } else {
            carry = 0;
            result += add + '0';
        }
    }
    reverse(result.begin(), result.end());
    BigInt result_(result);
    result_.neg = neg;
    return result_;
}

BigInt operator - (BigInt second){
    BigInt first("0"); return first - second;
}

BigInt operator * (BigInt first, BigInt second){
    bool neg = (first.neg != second.neg);

    first.neg = false;
    second.neg = false;

    int n = first.size();
    int m = second.size();

    BigInt result_;

    // 一位一位乘，然后加法
    for(int i = 0; i < n; i++){
        int carry = 0;
        std::string result;

        for(int j = 0; j < i; j++)
            result += '0'; // 先加上位数

        for(int j = 0; j < m; j++){
            int add = carry + (first.number[i] - '0') * (second.number[j] - '0');
            carry = add / 10;
            result += add % 10 + '0';
        }

        if(carry != 0) // 由于一位一位乘所以，最高进位不超过10
            result += carry + '0';

        reverse(result.begin(), result.end());
        // 这里用string给current赋值，所以要先反转。
        BigInt current(result);

        result_ += current;
    }

    result_.neg = neg;

    return result_;
}

BigInt operator / (BigInt first, BigInt second){
    if(second == "0")
        throw "Division with 0";

    bool neg = (first.neg != second.neg);
    first.neg = false;
    second.neg = false;

    BigInt quotient;
    int i = first.size() - 1;

    BigInt current(first.number[i] - '0');
    --i;

    while(true) {
        BigInt result = current;
        bool l = false;
        while(result < second && i >= 0) {
            result = result * 10 + (first.number[i--] - '0');
            if(l)
                quotient *= 10;
            l = true;
        }

        int c = 0;
        BigInt result_(result);
        while(result_ >= second) {
            result_ -= second;
            c++;
        }

        quotient = quotient * 10 + c;
        current = result_;

        if(i < 0)
            break;
    }

    quotient.neg = neg;

    return quotient;
}

BigInt operator % (BigInt first, BigInt second){
    if(second == "0")
        throw "Modulo with 0";

    first.neg = false;
    second.neg = false;

    int i = first.size() - 1;

    BigInt current(first.number[i] - '0');

    --i;

    while(true){
        BigInt result = current;

        while(result < second && i >= 0)
            result = result * 10 + (first.number[i--] - '0');

        int c = 0;

        BigInt result_(result);

        while(result_ >= second){
            result_ -= second;
            c++;
        }

        current = result_;

        if(i < 0)
            break;
    }

    current.neg = second.neg;

    return current;
}
