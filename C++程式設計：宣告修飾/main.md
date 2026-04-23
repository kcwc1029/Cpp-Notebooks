# 第 13 章 宣告修飾

> **本章目標**
>
> 學完本章後，你應該能夠：
>
> - 看懂 `short`、`long`、`long long` 如何影響整數大小與範圍。
> - 分辨 `signed` 與 `unsigned` 的語意、風險與適用時機。
> - 使用 C++11 的固定寬度整數型別，例如 `int32_t`、`uint64_t`。
> - 正確使用 `const` 宣告常數，理解常數與變數的差異。
> - 理解 `static` 在區域變數、全域變數、函式、類別成員中的意義。
> - 使用 `auto` 讓編譯器推導型別，同時避免濫用造成程式難讀。
> - 面對面試常見題時，能說清楚「型別、範圍、生命週期、連結性、可讀性」這幾個核心觀念。

---

## 13.0 為什麼需要宣告修飾？

前面章節你已經學過變數宣告：

```cpp
int age = 20;
double height = 1.75;
char grade = 'A';
bool passed = true;
```

但真實工程裡，只知道「這是一個整數」常常不夠。

例如：

```cpp
int money = 3000000000;     // 這可能放不下
int count = -1;             // 這個 count 真的可以是負數嗎？
double PI = 3.14159;        // 這個值應該被修改嗎？
int id = getUserId();       // 這個 id 的型別能否由編譯器推導？
```

這些問題都與「宣告修飾」有關。

宣告修飾符可以改變型別或變數的特性。常見包含：

| 類別 | 修飾符或語法 | 主要目的 |
|---|---|---|
| 大小修飾 | `short`、`long`、`long long` | 改變整數可表示範圍 |
| 符號修飾 | `signed`、`unsigned` | 決定能不能表示負數 |
| 固定寬度型別 | `int32_t`、`uint64_t` | 明確指定整數位元數 |
| 常數修飾 | `const`、`constexpr` | 防止值被修改，表達不可變語意 |
| 儲存期與連結性 | `static` | 讓變數長期存在，或限制名稱可見範圍 |
| 型別推導 | `auto` | 讓編譯器根據初始化值推導型別 |

> 工程師看宣告，不只是看「這個變數叫什麼」，更是在看作者對資料範圍、生命週期、可修改性與設計意圖的承諾。

---

## 13.1 修飾大小

### 13.1.1 整數大小與範圍

C++ 的整數型別有不同大小。大小通常用 byte 計算，1 byte 通常等於 8 bit。

常見整數型別：

```cpp
short s;
int i;
long l;
long long ll;
```

這些型別的實際大小會受到平台影響。C++ 標準只保證它們的相對大小至少滿足：

```text
sizeof(short) <= sizeof(int) <= sizeof(long) <= sizeof(long long)
```

常見 64-bit Windows 編譯器上：

| 型別 | 常見大小 | signed 範圍約略 |
|---|---:|---:|
| `short` | 2 bytes | -32,768 到 32,767 |
| `int` | 4 bytes | 約 -21 億到 21 億 |
| `long` | 4 bytes | 約 -21 億到 21 億 |
| `long long` | 8 bytes | 約 -9e18 到 9e18 |

常見 64-bit Linux/macOS 編譯器上：

| 型別 | 常見大小 |
|---|---:|
| `short` | 2 bytes |
| `int` | 4 bytes |
| `long` | 8 bytes |
| `long long` | 8 bytes |

所以工程上不要假設 `long` 一定是 8 bytes。如果需要精準寬度，請看 13.3 的 C++11 固定寬度整數。

### 範例檔案：`ex13_1_1_sizeof_integer.cpp`

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "sizeof(short)     = " << sizeof(short) << " bytes\n";
    cout << "sizeof(int)       = " << sizeof(int) << " bytes\n";
    cout << "sizeof(long)      = " << sizeof(long) << " bytes\n";
    cout << "sizeof(long long) = " << sizeof(long long) << " bytes\n";

    return 0;
}
```

可能輸出：

```text
sizeof(short)     = 2 bytes
sizeof(int)       = 4 bytes
sizeof(long)      = 4 bytes
sizeof(long long) = 8 bytes
```

### 13.1.2 `short`

`short` 通常用於想節省空間的小整數，例如年齡、月份、狀態碼。但對初學者來說，不必為了省幾個 byte 到處使用 `short`。

```cpp
short age = 20;
short year = 2026;
```

風險是範圍太小：

```cpp
short score = 40000; // 可能超出 short 範圍
```

如果值超出範圍，結果可能不是你期待的數字。

### 範例檔案：`ex13_1_2_short_overflow.cpp`

```cpp
#include <iostream>
using namespace std;

int main() {
    short x = 32767;
    cout << "x     = " << x << '\n';

    x = x + 1;
    cout << "x + 1 = " << x << '\n';

    return 0;
}
```

這個程式用來觀察超出範圍的現象。不同編譯器或設定下行為可能不同，不應依賴這種結果。

### 13.1.3 `long` 與 `long long`

當 `int` 放不下時，常用 `long long`。

```cpp
long long population = 23500000000LL;
long long distance = 9876543210LL;
```

整數字面值後面的 `LL` 表示這是一個 `long long` literal。

```cpp
long long a = 1000000000 * 1000000000;     // 錯誤風險：乘法可能先用 int 算
long long b = 1000000000LL * 1000000000LL; // 較安全：用 long long 算
```

重點：不是左邊宣告成 `long long` 就保證右邊運算過程安全。右邊表達式本身也要使用足夠大的型別。

### 範例檔案：`ex13_1_3_long_long_literal.cpp`

```cpp
#include <iostream>
using namespace std;

