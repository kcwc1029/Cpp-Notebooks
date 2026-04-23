// ex10_3_3_cstring_pointer.cpp
// 示範：C 字串（char 陣列）與指標操作
#include <iostream>
#include <cstring>
using namespace std;

// 用指標實作字串輸出
void print_string(const char *s) {
    while (*s != '\0') {
        cout << *s;
        s++;
    }
    cout << endl;
}

// 用指標實作字串長度
int my_strlen(const char *s) {
    int count = 0;
    while (*s++ != '\0') count++;
    return count;
}

// 用指標實作字串比較
int my_strcmp(const char *a, const char *b) {
    while (*a && *a == *b) { a++; b++; }
    return (unsigned char)*a - (unsigned char)*b;
}

int main() {
    char greeting[] = "Hello, World!";
    char *p = greeting;

    cout << "=== 字串基本輸出 ===" << endl;
    cout << "直接輸出：" << greeting << endl;
    cout << "指標輸出：";
    print_string(p);

    cout << "\n=== 字串長度 ===" << endl;
    cout << "my_strlen：" << my_strlen(greeting) << endl;
    cout << "strlen   ：" << strlen(greeting) << endl;

    cout << "\n=== 逐字元輸出（含位址）===" << endl;
    for (char *q = greeting; *q != '\0'; q++) {
        cout << (void*)q << "  '" << *q << "'" << endl;
    }

    cout << "\n=== 字串比較 ===" << endl;
    const char *s1 = "apple";
    const char *s2 = "banana";
    int result = my_strcmp(s1, s2);
    if (result < 0)      cout << s1 << " < " << s2 << endl;
    else if (result > 0) cout << s1 << " > " << s2 << endl;
    else                 cout << s1 << " == " << s2 << endl;

    return 0;
}
