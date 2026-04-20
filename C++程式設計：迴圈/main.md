# 第五章：迴圈（Loop）

> **學習目標**
> - 理解迴圈的概念與使用時機
> - 熟悉 `while`、`do-while`、`for` 三種迴圈語法
> - 掌握 `break` 與 `continue` 的用途
> - 能夠撰寫巢狀迴圈解決二維問題
> - 具備用迴圈解決實際問題的能力

---

## 5.0 為什麼需要迴圈？

想像一個情境：你要印出 1 到 100 的所有數字。

如果沒有迴圈，你必須寫 100 行 `cout`：

```cpp
cout << 1 << endl;
cout << 2 << endl;
cout << 3 << endl;
// ... 一直到 100
cout << 100 << endl;
```

這顯然既費時又容易出錯。**迴圈**讓我們只需寫一段程式，讓電腦重複執行：

```cpp
for (int i = 1; i <= 100; i++) {
    cout << i << endl;
}
```

迴圈是程式設計中最重要的概念之一，幾乎所有實際應用都離不開它。

---

## 5.1 `while` 迴圈

### 語法結構

```
while (條件式) {
    // 迴圈主體（重複執行的程式碼）
}
```

**執行流程：**
1. 判斷條件式是否為 `true`
2. 若為 `true`，執行迴圈主體
3. 執行完畢後，回到步驟 1
4. 若為 `false`，離開迴圈，繼續執行後面的程式

```
┌──────────────────────────────┐
│         開始                  │
└──────────────┬───────────────┘
               ↓
       ┌───────────────┐
       │  條件式成立？  │◄──────────┐
       └───┬───────┬───┘           │
          是│       │否             │
           ↓       ↓               │
     ┌──────────┐  結束            │
     │ 執行主體 │                  │
     └──────────┘                  │
          │                        │
          └────────────────────────┘
```

### 範例 5.1.1：印出 1 到 10

📄 **範例檔案：** [ex5_1_1_while_basic.cpp](examples/ex5_1_1_while_basic.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int i = 1;               // 初始化計數變數

    while (i <= 10) {        // 條件：i 小於等於 10
        cout << i << endl;   // 印出 i
        i++;                 // 更新：i 加 1（非常重要！）
    }

    return 0;
}
```

**輸出：**
```
1
2
3
4
5
6
7
8
9
10
```

> ⚠️ **常見錯誤：忘記更新計數變數**
> 如果忘記寫 `i++`，`i` 永遠是 1，條件 `i <= 10` 永遠成立，造成**無窮迴圈（infinite loop）**，程式永遠不會停止！

### 範例 5.1.2：計算 1 + 2 + ... + 100

📄 **範例檔案：** [ex5_1_2_while_sum.cpp](examples/ex5_1_2_while_sum.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int i = 1;
    int sum = 0;

    while (i <= 100) {
        sum += i;   // sum = sum + i
        i++;
    }

    cout << "1 到 100 的總和為：" << sum << endl;

    return 0;
}
```

**輸出：**
```
1 到 100 的總和為：5050
```

> 💡 **小知識：** 數學家高斯（Gauss）小時候用公式 n(n+1)/2 秒算出這個答案。電腦則用迴圈暴力計算，同樣得到 5050。

### 範例 5.1.3：使用者輸入控制迴圈

📄 **範例檔案：** [ex5_1_3_while_input.cpp](examples/ex5_1_3_while_input.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int number;
    int sum = 0;
    int count = 0;

    cout << "請輸入整數（輸入 0 結束）：" << endl;

    cin >> number;

    while (number != 0) {       // 輸入 0 時停止
        sum += number;
        count++;
        cin >> number;          // 繼續讀取下一個數
    }

    if (count > 0) {
        cout << "共輸入 " << count << " 個數" << endl;
        cout << "總和：" << sum << endl;
        cout << "平均：" << (double)sum / count << endl;
    } else {
        cout << "未輸入任何數字" << endl;
    }

    return 0;
}
```

**執行範例：**
```
請輸入整數（輸入 0 結束）：
10
20
30
0
共輸入 3 個數
總和：60
平均：20
```

### 範例 5.1.4：猜數字遊戲

📄 **範例檔案：** [ex5_1_4_while_guess.cpp](examples/ex5_1_4_while_guess.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int secret = 42;    // 秘密數字
    int guess;
    int attempts = 0;

    cout << "=== 猜數字遊戲 ===" << endl;
    cout << "請猜一個 1 到 100 之間的數字：" << endl;

    cin >> guess;
    attempts++;

    while (guess != secret) {
        if (guess < secret) {
            cout << "太小了！再猜一次：";
        } else {
            cout << "太大了！再猜一次：";
        }
        cin >> guess;
        attempts++;
    }

    cout << "恭喜！答對了！" << endl;
    cout << "你共猜了 " << attempts << " 次" << endl;

    return 0;
}
```

