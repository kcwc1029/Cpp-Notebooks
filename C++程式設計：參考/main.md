# 第十一章：參考（Reference）

> **學習目標**
>
> - 理解參考的本質：既有變數的「別名」
> - 掌握參考的宣告語法與初始化規則
> - 學會用傳參考讓函數修改呼叫者的變數
> - 辨別何時用傳值、傳參考、傳 const 參考
> - 理解回傳參考的使用時機與危險陷阱
> - 能在 range-based for 與複雜資料結構中靈活運用參考

---

## 為什麼需要參考？

學過函數之後，你可能遇過這個令人困惑的問題：

```cpp
void swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 10, y = 20;
    swap(x, y);
    cout << x << " " << y;   // 輸出：10 20（沒有交換！）
}
```

為什麼 `swap` 沒有效果？因為 C++ **預設傳值（pass by value）**，函數只收到副本，對副本的任何修改都不影響原始變數。

**參考（Reference）** 就是解決這個問題的關鍵工具：

```cpp
void swap(int& a, int& b) {   // & 代表傳參考
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 10, y = 20;
    swap(x, y);
    cout << x << " " << y;   // 輸出：20 10（成功！）
}
```

參考讓函數直接操作原始變數，而非副本。這是 C++ 中非常重要的機制，也是許多高效能程式的基礎。

---

```
參考的記憶體示意圖：

  int x = 42;
  int& r = x;     // r 是 x 的別名

  記憶體：
  ┌─────────┐
  │   42    │ ← 位址 0x1000
  └─────────┘
       ↑   ↑
       x   r    （r 就是 x，共用同一個記憶體位址）

  r = 100;        // 等同於 x = 100
  cout << x;      // 輸出 100
```

---

## 11.1 宣告及初始

### 11.1.1 什麼是參考

**參考（Reference）** 是一個變數的「別名（alias）」。參考和原始變數共用同一塊記憶體空間，對參考的任何操作，等同於對原始變數的操作。

```
一般變數：
  int x = 42;
  int y = x;   // y 是「副本」，x 和 y 各自獨立

  修改 y：  y = 100  →  x 仍然是 42

參考：
  int x = 42;
  int& r = x;  // r 是「別名」，r 和 x 共用記憶體

  修改 r：  r = 100  →  x 也變成 100
```

### 11.1.2 宣告語法

```
型別& 參考名稱 = 既有變數;
```

```cpp
int    x = 10;
int&   r = x;    // r 是 x 的參考（int 型別）

double pi = 3.14;
double& ref_pi = pi;    // ref_pi 是 pi 的參考

string name = "Alice";
string& ref_name = name;   // ref_name 是 name 的參考
```

> ⚠️ **`&` 放在型別後面表示「參考」，放在變數前面表示「取位址」，兩者意義完全不同！**
>
> ```cpp
> int x = 10;
> int& r = x;    // 宣告：r 是 int 參考
> cout << &x;    // 取址：輸出 x 的記憶體位址
> ```

📄 **範例檔案：** [ex11_1_1_ref_basic.cpp](examples/ex11_1_1_ref_basic.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 42;
    int& r = x;   // r 是 x 的參考（別名）

    cout << "=== 初始狀態 ===" << endl;
    cout << "x  = " << x << endl;
    cout << "r  = " << r << endl;
    cout << "&x = " << &x << endl;   // x 的記憶體位址
    cout << "&r = " << &r << endl;   // r 的位址（與 x 完全相同！）

    // 透過參考修改值
    r = 100;
    cout << "\n透過 r 修改後：" << endl;
    cout << "x = " << x << endl;    // x 也變成 100
    cout << "r = " << r << endl;

    // 透過原變數修改
    x = 200;
    cout << "\n透過 x 修改後：" << endl;
    cout << "x = " << x << endl;
    cout << "r = " << r << endl;    // r 也是 200

    // 多個參考指向同一個變數
    int& r2 = x;
    r2 = 999;
    cout << "\n透過 r2 修改後：" << endl;
    cout << "x = " << x << endl;    // 999
    cout << "r = " << r << endl;    // 999
    cout << "r2 = " << r2 << endl;  // 999

    return 0;
}
```

**執行結果：**

```
=== 初始狀態 ===
x  = 42
r  = 42
&x = 0x61ff08
&r = 0x61ff08
透過 r 修改後：
x = 100
r = 100
透過 x 修改後：
x = 200
r = 200
透過 r2 修改後：
x = 999
r = 999
r2 = 999
```

### 11.1.3 參考的三大規則

```
規則一：參考必須在宣告時初始化
  int& r;        // ❌ 錯誤！沒有初始化
  int x = 10;
  int& r = x;    // ✅ 正確

規則二：參考一旦綁定就無法改變（無法「重新綁定」）
  int a = 10, b = 20;
  int& r = a;    // r 綁定到 a
  r = b;         // ❌ 這不是改變綁定！
                 // 這是「把 b 的值指派給 r（也就是 a）」
                 // a 變成 20，但 r 仍然是 a 的別名

規則三：參考不能是 null
  int* p = nullptr;    // ✅ 指標可以是 null
  int& r = ???;        // ❌ 沒有「null 參考」的概念
```

> 💡 **提示：** 規則二特別容易混淆！`r = b;` 並不是讓 `r` 改為指向 `b`，而是把 `b` 的值寫入 `r`（也就是 `a`）。參考一旦綁定，就永遠是那個變數的別名。

### 11.1.4 參考與指標的比較

| 特性     | 參考（Reference）  | 指標（Pointer）      |
| -------- | ------------------ | -------------------- |
| 初始化   | 必須在宣告時初始化 | 可以稍後初始化       |
| 綁定     | 綁定後無法改變     | 可以改變指向         |
| null 值  | 不能是 null        | 可以是 `nullptr`     |
| 語法     | 直接使用，如同變數 | 需要用 `*` 解參考    |
| 空間佔用 | 通常不佔額外空間   | 佔 4 或 8 bytes      |
| 使用場合 | 簡單別名、函數參數 | 動態記憶體、陣列走訪 |

📄 **範例檔案：** [ex11_1_2_ref_vs_pointer.cpp](examples/ex11_1_2_ref_vs_pointer.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 10, y = 20;

    // === 指標操作 ===
    cout << "=== 指標 ===" << endl;
    int* p = &x;
    cout << "p 指向 x，*p = " << *p << endl;

    p = &y;            // 指標可以改變指向
    cout << "p 改指向 y，*p = " << *p << endl;

    *p = 99;           // 透過指標修改 y
    cout << "修改後 y = " << y << endl;

    // === 參考操作 ===
    cout << "\n=== 參考 ===" << endl;
    int& r = x;        // 必須立即初始化
    cout << "r 是 x 的別名，r = " << r << endl;

    r = y;             // 這是「把 y 的值存入 x」，不是改變綁定
    cout << "r = y 後：x = " << x << "，r 還是 x 的別名" << endl;
    cout << "&r == &x：" << (&r == &x ? "true" : "false") << endl;

    // === 使用便利性比較 ===
    cout << "\n=== 使用便利性 ===" << endl;
    int val = 42;
    int* ptr = &val;
    int& ref = val;

    // 指標需要解參考運算子
    *ptr += 10;
    cout << "指標：*ptr += 10 → val = " << val << endl;

    // 參考直接使用，像普通變數
    ref += 10;
    cout << "參考：ref += 10  → val = " << val << endl;

    return 0;
}
```

