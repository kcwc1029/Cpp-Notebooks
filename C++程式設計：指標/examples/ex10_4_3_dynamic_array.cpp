// ex10_4_3_dynamic_array.cpp
// 示範：new[]/delete[] 動態陣列
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "輸入學生人數：";
    cin >> n;

    // 動態配置整數陣列
    int *scores = new int[n];

    cout << "輸入 " << n << " 個成績：" << endl;
    for (int i = 0; i < n; i++) {
        cout << "第 " << i+1 << " 位：";
        cin >> scores[i];
    }

    // 計算平均
    double total = 0;
    for (int i = 0; i < n; i++) total += scores[i];
    double avg = total / n;

    // 統計高於平均的人數
    int above = 0;
    for (int i = 0; i < n; i++) {
        if (scores[i] > avg) above++;
    }

    cout << "\n=== 成績統計 ===" << endl;
    cout << "平均分：" << avg << endl;
    cout << "高於平均：" << above << " 人" << endl;

    // 重要：釋放動態陣列用 delete[]
    delete[] scores;
    scores = nullptr;
    cout << "記憶體已釋放（delete[]）" << endl;

    cout << "\n=== 動態配置雙精度陣列 ===" << endl;
    int m = 4;
    double *data = new double[m]{1.1, 2.2, 3.3, 4.4};
    for (int i = 0; i < m; i++) cout << data[i] << " ";
    cout << endl;
    delete[] data;
    data = nullptr;

    return 0;
}
