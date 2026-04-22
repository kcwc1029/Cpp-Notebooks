// project7_student_system_answer.cpp
// 專案解答：學生管理系統 2.0

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
using namespace std;

const int MAX_N    = 30;
const int SUBJECTS = 4;
const string SUBJECT_NAMES[] = {"語文", "數學", "英文", "自然"};

struct Student {
    string name;
    int    scores[SUBJECTS];
    double avg;
    int    rank;
};

void calcAvg(Student students[], int n) {
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < SUBJECTS; j++) sum += students[i].scores[j];
        students[i].avg = sum / SUBJECTS;
    }
}

void sortByAvg(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (students[j].avg < students[j+1].avg) {
                Student tmp    = students[j];
                students[j]    = students[j+1];
                students[j+1]  = tmp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    for (int i = 0; i < n; i++) students[i].rank = i + 1;
}

void printTable(const Student s[], int n) {
    cout << fixed << setprecision(2);
    cout << "╔══════════════════════════════════════════════════════╗\n";
    cout << "║                   成績排行榜                          ║\n";
    cout << "╠═══╦════════╦══════╦══════╦══════╦══════╦════════════╣\n";
    cout << "║ 名║  姓名  ║ 語文 ║ 數學 ║ 英文 ║ 自然 ║    平均    ║\n";
    cout << "╠═══╬════════╬══════╬══════╬══════╬══════╬════════════╣\n";

    for (int i = 0; i < n; i++) {
        cout << "║" << setw(3) << s[i].rank
             << "║" << left  << setw(8) << s[i].name << right
             << "║" << setw(6) << s[i].scores[0]
             << "║" << setw(6) << s[i].scores[1]
             << "║" << setw(6) << s[i].scores[2]
             << "║" << setw(6) << s[i].scores[3]
             << "║" << setw(12) << s[i].avg << "║\n";
    }

    // 統計
    cout << "╠═══╬════════╬══════╬══════╬══════╬══════╬════════════╣\n";

    double classAvg[SUBJECTS] = {};
    int    maxSc[SUBJECTS], minSc[SUBJECTS];
    for (int j = 0; j < SUBJECTS; j++) {
        maxSc[j] = minSc[j] = s[0].scores[j];
        for (int i = 0; i < n; i++) {
            classAvg[j] += s[i].scores[j];
            if (s[i].scores[j] > maxSc[j]) maxSc[j] = s[i].scores[j];
            if (s[i].scores[j] < minSc[j]) minSc[j] = s[i].scores[j];
        }
        classAvg[j] /= n;
    }
    double totalAvg = 0;
    for (int j = 0; j < SUBJECTS; j++) totalAvg += classAvg[j];
    totalAvg /= SUBJECTS;

    cout << "║班均║        ";
    for (int j = 0; j < SUBJECTS; j++) cout << "║" << setw(6) << classAvg[j];
    cout << "║" << setw(12) << totalAvg << "║\n";

    cout << "║最高║        ";
    for (int j = 0; j < SUBJECTS; j++) cout << "║" << setw(6) << maxSc[j];
    cout << "║            ║\n";

    cout << "║最低║        ";
    for (int j = 0; j < SUBJECTS; j++) cout << "║" << setw(6) << minSc[j];
    cout << "║            ║\n";

    cout << "╚═══╩════════╩══════╩══════╩══════╩══════╩════════════╝\n";
}

void queryStudent(const Student s[], int n, const string& name) {
    for (int i = 0; i < n; i++) {
        if (s[i].name == name) {
            cout << s[i].name << " | 排名第 " << s[i].rank << " | ";
            for (int j = 0; j < SUBJECTS; j++) {
                cout << SUBJECT_NAMES[j] << ":" << s[i].scores[j];
                if (j < SUBJECTS-1) cout << " ";
            }
            cout << " | 平均:" << fixed << setprecision(2) << s[i].avg << "\n";
            return;
        }
    }
    cout << "查無此學生：" << name << "\n";
}

int main() {
    Student students[MAX_N];
    int n;

    cout << "學生人數（1~" << MAX_N << "）：";
    cin >> n;
    assert(n >= 1 && n <= MAX_N);

    for (int i = 0; i < n; i++) {
        cout << "\n學生 " << (i+1) << " 姓名：";
        cin >> students[i].name;
        for (int j = 0; j < SUBJECTS; j++) {
            cout << "  " << SUBJECT_NAMES[j] << "：";
            cin >> students[i].scores[j];
        }
    }

    calcAvg(students, n);
    sortByAvg(students, n);

    cout << "\n";
    printTable(students, n);

    cout << "\n查詢學生（輸入姓名，q 結束）：";
    string query;
    while (cin >> query && query != "q") {
        queryStudent(students, n, query);
        cout << "查詢學生（輸入姓名，q 結束）：";
    }

    return 0;
}