int main() {
    long long wrong = 1000000000 * 1000000000;
    long long right = 1000000000LL * 1000000000LL;

    cout << "wrong = " << wrong << '\n';
    cout << "right = " << right << '\n';

    return 0;
}
```

### 13.1.4 浮點數也有大小差異

除了整數，浮點數也有不同大小：

```cpp
float f = 3.14f;
double d = 3.14;
long double ld = 3.14L;
```

常見比較：

| 型別 | 常見大小 | 精度概念 |
|---|---:|---|
| `float` | 4 bytes | 約 6 到 7 位有效數字 |
| `double` | 8 bytes | 約 15 到 16 位有效數字 |
| `long double` | 8、12 或 16 bytes | 依平台而定 |

一般程式設計預設使用 `double`。除非你有大量資料、GPU、遊戲或記憶體壓力，否則不用急著用 `float`。

### 範例檔案：`ex13_1_4_float_double_precision.cpp`

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    float f = 1.0f / 3.0f;
    double d = 1.0 / 3.0;
    long double ld = 1.0L / 3.0L;

    cout << fixed << setprecision(20);
    cout << "float       = " << f << '\n';
    cout << "double      = " << d << '\n';
    cout << "long double = " << ld << '\n';

    return 0;
}
```

---

## 13.2 有號及無號

### 13.2.1 `signed` 與 `unsigned`

整數預設通常是 `signed`，可以表示負數、零、正數。

```cpp
int a = -10;        // signed int 的簡寫
signed int b = -20;
```

`unsigned` 只能表示零和正數，但正數範圍會比同大小的 signed 型別大。

```cpp
unsigned int count = 100;
unsigned int score = 0;
```

以 4 bytes 為例：

| 型別 | 約略範圍 |
|---|---:|
| `int` | -2,147,483,648 到 2,147,483,647 |
| `unsigned int` | 0 到 4,294,967,295 |

### 13.2.2 無號整數的迴繞

`unsigned` 遇到低於 0 的情況，通常會迴繞到最大值附近。

### 範例檔案：`ex13_2_1_unsigned_wrap.cpp`

```cpp
#include <iostream>
using namespace std;

int main() {
    unsigned int x = 0;

    cout << "x     = " << x << '\n';
    cout << "x - 1 = " << x - 1 << '\n';

    return 0;
}
```

可能輸出：

```text
x     = 0
x - 1 = 4294967295
```

這不是 bug，而是 unsigned arithmetic 的規則。但對初學者而言，這非常容易造成 bug。

### 13.2.3 signed 與 unsigned 混用的陷阱

當 signed 與 unsigned 一起比較或運算時，C++ 可能把 signed 轉成 unsigned，造成直覺以外的結果。

### 範例檔案：`ex13_2_2_signed_unsigned_compare.cpp`

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = -1;
    unsigned int b = 1;

    if (a < b) {
        cout << "-1 < 1\n";
    } else {
        cout << "Surprise: -1 is not less than 1 here\n";
    }

    return 0;
}
```

許多編譯器會輸出：

```text
Surprise: -1 is not less than 1 here
```

原因是 `a` 被轉成很大的 unsigned 值。

### 13.2.4 `size_t`

`size_t` 是 C++ 標準函式庫常用來表示「大小」或「索引」的無號整數型別。

```cpp
#include <string>

string name = "Alice";
size_t len = name.size();
```

`size_t` 很常見，但使用時要注意：

```cpp
for (size_t i = len - 1; i >= 0; i--) { // 危險
    // ...
}
```

因為 `size_t` 是 unsigned，`i >= 0` 永遠成立，當 `i` 從 0 再減 1 會迴繞成巨大數字。

### 範例檔案：`ex13_2_3_size_t_reverse_loop.cpp`

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "abcd";

    // 寫法一：使用 int，簡單直覺，適合初學階段
    for (int i = static_cast<int>(s.size()) - 1; i >= 0; i--) {
        cout << s[i] << ' ';
    }
    cout << '\n';

    // 寫法二：使用 size_t 的安全倒數寫法
    for (size_t i = s.size(); i > 0; i--) {
        cout << s[i - 1] << ' ';
    }
    cout << '\n';

    return 0;
}
```

### 13.2.5 什麼時候該用 unsigned？

建議：

| 情境 | 建議 |
|---|---|
| 一般計數、分數、金額、差值 | 多數情況使用 `int` 或 `long long` |
| 位元操作、遮罩、二進位資料 | 適合使用 `unsigned` 或 `uint32_t` |
| 容器大小、標準函式庫回傳大小 | 常會遇到 `size_t` |
| 需要保證不為負 | 不要只靠 unsigned，仍要做輸入驗證 |

`unsigned` 不等於「更安全的非負整數」。它更像是「以二進位位元模式為主的整數」。

---

## 13.3 C++11 標準類別

本節的「標準類別」主要指 C++11 之後常用的標準整數型別與相關工具，尤其是 `<cstdint>` 提供的固定寬度整數。

### 13.3.1 為什麼需要固定寬度整數？

如果你在寫：

- 檔案格式
- 網路封包
- 加密或雜湊
- 遊戲存檔
- 跨平台資料交換
- 嵌入式系統

你常常不能只寫 `int`，因為不同平台上 `int` 雖然通常是 4 bytes，但標準不把它寫死。

C++11 提供 `<cstdint>`：

```cpp
#include <cstdint>
```

常見型別：

| 型別 | 意義 |
|---|---|
| `int8_t` | 8-bit signed integer |
| `uint8_t` | 8-bit unsigned integer |
| `int16_t` | 16-bit signed integer |
| `uint16_t` | 16-bit unsigned integer |
| `int32_t` | 32-bit signed integer |
| `uint32_t` | 32-bit unsigned integer |
| `int64_t` | 64-bit signed integer |
| `uint64_t` | 64-bit unsigned integer |

### 範例檔案：`ex13_3_1_fixed_width.cpp`

```cpp
#include <iostream>
#include <cstdint>
using namespace std;

int main() {
    int32_t score = 100;
    uint32_t flags = 0b00001111;
    int64_t big = 9000000000000000000LL;

    cout << "score = " << score << '\n';
    cout << "flags = " << flags << '\n';
    cout << "big   = " << big << '\n';

    cout << "sizeof(int32_t)  = " << sizeof(int32_t) << '\n';
    cout << "sizeof(uint32_t) = " << sizeof(uint32_t) << '\n';
    cout << "sizeof(int64_t)  = " << sizeof(int64_t) << '\n';

    return 0;
}
```

### 13.3.2 `int8_t` 與 `uint8_t` 的輸出陷阱

