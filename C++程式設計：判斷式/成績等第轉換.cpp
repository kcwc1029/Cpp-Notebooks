// 練習 4-7：成績等第轉換
#include <iostream>
#include <cctype>
using namespace std;

int main() {
    char grade;
    cout << "請輸入成績等第（A/B/C/D/F）：";
    cin >> grade;
    grade = toupper(grade);

    switch (grade) {
        case 'A':
            cout << "優秀（90-100分）：表現傑出，繼續保持！" << endl;
            break;
        case 'B':
            cout << "良好（80-89分）：表現不錯，再加把勁！" << endl;
            break;
        case 'C':
            cout << "普通（70-79分）：尚可，仍有進步空間。" << endl;
            break;
        case 'D':
            cout << "及格（60-69分）：剛好過關，需要加強。" << endl;
            break;
        case 'F':
            cout << "不及格（0-59分）：需要補考或補救教學。" << endl;
            break;
        default:
            cout << "無效的等第「" << grade << "」，請輸入 A/B/C/D/F。" << endl;
    }

    return 0;
}
