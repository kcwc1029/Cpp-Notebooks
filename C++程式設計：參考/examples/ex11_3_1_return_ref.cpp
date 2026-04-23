#include <iostream>
using namespace std;

// 全域陣列（生命期涵蓋整個程式）
int scores[5] = {70, 80, 90, 85, 75};

// ✅ 安全：回傳全域陣列元素的參考
int& getScore(int index) {
    return scores[index];
}

// ✅ 安全：回傳兩個參數中較大者的參考
//         （參數由呼叫者管理，生命期安全）
int& getMax(int& a, int& b) {
    return (a > b) ? a : b;
}

// ✅ 安全：回傳靜態變數的參考
//         （靜態變數在程式結束前一直存在）
int& getCallCount() {
    static int count = 0;
    return count;
}

int main() {
    // 用回傳的參考讀取
    cout << "=== 透過回傳參考讀取 ===" << endl;
    cout << "scores[2] = " << getScore(2) << endl;

    // 用回傳的參考修改（回傳的參考可以作為左值！）
    cout << "\n=== 透過回傳參考修改 ===" << endl;
    getScore(2) = 100;        // 直接修改陣列元素！
    cout << "getScore(2) = 100 後，scores[2] = " << getScore(2) << endl;

    cout << "所有分數：";
    for (int i = 0; i < 5; i++) cout << scores[i] << " ";
    cout << endl;

    // getMax：回傳較大值的參考，直接修改它
    int x = 10, y = 20;
    cout << "\n=== getMax 回傳參考 ===" << endl;
    cout << "x=" << x << ", y=" << y << endl;
    getMax(x, y) = 99;    // 把較大值（y=20）改為 99
    cout << "getMax(x,y)=99 後：x=" << x << ", y=" << y << endl;

    // 靜態計數器：每次呼叫都遞增
    cout << "\n=== 靜態計數器 ===" << endl;
    ++getCallCount();
    ++getCallCount();
    ++getCallCount();
    cout << "呼叫次數：" << getCallCount() << endl;

    // 可以直接對回傳參考做運算
    getCallCount() += 10;
    cout << "+= 10 後：" << getCallCount() << endl;

    return 0;
}