**執行結果：**

```
=== 指標 ===
p 指向 x，*p = 10
p 改指向 y，*p = 20
修改後 y = 99
=== 參考 ===
r 是 x 的別名，r = 10
r = y 後：x = 99，r 還是 x 的別名
&r == &x：true
=== 使用便利性 ===
指標：*ptr += 10 → val = 52
參考：ref += 10  → val = 62
```

### 11.1.5 常數參考（const Reference）

在參考宣告前加上 `const`，就是**常數參考**，只能讀取，不能修改。

```
const 型別& 參考名稱 = 變數或字面值;
```

```cpp
int x = 42;
const int& cr = x;    // 可以讀取 x，但不能透過 cr 修改
cr = 100;             // ❌ 錯誤！const 參考不能修改
x  = 100;             // ✅ 可以！直接修改原始變數沒問題
```

**const 參考的特殊能力：可以綁定字面值和臨時值**

```cpp
// 一般參考只能綁定「可修改的左值」
int& r1 = 42;         // ❌ 不合法！42 是字面值（右值）
int& r2 = x + 1;      // ❌ 不合法！x+1 是臨時值（右值）

// const 參考可以綁定任何東西
const int& cr1 = 42;      // ✅ 合法！
const int& cr2 = x + 1;   // ✅ 合法！
const double& cr3 = x;    // ✅ 合法！（會建立臨時的 double）
```

> 💡 **為什麼 const 參考可以綁定字面值？**
> 因為字面值是常數，你已承諾不修改它（`const`），編譯器才允許此操作。同時會延長臨時值的生命期，讓它存活到 const 參考的生命期結束。

📄 **範例檔案：** [ex11_1_3_const_ref.cpp](examples/ex11_1_3_const_ref.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 42;

    // 一般參考 vs const 參考
    int& r = x;
    const int& cr = x;

    r = 100;            // ✅ 可以修改
    cout << "r = 100 後，x = " << x << endl;

    // cr = 200;        // ❌ 錯誤！const 參考不能修改
    cout << "cr = " << cr << endl;   // ✅ 可以讀取

    // const 參考可以綁定字面值
    const int& lit = 42;
    cout << "\nconst 參考綁定字面值 42：lit = " << lit << endl;

    // const 參考可以綁定運算結果（臨時值）
    const int& expr = x + 10;
    cout << "const 參考綁定 x+10：expr = " << expr << endl;

    // const 參考可以綁定不同型別（隱含型別轉換）
    double d = 3.14;
    const int& di = d;    // 建立臨時 int，值為 3
    cout << "\nconst int& 綁定 double 3.14：di = " << di << endl;

    // 一般參考不允許此操作：
    // int& bad = d;      // ❌ 錯誤！

    return 0;
}
```

**執行結果：**

```
r = 100 後，x = 100
cr = 100
const 參考綁定字面值 42：lit = 42
const 參考綁定 x+10：expr = 110
const int& 綁定 double 3.14：di = 3
```

### 11.1.6 初始化規則整理

📄 **範例檔案：** [ex11_1_4_ref_init_rules.cpp](examples/ex11_1_4_ref_init_rules.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    // ✅ 合法：初始化時綁定可修改的左值
    int a = 10;
    int& r1 = a;
    cout << "r1 = " << r1 << endl;

    // ✅ 合法：多個參考可以指向同一變數
    int& r2 = a;
    int& r3 = r1;    // r3 也是 a 的別名（非 r1 的別名）
    r2 = 99;
    cout << "a=" << a << " r1=" << r1 << " r2=" << r2 << " r3=" << r3 << endl;

    // ✅ 合法：const 參考可以綁定字面值
    const int& cr1 = 42;
    cout << "cr1 = " << cr1 << endl;

    // ✅ 合法：const 參考可以綁定臨時運算式
    const int& cr2 = a * 2 + 1;
    cout << "cr2 = " << cr2 << endl;

    // ❌ 以下為非法（已用註解展示）：
    // int& r4;            // 錯誤：必須初始化
    // int& r5 = 42;       // 錯誤：非 const 參考不能綁定字面值
    // int& r6 = a + 1;    // 錯誤：非 const 參考不能綁定臨時值

    cout << "\n=== 規則摘要 ===" << endl;
    cout << "1. 參考必須在宣告時初始化" << endl;
    cout << "2. 一旦綁定，無法重新指向其他變數" << endl;
    cout << "3. 非 const 參考只能綁定可修改的左值" << endl;
    cout << "4. const 參考可以綁定左值、字面值、臨時值" << endl;

    return 0;
}
```

**執行結果：**

```
r1 = 10
a=99 r1=99 r2=99 r3=99
cr1 = 42
cr2 = 199
=== 規則摘要 ===
1. 參考必須在宣告時初始化
2. 一旦綁定，無法重新指向其他變數
3. 非 const 參考只能綁定可修改的左值
4. const 參考可以綁定左值、字面值、臨時值
```

---

## 11.2 參數傳遞

函數的參數傳遞有三種方式，選擇正確的方式直接影響程式的**正確性**與**效能**。

```
三種參數傳遞方式：

  傳值（Pass by Value）
  ┌──────────────────────────────┐
  │  呼叫端：int x = 10;         │
  │  函數端：void f(int n)       │
  │          n 是 x 的「副本」   │
  │  修改 n → x 不變             │
  └──────────────────────────────┘

  傳參考（Pass by Reference）
  ┌──────────────────────────────┐
  │  呼叫端：int x = 10;         │
  │  函數端：void f(int& n)      │
  │          n 就是 x 的「別名」 │
  │  修改 n → x 也改變           │
  └──────────────────────────────┘

  傳 const 參考（Pass by const Reference）
  ┌──────────────────────────────┐
  │  呼叫端：string s = "hi";    │
  │  函數端：void f(const string& s) │
  │          不複製，只讀取      │
  │  嘗試修改 → 編譯錯誤         │
  └──────────────────────────────┘
```

### 11.2.1 傳值：函數拿到副本

📄 **範例檔案：** [ex11_2_1_pass_by_value.cpp](examples/ex11_2_1_pass_by_value.cpp)

```cpp
#include <iostream>
using namespace std;

void addTen(int n) {        // n 是副本
    cout << "  [函數內] 修改前 n = " << n << ", 位址 = " << &n << endl;
    n += 10;
    cout << "  [函數內] 修改後 n = " << n << endl;
}

int main() {
    int a = 5;
    cout << "呼叫前：a = " << a << "，位址 = " << &a << endl;
    addTen(a);
    cout << "呼叫後：a = " << a << endl;   // 仍然是 5

    cout << endl;

    // 傳值的另一個問題：複製大型物件代價高
    // （將在 11.2.3 說明）

    return 0;
}
```

**執行結果：**

```
呼叫前：a = 5，位址 = 0x61ff1c
  [函數內] 修改前 n = 5, 位址 = 0x61fefc
  [函數內] 修改後 n = 15
呼叫後：a = 5
```