### `do-while` 迴圈

`do-while` 是 `while` 的變體，**先執行一次主體，再判斷條件**。

```
do {
    // 迴圈主體（至少執行一次）
} while (條件式);
```

```
┌──────────────────────────────┐
│         開始                  │
└──────────────┬───────────────┘
               ↓
     ┌──────────────────┐
     │    執行主體       │◄──────────┐
     └────────┬─────────┘           │
              ↓                     │
      ┌───────────────┐             │
      │  條件式成立？  │             │
      └───┬───────┬───┘             │
         是│       │否               │
           └───────┘                │
                                    │
          （是）────────────────────┘
          （否）→ 結束
```

### 範例 5.1.5：do-while 輸入驗證

📄 **範例檔案：** [ex5_1_5_dowhile.cpp](examples/ex5_1_5_dowhile.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int age;

    do {
        cout << "請輸入年齡（1-150）：";
        cin >> age;

        if (age < 1 || age > 150) {
            cout << "輸入無效，請重新輸入！" << endl;
        }
    } while (age < 1 || age > 150);   // 輸入無效就重複

    cout << "你的年齡是：" << age << endl;

    return 0;
}
```

> 💡 **`while` vs `do-while` 選擇原則：**
> - 若條件**可能一開始就不成立**（迴圈可能執行 0 次）→ 用 `while`
> - 若**至少需要執行一次**（如輸入驗證、顯示選單）→ 用 `do-while`

---

## 5.2 `for` 迴圈

`for` 迴圈是最常用的迴圈，特別適合**已知執行次數**的情況。

### 語法結構

```
for (初始化; 條件式; 更新) {
    // 迴圈主體
}
```

| 部分 | 說明 | 執行時機 |
|------|------|----------|
| 初始化 | 設定計數變數初始值 | 只執行一次（迴圈開始前） |
| 條件式 | 判斷是否繼續 | 每次執行主體**前**都判斷 |
| 更新 | 更新計數變數 | 每次執行主體**後**都執行 |

**執行順序：**
```
初始化 → [判斷條件] → 執行主體 → 更新 → [判斷條件] → 執行主體 → 更新 → ...
```

### 範例 5.2.1：基本計數

📄 **範例檔案：** [ex5_2_1_for_basic.cpp](examples/ex5_2_1_for_basic.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    // 正向計數
    cout << "正向計數：";
    for (int i = 1; i <= 5; i++) {
        cout << i << " ";
    }
    cout << endl;

    // 反向計數
    cout << "反向計數：";
    for (int i = 5; i >= 1; i--) {
        cout << i << " ";
    }
    cout << endl;

    // 間隔計數（每次加 2）
    cout << "偶數：";
    for (int i = 2; i <= 10; i += 2) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
```

**輸出：**
```
正向計數：1 2 3 4 5
反向計數：5 4 3 2 1
偶數：2 4 6 8 10
```

### 範例 5.2.2：計算階乘

📄 **範例檔案：** [ex5_2_2_for_factorial.cpp](examples/ex5_2_2_for_factorial.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "請輸入 n：";
    cin >> n;

    long long factorial = 1;    // 用 long long 避免溢位

    for (int i = 1; i <= n; i++) {
        factorial *= i;          // factorial = factorial * i
    }

    cout << n << "! = " << factorial << endl;

    return 0;
}
```

**執行範例：**
```
請輸入 n：10
10! = 3628800
```

### 範例 5.2.3：九九乘法表（單行）

📄 **範例檔案：** [ex5_2_3_for_multiplication.cpp](examples/ex5_2_3_for_multiplication.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "請輸入要顯示哪個乘法表（1-9）：";
    cin >> n;

    for (int i = 1; i <= 9; i++) {
        cout << n << " × " << i << " = " << n * i << endl;
    }

    return 0;
}
```

**執行範例（輸入 7）：**
```
7 × 1 = 7
7 × 2 = 14
7 × 3 = 21
7 × 4 = 28
7 × 5 = 35
7 × 6 = 42
7 × 7 = 49
7 × 8 = 56
7 × 9 = 63
```

### 範例 5.2.4：找出最大值與最小值