`int8_t` 和 `uint8_t` 很可能其實是 `signed char` 或 `unsigned char` 的別名。直接用 `cout` 印時，可能被當成字元輸出。

### 範例檔案：`ex13_3_2_int8_t_output.cpp`

```cpp
#include <iostream>
#include <cstdint>
using namespace std;

int main() {
    uint8_t x = 65;

    cout << "直接輸出 x: " << x << '\n';
    cout << "轉成 int: " << static_cast<int>(x) << '\n';

    return 0;
}
```

可能輸出：

```text
直接輸出 x: A
轉成 int: 65
```

### 13.3.3 最大值與最小值

可以用 `<limits>` 查詢型別範圍。

### 範例檔案：`ex13_3_3_numeric_limits.cpp`

```cpp
#include <iostream>
#include <limits>
#include <cstdint>
using namespace std;

int main() {
    cout << "int min      = " << numeric_limits<int>::min() << '\n';
    cout << "int max      = " << numeric_limits<int>::max() << '\n';
    cout << "uint32_t max = " << numeric_limits<uint32_t>::max() << '\n';
    cout << "int64_t max  = " << numeric_limits<int64_t>::max() << '\n';

    return 0;
}
```

### 13.3.4 常見標準型別選擇

| 需求 | 建議型別 |
|---|---|
| 一般整數運算 | `int` |
| 可能超過 21 億 | `long long` 或 `int64_t` |
| 明確 32-bit 檔案欄位 | `int32_t` / `uint32_t` |
| 明確 64-bit ID 或時間戳 | `int64_t` / `uint64_t` |
| 容器大小 | `size_t` |
| 指標差距 | `ptrdiff_t` |

`size_t` 與 `ptrdiff_t` 的差別：

```cpp
size_t n = 10;       // 大小，不應是負數
ptrdiff_t diff = -3; // 兩個位置相減，可能是負數
```

### 範例檔案：`ex13_3_4_size_t_ptrdiff_t.cpp`

```cpp
#include <iostream>
#include <cstddef>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};

    int* first = &arr[1];
    int* second = &arr[4];

    ptrdiff_t distance = second - first;
    size_t count = sizeof(arr) / sizeof(arr[0]);

    cout << "count    = " << count << '\n';
    cout << "distance = " << distance << '\n';

    return 0;
}
```

---

## 13.4 常數

### 13.4.1 為什麼要用常數？

如果一個值不應該被修改，就應該在宣告時寫出來。

```cpp
const double PI = 3.141592653589793;
const int MAX_STUDENTS = 50;
```

好處：

- 讓讀程式的人知道這個值不能改。
- 編譯器可以幫你抓錯。
- 避免魔法數字散落各處。
- 讓程式更容易維護。

壞例子：

```cpp
double area = 3.14159 * r * r;
double circumference = 2 * 3.14159 * r;
```

好例子：

```cpp
const double PI = 3.141592653589793;
double area = PI * r * r;
double circumference = 2 * PI * r;
```

### 範例檔案：`ex13_4_1_const_basic.cpp`

```cpp
#include <iostream>
using namespace std;

int main() {
    const double PI = 3.141592653589793;

    double r;
    cout << "請輸入半徑: ";
    cin >> r;

    cout << "面積 = " << PI * r * r << '\n';
    cout << "周長 = " << 2 * PI * r << '\n';

    // PI = 3.14; // 編譯錯誤：const 不能修改

    return 0;
}
```

### 13.4.2 `const` 與初始化

`const` 變數宣告時必須初始化。

```cpp
const int x = 10; // OK
const int y;      // 錯誤：沒有初始化
```

原因很簡單：既然它之後不能被修改，那一開始就必須給值。

### 13.4.3 `const` 參數

函式參數也可以用 `const` 表示不會被修改。

```cpp
void printScore(const int score) {
    cout << score << '\n';
    // score = 0; // 編譯錯誤
}
```

對基本型別來說，`const int score` 的好處有限，因為本來就是傳值。但對參考與指標非常重要。

```cpp
void printName(const string& name) {
    cout << name << '\n';
}
```

`const string&` 表示：

- 不複製整個字串，效率較好。
- 函式承諾不修改 `name`。

### 範例檔案：`ex13_4_2_const_reference.cpp`

```cpp
#include <iostream>
#include <string>
using namespace std;

void printProfile(const string& name, const int age) {
    cout << "姓名: " << name << '\n';
    cout << "年齡: " << age << '\n';

    // name += "!"; // 編譯錯誤
    // age = 0;     // 編譯錯誤
}

int main() {
    string name = "Alice";
    int age = 20;

    printProfile(name, age);

    return 0;
}
```

### 13.4.4 指標與 const

這是 C/C++ 面試非常常考的內容。

```cpp
const int* p1;       // 指向 const int 的指標：不能透過 p1 修改值
int* const p2 = &x;  // const 指標：p2 不能改指向，但可以改值
const int* const p3; // 指標本身與指向的值都不能改
```

讀法技巧：從變數名開始，往右讀，讀不下去再往左。

| 宣告 | 指標能改指向嗎？ | 能透過指標改值嗎？ |
|---|---:|---:|
| `int* p` | 可以 | 可以 |
| `const int* p` | 可以 | 不可以 |
| `int* const p` | 不可以 | 可以 |
| `const int* const p` | 不可以 | 不可以 |

### 範例檔案：`ex13_4_3_const_pointer.cpp`

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10;
    int b = 20;

    const int* p1 = &a;
    p1 = &b;       // OK：可以改指向
    // *p1 = 30;   // 錯誤：不能透過 p1 改值

    int* const p2 = &a;
    *p2 = 30;      // OK：可以改 a 的值
    // p2 = &b;    // 錯誤：p2 不能改指向

    const int* const p3 = &a;
    // p3 = &b;    // 錯誤
    // *p3 = 40;   // 錯誤

    cout << "a = " << a << '\n';
    cout << "b = " << b << '\n';

    return 0;
}
```

### 13.4.5 `constexpr`

`const` 表示「不能修改」。`constexpr` 表示「能在編譯期算出來的常數」。

```cpp
constexpr int MAX_SIZE = 100;
constexpr double PI = 3.141592653589793;
```

`constexpr` 常用在陣列大小、模板、編譯期計算等情境。

### 範例檔案：`ex13_4_4_constexpr.cpp`

```cpp
#include <iostream>
using namespace std;