> 💡 **注意到了嗎？** `a` 和 `n` 的位址不同，代表它們是完全獨立的變數。`n` 是 `a` 的副本，修改 `n` 不影響 `a`。

### 11.2.2 傳參考：函數直接操作原始變數

📄 **範例檔案：** [ex11_2_2_pass_by_ref.cpp](examples/ex11_2_2_pass_by_ref.cpp)

```cpp
#include <iostream>
using namespace std;

void addTen(int& n) {       // n 是 a 的別名
    cout << "  [函數內] 修改前 n = " << n << "，位址 = " << &n << endl;
    n += 10;
    cout << "  [函數內] 修改後 n = " << n << endl;
}

void resetToZero(int& val) {
    val = 0;
}

int main() {
    int a = 5;
    cout << "呼叫前：a = " << a << "，位址 = " << &a << endl;
    addTen(a);
    cout << "呼叫後：a = " << a << endl;   // 變成 15！

    cout << endl;

    int score = 95;
    cout << "重置前：score = " << score << endl;
    resetToZero(score);
    cout << "重置後：score = " << score << endl;   // 0

    return 0;
}
```

**執行結果：**

```
呼叫前：a = 5，位址 = 0x61ff1c
  [函數內] 修改前 n = 5，位址 = 0x61ff1c
  [函數內] 修改後 n = 15
呼叫後：a = 15
重置前：score = 95
重置後：score = 0
```

> 💡 **注意到了嗎？** 這次 `a` 和 `n` 的位址**完全相同**，代表它們是同一個變數（只是名字不同）。

### 11.2.3 傳參考的典型應用：交換函數

📄 **範例檔案：** [ex11_2_3_swap.cpp](examples/ex11_2_3_swap.cpp)

```cpp
#include <iostream>
using namespace std;

// ❌ 傳值：無效的交換
void swap_bad(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    cout << "  [swap_bad 內] a=" << a << ", b=" << b << endl;
}

// ✅ 傳參考：有效的交換
void swap_good(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// ✅ 模板版本（可交換任何型別）
template <typename T>
void my_swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 10, y = 20;

    cout << "=== 傳值交換（無效）===" << endl;
    cout << "呼叫前：x=" << x << ", y=" << y << endl;
    swap_bad(x, y);
    cout << "呼叫後：x=" << x << ", y=" << y << endl;   // 沒有改變！

    cout << "\n=== 傳參考交換（有效）===" << endl;
    cout << "呼叫前：x=" << x << ", y=" << y << endl;
    swap_good(x, y);
    cout << "呼叫後：x=" << x << ", y=" << y << endl;   // 成功交換！

    cout << "\n=== 模板交換（泛用）===" << endl;
    double a = 1.5, b = 2.5;
    cout << "交換前：a=" << a << ", b=" << b << endl;
    my_swap(a, b);
    cout << "交換後：a=" << a << ", b=" << b << endl;

    string s1 = "Hello", s2 = "World";
    cout << "交換前：s1=" << s1 << ", s2=" << s2 << endl;
    my_swap(s1, s2);
    cout << "交換後：s1=" << s1 << ", s2=" << s2 << endl;

    return 0;
}
```

**執行結果：**

```
=== 傳值交換（無效）===
呼叫前：x=10, y=20
  [swap_bad 內] a=20, b=10
呼叫後：x=10, y=20
=== 傳參考交換（有效）===
呼叫前：x=10, y=20
呼叫後：x=20, y=10
=== 模板交換（泛用）===
交換前：a=1.5, b=2.5
交換後：a=2.5, b=1.5
交換前：s1=Hello, s2=World
交換後：s1=World, s2=Hello
```

### 11.2.4 傳 const 參考：高效的只讀傳遞

當函數只需要**讀取**參數（不需要修改），但參數是大型物件時，傳 `const 參考`是最佳選擇。

```
傳值    ：建立副本（對小型資料 OK，大型資料浪費）
傳參考  ：可修改原始資料（不需修改時不應使用）
傳const參考：不複製，只讀（最安全且高效的唯讀傳遞）
```

📄 **範例檔案：** [ex11_2_4_const_param.cpp](examples/ex11_2_4_const_param.cpp)

```cpp
#include <iostream>
#include <string>
using namespace std;

// ❌ 傳值：每次呼叫都複製整個 string（代價高）
void print_by_value(string s) {
    cout << "[傳值]    " << s << endl;
}

// ✅ 傳 const 參考：零複製，效率高，且無法意外修改
void print_by_cref(const string& s) {
    cout << "[const參考] " << s << endl;
    // s += "!";   // ❌ 編譯錯誤！const 參考不能修改
}

// 計算字串中某字元出現次數
int countChar(const string& s, char target) {
    int count = 0;
    for (char c : s) {
        if (c == target) count++;
    }
    return count;
}

// 同時回傳最小值和最大值（用參考作為輸出參數）
void findMinMax(const int arr[], int size, int& minVal, int& maxVal) {
    minVal = maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }
}

int main() {
    string message = "Hello, C++ World!";

    print_by_value(message);    // 會複製 message
    print_by_cref(message);     // 不複製，直接存取

    // const 參考可以接受字面值
    print_by_cref("直接傳字串字面值也沒問題");

    cout << "\n'l' 出現次數：" << countChar(message, 'l') << endl;

    // 用參考作為「輸出參數」，讓函數回傳多個值
    int arr[] = {5, 2, 8, 1, 9, 3};
    int minVal, maxVal;
    findMinMax(arr, 6, minVal, maxVal);
    cout << "最小值：" << minVal << "，最大值：" << maxVal << endl;

    return 0;
}
```

**執行結果：**

```
[傳值]    Hello, C++ World!
[const參考] Hello, C++ World!
[const參考] 直接傳字串字面值也沒問題
'l' 出現次數：3
最小值：1，最大值：9
```

### 11.2.5 三種傳遞方式的選擇指南

📄 **範例檔案：** [ex11_2_5_performance.cpp](examples/ex11_2_5_performance.cpp)

```cpp
#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int    scores[100];
    double average;
};

// 傳值（複製整個結構體）
void process_value(Student s) {
    s.average = 99.0;    // 只修改副本
}

// 傳 const 參考（不複製，只讀）
void process_cref(const Student& s) {
    cout << "學生：" << s.name << "，平均：" << s.average << endl;
}

// 傳參考（不複製，可修改）
void process_ref(Student& s, double newAvg) {
    s.average = newAvg;  // 修改原始資料
}

int main() {
    Student alice;
    alice.name    = "Alice";
    alice.average = 85.0;

    cout << "=== 三種傳遞方式的效果 ===" << endl;
    cout << "原始 average = " << alice.average << endl;

    process_value(alice);
    cout << "傳值後 average = " << alice.average << endl;   // 不變

    process_ref(alice, 92.5);
    cout << "傳參考後 average = " << alice.average << endl;  // 改變了

    process_cref(alice);    // 只讀取

    cout << "\n=== 選擇指南 ===" << endl;
    cout << "┌──────────────────┬───────────────────────────┐" << endl;
    cout << "│ 情況             │ 建議傳遞方式              │" << endl;
    cout << "├──────────────────┼───────────────────────────┤" << endl;
    cout << "│ 小型資料，不修改 │ 傳值（int, double, char） │" << endl;
    cout << "│ 大型資料，不修改 │ const 參考                │" << endl;
    cout << "│ 需要修改呼叫者   │ 參考                      │" << endl;
    cout << "│ 需要回傳多個值   │ 參考作為輸出參數          │" << endl;
    cout << "└──────────────────┴───────────────────────────┘" << endl;

    return 0;
}
```

