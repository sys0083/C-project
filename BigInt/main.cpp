#include <iostream>
#include "BigInt.h"
using namespace std;


int main() {
    BigInt a("19");
    BigInt b("20");
    BigInt c("-10001");
    BigInt d(-99999999999999);
//    std::cout << a - b << std::endl;
//    std::cout << -a - b << std::endl;
//    std::cout << a - (-b) << std::endl;
//    std::cout << -a - (-b) << std::endl;

//    BigInt e = 0;
    cout << a * b << endl;

    return 0;
}