constexpr int square(int x) {
    return x * x;
}

int main() {
    constexpr int N = square(10);
    int arr[N] = {};

    cout << "N = " << N << '\n';
    cout << "array size = " << sizeof(arr) / sizeof(arr[0]) << '\n';

    return 0;
}
```

### 13.4.6 `#define`、`const`、`constexpr`

舊式 C 程式常用：

```cpp
#define PI 3.14159
```

現代 C++ 優先使用：

```cpp
constexpr double PI = 3.14159;
```

比較：

| 寫法 | 型別安全 | 作用域 | 建議 |
|---|---:|---:|---|
| `#define` | 差 | 沒有一般 C++ 作用域概念 | 少用 |
| `const` | 好 | 有 | 常用 |
| `constexpr` | 好 | 有 | 編譯期常數優先使用 |

---

## 13.5 靜態宣告

`static` 是 C++ 裡意義很多的關鍵字。它的意思會依照出現位置不同而不同。

先記大方向：

- 區域變數加 `static`：變數只初始化一次，生命週期延長到程式結束。
- 全域變數或函式加 `static`：限制只能在目前檔案使用。
- 類別成員加 `static`：屬於整個類別，不屬於某一個物件。

### 13.5.1 區域 static 變數

普通區域變數每次進入函式都會重新建立。

```cpp
void countNormal() {
    int count = 0;
    count++;
    cout << count << '\n';
}
```

每次呼叫都輸出 `1`。

`static` 區域變數只初始化一次，下一次呼叫會保留上次的值。

### 範例檔案：`ex13_5_1_static_local.cpp`

```cpp
#include <iostream>
using namespace std;

void countNormal() {
    int count = 0;
    count++;
    cout << "normal count = " << count << '\n';
}

void countStatic() {
    static int count = 0;
    count++;
    cout << "static count = " << count << '\n';
}

int main() {
    for (int i = 0; i < 3; i++) {
        countNormal();
    }

    cout << "---\n";

    for (int i = 0; i < 3; i++) {
        countStatic();
    }

    return 0;
}
```

輸出：

```text
normal count = 1
normal count = 1
normal count = 1
---
static count = 1
static count = 2
static count = 3
```

### 13.5.2 static 區域變數的生命週期

普通區域變數：

- 作用域：函式內。
- 生命週期：函式呼叫期間。

static 區域變數：

- 作用域：函式內。
- 生命週期：整個程式執行期間。

也就是說，外面不能直接存取它，但它的資料會一直留著。

### 範例檔案：`ex13_5_2_id_generator.cpp`

```cpp
#include <iostream>
using namespace std;

int nextId() {
    static int id = 1000;
    id++;
    return id;
}

int main() {
    cout << nextId() << '\n';
    cout << nextId() << '\n';
    cout << nextId() << '\n';

    return 0;
}
```

### 13.5.3 全域 static：限制檔案可見性

在全域變數或全域函式前加 `static`，代表這個名稱只在目前 `.cpp` 檔案內可見。

```cpp
static int counter = 0;

static void helper() {
    counter++;
}
```

這可以避免不同檔案之間的名稱衝突。

不過現代 C++ 更常用匿名 namespace 達成類似目的：

```cpp
namespace {
    int counter = 0;

    void helper() {
        counter++;
    }
}
```

初學階段只要知道：全域 `static` 會把名稱藏在目前檔案內。

### 13.5.4 類別中的 static 成員

如果你還沒正式學 class，可以先有個概念：`static` 成員屬於類別本身，而不是某一個物件。

### 範例檔案：`ex13_5_3_static_class_member.cpp`

```cpp
#include <iostream>
using namespace std;

class Student {
public:
    string name;
    static int total;

    Student(string n) {
        name = n;
        total++;
    }
};

int Student::total = 0;

int main() {
    Student a("Alice");
    Student b("Bob");
    Student c("Carol");

    cout << "學生總數 = " << Student::total << '\n';

    return 0;
}
```

### 13.5.5 static 的常見風險

`static` 很方便，但也容易被濫用。

風險：

- 函式看起來沒有狀態，實際上卻偷偷記住資料。
- 測試時狀態不容易重置。
- 多執行緒程式可能發生資料競爭。
- 全域狀態太多會讓程式難以理解。

壞例子：

```cpp
int getDiscount() {
    static int times = 0;
    times++;
    return times > 3 ? 20 : 10;
}
```

這個函式結果取決於被呼叫幾次，不只取決於輸入，容易造成難查的 bug。

適合使用 static 區域變數的例子：

- 簡單 ID 產生器。
- 計算函式被呼叫次數。
- 延遲初始化昂貴資源。
- 單檔小工具程式中保存狀態。

---

## 13.6 `auto`

### 13.6.1 `auto` 是什麼？

`auto` 讓編譯器根據初始化值推導變數型別。

```cpp
auto x = 10;       // int
auto y = 3.14;     // double
auto c = 'A';      // char
auto ok = true;    // bool
```

`auto` 必須有初始化值：

```cpp
auto x = 10; // OK
auto y;      // 錯誤：不知道要推導成什麼型別
```

### 範例檔案：`ex13_6_1_auto_basic.cpp`

```cpp
#include <iostream>
#include <typeinfo>
using namespace std;

int main() {
    auto a = 10;
    auto b = 3.14;
    auto c = 'X';
    auto d = true;

    cout << "a = " << a << ", type = " << typeid(a).name() << '\n';
    cout << "b = " << b << ", type = " << typeid(b).name() << '\n';
    cout << "c = " << c << ", type = " << typeid(c).name() << '\n';
    cout << "d = " << d << ", type = " << typeid(d).name() << '\n';

    return 0;
}
```

不同編譯器的 `typeid(...).name()` 顯示可能不同。

### 13.6.2 `auto` 最適合的情境

`auto` 很適合型別很長、右邊已經清楚表達型別的時候。

