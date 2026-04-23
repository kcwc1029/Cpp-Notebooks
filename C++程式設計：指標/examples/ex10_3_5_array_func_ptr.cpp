// ex10_3_5_array_func_ptr.cpp
// 示範：以指標傳遞陣列給函式
#include <iostream>
using namespace std;

void fill(int *arr, int n, int val) {
    for (int i = 0; i < n; i++) arr[i] = val;
}

void print(const int *arr, int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

int sum(const int *arr, int n) {
    int total = 0;
    for (int i = 0; i < n; i++) total += arr[i];
    return total;
}

double average(const int *arr, int n) {
    return (double)sum(arr, n) / n;
}

// 泡沫排序（升序）
void bubble_sort(int *arr, int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

int main() {
    int data[6];

    fill(data, 6, 7);
    cout << "填入 7：";    print(data, 6);

    // 手動設值
    int scores[] = {78, 92, 55, 88, 100, 63};
    cout << "原始成績：";  print(scores, 6);
    cout << "總和：" << sum(scores, 6) << endl;
    cout << "平均：" << average(scores, 6) << endl;

    bubble_sort(scores, 6);
    cout << "排序後：";    print(scores, 6);

    return 0;
}
