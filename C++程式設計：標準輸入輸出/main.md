# 第六章：標準輸入輸出

> **學習目標**
> - 掌握 `cin` 讀取各種資料型別（整數、浮點數、字元、字串）
> - 理解 `getline`、`cin.get`、`cin.ignore` 的使用時機與差異
> - 熟練使用 `cout` 輸出各種格式的訊息
> - 了解 `cerr`、`clog` 的用途與差異
> - 使用 `<iomanip>` 函式庫的格式操控子，對齊欄位、控制小數位數、切換進位制

---

## 6.0 輸入輸出的概念

程式與使用者（或外部系統）的互動，主要透過**輸入（Input）** 和 **輸出（Output）** 完成，合稱 **I/O（Input/Output）**。

```
  使用者          程式           使用者
（鍵盤）  ─────►  輸入  ─────►  處理  ─────►  輸出  ─────►  （螢幕）
                 cin                          cout
```

C++ 的標準 I/O 是透過**串流（Stream）**實現的：
- **`cin`（character input）**：從標準輸入（鍵盤）讀取資料
- **`cout`（character output）**：向標準輸出（螢幕）寫入資料
- **`cerr`（character error）**：向標準錯誤輸出寫入（不緩衝）
- **`clog`（character log）**：向標準錯誤輸出寫入（有緩衝）

這四個物件都定義在標頭檔 `<iostream>` 中，使用前須加上：

```cpp
#include <iostream>
using namespace std;
```

---

## 6.1 輸入資料

### 6.1.1 `cin` 基本語法

```
cin >> 變數;
```

`>>` 稱為**萃取運算子（extraction operator）**，將串流中的資料讀入變數。

執行流程：
```
  程式暫停
      │
      ▼
  等待使用者按下 Enter
      │
      ▼
  跳過前置空白/換行
      │
      ▼
  讀取資料，放入變數
      │
      ▼
  程式繼續執行
```

📄 **範例檔案：** [ex6_1_1_cin_basic.cpp](examples/ex6_1_1_cin_basic.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int age;
    cout << "請輸入你的年齡：";
    cin >> age;
    cout << "你輸入的年齡是：" << age << endl;
    return 0;
}
```

**執行範例：**
```
請輸入你的年齡：20
你輸入的年齡是：20
```

---

### 6.1.2 讀取各種資料型別

`cin` 可以自動根據變數型別轉換輸入的資料。

📄 **範例檔案：** [ex6_1_2_cin_types.cpp](examples/ex6_1_2_cin_types.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int    n;
    double d;
    char   c;
    bool   b;

    cout << "輸入整數：";
    cin >> n;
    cout << "你輸入了整數：" << n << endl;

    cout << "輸入浮點數：";
    cin >> d;
    cout << "你輸入了浮點數：" << d << endl;

    cout << "輸入單一字元：";
    cin >> c;   // 會跳過空白，只讀一個字元
    cout << "你輸入了字元：" << c << endl;

    cout << "輸入布林（0 或 1）：";
    cin >> b;
    cout << "你輸入了布林：" << b << endl;

    return 0;
}
```

**執行範例：**
```
輸入整數：42
你輸入了整數：42
輸入浮點數：3.14
你輸入了浮點數：3.14
輸入單一字元：A
你輸入了字元：A
輸入布林（0 或 1）：1
你輸入了布林：1
```

**各型別讀取行為整理：**

| 型別 | 讀取規則 |
|------|---------|
| `int`、`long`、`short` | 讀取整數，遇到非數字字元停止 |
| `float`、`double` | 讀取浮點數，可含小數點 |
| `char` | 跳過前置空白，讀取**一個**字元 |
| `string` | 跳過前置空白，讀到空白/換行為止 |
| `bool` | 讀取 `0`（false）或 `1`（true） |

> ⚠️ **注意：** `cin >> 字串變數` 遇到**空格**就會停止，無法讀取含空格的字串。要讀整行請使用 `getline`（見 6.1.4）。

---

### 6.1.3 讀取字串（`string`）

```cpp
string s;
cin >> s;   // 只讀到第一個空白為止
```

📄 **範例檔案：** [ex6_1_3_cin_string.cpp](examples/ex6_1_3_cin_string.cpp)

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string firstName, lastName;

    cout << "請輸入姓氏：";
    cin >> lastName;

    cout << "請輸入名字：";
    cin >> firstName;

    cout << "你好，" << lastName << firstName << "！" << endl;

    return 0;
}
```

**執行範例：**
```
請輸入姓氏：陳
請輸入名字：大明
你好，陳大明！
```

> ⚠️ **問題示範：** 如果試圖用 `cin >> s` 讀取「陳大明」（含空格的全名），只會讀到「陳大明」中的第一個詞。這時應使用 `getline`。

---

### 6.1.4 `getline`：讀取整行字串

```
getline(cin, 字串變數);
```

`getline` 讀取一整行輸入，直到遇到換行符 `\n` 為止（換行符被消耗但**不儲存**）。

📄 **範例檔案：** [ex6_1_4_getline.cpp](examples/ex6_1_4_getline.cpp)

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string fullName;
    string address;

    cout << "請輸入全名（可含空格）：";
    getline(cin, fullName);

    cout << "請輸入地址：";
    getline(cin, address);

    cout << "\n=== 資料確認 ===" << endl;
    cout << "姓名：" << fullName << endl;
    cout << "地址：" << address << endl;

    return 0;
}
```

**執行範例：**
```
請輸入全名（可含空格）：Chen Wei Cheng
請輸入地址：台北市大安區某路123號
 
=== 資料確認 ===
姓名：Chen Wei Cheng
地址：台北市大安區某路123號
```

---

### 6.1.5 `cin` 與 `getline` 混用問題

這是初學者**最常遇到的坑**！

**問題重現：**

```cpp
int age;
string name;

cin >> age;        // 讀取整數後，緩衝區殘留 '\n'
getline(cin, name); // 直接讀到那個 '\n'，name 變成空字串！
```

**原因：**
```
鍵盤輸入：  2 0 \n
                │
cin >> age   讀走 "20"，但 '\n' 還留在緩衝區
                │
getline      看到 '\n' 就認為「這行結束了」，讀到空字串
```

**解決方法：在 `getline` 之前加上 `cin.ignore()`**

