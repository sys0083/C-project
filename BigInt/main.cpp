#include <iostream>
#include "BigInt.h"
using namespace std;


int main() {
    BigInt a("8");
    BigInt b("15");
    cout << (a << 1) << endl;
    cout << (a & b) << endl;
    cout << (a | b) << endl;
    cout << (a ^ b) << endl;

    return 0;
}
