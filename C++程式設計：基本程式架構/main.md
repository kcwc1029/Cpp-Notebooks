# 第二章：基本程式架構

> **學習目標**
> - 理解 C++ 程式的基本骨架與執行流程
> - 掌握變數宣告、資料型別與常數的使用
> - 熟練使用 `cout` 進行格式化輸出
> - 熟練使用 `cin` 與 `getline` 進行使用者輸入
> - 建立良好的命名習慣與程式風格

---

## 2.1 程式骨架

### 2.1.1 你的第一支程式

學習任何程式語言的第一步，就是寫出一支在螢幕上印出 `Hello, World!` 的程式。這個傳統可追溯至 1978 年的 C 語言教科書，至今已成為程式設計的入門儀式。

**範例檔：`ex2_1_hello.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}
```

**輸出結果：**
```
Hello, World!
```

雖然只有六行，但這支程式包含了 C++ 的所有核心結構。接下來我們逐行拆解。

---

### 2.1.2 逐行解析程式骨架

```
┌─────────────────────────────────────────────────┐
│  #include <iostream>        ← 前置處理指令        │
│  using namespace std;       ← 命名空間宣告        │
│                                                  │
│  int main() {               ← 主函式開頭          │
│      cout << "Hello!" << endl;  ← 程式內容       │
│      return 0;              ← 回傳值              │
│  }                          ← 主函式結尾          │
└─────────────────────────────────────────────────┘
```

#### `#include <iostream>`

`#include` 是**前置處理指令（Preprocessor Directive）**，在程式編譯前執行。它告訴編譯器「把 `iostream` 這個標頭檔的內容複製進來」。

- `iostream` = **i**nput/**o**utput **stream**，提供 `cin`（輸入）與 `cout`（輸出）功能
- 尖括號 `< >` 代表這是系統提供的標準函式庫
- 引號 `" "` 則用於引入自己寫的標頭檔

常用的標頭檔：

| 標頭檔 | 用途 |
|--------|------|
| `<iostream>` | 基本輸入／輸出 |
| `<string>` | 字串處理 |
| `<cmath>` | 數學函式（sqrt、pow 等） |
| `<iomanip>` | 格式化輸出 |
| `<vector>` | 動態陣列 |
| `<algorithm>` | 排序、搜尋等演算法 |

#### `using namespace std;`

C++ 的標準函式庫中所有功能都放在 `std`（standard）這個**命名空間（namespace）**裡。如果不加這行，就必須每次都寫 `std::cout`、`std::endl`。

```cpp
// 不使用 using namespace std; 的寫法
std::cout << "Hello!" << std::endl;

// 使用 using namespace std; 的寫法（較簡潔）
cout << "Hello!" << endl;
```

> **工程師觀點**：在大型專案中，不建議在標頭檔中使用 `using namespace std;`，以避免命名衝突。但在學習階段，為了簡潔可放心使用。

#### `int main()`

`main()` 是**程式的進入點（Entry Point）**，每支 C++ 程式有且只有一個 `main()`。

- `int` 代表 `main()` 執行完畢後會回傳一個整數給作業系統
- 大括號 `{ }` 包住函式的內容（稱為**函式主體**）

#### `return 0;`

程式結束時回傳 `0` 給作業系統，代表「程式正常結束」。若回傳非零值，通常代表發生錯誤。這是 Unix/Linux 系統的慣例。

---

### 2.1.3 註解（Comments）

註解是給**人讀的說明文字**，編譯器會完全忽略它。寫好的註解是優秀工程師的基本素養。

**範例檔：`ex2_1_comments.cpp`**

```cpp
#include <iostream>
using namespace std;

// 這是單行註解，從 // 到行尾都是註解

/*
 * 這是多行註解
 * 適合用於較長的說明
 * 或暫時關閉一段程式碼
 */

int main() {
    // 印出歡迎訊息
    cout << "歡迎來到 C++ 的世界！" << endl;

    /*
    cout << "這行被暫時關閉了" << endl;
    cout << "這行也是" << endl;
    */

    return 0;
}
```

**好註解 vs. 壞註解：**

```cpp
// ❌ 壞註解：說明顯而易見的事
i = i + 1; // 把 i 加 1

// ✅ 好註解：說明「為什麼」這樣做
i = i + 1; // 索引從 0 開始，需加 1 才對齊顯示位置

// ✅ 好註解：說明演算法的關鍵步驟
// 使用牛頓法求平方根，收斂條件為誤差 < 1e-7
```

---

### 2.1.4 程式的編譯與執行流程

了解程式從原始碼到執行的過程，有助於理解各種錯誤訊息。

```
原始碼 (.cpp)
    ↓  前置處理器（Preprocessor）
    │  展開 #include、#define 等指令
    ↓
展開後的原始碼
    ↓  編譯器（Compiler）
    │  轉換成機器語言，進行語法檢查
    ↓
目的碼 (.o / .obj)
    ↓  連結器（Linker）
    │  結合各目的碼與函式庫
    ↓
執行檔 (.exe / a.out)
    ↓  執行
    ↓