📄 **範例檔案：** [ex5_2_4_for_minmax.cpp](examples/ex5_2_4_for_minmax.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "請輸入數字個數：";
    cin >> n;

    int num;
    cout << "請輸入第 1 個數字：";
    cin >> num;

    int maxVal = num;
    int minVal = num;

    for (int i = 2; i <= n; i++) {
        cout << "請輸入第 " << i << " 個數字：";
        cin >> num;

        if (num > maxVal) maxVal = num;
        if (num < minVal) minVal = num;
    }

    cout << "最大值：" << maxVal << endl;
    cout << "最小值：" << minVal << endl;

    return 0;
}
```

### 範例 5.2.5：判斷質數

📄 **範例檔案：** [ex5_2_5_for_prime.cpp](examples/ex5_2_5_for_prime.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "請輸入一個正整數：";
    cin >> n;

    if (n < 2) {
        cout << n << " 不是質數" << endl;
        return 0;
    }

    bool isPrime = true;

    for (int i = 2; i * i <= n; i++) {   // 只需檢查到 √n
        if (n % i == 0) {
            isPrime = false;
            break;
        }
    }

    if (isPrime) {
        cout << n << " 是質數" << endl;
    } else {
        cout << n << " 不是質數" << endl;
    }

    return 0;
}
```

> 💡 **為什麼只需檢查到 √n？**
> 若 n = a × b，且 a ≤ b，則 a ≤ √n。
> 所以只要找到 √n 以內的因數就夠了，可大幅減少計算量。

### 範例 5.2.6：`while` vs `for` 對比

📄 **範例檔案：** [ex5_2_6_while_vs_for.cpp](examples/ex5_2_6_while_vs_for.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    // 用 for 迴圈印出 1 到 5
    cout << "for 迴圈：";
    for (int i = 1; i <= 5; i++) {
        cout << i << " ";
    }
    cout << endl;

    // 完全等價的 while 迴圈
    cout << "while 迴圈：";
    int i = 1;          // 初始化（在迴圈外）
    while (i <= 5) {    // 條件
        cout << i << " ";
        i++;            // 更新（在主體內）
    }
    cout << endl;

    return 0;
}
```

> 💡 **選擇 `for` 還是 `while`？**
> - **已知次數** → 用 `for`（更簡潔、不易忘記更新）
> - **未知次數，依條件決定** → 用 `while`（如：讀到特定輸入為止）

---

## 5.4 `break` 敘述

`break` 用於**立即跳出**目前所在的迴圈（或 `switch`），繼續執行迴圈後面的程式碼。

```
while (條件) {
    ...
    if (某條件) break;    // 立即離開迴圈
    ...
}
// break 後跳到這裡
```

### 範例 5.4.1：搜尋第一個符合條件的數

📄 **範例檔案：** [ex5_4_1_break_search.cpp](examples/ex5_4_1_break_search.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int target;
    cout << "請輸入要搜尋的數字：";
    cin >> target;

    bool found = false;

    for (int i = 1; i <= 100; i++) {
        if (i % target == 0 && i != target) {
            cout << target << " 的第一個大於自身的倍數是：" << i << endl;
            found = true;
            break;    // 找到後立即停止
        }
    }

    if (!found) {
        cout << "在 1-100 範圍內找不到" << endl;
    }

    return 0;
}
```

### 範例 5.4.2：提前終止的選單系統

📄 **範例檔案：** [ex5_4_2_break_menu.cpp](examples/ex5_4_2_break_menu.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int choice;

    while (true) {       // 無窮迴圈，靠 break 離開
        cout << "\n=== 主選單 ===" << endl;
        cout << "1. 問候" << endl;
        cout << "2. 計算 1+2+...+10" << endl;
        cout << "3. 離開" << endl;
        cout << "請選擇：";
        cin >> choice;

        if (choice == 1) {
            cout << "Hello, World!" << endl;
        } else if (choice == 2) {
            int sum = 0;
            for (int i = 1; i <= 10; i++) sum += i;
            cout << "1+2+...+10 = " << sum << endl;
        } else if (choice == 3) {
            cout << "再見！" << endl;
            break;       // 離開 while 迴圈
        } else {
            cout << "無效選項，請重新輸入" << endl;
        }
    }

    return 0;
}
```

### 範例 5.4.3：質數搜尋優化（break 的實際應用）

📄 **範例檔案：** [ex5_4_3_break_prime_list.cpp](examples/ex5_4_3_break_prime_list.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int limit;
    cout << "列出 2 到多少之間的質數：";
    cin >> limit;

    int count = 0;

    for (int n = 2; n <= limit; n++) {
        bool isPrime = true;

        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                isPrime = false;
                break;      // 找到因數，不需繼續檢查
            }
        }

        if (isPrime) {
            cout << n << " ";
            count++;
        }
    }

    cout << endl;
    cout << "共 " << count << " 個質數" << endl;

    return 0;
}
```

