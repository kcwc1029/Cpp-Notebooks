#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_STUDENTS = 50;
const int MAX_SUBJECTS = 5;
const string SUBJECTS[] = {"國文", "英文", "數學", "物理", "化學"};

struct Student {
    string name;
    int    scores[MAX_SUBJECTS];
    double average;
    string grade;
};

// ─── 工具函數（參考技術的核心應用）───────────────────────

// 傳參考：就地計算平均與等第
void computeAvgGrade(Student& s) {
    int sum = 0;
    for (int i = 0; i < MAX_SUBJECTS; i++) sum += s.scores[i];
    s.average = sum / (double)MAX_SUBJECTS;

    if      (s.average >= 90) s.grade = "A";
    else if (s.average >= 80) s.grade = "B";
    else if (s.average >= 70) s.grade = "C";
    else if (s.average >= 60) s.grade = "D";
    else                      s.grade = "F";
}

// 印出表格標題
void printHeader() {
    cout << left
         << setw(10) << "姓名"
         << setw(6)  << "國文"
         << setw(6)  << "英文"
         << setw(6)  << "數學"
         << setw(6)  << "物理"
         << setw(6)  << "化學"
         << setw(8)  << "平均"
         << setw(5)  << "等第" << endl;
    cout << string(53, '-') << endl;
}

// 傳 const 參考：不複製結構體，只讀取
void printStudent(const Student& s) {
    cout << left << setw(10) << s.name;
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        cout << setw(6) << s.scores[i];
    }
    cout << fixed << setprecision(1)
         << setw(8) << s.average
         << setw(5) << s.grade << endl;
}

// 傳參考的 swap：高效交換兩個學生資料
void swapStudents(Student& a, Student& b) {
    Student temp = a;
    a = b;
    b = temp;
}

// 搜尋學生，回傳指標（可能為 nullptr）
Student* findStudent(Student arr[], int count, const string& name) {
    for (int i = 0; i < count; i++) {
        if (arr[i].name == name) return &arr[i];
    }
    return nullptr;
}

// ─── 功能函數 ────────────────────────────────────────────

// count 傳參考：函數結束後 count 反映實際數量
void addStudent(Student arr[], int& count) {
    if (count >= MAX_STUDENTS) {
        cout << "❌ 已達學生人數上限（" << MAX_STUDENTS << " 人）！" << endl;
        return;
    }

    Student& s = arr[count];    // 別名，簡化後續操作
    cout << "請輸入姓名：";
    cin >> s.name;

    // 確認姓名不重複
    for (int i = 0; i < count; i++) {
        if (arr[i].name == s.name) {
            cout << "❌ 學生 " << s.name << " 已存在！" << endl;
            return;
        }
    }

    cout << "請輸入五科成績（國文 英文 數學 物理 化學）：";
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        cin >> s.scores[i];
        // 確保成績合法
        while (s.scores[i] < 0 || s.scores[i] > 100) {
            cout << "  成績需介於 0~100，請重新輸入 " << SUBJECTS[i] << "：";
            cin >> s.scores[i];
        }
    }

    computeAvgGrade(s);
    count++;
    cout << "✅ 學生 " << s.name << " 新增成功！平均：" << s.average
         << "，等第：" << s.grade << endl;
}

// const 陣列：只讀取，不修改
void displayAll(const Student arr[], int count) {
    if (count == 0) {
        cout << "目前沒有學生資料。" << endl;
        return;
    }
    cout << "\n=== 所有學生（共 " << count << " 人）===" << endl;
    printHeader();
    for (int i = 0; i < count; i++) {
        printStudent(arr[i]);
    }
    cout << endl;
}

void modifyScore(Student arr[], int count) {
    if (count == 0) { cout << "沒有學生資料。" << endl; return; }

    string name;
    cout << "請輸入要修改的學生姓名：";
    cin >> name;

    Student* sp = findStudent(arr, count, name);
    if (!sp) {
        cout << "❌ 找不到學生 \"" << name << "\"" << endl;
        return;
    }

    Student& s = *sp;    // 建立別名，讓後續操作更簡潔
    cout << "目前成績：";
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        cout << SUBJECTS[i] << "=" << s.scores[i];
        if (i < MAX_SUBJECTS - 1) cout << " | ";
    }
    cout << endl;

    cout << "要修改哪科？（1=國文 2=英文 3=數學 4=物理 5=化學 0=取消）：";
    int subj;
    cin >> subj;
    if (subj == 0) { cout << "已取消。" << endl; return; }
    if (subj < 1 || subj > 5) { cout << "❌ 無效選項" << endl; return; }

    cout << "新成績（0~100）：";
    int newScore;
    cin >> newScore;
    if (newScore < 0 || newScore > 100) {
        cout << "❌ 成績無效" << endl;
        return;
    }

    s.scores[subj - 1] = newScore;
    computeAvgGrade(s);
    cout << "✅ 修改完成！" << endl;
    printHeader();
    printStudent(s);
}

