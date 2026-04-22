# 第七章：陣列（Array）

> **學習目標**
> - 理解陣列的概念：連續記憶體、固定大小、相同型別
> - 熟練宣告、初始化、存取一維陣列
> - 使用 `assert` 進行邊界檢查，養成防禦性程式設計習慣
> - 掌握排序（泡沫、選擇）與搜尋（線性、二分）等陣列演算法
> - 理解多維陣列的記憶體佈局與巢狀迴圈存取
> - 能用二維陣列解決矩陣運算、遊戲棋盤等實際問題

---

## 7.0 為什麼需要陣列？

假設你要儲存 50 位學生的成績，沒有陣列時你得這樣寫：

```cpp
int score1, score2, score3, score4, score5;
// ... 一直到 score50
```

這樣不但費時，而且無法用迴圈處理。有了**陣列（Array）**，只需：

```cpp
int score[50];   // 一次宣告 50 個整數變數

for (int i = 0; i < 50; i++) {
    cin >> score[i];   // 用迴圈讀取
}
```

陣列是 C++ 中**最基礎的資料結構**，幾乎所有演算法都以陣列為基礎。

---

## 7.1 屬性

### 7.1.1 陣列是什麼

**陣列（Array）** 是一組**相同型別**的變數，儲存在**連續的記憶體空間**中，並以**整數索引（Index）** 存取。

```
  索引：  [0]   [1]   [2]   [3]   [4]
        ┌─────┬─────┬─────┬─────┬─────┐
  值：  │ 85  │ 92  │ 78  │ 95  │ 88  │
        └─────┴─────┴─────┴─────┴─────┘
  位址： 1000  1004  1008  1012  1016
                  （每個 int 占 4 bytes）
```

**陣列的四大特性：**

| 特性 | 說明 |
|------|------|
| **相同型別** | 所有元素型別必須相同（int、double、char 等） |
| **連續記憶體** | 元素在記憶體中緊密排列，無間隔 |
| **固定大小** | 宣告後大小不可改變（編譯時期決定） |
| **從零索引** | 第一個元素的索引是 `0`，最後一個是 `n-1` |

### 7.1.2 與一般變數的比較

```
一般變數（各自獨立）：
  int a = 85;   // 位址 1000
  int b = 92;   // 位址 2048（不一定連續）
  int c = 78;   // 位址 3124

陣列（連續排列）：
  int score[3] = {85, 92, 78};
  //  score[0]=85  位址 1000
  //  score[1]=92  位址 1004  （1000 + 4）
  //  score[2]=78  位址 1008  （1000 + 8）
```

> 💡 **連續記憶體的好處：** CPU 讀取陣列時可以利用**快取（Cache）** 機制，比讀取分散的變數快很多，這是陣列在效能上的一大優勢。

### 7.1.3 陣列 vs 其他容器

C++ 有多種儲存集合的方式：

| | `int arr[5]` | `vector<int>` | `array<int,5>` |
|-|-------------|--------------|----------------|
| 大小 | 固定（編譯期） | 動態（執行期） | 固定（編譯期） |
| 邊界檢查 | ❌ | `.at()` 有 | `.at()` 有 |
| 效能 | 最快 | 稍慢 | 同原生陣列 |
| 功能 | 最少 | 最多 | 介於中間 |
| 使用情境 | 簡單固定集合 | 一般用途 | 現代C++推薦 |

> 💡 **學習建議：** 先學原生陣列（本章），理解底層原理後再學 `vector`（動態陣列）。面試常考原生陣列的操作。

📄 **範例檔案：** [ex7_1_1_array_intro.cpp](examples/ex7_1_1_array_intro.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    // 一般變數：5個分開的變數
    int s0 = 85, s1 = 92, s2 = 78, s3 = 95, s4 = 88;

    // 陣列：5個元素存在連續記憶體
    int score[5] = {85, 92, 78, 95, 88};

    // 用迴圈操作陣列（一般變數做不到）
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += score[i];
    }
    cout << "平均：" << sum / 5.0 << endl;

    // 顯示各元素的記憶體位址（驗證連續性）
    cout << "\n各元素記憶體位址：" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "score[" << i << "] 位址：" << &score[i] << endl;
    }

    return 0;
}
```

**輸出（位址數值因機器而異，但差距固定為 4）：**
```
平均：87.6

各元素記憶體位址：
score[0] 位址：0x61fdc0
score[1] 位址：0x61fdc4
score[2] 位址：0x61fdc8
score[3] 位址：0x61fdcc
score[4] 位址：0x61fdd0
```

---

## 7.2 一維陣列

### 7.2.1 宣告語法

```
型別  陣列名稱 [大小];
```

```cpp
int    score[5];     // 5 個 int，未初始化
double price[10];    // 10 個 double，未初始化
char   name[20];     // 20 個 char，未初始化
bool   flags[8];     // 8 個 bool，未初始化
```

> ⚠️ **大小必須是正整數常數（或常數運算式）。**  
> 在標準 C++ 中，陣列大小必須在**編譯時期**已知：
> ```cpp
> const int N = 5;
> int arr[N];     // ✅ 合法（N 是常數）
> 
> int n;
> cin >> n;
> int arr[n];     // ❌ 標準C++不合法（n是變數）
>                 //    部分編譯器允許（VLA），但應避免使用
> ```

### 7.2.2 初始化

**方式一：宣告時直接初始化**

```cpp
int score[5] = {85, 92, 78, 95, 88};
//  score[0]=85, score[1]=92, ..., score[4]=88
```

**方式二：省略大小（自動推算）**

```cpp
int score[] = {85, 92, 78, 95, 88};
// 編譯器自動計算大小為 5
```

**方式三：部分初始化（其餘補 0）**

```cpp
int arr[5] = {1, 2};
// arr[0]=1, arr[1]=2, arr[2]=0, arr[3]=0, arr[4]=0
```

**方式四：全部初始化為 0**

```cpp
int arr[5] = {};       // 全部為 0（C++11）
int arr2[5] = {0};    // 全部為 0（舊寫法）
```

**方式五：宣告後逐一賦值**

```cpp
int arr[5];
arr[0] = 10;
arr[1] = 20;
// ...
```

> ⚠️ **未初始化的陣列包含垃圾值！**  
> 不同於全域/靜態陣列（自動初始化為 0），區域陣列若不初始化，內容是記憶體中的隨機值，使用前務必初始化。

📄 **範例檔案：** [ex7_2_1_array_init.cpp](examples/ex7_2_1_array_init.cpp)

```cpp
#include <iostream>
using namespace std;

int globalArr[5];   // 全域陣列：自動初始化為 0

