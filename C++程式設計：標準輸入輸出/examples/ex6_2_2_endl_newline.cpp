// ex6_2_2_endl_newline.cpp
// 示範 endl 與 "\n" 的差異

#include <iostream>
using namespace std;

int main() {
    // endl：換行 + 強制清空輸出緩衝區（較慢，適合錯誤訊息）
    cout << "第一行" << endl;
    cout << "第二行" << endl;

    // "\n"：只換行，不清緩衝區（較快，適合大量輸出）
    cout << "第三行\n";
    cout << "第四行\n";

    // 多行一起輸出
    cout << "A\nB\nC\n";

    return 0;
}