```cpp
cin >> age;
cin.ignore();          // 丟棄緩衝區中的 '\n'
getline(cin, name);    // 這次才能正確讀取
```

📄 **範例檔案：** [ex6_1_5_cin_ignore.cpp](examples/ex6_1_5_cin_ignore.cpp)

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    int age;
    string name;

    cout << "請輸入年齡：";
    cin >> age;

    cin.ignore();   // 清除緩衝區中的換行符

    cout << "請輸入全名：";
    getline(cin, name);

    cout << "年齡：" << age << "，姓名：" << name << endl;

    return 0;
}
```

**執行範例：**
```
請輸入年齡：20
請輸入全名：Chen Wei Cheng
年齡：20，姓名：Chen Wei Cheng
```

> 💡 **進階用法：** `cin.ignore(1000, '\n')` 可以丟棄最多 1000 個字元直到換行，更保險。

---

### 6.1.6 `cin.get()`：讀取單一字元（含空白）

`cin >> c` 會跳過空白；如果想讀取**包含空白在內**的任意字元，使用 `cin.get()`。

```cpp
char c;
cin.get(c);    // 讀取下一個字元，包含空白和換行
```

📄 **範例檔案：** [ex6_1_6_cin_get.cpp](examples/ex6_1_6_cin_get.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    char c1, c2, c3;

    cout << "請輸入三個字元（可含空格）：";
    cin.get(c1);
    cin.get(c2);
    cin.get(c3);

    cout << "字元一：[" << c1 << "]" << endl;
    cout << "字元二：[" << c2 << "]" << endl;
    cout << "字元三：[" << c3 << "]" << endl;

    return 0;
}
```

**執行範例（輸入 `A B`）：**
```
請輸入三個字元（可含空格）：A B
字元一：[A]
字元二：[ ]
字元三：[B]
```

---

### 6.1.7 `cin` 的錯誤狀態

當使用者輸入不符合預期的資料（例如整數欄位輸入了字母），`cin` 會進入**失敗狀態（fail state）**，後續的所有讀取都會失敗。

📄 **範例檔案：** [ex6_1_7_cin_fail.cpp](examples/ex6_1_7_cin_fail.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int num;

    cout << "請輸入整數：";
    cin >> num;

    if (cin.fail()) {
        cout << "輸入錯誤！請輸入整數。" << endl;
        cin.clear();               // 清除錯誤旗標
        cin.ignore(1000, '\n');    // 丟棄錯誤輸入
    } else {
        cout << "你輸入了：" << num << endl;
    }

    return 0;
}
```

**執行範例（輸入字母）：**
```
請輸入整數：abc
輸入錯誤！請輸入整數。
```

**cin 狀態旗標：**

| 方法 | 說明 |
|------|------|
| `cin.good()` | 所有狀態正常，回傳 `true` |
| `cin.fail()` | 讀取失敗（型別不符），回傳 `true` |
| `cin.eof()` | 到達檔案結尾，回傳 `true` |
| `cin.bad()` | 嚴重錯誤（串流損壞），回傳 `true` |
| `cin.clear()` | 清除錯誤旗標，恢復正常狀態 |
| `cin.ignore(n, delim)` | 忽略最多 n 個字元，直到遇到 delim |

---

## 6.2 輸出訊息

### 6.2.1 `cout` 基本語法

```
cout << 運算式;
```

`<<` 稱為**插入運算子（insertion operator）**，將資料送入輸出串流。

📄 **範例檔案：** [ex6_2_1_cout_basic.cpp](examples/ex6_2_1_cout_basic.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    // 輸出各種型別
    cout << 42 << endl;
    cout << 3.14 << endl;
    cout << 'A' << endl;
    cout << true << endl;          // 輸出 1
    cout << "Hello, World!" << endl;

    // 可以連鎖輸出
    int x = 10, y = 20;
    cout << "x = " << x << ", y = " << y << endl;

    // 輸出計算結果
    cout << "x + y = " << x + y << endl;

    return 0;
}
```

**輸出：**
```
42
3.14
A
1
Hello, World!
x = 10, y = 20
x + y = 30
```

---

### 6.2.2 `endl` vs `"\n"`

換行有兩種寫法，它們有細微但重要的差異：

| | `endl` | `"\n"` |
|--|--------|--------|
| 換行 | ✅ | ✅ |
| 清空緩衝區（flush） | ✅ | ❌ |
| 速度 | 較慢 | 較快 |

📄 **範例檔案：** [ex6_2_2_endl_newline.cpp](examples/ex6_2_2_endl_newline.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    // endl：換行 + 強制寫出緩衝區（較慢，適合錯誤訊息）
    cout << "第一行" << endl;
    cout << "第二行" << endl;

    // "\n"：只換行，不清緩衝區（較快，適合大量輸出）
    cout << "第三行\n";
    cout << "第四行\n";

    // 多行一起輸出
    cout << "A\nB\nC\n";

    return 0;
}
```

**輸出：**
```
第一行
第二行
第三行
第四行
A
B
C
```

> 💡 **效能建議：** 在競賽程式或大量輸出的情境，優先使用 `"\n"` 而非 `endl`，因為 `endl` 會強制清空緩衝區，速度慢很多。但一般教學程式兩者差異不大。

---

### 6.2.3 跳脫字元（Escape Sequences）

在字串中，反斜線 `\` 後接特定字母，代表特殊字元：

| 跳脫字元 | 意義 | 說明 |
|---------|------|------|
| `\n` | 換行（newline） | 游標移到下一行開頭 |
| `\t` | 水平定位（tab） | 跳到下一個 tab 位置（通常 8 格） |
| `\\` | 反斜線 | 輸出一個 `\` |
| `\"` | 雙引號 | 輸出一個 `"` |
| `\'` | 單引號 | 輸出一個 `'` |
| `\0` | 空字元 | 字串結束標記 |
| `\a` | 嗶聲（bell） | 發出提示音 |
| `\r` | 歸位（carriage return） | 游標移到當前行開頭 |

📄 **範例檔案：** [ex6_2_3_escape.cpp](examples/ex6_2_3_escape.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "姓名\t年齡\t城市" << endl;
    cout << "陳大明\t20\t台北" << endl;
    cout << "李小華\t22\t台中" << endl;

    cout << "\n他說：\"你好！\"" << endl;
    cout << "路徑：C:\\Users\\student\\Desktop" << endl;

    return 0;
}
```