int main() {
    // 各種初始化方式
    int a[5] = {1, 2, 3, 4, 5};      // 完整初始化
    int b[5] = {10, 20};              // 部分初始化（後面補0）
    int c[5] = {};                     // 全部為 0
    int d[]  = {100, 200, 300};       // 自動推算大小（3個）

    cout << "a: ";
    for (int i = 0; i < 5; i++) cout << a[i] << " ";
    cout << endl;

    cout << "b: ";
    for (int i = 0; i < 5; i++) cout << b[i] << " ";
    cout << endl;

    cout << "c: ";
    for (int i = 0; i < 5; i++) cout << c[i] << " ";
    cout << endl;

    cout << "d: ";
    for (int i = 0; i < 3; i++) cout << d[i] << " ";
    cout << endl;

    cout << "global: ";
    for (int i = 0; i < 5; i++) cout << globalArr[i] << " ";
    cout << endl;

    return 0;
}
```

**輸出：**
```
a: 1 2 3 4 5
b: 10 20 0 0 0
c: 0 0 0 0 0
d: 100 200 300
global: 0 0 0 0 0
```

---

### 7.2.3 存取元素

```cpp
陣列名稱[索引]     // 讀取或寫入
```

索引從 `0` 開始，到 `大小-1` 結束。

📄 **範例檔案：** [ex7_2_2_array_access.cpp](examples/ex7_2_2_array_access.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};

    // 讀取
    cout << "第一個元素：" << arr[0] << endl;   // 10
    cout << "最後一個：" << arr[4] << endl;      // 50

    // 修改
    arr[2] = 99;
    cout << "修改後 arr[2]：" << arr[2] << endl; // 99

    // 用迴圈讀取所有元素
    cout << "全部元素：";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // 用迴圈輸入
    int scores[5];
    cout << "\n請輸入 5 個成績：";
    for (int i = 0; i < 5; i++) {
        cin >> scores[i];
    }

    cout << "你輸入的成績：";
    for (int i = 0; i < 5; i++) {
        cout << scores[i] << " ";
    }
    cout << endl;

    return 0;
}
```

---

### 7.2.4 用 `sizeof` 計算陣列大小

```cpp
sizeof(陣列名稱)                          // 陣列佔用的總位元組數
sizeof(陣列名稱) / sizeof(陣列名稱[0])    // 元素個數
```

