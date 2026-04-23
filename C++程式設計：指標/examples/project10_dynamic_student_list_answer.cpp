// project10_dynamic_student_list_answer.cpp
// 專案：動態學生名冊管理系統
// 功能：動態擴展陣列、成績統計、排序顯示
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int INIT_CAPACITY = 2;
const int NAME_LEN = 50;

struct Student {
    char   name[NAME_LEN];
    int    score;
};

struct StudentList {
    Student *data;
    int      size;
    int      capacity;
};

// 初始化名冊
void init(StudentList *list) {
    list->data     = new Student[INIT_CAPACITY];
    list->size     = 0;
    list->capacity = INIT_CAPACITY;
}

// 釋放名冊記憶體
void destroy(StudentList *list) {
    delete[] list->data;
    list->data     = nullptr;
    list->size     = 0;
    list->capacity = 0;
}

// 擴展容量到 2 倍
void expand(StudentList *list) {
    int new_cap = list->capacity * 2;
    Student *new_data = new Student[new_cap];
    for (int i = 0; i < list->size; i++) {
        new_data[i] = list->data[i];
    }
    delete[] list->data;
    list->data     = new_data;
    list->capacity = new_cap;
    cout << "  [系統] 容量已擴展到 " << new_cap << endl;
}

// 新增學生
void add_student(StudentList *list, const char *name, int score) {
    if (list->size == list->capacity) {
        expand(list);
    }
    strncpy(list->data[list->size].name, name, NAME_LEN - 1);
    list->data[list->size].name[NAME_LEN - 1] = '\0';
    list->data[list->size].score = score;
    list->size++;
    cout << "新增成功！（目前 " << list->size
         << "/" << list->capacity << " 人）" << endl;
}

// 列出所有學生
void list_students(const StudentList *list) {
    if (list->size == 0) {
        cout << "（名冊為空）" << endl;
        return;
    }
    cout << left
         << setw(6)  << "編號"
         << setw(16) << "姓名"
         << setw(8)  << "分數" << endl;
    cout << string(30, '-') << endl;
    for (int i = 0; i < list->size; i++) {
        cout << left
             << setw(6)  << (i + 1)
             << setw(16) << list->data[i].name
             << setw(8)  << list->data[i].score << endl;
    }
}

// 成績統計（透過指標回傳）
void calc_stats(const StudentList *list,
                int *min_score, int *max_score, double *avg) {
    if (list->size == 0) return;

    *min_score = list->data[0].score;
    *max_score = list->data[0].score;
    int total  = list->data[0].score;

    for (int i = 1; i < list->size; i++) {
        if (list->data[i].score < *min_score) *min_score = list->data[i].score;
        if (list->data[i].score > *max_score) *max_score = list->data[i].score;
        total += list->data[i].score;
    }
    *avg = (double)total / list->size;
}

// 找最高分學生（回傳指標）
Student* find_top(StudentList *list) {
    if (list->size == 0) return nullptr;
    Student *top = &list->data[0];
    for (int i = 1; i < list->size; i++) {
        if (list->data[i].score > top->score) {
            top = &list->data[i];
        }
    }
    return top;
}

// 排序顯示（不修改原始資料，使用指標陣列排序）
void sort_and_print(const StudentList *list) {
    if (list->size == 0) {
        cout << "（名冊為空）" << endl;
        return;
    }

    // 建立指標陣列
    Student **ptrs = new Student*[list->size];
    for (int i = 0; i < list->size; i++) {
        ptrs[i] = &list->data[i];
    }

    // 選擇排序（由高到低）
    for (int i = 0; i < list->size - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < list->size; j++) {
            if (ptrs[j]->score > ptrs[max_idx]->score) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            Student *tmp = ptrs[i];
            ptrs[i]      = ptrs[max_idx];
            ptrs[max_idx]= tmp;
        }
    }

    cout << left
         << setw(6)  << "排名"
         << setw(16) << "姓名"
         << setw(8)  << "分數" << endl;
    cout << string(30, '-') << endl;
    for (int i = 0; i < list->size; i++) {
        cout << left
             << setw(6)  << (i + 1)
             << setw(16) << ptrs[i]->name
             << setw(8)  << ptrs[i]->score << endl;
    }

    delete[] ptrs;
}

void print_menu() {
    cout << "\n╔════════════════════════╗" << endl;
    cout << "║   學生名冊管理系統     ║" << endl;
    cout << "╠════════════════════════╣" << endl;
    cout << "║ 1. 新增學生            ║" << endl;
    cout << "║ 2. 列出所有學生        ║" << endl;
    cout << "║ 3. 成績統計            ║" << endl;
    cout << "║ 4. 找最高分學生        ║" << endl;
    cout << "║ 5. 排序顯示            ║" << endl;
    cout << "║ 0. 離開                ║" << endl;
    cout << "╚════════════════════════╝" << endl;
    cout << "請選擇：";
}

int main() {
    StudentList roster;
    init(&roster);

    int choice;
    do {
        print_menu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                char name[NAME_LEN];
                int  score;
                cout << "姓名：";
                cin.getline(name, NAME_LEN);
                cout << "分數：";
                cin >> score;
                cin.ignore();
                if (score < 0 || score > 100) {
                    cout << "分數必須在 0~100 之間" << endl;
                } else {
                    add_student(&roster, name, score);
                }
                break;
            }
            case 2:
                cout << "\n=== 所有學生 ===" << endl;
                list_students(&roster);
                break;

            case 3: {
                if (roster.size == 0) {
                    cout << "名冊為空，無法統計" << endl;
                    break;
                }
                int min_s, max_s;
                double avg;
                calc_stats(&roster, &min_s, &max_s, &avg);
                cout << "\n=== 成績統計 ===" << endl;
                cout << fixed << setprecision(2);
                cout << "最高分：" << max_s << endl;
                cout << "最低分：" << min_s << endl;
                cout << "平均分：" << avg   << endl;
                break;
            }
            case 4: {
                Student *top = find_top(&roster);
                if (top == nullptr) {
                    cout << "名冊為空" << endl;
                } else {
                    cout << "\n=== 最高分學生 ===" << endl;
                    cout << "姓名：" << top->name  << endl;
                    cout << "分數：" << top->score << endl;
                }
                break;
            }
            case 5:
                cout << "\n=== 排名（由高到低）===" << endl;
                sort_and_print(&roster);
                break;

            case 0:
                cout << "再見！" << endl;
                break;

            default:
                cout << "無效選項，請重新輸入" << endl;
        }
    } while (choice != 0);

    destroy(&roster);
    return 0;
}
