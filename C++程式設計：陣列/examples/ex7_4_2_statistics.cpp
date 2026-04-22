// ex7_4_2_statistics.cpp
// 示範陣列統計計算：平均、變異數、標準差、及格率

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>
using namespace std;

double calcMean(const int arr[], int n) {
    assert(n > 0);
    int sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return (double)sum / n;
}

double calcVariance(const int arr[], int n) {
    assert(n > 0);
    double mean = calcMean(arr, n);
    double sumSq = 0;
    for (int i = 0; i < n; i++) {
        double diff = arr[i] - mean;
        sumSq += diff * diff;
    }
    return sumSq / n;
}

int main() {
    int scores[] = {85, 92, 78, 95, 88, 73, 99, 61};
    int n = sizeof(scores) / sizeof(scores[0]);

    double mean   = calcMean(scores, n);
    double var    = calcVariance(scores, n);
    double stddev = sqrt(var);

    cout << fixed << setprecision(2);
    cout << "人數：" << n << endl;
    cout << "平均：" << mean    << endl;
    cout << "變異數：" << var   << endl;
    cout << "標準差：" << stddev << endl;

    int pass = 0;
    for (int i = 0; i < n; i++) if (scores[i] >= 60) pass++;
    cout << "及格率：" << (double)pass / n * 100 << "%" << endl;

    return 0;
}