📄 **範例檔案：** [ex7_2_3_array_sizeof.cpp](examples/ex7_2_3_array_sizeof.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int    arr[5]    = {1, 2, 3, 4, 5};
    double darr[4]   = {1.1, 2.2, 3.3, 4.4};
    char   carr[10]  = "Hello";

    // sizeof(陣列) = 元素個數 × 每個元素大小
    cout << "int arr[5]:" << endl;
    cout << "  sizeof(arr)    = " << sizeof(arr)    << " bytes" << endl;  // 20
    cout << "  sizeof(arr[0]) = " << sizeof(arr[0]) << " bytes" << endl;  // 4
    cout << "  元素個數       = " << sizeof(arr) / sizeof(arr[0]) << endl; // 5

    cout << "\ndouble darr[4]:" << endl;
    cout << "  sizeof(darr)   = " << sizeof(darr)    << " bytes" << endl; // 32
    cout << "  元素個數       = " << sizeof(darr) / sizeof(darr[0]) << endl; // 4

    // 常見寫法：避免寫死大小
    const int N = sizeof(arr) / sizeof(arr[0]);
    cout << "\n用 sizeof 計算大小，再用迴圈：" << endl;
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
```

**輸出：**
```
int arr[5]:
  sizeof(arr)    = 20 bytes
  sizeof(arr[0]) = 4 bytes
  元素個數       = 5

double darr[4]:
  sizeof(darr)   = 32 bytes
  元素個數       = 4

用 sizeof 計算大小，再用迴圈：
1 2 3 4 5
```

---

### 7.2.5 範圍型 `for` 迴圈（Range-based for）

C++11 新增的語法，讓遍歷陣列更簡潔：

```cpp
for (型別 變數 : 陣列) {
    // 使用 變數
}
```

📄 **範例檔案：** [ex7_2_4_range_for.cpp](examples/ex7_2_4_range_for.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int scores[] = {85, 92, 78, 95, 88};

    // 傳統 for
    cout << "傳統 for：";
    for (int i = 0; i < 5; i++) {
        cout << scores[i] << " ";
    }
    cout << endl;

    // 範圍型 for（只讀）
    cout << "範圍型 for：";
    for (int s : scores) {
        cout << s << " ";
    }
    cout << endl;

    // 範圍型 for（修改：需加 &）
    for (int& s : scores) {
        s += 5;   // 每個成績加 5 分
    }

    cout << "加 5 分後：";
    for (int s : scores) {
        cout << s << " ";
    }
    cout << endl;

    // 適合用在不需要索引的情況
    double prices[] = {29.9, 49.9, 99.9, 149.9};
    double total = 0;
    for (double p : prices) {
        total += p;
    }
    cout << "\n總價：" << total << endl;

    return 0;
}
```

**輸出：**
```
傳統 for：85 92 78 95 88
範圍型 for：85 92 78 95 88
加 5 分後：90 97 83 100 93

總價：329.6
```

> ⚠️ **範圍型 for 的限制：**  
> 範圍型 for 在**函式參數**中的陣列無法正確得知大小（陣列退化為指標），這時只能用傳統 for。詳見 7.2.6。

---

### 7.2.6 陣列與函式

將陣列傳入函式時，有幾個重要觀念：

**觀念一：陣列傳入函式時「退化」為指標，需額外傳大小**

```cpp
void printArray(int arr[], int n) {   // 等同 int* arr
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}
```

**觀念二：函式中修改陣列元素，會影響原始陣列（傳址）**

```cpp
void addOne(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i]++;   // 修改的是原始陣列！
    }
}
```

**觀念三：若不想讓函式修改陣列，加上 `const`**

```cpp
void printArray(const int arr[], int n) {
    // arr[0] = 0;  ← 這樣寫會編譯錯誤！
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}
```

📄 **範例檔案：** [ex7_2_5_array_function.cpp](examples/ex7_2_5_array_function.cpp)

```cpp
#include <iostream>
using namespace std;

// 只讀函式（加 const 保護）
void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << endl;
}

// 計算總和
int sum(const int arr[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++) total += arr[i];
    return total;
}

// 修改陣列（不加 const，可修改）
void fillZero(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = 0;
}

int main() {
    int scores[5] = {85, 92, 78, 95, 88};

    cout << "原始：";
    printArray(scores, 5);

    cout << "總和：" << sum(scores, 5) << endl;
    cout << "平均：" << sum(scores, 5) / 5.0 << endl;

    fillZero(scores, 5);
    cout << "清零後：";
    printArray(scores, 5);

    return 0;
}
```

**輸出：**
```
原始：85, 92, 78, 95, 88
總和：438
平均：87.6
清零後：0, 0, 0, 0, 0
```

---

### 7.2.7 越界存取（Out-of-Bounds Access）

陣列越界是 C++ 中最危險的錯誤之一，**編譯器不會幫你檢查！**

```cpp
int arr[5] = {1, 2, 3, 4, 5};
cout << arr[5];   // ❌ 越界！索引 5 不存在（合法範圍 0~4）
arr[-1] = 10;     // ❌ 越界！負數索引
arr[100] = 99;    // ❌ 越界！存取非法記憶體，可能當機
```

**後果：**
- 讀到不可預期的垃圾值
- 覆蓋其他變數的記憶體
- 程式崩潰（Segmentation Fault）
- 安全漏洞（緩衝區溢位攻擊）

```
  [0]   [1]   [2]   [3]   [4]      [5]（越界）
┌─────┬─────┬─────┬─────┬─────┐   ┌─────┐
│  1  │  2  │  3  │  4  │  5  │   │ ??? │ ← 可能是其他變數！
└─────┴─────┴─────┴─────┴─────┘   └─────┘
                                    危險！
```

> 💡 **防禦策略：**
> 1. 迴圈條件用 `i < n`，不要用 `i <= n`
> 2. 使用 `assert` 做邊界檢查（見 7.3）
> 3. 使用 `std::vector` 的 `.at()` 方法（有邊界檢查）

---

## 7.3 `assert`

### 7.3.1 什麼是 `assert`

`assert` 是一種**斷言（Assertion）** 機制：在程式中插入「**這個條件應該永遠為真**」的斷言，若條件為假，程式立即停止並顯示錯誤位置。

```cpp
#include <cassert>

assert(條件);   // 若條件為 false，程式終止並顯示錯誤
```

這是**防禦性程式設計（Defensive Programming）** 的核心工具：在開發階段快速找出 bug。

### 7.3.2 基本用法

📄 **範例檔案：** [ex7_3_1_assert_basic.cpp](examples/ex7_3_1_assert_basic.cpp)

```cpp
#include <iostream>
#include <cassert>
using namespace std;

int divide(int a, int b) {
    assert(b != 0);   // 斷言：b 不能是 0
    return a / b;
}

int main() {
    cout << divide(10, 2) << endl;   // 5，assert 通過
    cout << divide(10, 0) << endl;   // ❌ assert 失敗，程式終止！

    return 0;
}
```

**正常執行（b=2）：**
```
5
```

**觸發 assert（b=0）：**
```
5
Assertion failed: b != 0, file ex7_3_1_assert_basic.cpp, line 6
```

> 💡 assert 觸發後顯示：
> - 失敗的條件式
> - 檔案名稱
> - 行號
> 這讓你可以**精確定位 bug 的位置**。

---

### 7.3.3 用 `assert` 做陣列邊界檢查

這是最常見的 assert 用途：

📄 **範例檔案：** [ex7_3_2_assert_bounds.cpp](examples/ex7_3_2_assert_bounds.cpp)

```cpp
#include <iostream>
#include <cassert>
using namespace std;

const int SIZE = 5;

// 安全的陣列存取函式
int safeGet(const int arr[], int n, int index) {
    assert(index >= 0 && index < n);   // 邊界檢查
    return arr[index];
}

void safeSet(int arr[], int n, int index, int value) {
    assert(index >= 0 && index < n);   // 邊界檢查
    arr[index] = value;
}

int main() {
    int arr[SIZE] = {10, 20, 30, 40, 50};

    // 合法存取
    cout << safeGet(arr, SIZE, 0) << endl;   // 10
    cout << safeGet(arr, SIZE, 4) << endl;   // 50

    safeSet(arr, SIZE, 2, 99);
    cout << safeGet(arr, SIZE, 2) << endl;   // 99

    // 非法存取：觸發 assert
    cout << safeGet(arr, SIZE, 5) << endl;   // ❌ 越界！
    cout << safeGet(arr, SIZE, -1) << endl;  // ❌ 越界！

    return 0;
}
```

---

### 7.3.4 `NDEBUG`：關閉 assert

在正式發布版本中，`assert` 可以被**完全移除**（不影響效能），方法是在 include 前定義 `NDEBUG`：

```cpp
#define NDEBUG       // 加上這行，以下所有 assert 都會被忽略
#include <cassert>
```

或在編譯指令加上 `-DNDEBUG` 參數：
```
g++ -DNDEBUG main.cpp -o main
```

**工作流程：**
```
開發階段（Debug Mode）：
  assert 啟用 → 快速發現 bug

正式發布（Release Mode）：
  定義 NDEBUG → assert 消失 → 無效能損耗
```

### 7.3.5 assert 使用原則

| 適合用 `assert` | 不適合用 `assert` |
|---------------|-----------------|
| 函式前置條件（不應發生的情況） | 使用者輸入驗證 |
| 程式邏輯不變式 | 外部資料（檔案、網路）驗證 |
| 開發/除錯階段的快速檢查 | 正式的錯誤處理（應用 if/exception） |

```cpp
// ✅ 適合：邏輯上不可能發生的情況
assert(ptr != nullptr);          // 指標不應為空
assert(index >= 0 && index < n); // 索引必須在範圍內

// ❌ 不適合：使用者輸入
int age;
cin >> age;
assert(age >= 0);   // 若使用者輸入負數，程式直接崩潰，不友善
// 應改為：
if (age < 0) { cerr << "年齡不合法" << endl; return 1; }
```

---

## 7.4 一維陣列應用

### 7.4.1 尋找最大值、最小值

📄 **範例檔案：** [ex7_4_1_max_min.cpp](examples/ex7_4_1_max_min.cpp)

```cpp
#include <iostream>
#include <cassert>
using namespace std;

// 回傳最大值
int findMax(const int arr[], int n) {
    assert(n > 0);
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    return maxVal;
}

// 回傳最小值的索引
int findMinIndex(const int arr[], int n) {
    assert(n > 0);
    int minIdx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[minIdx]) minIdx = i;
    }
    return minIdx;
}

int main() {
    int scores[] = {85, 92, 78, 95, 88, 73, 99, 61};
    int n = sizeof(scores) / sizeof(scores[0]);

    cout << "成績：";
    for (int i = 0; i < n; i++) cout << scores[i] << " ";
    cout << endl;

    cout << "最高分：" << findMax(scores, n) << endl;

    int minIdx = findMinIndex(scores, n);
    cout << "最低分：" << scores[minIdx]
         << "（第 " << minIdx + 1 << " 位學生）" << endl;

    return 0;
}
```

**輸出：**
```
成績：85 92 78 95 88 73 99 61
最高分：99
最低分：61（第 8 位學生）
```

---

### 7.4.2 統計計算

📄 **範例檔案：** [ex7_4_2_statistics.cpp](examples/ex7_4_2_statistics.cpp)

```cpp
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>
using namespace std;

double calcMean(const int arr[], int n) {
    assert(n > 0);
    int sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return (double)sum / n;
}

double calcVariance(const int arr[], int n) {
    assert(n > 0);
    double mean = calcMean(arr, n);
    double sumSq = 0;
    for (int i = 0; i < n; i++) {
        double diff = arr[i] - mean;
        sumSq += diff * diff;
    }
    return sumSq / n;
}

int main() {
    int scores[] = {85, 92, 78, 95, 88, 73, 99, 61};
    int n = sizeof(scores) / sizeof(scores[0]);

    double mean   = calcMean(scores, n);
    double var    = calcVariance(scores, n);
    double stddev = sqrt(var);

    cout << fixed << setprecision(2);
    cout << "人數：" << n << endl;
    cout << "平均：" << mean   << endl;
    cout << "變異數：" << var  << endl;
    cout << "標準差：" << stddev << endl;

    // 計算及格率
    int pass = 0;
    for (int i = 0; i < n; i++) {
        if (scores[i] >= 60) pass++;
    }
    cout << "及格率：" << (double)pass / n * 100 << "%" << endl;

    return 0;
}
```

**輸出：**
```
人數：8
平均：83.88
變異數：133.36
標準差：11.55
及格率：100.00%
```

---

### 7.4.3 線性搜尋（Linear Search）

從頭到尾依序比較，找到就回傳索引，找不到回傳 -1。

**時間複雜度：O(n)**

📄 **範例檔案：** [ex7_4_3_linear_search.cpp](examples/ex7_4_3_linear_search.cpp)

```cpp
#include <iostream>
using namespace std;

// 線性搜尋：回傳第一個符合的索引，找不到回傳 -1
int linearSearch(const int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

int main() {
    int arr[] = {85, 92, 78, 95, 88, 73, 99, 61};
    int n = sizeof(arr) / sizeof(arr[0]);

    int target;
    cout << "請輸入要搜尋的數字：";
    cin >> target;

    int idx = linearSearch(arr, n, target);

    if (idx != -1) {
        cout << target << " 在索引 " << idx
             << "（第 " << idx + 1 << " 個位置）" << endl;
    } else {
        cout << target << " 不在陣列中" << endl;
    }

    return 0;
}
```

---

### 7.4.4 二分搜尋（Binary Search）

**前提：陣列必須已排序！**  
每次比較中間值，將搜尋範圍減半。

**時間複雜度：O(log n)**

```
目標：找 78
陣列（排序後）：[61, 73, 78, 85, 88, 92, 95, 99]
索引：           0   1   2   3   4   5   6   7

步驟一：左=0, 右=7, 中=3, arr[3]=85 > 78 → 往左半找
步驟二：左=0, 右=2, 中=1, arr[1]=73 < 78 → 往右半找
步驟三：左=2, 右=2, 中=2, arr[2]=78 == 78 → 找到！
```

📄 **範例檔案：** [ex7_4_4_binary_search.cpp](examples/ex7_4_4_binary_search.cpp)

```cpp
#include <iostream>
using namespace std;

int binarySearch(const int arr[], int n, int target) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;   // 避免 (left+right) 溢位

        if (arr[mid] == target) {
            return mid;             // 找到
        } else if (arr[mid] < target) {
            left = mid + 1;         // 往右半找
        } else {
            right = mid - 1;        // 往左半找
        }
    }
    return -1;   // 找不到
}

int main() {
    // 注意：必須先排序！
    int arr[] = {61, 73, 78, 85, 88, 92, 95, 99};
    int n = sizeof(arr) / sizeof(arr[0]);

    int target;
    cout << "陣列：";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    cout << "請輸入要搜尋的數字：";
    cin >> target;

    int idx = binarySearch(arr, n, target);

    if (idx != -1) {
        cout << target << " 在索引 " << idx << endl;
    } else {
        cout << target << " 不在陣列中" << endl;
    }

    return 0;
}
```

**線性 vs 二分搜尋比較：**

| | 線性搜尋 | 二分搜尋 |
|-|--------|--------|
| 前提 | 無要求 | 已排序 |
| 最壞情況 | n 次比較 | log₂n 次比較 |
| n=1000 | 1000 次 | 10 次 |
| n=1,000,000 | 1,000,000 次 | 20 次 |
| 適用場合 | 資料少、未排序 | 資料多、已排序 |

---

### 7.4.5 泡沫排序（Bubble Sort）

相鄰元素比較，較大的往後「浮」，像泡泡浮到水面。

**時間複雜度：O(n²)**

```
原始：[5, 3, 8, 1, 4]

第一輪：
  比較 5,3 → 交換 → [3, 5, 8, 1, 4]
  比較 5,8 → 不換 → [3, 5, 8, 1, 4]
  比較 8,1 → 交換 → [3, 5, 1, 8, 4]
  比較 8,4 → 交換 → [3, 5, 1, 4, 8]   最大值 8 到位！

第二輪：
  ...最終結果 [1, 3, 4, 5, 8]
```

📄 **範例檔案：** [ex7_4_5_bubble_sort.cpp](examples/ex7_4_5_bubble_sort.cpp)

```cpp
#include <iostream>
using namespace std;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;   // 最佳化：若這輪沒交換代表已排序

        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                // 交換
                int temp = arr[j];
                arr[j]   = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) break;   // 提早結束
    }
}

void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "排序前：";
    printArray(arr, n);

    bubbleSort(arr, n);

    cout << "排序後：";
    printArray(arr, n);

    return 0;
}
```

**輸出：**
```
排序前：64 34 25 12 22 11 90
排序後：11 12 22 25 34 64 90
```

---

### 7.4.6 選擇排序（Selection Sort）

每輪從未排序部分找最小值，放到已排序部分的末尾。

**時間複雜度：O(n²)，交換次數少於泡沫排序**

```
原始：[5, 3, 8, 1, 4]

第一輪：找最小值 1（位置3），與位置0交換 → [1, 3, 8, 5, 4]
第二輪：找最小值 3（位置1），與位置1交換 → [1, 3, 8, 5, 4]（不動）
第三輪：找最小值 4（位置4），與位置2交換 → [1, 3, 4, 5, 8]
...
```

📄 **範例檔案：** [ex7_4_6_selection_sort.cpp](examples/ex7_4_6_selection_sort.cpp)

```cpp
#include <iostream>
using namespace std;

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // 在未排序部分找最小值的索引
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }

        // 將最小值與第 i 個元素交換
        if (minIdx != i) {
            int temp      = arr[i];
            arr[i]        = arr[minIdx];
            arr[minIdx]   = temp;
        }
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "排序前：";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    selectionSort(arr, n);

    cout << "排序後：";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
```

**排序演算法比較：**

| 演算法 | 時間複雜度 | 空間複雜度 | 穩定排序 | 特點 |
|--------|-----------|-----------|---------|------|
| 泡沫排序 | O(n²) | O(1) | ✅ | 最簡單，有早停最佳化 |
| 選擇排序 | O(n²) | O(1) | ❌ | 交換次數少 |
| 插入排序 | O(n²)~O(n) | O(1) | ✅ | 近乎排序時很快 |
| 合併排序 | O(n log n) | O(n) | ✅ | 穩定，適合大資料 |
| 快速排序 | O(n log n) | O(log n) | ❌ | 實務最常用 |

---

### 7.4.7 直方圖（Histogram）

📄 **範例檔案：** [ex7_4_7_histogram.cpp](examples/ex7_4_7_histogram.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    // 統計成績分布：A(90-100), B(80-89), C(70-79), D(60-69), F(<60)
    int scores[] = {85, 92, 78, 95, 88, 73, 99, 61, 54, 82, 76, 68, 91, 55, 83};
    int n = sizeof(scores) / sizeof(scores[0]);

    int grade[5] = {};   // [0]=F [1]=D [2]=C [3]=B [4]=A

    for (int i = 0; i < n; i++) {
        if      (scores[i] >= 90) grade[4]++;
        else if (scores[i] >= 80) grade[3]++;
        else if (scores[i] >= 70) grade[2]++;
        else if (scores[i] >= 60) grade[1]++;
        else                      grade[0]++;
    }

    char labels[] = {'F', 'D', 'C', 'B', 'A'};

    cout << "成績分布：" << endl;
    cout << "─────────────────────────────" << endl;

    for (int i = 4; i >= 0; i--) {   // 從 A 印到 F
        cout << labels[i] << " | ";
        for (int j = 0; j < grade[i]; j++) cout << "█";
        cout << " " << grade[i] << endl;
    }

    cout << "─────────────────────────────" << endl;
    cout << "共 " << n << " 位學生" << endl;

    return 0;
}
```

**輸出：**
```
成績分布：
─────────────────────────────
A | ████ 4
B | ████ 4
C | ███ 3
D | ██ 2
F | ██ 2
─────────────────────────────
共 15 位學生
```

---

### 7.4.8 反轉陣列

📄 **範例檔案：** [ex7_4_8_reverse.cpp](examples/ex7_4_8_reverse.cpp)

```cpp
#include <iostream>
using namespace std;

void reverseArray(int arr[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        int temp    = arr[left];
        arr[left]   = arr[right];
        arr[right]  = temp;
        left++;
        right--;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "原始：";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    reverseArray(arr, n);

    cout << "反轉後：";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
```

**輸出：**
```
原始：1 2 3 4 5 6 7
反轉後：7 6 5 4 3 2 1
```

---

## 7.5 多維陣列

### 7.5.1 二維陣列概念

二維陣列可以想像成一個**表格（矩陣）**，有列（Row）和行（Column）。

```cpp
int matrix[3][4];   // 3 列、4 行的二維陣列
```

**視覺化（3×4 矩陣）：**

```
          行0  行1  行2  行3
列0  →  [ 1][ 2][ 3][ 4]
列1  →  [ 5][ 6][ 7][ 8]
列2  →  [ 9][10][11][12]

存取：matrix[列][行]
matrix[0][0] = 1
matrix[1][2] = 7
matrix[2][3] = 12
```

**記憶體中的實際排列（列主序，Row-Major Order）：**

```
位址： 1000 1004 1008 1012 1016 1020 1024 1028 1032 1036 1040 1044
值：    1    2    3    4    5    6    7    8    9   10   11   12
      ◄───── 第0列 ─────►◄───── 第1列 ─────►◄───── 第2列 ─────►
```

> 💡 理解列主序很重要：外層迴圈走列、內層迴圈走行，比反過來快（因為連續存取記憶體，Cache 命中率高）。

### 7.5.2 宣告與初始化

📄 **範例檔案：** [ex7_5_1_2d_init.cpp](examples/ex7_5_1_2d_init.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    // 方式一：宣告時完整初始化（推薦，清楚明瞭）
    int a[3][4] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };

    // 方式二：一行初始化（不推薦，難讀）
    int b[3][4] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    // 方式三：全部初始化為 0
    int c[3][4] = {};

    // 方式四：部分初始化（其餘補 0）
    int d[3][3] = {{1}, {4, 5}, {7, 8, 9}};
    // d = {{1,0,0}, {4,5,0}, {7,8,9}}

    // 列印二維陣列
    cout << "矩陣 a：" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << a[i][j];
            if (j < 3) cout << "\t";
        }
        cout << endl;
    }

    cout << "\n矩陣 d：" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << d[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}
```

**輸出：**
```
矩陣 a：
1	2	3	4
5	6	7	8
9	10	11	12

矩陣 d：
1	0	0
4	5	0
7	8	9
```

---

### 7.5.3 遍歷二維陣列

📄 **範例檔案：** [ex7_5_2_2d_traverse.cpp](examples/ex7_5_2_2d_traverse.cpp)

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int rows = 3, cols = 4;
    int matrix[3][4] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };

    // 標準遍歷（列主序：先行後列，Cache 友好）
    cout << "標準遍歷（行主序）：" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(4) << matrix[i][j];
        }
        cout << endl;
    }

    // 計算每列總和
    cout << "\n每列總和：" << endl;
    for (int i = 0; i < rows; i++) {
        int rowSum = 0;
        for (int j = 0; j < cols; j++) rowSum += matrix[i][j];
        cout << "第 " << i << " 列：" << rowSum << endl;
    }

    // 計算每行總和
    cout << "\n每行總和：" << endl;
    for (int j = 0; j < cols; j++) {
        int colSum = 0;
        for (int i = 0; i < rows; i++) colSum += matrix[i][j];
        cout << "第 " << j << " 行：" << colSum << endl;
    }

    // 對角線（方陣才有，取 rows==cols 的情況）
    int sq[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int diagSum = 0;
    for (int i = 0; i < 3; i++) diagSum += sq[i][i];
    cout << "\n對角線總和：" << diagSum << endl;   // 1+5+9=15

    return 0;
}
```

---

### 7.5.4 二維陣列傳入函式

傳入函式時，**行數（第二維大小）必須在參數中指定**：

```cpp
void print(int arr[][4], int rows) {   // 行數必須固定
    ...
}
```

📄 **範例檔案：** [ex7_5_3_2d_function.cpp](examples/ex7_5_3_2d_function.cpp)

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

const int COLS = 4;

void printMatrix(const int arr[][COLS], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << setw(5) << arr[i][j];
        }
        cout << endl;
    }
}

int sumAll(const int arr[][COLS], int rows) {
    int total = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < COLS; j++)
            total += arr[i][j];
    return total;
}

int main() {
    int matrix[3][COLS] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };

    cout << "矩陣：" << endl;
    printMatrix(matrix, 3);

    cout << "\n所有元素總和：" << sumAll(matrix, 3) << endl;

    return 0;
}
```

