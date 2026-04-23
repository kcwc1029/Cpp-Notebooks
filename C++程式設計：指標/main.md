# 第十章：指標（Pointer）

> **學習目標**
> - 理解記憶體位址的概念，掌握指標變數的宣告與使用
> - 熟練 `&`（取址）與 `*`（解參考）兩個核心運算子
> - 能以指標作為函式參數，實現「傳址呼叫」修改外部變數
> - 理解陣列名稱即指標，活用指標算術走訪陣列
> - 掌握動態記憶體配置（`new`/`delete`），並養成防止洩漏的習慣
> - 認識常見指標陷阱（野指標、懸置指標、空指標解參考），學會防禦策略
> - 了解現代 C++ 的安全替代方案（`unique_ptr`、`shared_ptr`）

---

## 10.0 為什麼需要指標？

學到這裡，你已經可以宣告變數、寫函式、使用陣列。但有些問題，沒有指標就做不到：

**問題一：函式無法修改外部變數**
```cpp
void double_it(int x) {
    x = x * 2;   // 只改了副本，外面的變數沒變！
}
```

**問題二：陣列大小必須在編譯時決定**
```cpp
int n;
cin >> n;
int arr[n];   // 許多編譯器不允許，也不安全
```

**問題三：無法實作鏈結串列、樹等資料結構**
```
節點 A → 節點 B → 節點 C   （需要指向下一個節點的「指標」）
```

**指標（Pointer）** 讓你直接操作記憶體位址，是 C/C++ 最強大也最需要謹慎的工具。

```
                    ┌─────────────────────────────────────┐
                    │           記憶體（Memory）           │
                    │                                     │
  變數 x ─────────→ │ 位址 0x1A4C │ 值：42              │
                    │                                     │
  指標 p ─────────→ │ 位址 0x2B60 │ 值：0x1A4C ────────→│→ 指向 x
                    │                                     │
                    └─────────────────────────────────────┘

  p 儲存的是 x 的「位址」，透過 p 可以間接存取 x 的值
```

---

## 10.1 指標變數

### 10.1.1 記憶體位址的概念

程式中每個變數都佔據記憶體中的一塊空間，這塊空間有一個**位址（Address）**，就像每棟房子都有門牌號碼。

```
  記憶體示意圖（簡化）：

  位址      內容      變數名
  ──────────────────────────
  0x1000  │  42  │  ← int x
  0x1004  │  3.14│  ← double y（實際佔 8 bytes）
  0x100C  │ 'A'  │  ← char c
  ...
```

- 每個`int`通常占 **4 bytes**，所以相鄰 int 位址差 4
- 位址通常以**十六進位**表示（如 `0x1A4C`）
- `&` 運算子可以取得變數的位址

### 10.1.2 宣告指標變數

```cpp
型別 *指標名稱;     // 宣告一個指向「型別」的指標
```

| 宣告 | 意義 |
|------|------|
| `int *p;` | p 可以儲存一個 `int` 變數的位址 |
| `double *q;` | q 可以儲存一個 `double` 變數的位址 |
| `char *s;` | s 可以儲存一個 `char` 變數的位址 |

> ⚠️ **風格提示：** `int* p;` 和 `int *p;` 都合法，但宣告多個變數時要注意：
> ```cpp
> int* a, b;    // a 是指標，b 是普通 int！
> int *a, *b;   // a 和 b 都是指標（推薦此寫法）
> ```

### 10.1.3 取址運算子 `&`

`&` 放在變數前面，取得該變數的**記憶體位址**：

```cpp
int x = 42;
cout << &x;    // 輸出類似：0x7ffd5e3a1b4c（每次執行可能不同）
```

### 10.1.4 解參考運算子 `*`

`*` 放在指標前面，取得該指標**所指向的值**（透過位址存取變數）：

```cpp
int x = 42;
int *p = &x;   // p 存著 x 的位址

cout << p;     // 輸出位址：0x7ffd...
cout << *p;    // 輸出值：42    （解參考，取得 x 的內容）

*p = 100;      // 透過指標修改 x 的值
cout << x;     // 輸出：100（x 真的被改了！）
```

```
執行流程：
  int x = 42;   →  記憶體 [0x1000] = 42
  int *p = &x;  →  p = 0x1000（p 儲存 x 的位址）
  *p = 100;     →  到位址 0x1000，把那裡的值改成 100
  cout << x;    →  x 的值已是 100
```

📄 **範例檔案：** [ex10_1_1_pointer_basic.cpp](examples/ex10_1_1_pointer_basic.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 42;
    int *p = &x;   // p 指向 x

    cout << "x 的值：" << x << endl;
    cout << "x 的位址：" << &x << endl;
    cout << "p 儲存的位址：" << p << endl;
    cout << "*p（解參考）：" << *p << endl;

    *p = 100;      // 透過指標修改 x
    cout << "\n修改後：" << endl;
    cout << "x = " << x << endl;
    cout << "*p = " << *p << endl;

    return 0;
}
```

**執行結果：**
```
x 的值：42
x 的位址：0x7ffd5e3a1b4c
p 儲存的位址：0x7ffd5e3a1b4c
*p（解參考）：42