**執行結果：**

```
=== 三種傳遞方式的效果 ===
原始 average = 85
傳值後 average = 85
傳參考後 average = 92.5
學生：Alice，平均：92.5
=== 選擇指南 ===
┌──────────────────┬───────────────────────────┐
│ 情況             │ 建議傳遞方式              │
├──────────────────┼───────────────────────────┤
│ 小型資料，不修改 │ 傳值（int, double, char） │
│ 大型資料，不修改 │ const 參考                │
│ 需要修改呼叫者   │ 參考                      │
│ 需要回傳多個值   │ 參考作為輸出參數          │
└──────────────────┴───────────────────────────┘
```

---

## 11.3 參考回傳值

函數除了可以**接受**參考參數，也可以**回傳**參考。這讓函數的呼叫結果可以直接作為左值（被賦值）。

### 11.3.1 回傳參考的語法

```
回傳型別& 函數名稱(參數列) {
    return 某個具有持久生命期的變數;
}
```

```cpp
// 回傳型別加上 & 代表回傳參考
int& getElement(int arr[], int index) {
    return arr[index];   // 回傳陣列元素的參考
}

int arr[5] = {10, 20, 30, 40, 50};
getElement(arr, 2) = 99;    // 直接修改 arr[2]！
cout << arr[2];              // 99
```

📄 **範例檔案：** [ex11_3_1_return_ref.cpp](examples/ex11_3_1_return_ref.cpp)

```cpp
#include <iostream>
using namespace std;

// 全域陣列（生命期涵蓋整個程式）
int scores[5] = {70, 80, 90, 85, 75};

// ✅ 安全：回傳全域陣列元素的參考
int& getScore(int index) {
    return scores[index];
}

// ✅ 安全：回傳參數的參考（參數本身是參考）
int& getMax(int& a, int& b) {
    return (a > b) ? a : b;
}

// ✅ 安全：回傳靜態變數的參考
int& getCallCount() {
    static int count = 0;
    return count;
}

int main() {
    // 用回傳的參考修改全域陣列
    cout << "修改前 scores[2] = " << getScore(2) << endl;
    getScore(2) = 100;          // 直接修改！
    cout << "修改後 scores[2] = " << getScore(2) << endl;

    cout << "\n所有分數：";
    for (int i = 0; i < 5; i++) {
        cout << scores[i] << " ";
    }
    cout << endl;

    // getMax 回傳較大值的參考，可直接修改
    int x = 10, y = 20;
    cout << "\nx=" << x << ", y=" << y << endl;
    getMax(x, y) = 99;    // 將較大值（y=20）改為 99
    cout << "getMax(x,y)=99 後：x=" << x << ", y=" << y << endl;

    // 靜態變數計數器
    ++getCallCount();
    ++getCallCount();
    ++getCallCount();
    cout << "\n呼叫次數：" << getCallCount() << endl;

    return 0;
}
```

**執行結果：**

```
修改前 scores[2] = 90
修改後 scores[2] = 100
所有分數：70 80 100 85 75
x=10, y=20
getMax(x,y)=99 後：x=10, y=99
呼叫次數：3
```

### 11.3.2 鏈式呼叫（Method Chaining）

回傳參考最常見的應用之一，是讓物件的成員函數可以**連鎖呼叫**。這在標準庫（如 `cout`）中被廣泛使用。

> 💡 `cout << "A" << "B" << "C"` 能夠連鎖呼叫，正是因為 `operator<<` 回傳的是 `cout` 自身的參考。

📄 **範例檔案：** [ex11_3_2_chain.cpp](examples/ex11_3_2_chain.cpp)

```cpp
#include <iostream>
#include <string>
using namespace std;

// 簡易字串建構器（示範鏈式呼叫）
class StringBuilder {
public:
    string data;

    // 回傳 *this 的參考，實現鏈式呼叫
    StringBuilder& append(const string& s) {
        data += s;
        return *this;
    }

    StringBuilder& appendLine(const string& s) {
        data += s + "\n";
        return *this;
    }

    StringBuilder& clear() {
        data.clear();
        return *this;
    }

    void print() const {
        cout << data << endl;
    }
};

// 數值累加器（展示全域參考回傳）
int globalCounter = 0;
int& getCounter() { return globalCounter; }

int main() {
    cout << "=== 鏈式呼叫 ===" << endl;
    StringBuilder sb;

    // 連鎖呼叫：每次 append 都回傳 sb 自身的參考
    sb.append("C++").append(" 程式設計").appendLine(" 很有趣！")
      .append("參考（Reference）").appendLine(" 是重要的特性。");
    sb.print();

    // 使用回傳的參考直接賦值
    cout << "=== 全域計數器 ===" << endl;
    getCounter() = 10;
    cout << "設定為 10：" << getCounter() << endl;

    ++getCounter();
    cout << "遞增後：" << getCounter() << endl;

    getCounter() += 5;
    cout << "+= 5 後：" << getCounter() << endl;

    return 0;
}
```

**執行結果：**

```
=== 鏈式呼叫 ===
C++ 程式設計 很有趣！
參考（Reference） 是重要的特性。
=== 全域計數器 ===
設定為 10：10
遞增後：11
+= 5 後：16
```

### 11.3.3 ⚠️ 危險陷阱：懸空參考（Dangling Reference）

**絕對不要回傳區域變數的參考！** 這是 C++ 中最常見的嚴重錯誤之一。

```
函數呼叫流程：

  int& dangerousFunc() {
      int local = 42;    ← 建立區域變數
      return local;      ← 回傳其參考
  }                      ← 函數結束，local 被銷毀！

  int& ref = dangerousFunc();   ← ref 指向已銷毀的記憶體！
  cout << ref;                  ← 未定義行為！可能崩潰
```

📄 **範例檔案：** [ex11_3_3_dangling.cpp](examples/ex11_3_3_dangling.cpp)

