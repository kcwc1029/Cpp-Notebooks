// ex10_3_1_array_pointer.cpp
// 示範：陣列名稱即指標、指標算術
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *p = arr;   // 等同 int *p = &arr[0];

    cout << "=== 陣列名稱 = 首元素位址 ===" << endl;
    cout << "arr      = " << arr      << endl;
    cout << "&arr[0]  = " << &arr[0]  << endl;
    cout << "p        = " << p        << endl;
    cout << "（三個都相同）" << endl;

    cout << "\n=== 指標算術 ===" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "p+" << i << " = " << (p+i)
             << "，*(p+" << i << ") = " << *(p+i) << endl;
    }

    cout << "\n=== p++ 走訪 ===" << endl;
    int *q = arr;
    while (q < arr + 5) {
        cout << *q << " ";
        q++;
    }
    cout << endl;

    cout << "\n=== 指標相減（得到元素間距）===" << endl;
    int *first = arr;
    int *last  = arr + 4;
    cout << "last - first = " << last - first << endl;   // 4

    return 0;
}
