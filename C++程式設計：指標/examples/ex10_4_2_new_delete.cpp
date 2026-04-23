// ex10_4_2_new_delete.cpp
// 示範：new/delete 動態記憶體配置
#include <iostream>
using namespace std;

int main() {
    cout << "=== 動態配置 int ===" << endl;
    int *p = new int;        // 配置，未初始化
    *p = 42;
    cout << "位址：" << p << "，值：" << *p << endl;
    delete p;
    p = nullptr;

    int *q = new int(100);   // 配置並初始化
    cout << "初始化為 100：" << *q << endl;
    *q = 200;
    cout << "修改後：" << *q << endl;
    delete q;
    q = nullptr;

    cout << "\n=== 動態配置 double ===" << endl;
    double *d = new double(3.14159);
    cout << "π ≈ " << *d << endl;
    delete d;
    d = nullptr;

    cout << "\n=== 動態配置 char ===" << endl;
    char *c = new char('Z');
    cout << "字元：" << *c << endl;
    delete c;
    c = nullptr;

    cout << "\n=== delete nullptr 是安全的 ===" << endl;
    int *safe = nullptr;
    delete safe;            // 不做任何事，不會崩潰
    cout << "刪除 nullptr：安全" << endl;

    cout << "\n記憶體管理完成，程式正常結束" << endl;
    return 0;
}