---

## 5.5 `continue` 敘述

`continue` 用於**跳過**當次迴圈剩餘的程式碼，直接進入下一次迭代。

```
for (int i = 0; i < n; i++) {
    if (某條件) continue;    // 跳過本次，進入下一次
    ...                       // 這行在 continue 後不會執行
}
```

> ⚠️ **注意：** `continue` 只跳過**本次**的剩餘程式碼，不是跳出迴圈。

### 範例 5.5.1：跳過特定數字

📄 **範例檔案：** [ex5_5_1_continue_skip.cpp](examples/ex5_5_1_continue_skip.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "1 到 10 中，跳過 3 的倍數：";

    for (int i = 1; i <= 10; i++) {
        if (i % 3 == 0) {
            continue;    // 跳過 3、6、9
        }
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
```

**輸出：**
```
1 到 10 中，跳過 3 的倍數：1 2 4 5 7 8 10
```

### 範例 5.5.2：只加總奇數

📄 **範例檔案：** [ex5_5_2_continue_odd_sum.cpp](examples/ex5_5_2_continue_odd_sum.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int sum = 0;

    for (int i = 1; i <= 20; i++) {
        if (i % 2 == 0) continue;    // 跳過偶數
        sum += i;
    }

    cout << "1 到 20 中所有奇數的總和：" << sum << endl;

    return 0;
}
```

**輸出：**
```
1 到 20 中所有奇數的總和：100
```

### 範例 5.5.3：輸入過濾（忽略負數）

📄 **範例檔案：** [ex5_5_3_continue_filter.cpp](examples/ex5_5_3_continue_filter.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "請輸入 5 個正整數（負數會被忽略，直到收集夠 5 個）：" << endl;

    int count = 0;
    int sum = 0;

    while (count < 5) {
        int x;
        cin >> x;

        if (x < 0) {
            cout << "  忽略負數 " << x << endl;
            continue;    // 跳過本次，不計入
        }

        sum += x;
        count++;
        cout << "  已收集 " << count << " 個" << endl;
    }

    cout << "5 個正整數的總和：" << sum << endl;
    cout << "平均：" << (double)sum / 5 << endl;

    return 0;
}
```

### `break` vs `continue` 比較

| | `break` | `continue` |
|--|---------|------------|
| 作用 | **跳出**整個迴圈 | **跳過**本次，繼續下一次 |
| 迴圈是否結束 | 是 | 否 |
| 常見用途 | 提前結束搜尋、離開選單 | 過濾資料、跳過特殊情況 |

---

## 5.6 巢狀迴圈（Nested Loop）

**巢狀迴圈**是指迴圈裡面還有另一個迴圈。外層迴圈每執行一次，內層迴圈就會**完整跑完一遍**。

```cpp
for (int i = 0; i < 外層次數; i++) {        // 外層迴圈
    for (int j = 0; j < 內層次數; j++) {    // 內層迴圈
        // 最內層程式碼
    }
}
```

**總執行次數 = 外層次數 × 內層次數**

### 範例 5.6.1：完整九九乘法表

📄 **範例檔案：** [ex5_6_1_nested_multiplication.cpp](examples/ex5_6_1_nested_multiplication.cpp)

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    for (int i = 1; i <= 9; i++) {          // 外層：被乘數
        for (int j = 1; j <= 9; j++) {      // 內層：乘數
            cout << i << "×" << j << "="
                 << setw(2) << i * j << "  ";  // setw(2) 對齊
        }
        cout << endl;    // 換行（每個被乘數一行）
    }

    return 0;
}
```

**輸出：**
```
1×1= 1  1×2= 2  1×3= 3  ...  1×9= 9
2×1= 2  2×2= 4  2×3= 6  ...  2×9=18
...
9×1= 9  9×2=18  9×3=27  ...  9×9=81
```

### 範例 5.6.2：印出矩形星號

📄 **範例檔案：** [ex5_6_2_nested_rectangle.cpp](examples/ex5_6_2_nested_rectangle.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int rows, cols;
    cout << "請輸入列數和行數：";
    cin >> rows >> cols;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "* ";
        }
        cout << endl;
    }

    return 0;
}
```

**執行範例（4 行 6 列）：**
```
* * * * * *
* * * * * *
* * * * * *
* * * * * *
```

### 範例 5.6.3：印出直角三角形

📄 **範例檔案：** [ex5_6_3_nested_triangle.cpp](examples/ex5_6_3_nested_triangle.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "請輸入層數：";
    cin >> n;

    cout << "\n左下直角三角形：" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {    // 第 i 行印 i 個星號
            cout << "* ";
        }
        cout << endl;
    }

    cout << "\n右下直角三角形：" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++) {    // 先印空格
            cout << "  ";
        }
        for (int j = 1; j <= i; j++) {        // 再印星號
            cout << "* ";
        }
        cout << endl;
    }

    return 0;
}
```