---

### 7.5.5 三維陣列（簡介）

三維陣列可以理解為「多個二維陣列疊在一起」：

```cpp
int cube[2][3][4];   // 2 層、每層 3×4
```

```
層 0：          層 1：
 1  2  3  4      13 14 15 16
 5  6  7  8      17 18 19 20
 9 10 11 12      21 22 23 24

cube[0][1][2] = 7   （第0層、第1列、第2行）
cube[1][2][3] = 24  （第1層、第2列、第3行）
```

實際應用：
- RGB 圖片：`pixel[height][width][3]`（3 個色板）
- 3D 遊戲地圖：`map[z][y][x]`
- 時間序列矩陣：`data[時間][列][行]`

---

## 7.6 多維陣列應用

### 7.6.1 矩陣加法

📄 **範例檔案：** [ex7_6_1_matrix_add.cpp](examples/ex7_6_1_matrix_add.cpp)

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

const int N = 3;   // 使用 N×N 方陣

void printMatrix(const int m[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(6) << m[i][j];
        }
        cout << endl;
    }
}

void addMatrix(const int A[][N], const int B[][N], int C[][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C[i][j] = A[i][j] + B[i][j];
}

int main() {
    int A[N][N] = {{1, 2, 3},
                   {4, 5, 6},
                   {7, 8, 9}};

    int B[N][N] = {{9, 8, 7},
                   {6, 5, 4},
                   {3, 2, 1}};

    int C[N][N] = {};

    addMatrix(A, B, C);

    cout << "矩陣 A：" << endl;
    printMatrix(A);

    cout << "\n矩陣 B：" << endl;
    printMatrix(B);

    cout << "\nA + B = " << endl;
    printMatrix(C);

    return 0;
}
```

**輸出：**
```
矩陣 A：
     1     2     3
     4     5     6
     7     8     9

矩陣 B：
     9     8     7
     6     5     4
     3     2     1

A + B =
    10    10    10
    10    10    10
    10    10    10
```

---

### 7.6.2 矩陣乘法

A（m×n）× B（n×p）= C（m×p）

C[i][j] = Σ A[i][k] × B[k][j]，k 從 0 到 n-1

📄 **範例檔案：** [ex7_6_2_matrix_multiply.cpp](examples/ex7_6_2_matrix_multiply.cpp)

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

const int M = 2;   // A 的列數
const int N = 3;   // A 的行數 = B 的列數
const int P = 2;   // B 的行數

void multiplyMatrix(const int A[][N], const int B[][P], int C[][P]) {
    // 初始化 C 為 0
    for (int i = 0; i < M; i++)
        for (int j = 0; j < P; j++)
            C[i][j] = 0;

    // 矩陣乘法
    for (int i = 0; i < M; i++)
        for (int j = 0; j < P; j++)
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
}

int main() {
    int A[M][N] = {{1, 2, 3},
                   {4, 5, 6}};

    int B[N][P] = {{7, 8},
                   {9, 10},
                   {11, 12}};

    int C[M][P] = {};

    multiplyMatrix(A, B, C);

    cout << "A（2×3）：" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) cout << setw(5) << A[i][j];
        cout << endl;
    }

    cout << "\nB（3×2）：" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) cout << setw(5) << B[i][j];
        cout << endl;
    }

    cout << "\nA × B（2×2）：" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) cout << setw(5) << C[i][j];
        cout << endl;
    }

    return 0;
}
```

**輸出：**
```
A（2×3）：
    1    2    3
    4    5    6

B（3×2）：
    7    8
    9   10
   11   12

A × B（2×2）：
   58   64
  139  154
```

---

### 7.6.3 矩陣轉置（Transpose）

將矩陣的列和行互換：C[i][j] = A[j][i]

📄 **範例檔案：** [ex7_6_3_transpose.cpp](examples/ex7_6_3_transpose.cpp)

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

const int ROWS = 3, COLS = 4;

void transpose(const int A[][COLS], int B[][ROWS]) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            B[j][i] = A[i][j];
}

