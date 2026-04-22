# 第九章：函式（Function）

> **學習目標**
>
> - 理解函式的概念：封裝、重用、分而治之
> - 能呼叫標準函式庫函式，並閱讀函式原型
> - 掌握有回傳值與無回傳值函式的定義方式
> - 熟悉多參數函式、預設引數、函式重載
> - 深刻理解傳值、傳參考、傳指標三種參數傳遞方式的差異
> - 能用函式分解複雜問題（生命遊戲、鏡子房間、井字遊戲）

---

## 9.0 為什麼需要函式？

想像你要寫一個程式，需要在三個地方判斷某個數字是否為質數。如果沒有函式，你會重複寫三段相同的程式碼：

```cpp
// 沒有函式，到處重複
bool isPrime1 = true;
for (int i = 2; i * i <= n1; i++)
    if (n1 % i == 0) { isPrime1 = false; break; }

bool isPrime2 = true;
for (int i = 2; i * i <= n2; i++)
    if (n2 % i == 0) { isPrime2 = false; break; }
// ... 同樣的程式碼再寫一次
```

有了函式，你只需要：

```cpp
bool isPrime(int n) {
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

// 任何地方都可以呼叫
if (isPrime(17)) cout << "質數！";
if (isPrime(100)) cout << "質數！";
```

函式帶來三大好處：

```
┌─────────────────────────────────────────────────────────┐
│                   函式的三大好處                          │
├─────────────┬─────────────────┬─────────────────────────┤
│  封裝複雜度  │    程式碼重用    │       易於測試           │
│  (Hide)     │    (Reuse)      │       (Test)            │
├─────────────┼─────────────────┼─────────────────────────┤
│ 把複雜邏輯  │ 寫一次，呼叫     │ 可單獨測試每個函式，      │
│ 藏在函式裡  │ 無限次          │ 容易找到 bug             │
└─────────────┴─────────────────┴─────────────────────────┘
```

> 💡 **軟體工程師的習慣：** 如果一段程式碼會重複出現超過兩次，就把它寫成函式。

---

## 9.1 呼叫函式

### 9.1.1 函式原型（Function Prototype）

使用函式之前，必須先讓編譯器「認識」這個函式。函式原型包含：

```
回傳型別  函式名稱(參數型別1, 參數型別2, ...);
   │          │            │
  int      isPrime       (int n)
```

| 術語                       | 說明                   | 範例                    |
| -------------------------- | ---------------------- | ----------------------- |
| **函式名稱**               | 命名規則同變數         | `isPrime`, `calcArea`   |
| **參數（Parameter）**      | 函式定義中的變數名稱   | `int n`                 |
| **引數（Argument）**       | 呼叫函式時實際傳入的值 | `isPrime(17)` 中的 `17` |
| **回傳值（Return Value）** | 函式執行完後傳回的結果 | `return false;`         |

### 9.1.2 呼叫標準函式庫

C++ 標準函式庫提供大量現成函式，透過 `#include` 引入標頭檔後即可使用。

```cpp
#include <cmath>    // sqrt, pow, abs, ceil, floor
#include <cstdlib>  // rand, srand, abs
#include <ctime>    // time
#include <algorithm> // max, min, sort
```

| 標頭檔        | 常用函式               | 說明                      |
| ------------- | ---------------------- | ------------------------- |
| `<cmath>`     | `sqrt(x)`              | 平方根                    |
| `<cmath>`     | `pow(x, y)`            | x 的 y 次方               |
| `<cmath>`     | `abs(x)`               | 絕對值（浮點數）          |
| `<cmath>`     | `ceil(x)` / `floor(x)` | 無條件進位 / 捨去         |
| `<cmath>`     | `round(x)`             | 四捨五入                  |
| `<algorithm>` | `max(a, b)`            | 最大值                    |
| `<algorithm>` | `min(a, b)`            | 最小值                    |
| `<cstdlib>`   | `rand()`               | 產生亂數（0 到 RAND_MAX） |
| `<ctime>`     | `time(nullptr)`        | 取得目前時間（秒）        |

**範例程式：** `ex9_1_1_stdlib_calls.cpp`

```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    // --- cmath ---
    double x = 2.0;
    cout << "sqrt(2)  = " << sqrt(x) << endl;       // 1.41421
    cout << "pow(2,8) = " << pow(2, 8) << endl;      // 256
    cout << "ceil(3.2)= " << ceil(3.2) << endl;      // 4
    cout << "floor(3.8)=" << floor(3.8) << endl;     // 3
    cout << "round(3.5)=" << round(3.5) << endl;     // 4
    cout << "abs(-7.5) = " << abs(-7.5) << endl;     // 7.5

    // --- algorithm ---
    cout << "max(3,7) = " << max(3, 7) << endl;      // 7
    cout << "min(3,7) = " << min(3, 7) << endl;      // 3

    // --- 亂數 ---
    srand(time(nullptr));                             // 設定亂數種子
    int dice = rand() % 6 + 1;                       // 1~6
    cout << "骰子點數：" << dice << endl;

    return 0;
}
```

**執行結果：**

```
sqrt(2)  = 1.41421
pow(2,8) = 256
ceil(3.2)= 4
floor(3.8)= 3
round(3.5)= 4
abs(-7.5) = 7.5
max(3,7) = 7
min(3,7) = 3
骰子點數：4
```

> ⚠️ **注意：`rand()` 需要種子**
> 不呼叫 `srand()` 時，每次執行產生的亂數序列相同。
> 用 `srand(time(nullptr))` 以當下時間為種子，確保每次不同。

### 9.1.3 函式宣告與定義的順序

**方式一：先宣告（Prototype），後定義**（推薦，適合大型程式）

```cpp
// ① 宣告（告訴編譯器函式存在）
int square(int n);

int main() {
    cout << square(5);   // ② 可以呼叫
}

// ③ 定義（實際程式碼）
int square(int n) {
    return n * n;
}
```

**方式二：先定義，後呼叫**（小程式可用）

```cpp
int square(int n) {     // ① 定義
    return n * n;
}

int main() {
    cout << square(5);  // ② 呼叫
}
```

> 💡 **專業做法：** 大型程式通常把宣告放在 `.h` 標頭檔，定義放在 `.cpp` 實作檔。

**範例程式：** `ex9_1_2_prototype.cpp`

```cpp
#include <iostream>
using namespace std;

// 前置宣告（Prototype）
int square(int n);
double circleArea(double r);
bool isEven(int n);

int main() {
    cout << "5 的平方：" << square(5) << endl;
    cout << "半徑 3 的圓面積：" << circleArea(3.0) << endl;
    cout << "4 是偶數？" << isEven(4) << endl;
    cout << "7 是偶數？" << isEven(7) << endl;
    return 0;
}

int square(int n) {
    return n * n;
}

double circleArea(double r) {
    const double PI = 3.14159265;
    return PI * r * r;
}

bool isEven(int n) {
    return n % 2 == 0;
}
```

**執行結果：**

```
5 的平方：25
半徑 3 的圓面積：28.2743
4 是偶數？1
7 是偶數？0
```

---

## 9.2 定義有回傳值的函式

### 9.2.1 基本語法

```
回傳型別  函式名稱(參數列表) {
    // 函式主體
    return 回傳值;
}
```

執行流程：

```
main()                      square(5)
┌──────────────────┐        ┌───────────────────┐
│  int r = square(5);│──呼叫→│  int n = 5         │
│         ↑         │        │  return n * n;     │
│       r = 25      │←回傳─ │  (計算結果 25)     │
│  cout << r;       │        └───────────────────┘
└──────────────────┘
```

### 9.2.2 return 的作用

- `return` 立刻結束函式執行，並將值傳回給呼叫者
- 函式內可以有**多個 return**（通常在不同條件分支）
- `return` 的型別必須與宣告的回傳型別相符

