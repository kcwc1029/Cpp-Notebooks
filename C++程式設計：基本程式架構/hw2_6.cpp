// 練習 2-6：資料型別範圍驗證
#include <iostream>
#include <limits>
using namespace std;

int main() {
    cout << "=== 資料型別範圍 ===" << endl;

    cout << "\n[int]" << endl;
    cout << "最小值：" << numeric_limits<int>::min() << endl;
    cout << "最大值：" << numeric_limits<int>::max() << endl;

    cout << "\n[long long]" << endl;
    cout << "最小值：" << numeric_limits<long long>::min() << endl;
    cout << "最大值：" << numeric_limits<long long>::max() << endl;

    cout << "\n[double]" << endl;
    cout << "最小正值：" << numeric_limits<double>::min() << endl;
    cout << "最大值："   << numeric_limits<double>::max() << endl;
    cout << "精確位數："  << numeric_limits<double>::digits10 << endl;

    return 0;
}