**執行範例（n=5）：**
```
左下直角三角形：
*
* *
* * *
* * * *
* * * * *

右下直角三角形：
        *
      * *
    * * *
  * * * *
* * * * *
```

### 範例 5.6.4：印出等腰三角形

📄 **範例檔案：** [ex5_6_4_nested_isosceles.cpp](examples/ex5_6_4_nested_isosceles.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "請輸入層數：";
    cin >> n;

    for (int i = 1; i <= n; i++) {
        // 印空格
        for (int j = 1; j <= n - i; j++) {
            cout << " ";
        }
        // 印星號（第 i 層印 2i-1 個）
        for (int j = 1; j <= 2 * i - 1; j++) {
            cout << "*";
        }
        cout << endl;
    }

    return 0;
}
```

**執行範例（n=5）：**
```
    *
   ***
  *****
 *******
*********
```

### 範例 5.6.5：二維陣列遍歷（矩陣輸出）

📄 **範例檔案：** [ex5_6_5_nested_matrix.cpp](examples/ex5_6_5_nested_matrix.cpp)

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int rows = 3, cols = 4;

    cout << "一個 " << rows << "×" << cols << " 的乘法矩陣：" << endl;

    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            cout << setw(4) << i * j;
        }
        cout << endl;
    }

    return 0;
}
```

**輸出：**
```
一個 3×4 的乘法矩陣：
   1   2   3   4
   2   4   6   8
   3   6   9  12
```

### 範例 5.6.6：巢狀迴圈中的 break

📄 **範例檔案：** [ex5_6_6_nested_break.cpp](examples/ex5_6_6_nested_break.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    // break 只會跳出「最近一層」的迴圈
    for (int i = 1; i <= 3; i++) {
        cout << "外層 i=" << i << "：";

        for (int j = 1; j <= 5; j++) {
            if (j == 3) break;       // 只跳出內層迴圈
            cout << j << " ";
        }

        cout << endl;
    }

    cout << endl;

    // 若要跳出外層迴圈，需要用旗標（flag）
    bool done = false;

    for (int i = 1; i <= 3 && !done; i++) {
        for (int j = 1; j <= 5; j++) {
            if (i == 2 && j == 2) {
                done = true;
                break;
            }
            cout << "(" << i << "," << j << ") ";
        }
    }
    cout << endl;

    return 0;
}
```

**輸出：**
```
外層 i=1：1 2
外層 i=2：1 2
外層 i=3：1 2

(1,1) (1,2) (1,3) (1,4) (1,5) (2,1)
```

---

## 5.7 綜合應用範例

### 範例 5.7.1：FizzBuzz（經典面試題）

📄 **範例檔案：** [ex5_7_1_fizzbuzz.cpp](examples/ex5_7_1_fizzbuzz.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 100; i++) {
        if (i % 15 == 0) {
            cout << "FizzBuzz" << endl;
        } else if (i % 3 == 0) {
            cout << "Fizz" << endl;
        } else if (i % 5 == 0) {
            cout << "Buzz" << endl;
        } else {
            cout << i << endl;
        }
    }

    return 0;
}
```

### 範例 5.7.2：數字金字塔

📄 **範例檔案：** [ex5_7_2_number_pyramid.cpp](examples/ex5_7_2_number_pyramid.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "請輸入層數：";
    cin >> n;

    for (int i = 1; i <= n; i++) {
        // 印空格
        for (int j = 1; j <= n - i; j++) {
            cout << " ";
        }
        // 印數字（遞增）
        for (int j = 1; j <= i; j++) {
            cout << j;
        }
        // 印數字（遞減，不含中間那個）
        for (int j = i - 1; j >= 1; j--) {
            cout << j;
        }
        cout << endl;
    }

    return 0;
}
```

**執行範例（n=5）：**
```
    1
   121
  12321
 1234321
123454321
```

### 範例 5.7.3：歐幾里得輾轉相除法（GCD）

📄 **範例檔案：** [ex5_7_3_gcd.cpp](examples/ex5_7_3_gcd.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b;
    cout << "請輸入兩個正整數：";
    cin >> a >> b;

    int x = a, y = b;

    while (y != 0) {
        int temp = y;
        y = x % y;
        x = temp;
    }

    cout << a << " 和 " << b << " 的最大公因數是：" << x << endl;

    return 0;
}
```