```cpp
vector<int> numbers = {1, 2, 3};

for (auto it = numbers.begin(); it != numbers.end(); ++it) {
    cout << *it << '\n';
}
```

比起：

```cpp
for (vector<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
    cout << *it << '\n';
}
```

`auto` 明顯乾淨很多。

### 範例檔案：`ex13_6_2_auto_iterator.cpp`

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> scores = {80, 90, 75, 100};

    for (auto it = scores.begin(); it != scores.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';

    return 0;
}
```

### 13.6.3 range-based for 與 auto

C++11 提供 range-based for：

```cpp
for (auto x : container) {
    // ...
}
```

注意：`auto x` 會複製元素。

```cpp
for (auto x : scores) {
    x += 10; // 只改副本，不會改 scores 裡面的元素
}
```

若要修改容器內元素，要用 `auto&`。

```cpp
for (auto& x : scores) {
    x += 10;
}
```

若只讀取，建議用 `const auto&`。

```cpp
for (const auto& name : names) {
    cout << name << '\n';
}
```

### 範例檔案：`ex13_6_3_auto_reference.cpp`

```cpp
#include <iostream>
#include <vector>
using namespace std;

void print(const vector<int>& v) {
    for (const auto& x : v) {
        cout << x << ' ';
    }
    cout << '\n';
}

int main() {
    vector<int> scores = {80, 90, 75};

    for (auto x : scores) {
        x += 10;
    }
    print(scores); // 沒變

    for (auto& x : scores) {
        x += 10;
    }
    print(scores); // 有變

    return 0;
}
```

輸出：

```text
80 90 75
90 100 85
```

### 13.6.4 `auto` 與 const

`auto` 推導時，頂層 `const` 常會被拿掉。

```cpp
const int x = 10;
auto a = x;        // a 是 int，不是 const int
const auto b = x;  // b 是 const int
```

### 範例檔案：`ex13_6_4_auto_const.cpp`

```cpp
#include <iostream>
using namespace std;

int main() {
    const int x = 10;

    auto a = x;
    a = 20; // OK，a 是新的 int 變數

    const auto b = x;
    // b = 30; // 錯誤，b 是 const

    cout << "x = " << x << '\n';
    cout << "a = " << a << '\n';
    cout << "b = " << b << '\n';

    return 0;
}
```

### 13.6.5 `auto` 與窄化轉型

`auto x = 3.14;` 會推導成 `double`。

```cpp
auto x = 3.14; // double
int y = x;     // 小心，小數被截斷
```

如果你想要 `float`，要寫：

```cpp
auto f = 3.14f; // float
```

如果你想要 `long long`：

```cpp
auto big = 10000000000LL; // long long
```

### 13.6.6 什麼時候不要用 auto？

`auto` 不該讓程式變難讀。

不好的例子：

```cpp
auto result = process(data);
```

如果 `process(data)` 的回傳型別不明顯，讀程式的人會很痛苦。

較好的例子：

```cpp
UserProfile result = process(data);
```

建議：

| 情境 | 建議 |
|---|---|
| 右邊型別很明顯 | 可以用 `auto` |
| 迭代器型別很長 | 適合用 `auto` |
| range-based for | 常用 `auto`、`auto&`、`const auto&` |
| 函式回傳型別不明顯 | 斟酌，明寫型別可能更清楚 |
| 需要固定大小整數 | 不要用 `auto` 模糊掉 `int32_t`、`uint64_t` 的語意 |

---

## 13.7 綜合範例

### 範例檔案：`ex13_7_1_bank_account_report.cpp`

這個範例結合：

- `int64_t` 表示金額分。
- `const` 表示不可修改參數。
- `static` 建立流水號。
- `auto` 簡化迴圈。
- `uint32_t` 表示帳號 ID。

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <iomanip>
using namespace std;

struct Account {
    uint32_t id;
    string owner;
    int64_t cents;
};

uint32_t nextAccountId() {
    static uint32_t id = 100000;
    return ++id;
}

void deposit(Account& account, const int64_t cents) {
    if (cents <= 0) {
        cout << "存款金額必須大於 0\n";
        return;
    }
    account.cents += cents;
}

void printMoney(const int64_t cents) {
    cout << "NT$ " << cents / 100 << '.'
         << setw(2) << setfill('0') << cents % 100
         << setfill(' ');
}

void printAccounts(const vector<Account>& accounts) {
    cout << "帳號      姓名      餘額\n";
    cout << "---------------------------\n";

    for (const auto& account : accounts) {
        cout << account.id << "  "
             << setw(8) << left << account.owner << right << "  ";
        printMoney(account.cents);
        cout << '\n';
    }
}

int main() {
    vector<Account> accounts;

    accounts.push_back({nextAccountId(), "Alice", 150000});
    accounts.push_back({nextAccountId(), "Bob", 230050});
    accounts.push_back({nextAccountId(), "Carol", 999});

    deposit(accounts[0], 5000);
    deposit(accounts[1], 100000);

    printAccounts(accounts);

    return 0;
}
```

---

## 13.8 本章重點整理

```text
宣告修飾
├─ 修飾大小
│  ├─ short：通常較小，範圍有限
│  ├─ long：平台差異大，不要假設一定 8 bytes
│  └─ long long：常用於大整數
├─ 有號及無號
│  ├─ signed：可表示負數
│  ├─ unsigned：只表示非負，但有迴繞與比較陷阱
│  └─ size_t：常用於大小與索引，但倒數迴圈要小心
├─ C++11 標準整數
│  ├─ int8_t / uint8_t
│  ├─ int16_t / uint16_t
│  ├─ int32_t / uint32_t
│  └─ int64_t / uint64_t
├─ 常數
│  ├─ const：不可修改
│  ├─ constexpr：編譯期常數
│  └─ const T&：常用於只讀且避免複製
├─ static
│  ├─ 區域 static：保留狀態
│  ├─ 全域 static：限制檔案可見性
│  └─ 類別 static：屬於類別，不屬於個別物件
└─ auto
   ├─ 根據初始化值推導型別
   ├─ 適合迭代器與 range-based for
   ├─ auto& 可修改原資料
   └─ const auto& 適合只讀大型物件
```

