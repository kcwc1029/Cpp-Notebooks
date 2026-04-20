// **題目：** 撰寫一支程式，輸入使用者的姓名、年齡、科系，並輸出格式化的自我介紹。

// **輸入範例：**

// ```
// 姓名：陳小明
// 年齡：19
// 科系：資訊工程學系
// ```

// **輸出範例：**

// ```
// ==========================
// 大家好，我是 陳小明！
// 我今年 19 歲
// 目前就讀 資訊工程學系
// 很高興認識大家！
// ==========================
// ```

#include <iostream>
#include <string>
using namespace std;

int main() {
    string name, department;
    int age;

    cout << "姓名：";
    cin >> name;
    cout << "年齡：";
    cin >> age;
    cin.ignore();
    cout << "科系：";
    getline(cin, department);

    cout << "==========================" << endl;
    cout << "大家好，我是 " << name << "！" << endl;
    cout << "我今年 " << age << " 歲" << endl;
    cout << "目前就讀 " << department << endl;
    cout << "很高興認識大家！" << endl;
    cout << "==========================" << endl;

    return 0;
}