修改後：
x = 100
*p = 100
```

### 10.1.5 各型別指標

不同型別的指標，解參考時讀取的 bytes 數不同：

📄 **範例檔案：** [ex10_1_2_pointer_types.cpp](examples/ex10_1_2_pointer_types.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int    i = 10;
    double d = 3.14;
    char   c = 'A';

    int    *pi = &i;
    double *pd = &d;
    char   *pc = &c;

    cout << "int    大小：" << sizeof(int)    << " bytes，*pi = " << *pi << endl;
    cout << "double 大小：" << sizeof(double) << " bytes，*pd = " << *pd << endl;
    cout << "char   大小：" << sizeof(char)   << " bytes，*pc = " << *pc << endl;

    cout << "\n指標本身大小（都是 " << sizeof(pi) << " bytes）" << endl;

    return 0;
}
```

**執行結果：**
```
int    大小：4 bytes，*pi = 10
double 大小：8 bytes，*pd = 3.14
char   大小：1 bytes，*pc = A

指標本身大小（都是 8 bytes）
```

> 💡 **重要觀念：** 不管指向什麼型別，指標本身的大小在 64 位元系統上都是 **8 bytes**（儲存位址用）。型別的作用是告訴編譯器「解參考時要讀幾個 bytes」。

### 10.1.6 空指標 `nullptr`

未初始化的指標是**危險的**！它可能指向任意位址，解參考會造成程式崩潰。

```cpp
int *p;    // 危險！p 的值是垃圾（未初始化）
*p = 5;   // 可能造成程式崩潰（Segmentation Fault）
```

**正確做法：** 指標不用時指向 `nullptr`（C++11 以後），並在使用前檢查：

```cpp
int *p = nullptr;   // 安全：明確表示「現在不指向任何東西」

if (p != nullptr) {
    *p = 5;         // 確認不是 nullptr 才解參考
}
```

📄 **範例檔案：** [ex10_1_3_nullptr_safety.cpp](examples/ex10_1_3_nullptr_safety.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int *p = nullptr;

    cout << "p 的值：" << p << endl;   // 輸出 0

    if (p == nullptr) {
        cout << "p 是空指標，不能解參考" << endl;
    }

    int x = 99;
    p = &x;   // 現在 p 指向 x

    if (p != nullptr) {
        cout << "p 指向的值：" << *p << endl;
    }

    p = nullptr;   // 用完後設回 nullptr（良好習慣）
    return 0;
}
```

**執行結果：**
```
p 的值：0
p 是空指標，不能解參考
p 指向的值：99
```

### 10.1.7 指向指標的指標（雙重指標）

指標本身也是變數，所以可以有「指向指標的指標」：

```cpp
int x = 5;
int *p = &x;    // p 指向 x
int **pp = &p;  // pp 指向 p

cout << x;    // 5
cout << *p;   // 5（透過 p）
cout << **pp; // 5（透過 pp → p → x）
```

```
  pp ──→ p ──→ x
  位址 C   位址 B   位址 A
  值：B    值：A    值：5
```

📄 **範例檔案：** [ex10_1_4_double_pointer.cpp](examples/ex10_1_4_double_pointer.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 5;
    int *p = &x;
    int **pp = &p;

    cout << "x   = " << x    << "，位址：" << &x  << endl;
    cout << "*p  = " << *p   << "，p 儲存：" << p  << endl;
    cout << "**pp= " << **pp << "，pp 儲存：" << pp << endl;

    **pp = 999;    // 透過雙重指標修改 x
    cout << "\n修改後 x = " << x << endl;

    return 0;
}
```

**執行結果：**
```
x   = 5，位址：0x7ffd...100
*p  = 5，p 儲存：0x7ffd...100
**pp= 5，pp 儲存：0x7ffd...108

修改後 x = 999
```

---

## 10.2 指標參數傳遞

### 10.2.1 傳值 vs 傳指標

C++ 函式預設**傳值（Pass by Value）**，函式內修改的是**副本**，不影響原始變數：

```cpp
void add_ten(int x) {
    x += 10;   // 只改副本
}

int main() {
    int a = 5;
    add_ten(a);
    cout << a;   // 還是 5，沒有改變
}
```

要讓函式修改外部變數，有兩種方法：
1. **傳指標（Pass by Pointer）**：傳入變數的位址
2. **傳參考（Pass by Reference）**：使用 `&`，C++ 特有

本節先介紹傳指標：

```cpp
void add_ten(int *p) {   // 接收 int* 指標
    *p += 10;            // 透過指標修改原始變數
}

int main() {
    int a = 5;
    add_ten(&a);         // 傳入 a 的位址
    cout << a;           // 15，真的改了！
}
```

📄 **範例檔案：** [ex10_2_1_pass_by_ptr.cpp](examples/ex10_2_1_pass_by_ptr.cpp)

```cpp
#include <iostream>
using namespace std;

void add_ten_value(int x) {
    x += 10;
    cout << "函式內 x = " << x << endl;
}

void add_ten_ptr(int *p) {
    *p += 10;
    cout << "函式內 *p = " << *p << endl;
}

int main() {
    int a = 5, b = 5;

    cout << "=== 傳值 ===" << endl;
    add_ten_value(a);
    cout << "呼叫後 a = " << a << endl;   // 還是 5

    cout << "\n=== 傳指標 ===" << endl;
    add_ten_ptr(&b);
    cout << "呼叫後 b = " << b << endl;   // 變成 15

    return 0;
}
```

**執行結果：**
```
=== 傳值 ===
函式內 x = 15
呼叫後 a = 5

=== 傳指標 ===
函式內 *p = 15
呼叫後 b = 15
```

### 10.2.2 用指標實作 swap

經典範例：交換兩個變數的值。

