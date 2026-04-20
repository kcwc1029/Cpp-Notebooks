// 練習 4-10：身分證字號驗證
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string id;
    cout << "請輸入身分證字號：";
    cin >> id;

    bool valid = true;
    string reason = "";

    if (id.length() != 10) {
        valid = false;
        reason = "長度必須為 10 碼";
    } else if (!isalpha(id[0]) || !isupper(id[0])) {
        valid = false;
        reason = "第一碼必須為大寫英文字母";
    } else if (id[1] != '1' && id[1] != '2') {
        valid = false;
        reason = "第二碼必須為 1（男）或 2（女）";
    } else {
        for (int i = 2; i < 10; i++) {
            if (!isdigit(id[i])) {
                valid = false;
                reason = "第 3~10 碼必須全為數字";
                break;
            }
        }
    }

    if (!valid) {
        cout << "格式錯誤：" << reason << endl;
        return 0;
    }

    // 驗證碼計算
    int letterCode = (id[0] - 'A') + 10;
    int sum = (letterCode / 10) * 1 + (letterCode % 10) * 9;
    int weights[] = {8, 7, 6, 5, 4, 3, 2, 1, 1};
    for (int i = 0; i < 9; i++) {
        sum += (id[i+1] - '0') * weights[i];
    }

    if (sum % 10 == 0) {
        string gender = (id[1] == '1') ? "男性" : "女性";
        cout << "驗證通過！" << gender << "，縣市代碼：" << id[0] << endl;
    } else {
        cout << "驗證失敗：" << id << " 不是有效的身分證字號。" << endl;
    }

    return 0;
}