輸出結果
```

**三種常見錯誤：**

| 錯誤類型 | 發生時機 | 範例 |
|----------|----------|------|
| 語法錯誤（Syntax Error） | 編譯時 | 忘記加分號 `;` |
| 連結錯誤（Linker Error） | 連結時 | 呼叫未定義的函式 |
| 執行時錯誤（Runtime Error） | 執行時 | 除以零、陣列超出範圍 |

---

### 2.1.5 程式碼風格

良好的風格讓程式更易閱讀與維護。

**範例檔：`ex2_1_style.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    // 縮排使用 4 個空格（或 1 個 Tab）
    int score = 95;
    
    // 運算子兩側加空格，增加可讀性
    int total = score + 5;
    
    cout << "分數：" << score << endl;
    cout << "加分後：" << total << endl;
    
    return 0;
}
```

**基本風格規範：**
- 每個縮排層級使用 **4 個空格**（業界主流）
- 左大括號 `{` 可與函式名在同一行，或另起一行（擇一即可，保持一致）
- 每行不超過 **80～100 個字元**
- 運算子（`+`, `-`, `=` 等）兩側各加一個空格

---

## 2.2 變數

### 2.2.1 什麼是變數？

**變數（Variable）**是記憶體中的一塊空間，用來儲存資料。你可以把它想像成一個「有名字的盒子」：

```
  變數名稱      記憶體位址
   ┌─────┐
   │  42 │  ←── int age = 42;
   └─────┘
    age
```

變數有三個重要屬性：
1. **名稱（Name）**：用來存取這塊記憶體
2. **型別（Type）**：決定能儲存什麼資料、佔用多少記憶體
3. **值（Value）**：目前儲存的資料

---

### 2.2.2 基本資料型別

C++ 的基本資料型別（Primitive Data Types）：

#### 整數型別

| 型別 | 大小 | 範圍 | 用途 |
|------|------|------|------|
| `int` | 4 bytes | -2,147,483,648 ~ 2,147,483,647 | 最常用的整數 |
| `short` | 2 bytes | -32,768 ~ 32,767 | 較小範圍整數 |
| `long` | 4/8 bytes | 視系統而定 | 較大整數 |
| `long long` | 8 bytes | ±9.2 × 10¹⁸ | 超大整數 |
| `unsigned int` | 4 bytes | 0 ~ 4,294,967,295 | 非負整數 |

#### 浮點數型別

| 型別 | 大小 | 精確度 | 用途 |
|------|------|--------|------|
| `float` | 4 bytes | 約 7 位有效數字 | 一般小數 |
| `double` | 8 bytes | 約 15 位有效數字 | **預設浮點數** |
| `long double` | 16 bytes | 約 18 位有效數字 | 高精度計算 |

> **建議**：除非有記憶體限制，浮點數一律使用 `double`，精度更高。

#### 字元型別

| 型別 | 大小 | 用途 |
|------|------|------|
| `char` | 1 byte | 單一字元（ASCII） |
| `wchar_t` | 2/4 bytes | 寬字元（Unicode） |

#### 布林型別

| 型別 | 大小 | 值 |
|------|------|-----|
| `bool` | 1 byte | `true`（1）或 `false`（0） |

#### 字串型別（需引入 `<string>`）

| 型別 | 說明 |
|------|------|
| `string` | C++ 字串類別，功能豐富、推薦使用 |

**範例檔：`ex2_2_datatypes.cpp`**

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    // 整數
    int age = 20;
    long long population = 8000000000LL; // 全球人口，需加 LL 後綴

    // 浮點數
    double height = 175.5;
    float temperature = 36.6f;  // float 字面值加 f 後綴

    // 字元
    char grade = 'A';           // 字元用單引號

    // 布林
    bool isStudent = true;

    // 字串
    string name = "Alice";      // 字串用雙引號

    cout << "姓名：" << name << endl;
    cout << "年齡：" << age << endl;
    cout << "身高：" << height << " cm" << endl;
    cout << "體溫：" << temperature << " °C" << endl;
    cout << "成績：" << grade << endl;
    cout << "是學生：" << isStudent << endl;  // 輸出 1 (true) 或 0 (false)
    cout << "全球人口：" << population << endl;

    return 0;
}
```

**輸出結果：**
```
姓名：Alice
年齡：20
身高：175.5 cm
體溫：36.6 °C
成績：A
是學生：1
全球人口：8000000000
```

---

### 2.2.3 變數宣告與初始化

```cpp
// 宣告：告訴編譯器「有一個這樣的變數」
int score;

// 初始化：宣告的同時給予初始值（推薦）
int score = 100;

// C++11 的統一初始化語法（Uniform Initialization）
int score{100};

// 宣告多個同型別變數（可，但可讀性較差）
int a, b, c;

// 宣告多個並各自初始化
int x = 1, y = 2, z = 3;
```

> ⚠️ **重要**：未初始化的局部變數，其值是**不確定的垃圾值**，這是初學者常見的 bug 來源！

**範例檔：`ex2_2_uninitialized.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int x;          // ❌ 未初始化
    int y = 0;      // ✅ 明確初始化

    // cout << x << endl;  // 危險！x 的值不確定
    cout << y << endl;     // 安全，輸出 0

    return 0;
}
```

---

### 2.2.4 變數命名規則

**強制規則（違反會編譯錯誤）：**
- 只能使用字母（a-z, A-Z）、數字（0-9）、底線（_）
- **不能以數字開頭**
- **不能使用 C++ 關鍵字**（如 `int`, `for`, `while` 等）
- 區分大小寫：`score` 和 `Score` 是不同的變數

**命名慣例（業界常見風格）：**

| 風格 | 範例 | 適用場合 |
|------|------|----------|
| **camelCase** | `totalScore`, `studentName` | 變數、函式（C++ 常見） |
| **snake_case** | `total_score`, `student_name` | 變數、函式（也很常見） |
| **PascalCase** | `TotalScore`, `StudentName` | 類別名稱 |
| **UPPER_CASE** | `MAX_SIZE`, `PI` | 常數 |

**好的命名 vs. 壞的命名：**

```cpp
// ❌ 壞的命名
int a;
double x1;
string s;

// ✅ 好的命名
int studentAge;
double accountBalance;
string firstName;
```

---

### 2.2.5 常數

常數是**值不可改變的變數**，可防止意外修改重要數值。

#### 使用 `const`（推薦）

```cpp
const double PI = 3.14159265358979;
const int MAX_STUDENTS = 50;
const string SCHOOL_NAME = "國立台灣大學";
```

嘗試修改 `const` 變數會導致編譯錯誤：

```cpp
PI = 3.14;  // ❌ 編譯錯誤：cannot assign to variable with const-qualified type
```

#### 使用 `#define`（舊式，不推薦）

```cpp
#define PI 3.14159
#define MAX 100
```

`#define` 是前置處理指令，僅做文字替換，沒有型別檢查，且不佔記憶體位址。現代 C++ 建議使用 `const` 或 `constexpr`。

#### 使用 `constexpr`（C++11，編譯期常數）

```cpp
constexpr int ARRAY_SIZE = 100;   // 值在編譯期確定
constexpr double GRAVITY = 9.81;
```

**範例檔：`ex2_2_constants.cpp`**

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    const double PI = 3.14159265358979;
    const int RADIUS = 5;

    double area = PI * RADIUS * RADIUS;
    double circumference = 2 * PI * RADIUS;

    cout << "半徑：" << RADIUS << endl;
    cout << "面積：" << area << endl;
    cout << "圓周長：" << circumference << endl;

    return 0;
}
```

**輸出結果：**
```
半徑：5
面積：78.5398
圓周長：31.4159
```

---

### 2.2.6 sizeof 運算子

`sizeof` 可以查詢型別或變數在記憶體中佔用的位元組數。

**範例檔：`ex2_2_sizeof.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "=== 各型別大小 ===" << endl;
    cout << "bool:        " << sizeof(bool)        << " bytes" << endl;
    cout << "char:        " << sizeof(char)        << " bytes" << endl;
    cout << "short:       " << sizeof(short)       << " bytes" << endl;
    cout << "int:         " << sizeof(int)         << " bytes" << endl;
    cout << "long:        " << sizeof(long)        << " bytes" << endl;
    cout << "long long:   " << sizeof(long long)   << " bytes" << endl;
    cout << "float:       " << sizeof(float)       << " bytes" << endl;
    cout << "double:      " << sizeof(double)      << " bytes" << endl;
    cout << "long double: " << sizeof(long double) << " bytes" << endl;

    int x = 42;
    cout << "\n變數 x 的大小：" << sizeof(x) << " bytes" << endl;

    return 0;
}
```

---

### 2.2.7 型別轉換

#### 隱性轉換（Implicit Conversion）

編譯器自動進行，可能造成資料流失：

```cpp
int a = 3;
double b = a;    // ✅ int → double，安全（精度提升）