// 統計資料：用參考輸出多個結果
void calcStats(const Student arr[], int count,
               double& classAvg, int& topIdx, int& botIdx) {
    double total = 0;
    topIdx = botIdx = 0;
    for (int i = 0; i < count; i++) {
        total += arr[i].average;
        if (arr[i].average > arr[topIdx].average) topIdx = i;
        if (arr[i].average < arr[botIdx].average) botIdx = i;
    }
    classAvg = total / count;
}

void showStats(const Student arr[], int count) {
    if (count == 0) { cout << "沒有資料。" << endl; return; }

    double classAvg;
    int topIdx, botIdx;
    calcStats(arr, count, classAvg, topIdx, botIdx);

    cout << "\n=== 成績統計 ===" << endl;
    cout << fixed << setprecision(1);
    cout << "全班人數：" << count << " 人" << endl;
    cout << "全班平均：" << classAvg << endl;
    cout << "最高分：" << arr[topIdx].name
         << "（平均 " << arr[topIdx].average << "，" << arr[topIdx].grade << "）" << endl;
    cout << "最低分：" << arr[botIdx].name
         << "（平均 " << arr[botIdx].average << "，" << arr[botIdx].grade << "）" << endl;

    // 各等第人數統計
    int gradeCount[5] = {};
    for (int i = 0; i < count; i++) {
        if      (arr[i].grade == "A") gradeCount[0]++;
        else if (arr[i].grade == "B") gradeCount[1]++;
        else if (arr[i].grade == "C") gradeCount[2]++;
        else if (arr[i].grade == "D") gradeCount[3]++;
        else                          gradeCount[4]++;
    }
    cout << "\n等第分佈：" << endl;
    string grades[] = {"A (>=90)", "B (>=80)", "C (>=70)", "D (>=60)", "F (<60)"};
    for (int i = 0; i < 5; i++) {
        cout << "  " << grades[i] << "：" << gradeCount[i] << " 人" << endl;
    }
}

// 用傳參考的 swapStudents 實作泡沫排序
void sortByAverage(Student arr[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (arr[j].average < arr[j + 1].average) {
                swapStudents(arr[j], arr[j + 1]);    // 傳參考交換
            }
        }
    }
    cout << "✅ 已依平均分數（由高到低）完成排序！" << endl;
}

void searchStudent(Student arr[], int count) {
    if (count == 0) { cout << "沒有學生資料。" << endl; return; }

    string name;
    cout << "請輸入搜尋姓名：";
    cin >> name;

    Student* sp = findStudent(arr, count, name);
    if (!sp) {
        cout << "❌ 找不到學生 \"" << name << "\"" << endl;
        return;
    }

    cout << "\n=== 搜尋結果 ===" << endl;
    printHeader();
    printStudent(*sp);    // 解參考指標，傳 const 參考給 printStudent

    cout << "\n是否要修改此學生的成績？（y/n）：";
    char ans;
    cin >> ans;
    if (ans == 'y' || ans == 'Y') {
        // 回傳的指標可以直接修改
        cout << "要修改哪科？（1=國文 2=英文 3=數學 4=物理 5=化學）：";
        int subj;
        cin >> subj;
        if (subj >= 1 && subj <= 5) {
            cout << "新成績：";
            cin >> sp->scores[subj - 1];
            computeAvgGrade(*sp);
            cout << "✅ 修改完成！" << endl;
        }
    }
}

// ─── 主程式 ──────────────────────────────────────────────

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;

    // 預設測試資料
    students[0] = {"Alice",   {92, 88, 95, 90, 87}, 0, ""};
    students[1] = {"Bob",     {75, 82, 70, 68, 79}, 0, ""};
    students[2] = {"Charlie", {85, 91, 88, 83, 90}, 0, ""};
    students[3] = {"Diana",   {95, 97, 99, 94, 96}, 0, ""};
    students[4] = {"Eve",     {62, 55, 70, 58, 65}, 0, ""};
    count = 5;
    for (int i = 0; i < count; i++) computeAvgGrade(students[i]);

    int choice;
    do {
        cout << "\n=============================" << endl;
        cout << "     學生成績管理系統" << endl;
        cout << "=============================" << endl;
        cout << "1. 新增學生" << endl;
        cout << "2. 顯示所有學生" << endl;
        cout << "3. 修改學生成績" << endl;
        cout << "4. 成績統計" << endl;
        cout << "5. 依平均分數排序（高→低）" << endl;
        cout << "6. 搜尋學生" << endl;
        cout << "0. 離開" << endl;
        cout << "請選擇：";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: addStudent(students, count); break;
            case 2: displayAll(students, count); break;
            case 3: modifyScore(students, count); break;
            case 4: showStats(students, count); break;
            case 5: sortByAverage(students, count); break;
            case 6: searchStudent(students, count); break;
            case 0: cout << "感謝使用，掰掰！" << endl; break;
            default: cout << "❌ 無效選項，請輸入 0~6。" << endl;
        }
    } while (choice != 0);

    return 0;
}
