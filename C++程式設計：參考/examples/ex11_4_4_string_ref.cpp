#include <iostream>
#include <string>
using namespace std;

// const 參考：不複製，只讀取
bool isPalindrome(const string& s) {
    int left = 0, right = (int)s.length() - 1;
    while (left < right) {
        if (s[left] != s[right]) return false;
        left++;
        right--;
    }
    return true;
}

// 參考：就地修改字串（不傳回副本，直接改原字串）
void toUpperCase(string& s) {
    for (char& c : s) {    // char 也用參考才能修改
        if (c >= 'a' && c <= 'z') c -= 32;
    }
}

void toLowerCase(string& s) {
    for (char& c : s) {
        if (c >= 'A' && c <= 'Z') c += 32;
    }
}

// 就地字元替換
void replaceChar(string& s, char from, char to) {
    for (char& c : s) {
        if (c == from) c = to;
    }
}

// 回傳較長字串的參考（可作為左值被賦值）
string& getLonger(string& a, string& b) {
    return a.length() >= b.length() ? a : b;
}

// const 版本：只讀取較長字串
const string& getLongerConst(const string& a, const string& b) {
    return a.length() >= b.length() ? a : b;
}

int main() {
    // === 回文判斷（const 參考，不複製）===
    string words[] = {"racecar", "hello", "level", "world", "madam", "noon"};
    cout << "=== 回文判斷 ===" << endl;
    for (const string& w : words) {
        cout << "  \"" << w << "\"：" << (isPalindrome(w) ? "是" : "否") << "回文" << endl;
    }

    // === 就地大小寫轉換 ===
    string msg = "Hello, C++ World!";
    cout << "\n=== 大小寫轉換 ===" << endl;
    cout << "原始：" << msg << endl;
    toUpperCase(msg);
    cout << "大寫：" << msg << endl;
    toLowerCase(msg);
    cout << "小寫：" << msg << endl;

    // === 就地字元替換 ===
    replaceChar(msg, ' ', '_');
    cout << "空格→底線：" << msg << endl;

    // === 回傳參考，直接修改較長字串 ===
    string s1 = "Hi";
    string s2 = "Hello World";
    cout << "\n=== 修改較長字串 ===" << endl;
    cout << "前：s1=\"" << s1 << "\", s2=\"" << s2 << "\"" << endl;
    getLonger(s1, s2) = "已被替換成新內容";    // 直接賦值給 s2（它比較長）
    cout << "後：s1=\"" << s1 << "\", s2=\"" << s2 << "\"" << endl;

    // === 只讀版本 ===
    string a = "short", b = "longer string";
    cout << "\n較長的字串是：\"" << getLongerConst(a, b) << "\"" << endl;

    return 0;
}