**範例程式：** `ex9_2_1_return_basic.cpp`

```cpp
#include <iostream>
#include <cmath>
using namespace std;

// 回傳整數
int absolute(int x) {
    if (x < 0) return -x;
    return x;
}

// 回傳浮點數
double hypotenuse(double a, double b) {
    return sqrt(a * a + b * b);
}

// 回傳布林值
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

// 回傳字元
char grade(int score) {
    if (score >= 90) return 'A';
    if (score >= 80) return 'B';
    if (score >= 70) return 'C';
    if (score >= 60) return 'D';
    return 'F';
}

int main() {
    cout << "abs(-7)       = " << absolute(-7) << endl;
    cout << "斜邊(3,4)     = " << hypotenuse(3, 4) << endl;
    cout << "isPrime(17)   = " << isPrime(17) << endl;
    cout << "isPrime(20)   = " << isPrime(20) << endl;
    cout << "grade(85)     = " << grade(85) << endl;
    cout << "grade(55)     = " << grade(55) << endl;
    return 0;
}
```

**執行結果：**

```
abs(-7)       = 7
斜邊(3,4)     = 5
isPrime(17)   = 1
isPrime(20)   = 0
grade(85)     = B
grade(55)     = F
```

### 9.2.3 回傳型別的種類

| 回傳型別 | 說明       | 典型用途             |
| -------- | ---------- | -------------------- |
| `int`    | 整數結果   | 計算、索引           |
| `double` | 浮點數結果 | 數學運算             |
| `bool`   | 真/假      | 判斷、驗證           |
| `char`   | 字元       | 等級、符號           |
| `string` | 字串       | 文字處理             |
| `void`   | 無回傳值   | 輸出、修改（下一節） |

**範例程式：** `ex9_2_2_return_types.cpp`

```cpp
#include <iostream>
#include <string>
using namespace std;

int clamp(int val, int lo, int hi) {
    if (val < lo) return lo;
    if (val > hi) return hi;
    return val;
}

string repeatStr(string s, int n) {
    string result = "";
    for (int i = 0; i < n; i++) result += s;
    return result;
}

bool inRange(double x, double lo, double hi) {
    return x >= lo && x <= hi;
}

int main() {
    cout << clamp(150, 0, 100) << endl;   // 100
    cout << clamp(-5,  0, 100) << endl;   // 0
    cout << clamp(50,  0, 100) << endl;   // 50

    cout << repeatStr("ha", 3) << endl;   // hahaha

    cout << inRange(3.5, 1.0, 5.0) << endl;  // 1
    cout << inRange(7.5, 1.0, 5.0) << endl;  // 0

    return 0;
}
```

**執行結果：**

```
100
0
50
hahaha
1
0
```

---

## 9.3 定義無回傳值的函式

### 9.3.1 void 函式

當函式不需要回傳結果，只執行動作（如輸出、修改外部狀態），使用 `void` 作為回傳型別。

```cpp
void printLine(int n) {      // 不回傳值
    for (int i = 0; i < n; i++)
        cout << '-';
    cout << endl;
}

int main() {
    printLine(20);   // 直接呼叫，不需要 = 接收
}
```

### 9.3.2 提前結束 void 函式

在 `void` 函式中，`return;`（不帶值）可以提前結束函式。

```cpp
void printPositive(int n) {
    if (n <= 0) {
        cout << "不是正數！" << endl;
        return;          // 提前結束
    }
    cout << "正數：" << n << endl;
}
```

**範例程式：** `ex9_3_1_void_function.cpp`

```cpp
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void printDivider(char ch, int width) {
    for (int i = 0; i < width; i++) cout << ch;
    cout << endl;
}

void printBox(const string& title) {
    int w = title.size() + 4;
    printDivider('=', w);
    cout << "| " << title << " |" << endl;
    printDivider('=', w);
}

void printMultiTable(int n) {
    if (n < 1 || n > 9) {
        cout << "範圍限 1~9！" << endl;
        return;
    }
    for (int i = 1; i <= 9; i++)
        cout << n << " × " << i << " = " << n * i << endl;
}

int main() {
    printBox("第九章：函式");
    cout << endl;
    printMultiTable(7);
    cout << endl;
    printMultiTable(10);    // 超出範圍，提前 return
    return 0;
}
```

**執行結果：**

```
================
| 第九章：函式 |
================

7 × 1 = 7
7 × 2 = 14
...
7 × 9 = 63

範圍限 1~9！
```

**範例程式：** `ex9_3_2_void_menu.cpp`

```cpp
#include <iostream>
using namespace std;

void showMenu() {
    cout << "┌──────────────────┐" << endl;
    cout << "│  1. 計算圓面積    │" << endl;
    cout << "│  2. 計算矩形面積  │" << endl;
    cout << "│  0. 離開          │" << endl;
    cout << "└──────────────────┘" << endl;
    cout << "請選擇：";
}

void calcCircle() {
    double r;
    cout << "半徑："; cin >> r;
    cout << "面積 = " << 3.14159265 * r * r << endl;
}

void calcRect() {
    double w, h;
    cout << "寬："; cin >> w;
    cout << "高："; cin >> h;
    cout << "面積 = " << w * h << endl;
}

int main() {
    int choice;
    do {
        showMenu();
        cin >> choice;
        if      (choice == 1) calcCircle();
        else if (choice == 2) calcRect();
    } while (choice != 0);

    cout << "再見！" << endl;
    return 0;
}
```

**執行結果：**

```
┌──────────────────┐
│  1. 計算圓面積    │
│  2. 計算矩形面積  │
│  0. 離開          │
└──────────────────┘
請選擇：1
半徑：5
面積 = 78.5398
```

---

## 9.4 多個參數的函式

### 9.4.1 多參數語法

```cpp
回傳型別 函式名稱(型別1 參數1, 型別2 參數2, ...) {
    // ...
}
```

各參數之間以逗號分隔，每個參數需要獨立宣告型別（不能省略）：

```cpp
// ✅ 正確
int add(int a, int b);

// ❌ 錯誤：不能省略 int
int add(int a, b);
```

**範例程式：** `ex9_4_1_multi_params.cpp`

```cpp
#include <iostream>
#include <string>
using namespace std;

int clampedAdd(int a, int b, int limit) {
    int sum = a + b;
    return sum > limit ? limit : sum;
}

double bmi(double weight, double heightM) {
    return weight / (heightM * heightM);
}

void printFormatted(string label, double value, int decimals) {
    cout << label << ": ";
    cout.precision(decimals);
    cout << fixed << value << endl;
}

bool between(int x, int lo, int hi) {
    return x >= lo && x <= hi;
}

int main() {
    cout << clampedAdd(80, 50, 100) << endl;    // 100（限制在 100）
    cout << clampedAdd(30, 40, 100) << endl;    // 70

    double myBMI = bmi(70.0, 1.75);
    printFormatted("BMI", myBMI, 2);

    cout << "60 在 1~100 間？" << between(60, 1, 100) << endl;
    cout << "0 在 1~100 間？"  << between(0, 1, 100)  << endl;

    return 0;
}
```

**執行結果：**

```
100
70
BMI: 22.86
60 在 1~100 間？1
0 在 1~100 間？0
```

### 9.4.2 預設引數（Default Arguments）

可以為參數指定預設值，呼叫時若省略該引數，就使用預設值。

> ⚠️ **規則：** 預設引數只能從**右到左**設定，不能跳過中間的參數。

```cpp
// ✅ 合法：預設值從右到左
void drawRect(int w, int h, char ch = '*', bool border = true);

// ❌ 非法：中間有預設、後面沒有
void drawRect(int w, char ch = '*', int h);
```

**範例程式：** `ex9_4_2_default_args.cpp`

