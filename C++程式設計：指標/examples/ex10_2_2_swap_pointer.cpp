// ex10_2_2_swap_pointer.cpp
// 示範：用指標實作 swap（交換兩變數）
#include <iostream>
using namespace std;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap_double(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

// 排序三個數（氣泡排序概念）
void sort3(int *a, int *b, int *c) {
    if (*a > *b) swap(a, b);
    if (*b > *c) swap(b, c);
    if (*a > *b) swap(a, b);
}

int main() {
    cout << "=== 整數 swap ===" << endl;
    int x = 10, y = 20;
    cout << "交換前：x = " << x << "，y = " << y << endl;
    swap(&x, &y);
    cout << "交換後：x = " << x << "，y = " << y << endl;

    cout << "\n=== 浮點數 swap ===" << endl;
    double price1 = 99.9, price2 = 199.9;
    cout << "交換前：p1 = " << price1 << "，p2 = " << price2 << endl;
    swap_double(&price1, &price2);
    cout << "交換後：p1 = " << price1 << "，p2 = " << price2 << endl;

    cout << "\n=== 排序三個數 ===" << endl;
    int a = 30, b = 10, c = 20;
    cout << "排序前：" << a << " " << b << " " << c << endl;
    sort3(&a, &b, &c);
    cout << "排序後：" << a << " " << b << " " << c << endl;

    return 0;
}
