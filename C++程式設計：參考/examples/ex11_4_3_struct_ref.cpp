#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int    score;
    string grade;
};

// 傳參考：就地計算等第（不複製整個結構體）
void computeGrade(Student& s) {
    if      (s.score >= 90) s.grade = "A";
    else if (s.score >= 80) s.grade = "B";
    else if (s.score >= 70) s.grade = "C";
    else if (s.score >= 60) s.grade = "D";
    else                    s.grade = "F";
}

// 傳 const 參考：只讀取，不修改，不複製
void printStudent(const Student& s) {
    cout << "  姓名：" << s.name
         << "，分數：" << s.score
         << "，等第：" << s.grade << endl;
}

// 回傳最高分學生的參考（可直接修改）
Student& findTop(Student arr[], int size) {
    int maxIdx = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i].score > arr[maxIdx].score) maxIdx = i;
    }
    return arr[maxIdx];    // 回傳陣列元素的參考（安全！）
}

// 回傳最低分學生的 const 參考（只讀）
const Student& findBottom(const Student arr[], int size) {
    int minIdx = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i].score < arr[minIdx].score) minIdx = i;
    }
    return arr[minIdx];
}

int main() {
    Student students[5] = {
        {"Alice",   92, ""},
        {"Bob",     78, ""},
        {"Charlie", 85, ""},
        {"Diana",   95, ""},
        {"Eve",     62, ""}
    };

    // 為所有學生計算等第
    for (int i = 0; i < 5; i++) {
        computeGrade(students[i]);
    }

    cout << "=== 所有學生 ===" << endl;
    for (int i = 0; i < 5; i++) {
        printStudent(students[i]);
    }

    // 找出最高分並直接修改
    Student& top = findTop(students, 5);
    cout << "\n=== 最高分學生 ===" << endl;
    printStudent(top);
    top.score += 3;          // 加分（直接修改原始資料）
    computeGrade(top);       // 重新計算等第
    cout << "加 3 分後：";
    printStudent(top);

    // 找出最低分（只讀）
    const Student& bottom = findBottom(students, 5);
    cout << "\n=== 最低分學生 ===" << endl;
    printStudent(bottom);
    // bottom.score = 100;   // ❌ 錯誤！const 參考不能修改

    return 0;
}