```cpp
#include <iostream>
#include <string>
using namespace std;

void printSeparator(int n = 30, char ch = '-') {
    for (int i = 0; i < n; i++) cout << ch;
    cout << endl;
}

string currency(double amount, string symbol = "NT$", int decimals = 0) {
    char buf[50];
    snprintf(buf, sizeof(buf), "%s %.0f", symbol.c_str(), amount);
    return string(buf);
}

double power(double base, int exp = 2) {
    double result = 1.0;
    for (int i = 0; i < exp; i++) result *= base;
    return result;
}

int main() {
    printSeparator();          // 使用全部預設值
    printSeparator(20);        // 指定長度
    printSeparator(15, '=');   // 指定長度和字元

    cout << currency(1500.0) << endl;            // NT$ 1500
    cout << currency(29.99, "USD") << endl;      // USD 30
    cout << currency(1200.0, "JPY", 2) << endl;  // JPY 1200.00

    cout << power(3.0) << endl;     // 9（3^2）
    cout << power(2.0, 10) << endl; // 1024（2^10）

    return 0;
}
```

**執行結果：**

```
------------------------------
--------------------
===============
NT$ 1500
USD 30
JPY 1200.00
9
1024
```

### 9.4.3 函式重載（Function Overloading）

同一個函式名稱，可以有**不同的參數型別或個數**，編譯器根據呼叫方式選擇正確版本。

```cpp
int    max(int a,    int b);       // 版本1：整數
double max(double a, double b);    // 版本2：浮點數
int    max(int a, int b, int c);   // 版本3：三個整數
```

**範例程式：** `ex9_4_3_overload.cpp`

```cpp
#include <iostream>
#include <string>
using namespace std;

// 三個重載版本的 describe()
void describe(int n) {
    cout << "[整數] " << n << endl;
}
void describe(double d) {
    cout << "[浮點] " << d << endl;
}
void describe(string s) {
    cout << "[字串] " << s << endl;
}

// 三個重載版本的 area()
double area(double side) {
    return side * side;          // 正方形
}
double area(double w, double h) {
    return w * h;                // 矩形
}
double area(double a, double b, double c) {
    double s = (a + b + c) / 2;
    return sqrt(s * (s-a) * (s-b) * (s-c));  // 海龍公式
}

int main() {
    describe(42);
    describe(3.14);
    describe("Hello");

    cout << "正方形面積（5）：" << area(5.0) << endl;
    cout << "矩形面積（3,4）：" << area(3.0, 4.0) << endl;
    cout << "三角形面積（3,4,5）：" << area(3.0, 4.0, 5.0) << endl;

    return 0;
}
```

**執行結果：**

```
[整數] 42
[浮點] 3.14
[字串] Hello
正方形面積（5）：25
矩形面積（3,4）：12
三角形面積（3,4,5）：6
```

> ⚠️ **重載 ≠ 僅回傳型別不同**
>
> ```cpp
> int foo(int n);     // ✅
> double foo(int n);  // ❌ 編譯錯誤：只有回傳型別不同，無法重載
> ```

---

## 9.5 參數傳遞

### 9.5.1 傳值（Pass by Value）

C++ 預設將引數**複製一份**傳給函式。函式內的修改**不影響**外部變數。

```
main()          swap_val(a=3, b=7)
┌─────────┐    ┌────────────────────┐
│ a = 3   │───→│ int x = 3 (複製)   │
│ b = 7   │───→│ int y = 7 (複製)   │
│         │    │ swap x, y → x=7,y=3│
│ a 仍是 3│    └────────────────────┘
│ b 仍是 7│      外部 a, b 不受影響
└─────────┘
```

**範例程式：** `ex9_5_1_pass_by_value.cpp`

```cpp
#include <iostream>
using namespace std;

void trySwap(int x, int y) {
    int tmp = x; x = y; y = tmp;
    cout << "函式內：x=" << x << ", y=" << y << endl;
}

int addTen(int n) {
    n += 10;       // 只改了複製品
    return n;      // 回傳修改後的值
}

int main() {
    int a = 3, b = 7;
    cout << "呼叫前：a=" << a << ", b=" << b << endl;
    trySwap(a, b);
    cout << "呼叫後：a=" << a << ", b=" << b << endl;  // 未改變！

    int x = 5;
    int y = addTen(x);
    cout << "x=" << x << ", y=" << y << endl;  // x=5 (不變), y=15
    return 0;
}
```

**執行結果：**

```
呼叫前：a=3, b=7
函式內：x=7, y=3
呼叫後：a=3, b=7
x=5, y=15
```

### 9.5.2 傳參考（Pass by Reference）

在參數名稱前加 `&`，函式接收的是原始變數的**別名**，修改會影響外部。

```
main()            swap_ref(a, b)
┌─────────┐      ┌───────────────────┐
│ a = 3   │─別名→│ int& x → (就是 a) │
│ b = 7   │─別名→│ int& y → (就是 b) │
│         │      │ swap x, y         │
│ a 變 7  │←────│ → a=7, b=3        │
│ b 變 3  │      └───────────────────┘
└─────────┘
```

**範例程式：** `ex9_5_2_pass_by_ref.cpp`

```cpp
#include <iostream>
using namespace std;

void swap(int& x, int& y) {
    int tmp = x; x = y; y = tmp;
}

void normalize(double& val, double lo, double hi) {
    if (val < lo) val = lo;
    if (val > hi) val = hi;
}

// 一次回傳多個結果（用傳參考）
void minmax(const int arr[], int n, int& minVal, int& maxVal) {
    minVal = maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }
}

int main() {
    int a = 3, b = 7;
    cout << "交換前：a=" << a << ", b=" << b << endl;
    swap(a, b);
    cout << "交換後：a=" << a << ", b=" << b << endl;

    double temp = 150.0;
    normalize(temp, 0.0, 100.0);
    cout << "正規化後：" << temp << endl;   // 100

    int scores[] = {85, 42, 96, 73, 61};
    int lo, hi;
    minmax(scores, 5, lo, hi);
    cout << "最小：" << lo << "，最大：" << hi << endl;

    return 0;
}
```

**執行結果：**

```
交換前：a=3, b=7
交換後：a=7, b=3
正規化後：100
最小：42，最大：96
```

### 9.5.3 傳指標（Pass by Pointer）

傳入變數的記憶體位址，函式透過 `*` 解參考來存取原始值。C 語言常用此法；C++ 中通常優先使用傳參考，但 C API 或操作陣列時仍常見指標。

```cpp
void swap(int* px, int* py) {
    int tmp = *px; *px = *py; *py = tmp;
}

// 呼叫時要傳位址
int a = 3, b = 7;
swap(&a, &b);
```

**範例程式：** `ex9_5_3_pass_by_ptr.cpp`

```cpp
#include <iostream>
using namespace std;

void doubleIt(int* p) {
    *p = *p * 2;          // 解參考，修改原始值
}

void fillArray(int* arr, int n, int val) {
    for (int i = 0; i < n; i++)
        arr[i] = val;
}

// 函式可以傳回指標（但不要傳回局部變數的指標！）
int* findMax(int* arr, int n) {
    int* best = arr;
    for (int i = 1; i < n; i++)
        if (arr[i] > *best) best = &arr[i];
    return best;
}

int main() {
    int x = 10;
    cout << "前：x = " << x << endl;
    doubleIt(&x);
    cout << "後：x = " << x << endl;

    int arr[5];
    fillArray(arr, 5, 99);
    for (int i = 0; i < 5; i++) cout << arr[i] << " ";
    cout << endl;

    int data[] = {3, 8, 1, 9, 5};
    int* pMax = findMax(data, 5);
    cout << "最大值：" << *pMax << "，位址：" << pMax << endl;

    return 0;
}
```

**執行結果：**

```
前：x = 10
後：x = 20
99 99 99 99 99
最大值：9，位址：0x...
```

### 9.5.4 三種傳遞方式比較

