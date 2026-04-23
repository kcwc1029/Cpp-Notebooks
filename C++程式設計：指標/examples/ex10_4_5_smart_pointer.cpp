// ex10_4_5_smart_pointer.cpp
// 示範：unique_ptr 智慧指標（現代 C++ 推薦）
#include <iostream>
#include <memory>
using namespace std;

int main() {
    cout << "=== unique_ptr 基本用法 ===" << endl;
    {
        unique_ptr<int> p = make_unique<int>(100);
        cout << "值：" << *p << endl;
        *p = 200;
        cout << "修改後：" << *p << endl;
        cout << "位址：" << p.get() << endl;
    }   // p 在此作用域結束，自動 delete，不需手動管理
    cout << "已自動釋放（作用域結束）" << endl;

    cout << "\n=== unique_ptr 動態陣列 ===" << endl;
    {
        int n = 5;
        unique_ptr<int[]> arr = make_unique<int[]>(n);
        for (int i = 0; i < n; i++) arr[i] = (i+1) * 10;
        cout << "動態陣列：";
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << endl;
    }   // arr 自動 delete[]
    cout << "陣列已自動釋放" << endl;

    cout << "\n=== unique_ptr 轉移所有權 ===" << endl;
    unique_ptr<double> a = make_unique<double>(3.14);
    cout << "a 的值：" << *a << endl;

    unique_ptr<double> b = move(a);   // 所有權轉移給 b
    if (a == nullptr) cout << "a 已失去所有權（nullptr）" << endl;
    cout << "b 的值：" << *b << endl;
    // b 離開 main 時自動釋放

    cout << "\n=== shared_ptr 共享所有權 ===" << endl;
    {
        shared_ptr<int> sp1 = make_shared<int>(999);
        cout << "sp1 = " << *sp1 << "，引用計數：" << sp1.use_count() << endl;
        {
            shared_ptr<int> sp2 = sp1;   // 共享
            cout << "sp2 = " << *sp2 << "，引用計數：" << sp1.use_count() << endl;
        }   // sp2 消失，但記憶體仍保留（因為 sp1 還存在）
        cout << "sp2 結束後引用計數：" << sp1.use_count() << endl;
    }   // sp1 消失，引用計數歸零，自動釋放
    cout << "sp1 結束後自動釋放" << endl;

    return 0;
}