int main() {
    int A[ROWS][COLS] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };

    int B[COLS][ROWS] = {};
    transpose(A, B);

    cout << "原矩陣 A（3×4）：" << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) cout << setw(5) << A[i][j];
        cout << endl;
    }

    cout << "\n轉置後 B（4×3）：" << endl;
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) cout << setw(5) << B[i][j];
        cout << endl;
    }

    return 0;
}
```

**輸出：**
```
原矩陣 A（3×4）：
    1    2    3    4
    5    6    7    8
    9   10   11   12

轉置後 B（4×3）：
    1    5    9
    2    6   10
    3    7   11
    4    8   12
```

---

### 7.6.4 井字遊戲（Tic-Tac-Toe）

用 `3×3` 二維陣列實作井字遊戲棋盤。

📄 **範例檔案：** [ex7_6_4_tictactoe.cpp](examples/ex7_6_4_tictactoe.cpp)

```cpp
#include <iostream>
#include <cassert>
using namespace std;

// 棋盤：0=空, 1=X, 2=O
int board[3][3] = {};

void printBoard() {
    cout << "  0 1 2" << endl;
    for (int i = 0; i < 3; i++) {
        cout << i << " ";
        for (int j = 0; j < 3; j++) {
            if      (board[i][j] == 0) cout << ".";
            else if (board[i][j] == 1) cout << "X";
            else                       cout << "O";
            if (j < 2) cout << "|";
        }
        cout << endl;
        if (i < 2) cout << "  ─────" << endl;
    }
}