double x = 3.9;
int y = x;       // ⚠️ double → int，小數部分被截斷（y = 3，非 4！）
```

**型別提升規則（由小到大，自動轉換）：**
```
bool → char → short → int → long → long long → float → double → long double
```

計算時，兩個運算元會**自動提升到較大的型別**：

```cpp
int a = 5;
double b = 2.0;
double result = a + b;  // a 自動提升為 double，結果為 7.0
```

**整數除法陷阱：**

```cpp
int a = 5, b = 2;
double result = a / b;       // ❌ 結果是 2.0，不是 2.5！
                              //    因為 a/b 先做整數除法得 2，再轉 double

double result2 = (double)a / b;  // ✅ 結果是 2.5
```

#### 顯性轉換（Explicit Cast）

**C 風格轉型（不推薦）：**
```cpp
int x = (int)3.9;    // x = 3
```

**C++ 風格轉型（推薦）：**
```cpp
int x = static_cast<int>(3.9);       // x = 3，最常用
double d = static_cast<double>(5) / 2; // d = 2.5
```

**範例檔：`ex2_2_typecast.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    // 整數除法陷阱示範
    int a = 7, b = 2;
    
    cout << "整數除法 7/2 = " << a / b << endl;                    // 3
    cout << "強制轉型後  = " << static_cast<double>(a) / b << endl; // 3.5
    
    // 字元與整數的關係
    char c = 'A';
    cout << "\n字元 'A' 的 ASCII 值：" << static_cast<int>(c) << endl;  // 65
    
    int ascii = 66;
    cout << "ASCII 66 對應的字元：" << static_cast<char>(ascii) << endl; // B
    
    // 截斷小數
    double pi = 3.14159;
    int truncated = static_cast<int>(pi);
    cout << "\nPI 截斷後：" << truncated << endl;  // 3

    return 0;
}
```

---

### 2.2.8 `auto` 型別推導（C++11）

`auto` 讓編譯器自動判斷變數的型別，適合型別名稱很長時使用。

```cpp
auto x = 42;          // int
auto y = 3.14;        // double
auto z = 'A';         // char
auto s = "hello";     // const char*（注意，不是 string！）
auto str = string("hello");  // string
```

---

## 2.3 輸出

### 2.3.1 `cout` 基本輸出

`cout`（**c**haracter **out**put）是 C++ 標準輸出物件，搭配 `<<` 運算子（**串流插入運算子**）使用。

```cpp
cout << 值;           // 輸出值
cout << 值 << endl;   // 輸出值並換行
```

**串接輸出（Chaining）：**

```cpp
cout << "名字：" << "Alice" << "，年齡：" << 20 << endl;
// 等同於
cout << "名字：Alice，年齡：20" << endl;
```

**`endl` vs `"\n"`：**

| 比較 | `endl` | `"\n"` |
|------|--------|--------|
| 換行 | ✅ | ✅ |
| 清空緩衝區（flush） | ✅ | ❌ |
| 速度 | 較慢 | **較快** |
| 建議 | 需要即時輸出時 | 一般情況 |

```cpp
cout << "第一行" << endl;   // 換行 + flush
cout << "第二行" << "\n";  // 只換行，較快
```

**範例檔：`ex2_3_cout.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int age = 21;
    double gpa = 3.85;
    char gender = 'M';
    bool isEnrolled = true;
    string name = "Bob";

    cout << "=== 學生資料 ===" << endl;
    cout << "姓名：" << name << "\n";
    cout << "年齡：" << age << "\n";
    cout << "GPA：" << gpa << "\n";
    cout << "性別：" << gender << "\n";
    cout << "在學：" << isEnrolled << "\n";  // 輸出 1

    // 布林值以文字顯示
    cout << boolalpha;  // 讓 bool 顯示 true/false
    cout << "在學：" << isEnrolled << "\n";  // 輸出 true

    return 0;
}
```

---

### 2.3.2 格式化輸出（iomanip）

`<iomanip>` 標頭檔提供各種格式控制器（Manipulator）。

**範例檔：`ex2_3_iomanip.cpp`**

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double pi = 3.14159265358979;
    int num = 42;

    // ── 小數位數控制 ──────────────────────────────
    cout << "預設輸出：" << pi << endl;                   // 3.14159
    cout << fixed << setprecision(2) << pi << endl;      // 3.14
    cout << fixed << setprecision(5) << pi << endl;      // 3.14159
    cout << scientific << setprecision(3) << pi << endl; // 3.142e+00

    cout << defaultfloat;  // 恢復預設格式

    // ── 欄位寬度與對齊 ────────────────────────────
    cout << "\n=== 成績單 ===" << endl;
    cout << left;  // 靠左對齊（預設為靠右）
    cout << setw(15) << "學生姓名" << setw(8) << "分數" << endl;
    cout << setfill('-') << setw(23) << "" << setfill(' ') << endl;
    cout << setw(15) << "Alice"   << setw(8) << 95 << endl;
    cout << setw(15) << "Bob"     << setw(8) << 87 << endl;
    cout << setw(15) << "Charlie" << setw(8) << 72 << endl;

    // ── 進位制輸出 ────────────────────────────────
    cout << "\n=== 進位制 ===" << endl;
    cout << "十進位：" << dec << num << endl;  // 42
    cout << "十六進位：" << hex << num << endl; // 2a
    cout << "八進位：" << oct << num << endl;   // 52
    cout << dec;  // 恢復十進位

    // ── 補零 ──────────────────────────────────────
    cout << "\n=== 時間格式 ===" << endl;
    int hour = 9, minute = 5, second = 3;
    cout << setfill('0');
    cout << setw(2) << hour   << ":"
         << setw(2) << minute << ":"
         << setw(2) << second << endl;  // 09:05:03

    return 0;
}
```

