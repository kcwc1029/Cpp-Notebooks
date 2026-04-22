// ex6_2_4_cerr_clog.cpp
// 示範 cerr（無緩衝錯誤輸出）與 clog（有緩衝日誌輸出）

#include <iostream>
using namespace std;

int main() {
    int divisor;
    cout << "請輸入除數：";
    cin >> divisor;

    if (divisor == 0) {
        cerr << "[錯誤] 除數不能為零！" << endl;   // 嚴重錯誤用 cerr，立即輸出
        return 1;   // 非零回傳值代表程式異常結束
    }

    clog << "[日誌] 正在計算 100 / " << divisor << endl;   // 一般日誌用 clog
    cout << "結果：" << 100.0 / divisor << endl;

    return 0;
}