```
┌──────────────┬──────────────────┬──────────────────┬──────────────────┐
│              │    傳值           │    傳參考         │    傳指標         │
├──────────────┼──────────────────┼──────────────────┼──────────────────┤
│ 語法         │ f(int x)         │ f(int& x)        │ f(int* p)        │
│ 呼叫方式     │ f(a)             │ f(a)             │ f(&a)            │
│ 能修改原值？  │ ❌ 否            │ ✅ 是            │ ✅ 是            │
│ 可為 nullptr？│ ─               │ ❌ 否            │ ✅ 是            │
│ 用途         │ 只讀，保護原值   │ 需要修改，傳大物件│ C API，可能為空  │
└──────────────┴──────────────────┴──────────────────┴──────────────────┘
```

### 9.5.5 const 參數

用 `const` 修飾參數，防止函式內不小心修改。

```cpp
// const 傳值：幾乎無意義（複製品本來就改不到外部）
void f(const int n);

// const 傳參考：常用！避免複製大物件，又防止修改
void printStudent(const Student& s);    // 不複製，不修改

// const 傳指標：防止透過指標修改原始值
void printArray(const int* arr, int n);
```

**範例程式：** `ex9_5_4_const_param.cpp`

```cpp
#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int score;
};

// const& 避免複製整個 struct
void printStudent(const Student& s) {
    // s.score = 100;  // ❌ 編譯錯誤：const 禁止修改
    cout << s.name << "：" << s.score << " 分" << endl;
}

double average(const int* arr, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return sum / n;
}

int main() {
    Student stu = {"Alice", 92};
    printStudent(stu);

    int scores[] = {80, 90, 70, 85, 95};
    cout << "平均：" << average(scores, 5) << endl;

    return 0;
}
```

**執行結果：**

```
Alice：92 分
平均：84
```

### 9.5.6 陣列作為參數

陣列傳入函式時會**退化（decay）** 為指標，失去大小資訊，因此必須額外傳入長度。

```cpp
// 這三種寫法等價（都是傳指標）
void f(int arr[], int n);
void f(int* arr, int n);
void f(int arr[100], int n);  // 100 會被忽略！
```

**範例程式：** `ex9_5_5_array_param.cpp`

```cpp
#include <iostream>
using namespace std;

void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n-1) cout << ", ";
    }
    cout << endl;
}

void reverseArray(int arr[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        int tmp = arr[left];
        arr[left] = arr[right];
        arr[right] = tmp;
        left++; right--;
    }
}

int sumArray(const int arr[], int n) {
    int s = 0;
    for (int i = 0; i < n; i++) s += arr[i];
    return s;
}

int main() {
    int data[] = {1, 2, 3, 4, 5};
    int n = sizeof(data) / sizeof(data[0]);

    cout << "原始："; printArray(data, n);
    cout << "總和：" << sumArray(data, n) << endl;

    reverseArray(data, n);
    cout << "反轉："; printArray(data, n);

    return 0;
}
```

**執行結果：**

```
原始：1, 2, 3, 4, 5
總和：15
反轉：5, 4, 3, 2, 1
```

---

## 9.6 生命遊戲（Conway's Game of Life）

### 9.6.1 規則介紹

**生命遊戲（Game of Life）** 是英國數學家 John Conway 於 1970 年發明的**細胞自動機**。棋盤是一個二維格子，每個格子是「活」（1）或「死」（0）。

每一代的規則：

```
┌──────────────────────────────────────────────────────┐
│                   生命遊戲規則                         │
├──────────────────────────────────────────────────────┤
│ 1. 活細胞 + 鄰居 < 2  → 死亡（孤獨）                  │
│ 2. 活細胞 + 鄰居 = 2 或 3 → 存活                      │
│ 3. 活細胞 + 鄰居 > 3  → 死亡（擁擠）                  │
│ 4. 死細胞 + 鄰居 = 3  → 誕生                          │
└──────────────────────────────────────────────────────┘
```

「鄰居」是周圍 8 個格子中的活細胞數：

```
┌───┬───┬───┐
│ ↖ │ ↑ │ ↗ │
├───┼───┼───┤
│ ← │ ● │ → │   ← 計算 ● 的 8 個鄰居
├───┼───┼───┤
│ ↙ │ ↓ │ ↘ │
└───┴───┴───┘
```

### 9.6.2 程式設計

關鍵思路：每一代結束後才更新，不能邊計算邊修改（否則影響同代其他格）。

```
① 計算每格的新狀態 → 暫存到 next[][]
② 將 next[][] 複製回 board[][]
③ 顯示新的棋盤
```

**範例程式：** `ex9_6_1_game_of_life.cpp`

```cpp
// ex9_6_1_game_of_life.cpp
// Conway's Game of Life

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int ROWS = 20;
const int COLS = 40;

// 計算鄰居數（邊界視為死亡）
int countNeighbors(const int board[][COLS], int r, int c) {
    int count = 0;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;   // 跳過自己
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS)
                count += board[nr][nc];
        }
    }
    return count;
}

// 計算下一代
void nextGeneration(const int board[][COLS], int next[][COLS]) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            int n = countNeighbors(board, r, c);
            if (board[r][c] == 1)
                next[r][c] = (n == 2 || n == 3) ? 1 : 0;   // 存活條件
            else
                next[r][c] = (n == 3) ? 1 : 0;              // 誕生條件
        }
    }
}

// 複製棋盤
void copyBoard(const int src[][COLS], int dst[][COLS]) {
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            dst[r][c] = src[r][c];
}

// 顯示棋盤
void printBoard(const int board[][COLS], int gen) {
    cout << "第 " << gen << " 代：" << endl;
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++)
            cout << (board[r][c] ? "█" : ".");
        cout << endl;
    }
}

// 隨機初始化（約 30% 存活）
void randomInit(int board[][COLS]) {
    srand(42);   // 固定種子，方便重現
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            board[r][c] = (rand() % 10 < 3) ? 1 : 0;
}

// 統計活細胞數
int countAlive(const int board[][COLS]) {
    int cnt = 0;
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            cnt += board[r][c];
    return cnt;
}

int main() {
    int board[ROWS][COLS] = {};
    int next[ROWS][COLS]  = {};

    randomInit(board);

    int generations;
    cout << "模擬幾代？"; cin >> generations;

    for (int gen = 0; gen <= generations; gen++) {
        printBoard(board, gen);
        cout << "存活：" << countAlive(board) << " 個\n" << endl;

        if (gen < generations) {
            nextGeneration(board, next);
            copyBoard(next, board);
        }
    }

    return 0;
}
```

**執行結果（前幾代截圖）：**

```
第 0 代：
.█.█..█..█...
█.█..█.███..
...（20×40 的格子）
存活：237 個

第 1 代：
..██.....█...
...（演化後的格子）
存活：198 個
```

> 💡 **延伸思考：** 著名的「滑翔機（Glider）」是一種會移動的穩定圖案：
>
> ```
> .█.
> ..█
> ███
> ```
>
> 試著用這個初始圖案，觀察它如何在棋盤上移動！

---

## 9.7 鏡子房間（Recursion）

### 9.7.1 函式呼叫自己？

想像你站在兩面對照的鏡子之間，你看到無限個鏡中人。每個鏡中人又看到更遠的鏡中人……

**遞迴（Recursion）** 就是：**函式在自己的主體內呼叫自己**。

```
countdown(3)
  └─ cout 3
  └─ countdown(2)        ← 呼叫自己（n-1）
       └─ cout 2
       └─ countdown(1)
            └─ cout 1
            └─ countdown(0)   ← 到達終止條件
                 └─ return    ← 開始層層回傳
```

### 9.7.2 遞迴的兩個必要條件

