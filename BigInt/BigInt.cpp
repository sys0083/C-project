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
    // 3. 同时为正
    if (first.number.size() < second.number.size()) return true;
    if (first.number.size() > second.number.size()) return false;
    // 长度相同，按位比较
    std::string temp1 = first.number; reverse(temp1.begin(), temp1.end());
    std::string temp2 = second.number; reverse(temp2.begin(), temp2.end());

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
    // 3. 同时为正
    if (first.number.size() < second.number.size()) return false;
    if (first.number.size() > second.number.size()) return true;
    // 长度相同，按位比较
    std::string temp1 = first.number; reverse(temp1.begin(), temp1.end());
    std::string temp2 = second.number; reverse(temp2.begin(), temp2.end());

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

    BigInt answer = 0; // 最终结果
    BigInt res = 0; // 余数情况
    for (int i = first.size() - 1; i >= 0; -- i) {
        res *= 10;
        res += (first.number[i] - '0');
        int cnt = 0;
        while (res >= second) {
            res -= second;
            cnt ++;
        }
        answer *= 10;
        answer += cnt;
    }

    answer.neg = neg;
    return answer;
}

BigInt operator % (BigInt first, BigInt second){
    if(second == "0")
        throw "Modulo with 0";

    bool neg = (first.neg != second.neg);
    first.neg = false;
    second.neg = false;

    BigInt answer = 0; // 最终结果
    BigInt res = 0; // 余数情况
    for (int i = first.size() - 1; i >= 0; -- i) {
        res *= 10;
        res += (first.number[i] - '0');
        int cnt = 0;
        while (res >= second) {
            res -= second;
            cnt ++;
        }
        answer *= 10;
        answer += cnt;
    }

    res.neg = neg;
    return res;
}

BigInt pow(BigInt x, BigInt y, BigInt mod = 0) {
    if(mod != 0)
        x %= mod;

    BigInt res = 1;
    while(y != 0){
        if(y % 2 == 1){
            res *= x;
            if(mod != 0)
                res %= mod;
        }
        x *= x;
        if(mod != 0)
            x %= mod;
        y /= 2;
    }
    return res;
}

BigInt operator & (BigInt first, BigInt second) {
    std::string a = first.int_to_base(2);
    std::string b = second.int_to_base(2);

    // 取两个数二进制位数最小者
    unsigned int n = std::min(a.size(), b.size());

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    std::string result(n, '~');

    for(unsigned int i = 0; i < n; i++){
        if(a[i] == '1' && b[i] == '1')
            result[i] = '1';
        else
            result[i] = '0';
    }

    reverse(result.begin(), result.end());

    return BigInt().base_to_int(result, 2);
}

BigInt operator | (BigInt first, BigInt second) {
    std::string a = first.int_to_base(2);
    std::string b = second.int_to_base(2);

    // 取两个数二进制位数最小者
    unsigned int n = std::min(a.size(), b.size());

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    std::string result(n, '~');

    for(unsigned int i = 0; i < n; i++){
        if(a[i] == '1' || b[i] == '1')
            result[i] = '1';
        else
            result[i] = '0';
    }

    reverse(result.begin(), result.end());

    return BigInt().base_to_int(result, 2);
}

// 按位异或
BigInt operator ^ (BigInt first, BigInt second) {
    std::string a = first.int_to_base(2);
    std::string b = second.int_to_base(2);

    // 取两个数二进制位数最大者
    unsigned int n = std::max(a.size(), b.size());

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    std::string result(n, '~');

    for(unsigned int i = 0; i < n; i ++){
        if (i < a.size() && i < b.size()) {
            if (a[i] != b[i]) {
                result[i] = '1';
            }
            else {
                result[i] = '0';
            }
        }
        else {
            if (a[i] == '1' || b[i] == '1') {
                result[i] = '1';
            }
            else {
                result[i] = '0';
            }
        }
    }

    reverse(result.begin(), result.end());

    return BigInt().base_to_int(result, 2);
}

BigInt operator << (BigInt first, BigInt second){
    BigInt x = pow(2, second);
    return first * x;
}

BigInt operator >> (BigInt first, BigInt second){
    BigInt x = pow(2, second);
    return first / x;
}

int BigInt::to_int(BigInt bigint) {
    int n = 0;
    for (int i = bigint.size() - 1; i >= 0; -- i) {
        n *= 10;
        n += (bigint.number[i] - '0');
    }
    return n;
}

std::string BigInt::int_to_base(int base) {
    std::string result;

    BigInt bigInt(*this);
    while (bigInt != 0) {
        BigInt res = bigInt % base; // 保存结果用于判断

        // 如果整型用于判断
        if (res >= 10)
            result += (char)(to_int(res / 10) + 'A');
        else
            result += (char)(to_int(res) + '0');

        bigInt /= base;
    }
    reverse(result.begin(), result.end());

    return result;
}

BigInt BigInt::base_to_int(std::string str, int base) {
    BigInt result;

    for (int i = 0;i < str.size(); ++ i) {
        result *= base;
        if('0' <= str[i] && str[i] <= '9')
            result += str[i] - '0';
        else
            result += (str[i] - 'A') + 10;
    }

    return result;
}