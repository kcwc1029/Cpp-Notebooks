// ex10_2_3_multiple_return.cpp
// 示範：透過指標參數「回傳」多個結果
#include <iostream>
#include <cmath>
using namespace std;

// 同時計算最大值和最小值
void min_max(int arr[], int n, int *min_val, int *max_val) {
    *min_val = arr[0];
    *max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < *min_val) *min_val = arr[i];
        if (arr[i] > *max_val) *max_val = arr[i];
    }
}

// 解一元二次方程 ax^2 + bx + c = 0
// 回傳根的數量，根透過 r1, r2 輸出
int solve_quadratic(double a, double b, double c,
                    double *r1, double *r2) {
    double disc = b*b - 4*a*c;
    if (disc < 0) return 0;            // 無實數根
    if (disc == 0) {
        *r1 = *r2 = -b / (2*a);
        return 1;                       // 一個重根
    }
    *r1 = (-b + sqrt(disc)) / (2*a);
    *r2 = (-b - sqrt(disc)) / (2*a);
    return 2;                           // 兩個相異根
}

int main() {
    cout << "=== 成績最大最小值 ===" << endl;
    int scores[] = {78, 92, 55, 88, 100, 63};
    int n = sizeof(scores) / sizeof(scores[0]);
    int lo, hi;

    min_max(scores, n, &lo, &hi);
    cout << "最低分：" << lo << endl;
    cout << "最高分：" << hi << endl;

    cout << "\n=== 解一元二次方程 ===" << endl;
    double r1, r2;

    int cnt = solve_quadratic(1, -5, 6, &r1, &r2);
    cout << "x^2 - 5x + 6 = 0：" << cnt << " 個根" << endl;
    if (cnt >= 1) cout << "  r1 = " << r1 << endl;
    if (cnt >= 2) cout << "  r2 = " << r2 << endl;

    cnt = solve_quadratic(1, -2, 1, &r1, &r2);
    cout << "x^2 - 2x + 1 = 0：" << cnt << " 個根，r = " << r1 << endl;

    cnt = solve_quadratic(1, 0, 1, &r1, &r2);
    cout << "x^2 + 1 = 0：" << cnt << " 個實數根" << endl;

    return 0;
}