### 範例 5.7.4：數字反轉

📄 **範例檔案：** [ex5_7_4_reverse_number.cpp](examples/ex5_7_4_reverse_number.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "請輸入一個正整數：";
    cin >> n;

    int original = n;
    int reversed = 0;

    while (n > 0) {
        int digit = n % 10;      // 取最後一位
        reversed = reversed * 10 + digit;
        n /= 10;                 // 去掉最後一位
    }

    cout << original << " 反轉後是：" << reversed << endl;

    return 0;
}
```

---

## 總結

| 迴圈種類 | 適用情境 | 特點 |
|----------|----------|------|
| `while` | 條件不確定，可能 0 次 | 先判斷再執行 |
| `do-while` | 至少執行一次 | 先執行再判斷 |
| `for` | 已知執行次數 | 初始化、條件、更新集中 |
| 巢狀迴圈 | 二維問題、圖形輸出 | 總次數 = 外層 × 內層 |

**`break` 與 `continue` 要點：**
- `break`：跳出**整個**當前迴圈
- `continue`：跳過**本次**迭代，繼續下一次
- 在巢狀迴圈中，只影響**最近一層**

---

## 練習題

### 基礎練習

**練習 5-1：** 印出 1 到 50 所有 3 的倍數。

**練習 5-2：** 計算並輸出 1² + 2² + 3² + ... + n² 的值（n 由使用者輸入）。

**練習 5-3：** 使用 `do-while` 實作一個可以重複計算的加法機，使用者輸入兩個數字，程式輸出其和，並詢問是否繼續（輸入 y/n）。

**練習 5-4：** 印出 1 到 100 中，同時是 2 的倍數且個位數為 4 或 8 的數字。

**練習 5-5：** 輸入一個正整數 n，判斷它是否為完全平方數（例如 16 = 4²，是完全平方數）。

### 進階練習

**練習 5-6：** 印出 1 到 100 中所有的質數，每行印 10 個，並在最後顯示共有幾個質數。

**練習 5-7：** 輸入一個正整數，計算其各位數字的總和。例如：1234 → 1+2+3+4 = 10。

**練習 5-8：** 用巢狀迴圈印出以下菱形（n 由使用者輸入，下面為 n=4 的範例）：
```
   *
  ***
 *****
*******
 *****
  ***
   *
```

**練習 5-9：** 實作一個簡單的計算機，支援 +、-、×、÷，使用迴圈持續計算，直到使用者輸入 q 退出。

**練習 5-10：** 找出 1000 以內所有的**完美數**（perfect number）。完美數的定義：一個數等於其所有真因數（不含本身）的總和。例如：6 = 1+2+3，28 = 1+2+4+7+14。

### 圖形練習

**練習 5-11：** 輸入 n，印出以下圖形（n=4）：
```
*
**
***
****
***
**
*
```

**練習 5-12：** 印出 n×n 的空心正方形，例如 n=5：
```
*****
*   *
*   *
*   *
*****
```

---

## 練習題答案

### 練習 5-1 答案

📄 **範例檔案：** [hw5_1_ans.cpp](homework/hw5_1_ans.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "1 到 50 中 3 的倍數：";
    for (int i = 1; i <= 50; i++) {
        if (i % 3 == 0) {
            cout << i << " ";
        }
    }
    cout << endl;
    return 0;
}
```

### 練習 5-2 答案

📄 **範例檔案：** [hw5_2_ans.cpp](homework/hw5_2_ans.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "請輸入 n：";
    cin >> n;

    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += (long long)i * i;
    }

    cout << "1² + 2² + ... + " << n << "² = " << sum << endl;
    return 0;
}
```

### 練習 5-3 答案

📄 **範例檔案：** [hw5_3_ans.cpp](homework/hw5_3_ans.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    char again;

    do {
        int a, b;
        cout << "請輸入兩個整數：";
        cin >> a >> b;
        cout << a << " + " << b << " = " << a + b << endl;

        cout << "繼續計算嗎？(y/n)：";
        cin >> again;
    } while (again == 'y' || again == 'Y');

    cout << "謝謝使用！" << endl;
    return 0;
}
```

### 練習 5-4 答案