**常用格式控制器一覽：**

| 控制器 | 效果 | 範例 |
|--------|------|------|
| `setw(n)` | 設定欄位寬度（只影響下一個輸出） | `setw(10)` |
| `setprecision(n)` | 設定有效位數或小數位數 | `setprecision(2)` |
| `fixed` | 搭配 setprecision 固定小數點後位數 | `fixed` |
| `scientific` | 科學記號表示法 | `scientific` |
| `left` / `right` | 靠左 / 靠右對齊 | `left` |
| `setfill(c)` | 設定填充字元（預設空格） | `setfill('0')` |
| `boolalpha` | bool 顯示 true/false | `boolalpha` |
| `hex` / `oct` / `dec` | 十六 / 八 / 十進位 | `hex` |

> ⚠️ `setw()` 的效果**僅作用於緊接的下一個輸出**，其他控制器則持續生效直到更改。

---

### 2.3.3 特殊字元（跳脫字元）

在字串中，反斜線 `\` 開頭的字元有特殊意義：

| 跳脫字元 | 意義 |
|----------|------|
| `\n` | 換行（Newline） |
| `\t` | 水平定位（Tab） |
| `\r` | 歸位（Carriage Return） |
| `\\` | 反斜線本身 |
| `\"` | 雙引號 |
| `\'` | 單引號 |
| `\0` | 空字元（字串結尾） |
| `\a` | 警告音 |

**範例檔：`ex2_3_escape.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "第一行\n第二行" << endl;
    cout << "姓名\t分數\t等級" << endl;
    cout << "Alice\t95\tA" << endl;
    cout << "Bob\t87\tB" << endl;

    cout << "路徑：C:\\Users\\Alice\\Desktop" << endl;
    cout << "他說：\"Hello!\"" << endl;

    return 0;
}
```

**輸出結果：**
```
第一行
第二行
姓名	分數	等級
Alice	95	A
Bob	87	B
路徑：C:\Users\Alice\Desktop
他說："Hello!"
```

---

## 2.4 輸入

### 2.4.1 `cin` 基本輸入

`cin`（**c**haracter **in**put）是 C++ 標準輸入物件，搭配 `>>` 運算子（**串流提取運算子**）使用。

```cpp
cin >> 變數;   // 從鍵盤讀取一個值存入變數
```

**範例檔：`ex2_4_cin_basic.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int age;
    double height;
    string name;

    cout << "請輸入你的名字：";
    cin >> name;

    cout << "請輸入你的年齡：";
    cin >> age;

    cout << "請輸入你的身高（cm）：";
    cin >> height;

    cout << "\n=== 基本資料 ===" << endl;
    cout << "姓名：" << name << endl;
    cout << "年齡：" << age << " 歲" << endl;
    cout << "身高：" << height << " cm" << endl;

    return 0;
}
```

**執行範例：**
```
請輸入你的名字：Alice
請輸入你的年齡：20
請輸入你的身高（cm）：165.5

=== 基本資料 ===
姓名：Alice
年齡：20 歲
身高：165.5 cm
```

---

### 2.4.2 同時讀取多個值

```cpp
int a, b;
cin >> a >> b;    // 以空格或 Enter 分隔兩個整數

double x, y, z;
cin >> x >> y >> z;  // 讀取三個浮點數
```

**範例檔：`ex2_4_multi_input.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int length, width;

    cout << "請輸入矩形的長和寬（空格分隔）：";
    cin >> length >> width;

    int area = length * width;
    int perimeter = 2 * (length + width);

    cout << "面積 = " << area << endl;
    cout << "周長 = " << perimeter << endl;

    return 0;
}
```

---

### 2.4.3 `cin` 的空白問題與 `getline`

`cin >>` 遇到空白（空格、Tab、換行）就**停止讀取**，因此無法讀取含空格的字串。

```cpp
string name;
cin >> name;   // 若輸入 "Alice Wang"，name 只會是 "Alice"
```

**解決方法：使用 `getline()`**

```cpp
string name;
getline(cin, name);   // 讀取整行，包含空格，直到 Enter
```