**輸出：**
```
姓名	年齡	城市
陳大明	20	台北
李小華	22	台中

他說："你好！"
路徑：C:\Users\student\Desktop
```

---

### 6.2.4 `cerr` 與 `clog`：錯誤輸出

`cerr` 和 `clog` 專門用於輸出**錯誤訊息或日誌**，輸出目標是標準錯誤輸出（`stderr`），與 `cout` 的標準輸出（`stdout`）**分開**。

```
cout  → stdout（標準輸出）  → 通常是螢幕
cerr  → stderr（標準錯誤）  → 通常也是螢幕，但可獨立重新導向
clog  → stderr（標準錯誤）  → 有緩衝，效率較 cerr 高
```

| | `cerr` | `clog` |
|--|--------|--------|
| 緩衝 | ❌（立即輸出） | ✅（有緩衝） |
| 適合 | 嚴重錯誤、即時警告 | 一般日誌、大量訊息 |

📄 **範例檔案：** [ex6_2_4_cerr_clog.cpp](examples/ex6_2_4_cerr_clog.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int divisor;
    cout << "請輸入除數：";
    cin >> divisor;

    if (divisor == 0) {
        cerr << "[錯誤] 除數不能為零！" << endl;   // 錯誤訊息用 cerr
        return 1;   // 非零回傳值表示程式異常結束
    }

    clog << "[日誌] 正在計算 100 / " << divisor << endl;   // 日誌用 clog
    cout << "結果：" << 100.0 / divisor << endl;

    return 0;
}
```

**執行範例（正常情況）：**
```
請輸入除數：4
[日誌] 正在計算 100 / 4
結果：25
```

**執行範例（輸入 0）：**
```
請輸入除數：0
[錯誤] 除數不能為零！
```

> 💡 **為什麼要分開？** 在實務中，可以將 `stdout` 導向檔案，但讓 `stderr` 仍顯示在終端機，這樣就能在儲存輸出的同時看到即時錯誤訊息。

---

## 6.3 多變數輸出入

### 6.3.1 一次讀取多個變數

`cin` 支援用空白（空格或換行）分隔，一次讀取多個變數：

```cpp
cin >> 變數1 >> 變數2 >> 變數3;
```

使用者可以：
- 在同一行用空格分隔輸入
- 分多行輸入（按 Enter）

📄 **範例檔案：** [ex6_3_1_multi_input.cpp](examples/ex6_3_1_multi_input.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b, c;

    cout << "請輸入三個整數（以空格分隔）：";
    cin >> a >> b >> c;

    cout << "你輸入的三個數是：" << a << "、" << b << "、" << c << endl;
    cout << "總和：" << a + b + c << endl;
    cout << "平均：" << (a + b + c) / 3.0 << endl;

    return 0;
}
```

**執行範例（同一行輸入）：**
```
請輸入三個整數（以空格分隔）：10 20 30
你輸入的三個數是：10、20、30
總和：60
平均：20
```

**執行範例（分行輸入）：**
```
請輸入三個整數（以空格分隔）：10
20
30
你輸入的三個數是：10、20、30
總和：60
平均：20
```

---

### 6.3.2 一次輸出多個值

`cout` 同樣支援連鎖：

```cpp
cout << 值1 << " " << 值2 << " " << 值3 << endl;
```

📄 **範例檔案：** [ex6_3_2_multi_output.cpp](examples/ex6_3_2_multi_output.cpp)

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string name = "陳大明";
    int age = 20;
    double gpa = 3.75;
    char grade = 'A';

    // 各種型別混合輸出
    cout << "姓名：" << name << endl;
    cout << "年齡：" << age << " 歲" << endl;
    cout << "GPA：" << gpa << endl;
    cout << "等第：" << grade << endl;

    // 計算並輸出
    int x = 15, y = 4;
    cout << x << " / " << y << " = " << x / y
         << " 餘 " << x % y << endl;

    return 0;
}
```

**輸出：**
```
姓名：陳大明
年齡：20 歲
GPA：3.75
等第：A
15 / 4 = 3 餘 3
```

---

### 6.3.3 綜合輸出入範例：個人資料表

📄 **範例檔案：** [ex6_3_3_personal_info.cpp](examples/ex6_3_3_personal_info.cpp)

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string name, department, hometown;
    int age, studentId;
    double gpa;

    cout << "===== 學生資料輸入 =====" << endl;

    cout << "學號：";
    cin >> studentId;

    cout << "年齡：";
    cin >> age;

    cin.ignore();   // 清除換行符

    cout << "姓名：";
    getline(cin, name);

    cout << "科系：";
    getline(cin, department);

    cout << "家鄉：";
    getline(cin, hometown);

    cout << "GPA：";
    cin >> gpa;

    cout << "\n===== 學生資料輸出 =====" << endl;
    cout << "學號：" << studentId << endl;
    cout << "姓名：" << name << endl;
    cout << "年齡：" << age << " 歲" << endl;
    cout << "科系：" << department << endl;
    cout << "家鄉：" << hometown << endl;
    cout << "GPA：" << gpa << endl;

    return 0;
}
```

**執行範例：**
```
===== 學生資料輸入 =====
學號：20240001
年齡：20
姓名：陳大明
科系：資訊工程學系
家鄉：台北市
GPA：3.8

===== 學生資料輸出 =====
學號：20240001
姓名：陳大明
年齡：20 歲
科系：資訊工程學系
家鄉：台北市
GPA：3.8
```

---

## 6.4 格式輸出入操控子

在實際應用中，常常需要精確控制輸出的格式：對齊欄位、固定小數位數、以不同進位制顯示數字等。C++ 提供了 `<iomanip>` 函式庫來完成這些工作。

```cpp
#include <iomanip>
```

格式操控子分為兩類：

| 類型 | 說明 |
|------|------|
| **黏著型（sticky）** | 設定後持續生效，直到再次改變 |
| **一次型（non-sticky）** | 只影響下一個輸出 |

---

### 6.4.1 `setw()`：設定欄位寬度

```cpp
cout << setw(n) << 值;  // 佔 n 個字元寬，預設靠右對齊
```