```
┌─────────────────────────────────────────────────────────┐
│                   遞迴的兩個必要條件                      │
├──────────────────────┬──────────────────────────────────┤
│  ① 終止條件          │  ② 遞迴步驟                      │
│  (Base Case)         │  (Recursive Case)                │
├──────────────────────┼──────────────────────────────────┤
│  什麼情況下停止呼叫  │  每次呼叫要讓問題「縮小」         │
│  缺少 → 無限遞迴     │  缺少 → 永遠到不了終止條件       │
└──────────────────────┴──────────────────────────────────┘
```

### 9.7.3 鏡子房間的遞迴模型

當你進入一個「鏡子房間」：

- 你往前走 n 步，看到自己的反射
- 反射又往前走 n-1 步
- 直到鏡子距離為 0，才停止反射

這就是遞迴的本質！

**範例程式：** `ex9_7_1_recursion_intro.cpp`

```cpp
#include <iostream>
#include <string>
using namespace std;

// 印出 n 個縮排空格（視覺化遞迴深度）
void indent(int depth) {
    for (int i = 0; i < depth; i++) cout << "  ";
}

void mirrorRoom(int n, int depth = 0) {
    if (n <= 0) {        // ① 終止條件
        indent(depth);
        cout << "[鏡子底部，開始反射]" << endl;
        return;
    }
    indent(depth);
    cout << "→ 進入第 " << n << " 層鏡子" << endl;
    mirrorRoom(n - 1, depth + 1);    // ② 遞迴步驟（n 縮小）
    indent(depth);
    cout << "← 從第 " << n << " 層反射回來" << endl;
}

int main() {
    cout << "=== 鏡子房間（深度=4）===" << endl;
    mirrorRoom(4);
    return 0;
}
```

**執行結果：**

```
=== 鏡子房間（深度=4）===
→ 進入第 4 層鏡子
  → 進入第 3 層鏡子
    → 進入第 2 層鏡子
      → 進入第 1 層鏡子
        [鏡子底部，開始反射]
      ← 從第 1 層反射回來
    ← 從第 2 層反射回來
  ← 從第 3 層反射回來
← 從第 4 層反射回來
```

### 9.7.4 遞迴的經典應用

#### 階乘（Factorial）

```
n! = n × (n-1)!          （遞迴步驟）
0! = 1                    （終止條件）
```

**範例程式：** `ex9_7_2_factorial.cpp`

```cpp
#include <iostream>
using namespace std;

long long factorial(int n) {
    if (n <= 0) return 1;           // 終止條件
    return n * factorial(n - 1);   // 遞迴步驟
}

// 對照：用迴圈實作
long long factIter(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) result *= i;
    return result;
}

int main() {
    for (int i = 0; i <= 10; i++)
        cout << i << "! = " << factorial(i) << endl;

    return 0;
}
```

**執行結果：**

```
0! = 1
1! = 1
2! = 2
3! = 6
4! = 24
5! = 120
6! = 720
7! = 5040
8! = 40320
9! = 362880
10! = 3628800
```

#### 費波那契數列（Fibonacci）

```
F(0) = 0, F(1) = 1
F(n) = F(n-1) + F(n-2)   （n ≥ 2）
```

> ⚠️ **效能警告：** 單純遞迴的費波那契重複計算大量子問題，F(40) 需要數十億次呼叫！

**範例程式：** `ex9_7_3_fibonacci.cpp`

```cpp
#include <iostream>
using namespace std;

// 單純遞迴（效能差，但清晰）
int fibRec(int n) {
    if (n <= 1) return n;
    return fibRec(n-1) + fibRec(n-2);
}

// 記憶化（Memoization）：用陣列記錄已算過的值
int memo[50] = {};
int fibMemo(int n) {
    if (n <= 1) return n;
    if (memo[n] != 0) return memo[n];   // 已算過，直接取用
    memo[n] = fibMemo(n-1) + fibMemo(n-2);
    return memo[n];
}

// 迴圈版（最快）
int fibIter(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        int c = a + b; a = b; b = c;
    }
    return b;
}

int main() {
    for (int i = 0; i <= 15; i++)
        cout << "F(" << i << ") = " << fibRec(i) << endl;

    return 0;
}
```

**執行結果：**

```
F(0) = 0
F(1) = 1
F(2) = 1
F(3) = 2
...
F(15) = 610
```

#### 漢諾塔（Tower of Hanoi）

3 根柱子 A、B、C，把 n 個圓盤從 A 移到 C，每次只能移一個，且不可大盤壓小盤。

```
移 n 個盤從 A 到 C（用 B 輔助）：
  ① 把 n-1 個盤從 A 移到 B（用 C 輔助）
  ② 把最大盤從 A 移到 C
  ③ 把 n-1 個盤從 B 移到 C（用 A 輔助）
```

**範例程式：** `ex9_7_4_hanoi.cpp`

```cpp
#include <iostream>
using namespace std;

int moves = 0;

void hanoi(int n, char from, char to, char aux) {
    if (n == 0) return;                    // 終止條件
    hanoi(n-1, from, aux, to);            // ① A→B
    cout << "移動圓盤 " << n
         << "：" << from << " → " << to << endl;
    moves++;
    hanoi(n-1, aux, to, from);            // ③ B→C
}

int main() {
    int n;
    cout << "圓盤數："; cin >> n;
    hanoi(n, 'A', 'C', 'B');
    cout << "共移動 " << moves << " 次（= 2^"
         << n << "-1 = " << ((1 << n) - 1) << "）" << endl;
    return 0;
}
```

**執行結果（n=3）：**

```
移動圓盤 1：A → C
移動圓盤 2：A → B
移動圓盤 1：C → B
移動圓盤 3：A → C
移動圓盤 1：B → A
移動圓盤 2：B → C
移動圓盤 1：A → C
共移動 7 次（= 2^3-1 = 7）
```

> 💡 **遞迴 vs 迴圈：** 遞迴程式碼簡潔優美，但每次呼叫都要用記憶體存放函式堆疊（Stack Frame）。對於深度遞迴，可能導致 **Stack Overflow**。實務上，如果能用迴圈，通常優先選迴圈；遞迴最適合天然具有遞迴結構的問題（樹、圖、分治演算法）。

### 9.7.5 遞迴的執行堆疊

每次函式呼叫，系統會在「**呼叫堆疊（Call Stack）**」中放入一個 **堆疊框架（Stack Frame）**：

```
factorial(4) 的呼叫堆疊（從下往上疊）：

┌────────────────────┐  ← 最頂端（最後被呼叫）
│ factorial(1)       │  → return 1
├────────────────────┤
│ factorial(2)       │  → return 2 × 1 = 2
├────────────────────┤
│ factorial(3)       │  → return 3 × 2 = 6
├────────────────────┤
│ factorial(4)       │  → return 4 × 6 = 24
├────────────────────┤
│    main()          │  ← 最底端（最先被呼叫）
└────────────────────┘
```

---

## 9.8 井字遊戲（Tic-Tac-Toe）

### 9.8.1 設計思路

井字遊戲是練習函式分解的好範例。我們把整個程式拆成多個職責清晰的函式：

```
main()
 ├─ initBoard()          → 初始化棋盤
 ├─ printBoard()         → 顯示棋盤
 ├─ getMove()            → 取得玩家輸入
 ├─ isValidMove()        → 驗證輸入合法
 ├─ applyMove()          → 落子
 ├─ checkWin()           → 判斷獲勝
 ├─ isBoardFull()        → 判斷平局
 └─ switchPlayer()       → 切換玩家
```

每個函式**只做一件事**，這是良好程式設計的基本原則（Single Responsibility Principle）。

### 9.8.2 完整實作

**範例程式：** `ex9_8_1_tictactoe.cpp`