**範例檔：`ex2_4_getline.cpp`**

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string fullName;
    string address;
    int age;

    cout << "請輸入年齡：";
    cin >> age;
    cin.ignore();   // 清除輸入緩衝區中殘留的換行符號！

    cout << "請輸入全名（含空格）：";
    getline(cin, fullName);

    cout << "請輸入地址：";
    getline(cin, address);

    cout << "\n=== 資料確認 ===" << endl;
    cout << "年齡：" << age << endl;
    cout << "姓名：" << fullName << endl;
    cout << "地址：" << address << endl;

    return 0;
}
```

> ⚠️ **重要陷阱**：`cin >>` 讀取後，輸入緩衝區中會殘留一個換行符號 `\n`。緊接著用 `getline()` 會直接讀到這個空的換行，導致看起來「跳過輸入」。解決方法是在 `cin >>` 後加上 `cin.ignore();` 清除換行。

**`cin.ignore()` 的完整語法：**

```cpp
cin.ignore();                          // 忽略 1 個字元
cin.ignore(1000, '\n');               // 忽略直到換行（最多 1000 個字元）
cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 忽略整行（最安全）
```

---

### 2.4.4 綜合範例：學生成績計算機

**範例檔：`ex2_4_grade_calculator.cpp`**

```cpp
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    string studentName;
    int studentID;
    double math, english, science;

    cout << "╔══════════════════════╗" << endl;
    cout << "║   學生成績計算系統   ║" << endl;
    cout << "╚══════════════════════╝" << endl;

    cout << "\n請輸入學號：";
    cin >> studentID;
    cin.ignore();

    cout << "請輸入學生姓名：";
    getline(cin, studentName);

    cout << "請輸入數學成績：";
    cin >> math;
    cout << "請輸入英文成績：";
    cin >> english;
    cout << "請輸入自然成績：";
    cin >> science;

    double average = (math + english + science) / 3.0;

    char letterGrade;
    if (average >= 90)      letterGrade = 'A';
    else if (average >= 80) letterGrade = 'B';
    else if (average >= 70) letterGrade = 'C';
    else if (average >= 60) letterGrade = 'D';
    else                    letterGrade = 'F';

    cout << fixed << setprecision(1);
    cout << "\n=== 成績報告 ===" << endl;
    cout << "學號：" << studentID << endl;
    cout << "姓名：" << studentName << endl;
    cout << "────────────────" << endl;
    cout << setw(8) << left << "數學" << math << endl;
    cout << setw(8) << left << "英文" << english << endl;
    cout << setw(8) << left << "自然" << science << endl;
    cout << "────────────────" << endl;
    cout << setw(8) << left << "平均" << average << endl;
    cout << setw(8) << left << "等級" << letterGrade << endl;

    return 0;
}
```

---

## 2.5 綜合範例

### 2.5.1 BMI 計算機

**範例檔：`ex2_5_bmi.cpp`**

```cpp
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    string name;
    double weight, height;

    cout << "=== BMI 計算機 ===" << endl;
    cout << "請輸入姓名：";
    cin >> name;
    cout << "請輸入體重（公斤）：";
    cin >> weight;
    cout << "請輸入身高（公分）：";
    cin >> height;

    // 身高換算成公尺
    double heightM = height / 100.0;
    double bmi = weight / (heightM * heightM);

    string category;
    if      (bmi < 18.5) category = "體重過輕";
    else if (bmi < 24.0) category = "正常範圍";
    else if (bmi < 27.0) category = "體重過重";
    else if (bmi < 30.0) category = "輕度肥胖";
    else if (bmi < 35.0) category = "中度肥胖";
    else                 category = "重度肥胖";

    cout << fixed << setprecision(2);
    cout << "\n" << name << " 的 BMI = " << bmi << endl;
    cout << "健康狀態：" << category << endl;

    return 0;
}
```

---

## 📝 實作練習

### 基礎題

#### 練習 2-1：自我介紹程式

**題目：** 撰寫一支程式，輸入使用者的姓名、年齡、科系，並輸出格式化的自我介紹。

**輸入範例：**
```
姓名：陳小明
年齡：19
科系：資訊工程學系
```

**輸出範例：**
```
==========================
大家好，我是 陳小明！
我今年 19 歲
目前就讀 資訊工程學系
很高興認識大家！
==========================
```

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw2_1.cpp`**

```cpp
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
```
</details>

---

#### 練習 2-2：溫度換算器

**題目：** 輸入攝氏溫度，轉換並輸出對應的華氏溫度與克氏溫度。

**轉換公式：**
- 華氏 °F = 攝氏 °C × 9/5 + 32
- 克氏 K = 攝氏 °C + 273.15

**輸入範例：**
```
請輸入攝氏溫度：100
```

**輸出範例：**
```
攝氏：  100.00 °C
華氏：  212.00 °F
克氏：  373.15 K
```

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw2_2.cpp`**

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double celsius;

    cout << "請輸入攝氏溫度：";
    cin >> celsius;

    double fahrenheit = celsius * 9.0 / 5.0 + 32;
    double kelvin = celsius + 273.15;

    cout << fixed << setprecision(2);
    cout << "攝氏：" << setw(8) << celsius    << " °C" << endl;
    cout << "華氏：" << setw(8) << fahrenheit << " °F" << endl;
    cout << "克氏：" << setw(8) << kelvin     << " K"  << endl;

    return 0;
}
```
</details>

---

#### 練習 2-3：矩形計算

**題目：** 輸入矩形的長與寬，計算並輸出面積、周長、對角線長度（保留 2 位小數）。

**對角線公式：** d = √(長² + 寬²)

**輸入範例：**
```
請輸入長（cm）：6
請輸入寬（cm）：8
```

**輸出範例：**
```
面積：48.00 cm²
周長：28.00 cm
對角線：10.00 cm
```

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw2_3.cpp`**

```cpp
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    double length, width;

    cout << "請輸入長（cm）：";
    cin >> length;
    cout << "請輸入寬（cm）：";
    cin >> width;

    double area = length * width;
    double perimeter = 2 * (length + width);
    double diagonal = sqrt(length * length + width * width);

    cout << fixed << setprecision(2);
    cout << "面積：" << area << " cm²" << endl;
    cout << "周長：" << perimeter << " cm" << endl;
    cout << "對角線：" << diagonal << " cm" << endl;

    return 0;
}
```
</details>

---

#### 練習 2-4：時間換算

**題目：** 輸入總秒數，換算成「X 小時 X 分 X 秒」的格式輸出。

**輸入範例：**
```
請輸入秒數：3723
```

**輸出範例：**
```
3723 秒 = 1 小時 2 分 3 秒
```

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw2_4.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int totalSeconds;

    cout << "請輸入秒數：";
    cin >> totalSeconds;

    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    int seconds = totalSeconds % 60;

    cout << totalSeconds << " 秒 = "
         << hours << " 小時 "
         << minutes << " 分 "
         << seconds << " 秒" << endl;

    return 0;
}
```
</details>

---

#### 練習 2-5：商品結帳

**題目：** 輸入商品名稱、單價、數量，計算小計、5% 稅後金額並格式化輸出收據。