📄 **範例檔案：** [hw5_4_ans.cpp](homework/hw5_4_ans.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "1-100 中，2 的倍數且個位是 4 或 8：";
    for (int i = 1; i <= 100; i++) {
        int lastDigit = i % 10;
        if (i % 2 == 0 && (lastDigit == 4 || lastDigit == 8)) {
            cout << i << " ";
        }
    }
    cout << endl;
    return 0;
}
```

### 練習 5-5 答案

📄 **範例檔案：** [hw5_5_ans.cpp](homework/hw5_5_ans.cpp)

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n;
    cout << "請輸入正整數：";
    cin >> n;

    int root = (int)sqrt((double)n);
    if (root * root == n) {
        cout << n << " 是完全平方數（" << root << "²）" << endl;
    } else {
        cout << n << " 不是完全平方數" << endl;
    }
    return 0;
}
```

### 練習 5-6 答案

📄 **範例檔案：** [hw5_6_ans.cpp](homework/hw5_6_ans.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int count = 0;

    for (int n = 2; n <= 100; n++) {
        bool isPrime = true;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            cout << n;
            count++;
            if (count % 10 == 0) {
                cout << endl;
            } else {
                cout << "\t";
            }
        }
    }

    cout << endl << "共 " << count << " 個質數" << endl;
    return 0;
}
```

### 練習 5-7 答案

📄 **範例檔案：** [hw5_7_ans.cpp](homework/hw5_7_ans.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "請輸入正整數：";
    cin >> n;

    int original = n;
    int digitSum = 0;

    while (n > 0) {
        digitSum += n % 10;
        n /= 10;
    }

    cout << original << " 的各位數字總和：" << digitSum << endl;
    return 0;
}
```

### 練習 5-8 答案

📄 **範例檔案：** [hw5_8_ans.cpp](homework/hw5_8_ans.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "請輸入 n：";
    cin >> n;

    // 上半部（含中間行）
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++) cout << " ";
        for (int j = 1; j <= 2 * i - 1; j++) cout << "*";
        cout << endl;
    }

    // 下半部
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 1; j <= n - i; j++) cout << " ";
        for (int j = 1; j <= 2 * i - 1; j++) cout << "*";
        cout << endl;
    }

    return 0;
}
```

### 練習 5-9 答案

📄 **範例檔案：** [hw5_9_ans.cpp](homework/hw5_9_ans.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "簡易計算機（輸入 q 退出）" << endl;

    while (true) {
        double a, b;
        char op;

        cout << "請輸入算式（例如 3 + 4）：";

        // 嘗試讀取，如果不是數字則退出
        if (!(cin >> a)) break;

        cin >> op;

        if (op == 'q') break;

        cin >> b;

        if (op == '+') cout << "= " << a + b << endl;
        else if (op == '-') cout << "= " << a - b << endl;
        else if (op == '*') cout << "= " << a * b << endl;
        else if (op == '/') {
            if (b == 0) cout << "錯誤：除以零" << endl;
            else cout << "= " << a / b << endl;
        } else {
            cout << "未知運算符" << endl;
        }
    }

    cout << "再見！" << endl;
    return 0;
}
```

### 練習 5-10 答案

📄 **範例檔案：** [hw5_10_ans.cpp](homework/hw5_10_ans.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "1000 以內的完美數：" << endl;

    for (int n = 2; n <= 1000; n++) {
        int sum = 1;    // 1 必定是因數

        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                sum += i;
                if (i != n / i) {    // 避免重複加平方根
                    sum += n / i;
                }
            }
        }

        if (sum == n) {
            cout << n << " 是完美數（";

            // 列出因數
            bool first = true;
            for (int i = 1; i < n; i++) {
                if (n % i == 0) {
                    if (!first) cout << "+";
                    cout << i;
                    first = false;
                }
            }
            cout << "=" << n << "）" << endl;
        }
    }

    return 0;
}
```

### 練習 5-11 答案

📄 **範例檔案：** [hw5_11_ans.cpp](homework/hw5_11_ans.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "請輸入 n：";
    cin >> n;

    // 遞增部分
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) cout << "*";
        cout << endl;
    }

    // 遞減部分
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 0; j < i; j++) cout << "*";
        cout << endl;
    }

    return 0;
}
```

### 練習 5-12 答案