```cpp
#include <iostream>
using namespace std;

// ❌ 危險！回傳區域變數的參考（懸空參考）
// 函數結束後，local 被銷毀，參考指向無效記憶體！
/*
int& dangerousFunc() {
    int local = 42;
    return local;       // ⚠️ 編譯器通常會發出警告
}
*/

// ✅ 安全：回傳的是「參數」的參考（參數由呼叫者管理）
int& safeMax(int& a, int& b) {
    return a > b ? a : b;
}

// ✅ 安全：回傳靜態變數（靜態變數在程式結束前一直存在）
int& getSingleton() {
    static int instance = 0;
    return instance;
}

// ✅ 安全：回傳全域變數
int globalVal = 100;
int& getGlobal() { return globalVal; }

// ❌ 常見的錯誤模式（用於教學，不要使用）
/*
string& createString() {
    string s = "Hello";
    return s;    // 區域變數！函數結束後 s 消失
}
*/

int main() {
    cout << "=== 合法的回傳參考方式 ===" << endl;

    // 回傳參數的參考
    int x = 5, y = 10;
    safeMax(x, y) = 99;
    cout << "safeMax(5,10)=99：y = " << y << endl;

    // 回傳靜態變數的參考
    getSingleton() = 42;
    cout << "Singleton = " << getSingleton() << endl;
    ++getSingleton();
    cout << "Singleton++ = " << getSingleton() << endl;

    // 回傳全域變數的參考
    getGlobal() += 50;
    cout << "globalVal = " << getGlobal() << endl;

    cout << "\n=== 記憶口訣 ===" << endl;
    cout << "可以回傳參考的來源：" << endl;
    cout << "  ✅ 全域變數" << endl;
    cout << "  ✅ 靜態變數" << endl;
    cout << "  ✅ 傳入的參考參數" << endl;
    cout << "  ❌ 區域變數（絕對不行！）" << endl;

    return 0;
}
```

**執行結果：**

```
=== 合法的回傳參考方式 ===
safeMax(5,10)=99：y = 99
Singleton = 42
Singleton++ = 43
globalVal = 150
=== 記憶口訣 ===
可以回傳參考的來源：
  ✅ 全域變數
  ✅ 靜態變數
  ✅ 傳入的參考參數
  ❌ 區域變數（絕對不行！）
```

---

## 11.4 參考應用

### 11.4.1 Range-based For 迴圈中的參考

C++11 引入的 range-based for 迴圈搭配參考，是現代 C++ 最常用的寫法之一。

```cpp
// 只讀（不需要參考）
for (int x : arr) { ... }

// 修改元素（必須用參考！）
for (int& x : arr) { ... }

// 大型物件只讀（const 參考，避免複製）
for (const string& s : words) { ... }

// 自動推導型別（最常見的寫法）
for (auto& x : collection) { ... }
for (const auto& x : collection) { ... }
```

📄 **範例檔案：** [ex11_4_1_range_for.cpp](examples/ex11_4_1_range_for.cpp)

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    // === 場景1：只讀取（不需要參考）===
    int arr[] = {1, 2, 3, 4, 5};
    cout << "原始陣列：";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    // === 場景2：修改元素（必須用參考！）===
    cout << "\n每個元素乘以 2：";
    for (int& x : arr) {     // 必須用 & 才能修改
        x *= 2;
    }
    for (int x : arr) { cout << x << " "; }
    cout << endl;

    // 對照：不用參考的「修改」是無效的
    for (int x : arr) {    // x 是副本
        x = 0;             // 只修改副本，陣列沒有變
    }
    cout << "（不用&）修改後陣列：";
    for (int x : arr) { cout << x << " "; }  // 數值不變！
    cout << endl;

    // === 場景3：大型物件用 const 參考避免複製 ===
    vector<string> fruits = {"apple", "banana", "cherry", "date"};
    cout << "\n水果清單（const 參考，不複製）：" << endl;
    for (const string& fruit : fruits) {    // 不複製，只讀
        cout << "  " << fruit << "（" << fruit.length() << " 字元）" << endl;
    }

    // === 場景4：auto& 自動推導型別 ===
    vector<int> nums = {10, 20, 30, 40, 50};
    for (auto& n : nums) {
        n += 5;    // 每個元素加 5
    }
    cout << "\n加 5 後：";
    for (auto n : nums) { cout << n << " "; }
    cout << endl;

    return 0;
}
```

**執行結果：**

```
原始陣列：1 2 3 4 5
每個元素乘以 2：2 4 6 8 10
（不用&）修改後陣列：2 4 6 8 10
水果清單（const 參考，不複製）：
  apple（5 字元）
  banana（6 字元）
  cherry（6 字元）
  date（4 字元）
加 5 後：15 25 35 45 55
```

### 11.4.2 參考作為別名：簡化複雜表達式

當你需要多次存取某個「深層」的資料時，可以用參考建立一個短名稱（別名），讓程式碼更清晰。

📄 **範例檔案：** [ex11_4_2_alias.cpp](examples/ex11_4_2_alias.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    // === 場景1：簡化矩陣元素存取 ===
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // 不用別名：重複寫 matrix[1][1]
    cout << "中心元素（前）：" << matrix[1][1] << endl;

    // 用別名：清晰且高效（不複製）
    int& center = matrix[1][1];
    center = 99;
    cout << "中心元素（後）：" << center << endl;
    cout << "matrix[1][1] = " << matrix[1][1] << endl;

    // === 場景2：在迴圈中簡化存取 ===
    int data[3][3] = {
        {10, 20, 30},
        {40, 50, 60},
        {70, 80, 90}
    };

    cout << "\n處理前：" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << data[i][j] << "\t";
        }
        cout << endl;
    }

    // 用別名讓迴圈體更清晰
    for (int i = 0; i < 3; i++) {
        int& first = data[i][0];    // 每行第一個元素的別名
        int& last  = data[i][2];    // 每行最後元素的別名
        int  mid   = data[i][1];    // 中間元素（只讀，不需要別名）

        first += mid;    // 第一個加上中間
        last  -= mid;    // 最後一個減去中間
    }

    cout << "\n處理後：" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << data[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}
```

**執行結果：**

```
中心元素（前）：5
中心元素（後）：99
matrix[1][1] = 99
處理前：
10    20    30
40    50    60
70    80    90
處理後：
30    20    10
90    50    10
150   80    10
```

### 11.4.3 結構體與參考

結構體（struct）通常佔用較大記憶體，傳遞時特別需要參考來避免複製。

📄 **範例檔案：** [ex11_4_3_struct_ref.cpp](examples/ex11_4_3_struct_ref.cpp)

```cpp
#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int    score;
    string grade;
};

// 用參考修改結構體（不複製）
void computeGrade(Student& s) {
    if      (s.score >= 90) s.grade = "A";
    else if (s.score >= 80) s.grade = "B";
    else if (s.score >= 70) s.grade = "C";
    else if (s.score >= 60) s.grade = "D";
    else                    s.grade = "F";
}

// 用 const 參考讀取（不修改、不複製）
void printStudent(const Student& s) {
    cout << "  姓名：" << s.name
         << "，分數：" << s.score
         << "，等第：" << s.grade << endl;
}

// 回傳最高分學生的參考
Student& findTop(Student arr[], int size) {
    int maxIdx = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i].score > arr[maxIdx].score) {
            maxIdx = i;
        }
    }
    return arr[maxIdx];
}

int main() {
    Student students[4] = {
        {"Alice",   92, ""},
        {"Bob",     78, ""},
        {"Charlie", 85, ""},
        {"Diana",   95, ""}
    };

    // 為所有學生計算等第
    for (int i = 0; i < 4; i++) {
        computeGrade(students[i]);
    }

    cout << "=== 所有學生 ===" << endl;
    for (int i = 0; i < 4; i++) {
        printStudent(students[i]);
    }

    // 找出最高分並直接修改
    Student& top = findTop(students, 4);
    cout << "\n=== 最高分學生 ===" << endl;
    printStudent(top);

    top.score += 3;       // 加分
    computeGrade(top);    // 重新計算等第
    cout << "加分後：";
    printStudent(top);

    return 0;
}
```