**輸入範例：**
```
商品名稱：筆記型電腦
單價：32000
數量：2
```

**輸出範例：**
```
========== 收據 ==========
商品：筆記型電腦
單價：$32000
數量：2
--------------------------
小計：$64000
稅額（5%）：$3200
總計：$67200
==========================
```

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw2_5.cpp`**

```cpp
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    string productName;
    double unitPrice;
    int quantity;

    cout << "商品名稱：";
    cin.ignore();
    getline(cin, productName);
    cout << "單價：";
    cin >> unitPrice;
    cout << "數量：";
    cin >> quantity;

    double subtotal = unitPrice * quantity;
    double tax = subtotal * 0.05;
    double total = subtotal + tax;

    cout << fixed << setprecision(0);
    cout << "========== 收據 ==========" << endl;
    cout << "商品：" << productName << endl;
    cout << "單價：$" << unitPrice << endl;
    cout << "數量：" << quantity << endl;
    cout << "--------------------------" << endl;
    cout << "小計：$" << subtotal << endl;
    cout << "稅額（5%）：$" << tax << endl;
    cout << "總計：$" << total << endl;
    cout << "==========================" << endl;

    return 0;
}
```
</details>

---

### 進階題

#### 練習 2-6：資料型別範圍驗證

**題目：** 撰寫程式，使用 `numeric_limits`（需 `#include <limits>`）顯示 `int`、`long long`、`double` 的最大值、最小值。

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw2_6.cpp`**

```cpp
#include <iostream>
#include <limits>
using namespace std;

int main() {
    cout << "=== 資料型別範圍 ===" << endl;

    cout << "\n[int]" << endl;
    cout << "最小值：" << numeric_limits<int>::min() << endl;
    cout << "最大值：" << numeric_limits<int>::max() << endl;

    cout << "\n[long long]" << endl;
    cout << "最小值：" << numeric_limits<long long>::min() << endl;
    cout << "最大值：" << numeric_limits<long long>::max() << endl;

    cout << "\n[double]" << endl;
    cout << "最小正值：" << numeric_limits<double>::min() << endl;
    cout << "最大值：" << numeric_limits<double>::max() << endl;
    cout << "精確位數：" << numeric_limits<double>::digits10 << endl;

    return 0;
}
```
</details>

---

#### 練習 2-7：成績格式化表格

**題目：** 輸入 3 位學生的姓名與 3 科成績，使用 `iomanip` 輸出格式整齊的成績單，包含每位學生的平均分數。

**輸出格式範例：**
```
╔══════════════════════════════════════╗
║           期中考成績單               ║
╠═══════════╦══════╦══════╦══════╦════╣
║ 姓名      ║ 國文 ║ 數學 ║ 英文 ║ 均 ║
╠═══════════╬══════╬══════╬══════╬════╣
║ 陳小明    ║   85 ║   92 ║   78 ║ 85 ║
║ 王大華    ║   73 ║   88 ║   91 ║ 84 ║
║ 李美玲    ║   96 ║   74 ║   83 ║ 84 ║
╚═══════════╩══════╩══════╩══════╩════╝
```

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw2_7.cpp`**

```cpp
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    const int N = 3;
    string names[N];
    int chinese[N], math[N], english[N];

    for (int i = 0; i < N; i++) {
        cout << "輸入第 " << i+1 << " 位學生姓名：";
        cin >> names[i];
        cout << "國文 數學 英文：";
        cin >> chinese[i] >> math[i] >> english[i];
    }

    cout << "\n╔═══════════╦══════╦══════╦══════╦════╗" << endl;
    cout <<   "║ " << left << setw(9) << "姓名"
         << " ║ " << setw(4) << "國文"
         << " ║ " << setw(4) << "數學"
         << " ║ " << setw(4) << "英文"
         << " ║ " << setw(2) << "均" << " ║" << endl;
    cout << "╠═══════════╬══════╬══════╬══════╬════╣" << endl;

    for (int i = 0; i < N; i++) {
        double avg = (chinese[i] + math[i] + english[i]) / 3.0;
        cout << "║ " << left << setw(9) << names[i]
             << " ║ " << right << setw(4) << chinese[i]
             << " ║ " << setw(4) << math[i]
             << " ║ " << setw(4) << english[i]
             << " ║ " << setw(2) << static_cast<int>(avg) << " ║" << endl;
    }

    cout << "╚═══════════╩══════╩══════╩══════╩════╝" << endl;

    return 0;
}
```
</details>

---

#### 練習 2-8：匯率換算機

**題目：** 輸入台幣金額，同時換算成美元（÷30）、日圓（×4.5）、歐元（÷33）。所有結果保留 2 位小數。

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw2_8.cpp`**

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    const double TWD_TO_USD = 1.0 / 30.0;
    const double TWD_TO_JPY = 4.5;
    const double TWD_TO_EUR = 1.0 / 33.0;

    double twd;
    cout << "請輸入台幣金額：NT$";
    cin >> twd;

    cout << fixed << setprecision(2);
    cout << "\n=== 匯率換算結果 ===" << endl;
    cout << "台幣：NT$ " << twd << endl;
    cout << "美元：USD " << twd * TWD_TO_USD << endl;
    cout << "日圓：JPY " << twd * TWD_TO_JPY << endl;
    cout << "歐元：EUR " << twd * TWD_TO_EUR << endl;

    return 0;
}
```
</details>

---

#### 練習 2-9：圓柱體積與表面積

**題目：** 輸入圓柱的底面半徑和高，計算體積與表面積。

**公式：**
- 體積 V = π × r² × h
- 表面積 S = 2πr² + 2πrh

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw2_9.cpp`**

```cpp
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    const double PI = acos(-1.0);  // 利用 acos(-1) 得到精確的 PI
    double r, h;

    cout << "請輸入底面半徑：";
    cin >> r;
    cout << "請輸入圓柱高度：";
    cin >> h;

    double volume = PI * r * r * h;
    double surface = 2 * PI * r * r + 2 * PI * r * h;

    cout << fixed << setprecision(4);
    cout << "體積 = " << volume << endl;
    cout << "表面積 = " << surface << endl;

    return 0;
}
```
</details>

---

#### 練習 2-10：個人資料卡

**題目：** 建立一張格式化的個人資料卡，包含姓名（含空格）、身分證字號、生日、電話、地址。使用 `getline` 讀取各欄位，並以固定框線格式輸出。

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw2_10.cpp`**