> ⚠️ `setw()` 是**一次型**操控子，只影響緊接在後的**一個**輸出項目，之後自動恢復預設。

📄 **範例檔案：** [ex6_4_1_setw.cpp](examples/ex6_4_1_setw.cpp)

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // 不設定欄寬
    cout << 1 << endl;
    cout << 22 << endl;
    cout << 333 << endl;

    cout << "---" << endl;

    // 設定欄寬為 6（靠右對齊）
    cout << setw(6) << 1   << endl;
    cout << setw(6) << 22  << endl;
    cout << setw(6) << 333 << endl;

    return 0;
}
```

**輸出：**
```
1
22
333
---
     1
    22
   333
```

**欄位寬度示意（setw(6)）：**
```
[     1]   ← 5個空白 + '1'，共6格
[    22]   ← 4個空白 + "22"，共6格
[   333]   ← 3個空白 + "333"，共6格
```

---

### 6.4.2 `setfill()`：設定填充字元

`setw()` 預設用空白填充，`setfill()` 可以換成其他字元。

> 💡 `setfill()` 是**黏著型**操控子，設定後持續生效。

📄 **範例檔案：** [ex6_4_2_setfill.cpp](examples/ex6_4_2_setfill.cpp)

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // 用 * 填充
    cout << setfill('*');
    cout << setw(10) << 123   << endl;
    cout << setw(10) << "Hi"  << endl;
    cout << setw(10) << 3.14  << endl;

    cout << "---" << endl;

    // 用 0 填充（常見於編號、時間格式）
    cout << setfill('0');
    cout << setw(4) << 7  << endl;   // 0007
    cout << setw(4) << 42 << endl;   // 0042

    // 模擬時間格式
    int h = 9, m = 5, s = 3;
    cout << setw(2) << h << ":"
         << setw(2) << m << ":"
         << setw(2) << s << endl;   // 09:05:03

    return 0;
}
```

**輸出：**
```
*******123
********Hi
******3.14
---
0007
0042
09:05:03
```

---

### 6.4.3 `left`、`right`、`internal`：對齊方向

預設是靠右對齊。可以用操控子切換：

| 操控子 | 說明 |
|--------|------|
| `right` | 靠右對齊（預設） |
| `left` | 靠左對齊 |
| `internal` | 符號靠左，數字靠右（填充在中間） |

> 💡 這三個是**黏著型**操控子。

📄 **範例檔案：** [ex6_4_3_align.cpp](examples/ex6_4_3_align.cpp)

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    cout << "靠右（預設）：" << endl;
    cout << right << setfill(' ');
    cout << setw(10) << "姓名"   << setw(6) << "年齡" << setw(8) << "GPA"  << endl;
    cout << setw(10) << "陳大明" << setw(6) << 20     << setw(8) << 3.8    << endl;
    cout << setw(10) << "李小華" << setw(6) << 22     << setw(8) << 3.5    << endl;

    cout << "\n靠左：" << endl;
    cout << left;
    cout << setw(10) << "姓名"   << setw(6) << "年齡" << setw(8) << "GPA"  << endl;
    cout << setw(10) << "陳大明" << setw(6) << 20     << setw(8) << 3.8    << endl;
    cout << setw(10) << "李小華" << setw(6) << 22     << setw(8) << 3.5    << endl;

    cout << "\ninternal 範例：" << endl;
    cout << internal << setfill('0') << right;
    cout << setw(8) << -42   << endl;   // -0000042
    cout << setw(8) << +42   << endl;   // 00000042（showpos 才會顯示+）

    return 0;
}
```

**輸出：**
```
靠右（預設）：
        姓名  年齡     GPA
      陳大明    20     3.8
      李小華    22     3.5

靠左：
姓名        年齡  GPA     
陳大明      20    3.8     
李小華      22    3.5     

internal 範例：
-0000042
00000042
```

---

### 6.4.4 `setprecision()`、`fixed`、`scientific`：浮點數精度

**預設行為（不加任何操控子）：** 最多顯示 6 位有效數字。

| 操控子 | 說明 |
|--------|------|
| `setprecision(n)` | 設定精度（有效數字或小數位數，視模式而定） |
| `fixed` | 固定小數點格式（小數位數固定） |
| `scientific` | 科學記號格式 |
| `defaultfloat` | 恢復預設格式（C++11） |

> 💡 `setprecision()`、`fixed`、`scientific` 都是**黏著型**操控子。

📄 **範例檔案：** [ex6_4_4_precision.cpp](examples/ex6_4_4_precision.cpp)

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double pi    = 3.14159265358979;
    double big   = 123456789.0;
    double small_ = 0.000012345;

    cout << "=== 預設格式（6位有效數字）===" << endl;
    cout << pi    << endl;   // 3.14159
    cout << big   << endl;   // 1.23457e+08
    cout << small_ << endl;   // 1.2345e-05

    cout << "\n=== fixed 固定小數點 ===" << endl;
    cout << fixed;
    cout << setprecision(2) << pi     << endl;   // 3.14
    cout << setprecision(4) << pi     << endl;   // 3.1416
    cout << setprecision(2) << big    << endl;   // 123456789.00
    cout << setprecision(6) << small_ << endl;   // 0.000012

    cout << "\n=== scientific 科學記號 ===" << endl;
    cout << scientific;
    cout << setprecision(3) << pi     << endl;   // 3.142e+00
    cout << setprecision(3) << big    << endl;   // 1.235e+08
    cout << setprecision(3) << small_ << endl;   // 1.235e-05

    cout << "\n=== defaultfloat 恢復預設 ===" << endl;
    cout << defaultfloat;
    cout << setprecision(6) << pi << endl;       // 3.14159

    return 0;
}
```

**輸出：**
```
=== 預設格式（6位有效數字）===
3.14159
1.23457e+08
1.2345e-05

=== fixed 固定小數點 ===
3.14
3.1416
123456789.00
0.000012

=== scientific 科學記號 ===
3.142e+00
1.235e+08
1.235e-05

=== defaultfloat 恢復預設 ===
3.14159
```

---

### 6.4.5 進位制：`hex`、`oct`、`dec`