```cpp
// ex9_8_1_tictactoe.cpp
// 井字遊戲：以函式分解每個職責

#include <iostream>
using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE];

// ① 初始化棋盤
void initBoard() {
    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++)
            board[r][c] = '1' + r * SIZE + c;  // '1'~'9'
}

// ② 顯示棋盤
void printBoard() {
    cout << "┌───┬───┬───┐" << endl;
    for (int r = 0; r < SIZE; r++) {
        cout << "│";
        for (int c = 0; c < SIZE; c++)
            cout << " " << board[r][c] << " │";
        cout << endl;
        if (r < SIZE-1)
            cout << "├───┼───┼───┤" << endl;
    }
    cout << "└───┴───┴───┘" << endl;
}

// ③ 驗證輸入（1~9，且未被佔用）
bool isValidMove(int pos) {
    if (pos < 1 || pos > 9) return false;
    int r = (pos - 1) / SIZE;
    int c = (pos - 1) % SIZE;
    return board[r][c] != 'X' && board[r][c] != 'O';
}

// ④ 落子
void applyMove(int pos, char player) {
    int r = (pos - 1) / SIZE;
    int c = (pos - 1) % SIZE;
    board[r][c] = player;
}

// ⑤ 判斷獲勝
bool checkWin(char player) {
    // 橫列
    for (int r = 0; r < SIZE; r++) {
        bool win = true;
        for (int c = 0; c < SIZE; c++)
            if (board[r][c] != player) { win = false; break; }
        if (win) return true;
    }
    // 縱行
    for (int c = 0; c < SIZE; c++) {
        bool win = true;
        for (int r = 0; r < SIZE; r++)
            if (board[r][c] != player) { win = false; break; }
        if (win) return true;
    }
    // 對角線
    bool d1 = true, d2 = true;
    for (int i = 0; i < SIZE; i++) {
        if (board[i][i]         != player) d1 = false;
        if (board[i][SIZE-1-i]  != player) d2 = false;
    }
    return d1 || d2;
}

// ⑥ 判斷平局（棋盤滿）
bool isBoardFull() {
    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++)
            if (board[r][c] != 'X' && board[r][c] != 'O')
                return false;
    return true;
}

// ⑦ 切換玩家
char switchPlayer(char current) {
    return (current == 'X') ? 'O' : 'X';
}

// ⑧ 取得合法輸入
int getMove(char player) {
    int pos;
    while (true) {
        cout << "玩家 " << player << " 請輸入位置（1~9）：";
        cin >> pos;
        if (isValidMove(pos)) return pos;
        cout << "非法位置，請重新輸入！" << endl;
    }
}

int main() {
    cout << "=== 井字遊戲 ===" << endl;
    cout << "位置編號如左，X 先手" << endl << endl;

    initBoard();
    printBoard();

    char current = 'X';
    while (true) {
        int pos = getMove(current);
        applyMove(pos, current);

        cout << endl;
        printBoard();

        if (checkWin(current)) {
            cout << "\n玩家 " << current << " 獲勝！🎉" << endl;
            break;
        }
        if (isBoardFull()) {
            cout << "\n平局！" << endl;
            break;
        }

        current = switchPlayer(current);
    }

    return 0;
}
```

**執行結果：**

```
=== 井字遊戲 ===
位置編號如左，X 先手

┌───┬───┬───┐
│ 1 │ 2 │ 3 │
├───┼───┼───┤
│ 4 │ 5 │ 6 │
├───┼───┼───┤
│ 7 │ 8 │ 9 │
└───┴───┴───┘
玩家 X 請輸入位置（1~9）：5

┌───┬───┬───┐
│ 1 │ 2 │ 3 │
├───┼───┼───┤
│ 4 │ X │ 6 │
├───┼───┼───┤
│ 7 │ 8 │ 9 │
└───┴───┴───┘
玩家 O 請輸入位置（1~9）：1
...（遊戲繼續）
```

### 9.8.3 N×N 版本（進階）

將棋盤大小設為可變，挑戰更大的棋盤。

**範例程式：** `ex9_8_2_tictactoe_n.cpp`

```cpp
// ex9_8_2_tictactoe_n.cpp
// 可自訂大小的 N×N 井字遊戲（需連 winLen 個）

#include <iostream>
using namespace std;

const int MAXN = 10;
int SIZE, WIN_LEN;
char board[MAXN][MAXN];

void initBoard() {
    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++)
            board[r][c] = '.';
}

void printBoard() {
    cout << "  ";
    for (int c = 0; c < SIZE; c++) cout << c+1 << " ";
    cout << endl;
    for (int r = 0; r < SIZE; r++) {
        cout << r+1 << " ";
        for (int c = 0; c < SIZE; c++) cout << board[r][c] << " ";
        cout << endl;
    }
}

bool isValid(int r, int c) {
    return r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c] == '.';
}

bool checkDirection(int r, int c, int dr, int dc, char p) {
    for (int i = 0; i < WIN_LEN; i++) {
        int nr = r + i * dr, nc = c + i * dc;
        if (nr < 0 || nr >= SIZE || nc < 0 || nc >= SIZE) return false;
        if (board[nr][nc] != p) return false;
    }
    return true;
}

bool checkWin(char p) {
    int dirs[4][2] = {{0,1},{1,0},{1,1},{1,-1}};
    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++)
            for (auto& d : dirs)
                if (checkDirection(r, c, d[0], d[1], p)) return true;
    return false;
}

bool isFull() {
    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++)
            if (board[r][c] == '.') return false;
    return true;
}

int main() {
    cout << "棋盤大小 N（3~10）："; cin >> SIZE;
    cout << "幾連 獲勝？"; cin >> WIN_LEN;

    initBoard();
    char cur = 'X';

    while (true) {
        printBoard();
        int r, c;
        cout << "玩家 " << cur << "（列 行）：";
        cin >> r >> c;
        r--; c--;
        if (!isValid(r, c)) { cout << "非法！\n"; continue; }
        board[r][c] = cur;
        if (checkWin(cur)) { printBoard(); cout << cur << " 獲勝！\n"; break; }
        if (isFull())       { printBoard(); cout << "平局！\n"; break; }
        cur = (cur == 'X') ? 'O' : 'X';
    }

    return 0;
}
```

---

## 9.9 結語

### 本章回顧

本章我們從「呼叫現有函式」出發，一步步學會如何定義自己的函式，最終用函式分解出三個完整程式：

```
第九章知識樹
函式
├── 9.1 呼叫函式
│   ├── 標準函式庫（cmath, algorithm, cstdlib）
│   └── 函式原型 vs 定義
├── 9.2 有回傳值的函式
│   ├── return 語法
│   └── 多種回傳型別
├── 9.3 無回傳值的函式（void）
│   └── return; 提前結束
├── 9.4 多個參數
│   ├── 多參數語法
│   ├── 預設引數（右到左）
│   └── 函式重載
├── 9.5 參數傳遞
│   ├── 傳值（複製，不影響外部）
│   ├── 傳參考（別名，影響外部）
│   ├── 傳指標（位址，影響外部）
│   ├── const 參數（防止意外修改）
│   └── 陣列參數（退化為指標）
├── 9.6 生命遊戲（函式分解 + 2D 陣列）
├── 9.7 鏡子房間（遞迴）
│   ├── 終止條件 + 遞迴步驟
│   ├── 階乘、費波那契、漢諾塔
│   └── 呼叫堆疊（Stack Frame）
└── 9.8 井字遊戲（函式分解設計）
    └── 單一職責原則
```

### 函式設計原則

| 原則                | 說明                   | 反例                       |
| ------------------- | ---------------------- | -------------------------- |
| **單一職責**        | 每個函式只做一件事     | 一個函式又輸入又計算又輸出 |
| **有意義的名稱**    | 名稱說明函式做什麼     | `f1()`, `doStuff()`        |
| **參數不超過 5 個** | 太多參數難以使用       | `f(a,b,c,d,e,g,h)`         |
| **避免全域變數**    | 優先用參數傳遞         | 大量全域狀態               |
| **const 保護**      | 不需修改的參數加 const | 無 const 的大型結構參考    |