```cpp
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    string name, idNumber, birthday, phone, address;

    cout << "=== 個人資料填寫 ===" << endl;
    cout << "姓名：";        getline(cin, name);
    cout << "身分證字號：";  getline(cin, idNumber);
    cout << "生日（yyyy/mm/dd）："; getline(cin, birthday);
    cout << "電話：";        getline(cin, phone);
    cout << "地址：";        getline(cin, address);

    string line(40, '=');
    cout << "\n" << line << endl;
    cout << "║" << setw(38) << left << "          個人資料卡" << "║" << endl;
    cout << line << endl;
    cout << "║ " << left << setw(10) << "姓名"     << "│ " << setw(24) << name      << "║" << endl;
    cout << "║ " << setw(10) << "身分證字號" << "│ " << setw(24) << idNumber << "║" << endl;
    cout << "║ " << setw(10) << "生日"     << "│ " << setw(24) << birthday  << "║" << endl;
    cout << "║ " << setw(10) << "電話"     << "│ " << setw(24) << phone     << "║" << endl;
    cout << "║ " << setw(10) << "地址"     << "│ " << setw(24) << address   << "║" << endl;
    cout << line << endl;

    return 0;
}
```
</details>

---

## 💼 面試考題

### 觀念題

**Q1. `int`、`float`、`double` 的差異為何？什麼情況下選哪個？**

> **參考答案：**
> - `int`：整數，無法表示小數，4 bytes
> - `float`：單精度浮點數，約 7 位有效數字，4 bytes
> - `double`：雙精度浮點數，約 15 位有效數字，8 bytes
>
> 選擇原則：需要整數用 `int`；需要浮點數預設用 `double`；嵌入式系統記憶體受限時才考慮 `float`。

---

**Q2. 以下程式的輸出為何？解釋原因。**

```cpp
int a = 5, b = 2;
cout << a / b << endl;        // (A)
cout << a / 2.0 << endl;      // (B)
cout << (double)a / b << endl; // (C)
```

> **參考答案：**
> - (A) 輸出 `2`：兩個 `int` 相除執行整數除法，結果為 2（商），小數部分直接丟棄
> - (B) 輸出 `2.5`：`b=2` 被隱性轉換成 `double`，執行浮點除法
> - (C) 輸出 `2.5`：`a` 被顯性轉換成 `double`，執行浮點除法

---

**Q3. `const` 與 `#define` 的差異？**

> **參考答案：**
>
> | 比較 | `const` | `#define` |
> |------|---------|-----------|
> | 型別檢查 | ✅ 有 | ❌ 無 |
> | 記憶體位址 | ✅ 有 | ❌ 無（純文字替換） |
> | 偵錯器可見 | ✅ 可見 | ❌ 不可見 |
> | 作用域 | ✅ 尊重作用域 | ❌ 全域 |
> | 推薦 | ✅ 現代 C++ 推薦 | 不推薦（舊式寫法） |

---

**Q4. 以下程式有什麼問題？**

```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    int age;
    string name;
    cin >> age;
    getline(cin, name);
    cout << name << endl;
}
```

> **參考答案：**
> `cin >> age` 讀取整數後，輸入緩衝區中殘留換行符號 `\n`。緊接著的 `getline(cin, name)` 直接讀到這個 `\n`，因此 `name` 會是空字串。
>
> 修正方法：在 `cin >> age` 後加上 `cin.ignore();` 或 `cin.ignore(1000, '\n');`。

---

**Q5. `endl` 和 `"\n"` 有何不同？在效能敏感的場景中，應選哪個？**

> **參考答案：**
> `endl` 除了輸出換行符號外，還會呼叫 `flush()` 強制清空輸出緩衝區，這個操作有 I/O 開銷。`"\n"` 只輸出換行，不 flush。
>
> 在需要大量輸出的場景（如競程、大資料處理），應使用 `"\n"` 以避免頻繁 flush 導致效能瓶頸。只有在需要即時顯示輸出時才用 `endl`。

---

**Q6. 解釋「未定義行為（Undefined Behavior）」，並舉例。**

> **參考答案：**
> 未定義行為（UB）是指 C++ 標準未規定某操作的結果，編譯器可以做任何事（產生任何輸出、崩潰、甚至看起來「正常運作」）。
>
> 常見例子：
> - 使用未初始化的局部變數
> - 有號整數溢位（`int` 超過 2,147,483,647 後再加 1）
> - 陣列越界存取
> - 空指標解參考

---

**Q7. C++ 中 `auto` 關鍵字的用途？**

> **參考答案：**
> `auto` 讓編譯器根據初始值自動推導變數型別，減少冗長的型別書寫（特別是 STL 的疊代器型別）。
>
> 例如：`auto it = myVector.begin();` 比 `vector<int>::iterator it = myVector.begin();` 簡潔許多。
> 注意：`auto` 必須在宣告時初始化，且推導出的型別在編譯期固定，不是動態型別。

---

**Q8. 以下宣告各別佔用多少記憶體（64 位元系統）？**

```cpp
char a;
int b;
double c;
bool d;
long long e;
```

> **參考答案：**
> - `char a`：1 byte
> - `int b`：4 bytes
> - `double c`：8 bytes
> - `bool d`：1 byte
> - `long long e`：8 bytes

---

## 🚀 專案：個人財務管理系統 v1.0

### 專案說明

建立一個簡易的個人財務管理程式，使用者可以輸入本月的各項收入與支出，程式自動計算剩餘金額並給出理財建議。

### 功能需求

1. 輸入使用者姓名與月份
2. 輸入以下收入項目：
   - 薪資
   - 兼職收入
   - 其他收入
3. 輸入以下支出項目：
   - 房租
   - 飲食費
   - 交通費
   - 娛樂費
   - 其他支出
4. 計算：總收入、總支出、結餘、儲蓄率
5. 根據儲蓄率給出建議：
   - ≥ 30%：優秀，繼續保持！
   - 20~30%：良好，可以更好
   - 10~20%：普通，建議減少非必要支出
   - < 10%：警告，財務狀況需要注意！