**執行結果：**

```
=== 所有學生 ===
  姓名：Alice，分數：92，等第：A
  姓名：Bob，分數：78，等第：C
  姓名：Charlie，分數：85，等第：B
  姓名：Diana，分數：95，等第：A
=== 最高分學生 ===
  姓名：Diana，分數：95，等第：A
加分後：  姓名：Diana，分數：98，等第：A
```

### 11.4.4 字串與參考

`std::string` 是 C++ 中最常用的大型物件之一，搭配參考可以大幅提升效率，同時讓程式碼更清晰。

📄 **範例檔案：** [ex11_4_4_string_ref.cpp](examples/ex11_4_4_string_ref.cpp)

```cpp
#include <iostream>
#include <string>
using namespace std;

// const 參考參數：不複製，只讀取
bool isPalindrome(const string& s) {
    int left = 0, right = (int)s.length() - 1;
    while (left < right) {
        if (s[left] != s[right]) return false;
        left++;
        right--;
    }
    return true;
}

// 參考參數：就地修改字串
void toUpperCase(string& s) {
    for (char& c : s) {    // char 也用參考
        if (c >= 'a' && c <= 'z') c -= 32;
    }
}

// 就地字串替換
void replaceChar(string& s, char from, char to) {
    for (char& c : s) {
        if (c == from) c = to;
    }
}

// 回傳較長字串的參考
string& getLonger(string& a, string& b) {
    return a.length() >= b.length() ? a : b;
}

int main() {
    // 回文判斷
    string words[] = {"racecar", "hello", "level", "world", "madam"};
    cout << "=== 回文判斷 ===" << endl;
    for (const string& w : words) {
        cout << "  \"" << w << "\"：" << (isPalindrome(w) ? "是" : "否") << endl;
    }

    // 就地大寫轉換
    string msg = "hello, c++ world!";
    cout << "\n=== 大寫轉換 ===" << endl;
    cout << "原始：" << msg << endl;
    toUpperCase(msg);
    cout << "轉換：" << msg << endl;

    // 就地替換
    replaceChar(msg, ' ', '_');
    cout << "空格→底線：" << msg << endl;

    // 回傳參考，直接修改較長的字串
    string s1 = "Hi";
    string s2 = "Hello World";
    cout << "\n=== 修改較長字串 ===" << endl;
    cout << "前：s1=\"" << s1 << "\", s2=\"" << s2 << "\"" << endl;
    getLonger(s1, s2) = "已被替換";
    cout << "後：s1=\"" << s1 << "\", s2=\"" << s2 << "\"" << endl;

    return 0;
}
```

**執行結果：**

```
=== 回文判斷 ===
  "racecar"：是
  "hello"：否
  "level"：是
  "world"：否
  "madam"：是
=== 大寫轉換 ===
原始：hello, c++ world!
轉換：HELLO, C++ WORLD!
空格→底線：HELLO,_C++_WORLD!
=== 修改較長字串 ===
前：s1="Hi", s2="Hello World"
後：s1="Hi", s2="已被替換"
```

---

## 章節總結

```
第十一章：參考（Reference）
│
├─ 11.1 宣告及初始
│   ├─ 參考是變數的「別名」，共用同一記憶體位址
│   ├─ 語法：型別& 名稱 = 變數;
│   ├─ 三大規則
│   │   ├─ 必須在宣告時初始化
│   │   ├─ 綁定後無法改變（無法重新綁定）
│   │   └─ 不能是 null
│   ├─ vs 指標：語法更簡單，但彈性較低
│   └─ const 參考：只讀，可綁定字面值/臨時值
│
├─ 11.2 參數傳遞
│   ├─ 傳值（Pass by Value）
│   │   └─ 複製副本，不影響原始資料
│   ├─ 傳參考（Pass by Reference）
│   │   └─ 函數可修改呼叫者的變數
│   ├─ 傳 const 參考（Pass by const Reference）
│   │   └─ 高效只讀，避免複製大型物件
│   └─ 選擇原則
│       ├─ 小型資料（int/double）且不修改 → 傳值
│       ├─ 大型資料且不修改 → const 參考
│       └─ 需要修改 → 參考
│
├─ 11.3 參考回傳值
│   ├─ 語法：回傳型別& 函數名稱(...)
│   ├─ 回傳後可作為左值（被賦值）
│   ├─ 鏈式呼叫（Method Chaining）
│   └─ ⚠️ 絕對不能回傳區域變數的參考！
│       ├─ ✅ 可回傳：全域變數、靜態變數、傳入的參考參數
│       └─ ❌ 不可回傳：區域變數（懸空參考！）
│
└─ 11.4 參考應用
    ├─ Range-based for + 參考（修改元素）
    ├─ Range-based for + const 參考（高效讀取）
    ├─ 別名：簡化複雜的巢狀存取
    ├─ 結構體參考：避免複製大型結構體
    └─ 字串參考：就地修改，高效傳遞
```

---

## 實作練習

### 基礎題

**題目 1【宣告與修改】**

宣告一個整數變數 `score = 60`，建立它的參考 `ref_score`，透過參考將值增加 40，最後分別印出 `score` 和 `ref_score` 的值與記憶體位址，驗證兩者位址相同。

**題目 2【const 參考】**

寫一個函數 `void displayInfo(const string& name, const int& age)`，用 const 參考接收姓名和年齡，並印出 `"姓名：XXX，年齡：YY 歲"`。在 `main` 中呼叫並測試。

**題目 3【傳參考】**

寫一個函數 `void increment(int& n, int step = 1)`，將 `n` 增加 `step`。在 main 中測試：

- `increment(x)` → 加 1
- `increment(x, 5)` → 加 5

---

### 中階題

**題目 4【多值回傳】**

寫一個函數 `void calcStats(const int arr[], int size, int& sum, double& avg, int& maxVal)`，用參考同時計算並回傳整數陣列的總和、平均、最大值。在 main 中測試：輸入 `{5, 3, 8, 1, 9, 2, 7}`，印出結果。

**題目 5【就地字串處理】**

寫以下兩個函數，都接受 `string&` 參數（就地修改）：

- `void reverseStr(string& s)`：反轉字串
- `void removeSpaces(string& s)`：移除所有空白字元

在 main 中對 `"Hello World"` 連續呼叫這兩個函數，觀察結果。

**題目 6【泡沫排序法 + 參考交換】**

實作泡沫排序法（Bubble Sort）。要求：

1. 寫 `void mySwap(int& a, int& b)` 用參考實作交換
2. 寫 `void bubbleSort(int arr[], int size)` 使用 `mySwap` 進行排序
3. 在 main 中對 `{64, 34, 25, 12, 22, 11, 90}` 進行排序並印出排序過程

**題目 7【Range-for 應用】**

有一個整數陣列 `{-3, 7, -1, 5, -8, 2, -4, 6}`，用 range-based for 迴圈（搭配參考）完成：

1. 將所有負數改為正數（取絕對值）
2. 計算所有元素的總和
3. 找出最大值和最小值（不修改，用 const 參考）

