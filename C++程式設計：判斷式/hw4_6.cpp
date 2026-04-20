// 練習 4-6：石頭剪刀布
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    string names[] = {"", "石頭", "剪刀", "布"};

    int player;
    cout << "=== 石頭剪刀布 ===" << endl;
    cout << "1. 石頭  2. 剪刀  3. 布" << endl;
    cout << "請出拳：";
    cin >> player;

    if (player < 1 || player > 3) {
        cout << "輸入無效！" << endl;
        return 1;
    }

    int computer = rand() % 3 + 1;

    cout << "你出：" << names[player]   << endl;
    cout << "電腦出：" << names[computer] << endl;

    if (player == computer) {
        cout << "結果：平手！" << endl;
    } else if ((player == 1 && computer == 2) ||
               (player == 2 && computer == 3) ||
               (player == 3 && computer == 1)) {
        cout << "結果：你贏了！" << endl;
    } else {
        cout << "結果：你輸了！" << endl;
    }

    return 0;
}
