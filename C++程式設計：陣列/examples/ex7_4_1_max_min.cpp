// ex7_4_1_max_min.cpp
// 示範在陣列中尋找最大值、最小值及其索引

#include <iostream>
#include <cassert>
using namespace std;

int findMax(const int arr[], int n) {
    assert(n > 0);
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    return maxVal;
}

int findMinIndex(const int arr[], int n) {
    assert(n > 0);
    int minIdx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[minIdx]) minIdx = i;
    }
    return minIdx;
}

int main() {
    int scores[] = {85, 92, 78, 95, 88, 73, 99, 61};
    int n = sizeof(scores) / sizeof(scores[0]);

    cout << "成績：";
    for (int i = 0; i < n; i++) cout << scores[i] << " ";
    cout << endl;

    cout << "最高分：" << findMax(scores, n) << endl;

    int minIdx = findMinIndex(scores, n);
    cout << "最低分：" << scores[minIdx]
         << "（第 " << minIdx + 1 << " 位學生）" << endl;

    return 0;
}
