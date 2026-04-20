#include <iostream>
using namespace std;

int main() {
    int age;
    char answer;

    cout << "請輸入年齡：";
    cin >> age;
    cout << "是否有身分證？(y/n)：";
    cin >> answer;
    bool hasID = (answer == 'y' || answer == 'Y');

    if (age >= 18) {
        cout << "年齡符合資格。" << endl;
        if (hasID) {
            cout << "✅ 可以投票！" << endl;
        } else {
            cout << "❌ 需要出示身分證才能投票。" << endl;
        }
    } else {
        cout << "❌ 年齡未滿 18 歲，不能投票。" << endl;
        if (age >= 16) {
            cout << "（再等 " << 18 - age << " 年就可以了！）" << endl;
        }
    }

    return 0;
}