| 操控子 | 說明 |
|--------|------|
| `dec` | 十進位（預設） |
| `oct` | 八進位 |
| `hex` | 十六進位 |
| `showbase` | 顯示進位前綴（`0x`、`0`） |
| `noshowbase` | 不顯示前綴（預設） |
| `uppercase` | 十六進位字母大寫（`A`~`F`） |
| `nouppercase` | 十六進位字母小寫（預設，`a`~`f`） |

> 💡 這些都是**黏著型**操控子。注意：進位制操控子只對**整數**有效，不影響浮點數。

📄 **範例檔案：** [ex6_4_5_bases.cpp](examples/ex6_4_5_bases.cpp)

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int num = 255;

    cout << "數值：" << num << endl;
    cout << "十進位：" << dec << num << endl;
    cout << "八進位：" << oct << num << endl;
    cout << "十六進位（小寫）：" << hex << num << endl;
    cout << "十六進位（大寫）：" << uppercase << hex << num << endl;

    cout << "\n加上前綴（showbase）：" << endl;
    cout << showbase << nouppercase;
    cout << "十進位：" << dec << num << endl;   // 255
    cout << "八進位：" << oct << num << endl;   // 0377
    cout << "十六進位：" << hex << num << endl; // 0xff

    cout << "\n回到十進位：" << noshowbase << dec << endl;
    cout << num << endl;

    // 實用：顏色代碼（RGB）
    int r = 255, g = 128, b = 0;
    cout << "\nRGB 顏色代碼：#"
         << uppercase << hex
         << setw(2) << setfill('0') << r
         << setw(2) << setfill('0') << g
         << setw(2) << setfill('0') << b
         << endl;   // #FF8000

    return 0;
}
```

**輸出：**
```
數值：255
十進位：255
八進位：377
十六進位（小寫）：ff
十六進位（大寫）：FF

加上前綴（showbase）：
十進位：255
八進位：0377
十六進位：0xff

回到十進位：
255

RGB 顏色代碼：#FF8000
```

---

### 6.4.6 `boolalpha`：布林值顯示

預設布林值顯示為 `1`（true）和 `0`（false），用 `boolalpha` 可以改為 `true`/`false`。

📄 **範例檔案：** [ex6_4_6_boolalpha.cpp](examples/ex6_4_6_boolalpha.cpp)

```cpp
#include <iostream>
using namespace std;

int main() {
    bool a = true, b = false;

    cout << "預設：" << a << " " << b << endl;           // 1 0

    cout << boolalpha;
    cout << "boolalpha：" << a << " " << b << endl;      // true false

    cout << noboolalpha;
    cout << "noboolalpha：" << a << " " << b << endl;    // 1 0

    // 配合 cin 讀取 true/false 字串
    bool result;
    cout << boolalpha;
    cout << "請輸入 true 或 false：";
    cin >> result;
    cout << "你輸入了：" << result << endl;

    return 0;
}
```

**輸出（輸入 true）：**
```
預設：1 0
boolalpha：true false
noboolalpha：1 0
請輸入 true 或 false：true
你輸入了：true
```

---

### 6.4.7 `showpos`：顯示正號

`showpos` 讓正數也顯示 `+` 號。

📄 **範例檔案：** [ex6_4_7_showpos.cpp](examples/ex6_4_7_showpos.cpp)

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int values[] = {-10, 0, 5, 100};

    cout << "不顯示正號：" << endl;
    for (int v : values) {
        cout << setw(6) << v << endl;
    }

    cout << "\n顯示正號（showpos）：" << endl;
    cout << showpos;
    for (int v : values) {
        cout << setw(6) << v << endl;
    }

    cout << noshowpos;  // 取消

    return 0;
}
```

**輸出：**
```
不顯示正號：
   -10
     0
     5
   100

顯示正號（showpos）：
   -10
    +0
    +5
  +100
```

---

### 6.4.8 綜合應用：格式化表格

這是最重要的應用情境：輸出整齊的表格。

📄 **範例檔案：** [ex6_4_8_table.cpp](examples/ex6_4_8_table.cpp)

```cpp
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    // 商品清單
    string items[]   = {"筆記型電腦", "滑鼠", "鍵盤", "螢幕"};
    int    quantity[] = {1, 2, 1, 2};
    double price[]    = {32000.0, 299.0, 1500.0, 5999.0};
    int n = 4;

    // 表頭
    cout << string(45, '=') << endl;
    cout << left
         << setw(12) << "商品名稱"
         << right
         << setw(6)  << "數量"
         << setw(10) << "單價"
         << setw(12) << "小計"
         << endl;
    cout << string(45, '-') << endl;

    double total = 0.0;

    // 資料列
    for (int i = 0; i < n; i++) {
        double subtotal = quantity[i] * price[i];
        total += subtotal;

        cout << left  << setw(12) << items[i]
             << right << fixed << setprecision(0)
             << setw(6)  << quantity[i]
             << setw(10) << price[i]
             << setw(12) << subtotal
             << endl;
    }

    // 總計
    cout << string(45, '-') << endl;
    cout << left  << setw(18) << "合計"
         << right << setw(12) << total
         << endl;

    double tax    = total * 0.05;
    double grand  = total + tax;
    cout << left  << setw(18) << "稅額（5%）"
         << right << setw(12) << tax << endl;
    cout << string(45, '-') << endl;
    cout << left  << setw(18) << "總計（含稅）"
         << right << setw(12) << grand << endl;
    cout << string(45, '=') << endl;

    return 0;
}
```

**輸出：**
```
=============================================
商品名稱          數量        單價          小計
---------------------------------------------
筆記型電腦           1     32000       32000
滑鼠                 2       299         598
鍵盤                 1      1500        1500
螢幕                 2      5999       11998
---------------------------------------------
合計                                   46096
稅額（5%）                              2305
---------------------------------------------
總計（含稅）                            48401
=============================================
```

---

### 6.4.9 操控子快速參考表

