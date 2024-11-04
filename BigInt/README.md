# 2024.10.25

# 项目介绍
    近期在学习高精度算法，想着利用c++封装一个BigInt类进行任意长度的整数运算，顺便复习一下c++面向对象编程、重载运算符等相关知识。

主要参考了一下内容

[3. 六大类运算符_运算符有哪几种-CSDN博客](https://blog.csdn.net/weixin_36881846/article/details/104734666)

[c++11 - BigInt class in C++ - Code Review Stack Exchange](https://codereview.stackexchange.com/questions/237690/bigint-class-in-c)

# 环境依赖

C++14


# 目录结构描述
    ├── ReadMe.md           // 帮助文档
    
    ├── BigInt.h            // 函数声明
    
    ├── BigInt.cpp		// 函数定义
    
    ├── BigInt.cpp		// 可执行文件，进行测试

# 设计思路

主要利用字符串进行存储，由于整型运算时涉及位数对齐的问题，所以我们采用逆序存储的方式。
主要的**成员属性**为存储数值的字符串**number**和符号**neg**(是否为负数，负数为true，正数为false)

## 构造函数

考虑到不同应用情况下，创建大整型的方式比较多(包括一些强制类型转换)，所以创建可以多种构造函数，包括但不限于如下函数

``` c++
BigInt(const BigInt& other); // 拷贝构造函数
BigInt(int number);// 利用整型构造
BigInt(long long int number);// 利用长整型
BigInt(unsigned long long int number);// 利用无符号长整型
BigInt(const char *number);// 利用字符数组
BigInt(std::string number);// 利用字符串
```

## 比较运算符

```c++
friend bool operator == (BigInt first, BigInt second);
friend bool operator != (BigInt first, BigInt second);
friend bool operator < (BigInt first, BigInt second);
friend bool operator <= (BigInt first, BigInt second);
friend bool operator > (BigInt first, BigInt second);
friend bool operator >= (BigInt first, BigInt second);
```

## 算术运算符

在设计算数运算符时，我们主要利用转化的思想将一些不好处理的问题（例如负数）进行转化。

- 加法

> 分为四种情况 ++，+-，-+，--
> >++和--可以都用++实现，
> > +-、-+转化为正数减法

- 减法

> 先处理两种特殊情况 x- 和 -+ 和 ++（x为任意字符）
> > x- 转化为加法。若为+-，转化为++；若为--，转化为-+，经过加法转化为两个正数作差。
> >
> > -+ 转化为--加法。（经过上面的处理，这里第二个元素一定不为负，直接转化为加法 --）
>
> 只剩下 ++
> > 直接进行正数减法
> >

- 乘法

> 直接按位计算，保留当前位的计算结果，然后进行累加。

- 除法
> 除法实现思路：利用高精度减法实现除法，毕竟除数可能会超过 int 的最大范围。

- 取模
> 取模实现思路：直接取除法余数即可。

- 指数取幂
> 利用快速幂算法和前面封装好的算法进行。

```c++
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
// pow快速幂
BigInt pow(BigInt x, BigInt y, BigInt mod = 0);
```

## 位运算符

位运算主要解决十进制转二进制的问题

- 主要利用下面来处理进制转化的问题

```c++
// 将个位数大小的高精度整型数转为int
int to_int(BigInt bigint); 
// 将高精度整型转化为base进制的数
std::string int_to_base(int base);
// 将base进制的数转化为高精度整型
BigInt base_to_int(std::string str, int base);
```


主要重载的位运算符有&、|、^、>>、<<。

```c++
// 按位与
friend BigInt operator & (BigInt first, BigInt second);
// 按位或
friend BigInt operator | (BigInt first, BigInt second);
// 按位异或
friend BigInt operator ^ (BigInt first, BigInt second);
// 左移
friend BigInt operator << (BigInt first, BigInt second);
// 右移
friend BigInt operator >> (BigInt first, BigInt second);
```



# 版本内容更新

###### v1.0.0: 
```
主要实现了BigInt类的构造函数、比较运算符的重载、加减乘等运算符的重载。后续运算符待更新。
```

###### v2.0.0:  

```
更新了除法和取模运算，以及位运算的运算符重载。
```

