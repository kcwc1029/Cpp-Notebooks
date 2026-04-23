// ex10_3_2_ptr_array_equiv.cpp
// 示範：arr[i] 和 *(arr+i) 完全等價
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *p = arr;

    cout << "=== 四種等價寫法 ===" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "索引 " << i << "："
             << "arr[i]=" << arr[i]
             << "  *(arr+i)=" << *(arr+i)
             << "  p[i]=" << p[i]
             << "  *(p+i)=" << *(p+i) << endl;
    }

    cout << "\n=== 使用 p++ 走訪（最常見慣用法）===" << endl;
    for (int *q = arr; q < arr + 5; q++) {
        cout << *q << " ";
    }
    cout << endl;

    cout << "\n=== 反向走訪 ===" << endl;
    for (int *q = arr + 4; q >= arr; q--) {
        cout << *q << " ";
    }
    cout << endl;

    cout << "\n=== 用指標修改陣列 ===" << endl;
    for (int *q = arr; q < arr + 5; q++) {
        *q *= 2;
    }
    for (int i = 0; i < 5; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