---

## 13.9 大量實作練習

以下練習都附答案。建議學生先自己寫，再看答案。

### 練習 13-1：印出型別大小

建立 `hw13_1_type_sizes.cpp`，印出以下型別的 `sizeof`：

- `short`
- `int`
- `long`
- `long long`
- `float`
- `double`
- `long double`
- `size_t`

#### 參考答案

```cpp
#include <iostream>
#include <cstddef>
using namespace std;

int main() {
    cout << "short       : " << sizeof(short) << '\n';
    cout << "int         : " << sizeof(int) << '\n';
    cout << "long        : " << sizeof(long) << '\n';
    cout << "long long   : " << sizeof(long long) << '\n';
    cout << "float       : " << sizeof(float) << '\n';
    cout << "double      : " << sizeof(double) << '\n';
    cout << "long double : " << sizeof(long double) << '\n';
    cout << "size_t      : " << sizeof(size_t) << '\n';
    return 0;
}
```

### 練習 13-2：避免整數溢位

建立 `hw13_2_multiply_large.cpp`。輸入兩個整數 `a`、`b`，輸出它們的乘積。假設輸入可能到 10 億，請選擇安全型別。

#### 參考答案

```cpp
#include <iostream>
using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;
    cout << a * b << '\n';
    return 0;
}
```

### 練習 13-3：修正 signed/unsigned 比較

建立 `hw13_3_fix_compare.cpp`。給定：

```cpp
int target = -1;
unsigned int count = 10;
```

請寫出安全比較，不要讓 `target < count` 發生 unsigned 轉型陷阱。

#### 參考答案

```cpp
#include <iostream>
using namespace std;

int main() {
    int target = -1;
    unsigned int count = 10;

    if (target < 0) {
        cout << "target 是負數，一定小於 count\n";
    } else if (static_cast<unsigned int>(target) < count) {
        cout << "target 小於 count\n";
    } else {
        cout << "target 不小於 count\n";
    }

    return 0;
}
```

### 練習 13-4：倒著印字串

建立 `hw13_4_reverse_string.cpp`。輸入一個字串，倒著印出來。請避免 `size_t` 倒數迴圈陷阱。

#### 參考答案

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;

    for (size_t i = s.size(); i > 0; i--) {
        cout << s[i - 1];
    }
    cout << '\n';

    return 0;
}
```

### 練習 13-5：使用固定寬度整數

建立 `hw13_5_packet_header.cpp`。宣告封包欄位：

- `version`：8-bit unsigned
- `type`：8-bit unsigned
- `length`：16-bit unsigned
- `sequence`：32-bit unsigned

印出各欄位大小。

#### 參考答案

```cpp
#include <iostream>
#include <cstdint>
using namespace std;

int main() {
    uint8_t version = 1;
    uint8_t type = 2;
    uint16_t length = 128;
    uint32_t sequence = 10001;

    cout << "version size  = " << sizeof(version) << '\n';
    cout << "type size     = " << sizeof(type) << '\n';
    cout << "length size   = " << sizeof(length) << '\n';
    cout << "sequence size = " << sizeof(sequence) << '\n';

    cout << "version = " << static_cast<int>(version) << '\n';
    cout << "type    = " << static_cast<int>(type) << '\n';
    cout << "length  = " << length << '\n';
    cout << "seq     = " << sequence << '\n';

    return 0;
}
```

### 練習 13-6：使用 `numeric_limits`

建立 `hw13_6_limits.cpp`。印出 `int`、`long long`、`uint32_t`、`int64_t` 的最小值與最大值。

#### 參考答案

```cpp
#include <iostream>
#include <limits>
#include <cstdint>
using namespace std;

int main() {
    cout << "int min = " << numeric_limits<int>::min() << '\n';
    cout << "int max = " << numeric_limits<int>::max() << '\n';

    cout << "long long min = " << numeric_limits<long long>::min() << '\n';
    cout << "long long max = " << numeric_limits<long long>::max() << '\n';

    cout << "uint32_t min = " << numeric_limits<uint32_t>::min() << '\n';
    cout << "uint32_t max = " << numeric_limits<uint32_t>::max() << '\n';

    cout << "int64_t min = " << numeric_limits<int64_t>::min() << '\n';
    cout << "int64_t max = " << numeric_limits<int64_t>::max() << '\n';

    return 0;
}
```

### 練習 13-7：圓形計算器

建立 `hw13_7_circle_const.cpp`。使用 `constexpr double PI`，輸入半徑，輸出面積與周長。

#### 參考答案

```cpp
#include <iostream>
using namespace std;

int main() {
    constexpr double PI = 3.141592653589793;

    double r;
    cin >> r;

    cout << "area = " << PI * r * r << '\n';
    cout << "circumference = " << 2 * PI * r << '\n';

    return 0;
}
```

### 練習 13-8：安全列印學生姓名

建立 `hw13_8_const_reference.cpp`。寫一個函式：

```cpp
void printStudent(const string& name, int score);
```

輸出姓名與成績，不要修改姓名。

#### 參考答案

```cpp
#include <iostream>
#include <string>
using namespace std;

void printStudent(const string& name, int score) {
    cout << "name  = " << name << '\n';
    cout << "score = " << score << '\n';
}

int main() {
    string name = "Alice";
    int score = 90;

    printStudent(name, score);

    return 0;
}
```

### 練習 13-9：讀懂 const pointer

建立 `hw13_9_const_pointer_quiz.cpp`。宣告兩個整數 `a`、`b`，分別示範：

- `const int*`
- `int* const`
- `const int* const`

#### 參考答案

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10;
    int b = 20;

    const int* p1 = &a;
    p1 = &b;
    // *p1 = 99;

    int* const p2 = &a;
    *p2 = 99;
    // p2 = &b;

    const int* const p3 = &a;
    // p3 = &b;
    // *p3 = 100;

    cout << "a = " << a << '\n';
    cout << "b = " << b << '\n';

    return 0;
}
```

### 練習 13-10：流水號產生器

建立 `hw13_10_static_id.cpp`。寫一個函式 `int nextId()`，第一次回傳 1，第二次回傳 2，以此類推。

#### 參考答案

