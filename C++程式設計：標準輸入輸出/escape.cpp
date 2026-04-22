// ex6_2_3_escape.cpp
// 示範跳脫字元（\n \t \\ \" 等）

#include <iostream>
using namespace std;

int main() {
    // \t 水平定位（Tab），常用來對齊欄位
    cout << "姓名\t年齡\t城市" << endl;
    cout << "陳大明\t20\t台北" << endl;
    cout << "李小華\t22\t台中" << endl;

    // \" 在字串中輸出雙引號
    cout << "\n他說：\"你好！\"" << endl;

    // \\ 輸出反斜線
    cout << "路徑：C:\\Users\\student\\Desktop" << endl;

    // \n 換行
    cout << "第一行\n第二行\n第三行" << endl;

    return 0;
}
