#include <iostream>
using namespace std;

int main() {
    cout << "=== 各型別大小 ===" << endl;
    cout << "bool:        " << sizeof(bool)        << " bytes" << endl;
    cout << "char:        " << sizeof(char)        << " bytes" << endl;
    cout << "short:       " << sizeof(short)       << " bytes" << endl;
    cout << "int:         " << sizeof(int)         << " bytes" << endl;
    cout << "long:        " << sizeof(long)        << " bytes" << endl;
    cout << "long long:   " << sizeof(long long)   << " bytes" << endl;
    cout << "float:       " << sizeof(float)       << " bytes" << endl;
    cout << "double:      " << sizeof(double)      << " bytes" << endl;
    cout << "long double: " << sizeof(long double) << " bytes" << endl;

    int x = 42;
    cout << "\n變數 x 的大小：" << sizeof(x) << " bytes" << endl;

    return 0;
}