📄 **範例檔案：** [ex10_2_2_swap_pointer.cpp](examples/ex10_2_2_swap_pointer.cpp)

```cpp
#include <iostream>
using namespace std;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10, y = 20;
    cout << "交換前：x = " << x << "，y = " << y << endl;

    swap(&x, &y);
    cout << "交換後：x = " << x << "，y = " << y << endl;

    return 0;
}
```

**執行結果：**
```
交換前：x = 10，y = 20
交換後：x = 20，y = 10
```

```
執行流程（swap 函式內）：
  a = &x（指向 x，值=10）
  b = &y（指向 y，值=20）

  temp = *a     → temp = 10
  *a   = *b     → x = 20
  *b   = temp   → y = 10
```

### 10.2.3 同時回傳多個結果

函式只能有一個 `return` 值，但透過指標參數可以「回傳」多個結果：

📄 **範例檔案：** [ex10_2_3_multiple_return.cpp](examples/ex10_2_3_multiple_return.cpp)

```cpp
#include <iostream>
using namespace std;

// 同時計算最大值和最小值
void min_max(int arr[], int n, int *min_val, int *max_val) {
    *min_val = arr[0];
    *max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < *min_val) *min_val = arr[i];
        if (arr[i] > *max_val) *max_val = arr[i];
    }
}

int main() {
    int scores[] = {78, 92, 55, 88, 100, 63};
    int n = sizeof(scores) / sizeof(scores[0]);
    int lo, hi;

    min_max(scores, n, &lo, &hi);
    cout << "最低分：" << lo << endl;
    cout << "最高分：" << hi << endl;

    return 0;
}
```

**執行結果：**
```
最低分：55
最高分：100
```

### 10.2.4 const 指標的四種組合

`const` 和指標搭配有四種情況：

| 宣告 | 指標本身 | 指向的值 | 說明 |
|------|---------|---------|------|
| `int *p` | 可改 | 可改 | 普通指標 |
| `const int *p` | 可改 | **不可改** | 指向常數的指標 |
| `int * const p` | **不可改** | 可改 | 常數指標 |
| `const int * const p` | **不可改** | **不可改** | 指向常數的常數指標 |

> 💡 **記憶技巧：** `*` 左邊的 `const` 限制「值」，`*` 右邊的 `const` 限制「指標本身」。

📄 **範例檔案：** [ex10_2_4_const_pointer.cpp](examples/ex10_2_4_const_pointer.cpp)

```cpp
#include <iostream>
using namespace std;

void print_array(const int *arr, int n) {
    // const int* 保護陣列不被函式修改
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    // arr[0] = 999;  // 編譯錯誤！不能修改
}

int main() {
    int x = 10, y = 20;

    // 1. 一般指標
    int *p1 = &x;
    *p1 = 50;         // OK
    p1 = &y;          // OK

    // 2. 指向常數的指標（保護值）
    const int *p2 = &x;
    // *p2 = 50;      // 錯誤：不能修改值
    p2 = &y;          // OK：可以改變指向

    // 3. 常數指標（鎖定指向）
    int * const p3 = &x;
    *p3 = 50;         // OK：可以修改值
    // p3 = &y;       // 錯誤：不能改變指向

    int arr[] = {1, 2, 3, 4, 5};
    print_array(arr, 5);   // 安全：arr 不會被修改

    return 0;
}
```

**執行結果：**
```
1 2 3 4 5
```

---

## 10.3 指標與陣列

### 10.3.1 陣列名稱即指標

這是 C/C++ 最重要的觀念之一：**陣列名稱本質上是陣列第一個元素的位址**。

```cpp
int arr[] = {10, 20, 30, 40, 50};

cout << arr;      // 輸出陣列首位址，等同 &arr[0]
cout << &arr[0];  // 與上面相同
```

因此：
```cpp
int *p = arr;     // 合法！等同 int *p = &arr[0];
cout << *p;       // 10，等同 arr[0]
```

### 10.3.2 指標算術（Pointer Arithmetic）

對指標進行加減，會以**指向型別的大小**為單位移動：

```cpp
int arr[] = {10, 20, 30, 40, 50};
int *p = arr;   // p 指向 arr[0]

p + 0  →  指向 arr[0]（位址 + 0*4）
p + 1  →  指向 arr[1]（位址 + 1*4）
p + 2  →  指向 arr[2]（位址 + 2*4）
```

```
  arr:   [10] [20] [30] [40] [50]
  位址:  1000  1004  1008  1012  1016
  指標:   p    p+1   p+2   p+3   p+4
```

📄 **範例檔案：** [ex10_3_1_array_pointer.cpp](examples/ex10_3_1_array_pointer.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *p = arr;   // p 指向 arr[0]

    cout << "陣列名稱 arr = " << arr << endl;
    cout << "&arr[0]     = " << &arr[0] << endl;
    cout << "指標 p      = " << p << endl;

    cout << "\n--- 指標算術 ---" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "p+" << i << " = " << (p+i)
             << "，*(p+" << i << ") = " << *(p+i)
             << "，arr[" << i << "] = " << arr[i] << endl;
    }

    return 0;
}
```

**執行結果：**
```
陣列名稱 arr = 0x7ffd...
&arr[0]     = 0x7ffd...
指標 p      = 0x7ffd...

