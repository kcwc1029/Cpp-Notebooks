#include <iostream>
#include <string>
using namespace std;

// ❌ 傳值：每次呼叫都複製整個 string（對長字串代價高）
void print_by_value(string s) {
    cout << "[傳值]       " << s << endl;
}

// ✅ 傳 const 參考：不複製，只讀，效率高
void print_by_cref(const string& s) {
    cout << "[const 參考] " << s << endl;
    // s += "!";   // ❌ 編譯錯誤！const 參考不能修改
}

// 計算字串中某字元出現的次數
int countChar(const string& s, char target) {
    int count = 0;
    for (char c : s) {
        if (c == target) count++;
    }
    return count;
}

// 同時回傳最小值和最大值（用參考作為輸出參數）
void findMinMax(const int arr[], int size, int& minVal, int& maxVal) {
    minVal = maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }
}

// 計算平均值（const 陣列參考）
double calcAverage(const int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) sum += arr[i];
    return (double)sum / size;
}

int main() {
    string message = "Hello, C++ World!";

    print_by_value(message);    // 複製一份
    print_by_cref(message);     // 不複製

    // const 參考可以直接接受字串字面值
    print_by_cref("直接傳字串字面值也沒問題");

    cout << "\n'l' 在 \"" << message << "\" 中出現：";
    cout << countChar(message, 'l') << " 次" << endl;

    // 用參考作為「輸出參數」，讓函數同時回傳多個值
    int arr[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int minVal, maxVal;
    findMinMax(arr, n, minVal, maxVal);
    cout << "\n陣列統計：" << endl;
    cout << "  最小值：" << minVal << endl;
    cout << "  最大值：" << maxVal << endl;
    cout << "  平均值：" << calcAverage(arr, n) << endl;

    return 0;
}