```cpp
#include <iostream>
using namespace std;

int nextId() {
    static int id = 0;
    id++;
    return id;
}

int main() {
    cout << nextId() << '\n';
    cout << nextId() << '\n';
    cout << nextId() << '\n';
    return 0;
}
```

### 練習 13-11：函式呼叫次數統計

建立 `hw13_11_static_call_count.cpp`。寫 `void hello()`，每次呼叫都印出這是第幾次呼叫。

#### 參考答案

```cpp
#include <iostream>
using namespace std;

void hello() {
    static int times = 0;
    times++;
    cout << "hello called " << times << " time(s)\n";
}

int main() {
    hello();
    hello();
    hello();
    return 0;
}
```

### 練習 13-12：用 auto 改寫迭代器

建立 `hw13_12_auto_iterator.cpp`。建立 `vector<int>`，用 iterator 印出所有元素。請使用 `auto`。

#### 參考答案

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};

    for (auto it = nums.begin(); it != nums.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';

    return 0;
}
```

### 練習 13-13：`auto`、`auto&` 差異

建立 `hw13_13_auto_reference.cpp`。建立 `vector<int>{1,2,3}`，先用 `auto x` 嘗試每個元素加 10，再用 `auto& x` 每個元素加 10，觀察差異。

#### 參考答案

```cpp
#include <iostream>
#include <vector>
using namespace std;

void print(const vector<int>& nums) {
    for (const auto& x : nums) {
        cout << x << ' ';
    }
    cout << '\n';
}

int main() {
    vector<int> nums = {1, 2, 3};

    for (auto x : nums) {
        x += 10;
    }
    print(nums);

    for (auto& x : nums) {
        x += 10;
    }
    print(nums);

    return 0;
}
```

### 練習 13-14：統計成績

建立 `hw13_14_score_stats.cpp`。使用 `vector<int>` 儲存成績，使用 `const auto&` 印出成績，使用 `long long` 計算總分，避免大量加總時溢位。

#### 參考答案

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> scores = {80, 90, 75, 100, 60};

    long long sum = 0;
    for (const auto& score : scores) {
        cout << score << ' ';
        sum += score;
    }
    cout << '\n';

    double avg = static_cast<double>(sum) / scores.size();
    cout << "sum = " << sum << '\n';
    cout << "avg = " << avg << '\n';

    return 0;
}
```

### 練習 13-15：交易金額

建立 `hw13_15_money_cents.cpp`。使用 `int64_t` 儲存金額的「分」，輸入多筆交易金額分，計算總和。

輸入：

```text
5
100
-30
250
-20
1000
```

輸出總分數與元。

#### 參考答案

```cpp
#include <iostream>
#include <cstdint>
#include <iomanip>
using namespace std;

int main() {
    int n;
    cin >> n;

    int64_t total = 0;
    for (int i = 0; i < n; i++) {
        int64_t cents;
        cin >> cents;
        total += cents;
    }

    cout << "total cents = " << total << '\n';
    cout << "total money = " << total / 100 << '.'
         << setw(2) << setfill('0') << (total >= 0 ? total % 100 : -total % 100)
         << '\n';

    return 0;
}
```

---

## 13.10 面試考題補充

### 題目 1：`int`、`long`、`long long` 一定分別是幾 bytes 嗎？

答案：不一定。C++ 標準只保證相對大小順序，實際大小由平台與編譯器決定。若需要固定寬度，應使用 `<cstdint>` 的 `int32_t`、`int64_t` 等。

### 題目 2：為什麼 `unsigned int x = 0; cout << x - 1;` 不是 `-1`？

答案：`unsigned` 不表示負數。`0 - 1` 會依 unsigned 規則迴繞，通常變成該型別最大值。

### 題目 3：下面程式可能輸出什麼？

```cpp
int a = -1;
unsigned int b = 1;
cout << (a < b);
```

答案：可能輸出 `0`。因為比較時 `a` 可能被轉成 unsigned，成為很大的正數。

### 題目 4：`const int* p` 與 `int* const p` 差在哪？

答案：

```cpp
const int* p;      // 不能透過 p 修改值，但 p 可以改指向
int* const p = &x; // p 不能改指向，但可以透過 p 修改值
```

### 題目 5：`const` 和 `constexpr` 差在哪？

答案：`const` 表示值不可修改，但不一定是編譯期常數。`constexpr` 要求值可在編譯期求得，適合用於陣列大小、模板參數、編譯期運算。

### 題目 6：區域變數加 `static` 後有什麼不同？

答案：普通區域變數每次函式呼叫都重新建立；`static` 區域變數只初始化一次，生命週期持續到程式結束，但作用域仍限制在函式內。

### 題目 7：全域函式前面的 `static` 是什麼意思？

答案：代表此函式具有 internal linkage，只能在目前 `.cpp` 檔案內使用，避免與其他檔案中的同名函式衝突。

### 題目 8：`auto` 是否永遠讓程式更好？

答案：不是。`auto` 適合型別冗長或右邊很明顯的情境，但如果隱藏了重要語意，例如固定寬度整數、金額型別、複雜函式回傳型別，明寫型別可能更清楚。

### 題目 9：`auto x = vec[0];` 與 `auto& x = vec[0];` 差在哪？

答案：`auto x` 會複製元素，修改 `x` 不影響 `vec[0]`。`auto& x` 是參考，修改 `x` 會修改原本元素。

### 題目 10：為什麼 `uint8_t x = 65; cout << x;` 可能印出 `A`？

答案：`uint8_t` 常是 `unsigned char` 的別名，`cout` 可能把它當字元輸出。若要印數字，使用 `static_cast<int>(x)`。

---

## 13.11 作品集專案

以下專案適合當作學生作品集練習。每個專案都刻意使用本章重點。

---

### 專案 13-1：交易紀錄統計器

#### 檔案名稱

`project13_transaction_tracker_answer.cpp`

#### 功能需求

建立一個簡單交易紀錄程式：

1. 每筆交易有流水號、說明、金額分。
2. 使用 `static` 產生交易流水號。
3. 使用 `int64_t` 儲存金額分。
4. 使用 `const auto&` 列印所有交易。
5. 使用 `constexpr` 定義每元幾分。
6. 支援新增交易、列印交易、計算總額。