bool checkWin(int player) {
    // 檢查每列
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
    }
    // 檢查每行
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
            return true;
    }
    // 對角線
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    return false;
}

bool isFull() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == 0) return false;
    return true;
}

int main() {
    cout << "=== 井字遊戲 ===" << endl;
    cout << "玩家1 = X，玩家2 = O" << endl;
    cout << "輸入格式：列 行（例如：1 2）" << endl << endl;

    int currentPlayer = 1;

    while (true) {
        printBoard();
        cout << endl;

        cout << "玩家 " << currentPlayer << " (" << (currentPlayer == 1 ? "X" : "O") << ") 請走棋：";
        int row, col;
        cin >> row >> col;

        // 邊界檢查
        if (row < 0 || row > 2 || col < 0 || col > 2) {
            cout << "超出範圍，請重新輸入！" << endl;
            continue;
        }
        // 已有棋子
        if (board[row][col] != 0) {
            cout << "該位置已有棋子，請重新輸入！" << endl;
            continue;
        }

        board[row][col] = currentPlayer;

        if (checkWin(currentPlayer)) {
            printBoard();
            cout << "\n玩家 " << currentPlayer << " 獲勝！" << endl;
            break;
        }

        if (isFull()) {
            printBoard();
            cout << "\n平局！" << endl;
            break;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    return 0;
}
```

**執行範例：**
```
=== 井字遊戲 ===
玩家1 = X，玩家2 = O
輸入格式：列 行（例如：1 2）

  0 1 2
0 .|.|.
  ─────
1 .|.|.
  ─────
2 .|.|.

玩家 1 (X) 請走棋：1 1
  0 1 2
0 .|.|.
  ─────
1 .|X|.
  ─────
2 .|.|.
...
```

---

## 章節總結

```
陣列（Array）
│
├─ 7.1 屬性
│   ├─ 相同型別、連續記憶體、固定大小、從零索引
│   └─ sizeof() 計算大小
│
├─ 7.2 一維陣列
│   ├─ int arr[N]               宣告
│   ├─ int arr[] = {1,2,3}      初始化（自動推算大小）
│   ├─ arr[i]                   存取（0 ~ N-1）
│   ├─ for (int x : arr)        範圍型 for（遍歷用）
│   ├─ void f(int arr[], int n) 傳入函式（需附大小）
│   └─ ⚠ 越界存取：未定義行為，極度危險
│
├─ 7.3 assert
│   ├─ #include <cassert>
│   ├─ assert(條件)              條件為 false 時程式終止
│   ├─ 適合：邏輯不變式、邊界檢查（開發期）
│   └─ #define NDEBUG           發布時關閉所有 assert
│
├─ 7.4 一維陣列應用
│   ├─ 最大/最小值、統計（平均/標準差）
│   ├─ 線性搜尋 O(n)、二分搜尋 O(log n)（需排序）
│   ├─ 泡沫排序 O(n²)、選擇排序 O(n²)
│   └─ 反轉、直方圖
│
├─ 7.5 多維陣列
│   ├─ int m[R][C]              二維陣列（R列C行）
│   ├─ m[i][j]                  存取（列i行j）
│   ├─ 列主序（Row-Major）      記憶體連續存放
│   ├─ void f(int m[][C], int R) 傳入函式（需指定行數）
│   └─ 三維：int cube[L][R][C]
│
└─ 7.6 多維陣列應用
    ├─ 矩陣加法：C[i][j] = A[i][j] + B[i][j]
    ├─ 矩陣乘法：C[i][j] = Σ A[i][k]*B[k][j]
    ├─ 轉置：    B[j][i] = A[i][j]
    └─ 遊戲棋盤（井字遊戲）
```

---

## 實作練習

> 以下練習請獨立完成後，再對照參考解答。

---

### 練習 7-1：陣列反轉輸出

**題目：** 輸入 n 個整數（n ≤ 20），以相反順序輸出。

**輸入範例：**
```
請輸入個數：5
請輸入 5 個整數：3 1 4 1 5
```

**輸出範例：**
```
反轉後：5 1 4 1 3
```

📄 **練習檔案：** `hw7_1_reverse_output.cpp`

---

### 練習 7-2：陣列旋轉

**題目：** 輸入 n 個整數，將陣列向右旋轉 k 個位置。

**輸入範例：**
```
個數：5
陣列：1 2 3 4 5
旋轉：2
```

**輸出範例：**
```
旋轉後：4 5 1 2 3
```

📄 **練習檔案：** `hw7_2_rotate_array.cpp`

---

### 練習 7-3：成績統計

**題目：** 輸入 n 個學生的成績（0~100），輸出最高分、最低分、平均分（保留 2 位小數），並統計各等級人數（A/B/C/D/F）。

📄 **練習檔案：** `hw7_3_grade_stats.cpp`

---

### 練習 7-4：去除重複

**題目：** 輸入 n 個整數，輸出去除重複後的陣列（保留第一次出現的順序）。

**輸入範例：**
```
個數：8
陣列：3 1 4 1 5 9 2 6
```

**輸出範例：**（只輸出不重複的元素，保留第一次出現順序）
```
去除重複：3 1 4 5 9 2 6
```

📄 **練習檔案：** `hw7_4_remove_duplicate.cpp`

---

### 練習 7-5：二分搜尋實作

**題目：** 實作一個完整的二分搜尋程式。先輸入 n 個整數，程式自動排序後，輸入目標值，輸出找到的位置（如有多個，回傳第一個）。

📄 **練習檔案：** `hw7_5_binary_search.cpp`

---

### 練習 7-6：矩陣旋轉 90 度

**題目：** 輸入一個 N×N 方陣，輸出順時針旋轉 90 度後的矩陣。

**規律：** 旋轉後 B[i][j] = A[N-1-j][i]

**輸入範例（N=3）：**
```
1 2 3
4 5 6
7 8 9
```

**輸出範例：**
```
7 4 1
8 5 2
9 6 3
```

📄 **練習檔案：** `hw7_6_rotate_matrix.cpp`

---

### 練習 7-7：魔術方陣驗證

**題目：** 輸入一個 3×3 矩陣，判斷是否為魔術方陣（每行、每列、兩條對角線的總和都相等）。

**輸入範例：**
```
2 7 6
9 5 1
4 3 8
```

**輸出範例：**
```
是魔術方陣（總和 = 15）
```

📄 **練習檔案：** `hw7_7_magic_square.cpp`

---

### 練習 7-8：螺旋矩陣

**題目：** 輸入 N，生成 N×N 的螺旋矩陣（從 1 到 N² 依螺旋方向填入）。

**輸入範例：** `N = 4`

**輸出範例：**
```
 1  2  3  4
12 13 14  5
11 16 15  6
10  9  8  7
```

📄 **練習檔案：** `hw7_8_spiral_matrix.cpp`

---

## 面試考題

### 面試題 1

**題目：** 請說明 C++ 陣列的越界存取（Out-of-Bounds Access）會發生什麼事？如何防範？

**參考答案：**

越界存取是**未定義行為（Undefined Behavior）**，可能導致：
1. **讀到垃圾值**：讀取相鄰記憶體的隨機內容
2. **覆蓋其他變數**：寫入越界位置可能破壞其他變數
3. **Segmentation Fault**：存取不屬於程式的記憶體，OS 強制終止
4. **安全漏洞**：緩衝區溢位（Buffer Overflow）是最常見的安全攻擊手法

防範方式：
- 迴圈條件用 `i < n`（不要 `<=`）
- 傳入函式時同時傳入大小
- 開發期用 `assert(index >= 0 && index < n)`
- 使用 `std::vector` 的 `.at()` 方法（會拋出例外）
- 使用 `-fsanitize=address` 編譯選項（AddressSanitizer）

---

### 面試題 2

**題目：** 二分搜尋中，為什麼用 `mid = left + (right - left) / 2` 而不是 `mid = (left + right) / 2`？

**參考答案：**

`(left + right) / 2` 可能發生**整數溢位（Integer Overflow）**：

當 `left` 和 `right` 都接近 `INT_MAX`（2,147,483,647）時，`left + right` 會超過 `int` 的最大值，導致變成負數，結果錯誤。

例如：`left = 2,000,000,000`，`right = 2,000,000,001`
- `left + right = 4,000,000,001` → 超過 INT_MAX（2,147,483,647），溢位為負數
- `left + (right - left) / 2 = 2,000,000,000 + 0 = 2,000,000,000` → 正確

這是面試常問的細節，也是工程師在寫搜尋演算法時必須注意的問題。

---

### 面試題 3

**題目：** 為什麼 C++ 陣列傳入函式後，在函式內部無法用 `sizeof` 得到陣列大小？

**參考答案：**

這是因為**陣列退化為指標（Array Decay）** 的機制：

當陣列作為函式參數傳遞時，C++ 將其隱式轉換為指向第一個元素的指標：
```cpp
void f(int arr[]) { ... }
// 等同於
void f(int* arr) { ... }
```

此時 `sizeof(arr)` 得到的是**指標的大小**（通常是 8 bytes，64位元系統），而非陣列的總大小。

因此，傳入陣列時必須**額外傳入大小 `n`**，或者改用 `std::array<T,N>` 或 `std::vector<T>` 等容器，它們保留了大小資訊。

---

### 面試題 4

**題目：** 請比較泡沫排序和選擇排序，各有什麼特點？

**參考答案：**

**泡沫排序（Bubble Sort）：**
- 時間複雜度：最差/平均 O(n²)，最佳 O(n)（已排序時有早停）
- **穩定排序**：相等元素的相對順序不變
- 交換次數多（最多 n²/2 次）
- 有早停最佳化：若某輪沒有交換，代表已排序完成

**選擇排序（Selection Sort）：**
- 時間複雜度：始終 O(n²)（無論輸入如何）
- **不穩定排序**：交換可能改變相等元素的順序
- **交換次數少**（最多 n-1 次），適合交換成本高的情況（如交換整個物件）
- 沒有早停，效能不隨輸入排序程度改善

**何時用哪個？**
- 幾乎已排序的資料 → 泡沫（有早停）
- 交換成本高的資料 → 選擇（交換少）
- 實務上兩者都太慢，大資料用快速排序或 `std::sort`

---

### 面試題 5

**題目：** 什麼是「列主序（Row-Major Order）」？為什麼遍歷二維陣列時，應該外層迴圈走列、內層迴圈走行？

**參考答案：**

**列主序（Row-Major Order）** 是 C/C++ 中二維陣列在記憶體中的排列方式：同一列的元素在記憶體中**連續存放**。

```
int a[3][4]:
記憶體： a[0][0] a[0][1] a[0][2] a[0][3] | a[1][0] a[1][1] ...
                  第0列全部連續              第1列全部連續
```

**效能影響（Cache 局部性）：**
- CPU 有快取（Cache），讀取資料時會預先載入**相鄰的記憶體區塊**
- 若外層走列、內層走行 → 存取 a[i][0], a[i][1], a[i][2]... 連續，**Cache 命中率高**，速度快
- 若外層走行、內層走列 → 存取 a[0][j], a[1][j], a[2][j]... 跳躍，**Cache 未命中率高**，速度慢（可能慢數倍到十倍）

這在大矩陣運算（機器學習、影像處理）中影響很大，是效能最佳化的基礎知識。

---

## 專案：學生管理系統 2.0

> 本專案整合陣列與格式化輸出，建立完整的學生資料管理系統。

### 需求說明

建立一個程式，管理 N 位學生（N ≤ 30）的資料：
1. 輸入每位學生的姓名（最多 20 字元）和四科成績
2. 計算每位學生的平均分
3. 使用泡沫排序依平均分由高到低排名
4. 輸出排名表格
5. 提供以下查詢功能：
   - 輸入姓名，查詢該學生排名與成績
   - 輸出每科的最高分、最低分、班級平均

### 輸入範例
```
學生人數：4
學生 1 姓名：Alice
  語文：85  數學：92  英文：78  自然：88
學生 2 姓名：Bob
  語文：70  數學：65  英文：80  自然：75
學生 3 姓名：Carol
  語文：95  數學：98  英文：92  自然：96
學生 4 姓名：David
  語文：60  數學：72  英文：55  自然：68
```

### 輸出範例
```
╔══════════════════════════════════════════════════════╗
║                   成績排行榜                          ║
╠══╦════════╦══════╦══════╦══════╦══════╦══════════════╣
║名 ║  姓名  ║ 語文 ║ 數學 ║ 英文 ║ 自然 ║     平均     ║
╠══╬════════╬══════╬══════╬══════╬══════╬══════════════╣
║ 1 ║ Carol  ║   95 ║   98 ║   92 ║   96 ║        95.25 ║
║ 2 ║ Alice  ║   85 ║   92 ║   78 ║   88 ║        85.75 ║
║ 3 ║ Bob    ║   70 ║   65 ║   80 ║   75 ║        72.50 ║
║ 4 ║ David  ║   60 ║   72 ║   55 ║   68 ║        63.75 ║
╠══╬════════╬══════╬══════╬══════╬══════╬══════════════╣
║班均║       ║77.50 ║81.75 ║76.25 ║81.75 ║        79.31 ║
║最高║       ║   95 ║   98 ║   92 ║   96 ║              ║
║最低║       ║   60 ║   65 ║   55 ║   68 ║              ║
╚══╩════════╩══════╩══════╩══════╩══════╩══════════════╝

查詢學生（輸入姓名，q 結束）：Alice
Alice | 排名第 2 | 語文:85 數學:92 英文:78 自然:88 | 平均:85.75
```

📄 **專案檔案：** `project7_student_system.cpp`

---

### 專案解答

📄 **解答檔案：** [project7_student_system_answer.cpp](examples/project7_student_system_answer.cpp)

```cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cassert>
using namespace std;

const int MAX_N    = 30;
const int SUBJECTS = 4;
const string SUBJECT_NAMES[] = {"語文", "數學", "英文", "自然"};

struct Student {
    string name;
    int    scores[SUBJECTS];
    double avg;
    int    rank;
};

void calcAvg(Student students[], int n) {
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < SUBJECTS; j++) sum += students[i].scores[j];
        students[i].avg = sum / SUBJECTS;
    }
}