| 操控子 | 標頭 | 黏著型 | 說明 |
|--------|------|--------|------|
| `setw(n)` | `<iomanip>` | ❌ | 下一個輸出佔 n 字元寬 |
| `setfill(c)` | `<iomanip>` | ✅ | 設定填充字元為 c |
| `setprecision(n)` | `<iomanip>` | ✅ | 設定精度 |
| `left` | `<ios>` | ✅ | 靠左對齊 |
| `right` | `<ios>` | ✅ | 靠右對齊（預設） |
| `internal` | `<ios>` | ✅ | 符號靠左，數字靠右 |
| `fixed` | `<ios>` | ✅ | 固定小數點格式 |
| `scientific` | `<ios>` | ✅ | 科學記號格式 |
| `defaultfloat` | `<ios>` | ✅ | 恢復預設浮點格式 |
| `dec` | `<ios>` | ✅ | 十進位（預設） |
| `oct` | `<ios>` | ✅ | 八進位 |
| `hex` | `<ios>` | ✅ | 十六進位 |
| `showbase` | `<ios>` | ✅ | 顯示進位前綴 |
| `noshowbase` | `<ios>` | ✅ | 不顯示前綴（預設） |
| `uppercase` | `<ios>` | ✅ | 十六進位大寫 |
| `nouppercase` | `<ios>` | ✅ | 十六進位小寫（預設） |
| `boolalpha` | `<ios>` | ✅ | 布林值顯示 true/false |
| `noboolalpha` | `<ios>` | ✅ | 布林值顯示 1/0（預設） |
| `showpos` | `<ios>` | ✅ | 正數顯示 + |
| `noshowpos` | `<ios>` | ✅ | 不顯示 +（預設） |

> 💡 `<ios>` 中的操控子通常被 `<iostream>` 間接 include，寫程式時只要記得有用到 `setw`、`setfill`、`setprecision` 就須加 `#include <iomanip>`。

---

## 章節總結

```
標準輸入輸出
│
├─ 6.1 輸入資料
│   ├─ cin >> 變數           （讀整數、浮點數、字元、字串）
│   ├─ cin >> s1 >> s2       （讀到空白停止）
│   ├─ getline(cin, s)       （讀整行，含空格）
│   ├─ cin.get(c)            （讀單一字元，含空白）
│   ├─ cin.ignore()          （混用 cin >> 和 getline 的必要步驟）
│   └─ cin.fail()/clear()    （錯誤處理）
│
├─ 6.2 輸出訊息
│   ├─ cout << 值            （輸出到螢幕）
│   ├─ endl vs "\n"          （endl 會 flush，"\n" 較快）
│   ├─ 跳脫字元 \n \t \\ \" （特殊字元輸出）
│   ├─ cerr                  （無緩衝錯誤輸出）
│   └─ clog                  （有緩衝日誌輸出）
│
├─ 6.3 多變數輸出入
│   ├─ cin >> a >> b >> c    （一次讀多個）
│   └─ cout << a << b << c   （一次輸出多個）
│
└─ 6.4 格式操控子（需 #include <iomanip>）
    ├─ setw(n)               （欄位寬度，一次型）
    ├─ setfill(c)            （填充字元）
    ├─ left / right          （對齊方向）
    ├─ setprecision(n) + fixed / scientific  （浮點數格式）
    ├─ hex / oct / dec       （進位制）
    └─ boolalpha / showpos   （布林值、正號）
```

---

## 實作練習

> 以下練習題請獨立完成後，再對照參考解答。

---

### 練習 6-1：基本輸出格式

**題目：** 輸入學生的姓名、學號、三科成績（整數），計算平均（保留 2 位小數），輸出如下格式的成績單。

**輸入範例：**
```
姓名：陳大明
學號：20240001
國文：85
數學：92
英文：78
```

**輸出範例：**
```
╔══════════════════════════════╗
║          學生成績單           ║
╠══════════════════════════════╣
║ 姓名：陳大明                 ║
║ 學號：20240001               ║
╠══════════════════════════════╣
║ 國文：  85 分                ║
║ 數學：  92 分                ║
║ 英文：  78 分                ║
╠══════════════════════════════╣
║ 平均：  85.00 分             ║
╚══════════════════════════════╝
```

📄 **練習檔案：** `hw6_1_grade_report.cpp`

---

### 練習 6-2：時鐘格式輸出

**題目：** 輸入時、分、秒（三個整數），以 `HH:MM:SS` 的格式輸出，不足兩位數的要補 `0`。

**輸入範例：**
```
請輸入時：9
請輸入分：5
請輸入秒：3
```

**輸出範例：**
```
09:05:03
```

📄 **練習檔案：** `hw6_2_clock_format.cpp`

---

### 練習 6-3：BMI 計算機

**題目：** 輸入體重（kg，保留 1 位小數）和身高（cm，整數），計算 BMI（保留 2 位小數）並輸出體重等級。

**公式：** BMI = 體重(kg) / 身高(m)²

**BMI 分級：**
| BMI | 等級 |
|-----|------|
| < 18.5 | 過輕 |
| 18.5 ~ 24.9 | 正常 |
| 25.0 ~ 29.9 | 過重 |
| ≥ 30.0 | 肥胖 |

**輸入範例：**
```
請輸入體重（kg）：70.5
請輸入身高（cm）：175
```

**輸出範例：**
```
體重：70.5 kg
身高：175 cm
BMI：23.02
體重等級：正常
```

📄 **練習檔案：** `hw6_3_bmi.cpp`

---

### 練習 6-4：RGB 轉十六進位

**題目：** 輸入三個整數（0~255），分別代表 R、G、B 值，輸出對應的 HTML 顏色代碼（`#RRGGBB` 格式，大寫）。

**輸入範例：**
```
R：255
G：128
B：0
```

**輸出範例：**
```
HTML 顏色代碼：#FF8000
十六進位（帶前綴）：R=0xff, G=0x80, B=0x0
```

📄 **練習檔案：** `hw6_4_rgb_hex.cpp`

---

### 練習 6-5：乘法表格

**題目：** 輸入一個整數 n（1~9），輸出 n 的乘法表，使用 `setw` 對齊欄位。

**輸入範例：**
```
請輸入 n（1~9）：7
```

**輸出範例：**
```
7 的乘法表
──────────────────
7 × 1 =  7
7 × 2 = 14
7 × 3 = 21
7 × 4 = 28
7 × 5 = 35
7 × 6 = 42
7 × 7 = 49
7 × 8 = 56
7 × 9 = 63
```

📄 **練習檔案：** `hw6_5_times_table.cpp`

---

### 練習 6-6：個人資料卡（綜合）