#### 參考答案

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <iomanip>
using namespace std;

struct Transaction {
    uint32_t id;
    string note;
    int64_t cents;
};

uint32_t nextTransactionId() {
    static uint32_t id = 0;
    return ++id;
}

void printMoney(const int64_t cents) {
    constexpr int CENTS_PER_DOLLAR = 100;

    int64_t dollars = cents / CENTS_PER_DOLLAR;
    int64_t remain = cents % CENTS_PER_DOLLAR;
    if (remain < 0) remain = -remain;

    cout << dollars << '.'
         << setw(2) << setfill('0') << remain
         << setfill(' ');
}

void addTransaction(vector<Transaction>& records) {
    Transaction t;
    t.id = nextTransactionId();

    cout << "說明: ";
    cin >> t.note;
    cout << "金額分，可為負數: ";
    cin >> t.cents;

    records.push_back(t);
}

void printTransactions(const vector<Transaction>& records) {
    cout << "ID      NOTE            AMOUNT\n";
    cout << "--------------------------------\n";

    for (const auto& t : records) {
        cout << setw(7) << left << t.id
             << setw(16) << left << t.note
             << right;
        printMoney(t.cents);
        cout << '\n';
    }
}

int64_t totalAmount(const vector<Transaction>& records) {
    int64_t total = 0;
    for (const auto& t : records) {
        total += t.cents;
    }
    return total;
}

int main() {
    vector<Transaction> records;

    while (true) {
        cout << "\n1. 新增交易\n";
        cout << "2. 列印交易\n";
        cout << "3. 顯示總額\n";
        cout << "0. 離開\n";
        cout << "選擇: ";

        int choice;
        cin >> choice;

        if (choice == 0) break;
        if (choice == 1) {
            addTransaction(records);
        } else if (choice == 2) {
            printTransactions(records);
        } else if (choice == 3) {
            cout << "總額: ";
            printMoney(totalAmount(records));
            cout << '\n';
        } else {
            cout << "無效選項\n";
        }
    }

    return 0;
}
```

---

### 專案 13-2：二進位封包檢視器

#### 檔案名稱

`project13_packet_viewer_answer.cpp`

#### 功能需求

模擬一個封包標頭：

- version：`uint8_t`
- type：`uint8_t`
- flags：`uint16_t`
- length：`uint32_t`

輸出欄位、大小、flags 的二進位。

#### 參考答案

```cpp
#include <iostream>
#include <cstdint>
using namespace std;

struct PacketHeader {
    uint8_t version;
    uint8_t type;
    uint16_t flags;
    uint32_t length;
};

void printBits(uint32_t value, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        cout << ((value >> i) & 1U);
        if (i % 4 == 0) cout << ' ';
    }
}

void printHeader(const PacketHeader& h) {
    cout << "version = " << static_cast<int>(h.version) << '\n';
    cout << "type    = " << static_cast<int>(h.type) << '\n';
    cout << "flags   = " << h.flags << " (";
    printBits(h.flags, 16);
    cout << ")\n";
    cout << "length  = " << h.length << '\n';

    cout << "sizeof(PacketHeader) = " << sizeof(PacketHeader) << '\n';
}

int main() {
    PacketHeader header;
    header.version = 1;
    header.type = 3;
    header.flags = 0b0000000010101010;
    header.length = 1024;

    printHeader(header);

    return 0;
}
```

---

### 專案 13-3：學生成績排行榜

#### 檔案名稱

`project13_scoreboard_answer.cpp`

#### 功能需求

1. 新增學生姓名與分數。
2. 每位學生有自動 ID。
3. 使用 `static` 產生 ID。
4. 使用 `const auto&` 顯示學生。
5. 使用 `long long` 計算總分。
6. 顯示平均與最高分。

#### 參考答案

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct Student {
    int id;
    string name;
    int score;
};

int nextStudentId() {
    static int id = 100;
    return ++id;
}

void addStudent(vector<Student>& students) {
    Student s;
    s.id = nextStudentId();

    cout << "姓名: ";
    cin >> s.name;
    cout << "分數: ";
    cin >> s.score;

    students.push_back(s);
}

void printStudents(const vector<Student>& students) {
    cout << "ID     NAME        SCORE\n";
    cout << "-------------------------\n";

    for (const auto& s : students) {
        cout << setw(7) << left << s.id
             << setw(12) << left << s.name
             << right << s.score << '\n';
    }
}

void printStats(const vector<Student>& students) {
    if (students.empty()) {
        cout << "尚無資料\n";
        return;
    }

    long long sum = 0;
    const Student* best = &students[0];

    for (const auto& s : students) {
        sum += s.score;
        if (s.score > best->score) {
            best = &s;
        }
    }

    double avg = static_cast<double>(sum) / students.size();

    cout << "平均 = " << avg << '\n';
    cout << "最高 = " << best->name << " (" << best->score << ")\n";
}

int main() {
    vector<Student> students;

    while (true) {
        cout << "\n1. 新增學生\n";
        cout << "2. 列印名單\n";
        cout << "3. 統計\n";
        cout << "0. 離開\n";
        cout << "選擇: ";

        int choice;
        cin >> choice;

        if (choice == 0) break;
        if (choice == 1) {
            addStudent(students);
        } else if (choice == 2) {
            printStudents(students);
        } else if (choice == 3) {
            printStats(students);
        } else {
            cout << "無效選項\n";
        }
    }

    return 0;
}
```

---

## 13.12 教學建議

這一章不要只讓學生背語法。最重要的是讓學生建立工程直覺：

1. 數值有範圍，超出範圍會出事。
2. `unsigned` 不是單純的「比較大的 int」。
3. 如果資料格式要求明確位元數，就用 `<cstdint>`。
4. 不該改的值就寫成 `const` 或 `constexpr`。
5. `static` 會留下狀態，使用前要想清楚。
6. `auto` 是讓程式更清楚的工具，不是把型別藏起來的藉口。

學生如果能把這幾點說清楚，之後學指標、參考、記憶體管理、物件導向與 STL 時會順很多。