--- 指標算術 ---
p+0 = 0x7ffd...00，*(p+0) = 10，arr[0] = 10
p+1 = 0x7ffd...04，*(p+1) = 20，arr[1] = 20
p+2 = 0x7ffd...08，*(p+2) = 30，arr[2] = 30
p+3 = 0x7ffd...0C，*(p+3) = 40，arr[3] = 40
p+4 = 0x7ffd...10，*(p+4) = 50，arr[4] = 50
```

### 10.3.3 指標與陣列語法的等價關係

C++ 保證以下四種寫法**完全等價**：

| 陣列語法 | 指標語法 |
|----------|----------|
| `arr[i]` | `*(arr + i)` |
| `&arr[i]` | `arr + i` |
| `p[i]`（p = arr） | `*(p + i)` |

📄 **範例檔案：** [ex10_3_2_ptr_array_equiv.cpp](examples/ex10_3_2_ptr_array_equiv.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *p = arr;

    cout << "四種等價寫法（第3個元素）：" << endl;
    cout << "arr[2]      = " << arr[2]      << endl;
    cout << "*(arr + 2)  = " << *(arr + 2)  << endl;
    cout << "p[2]        = " << p[2]        << endl;
    cout << "*(p + 2)    = " << *(p + 2)    << endl;

    cout << "\n用指標走訪陣列（p++）：" << endl;
    for (int *q = arr; q < arr + 5; q++) {
        cout << *q << " ";
    }
    cout << endl;

    return 0;
}
```

**執行結果：**
```
四種等價寫法（第3個元素）：
arr[2]      = 30
*(arr + 2)  = 30
p[2]        = 30
*(p + 2)    = 30

用指標走訪陣列（p++）：
10 20 30 40 50
```

### 10.3.4 C 字串與 `char*`

C 風格的字串就是以 `'\0'`（null 字元）結尾的 `char` 陣列，常用指標操作：

📄 **範例檔案：** [ex10_3_3_cstring_pointer.cpp](examples/ex10_3_3_cstring_pointer.cpp)

```cpp
#include <iostream>
#include <cstring>
using namespace std;

void print_string(const char *s) {
    while (*s != '\0') {   // 走到 null 字元為止
        cout << *s;
        s++;
    }
    cout << endl;
}

int my_strlen(const char *s) {
    int count = 0;
    while (*s++ != '\0') count++;
    return count;
}

int main() {
    char greeting[] = "Hello";
    char *p = greeting;

    cout << "字串：";
    print_string(p);

    cout << "長度：" << my_strlen(greeting) << endl;

    cout << "\n逐字輸出（含位址）：" << endl;
    for (char *q = greeting; *q != '\0'; q++) {
        cout << "位址 " << (void*)q << "：'" << *q << "'" << endl;
    }

    return 0;
}
```

**執行結果：**
```
字串：Hello
長度：5

逐字輸出（含位址）：
位址 0x7ffd...00：'H'
位址 0x7ffd...01：'e'
位址 0x7ffd...02：'l'
位址 0x7ffd...03：'l'
位址 0x7ffd...04：'o'
```

> ⚠️ **注意：** `char *p = "Hello";` 在現代 C++ 中已不推薦（字串常數不可修改）。應使用 `const char *p = "Hello";` 或改用 `std::string`。

### 10.3.5 指標陣列 vs 陣列指標

這兩個概念很容易混淆：

```cpp
int *p[5];    // 指標陣列：5 個 int* 的陣列
int (*p)[5];  // 陣列指標：指向一個含 5 個 int 的陣列
```

📄 **範例檔案：** [ex10_3_4_ptr_array_vs_array_ptr.cpp](examples/ex10_3_4_ptr_array_vs_array_ptr.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 1, b = 2, c = 3;

    // 指標陣列：儲存多個指標
    int *ptr_arr[3] = {&a, &b, &c};
    cout << "指標陣列：";
    for (int i = 0; i < 3; i++) {
        cout << *ptr_arr[i] << " ";
    }
    cout << endl;

    // 陣列指標：指向整個陣列
    int matrix[2][4] = {{1,2,3,4}, {5,6,7,8}};
    int (*row_ptr)[4] = matrix;   // 指向第一列（含4個int的陣列）

    cout << "第一列：";
    for (int j = 0; j < 4; j++) cout << row_ptr[0][j] << " ";
    cout << endl;

    cout << "第二列：";
    for (int j = 0; j < 4; j++) cout << row_ptr[1][j] << " ";
    cout << endl;

    return 0;
}
```

**執行結果：**
```
指標陣列：1 2 3
第一列：1 2 3 4
第二列：5 6 7 8
```

### 10.3.6 以指標傳遞陣列給函式

陣列傳入函式時，自動退化為指標，所以函式可以修改陣列內容：

📄 **範例檔案：** [ex10_3_5_array_func_ptr.cpp](examples/ex10_3_5_array_func_ptr.cpp)

```cpp
#include <iostream>
using namespace std;

// 這三種寫法等價：
// void fill(int arr[], int n)
// void fill(int *arr, int n)
void fill(int *arr, int n, int val) {
    for (int i = 0; i < n; i++) {
        arr[i] = val;   // 直接修改原始陣列
    }
}

