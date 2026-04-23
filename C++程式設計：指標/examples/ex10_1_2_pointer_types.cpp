// ex10_1_2_pointer_types.cpp
// 示範：不同型別的指標與大小
#include <iostream>
using namespace std;

int main() {
    int    i = 10;
    double d = 3.14;
    char   c = 'A';
    bool   b = true;

    int    *pi = &i;
    double *pd = &d;
    char   *pc = &c;
    bool   *pb = &b;

    cout << "=== 各型別指標 ===" << endl;
    cout << "int    大小：" << sizeof(int)    << " bytes，*pi = " << *pi << endl;
    cout << "double 大小：" << sizeof(double) << " bytes，*pd = " << *pd << endl;
    cout << "char   大小：" << sizeof(char)   << " bytes，*pc = " << *pc << endl;
    cout << "bool   大小：" << sizeof(bool)   << " bytes，*pb = " << *pb << endl;

    cout << "\n=== 指標本身大小（全相同）===" << endl;
    cout << "sizeof(pi) = " << sizeof(pi) << " bytes" << endl;
    cout << "sizeof(pd) = " << sizeof(pd) << " bytes" << endl;
    cout << "sizeof(pc) = " << sizeof(pc) << " bytes" << endl;

    cout << "\n=== 透過指標修改值 ===" << endl;
    *pi = 999;
    *pd = 2.71828;
    cout << "i 變成：" << i << endl;
    cout << "d 變成：" << d << endl;

    return 0;
}