**題目：** 建立一張格式化的個人資料卡，包含姓名（可含空格）、年齡、科系、GPA、電話號碼，以框線格式輸出。

**輸入範例：**
```
姓名：Chen Wei Cheng
年齡：20
科系：資訊工程學系
GPA：3.85
電話：0912-345-678
```

**輸出範例：**
```
┌─────────────────────────────┐
│        個人資料卡            │
├─────────────────────────────┤
│ 姓名：Chen Wei Cheng        │
│ 年齡：20 歲                 │
│ 科系：資訊工程學系           │
│ GPA： 3.85                  │
│ 電話：0912-345-678          │
└─────────────────────────────┘
```

📄 **練習檔案：** `hw6_6_profile_card.cpp`

---

### 練習 6-7：貨幣換算表

**題目：** 輸入新台幣金額（整數），輸出換算後的各國貨幣表格（保留 2 位小數，使用固定欄寬對齊）。

**匯率（固定）：** USD ÷30、JPY ×4.5、EUR ÷33、GBP ÷38

**輸入範例：**
```
請輸入台幣金額：10000
```

**輸出範例：**
```
台幣：10000 元
═══════════════════════════
幣別         換算金額
───────────────────────────
USD         333.33
JPY       45000.00
EUR         303.03
GBP         263.16
═══════════════════════════
```

📄 **練習檔案：** `hw6_7_currency.cpp`

---

### 練習 6-8：輸入驗證器（進階）

**題目：** 持續要求使用者輸入一個 1~100 之間的整數，若輸入非整數或超出範圍，顯示錯誤訊息並重新輸入，直到輸入正確為止。

**執行範例：**
```
請輸入 1 到 100 之間的整數：abc
[錯誤] 請輸入整數！
請輸入 1 到 100 之間的整數：150
[錯誤] 數值超出範圍（1~100）！
請輸入 1 到 100 之間的整數：42
輸入成功：42
```

📄 **練習檔案：** `hw6_8_input_validator.cpp`

---

## 面試考題

### 面試題 1

**題目：** 請解釋 `cin >>` 和 `getline()` 的差異，以及混用時會遇到什麼問題？

**參考答案：**
- `cin >>` 遇到空白（空格、Tab、換行）就停止讀取，適合讀取不含空白的單一資料。
- `getline()` 讀取整行字串，直到換行符為止，適合讀取含空格的輸入。
- **混用問題：** `cin >>` 讀完後緩衝區中殘留 `'\n'`，`getline()` 立即讀到這個 `'\n'` 就停止，結果為空字串。
- **解決方法：** 在 `getline()` 前加 `cin.ignore()`，清除緩衝區中的殘留換行符。

---

### 面試題 2

**題目：** `endl` 和 `"\n"` 有什麼差異？什麼情境下應選擇哪一個？

**參考答案：**
- `endl`：輸出換行符 **且** 強制 flush（清空）輸出緩衝區，確保資料立即顯示。
- `"\n"`：只輸出換行符，不強制 flush，資料可能暫存在緩衝區等待批次輸出。
- **選擇原則：**
  - 需要即時顯示（如錯誤訊息、互動提示）→ 用 `endl`
  - 大量迴圈輸出（如競賽程式）→ 用 `"\n"`，速度可快數倍
  - 一般教學/練習 → 無明顯差異，習慣即可

---

### 面試題 3

**題目：** 下列程式碼有什麼 bug？請修正。

```cpp
int age;
string name;
cin >> age;
getline(cin, name);
cout << name;
```

**參考答案：**
- **Bug：** `cin >> age` 讀取整數後，緩衝區中殘留換行符 `'\n'`。接著 `getline(cin, name)` 立即讀到 `'\n'`，`name` 變成空字串，無法正確讀取姓名。
- **修正：** 在 `cin >> age` 後加上 `cin.ignore();`

```cpp
int age;
string name;
cin >> age;
cin.ignore();          // 清除換行符
getline(cin, name);
cout << name;
```

---

### 面試題 4

**題目：** `setw()` 和 `setfill()` 哪一個是黏著型（sticky）操控子？差異為何？

**參考答案：**
- `setw(n)` 是**非黏著型**：只影響緊接在後的一個輸出，之後自動恢復。
- `setfill(c)` 是**黏著型**：設定後持續生效，直到再次呼叫 `setfill` 或程式結束。
- 這個設計的原因：欄寬通常每個欄位都不同（所以一次型更方便），但填充字元通常整個表格都一樣（所以黏著型更方便）。

---

### 面試題 5

**題目：** `cout`、`cerr`、`clog` 各自的用途是什麼？在實務中如何搭配使用？

**參考答案：**
- `cout`：標準輸出（stdout），輸出正常執行結果，有緩衝。
- `cerr`：標準錯誤（stderr），輸出錯誤訊息，**無緩衝**，立即輸出，即使程式崩潰也不會丟失。
- `clog`：標準錯誤（stderr），輸出日誌訊息，**有緩衝**，效能優於 `cerr`。
- **實務搭配：**
  - 程式正常結果 → `cout`
  - 嚴重錯誤、例外 → `cerr`（確保訊息不丟失）
  - 一般日誌紀錄 → `clog`（效能較好）
  - 在 shell 中可將 stdout 和 stderr 分開：`./program > output.txt 2> error.txt`

---

## 專案：學生成績管理系統（基礎版）

> 本專案讓你綜合運用本章所有 I/O 技巧，完成一個具備格式化輸出的成績管理程式。

### 需求說明

建立一個程式，可以：
1. 輸入 N 位學生的姓名（含空格）和三科成績
2. 計算每位學生的平均分
3. 計算全班各科與平均的最高分、最低分、全班平均
4. 以格式化表格輸出成績單

### 輸入格式

```
請輸入學生人數：3
--- 學生 1 ---
姓名：陳大明
國文：85
數學：92
英文：78
--- 學生 2 ---
姓名：李小華
國文：90
數學：75
英文：88
--- 學生 3 ---
姓名：Wang Ming
國文：72
數學：95
英文：83
```

### 輸出格式