---

## 實作練習

> 以下習題難易度由淺到深，建議依序完成。標注 ★ 為較具挑戰性題目。

### 練習 9-1：溫度轉換函式

撰寫三個函式：

- `double celsiusToFahrenheit(double c)` — 攝氏轉華氏（F = C × 9/5 + 32）
- `double fahrenheitToCelsius(double f)` — 華氏轉攝氏
- `double celsiusToKelvin(double c)` — 攝氏轉克氏（K = C + 273.15）

主程式讓使用者輸入溫度和單位，輸出三種換算結果。

---

### 練習 9-2：字串處理函式

撰寫以下函式（不得使用 `<algorithm>` 或 `<string>` 的成員函式，僅能用索引操作）：

- `int strLen(const char* s)` — 計算字串長度
- `bool isPalindrome(const string& s)` — 判斷迴文（忽略大小寫）
- `int countChar(const string& s, char c)` — 計算字元出現次數

---

### 練習 9-3：數學函式庫

實作以下數學函式（不使用 `<cmath>`）：

- `long long power(long long base, int exp)` — 整數次方（exp ≥ 0）
- `double mysqrt(double n)` — 牛頓法求平方根（誤差 < 1e-9）
- `int gcd(int a, int b)` — 輾轉相除法求最大公因數
- `int lcm(int a, int b)` — 最小公倍數（利用 gcd）

---

### 練習 9-4：陣列操作函式

實作：

- `void bubbleSort(int arr[], int n)` — 泡沫排序（由小到大）
- `int binarySearch(const int arr[], int n, int target)` — 二分搜尋（傳回索引，找不到傳回 -1）
- `double standardDeviation(const int arr[], int n)` — 標準差

用這些函式實作：輸入 n 個成績 → 排序 → 二分搜尋特定分數 → 計算標準差。

---

### 練習 9-5：傳參考練習

實作以下函式，所有輸出結果透過參考傳回：

- `void swap3(int& a, int& b, int& c)` — 將 a, b, c 旋轉（a→b, b→c, c→a）
- `void splitNum(double x, int& intPart, double& fracPart)` — 分離整數與小數部分
- `bool quadratic(double a, double b, double c, double& x1, double& x2)` — 求一元二次方程式的根（有解傳回 true，無實數解傳回 false）

---

### 練習 9-6：遞迴練習 ★

用遞迴實作：

- `int sumDigits(int n)` — 各位數字之和（如 1234 → 10）
- `bool isPalindrome(int n)` — 整數迴文判斷（如 1221 是，1234 否）
- `void printBinary(int n)` — 印出 n 的二進位表示（不用陣列）
- `int power(int base, int exp)` — 遞迴快速冪（每次 exp/2）

---

### 練習 9-7：井字遊戲 AI ★

在 9.8 的井字遊戲基礎上，新增一個簡單的 AI 玩家：

1. **優先獲勝：** 如果能一步獲勝，就下那裡
2. **防守：** 如果對手下一步能獲勝，就擋住
3. **其他：** 隨機選一個空格

新增函式：

- `int findWinningMove(char player)` — 找能獲勝的位置
- `int aiMove(char aiPlayer, char humanPlayer)` — AI 決策

---

### 練習 9-8：數字謎題（神奇函式）★★

一個 n 位的**自戀數（Narcissistic Number）** 滿足：各位數字的 n 次方之和等於本身。
例如：153 = 1³ + 5³ + 3³。

撰寫：

- `bool isNarcissistic(int n)` — 判斷 n 是否為自戀數
- `int digitCount(int n)` — 計算 n 的位數
- `long long digitPowerSum(int n)` — 各位數的「位數次方」之和

找出所有 3 位數自戀數（100~999）。

---

## 面試考題

### 問題一：傳值、傳參考、傳指標的差異是什麼？各適合什麼場合？

**參考答案：**

| 方式   | 語法        | 能修改原值 | 典型場合                       |
| ------ | ----------- | ---------- | ------------------------------ |
| 傳值   | `f(int x)`  | 否         | 基本型別的唯讀存取             |
| 傳參考 | `f(int& x)` | 是         | 需修改原值，或避免複製大物件   |
| 傳指標 | `f(int* x)` | 是         | C API 相容，或引數可為 nullptr |

選用原則：

1. 基本型別（int、double）只需讀取 → **傳值**
2. 需要讓函式修改外部變數 → **傳參考**
3. 大型物件只需讀取 → **const 傳參考（const T&）**
4. 引數可能為空 → **傳指標（加 nullptr 檢查）**

---

### 問題二：遞迴有哪些優缺點？遞迴和迴圈怎麼選擇？

**參考答案：**

|          | 遞迴                                                  | 迴圈                    |
| -------- | ----------------------------------------------------- | ----------------------- |
| **優點** | 程式碼簡潔，貼近數學定義                              | 效能好，不佔 Stack 空間 |
| **缺點** | 每次呼叫要建立 Stack Frame，深度過大會 Stack Overflow | 有時難以表達遞迴結構    |

**選擇原則：**

- 問題天然具有遞迴結構（樹、圖、分治演算法）→ 遞迴更自然
- 可以輕鬆改寫成迴圈 → 優先選迴圈（效能更好）
- 深度不確定的問題 → 小心 Stack Overflow（考慮改成尾遞迴或迭代）

---

### 問題三：什麼是函式重載（Overloading）？編譯器如何決定呼叫哪個版本？

**參考答案：**

函式重載允許同名函式有不同的參數列（型別或個數不同）。

編譯器在**編譯期**根據呼叫時的引數型別與個數，選擇最匹配的版本（稱為「**名稱解析（Name Mangling）**」）。

```cpp
void print(int n);
void print(double d);
void print(string s);

print(42);      // → print(int)
print(3.14);    // → print(double)
print("hi");    // → print(string)
```

**注意：** 僅回傳型別不同無法重載（編譯器靠參數判斷，不靠回傳型別）。

---

### 問題四：陣列傳入函式後，為什麼不知道自己的大小？

**參考答案：**

陣列名稱傳入函式時會**退化（Decay）** 為指向第一個元素的指標，失去陣列大小資訊。

```cpp
void f(int arr[]) {
    // 在這裡 sizeof(arr) == sizeof(int*) == 8（64位元）
    // 不是陣列的總大小！
}

int data[10] = {};
// sizeof(data) == 40（10 × 4 bytes）
f(data);  // 傳入後只有指標，失去大小資訊
```

**解決方案：**

1. 額外傳入 `int n`（陣列長度）
2. 用 `std::array<int, 10>`（C++11，保留大小）
3. 用 `std::vector<int>`（動態大小）

---

### 問題五：什麼是「呼叫堆疊（Call Stack）」？為什麼無限遞迴會導致程式崩潰？

**參考答案：**

**呼叫堆疊（Call Stack）** 是作業系統為每個執行緒分配的一塊記憶體區域，專門用於儲存函式呼叫的狀態。每次呼叫函式，系統會 push 一個**堆疊框架（Stack Frame）**，包含：

- 局部變數的值
- 回傳位址（函式執行完要回到哪裡）
- 傳入的引數

Call Stack 的大小是有限的（通常 1~8 MB）。無限遞迴沒有終止條件，Stack Frame 不斷堆疊，最終超出 Stack 的上限，導致 **Stack Overflow**，程式崩潰。

---

## 專案：計算機模擬器

> 用函式分解設計一個完整的指令行計算機，可以當作作品集展示「函式設計能力」。

### 功能需求

1. **基本運算：** `+`, `-`, `*`, `/`, `%`（整數取餘）
2. **數學函式：** `sqrt`, `pow`, `abs`, `log`（自然對數）
3. **歷史記錄：** 最近 10 筆計算結果
4. **變數：** 可將結果存入 A~Z 的變數，並在後續計算中使用
5. **指令：**
    - `help` — 顯示說明
    - `history` — 顯示計算歷史
    - `vars` — 顯示所有已設定的變數
    - `quit` — 離開