---

### 進階題

**題目 8【結構體參考應用】**

定義結構體 `Point { double x, y; }`，寫以下函數：

- `void move(Point& p, double dx, double dy)`：移動點的座標
- `double distance(const Point& p1, const Point& p2)`：計算兩點距離
- `Point& closer(Point& p1, Point& p2, const Point& origin)`：回傳離原點較近的點之參考

在 main 中測試：建立兩個點，移動其中一個，計算距離，找出較近的點並修改其座標。

**題目 9【回傳參考的自訂容器】**

設計一個簡單的「安全陣列」類別 `SafeArray`：

```cpp
class SafeArray {
    int data[100];
    int size;
public:
    SafeArray(int n);
    int& at(int index);          // 回傳元素參考（含邊界檢查）
    int size_of() const;
};
```

實作 `at()`：如果 index 超出範圍，印出錯誤訊息並回傳 `data[0]` 的參考（不崩潰）。在 main 中測試讀取、修改和越界存取。

**題目 10【字串解析器】**

寫一個函數 `void parseCSV(const string& line, string& field1, string& field2, string& field3)`，解析逗號分隔的字串，把三個欄位分別存入三個參考參數。例如輸入 `"Alice,92,A"` → `field1="Alice"`, `field2="92"`, `field3="A"`。在 main 中讀取多行 CSV 並印出解析結果。

---

## 面試考題

**Q1：參考（Reference）和指標（Pointer）有什麼主要區別？**

> **參考答案：**
>
> | 比較點     | 參考                     | 指標                   |
> | ---------- | ------------------------ | ---------------------- |
> | 初始化     | 宣告時必須初始化         | 可延後初始化           |
> | null 值    | 不能是 null              | 可以是 nullptr         |
> | 重新綁定   | 不能（一旦綁定永遠不變） | 可以（隨時改變指向）   |
> | 使用語法   | 直接使用，像普通變數     | 需要 `*` 解參考        |
> | 記憶體佔用 | 通常不佔額外空間         | 佔 4 或 8 bytes        |
> | nullptr    | 無法是 null → 更安全     | 可能是 null → 需要檢查 |
>
> 一般來說，當你只需要一個變數的別名（如函數參數、返回值）時，優先使用參考；需要動態記憶體管理或改變指向時，使用指標。

---

**Q2：什麼時候應該用 `const 參考`？什麼時候用傳值？**

> **參考答案：**
>
> - **傳值（Pass by Value）**：當資料型別小（`int`、`double`、`char`、`bool`），或你需要在函數內修改副本而不影響原始資料時。
> - **傳 const 參考（Pass by const Reference）**：當資料型別較大（`string`、`struct`、`class`、`vector` 等），且函數只需要讀取資料（不修改）時。這樣可以避免複製帶來的效能損耗，同時用 `const` 保證資料不被意外修改。
>
> 規則：**「大型物件 + 只讀 → const 參考；需要修改 → 參考；小型基本型別 → 傳值」**

---

**Q3：為什麼不能回傳區域變數的參考？**

> **參考答案：**
>
> 區域變數的生命期只在函數執行期間。函數返回後，區域變數所佔用的堆疊（stack）空間被釋放，其記憶體內容可能立刻被其他資料覆蓋。如果回傳其參考，呼叫者拿到的是一個指向「已釋放記憶體」的參考，稱為**懸空參考（Dangling Reference）**。
>
> 存取懸空參考是**未定義行為（Undefined Behavior）**，可能導致：
>
> - 讀到垃圾值
> - 程式崩潰
> - 難以重現的 bug
>
> **安全的回傳參考來源**：全域變數、靜態變數、傳入的參考參數（生命期由呼叫者管理）。

---

**Q4：什麼是左值（lvalue）和右值（rvalue）？與參考有什麼關係？**

> **參考答案：**
>
> - **左值（lvalue）**：有持久記憶體位址、可以出現在賦值左側的表達式。例如：變數 `x`、陣列元素 `arr[i]`、解參考的指標 `*p`。
> - **右值（rvalue）**：臨時的、沒有持久位址的值，通常出現在賦值右側。例如：字面值 `42`、運算結果 `x + 1`、函數回傳的臨時值。
>
> 與參考的關係：
>
> - **非 const 參考**：只能綁定左值（可修改的左值）
> - **const 參考**：可以綁定左值和右值（字面值、臨時值）
> - **右值參考（`&&`，C++11）**：專門用來綁定右值，用於移動語意（Move Semantics）和完美轉發（Perfect Forwarding）

---

**Q5：請解釋以下程式碼的行為，並指出問題所在：**

```cpp
int& getRef() {
    int x = 10;
    return x;
}

int main() {
    int& r = getRef();
    cout << r << endl;
}
```

> **參考答案：**
>
> 這段程式碼有**未定義行為**，是一個嚴重的 bug。
>
> 問題所在：`getRef()` 回傳了區域變數 `x` 的參考。當函數執行完畢，`x` 的生命期結束，其記憶體被回收。`r` 成為懸空參考，指向已無效的記憶體位址。
>
> `cout << r` 的結果是未定義的：可能印出 `10`（記憶體尚未被覆蓋），也可能印出垃圾值，甚至導致程式崩潰。大多數現代編譯器會在編譯時發出警告：`warning: reference to local variable 'x' returned`。
>
> **修正方式**：使用靜態變數、全域變數，或傳入參考參數並回傳它。

---

## 專案：學生成績管理系統（Grade Manager）

### 專案說明

實作一個命令列學生成績管理系統，綜合運用本章所學的參考技巧。系統需具備以下功能：

1. 新增學生（姓名 + 多科成績）
2. 修改學生成績（用參考直接修改）
3. 顯示所有學生（const 參考，不複製）
4. 計算統計資料（平均、最高、最低）
5. 依成績排序（參考交換）
6. 搜尋學生並回傳參考（支援直接修改）

### 學習重點對應

| 功能      | 用到的參考技術             |
| --------- | -------------------------- |
| 新增/修改 | 傳參考修改結構體資料       |
| 顯示      | const 參考避免複製         |
| 統計      | 參考作為輸出參數           |
| 排序      | 傳參考的 swap 函數         |
| 搜尋      | 回傳參考讓外部可直接修改   |
| 輸入處理  | const 參考接受 string 參數 |

### 專案範例執行

```
============================
     學生成績管理系統
============================
1. 新增學生
2. 顯示所有學生
3. 修改學生成績
4. 成績統計
5. 依平均分數排序
6. 搜尋學生
0. 離開
請選擇：
```

📄 **完整解答：** [project11_grade_manager_answer.cpp](examples/project11_grade_manager_answer.cpp)