```
╔═══════════════════════════════════════════════════╗
║                  班級成績報告                       ║
╠═══════════════╦══════╦══════╦══════╦══════════════╣
║ 姓名          ║ 國文 ║ 數學 ║ 英文 ║     平均     ║
╠═══════════════╬══════╬══════╬══════╬══════════════╣
║ 陳大明        ║   85 ║   92 ║   78 ║        85.00 ║
║ 李小華        ║   90 ║   75 ║   88 ║        84.33 ║
║ Wang Ming     ║   72 ║   95 ║   83 ║        83.33 ║
╠═══════════════╬══════╬══════╬══════╬══════════════╣
║ 班級平均      ║82.33 ║87.33 ║83.00 ║        84.22 ║
║ 最高分        ║   90 ║   95 ║   88 ║              ║
║ 最低分        ║   72 ║   75 ║   78 ║              ║
╚═══════════════╩══════╩══════╩══════╩══════════════╝
```

📄 **專案檔案：** `project6_grade_system.cpp`

---

### 專案解答

📄 **解答檔案：** [project6_grade_system_answer.cpp](examples/project6_grade_system_answer.cpp)

```cpp
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    const int MAX_STUDENTS = 50;
    const int SUBJECTS = 3;

    string names[MAX_STUDENTS];
    int scores[MAX_STUDENTS][SUBJECTS];
    double avg[MAX_STUDENTS];
    int n;

    cout << "請輸入學生人數：";
    cin >> n;

    // 輸入資料
    for (int i = 0; i < n; i++) {
        cout << "--- 學生 " << (i + 1) << " ---" << endl;

        cout << "姓名：";
        cin.ignore();
        getline(cin, names[i]);

        string subjects[] = {"國文", "數學", "英文"};
        double sum = 0;
        for (int j = 0; j < SUBJECTS; j++) {
            cout << subjects[j] << "：";
            cin >> scores[i][j];
            sum += scores[i][j];
        }
        avg[i] = sum / SUBJECTS;
    }

    // 計算統計
    double classAvg[SUBJECTS] = {};
    int maxScore[SUBJECTS], minScore[SUBJECTS];
    double totalAvg = 0;

    for (int j = 0; j < SUBJECTS; j++) {
        maxScore[j] = scores[0][j];
        minScore[j] = scores[0][j];
        for (int i = 0; i < n; i++) {
            classAvg[j] += scores[i][j];
            if (scores[i][j] > maxScore[j]) maxScore[j] = scores[i][j];
            if (scores[i][j] < minScore[j]) minScore[j] = scores[i][j];
        }
        classAvg[j] /= n;
    }
    for (int i = 0; i < n; i++) totalAvg += avg[i];
    totalAvg /= n;

    // 輸出表格
    cout << "\n";
    string H = "═", V = "║", TL = "╔", TR = "╗", BL = "╚", BR = "╝";
    string MT = "╦", MB = "╩", ML = "╠", MR = "╣", MC = "╬";

    // 表頭
    cout << TL;
    for (int k = 0; k < 51; k++) cout << H;
    cout << TR << endl;

    cout << V << setw(26) << right << "班級成績報告"
         << setw(25) << left << ""  << V << endl;

    cout << ML;
    for (int k = 0; k < 15; k++) cout << H;
    cout << MT;
    for (int k = 0; k < 6; k++) cout << H;
    cout << MT;
    for (int k = 0; k < 6; k++) cout << H;
    cout << MT;
    for (int k = 0; k < 6; k++) cout << H;
    cout << MT;
    for (int k = 0; k < 14; k++) cout << H;
    cout << MR << endl;

    cout << V << left  << setw(15) << " 姓名"
         << V << right << setw(6)  << " 國文"
         << V << right << setw(6)  << " 數學"
         << V << right << setw(6)  << " 英文"
         << V << right << setw(14) << "平均"
         << V << endl;

    cout << ML;
    for (int k = 0; k < 15; k++) cout << H;
    cout << MC;
    for (int k = 0; k < 6; k++) cout << H;
    cout << MC;
    for (int k = 0; k < 6; k++) cout << H;
    cout << MC;
    for (int k = 0; k < 6; k++) cout << H;
    cout << MC;
    for (int k = 0; k < 14; k++) cout << H;
    cout << MR << endl;

    // 學生資料
    cout << fixed << setprecision(2);
    for (int i = 0; i < n; i++) {
        cout << V << " " << left  << setw(14) << names[i]
             << V        << right << setw(5)  << scores[i][0] << " "
             << V        << right << setw(5)  << scores[i][1] << " "
             << V        << right << setw(5)  << scores[i][2] << " "
             << V        << right << setw(13) << avg[i]
             << V << endl;
    }

    // 統計列
    cout << ML;
    for (int k = 0; k < 15; k++) cout << H;
    cout << MC;
    for (int k = 0; k < 6; k++) cout << H;
    cout << MC;
    for (int k = 0; k < 6; k++) cout << H;
    cout << MC;
    for (int k = 0; k < 6; k++) cout << H;
    cout << MC;
    for (int k = 0; k < 14; k++) cout << H;
    cout << MR << endl;

    cout << V << " " << left << setw(14) << "班級平均"
         << V << right << setw(5) << classAvg[0] << " "
         << V << right << setw(5) << classAvg[1] << " "
         << V << right << setw(5) << classAvg[2] << " "
         << V << right << setw(13) << totalAvg
         << V << endl;

    cout << V << " " << left << setw(14) << "最高分"
         << V << right << setw(5) << maxScore[0] << " "
         << V << right << setw(5) << maxScore[1] << " "
         << V << right << setw(5) << maxScore[2] << " "
         << V << right << setw(13) << ""
         << V << endl;

    cout << V << " " << left << setw(14) << "最低分"
         << V << right << setw(5) << minScore[0] << " "
         << V << right << setw(5) << minScore[1] << " "
         << V << right << setw(5) << minScore[2] << " "
         << V << right << setw(13) << ""
         << V << endl;

    // 底線
    cout << BL;
    for (int k = 0; k < 15; k++) cout << H;
    cout << MB;
    for (int k = 0; k < 6; k++) cout << H;
    cout << MB;
    for (int k = 0; k < 6; k++) cout << H;
    cout << MB;
    for (int k = 0; k < 6; k++) cout << H;
    cout << MB;
    for (int k = 0; k < 14; k++) cout << H;
    cout << BR << endl;

    return 0;
}
```