// 依平均分由高到低泡沫排序
void sortByAvg(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (students[j].avg < students[j + 1].avg) {
                Student temp    = students[j];
                students[j]     = students[j + 1];
                students[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    for (int i = 0; i < n; i++) students[i].rank = i + 1;
}

void printTable(const Student students[], int n) {
    cout << "╔══════════════════════════════════════════════════════╗\n";
    cout << "║                   成績排行榜                          ║\n";
    cout << "╠═══╦════════╦══════╦══════╦══════╦══════╦════════════╣\n";
    cout << "║ 名║  姓名  ║ 語文 ║ 數學 ║ 英文 ║ 自然 ║    平均    ║\n";
    cout << "╠═══╬════════╬══════╬══════╬══════╬══════╬════════════╣\n";

    cout << fixed << setprecision(2);

    for (int i = 0; i < n; i++) {
        cout << "║" << setw(3) << students[i].rank
             << "║" << left << setw(8) << students[i].name << right
             << "║" << setw(6) << students[i].scores[0]
             << "║" << setw(6) << students[i].scores[1]
             << "║" << setw(6) << students[i].scores[2]
             << "║" << setw(6) << students[i].scores[3]
             << "║" << setw(12) << students[i].avg
             << "║\n";
    }

    // 統計
    cout << "╠═══╬════════╬══════╬══════╬══════╬══════╬════════════╣\n";

    double classAvg[SUBJECTS] = {};
    int    maxSc[SUBJECTS], minSc[SUBJECTS];
    for (int j = 0; j < SUBJECTS; j++) {
        maxSc[j] = minSc[j] = students[0].scores[j];
        for (int i = 0; i < n; i++) {
            classAvg[j] += students[i].scores[j];
            if (students[i].scores[j] > maxSc[j]) maxSc[j] = students[i].scores[j];
            if (students[i].scores[j] < minSc[j]) minSc[j] = students[i].scores[j];
        }
        classAvg[j] /= n;
    }

    double totalAvg = 0;
    for (int j = 0; j < SUBJECTS; j++) totalAvg += classAvg[j];
    totalAvg /= SUBJECTS;

    cout << "║班均║        ";
    for (int j = 0; j < SUBJECTS; j++) cout << "║" << setw(6) << classAvg[j];
    cout << "║" << setw(12) << totalAvg << "║\n";

    cout << "║最高║        ";
    for (int j = 0; j < SUBJECTS; j++) cout << "║" << setw(6) << maxSc[j];
    cout << "║" << setw(12) << "" << "║\n";

    cout << "║最低║        ";
    for (int j = 0; j < SUBJECTS; j++) cout << "║" << setw(6) << minSc[j];
    cout << "║" << setw(12) << "" << "║\n";

    cout << "╚═══╩════════╩══════╩══════╩══════╩══════╩════════════╝\n";
}

void queryStudent(const Student students[], int n, const string& target) {
    for (int i = 0; i < n; i++) {
        if (students[i].name == target) {
            cout << students[i].name << " | 排名第 " << students[i].rank << " | ";
            for (int j = 0; j < SUBJECTS; j++) {
                cout << SUBJECT_NAMES[j] << ":" << students[i].scores[j];
                if (j < SUBJECTS - 1) cout << " ";
            }
            cout << " | 平均:" << fixed << setprecision(2) << students[i].avg << endl;
            return;
        }
    }
    cout << "查無此學生：" << target << endl;
}

int main() {
    Student students[MAX_N];
    int n;

    cout << "學生人數（1~" << MAX_N << "）：";
    cin >> n;
    assert(n >= 1 && n <= MAX_N);

    for (int i = 0; i < n; i++) {
        cout << "\n學生 " << (i + 1) << " 姓名：";
        cin >> students[i].name;
        for (int j = 0; j < SUBJECTS; j++) {
            cout << "  " << SUBJECT_NAMES[j] << "：";
            cin >> students[i].scores[j];
        }
    }

    calcAvg(students, n);
    sortByAvg(students, n);

    cout << "\n";
    printTable(students, n);

    cout << "\n查詢學生（輸入姓名，q 結束）：";
    string query;
    while (cin >> query && query != "q") {
        queryStudent(students, n, query);
        cout << "查詢學生（輸入姓名，q 結束）：";
    }

    return 0;
}
```