void print(const int *arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int sum(const int *arr, int n) {
    int total = 0;
    for (int i = 0; i < n; i++) total += arr[i];
    return total;
}

int main() {
    int data[5];

    fill(data, 5, 7);
    cout << "填入 7 後：";
    print(data, 5);

    data[2] = 100;
    cout << "修改中間後：";
    print(data, 5);

    cout << "總和：" << sum(data, 5) << endl;

    return 0;
}
```

**執行結果：**
```
填入 7 後：7 7 7 7 7
修改中間後：7 7 100 7 7
總和：128
```

---

## 10.4 指標回傳值

### 10.4.1 回傳指標的函式

函式可以回傳一個指標，但必須**非常小心**：不能回傳指向區域變數的指標！

```cpp
int* bad_func() {
    int x = 5;
    return &x;   // 危險！x 在函式結束後就消失了
}
```

安全的做法：回傳靜態變數、全域變數、或動態配置的記憶體的指標。

📄 **範例檔案：** [ex10_4_1_return_pointer.cpp](examples/ex10_4_1_return_pointer.cpp)

```cpp
#include <iostream>
using namespace std;

// 正確：回傳靜態變數的指標
int* get_counter() {
    static int count = 0;   // static 變數不會隨函式消失
    count++;
    return &count;
}

// 正確：回傳陣列中最大值的指標
int* find_max(int *arr, int n) {
    int *max_p = arr;
    for (int i = 1; i < n; i++) {
        if (arr[i] > *max_p) max_p = &arr[i];
    }
    return max_p;
}

int main() {
    // 靜態變數指標
    int *p = get_counter();
    cout << "計數：" << *p << endl;
    get_counter();
    get_counter();
    cout << "計數：" << *p << endl;

    // 找最大值並修改它
    int scores[] = {78, 92, 55, 88, 100, 63};
    int *top = find_max(scores, 6);
    cout << "\n最高分：" << *top << endl;
    *top = 0;   // 清除最高分
    cout << "清除後陣列：";
    for (int i = 0; i < 6; i++) cout << scores[i] << " ";
    cout << endl;

    return 0;
}
```

**執行結果：**
```
計數：1
計數：3

最高分：100
清除後陣列：78 92 55 88 0 63
```

### 10.4.2 動態記憶體配置：`new` 與 `delete`

到目前為止，所有變數都是**靜態配置（Stack）**，大小在編譯時就確定了。

**動態記憶體配置（Heap）** 讓我們在**執行時期**決定需要多少記憶體：

```cpp
// 配置單一變數
int *p = new int;        // 在 heap 配置一個 int
int *q = new int(42);   // 配置並初始化為 42

// 使用
*p = 10;
cout << *q;   // 42

// 釋放（非常重要！用完一定要 delete）
delete p;
delete q;
p = nullptr;   // 避免成為懸置指標
q = nullptr;
```

📄 **範例檔案：** [ex10_4_2_new_delete.cpp](examples/ex10_4_2_new_delete.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    // 動態配置單一 int
    int *p = new int(100);
    cout << "動態配置的 int：" << *p << endl;
    cout << "位址：" << p << endl;

    *p = 200;
    cout << "修改後：" << *p << endl;

    delete p;
    p = nullptr;
    cout << "釋放後 p = " << p << endl;

    // 動態配置 double
    double *d = new double(3.14159);
    cout << "\n動態配置的 double：" << *d << endl;
    delete d;
    d = nullptr;

    return 0;
}
```

**執行結果：**
```
動態配置的 int：100
位址：0x55a7f2c02eb0
修改後：200
釋放後 p = 0

動態配置的 double：3.14159
```

### 10.4.3 動態陣列

`new[]` 和 `delete[]` 用來配置/釋放動態陣列：

```cpp
int n;
cin >> n;
int *arr = new int[n];   // 執行時才決定大小

// ... 使用 arr ...

delete[] arr;    // 注意：要用 delete[]，不是 delete
arr = nullptr;
```

📄 **範例檔案：** [ex10_4_3_dynamic_array.cpp](examples/ex10_4_3_dynamic_array.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "輸入學生人數：";
    cin >> n;

    // 動態配置陣列
    int *scores = new int[n];

    cout << "輸入 " << n << " 個成績：" << endl;
    for (int i = 0; i < n; i++) {
        cout << "第 " << i+1 << " 位：";
        cin >> scores[i];
    }

    // 計算平均
    double sum = 0;
    for (int i = 0; i < n; i++) sum += scores[i];
    cout << "平均成績：" << sum / n << endl;

    // 釋放記憶體（重要！）
    delete[] scores;
    scores = nullptr;

    cout << "記憶體已釋放" << endl;
    return 0;
}
```

**執行結果（輸入 3, 80, 90, 70）：**
```
輸入學生人數：3
輸入 3 個成績：
第 1 位：80
第 2 位：90
第 3 位：70
平均成績：80
記憶體已釋放
```

### 10.4.4 記憶體洩漏（Memory Leak）

配置了記憶體卻忘記釋放，就會造成**記憶體洩漏**：

```cpp
void leaky_func() {
    int *p = new int(5);
    // ... 忘記 delete p; ...
}   // p 消失了，但 heap 上的記憶體還在！無法再存取了！
```

📄 **範例檔案：** [ex10_4_4_memory_leak.cpp](examples/ex10_4_4_memory_leak.cpp)

```cpp
#include <iostream>
using namespace std;

void good_func() {
    int *p = new int(42);
    cout << "值：" << *p << endl;
    delete p;     // 正確釋放
    p = nullptr;
}

void bad_func() {
    int *p = new int(42);
    cout << "值：" << *p << endl;
    // 忘記 delete！記憶體洩漏
}

int main() {
    cout << "=== 正確版本 ===" << endl;
    for (int i = 0; i < 3; i++) good_func();

    cout << "\n=== 洩漏版本（不要學）===" << endl;
    for (int i = 0; i < 3; i++) bad_func();
    // 每次呼叫都洩漏 4 bytes，程式跑越久佔用越多記憶體

    return 0;
}
```

> ⚠️ **記憶體洩漏的後果：** 程式長時間執行後記憶體占用不斷增加，最終可能讓系統無法使用。伺服器程式尤其嚴重。

### 10.4.5 現代 C++ 的安全指標

C++11 引入了**智慧指標（Smart Pointer）**，自動管理記憶體，幾乎不需要手動 `delete`：

```cpp
#include <memory>

// unique_ptr：獨佔式，離開作用域自動釋放
unique_ptr<int> p = make_unique<int>(42);
cout << *p;   // 42
// 不需要 delete！

// shared_ptr：共享式，最後一個持有者釋放時自動釋放
shared_ptr<int> a = make_shared<int>(10);
shared_ptr<int> b = a;   // 兩個指標共享同一塊記憶體
```

📄 **範例檔案：** [ex10_4_5_smart_pointer.cpp](examples/ex10_4_5_smart_pointer.cpp)

```cpp
#include <iostream>
#include <memory>
using namespace std;

int main() {
    // unique_ptr：唯一擁有者
    {
        unique_ptr<int> p = make_unique<int>(100);
        cout << "unique_ptr 值：" << *p << endl;
        *p = 200;
        cout << "修改後：" << *p << endl;
    }   // p 在此自動 delete，不需要手動管理
    cout << "已自動釋放" << endl;

    // unique_ptr 動態陣列
    int n = 5;
    unique_ptr<int[]> arr = make_unique<int[]>(n);
    for (int i = 0; i < n; i++) arr[i] = (i+1) * 10;
    cout << "\n動態陣列：";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    // 離開 main 時自動釋放，不需要 delete[]

    return 0;
}
```

**執行結果：**
```
unique_ptr 值：100
修改後：200
已自動釋放

動態陣列：10 20 30 40 50
```

> 💡 **現代 C++ 建議：** 盡量使用 `unique_ptr` 取代裸指標（raw pointer）的動態配置，可避免絕大多數記憶體問題。

---

## 10.5 用途與限制

### 10.5.1 指標的主要用途整理

| 用途 | 說明 | 範例 |
|------|------|------|
| 傳址呼叫 | 讓函式修改外部變數 | `swap(&a, &b)` |
| 動態記憶體 | 執行時期決定大小 | `new int[n]` |
| 陣列傳遞 | 高效傳遞大型陣列 | `void f(int *arr, int n)` |
| 資料結構 | 鏈結串列、樹、圖 | `node->next = newNode` |
| 函式指標 | 傳遞函式作為參數 | 回呼函式（Callback） |
| 硬體操作 | 直接存取特定記憶體 | 嵌入式系統驅動程式 |

### 10.5.2 常見錯誤與防範

#### 錯誤一：野指標（Wild Pointer）

```cpp
int *p;       // 未初始化
*p = 5;      // 危險！p 指向不知道哪裡

// 修正：
int *p = nullptr;
int x = 5;
p = &x;
```

#### 錯誤二：懸置指標（Dangling Pointer）

```cpp
int *p = new int(5);
delete p;
cout << *p;   // 危險！p 仍然「指著」已釋放的記憶體

// 修正：delete 後立刻設 nullptr
delete p;
p = nullptr;
```

#### 錯誤三：解參考空指標

```cpp
int *p = nullptr;
*p = 5;        // 程式崩潰！（Segmentation Fault）

// 修正：使用前檢查
if (p != nullptr) {
    *p = 5;
}
```

#### 錯誤四：陣列越界

```cpp
int arr[5];
int *p = arr;
*(p + 10) = 99;   // 越界！存取到不屬於 arr 的記憶體
```

#### 錯誤五：delete 後再 delete（Double Free）

```cpp
int *p = new int(5);
delete p;
delete p;   // 危險！未定義行為

// 修正：delete 後設 nullptr，再次 delete nullptr 是安全的
delete p;
p = nullptr;
delete p;   // 安全，delete nullptr 不做任何事
```

📄 **範例檔案：** [ex10_5_1_pointer_pitfalls.cpp](examples/ex10_5_1_pointer_pitfalls.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    // 示範正確的指標生命週期管理
    int *p = nullptr;

    // 1. 確認非 null 才使用
    if (p == nullptr) {
        cout << "指標為空，先配置記憶體" << endl;
        p = new int(42);
    }

    cout << "值：" << *p << endl;

    // 2. 用完立刻釋放並設 null
    delete p;
    p = nullptr;
    cout << "釋放後 p = " << (p == nullptr ? "nullptr" : "非空") << endl;

    // 3. delete nullptr 是安全的
    delete p;
    cout << "再次 delete nullptr：安全" << endl;

    return 0;
}
```

**執行結果：**
```
指標為空，先配置記憶體
值：42
釋放後 p = nullptr
再次 delete nullptr：安全
```

### 10.5.3 指標 vs 參考

C++ 有參考（Reference）可以達到和指標類似的效果，且更安全：

| | 指標 `int *p` | 參考 `int &r` |
|-|--------------|--------------|
| 初始化 | 可晚綁定，可為 nullptr | 必須初始化，不能為 null |
| 重新指向 | 可以指向其他變數 | 不能重新綁定 |
| 語法 | 需要 `*` 解參考 | 直接使用，如普通變數 |
| 安全性 | 較低（可為 null、dangling） | 較高 |
| 使用場景 | 動態記憶體、資料結構 | 函式參數傳遞（推薦） |

```cpp
// 傳指標（C 風格）
void swap_ptr(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}
swap_ptr(&x, &y);

// 傳參考（C++ 風格，更清晰）
void swap_ref(int &a, int &b) {
    int t = a; a = b; b = t;
}
swap_ref(x, y);   // 呼叫更直觀
```

### 10.5.4 現代 C++ 的替代方案

| 裸指標用途 | 現代替代方案 |
|-----------|------------|
| 動態單一物件 | `unique_ptr<T>` / `shared_ptr<T>` |
| 動態陣列 | `vector<T>` |
| C 字串 `char*` | `std::string` |
| 函式指標 | `std::function` / lambda |
| 傳址修改 | 參考 `T&` |

> 💡 **學習建議：** 指標是基礎，必須學好。但在實際 C++ 專案中，應優先使用 STL 容器和智慧指標，避免裸指標的陷阱。面試時兩種都要會！

---

## 章節總結

```
第十章：指標
│
├── 10.1 指標變數
│   ├── 記憶體位址概念
│   ├── 宣告語法：int *p
│   ├── & 取址運算子
│   ├── * 解參考運算子
│   ├── nullptr 空指標
│   └── 雙重指標 int **pp
│
├── 10.2 指標參數傳遞
│   ├── 傳值 vs 傳指標
│   ├── 透過指標修改外部變數
│   ├── swap 實作
│   ├── 「回傳」多個結果
│   └── const 指標四種組合
│
├── 10.3 指標與陣列
│   ├── 陣列名稱 = 首元素位址
│   ├── 指標算術（+, -, ++, --）
│   ├── arr[i] ≡ *(arr+i)
│   ├── C 字串與 char*
│   ├── 指標陣列 vs 陣列指標
│   └── 陣列傳入函式（退化為指標）
│
├── 10.4 指標回傳值
│   ├── 回傳靜態/全域變數指標
│   ├── new/delete 動態配置
│   ├── new[]/delete[] 動態陣列
│   ├── 記憶體洩漏
│   └── unique_ptr 智慧指標
│
└── 10.5 用途與限制
    ├── 主要用途（傳址、動態記憶體、資料結構）
    ├── 常見錯誤（野指標、懸置指標、空指標解參考）
    ├── 指標 vs 參考
    └── 現代 C++ 替代方案
```

---

## 實作練習

### 基礎題（⭐）

**練習 1：指標基本操作**
宣告一個 `double` 變數 `price = 99.9`，再宣告一個指標 `p` 指向它。透過指標：
- 輸出 price 的值與位址
- 修改 price 為 199.9
- 輸出修改後的值

**練習 2：指標與函式**
寫一個函式 `void triple(int *n)`，透過指標將傳入的整數乘以三。在 main 中宣告 `int x = 7`，呼叫後輸出結果。

### 進階題（⭐⭐）

**練習 3：指標走訪陣列**
宣告 `int arr[] = {3, 1, 4, 1, 5, 9, 2, 6}`，僅使用指標（不使用陣列索引 `[]`）走訪陣列並輸出所有元素，再計算總和與平均。

**練習 4：圓形統計**
寫一個函式 `void circle_stats(double r, double *area, double *circumference)`，給定半徑，透過指標「回傳」圓面積和圓周長（π 取 3.14159）。

**練習 5：字串反轉**
使用 `char` 陣列與指標，不借助任何函式庫，寫一個 `void reverse_str(char *s)` 原地反轉字串。測試：`"Hello"` → `"olleH"`。

### 挑戰題（⭐⭐⭐）

**練習 6：動態配置矩陣**
使用 `new` 動態配置一個 `n × m` 的二維 `int` 矩陣（用指標的指標 `int **mat`），讓使用者輸入 n 和 m，填入 1～n×m，輸出後正確釋放記憶體。

**練習 7：統計函式**
寫一個函式 `void stats(int *arr, int n, int *min_v, int *max_v, double *avg)`，一次計算陣列的最小值、最大值、平均值，全部透過指標「回傳」。

**練習 8：字串複製**
不使用 `strcpy`，自己實作 `void my_strcpy(char *dst, const char *src)` 使用指標逐字元複製，包含結尾的 `'\0'`。

### 綜合題（⭐⭐⭐⭐）

**練習 9：動態堆疊（Stack）**
使用動態陣列（`new int[capacity]`）實作一個簡單的整數堆疊，支援：
- `push(int val)`：推入一個值（滿了就擴展至 2 倍容量）
- `pop()`：彈出頂部值
- `top()`：查看頂部值
- `is_empty()`：檢查是否為空

**練習 10：指標排序**
宣告 `int arr[8]` 並讓使用者輸入，建立一個 `int *ptr_arr[8]` 存放各元素的指標。對 `ptr_arr` 排序（透過比較 `*ptr_arr[i]`），使得輸出 `ptr_arr` 的解參考值是由小到大的排列。（注意：原始 `arr` 不變）

---

## 面試考題

### 題目 1：`*` 和 `&` 的差異

**問：** 請解釋 C++ 中 `*` 和 `&` 在指標相關語法中的用途差異，並給出例子。

**參考答案：**
- **`&`（取址運算子）**：放在變數前，取得該變數的記憶體位址。例如 `int x = 5; int *p = &x;` 中，`&x` 是 `x` 的位址。
- **`*`（解參考運算子）**：放在指標前，取得指標所指向位址的值。例如 `cout << *p;` 輸出 `5`。
- **宣告時的 `*`**：是指標宣告的語法，`int *p;` 表示 `p` 是指向 int 的指標，這個 `*` 是型別的一部分，不是運算子。
- **宣告時的 `&`**：是參考宣告的語法，`int &r = x;` 表示 `r` 是 `x` 的別名（參考）。

---

### 題目 2：傳值、傳指標、傳參考的比較

**問：** 比較這三種參數傳遞方式的差異，各適合什麼場景？

**參考答案：**

| | 傳值 `int x` | 傳指標 `int *p` | 傳參考 `int &r` |
|-|------------|----------------|----------------|
| 複製 | 複製一份 | 複製位址 | 不複製 |
| 修改原始 | ❌ | ✅（需 `*p`） | ✅（直接用） |
| 可為 null | ✅ | ✅（需檢查） | ❌ |
| 語法 | 最簡單 | 需要 `*`/`&` | 較清晰 |

- **傳值**：適合小型基本型別（int、double 等），不需修改原始值。
- **傳指標**：適合需要表達「可選（nullable）」的情況，或 C 風格 API 互通。
- **傳參考**：C++ 首選，函式需修改參數，或傳遞大型物件（`const T&`）時使用。

---

### 題目 3：`delete` 後為何要設 `nullptr`？

**問：** 執行 `delete p;` 後為什麼要接著寫 `p = nullptr;`？

**參考答案：**
`delete p` 釋放了 `p` 所指向的記憶體，但 **`p` 本身仍然存有舊位址**，稱為「**懸置指標（Dangling Pointer）**」。此時若再對 `p` 解參考（`*p`），行為是**未定義（Undefined Behavior）**，可能讀到垃圾值、修改到不相關的資料，或造成程式崩潰。

將 `p = nullptr` 有兩個好處：
1. 任何後續的 `if (p != nullptr)` 檢查都能正確判斷出指標已無效。
2. `delete nullptr` 是合法且不做任何事，避免 double-free 問題。

---

### 題目 4：`const int *p` 和 `int * const p` 有何不同？

**問：** 這兩個宣告有何差異？能不能各舉一個實際用途？

**參考答案：**
- **`const int *p`（指向常數的指標）**：`p` 可以改變指向，但不能透過 `p` 修改值（`*p = x` 非法）。常用於函式參數中保護輸入資料不被修改，如 `void print(const int *arr, int n)`。
- **`int * const p`（常數指標）**：`p` 不能改變指向（`p = &y` 非法），但可以修改值（`*p = x` 合法）。常用於指向固定硬體暫存器的指標，確保指標始終指向同一位置。

記憶技巧：讀 C 宣告由右往左，遇到 `const` 和 `*` 的順序決定限制對象。

---

### 題目 5：記憶體洩漏是什麼？如何避免？

**問：** 解釋記憶體洩漏，並說明現代 C++ 如何解決這個問題。

**參考答案：**
**記憶體洩漏（Memory Leak）** 是指程式用 `new` 動態配置的記憶體，在使用完畢後沒有用 `delete` 釋放，導致這塊記憶體在程式執行期間始終被佔用，即使已無法再被程式存取。長時間運行的程式（如伺服器）若有洩漏，記憶體用量會持續增加，最終耗盡系統資源。

**常見原因：**
1. 忘記 `delete`
2. 異常發生時跳過 `delete`（Exception Safety 問題）
3. 指標被覆蓋前忘記釋放

**現代 C++ 解決方案（RAII 原則）：**
- `std::unique_ptr<T>`：唯一擁有者，作用域結束自動 `delete`
- `std::shared_ptr<T>`：引用計數，最後一個使用者離開時自動 `delete`
- `std::vector<T>`：取代動態陣列，自動管理記憶體

原則：盡量避免裸指標（raw pointer）負責所有權管理。

---

## 專案：動態學生名冊管理系統

### 需求說明

實作一個使用**動態記憶體配置**的學生名冊管理系統，支援新增學生（人數不固定，需要動態擴展），並提供統計功能。

### 功能要求

1. **新增學生**：輸入姓名和分數，動態新增（初始容量 2，每次滿了擴展為 2 倍）
2. **列出所有學生**：顯示編號、姓名、分數
3. **成績統計**：透過指標參數計算並回傳最高分、最低分、平均分
4. **找出最高分學生**：回傳指向該學生的指標
5. **排序顯示**：按成績由高到低排列輸出

### 範例執行畫面

```
=== 學生名冊管理系統 ===
1. 新增學生
2. 列出所有學生
3. 成績統計
4. 找最高分學生
5. 排序顯示
0. 離開
選項：1
姓名：Alice  分數：85
新增成功！（容量：2/2）

選項：1
姓名：Bob  分數：92
新增成功！（容量：2/2）

選項：1
姓名：Carol  分數：78
陣列已滿，擴展容量到 4...
新增成功！（容量：3/4）

選項：3
最高分：92（Bob）
最低分：78（Carol）
平均分：85.00

選項：5
排名  姓名   分數
1     Bob    92
2     Alice  85
3     Carol  78
```

📄 **專案解答：** [project10_dynamic_student_list_answer.cpp](examples/project10_dynamic_student_list_answer.cpp)

---

*第十章完*
