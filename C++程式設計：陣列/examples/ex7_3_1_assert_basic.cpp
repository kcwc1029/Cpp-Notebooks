// ex7_3_1_assert_basic.cpp
// 示範 assert 基本用法：斷言條件，違反時終止程式並顯示位置

#include <iostream>
#include <cassert>
using namespace std;

int divide(int a, int b) {
    assert(b != 0);   // 斷言 b 不為零，若違反則程式立即終止
    return a / b;
}

int main() {
    cout << divide(10, 2) << endl;   // 5，assert 通過

    // 以下會觸發 assert：
    // cout << divide(10, 0) << endl;

    return 0;
}
