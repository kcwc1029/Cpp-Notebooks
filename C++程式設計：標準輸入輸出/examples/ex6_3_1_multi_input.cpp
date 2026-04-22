// ex6_3_1_multi_input.cpp
// 示範一次讀取多個變數（用空白或換行分隔）

#include <iostream>
using namespace std;

int main() {
    int a, b, c;

    cout << "請輸入三個整數（以空格分隔）：";
    cin >> a >> b >> c;   // 可以用空格或按 Enter 分隔

    cout << "你輸入的三個數是：" << a << "、" << b << "、" << c << endl;
    cout << "總和：" << a + b + c << endl;
    cout << "平均：" << (a + b + c) / 3.0 << endl;

    return 0;
}
