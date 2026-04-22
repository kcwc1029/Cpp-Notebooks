// project6_grade_system_answer.cpp
// 專案解答：學生成績管理系統（基礎版）

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    const int MAX_STUDENTS = 50;
    const int SUBJECTS = 3;

    string names[MAX_STUDENTS];
    int    scores[MAX_STUDENTS][SUBJECTS];
    double avg[MAX_STUDENTS];
    int n;

    cout << "請輸入學生人數：";
    cin >> n;

    // 輸入資料
    for (int i = 0; i < n; i++) {
        cout << "--- 學生 " << (i + 1) << " ---" << endl;

        cout << "姓名：";
        cin.ignore();
        getline(cin, names[i]);

        string subjects[] = {"國文", "數學", "英文"};
        double sum = 0;
        for (int j = 0; j < SUBJECTS; j++) {
            cout << subjects[j] << "：";
            cin >> scores[i][j];
            sum += scores[i][j];
        }
        avg[i] = sum / SUBJECTS;
    }

    // 統計計算
    double classAvg[SUBJECTS] = {};
    int    maxScore[SUBJECTS], minScore[SUBJECTS];
    double totalAvg = 0;

    for (int j = 0; j < SUBJECTS; j++) {
        maxScore[j] = scores[0][j];
        minScore[j] = scores[0][j];
        for (int i = 0; i < n; i++) {
            classAvg[j] += scores[i][j];
            if (scores[i][j] > maxScore[j]) maxScore[j] = scores[i][j];
            if (scores[i][j] < minScore[j]) minScore[j] = scores[i][j];
        }
        classAvg[j] /= n;
    }
    for (int i = 0; i < n; i++) totalAvg += avg[i];
    totalAvg /= n;

    // 表格框線字元
    string H  = "═", V  = "║";
    string TL = "╔", TR = "╗", BL = "╚", BR = "╝";
    string MT = "╦", MB = "╩", ML = "╠", MR = "╣", MC = "╬";

    auto hline = [&](string left_, string mid_, string right_, int w1, int w2) {
        cout << left_;
        for (int k = 0; k < w1; k++) cout << H;
        for (int j = 0; j < 3; j++) {
            cout << mid_;
            for (int k = 0; k < w2; k++) cout << H;
        }
        cout << mid_ << right_;
        for (int k = 0; k < 14; k++) cout << H;
        cout << right_ << "\n";
    };

    // 表頭
    cout << "\n";
    cout << TL;
    for (int k = 0; k < 51; k++) cout << H;
    cout << TR << "\n";

    cout << V;
    cout << setw(30) << right << "班級成績報告";
    cout << setw(21) << left  << "";
    cout << V << "\n";

    // 分隔線
    cout << ML;
    for (int k = 0; k < 15; k++) cout << H;
    for (int j = 0; j < 3; j++) { cout << MT; for (int k = 0; k < 6; k++) cout << H; }
    cout << MT;
    for (int k = 0; k < 14; k++) cout << H;
    cout << MR << "\n";

    // 欄位標題
    cout << V << left  << setw(15) << " 姓名"
         << V << right << setw(6)  << " 國文"
         << V << right << setw(6)  << " 數學"
         << V << right << setw(6)  << " 英文"
         << V << right << setw(14) << "平均"
         << V << "\n";

    // 分隔線
    cout << ML;
    for (int k = 0; k < 15; k++) cout << H;
    for (int j = 0; j < 3; j++) { cout << MC; for (int k = 0; k < 6; k++) cout << H; }
    cout << MC;
    for (int k = 0; k < 14; k++) cout << H;
    cout << MR << "\n";

    // 學生資料
    cout << fixed << setprecision(2);
    for (int i = 0; i < n; i++) {
        cout << V << " " << left  << setw(14) << names[i]
             << V        << right << setw(5)  << scores[i][0] << " "
             << V        << right << setw(5)  << scores[i][1] << " "
             << V        << right << setw(5)  << scores[i][2] << " "
             << V        << right << setw(13) << avg[i]
             << V << "\n";
    }

    // 統計分隔線
    cout << ML;
    for (int k = 0; k < 15; k++) cout << H;
    for (int j = 0; j < 3; j++) { cout << MC; for (int k = 0; k < 6; k++) cout << H; }
    cout << MC;
    for (int k = 0; k < 14; k++) cout << H;
    cout << MR << "\n";

    // 班級統計列
    auto statsRow = [&](string label, auto s0, auto s1, auto s2, string extra) {
        cout << V << " " << left  << setw(14) << label
             << V        << right << setw(5)  << s0 << " "
             << V        << right << setw(5)  << s1 << " "
             << V        << right << setw(5)  << s2 << " "
             << V        << right << setw(13) << extra
             << V << "\n";
    };

    cout << V << " " << left << setw(14) << "班級平均"
         << V << right << setw(5) << classAvg[0] << " "
         << V << right << setw(5) << classAvg[1] << " "
         << V << right << setw(5) << classAvg[2] << " "
         << V << right << setw(13) << totalAvg
         << V << "\n";

    cout << defaultfloat << setprecision(6);
    cout << V << " " << left << setw(14) << "最高分"
         << V << right << setw(5) << maxScore[0] << " "
         << V << right << setw(5) << maxScore[1] << " "
         << V << right << setw(5) << maxScore[2] << " "
         << V << setw(13) << "" << V << "\n";

    cout << V << " " << left << setw(14) << "最低分"
         << V << right << setw(5) << minScore[0] << " "
         << V << right << setw(5) << minScore[1] << " "
         << V << right << setw(5) << minScore[2] << " "
         << V << setw(13) << "" << V << "\n";

    // 底線
    cout << BL;
    for (int k = 0; k < 15; k++) cout << H;
    for (int j = 0; j < 3; j++) { cout << MB; for (int k = 0; k < 6; k++) cout << H; }
    cout << MB;
    for (int k = 0; k < 14; k++) cout << H;
    cout << BR << "\n";

    return 0;
}
