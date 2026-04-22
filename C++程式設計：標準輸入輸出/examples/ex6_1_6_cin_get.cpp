// ex6_1_6_cin_get.cpp
// 示範 cin.get() 讀取單一字元（含空白字元）

#include <iostream>
using namespace std;

int main() {
    char c1, c2, c3;

    cout << "請輸入三個字元（可含空格）：";
    cin.get(c1);
    cin.get(c2);
    cin.get(c3);

    cout << "字元一：[" << c1 << "]" << endl;
    cout << "字元二：[" << c2 << "]" << endl;
    cout << "字元三：[" << c3 << "]" << endl;

    return 0;
}