📄 **範例檔案：** [hw5_12_ans.cpp](homework/hw5_12_ans.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "請輸入 n：";
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // 邊框：第一行、最後行、第一列、最後列
            if (i == 0 || i == n - 1 || j == 0 || j == n - 1) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
```

---

## 面試考題

### 基礎概念題

**Q1：while 和 do-while 的差別是什麼？**

> `while` 是先判斷條件再執行，若一開始條件為假，迴圈主體執行 0 次。
> `do-while` 是先執行再判斷，迴圈主體**至少執行一次**。
> 使用時機：需要輸入驗證或顯示選單時用 `do-while`，其他情況用 `while`。

**Q2：break 和 continue 在巢狀迴圈中的行為？**

> 兩者都只影響**最近一層（最內層）**的迴圈。
> 若要跳出外層迴圈，常見方式是使用 `bool` 旗標，或使用 `goto`（不推薦）。

**Q3：以下程式碼的輸出為何？**

```cpp
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        if (i == j) continue;
        cout << i << j << " ";
    }
}
```

> 輸出：`01 02 10 12 20 21`（跳過 i==j 的情況）

**Q4：如何用迴圈判斷一個數是否為質數？時間複雜度是多少？**

> 從 2 遍歷到 √n，若存在因數則非質數。
> 時間複雜度：O(√n)。
> 原因：若 n = a×b 且 a≤b，則 a≤√n，只需檢查到 √n 即可。

**Q5：FizzBuzz（幾乎每家公司都會考）**

> 印出 1 到 100：3 的倍數印 "Fizz"，5 的倍數印 "Buzz"，15 的倍數印 "FizzBuzz"，其他印數字。
> 注意要**先判斷 15 的倍數**，否則邏輯會有問題。

### 進階題

**Q6：如何不用額外變數，交換兩個整數？**

```cpp
a = a ^ b;
b = a ^ b;
a = a ^ b;
```

> 使用 XOR（互斥或）運算。這是考察位元操作的常見題。

**Q7：以下無窮迴圈有什麼問題？如何修正？**

```cpp
int i = 0;
while (i != 10) {
    i += 3;
}
```

> `i` 依序變成 0, 3, 6, 9, 12, ...，**永遠不會等於 10**，造成無窮迴圈。
> 修正：將條件改為 `i < 10` 或 `i <= 10`。

---

## 專案：簡易文字型撲克牌遊戲（骰子版）

📄 **專案檔案：** [project_dice_game/](project_dice_game/)

### 專案說明

實作一個雙人骰子遊戲：
- 玩家輪流擲骰子（模擬隨機數）
- 每輪可選擇「擲」或「停」
- 累積點數最接近 21 但不超過 21 的玩家獲勝
- 超過 21 點即爆牌（bust）

### 功能需求

1. 支援 2 位玩家輪流
2. 使用迴圈控制遊戲流程
3. 使用亂數模擬骰子
4. 顯示每次擲骰結果與累積分數
5. 判斷勝負

📄 **專案答案：** [project_dice_game/dice_game.cpp](project_dice_game/dice_game.cpp)

```cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int rollDice() {
    return rand() % 6 + 1;    // 1 到 6
}

int playerTurn(string playerName) {
    int total = 0;
    char choice;

    cout << "\n=== " << playerName << " 的回合 ===" << endl;

    while (total < 21) {
        cout << "目前分數：" << total << "  擲骰子？(y/n)：";
        cin >> choice;

        if (choice == 'n' || choice == 'N') {
            cout << playerName << " 選擇停止，最終分數：" << total << endl;
            break;
        }

        int dice = rollDice();
        total += dice;
        cout << "擲出：" << dice << "，累積：" << total << endl;

        if (total > 21) {
            cout << "爆牌！" << playerName << " 超過 21 點！" << endl;
            break;
        }

        if (total == 21) {
            cout << "完美！剛好 21 點！" << endl;
            break;
        }
    }

    return total;
}

int main() {
    srand(time(0));    // 初始化亂數種子

    cout << "==============================" << endl;
    cout << "   歡迎來到骰子 21 點遊戲！   " << endl;
    cout << "==============================" << endl;
    cout << "規則：累積點數最接近 21（不超過）的玩家獲勝" << endl;

    int score1 = playerTurn("玩家 1");
    int score2 = playerTurn("玩家 2");

    cout << "\n=== 遊戲結果 ===" << endl;
    cout << "玩家 1：" << score1 << " 分" << endl;
    cout << "玩家 2：" << score2 << " 分" << endl;

    if (score1 > 21 && score2 > 21) {
        cout << "兩位玩家都爆牌，平局！" << endl;
    } else if (score1 > 21) {
        cout << "玩家 2 獲勝！" << endl;
    } else if (score2 > 21) {
        cout << "玩家 1 獲勝！" << endl;
    } else if (score1 > score2) {
        cout << "玩家 1 獲勝！" << endl;
    } else if (score2 > score1) {
        cout << "玩家 2 獲勝！" << endl;
    } else {
        cout << "平局！" << endl;
    }

    return 0;
}
```

---

*本章完*

> **下一章預告：** 第六章將介紹**陣列（Array）**，學習如何用迴圈處理大量資料。
