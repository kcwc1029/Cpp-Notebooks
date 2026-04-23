#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    // === 場景 1：只讀取（不用參考）===
    int arr[] = {1, 2, 3, 4, 5};
    cout << "原始陣列：";
    for (int x : arr) {        // x 是副本，讀取即可
        cout << x << " ";
    }
    cout << endl;

    // === 場景 2：修改元素（必須用參考！）===
    for (int& x : arr) {       // x 是別名，可以修改
        x *= 2;
    }
    cout << "每個元素乘以 2：";
    for (int x : arr) { cout << x << " "; }
    cout << endl;

    // 對照：不用參考的「修改」是無效的
    for (int x : arr) {    // x 是副本，不是別名
        x = 0;             // 只修改副本，原陣列不變！
    }
    cout << "（不用&修改，陣列不變）：";
    for (int x : arr) { cout << x << " "; }
    cout << endl;

    // === 場景 3：大型物件用 const 參考，避免複製 ===
    vector<string> fruits = {"apple", "banana", "cherry", "date", "elderberry"};
    cout << "\n水果清單（const 參考，不複製）：" << endl;
    for (const string& fruit : fruits) {    // 不複製 string
        cout << "  " << fruit << "（" << fruit.length() << " 字元）" << endl;
    }

    // === 場景 4：auto& 自動推導型別 ===
    vector<int> nums = {10, 20, 30, 40, 50};
    for (auto& n : nums) {    // auto 推導為 int，加上 & 就是 int&
        n += 5;
    }
    cout << "\n加 5 後（auto& 修改）：";
    for (auto n : nums) { cout << n << " "; }
    cout << endl;

    // === 場景 5：const auto& 讀取複雜物件 ===
    vector<vector<int>> matrix = {{1,2,3}, {4,5,6}, {7,8,9}};
    cout << "\n矩陣（const auto& 讀取）：" << endl;
    for (const auto& row : matrix) {      // row 是 const vector<int>&
        for (const auto& val : row) {     // val 是 const int&
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