```cpp
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_STUDENTS  = 50;
const int MAX_SUBJECTS  = 5;
const string SUBJECTS[] = {"國文", "英文", "數學", "物理", "化學"};

struct Student {
    string name;
    int    scores[MAX_SUBJECTS];
    double average;
    string grade;
};

// ─── 工具函數 ───────────────────────────────────────────────

void computeAvgGrade(Student& s) {    // 傳參考，直接修改
    int sum = 0;
    for (int i = 0; i < MAX_SUBJECTS; i++) sum += s.scores[i];
    s.average = sum / (double)MAX_SUBJECTS;

    if      (s.average >= 90) s.grade = "A";
    else if (s.average >= 80) s.grade = "B";
    else if (s.average >= 70) s.grade = "C";
    else if (s.average >= 60) s.grade = "D";
    else                      s.grade = "F";
}

void printHeader() {
    cout << left
         << setw(10) << "姓名"
         << setw(8)  << "國文"
         << setw(8)  << "英文"
         << setw(8)  << "數學"
         << setw(8)  << "物理"
         << setw(8)  << "化學"
         << setw(8)  << "平均"
         << setw(5)  << "等第" << endl;
    cout << string(63, '-') << endl;
}

void printStudent(const Student& s) {    // const 參考，不複製
    cout << left << setw(10) << s.name;
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        cout << setw(8) << s.scores[i];
    }
    cout << fixed << setprecision(1)
         << setw(8) << s.average
         << setw(5) << s.grade << endl;
}

void swapStudents(Student& a, Student& b) {    // 傳參考交換
    Student temp = a;
    a = b;
    b = temp;
}

// ─── 功能函數 ───────────────────────────────────────────────

void addStudent(Student arr[], int& count) {    // count 傳參考
    if (count >= MAX_STUDENTS) {
        cout << "已達學生人數上限！" << endl;
        return;
    }
    Student& s = arr[count];    // 別名，簡化後續程式碼
    cout << "請輸入姓名：";
    cin >> s.name;
    cout << "請輸入五科成績（國英數物化）：";
    for (int i = 0; i < MAX_SUBJECTS; i++) cin >> s.scores[i];
    computeAvgGrade(s);
    count++;
    cout << "✅ 學生 " << s.name << " 已新增！" << endl;
}

void displayAll(const Student arr[], int count) {    // const 陣列
    if (count == 0) { cout << "目前沒有學生資料。" << endl; return; }
    cout << "\n=== 所有學生 ===" << endl;
    printHeader();
    for (int i = 0; i < count; i++) {
        printStudent(arr[i]);
    }
    cout << endl;
}

Student* findStudent(Student arr[], int count, const string& name) {
    for (int i = 0; i < count; i++) {
        if (arr[i].name == name) return &arr[i];
    }
    return nullptr;
}

void modifyScore(Student arr[], int count) {
    string name;
    cout << "請輸入要修改的學生姓名：";
    cin >> name;

    Student* sp = findStudent(arr, count, name);
    if (!sp) { cout << "找不到學生 " << name << endl; return; }

    Student& s = *sp;    // 建立參考，讓後續操作更簡潔
    cout << "目前成績：";
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        cout << SUBJECTS[i] << "=" << s.scores[i] << " ";
    }
    cout << "\n要修改哪科？（1=國文 2=英文 3=數學 4=物理 5=化學）：";
    int subj;
    cin >> subj;
    if (subj < 1 || subj > 5) { cout << "無效選項" << endl; return; }

    cout << "新成績：";
    cin >> s.scores[subj - 1];
    computeAvgGrade(s);
    cout << "✅ 修改完成！";
    printStudent(s);
}

void showStats(const Student arr[], int count) {
    if (count == 0) { cout << "沒有資料。" << endl; return; }

    // 用參考輸出參數（或這裡直接計算）
    double totalAvg = 0;
    int    topIdx = 0, botIdx = 0;

    for (int i = 0; i < count; i++) {
        totalAvg += arr[i].average;
        if (arr[i].average > arr[topIdx].average) topIdx = i;
        if (arr[i].average < arr[botIdx].average) botIdx = i;
    }

    cout << "\n=== 成績統計 ===" << endl;
    cout << "全班平均：" << fixed << setprecision(1) << totalAvg / count << endl;
    cout << "最高分：" << arr[topIdx].name << "（" << arr[topIdx].average << "）" << endl;
    cout << "最低分：" << arr[botIdx].name << "（" << arr[botIdx].average << "）" << endl;

    cout << "\n各等第人數：" << endl;
    int gradeCount[5] = {};
    for (int i = 0; i < count; i++) {
        if      (arr[i].grade == "A") gradeCount[0]++;
        else if (arr[i].grade == "B") gradeCount[1]++;
        else if (arr[i].grade == "C") gradeCount[2]++;
        else if (arr[i].grade == "D") gradeCount[3]++;
        else                          gradeCount[4]++;
    }
    string grades[] = {"A", "B", "C", "D", "F"};
    for (int i = 0; i < 5; i++) {
        cout << "  " << grades[i] << "：" << gradeCount[i] << " 人" << endl;
    }
}

void sortByAverage(Student arr[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (arr[j].average < arr[j + 1].average) {
                swapStudents(arr[j], arr[j + 1]);    // 傳參考交換
            }
        }
    }
    cout << "✅ 已依平均分數（由高到低）排序！" << endl;
}

void searchStudent(Student arr[], int count) {
    string name;
    cout << "請輸入搜尋姓名：";
    cin >> name;

    Student* sp = findStudent(arr, count, name);
    if (!sp) { cout << "找不到學生 " << name << endl; return; }

    cout << "\n找到學生：" << endl;
    printHeader();
    printStudent(*sp);
}

// ─── 主程式 ─────────────────────────────────────────────────

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;

    // 預先新增幾位測試學生
    students[0] = {"Alice",   {92, 88, 95, 90, 87}, 0, ""};
    students[1] = {"Bob",     {75, 82, 70, 68, 79}, 0, ""};
    students[2] = {"Charlie", {85, 91, 88, 83, 90}, 0, ""};
    students[3] = {"Diana",   {95, 97, 99, 94, 96}, 0, ""};
    count = 4;
    for (int i = 0; i < count; i++) computeAvgGrade(students[i]);

    int choice;
    do {
        cout << "\n=============================" << endl;
        cout << "     學生成績管理系統" << endl;
        cout << "=============================" << endl;
        cout << "1. 新增學生" << endl;
        cout << "2. 顯示所有學生" << endl;
        cout << "3. 修改學生成績" << endl;
        cout << "4. 成績統計" << endl;
        cout << "5. 依平均分數排序" << endl;
        cout << "6. 搜尋學生" << endl;
        cout << "0. 離開" << endl;
        cout << "請選擇：";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(students, count); break;
            case 2: displayAll(students, count); break;
            case 3: modifyScore(students, count); break;
            case 4: showStats(students, count); break;
            case 5: sortByAverage(students, count); break;
            case 6: searchStudent(students, count); break;
            case 0: cout << "掰掰！" << endl; break;
            default: cout << "無效選項，請重新輸入。" << endl;
        }
    } while (choice != 0);

    return 0;
}
```

**專案執行範例：**

```
=============================
     學生成績管理系統
=============================
1. 新增學生
...
請選擇：2

=== 所有學生 ===
姓名      國文    英文    數學    物理    化學    平均    等第
---------------------------------------------------------------
Alice     92      88      95      90      87      90.4    A
Bob       75      82      70      68      79      74.8    C
Charlie   85      91      88      83      90      87.4    B
Diana     95      97      99      94      96      96.2    A
```