6. 以格式化表格輸出報表

### 輸出範例

```
╔══════════════════════════════════╗
║       個人財務月報表             ║
║  姓名：王小明   2024年 3月       ║
╠══════════════════════════════════╣
║ 【收入明細】                     ║
║   薪資收入：       $ 45,000      ║
║   兼職收入：       $  5,000      ║
║   其他收入：       $  1,000      ║
║   ──────────────────────────     ║
║   總收入：         $ 51,000      ║
╠══════════════════════════════════╣
║ 【支出明細】                     ║
║   房租：           $ 12,000      ║
║   飲食費：         $  8,000      ║
║   交通費：         $  2,500      ║
║   娛樂費：         $  3,000      ║
║   其他支出：       $  1,500      ║
║   ──────────────────────────     ║
║   總支出：         $ 27,000      ║
╠══════════════════════════════════╣
║ 【財務摘要】                     ║
║   結餘：           $ 24,000      ║
║   儲蓄率：              47.06%   ║
║   評級：優秀，繼續保持！         ║
╚══════════════════════════════════╝
```

<details>
<summary>✅ 完整參考答案（點擊展開）</summary>

**檔名：`project2_finance.cpp`**

```cpp
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// 格式化輸出一行金額資料
void printRow(const string& label, double amount, int width = 32) {
    cout << "║   " << left << setw(12) << label
         << "$ " << right << setw(9) << fixed << setprecision(0) << amount
         << setw(width - 26) << "║" << endl;
}

int main() {
    string name;
    int month;

    cout << "╔══════════════════════════════════╗" << endl;
    cout << "║       個人財務管理系統            ║" << endl;
    cout << "╚══════════════════════════════════╝" << endl;

    cout << "\n請輸入姓名：";
    cin >> name;
    cout << "請輸入月份（1-12）：";
    cin >> month;

    // 收入輸入
    double salary, partTime, otherIncome;
    cout << "\n【請輸入收入】" << endl;
    cout << "薪資收入：$";     cin >> salary;
    cout << "兼職收入：$";     cin >> partTime;
    cout << "其他收入：$";     cin >> otherIncome;

    double totalIncome = salary + partTime + otherIncome;

    // 支出輸入
    double rent, food, transport, entertainment, otherExpense;
    cout << "\n【請輸入支出】" << endl;
    cout << "房租：$";     cin >> rent;
    cout << "飲食費：$";   cin >> food;
    cout << "交通費：$";   cin >> transport;
    cout << "娛樂費：$";   cin >> entertainment;
    cout << "其他支出：$"; cin >> otherExpense;

    double totalExpense = rent + food + transport + entertainment + otherExpense;
    double balance = totalIncome - totalExpense;
    double savingRate = (totalIncome > 0) ? (balance / totalIncome * 100) : 0;

    string advice;
    if      (savingRate >= 30) advice = "優秀，繼續保持！";
    else if (savingRate >= 20) advice = "良好，可以更好";
    else if (savingRate >= 10) advice = "普通，建議減少非必要支出";
    else                       advice = "警告，財務狀況需要注意！";

    // 輸出報表
    cout << "\n╔══════════════════════════════════╗" << endl;
    cout << "║       個人財務月報表             ║" << endl;
    cout << "║  姓名：" << left << setw(6) << name
         << "  " << setw(4) << "2024年" << setw(2) << month << "月"
         << setw(4) << "" << "║" << endl;
    cout << "╠══════════════════════════════════╣" << endl;
    cout << "║ 【收入明細】                     ║" << endl;
    printRow("薪資收入：", salary);
    printRow("兼職收入：", partTime);
    printRow("其他收入：", otherIncome);
    cout << "║   ──────────────────────────     ║" << endl;
    printRow("總收入：", totalIncome);
    cout << "╠══════════════════════════════════╣" << endl;
    cout << "║ 【支出明細】                     ║" << endl;
    printRow("房租：", rent);
    printRow("飲食費：", food);
    printRow("交通費：", transport);
    printRow("娛樂費：", entertainment);
    printRow("其他支出：", otherExpense);
    cout << "║   ──────────────────────────     ║" << endl;
    printRow("總支出：", totalExpense);
    cout << "╠══════════════════════════════════╣" << endl;
    cout << "║ 【財務摘要】                     ║" << endl;
    printRow("結餘：", balance);
    cout << fixed << setprecision(2);
    cout << "║   " << left << setw(12) << "儲蓄率："
         << right << setw(11) << savingRate << "%" << setw(7) << "║" << endl;
    cout << "║   評級：" << left << setw(22) << advice << "║" << endl;
    cout << "╚══════════════════════════════════╝" << endl;

    return 0;
}
```
</details>

---

## 🔑 章節重點整理

```
┌─────────────────────────────────────────────────────┐
│                  第二章重點摘要                      │
├─────────────────────────────────────────────────────┤
│ 程式骨架                                            │
│  • #include 引入標頭檔                              │
│  • using namespace std; 省略 std:: 前綴             │
│  • int main() 是程式唯一入口                        │
│  • return 0 代表正常結束                            │
├─────────────────────────────────────────────────────┤
│ 變數                                                │
│  • 宣告時務必初始化，避免垃圾值                     │
│  • 整數優先用 int，浮點數優先用 double              │
│  • 常數使用 const，避免意外修改                     │
│  • 整數除法會截斷小數，需注意型別                   │
├─────────────────────────────────────────────────────┤
│ 輸出                                                │
│  • cout << 值 << endl; 基本輸出                     │
│  • fixed << setprecision(n) 控制小數位數            │
│  • setw(n) 僅影響下一個輸出，其餘持續生效           │
├─────────────────────────────────────────────────────┤
│ 輸入                                                │
│  • cin >> 以空白分隔，無法讀含空格字串              │
│  • getline() 讀取整行含空格                         │
│  • cin >> 後接 getline() 須先 cin.ignore()          │
└─────────────────────────────────────────────────────┘
```

---

*教材版本：v1.0 | 適用對象：大學程式設計初學者 | 建議學習時間：6-8 小時*