### 範例互動

```
計算機 v1.0（輸入 help 查看說明）
> 3 + 4
= 7
> sqrt 25
= 5
> pow 2 10
= 1024
> store A
A = 1024
> A * 2
= 2048
> history
[1] 3 + 4 = 7
[2] sqrt 25 = 5
[3] pow 2 10 = 1024
[4] A * 2 = 2048
> quit
再見！
```

### 函式架構

```cpp
// 顯示說明
void showHelp();

// 解析輸入（判斷是哪種指令）
int parseInput(const string& input, string& op, double& a, double& b);

// 執行二元運算（+,-,*,/,%）
double evalBinary(const string& op, double a, double b, bool& ok);

// 執行一元數學函式（sqrt, abs, log...）
double evalUnary(const string& func, double a, bool& ok);

// 歷史記錄
void addHistory(const string& expr, double result);
void showHistory();

// 變數管理
void storeVar(char name, double val);
double loadVar(char name, bool& ok);
void showVars();
```

**解答程式碼：** `project9_calculator_answer.cpp`

```cpp
// project9_calculator_answer.cpp
// 計算機模擬器：函式分解設計

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

// ── 歷史記錄 ──────────────────────────────────────
const int MAX_HIST = 10;
string histExprs[MAX_HIST];
double histVals[MAX_HIST];
int    histCount = 0;

void addHistory(const string& expr, double result) {
    if (histCount < MAX_HIST) {
        histExprs[histCount] = expr;
        histVals[histCount]  = result;
        histCount++;
    } else {
        for (int i = 0; i < MAX_HIST-1; i++) {
            histExprs[i] = histExprs[i+1];
            histVals[i]  = histVals[i+1];
        }
        histExprs[MAX_HIST-1] = expr;
        histVals[MAX_HIST-1]  = result;
    }
}

void showHistory() {
    if (histCount == 0) { cout << "（無歷史記錄）" << endl; return; }
    for (int i = 0; i < histCount; i++)
        cout << "[" << i+1 << "] " << histExprs[i]
             << " = " << histVals[i] << endl;
}

// ── 變數 ──────────────────────────────────────────
double vars[26];
bool   varSet[26] = {};

void storeVar(char name, double val) {
    int idx = toupper(name) - 'A';
    vars[idx]   = val;
    varSet[idx] = true;
    cout << (char)toupper(name) << " = " << val << endl;
}

double loadVar(char name, bool& ok) {
    int idx = toupper(name) - 'A';
    ok = varSet[idx];
    return ok ? vars[idx] : 0.0;
}

void showVars() {
    bool any = false;
    for (int i = 0; i < 26; i++) {
        if (varSet[i]) {
            cout << (char)('A'+i) << " = " << vars[i] << endl;
            any = true;
        }
    }
    if (!any) cout << "（無已設定的變數）" << endl;
}

// ── 計算 ──────────────────────────────────────────
double evalBinary(const string& op, double a, double b, bool& ok) {
    ok = true;
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) { cout << "除以零！" << endl; ok = false; return 0; }
        return a / b;
    }
    if (op == "%") {
        if ((int)b == 0) { cout << "取餘除以零！" << endl; ok = false; return 0; }
        return (int)a % (int)b;
    }
    ok = false; return 0;
}

double evalUnary(const string& fn, double a, bool& ok) {
    ok = true;
    if (fn == "sqrt") {
        if (a < 0) { cout << "負數無法開根！" << endl; ok = false; return 0; }
        return sqrt(a);
    }
    if (fn == "abs")  return abs(a);
    if (fn == "log")  {
        if (a <= 0) { cout << "對數定義域錯誤！" << endl; ok = false; return 0; }
        return log(a);
    }
    if (fn == "sin")  return sin(a * M_PI / 180.0);  // 角度轉弧度
    if (fn == "cos")  return cos(a * M_PI / 180.0);
    if (fn == "ceil") return ceil(a);
    if (fn == "floor")return floor(a);
    ok = false; return 0;
}

// ── 解析引數（可能是數字或變數名稱）──────────────
double parseOperand(const string& token, bool& ok) {
    ok = true;
    // 單個字母 → 視為變數
    if (token.size() == 1 && isalpha(token[0])) {
        return loadVar(token[0], ok);
    }
    // 嘗試轉換為數字
    try {
        return stod(token);
    } catch (...) {
        ok = false;
        return 0;
    }
}

// ── 說明 ──────────────────────────────────────────
void showHelp() {
    cout << "┌────────────────────────────────────────┐" << endl;
    cout << "│            計算機說明                    │" << endl;
    cout << "├────────────────────────────────────────┤" << endl;
    cout << "│ 二元：a + b  a - b  a * b  a / b  a % b│" << endl;
    cout << "│ 一元：sqrt n  abs n  log n              │" << endl;
    cout << "│       sin n  cos n  ceil n  floor n     │" << endl;
    cout << "│ 次方：pow a b  (= a^b)                  │" << endl;
    cout << "│ 變數：store X  (把上一個結果存入 X)      │" << endl;
    cout << "│ 指令：history  vars  help  quit          │" << endl;
    cout << "└────────────────────────────────────────┘" << endl;
}

int main() {
    cout << "計算機 v1.0（輸入 help 查看說明）" << endl;

    double lastResult = 0;
    string line;

    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;

        if (line.empty()) continue;

        // 特殊指令
        if (line == "quit" || line == "exit") {
            cout << "再見！" << endl; break;
        }
        if (line == "help")    { showHelp();    continue; }
        if (line == "history") { showHistory(); continue; }
        if (line == "vars")    { showVars();    continue; }

        istringstream ss(line);
        string token1, token2, token3;
        ss >> token1;

        // store X
        if (token1 == "store") {
            if (!(ss >> token2) || token2.size() != 1 || !isalpha(token2[0])) {
                cout << "格式：store <字母>" << endl;
            } else {
                storeVar(token2[0], lastResult);
            }
            continue;
        }

        bool ok1, ok2, ok;
        double result;

        // 嘗試一元函式：fn a
        if (token1 == "sqrt" || token1 == "abs" || token1 == "log" ||
            token1 == "sin"  || token1 == "cos" || token1 == "ceil" ||
            token1 == "floor") {
            if (!(ss >> token2)) { cout << "格式：" << token1 << " <數字>" << endl; continue; }
            double a = parseOperand(token2, ok1);
            if (!ok1) { cout << "無效的運算元：" << token2 << endl; continue; }
            result = evalUnary(token1, a, ok);
            if (!ok) continue;
            cout << "= " << result << endl;
            addHistory(line, result);
            lastResult = result;
            continue;
        }

        // 嘗試 pow a b
        if (token1 == "pow") {
            if (!(ss >> token2 >> token3)) { cout << "格式：pow <a> <b>" << endl; continue; }
            double a = parseOperand(token2, ok1);
            double b = parseOperand(token3, ok2);
            if (!ok1 || !ok2) { cout << "無效的運算元" << endl; continue; }
            result = pow(a, b);
            cout << "= " << result << endl;
            addHistory(line, result);
            lastResult = result;
            continue;
        }

        // 嘗試二元：a op b
        if (!(ss >> token2 >> token3)) {
            cout << "無法解析：" << line << "（輸入 help）" << endl; continue;
        }
        double a = parseOperand(token1, ok1);
        double b = parseOperand(token3, ok2);
        if (!ok1) { cout << "無效的運算元：" << token1 << endl; continue; }
        if (!ok2) { cout << "無效的運算元：" << token3 << endl; continue; }
        result = evalBinary(token2, a, b, ok);
        if (!ok) continue;
        cout << "= " << result << endl;
        addHistory(line, result);
        lastResult = result;
    }

    return 0;
}
```
