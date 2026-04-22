// ex7_4_7_histogram.cpp
// 示範用陣列統計成績分布並繪製文字直方圖

#include <iostream>
using namespace std;

int main() {
    int scores[] = {85, 92, 78, 95, 88, 73, 99, 61, 54, 82, 76, 68, 91, 55, 83};
    int n = sizeof(scores) / sizeof(scores[0]);

    // grade[0]=F(<60), grade[1]=D(60-69), grade[2]=C(70-79),
    // grade[3]=B(80-89), grade[4]=A(90-100)
    int grade[5] = {};

    for (int i = 0; i < n; i++) {
        if      (scores[i] >= 90) grade[4]++;
        else if (scores[i] >= 80) grade[3]++;
        else if (scores[i] >= 70) grade[2]++;
        else if (scores[i] >= 60) grade[1]++;
        else                      grade[0]++;
    }

    char labels[] = {'F', 'D', 'C', 'B', 'A'};

    cout << "成績分布（共 " << n << " 位學生）" << endl;
    cout << "─────────────────────────────" << endl;

    for (int i = 4; i >= 0; i--) {
        cout << labels[i] << " | ";
        for (int j = 0; j < grade[i]; j++) cout << "█";
        cout << " " << grade[i] << endl;
    }

    cout << "─────────────────────────────" << endl;

    return 0;
}
