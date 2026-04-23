#include <iostream>
using namespace std;

// ❌ 危險！回傳區域變數的參考（懸空參考）
// 函數結束後，local 被銷毀，回傳的參考指向無效記憶體！
// 大多數編譯器會對此發出警告。
/*
int& dangerousFunc() {
    int local = 42;
    return local;   // ⚠️ warning: reference to local variable returned
}
*/

// ❌ 同樣的問題：string
/*
string& dangerousString() {
    string s = "Hello";
    return s;    // ⚠️ s 在函數結束後消失！
}
*/

// ✅ 安全方式一：回傳參數的參考（生命期由呼叫者管理）
int& safeMax(int& a, int& b) {
    return a > b ? a : b;
}

// ✅ 安全方式二：回傳靜態變數（靜態變數整個程式期間存在）
int& getSingleton() {
    static int instance = 0;
    return instance;
}

// ✅ 安全方式三：回傳全域變數
int globalVal = 100;
int& getGlobal() { return globalVal; }

// ✅ 安全方式四：回傳動態配置的記憶體（需要記得釋放）
int& createDynamic() {
    int* p = new int(55);    // heap 上的記憶體，手動管理
    return *p;
}

int main() {
    cout << "=== 懸空參考（已停用，僅作說明）===" << endl;
    cout << "回傳區域變數的參考 → 未定義行為（崩潰/垃圾值）" << endl;
    // int& bad = dangerousFunc();  // ❌ 勿使用！
    // cout << bad;                 // ❌ 未定義行為！

    cout << "\n=== 安全的回傳參考方式 ===" << endl;

    // 方式一：回傳參數的參考
    int x = 5, y = 10;
    safeMax(x, y) = 99;
    cout << "safeMax：y = " << y << "（從 10 改為 99）" << endl;

    // 方式二：回傳靜態變數的參考
    getSingleton() = 42;
    cout << "Singleton = " << getSingleton() << endl;
    ++getSingleton();
    cout << "Singleton++ = " << getSingleton() << endl;

    // 方式三：回傳全域變數的參考
    getGlobal() += 50;
    cout << "globalVal = " << getGlobal() << endl;

    // 方式四：動態配置（需要釋放）
    int& dyn = createDynamic();
    cout << "動態配置值 = " << dyn << endl;
    dyn = 100;
    cout << "修改後 = " << dyn << endl;
    delete &dyn;    // 釋放記憶體

    cout << "\n=== 判斷原則 ===" << endl;
    cout << "問：回傳的變數，函數結束後還存在嗎？" << endl;
    cout << "  是 → 安全（全域、靜態、傳入的參考、heap）" << endl;
    cout << "  否 → 危險！（區域變數）" << endl;

    return 0;
}
