# 第四章：判斷式

> **學習目標**
> - 掌握 `if`、`if-else`、`if-else if-else` 的語法與使用時機
> - 理解巢狀 `if` 與程式流程控制
> - 熟練使用 `switch-case` 處理多重分支
> - 深入理解布林運算式的值、邏輯運算子與短路求值
> - 學會三元運算子，並辨識常見陷阱

---

## 4.1 if 判斷

### 4.1.1 為什麼需要判斷？

現實世界中充滿了條件：「如果下雨，就帶傘」、「如果成績大於 60 分，就及格」。  
程式也需要根據不同情況做不同的事，這就是**條件判斷（Conditional Statement）**的用途。

沒有判斷式的程式只能從第一行執行到最後一行，無論輸入是什麼，結果都一樣。判斷式讓程式擁有「做決定」的能力。

---

### 4.1.2 比較運算子

在學 `if` 之前，先認識用來構成條件的**比較運算子（Relational Operators）**：

| 運算子 | 意義 | 範例 | 結果 |
|--------|------|------|------|
| `==` | 等於 | `5 == 5` | `true` |
| `!=` | 不等於 | `5 != 3` | `true` |
| `<` | 小於 | `3 < 5` | `true` |
| `>` | 大於 | `5 > 3` | `true` |
| `<=` | 小於等於 | `5 <= 5` | `true` |
| `>=` | 大於等於 | `3 >= 5` | `false` |

> ⚠️ **超級常見的 Bug**：`=` 是**賦值**（assignment），`==` 才是**比較**（comparison）！  
> `if (x = 5)` 不是在比較 x 是否等於 5，而是把 5 賦值給 x，這幾乎永遠是 bug！

---

### 4.1.3 基本 `if` 語法

```
if (條件) {
    // 條件為 true 時執行的程式碼
}
```

執行流程：
```
         ┌──────────────┐
         │    條件判斷   │
         └──────┬───────┘
          true  │  false
         ┌──────▼──────┐    ┌─────────────┐
         │  執行區塊    │    │  跳過區塊   │
         └──────┬──────┘    └──────┬──────┘
                └──────────────────┘
                         ↓
                    繼續往下執行
```

**範例檔：`ex4_1_if_basic.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int score;
    cout << "請輸入你的分數：";
    cin >> score;

    if (score >= 60) {
        cout << "恭喜！你及格了！" << endl;
    }

    if (score == 100) {
        cout << "完美分數！太厲害了！" << endl;
    }

    cout << "程式結束。" << endl;
    return 0;
}
```

**執行範例（輸入 100）：**
```
請輸入你的分數：100
恭喜！你及格了！
完美分數！太厲害了！
程式結束。
```

**執行範例（輸入 50）：**
```
請輸入你的分數：50
程式結束。
```

> **注意**：即使條件區塊只有一行，也建議加上大括號 `{ }`，可避免後來新增程式碼時造成邏輯錯誤。

---

### 4.1.4 `if-else`：二選一

當你需要「如果……否則……」的邏輯，使用 `if-else`：

```
if (條件) {
    // 條件為 true 時執行
} else {
    // 條件為 false 時執行
}
```

執行流程：
```
         ┌──────────────┐
         │    條件判斷   │
         └──────┬───────┘
          true  │  false
    ┌───────────▼─┐   ┌─▼──────────────┐
    │  if 區塊    │   │  else 區塊      │
    └───────────┬─┘   └─┬──────────────┘
                └────┬───┘
                     ↓
               繼續往下執行
```

**範例檔：`ex4_1_if_else.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int score;
    cout << "請輸入你的分數：";
    cin >> score;

    if (score >= 60) {
        cout << "及格" << endl;
    } else {
        cout << "不及格" << endl;
    }

    // 判斷奇偶數
    int num;
    cout << "請輸入一個整數：";
    cin >> num;

    if (num % 2 == 0) {
        cout << num << " 是偶數" << endl;
    } else {
        cout << num << " 是奇數" << endl;
    }

    return 0;
}
```

---

### 4.1.5 `if-else if-else`：多重條件

當有三種以上的情況，使用 `else if` 串接：

```
if (條件一) {
    // 條件一為 true
} else if (條件二) {
    // 條件一為 false，條件二為 true
} else if (條件三) {
    // 條件一、二為 false，條件三為 true
} else {
    // 以上全部為 false
}
```

> **關鍵**：一旦某個條件成立，執行完該區塊後**直接跳出**，不再檢查後面的條件。

**範例檔：`ex4_1_multi_if.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int score;
    cout << "請輸入分數（0-100）：";
    cin >> score;

    // 成績等級判斷
    char grade;
    if      (score >= 90) grade = 'A';
    else if (score >= 80) grade = 'B';
    else if (score >= 70) grade = 'C';
    else if (score >= 60) grade = 'D';
    else                  grade = 'F';

    cout << "等級：" << grade << endl;

    // 配合說明文字
    if (grade == 'A') {
        cout << "優秀！繼續保持！" << endl;
    } else if (grade == 'B') {
        cout << "不錯！再加把勁！" << endl;
    } else if (grade == 'C') {
        cout << "及格，但還有進步空間。" << endl;
    } else if (grade == 'D') {
        cout << "剛好及格，需要加強。" << endl;
    } else {
        cout << "不及格，請找老師補救。" << endl;
    }

    return 0;
}
```

**常見錯誤：條件順序錯誤**

```cpp
// ❌ 錯誤版本：所有 >= 60 的分數都會印「D」
if (score >= 60) grade = 'D';
else if (score >= 70) grade = 'C';  // 永遠不會到這裡
else if (score >= 80) grade = 'B';  // 永遠不會到這裡
else if (score >= 90) grade = 'A';  // 永遠不會到這裡
else grade = 'F';

// ✅ 正確版本：從最嚴格的條件開始判斷
if      (score >= 90) grade = 'A';
else if (score >= 80) grade = 'B';
else if (score >= 70) grade = 'C';
else if (score >= 60) grade = 'D';
else                  grade = 'F';
```

---

### 4.1.6 巢狀 `if`（Nested if）

`if` 裡面可以再放 `if`，稱為**巢狀 if**：

**範例檔：`ex4_1_nested_if.cpp`**

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    int age;
    bool hasID;
    char answer;

    cout << "請輸入年齡：";
    cin >> age;
    cout << "是否有身分證？(y/n)：";
    cin >> answer;
    hasID = (answer == 'y' || answer == 'Y');

    if (age >= 18) {
        cout << "年齡符合資格。" << endl;
        if (hasID) {
            cout << "✅ 可以投票！" << endl;
        } else {
            cout << "❌ 需要出示身分證才能投票。" << endl;
        }
    } else {
        cout << "❌ 年齡未滿 18 歲，不能投票。" << endl;
        if (age >= 16) {
            cout << "（再等 " << 18 - age << " 年就可以了！）" << endl;
        }
    }

    return 0;
}
```

> **建議**：巢狀 if 最多 2～3 層，過深會讓程式難以閱讀。若層數太多，考慮用邏輯運算子合併條件，或重構成函式。

---

### 4.1.7 `switch-case`：多值分支

當條件是「某個變數等於哪個特定值」時，`switch-case` 比一連串的 `if-else if` 更清晰：

```cpp
switch (變數或運算式) {
    case 值一:
        // 執行內容
        break;
    case 值二:
        // 執行內容
        break;
    // ...
    default:
        // 以上都不符合時執行
        break;
}
```

**限制**：`switch` 的運算式必須是整數型別（`int`、`char`、`enum`），**不能用浮點數或字串**。

**範例檔：`ex4_1_switch.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int day;
    cout << "請輸入星期幾（1-7）：";
    cin >> day;

    switch (day) {
        case 1:
            cout << "星期一：開始新的一週，加油！" << endl;
            break;
        case 2:
            cout << "星期二：繼續努力！" << endl;
            break;
        case 3:
            cout << "星期三：已經過了一半了！" << endl;
            break;
        case 4:
            cout << "星期四：快到週末了！" << endl;
            break;
        case 5:
            cout << "星期五：TGIF！今晚要慶祝嗎？" << endl;
            break;
        case 6:
        case 7:
            cout << "週末！好好休息！" << endl;  // case 6 和 7 共用
            break;
        default:
            cout << "輸入錯誤，請輸入 1-7。" << endl;
            break;
    }

    return 0;
}
```

#### `break` 的重要性：Fall-through

如果省略 `break`，執行完該 `case` 後**會繼續往下執行**，直到遇到 `break` 或 `switch` 結尾，稱為 **fall-through**：

**範例檔：`ex4_1_switch_fallthrough.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    // Fall-through 的用途：多個 case 共用同一段程式碼
    char grade;
    cout << "請輸入等級（A/B/C/D/F）：";
    cin >> grade;

    switch (grade) {
        case 'A':
        case 'B':
        case 'C':
        case 'D':
            cout << "及格" << endl;
            break;
        case 'F':
            cout << "不及格" << endl;
            break;
        default:
            cout << "無效的等級" << endl;
    }

    // ❌ 忘記 break 造成的 bug 示範
    int x = 2;
    cout << "\n示範忘記 break 的結果：" << endl;
    switch (x) {
        case 1:
            cout << "Case 1" << endl;
        case 2:
            cout << "Case 2" << endl;  // 會執行
        case 3:
            cout << "Case 3" << endl;  // 也會執行！（fall-through）
        default:
            cout << "Default" << endl; // 也會執行！
    }

    return 0;
}
```

**輸出（x=2 時）：**
```
示範忘記 break 的結果：
Case 2
Case 3
Default
```

#### `switch` vs `if-else if` 選擇時機

| 情境 | 建議 |
|------|------|
| 條件是「等於某個整數/字元」 | `switch` 更清晰 |
| 條件是範圍比較（>, <, >=） | `if-else if` |
| 條件涉及浮點數或字串 | `if-else if` |
| 多個 case 共用同一邏輯 | `switch`（利用 fall-through） |

---

### 4.1.8 綜合範例：BMI 健康建議系統

**範例檔：`ex4_1_bmi_advice.cpp`**

```cpp
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    string name;
    double weight, height;

    cout << "=== BMI 健康評估系統 ===" << endl;
    cout << "姓名：";    cin >> name;
    cout << "體重(kg)："; cin >> weight;
    cout << "身高(cm)："; cin >> height;

    if (weight <= 0 || height <= 0) {
        cout << "錯誤：體重和身高必須為正數！" << endl;
        return 1;
    }

    double h = height / 100.0;
    double bmi = weight / (h * h);

    string category, advice;

    if (bmi < 18.5) {
        category = "體重過輕";
        advice   = "建議增加營養攝取，適當重訓增加肌肉量。";
    } else if (bmi < 24.0) {
        category = "正常範圍";
        advice   = "體重維持得很好！繼續保持健康的生活習慣。";
    } else if (bmi < 27.0) {
        category = "體重過重";
        advice   = "建議控制飲食，增加有氧運動頻率。";
    } else if (bmi < 30.0) {
        category = "輕度肥胖";
        advice   = "建議尋求營養師協助，制訂減重計畫。";
    } else {
        category = "中重度肥胖";
        advice   = "建議就醫評估，在醫師指導下進行健康管理。";
    }

    cout << fixed << setprecision(1);
    cout << "\n" << name << " 的評估結果：" << endl;
    cout << "BMI：" << bmi << endl;
    cout << "分類：" << category << endl;
    cout << "建議：" << advice << endl;

    return 0;
}
```

---

## 4.2 判斷式值

### 4.2.1 布林型別與真假值

C++ 中的條件判斷，本質上是在求一個**布林（bool）值**：`true` 或 `false`。

```cpp
bool a = (5 > 3);   // true
bool b = (5 < 3);   // false
bool c = (5 == 5);  // true

cout << a << endl;  // 輸出 1（true 以整數 1 表示）
cout << b << endl;  // 輸出 0（false 以整數 0 表示）
```

**任何數值都可以作為條件**（C++ 的 truthy/falsy 規則）：

| 值 | 布林意義 |
|----|----------|
| `0` | `false` |
| `0.0` | `false` |
| `nullptr` | `false` |
| **其他任何非零值** | `true` |

```cpp
if (1)    cout << "1 是 true"  << endl;  // 輸出
if (0)    cout << "0 是 true"  << endl;  // 不輸出
if (-5)   cout << "-5 是 true" << endl;  // 輸出
if (0.0)  cout << "0.0 是 true"<< endl;  // 不輸出
if (3.14) cout << "3.14 是 true"<<endl;  // 輸出
```

**範例檔：`ex4_2_bool_expr.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    // 比較運算子回傳 bool 值
    int x = 10, y = 20;

    bool isGreater = (x > y);
    bool isEqual   = (x == y);
    bool notEqual  = (x != y);

    cout << boolalpha;  // 讓 bool 顯示 true/false
    cout << "x > y  : " << isGreater << endl;  // false
    cout << "x == y : " << isEqual   << endl;  // false
    cout << "x != y : " << notEqual  << endl;  // true

    // 比較運算式可以直接在 if 中使用
    // 也可以儲存起來重用
    bool isTeen = (x >= 13 && x <= 19);
    if (isTeen) {
        cout << x << " 是青少年" << endl;
    } else {
        cout << x << " 不是青少年" << endl;
    }

    return 0;
}
```

---

### 4.2.2 邏輯運算子

**邏輯運算子（Logical Operators）**用來組合多個條件：

| 運算子 | 名稱 | 說明 | 範例 |
|--------|------|------|------|
| `&&` | 邏輯 AND（且） | 兩邊都 true 才 true | `a && b` |
| `\|\|` | 邏輯 OR（或） | 任一邊為 true 即 true | `a \|\| b` |
| `!` | 邏輯 NOT（非） | 反轉真假值 | `!a` |

**真值表：**

```
A     B     A&&B   A||B   !A
─────────────────────────────
true  true  true   true   false
true  false false  true   false
false true  false  true   true
false false false  false  true
```

**範例檔：`ex4_2_logical.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int age;
    double gpa;
    bool hasRecommendation;
    char ans;

    cout << "=== 研究所錄取資格審查 ===" << endl;
    cout << "年齡：";     cin >> age;
    cout << "GPA：";      cin >> gpa;
    cout << "有推薦信？(y/n)："; cin >> ans;
    hasRecommendation = (ans == 'y' || ans == 'Y');

    // 條件一：年齡在 22~35 之間
    bool ageOK = (age >= 22 && age <= 35);

    // 條件二：GPA 大於 3.0
    bool gpaOK = (gpa > 3.0);

    // 條件三：有推薦信
    // hasRecommendation 直接就是 bool

    // 錄取條件：GPA 符合，且（年齡符合 或 有推薦信）
    if (gpaOK && (ageOK || hasRecommendation)) {
        cout << "\n✅ 恭喜！符合申請資格。" << endl;
    } else {
        cout << "\n❌ 抱歉，目前不符合資格。" << endl;

        if (!gpaOK) {
            cout << "  → GPA 需在 3.0 以上（目前 " << gpa << "）" << endl;
        }
        if (!ageOK && !hasRecommendation) {
            cout << "  → 需符合年齡條件（22-35）或具備推薦信" << endl;
        }
    }

    // NOT 運算子的其他應用
    bool isEmpty = false;
    if (!isEmpty) {
        cout << "\n資料非空，可以處理。" << endl;
    }

    return 0;
}
```

**範圍判斷的常見錯誤：**

```cpp
int x = 10;

// ❌ 數學式的連鎖比較（C++ 不支援）
if (0 < x < 20) {  // 邏輯上正確，但 C++ 行為是：先算 (0<x)=true=1，再算 1<20=true
                    // 所以 x=100 時也會是 true！這是 bug！

// ✅ 正確寫法：用 && 連接兩個比較
if (0 < x && x < 20) {  // 正確
    cout << "x 在 0 到 20 之間" << endl;
}
```

---

### 4.2.3 短路求值（Short-circuit Evaluation）

C++ 的邏輯運算子有一個重要特性：**一旦結果確定，就不再計算後面的運算式**。

- `A && B`：若 A 為 `false`，B **不會被計算**（結果已確定是 false）
- `A || B`：若 A 為 `true`，B **不會被計算**（結果已確定是 true）

**範例檔：`ex4_2_shortcircuit.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    // 短路求值的安全應用：防止除以零
    int divisor = 0;
    int dividend = 10;

    // 若 divisor == 0，右側的除法不會執行（不會 crash）
    if (divisor != 0 && dividend / divisor > 2) {
        cout << "商大於 2" << endl;
    } else {
        cout << "除數為零，跳過計算" << endl;
    }

    // 短路求值的副作用：影響有副作用的函式呼叫
    int counter = 0;
    auto increment = [&]() -> bool {
        counter++;
        return true;
    };

    // 因為短路，increment 只被呼叫一次（false && ? 直接跳過後面）
    if (false && increment()) {
        cout << "不會執行" << endl;
    }
    cout << "counter = " << counter << endl;  // 0，increment 沒被呼叫

    // || 的短路：true || ? 跳過後面
    if (true || increment()) {
        cout << "counter 仍然 = " << counter << endl;  // 仍然 0
    }

    return 0;
}
```

**短路求值的實際應用：**

```cpp
// 安全地存取指標（第7章會詳細說明）
int* ptr = nullptr;
if (ptr != nullptr && *ptr > 0) {  // 若 ptr 為 null，不會解參考（避免 crash）
    cout << *ptr << endl;
}

// 字串長度檢查後再比較
string s = "";
if (!s.empty() && s[0] == 'A') {  // 若字串為空，不會存取 s[0]
    cout << "以 A 開頭" << endl;
}
```

---

### 4.2.4 三元運算子（Ternary Operator）

三元運算子 `?:` 是 `if-else` 的**簡化版**，它本身是一個**運算式**（有值）：

```cpp
條件 ? 值（true時） : 值（false時）
```

**範例檔：`ex4_2_ternary.cpp`**

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    int score;
    cout << "請輸入分數：";
    cin >> score;

    // 三元運算子：簡化 if-else
    string result = (score >= 60) ? "及格" : "不及格";
    cout << result << endl;

    // 可以嵌套（但超過兩層就不建議了）
    string grade = (score >= 90) ? "A" :
                   (score >= 80) ? "B" :
                   (score >= 70) ? "C" :
                   (score >= 60) ? "D" : "F";
    cout << "等級：" << grade << endl;

    // 用於輸出（很常見的用法）
    int num;
    cout << "請輸入一個整數：";
    cin >> num;
    cout << num << " 是 " << (num % 2 == 0 ? "偶數" : "奇數") << endl;

    // 取兩數中的較大值
    int a = 15, b = 28;
    int maxVal = (a > b) ? a : b;
    cout << "較大值：" << maxVal << endl;

    return 0;
}
```

**三元運算子 vs `if-else` 的選擇：**

```cpp
// ✅ 適合三元運算子：簡單的值選擇
int abs_val = (x >= 0) ? x : -x;

// ❌ 不適合：複雜邏輯，可讀性差
int result = (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);

// ✅ 改用 if-else 更清晰
int result;
if (a > b && a > c)      result = a;
else if (b > c)          result = b;
else                     result = c;
```

---

### 4.2.5 浮點數比較的陷阱

由於浮點數在電腦中以二進位儲存，**某些小數無法精確表示**，直接用 `==` 比較浮點數可能出錯：

**範例檔：`ex4_2_float_compare.cpp`**

```cpp
#include <iostream>
#include <cmath>    // fabs
#include <iomanip>
using namespace std;

int main() {
    double a = 0.1 + 0.2;
    double b = 0.3;

    cout << setprecision(20);
    cout << "0.1 + 0.2 = " << a << endl;
    cout << "0.3       = " << b << endl;

    // ❌ 直接比較：可能失敗！
    if (a == b) {
        cout << "相等（直接比較）" << endl;
    } else {
        cout << "不相等（直接比較）← 通常會到這裡！" << endl;
    }

    // ✅ 正確做法：比較差值是否在容忍範圍內
    const double EPSILON = 1e-9;  // 容忍誤差
    if (fabs(a - b) < EPSILON) {
        cout << "相等（誤差比較）" << endl;
    } else {
        cout << "不相等（誤差比較）" << endl;
    }

    return 0;
}
```

**輸出：**
```
0.1 + 0.2 = 0.30000000000000004440892098500626
0.3       = 0.29999999999999998889776975374843
不相等（直接比較）← 通常會到這裡！
相等（誤差比較）
```

> **結論**：**永遠不要用 `==` 直接比較浮點數**，改用 `fabs(a - b) < EPSILON`。

---

### 4.2.6 常見陷阱總整理

**範例檔：`ex4_2_traps.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 5;

    // ── 陷阱 1：= 與 == 混淆 ──────────────────────────
    // ❌ 賦值當條件（現代編譯器通常會警告）
    if (x = 10) {       // 把 10 賦給 x，條件永遠為 true
        cout << "x = " << x << endl;  // x 已變成 10！
    }

    x = 5;  // 重設

    // ✅ 正確：比較
    if (x == 5) {
        cout << "x 等於 5" << endl;
    }

    // ── 陷阱 2：沒有大括號造成的邏輯錯誤 ──────────────
    int score = 75;

    // ❌ 容易誤解為 else 屬於第二個 if
    if (score >= 90)
        cout << "優秀" << endl;
    if (score >= 60)
        cout << "及格" << endl;
    else                          // 這個 else 屬於最近的 if(score>=60)
        cout << "不及格" << endl;

    // ✅ 加上大括號，意圖明確
    if (score >= 90) {
        cout << "優秀" << endl;
    }
    if (score >= 60) {
        cout << "及格" << endl;
    } else {
        cout << "不及格" << endl;
    }

    // ── 陷阱 3：Dangling else 問題 ────────────────────
    int a = 5, b = 10;

    // 格式讓人誤以為 else 屬於外層 if
    if (a > 0)
        if (b > 5)
            cout << "a>0 且 b>5" << endl;
    else        // 注意！這個 else 屬於內層的 if(b>5)，不是外層！
        cout << "a <= 0" << endl;   // 這行只在 a>0 且 b<=5 時執行

    // ✅ 加上大括號讓結構清晰
    if (a > 0) {
        if (b > 5) {
            cout << "a>0 且 b>5" << endl;
        }
    } else {
        cout << "a <= 0" << endl;  // 現在確實是在 a<=0 時執行
    }

    // ── 陷阱 4：switch 忘記 break ─────────────────────
    int day = 3;
    switch (day) {
        case 3:
            cout << "星期三" << endl;
            // ❌ 忘記 break，繼續執行 case 4
        case 4:
            cout << "星期四" << endl;  // 也會印出！
            break;
    }

    return 0;
}
```

---

### 4.2.7 綜合範例：簡易計算機

**範例檔：`ex4_2_calculator.cpp`**

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double a, b;
    char op;

    cout << "=== 簡易計算機 ===" << endl;
    cout << "請輸入運算式（例：5.5 + 3）：";
    cin >> a >> op >> b;

    double result;
    bool valid = true;

    switch (op) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            if (b == 0) {
                cout << "錯誤：除數不能為零！" << endl;
                valid = false;
            } else {
                result = a / b;
            }
            break;
        case '%': {
            // 取餘數只支援整數
            int ia = static_cast<int>(a);
            int ib = static_cast<int>(b);
            if (ib == 0) {
                cout << "錯誤：除數不能為零！" << endl;
                valid = false;
            } else {
                result = ia % ib;
            }
            break;
        }
        case '^':
            result = pow(a, b);
            break;
        default:
            cout << "錯誤：未知的運算子 '" << op << "'！" << endl;
            valid = false;
    }

    if (valid) {
        cout << a << " " << op << " " << b << " = " << result << endl;
    }

    return 0;
}
```

---

## 📝 實作練習

### 基礎題

#### 練習 4-1：正負零判斷

**題目：** 輸入一個整數，判斷它是正數、負數還是零，並輸出對應訊息。

**輸入／輸出範例：**
```
輸入：-7
輸出：-7 是負數
```

<details>
<summary>✅ 參考答案</summary>

**檔名：`hw4_1.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "請輸入一個整數：";
    cin >> n;

    if (n > 0) {
        cout << n << " 是正數" << endl;
    } else if (n < 0) {
        cout << n << " 是負數" << endl;
    } else {
        cout << n << " 是零" << endl;
    }

    return 0;
}
```
</details>

---

#### 練習 4-2：閏年判斷

**題目：** 輸入一個西元年份，判斷是否為閏年。

**閏年條件（符合以下任一即為閏年）：**
- 能被 400 整除，**或**
- 能被 4 整除，**但不能**被 100 整除

**輸入／輸出範例：**
```
輸入：2024
輸出：2024 是閏年（366 天）
```

<details>
<summary>✅ 參考答案</summary>

**檔名：`hw4_2.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int year;
    cout << "請輸入年份：";
    cin >> year;

    bool isLeap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);

    if (isLeap) {
        cout << year << " 是閏年（366 天）" << endl;
    } else {
        cout << year << " 不是閏年（365 天）" << endl;
    }

    return 0;
}
```
</details>

---

#### 練習 4-3：三角形判斷

**題目：** 輸入三條邊的長度，判斷：
1. 能否構成三角形（任意兩邊之和大於第三邊）
2. 若能，判斷是等邊、等腰還是一般三角形
3. 並判斷是否為直角三角形（使用畢氏定理，注意浮點數誤差）

<details>
<summary>✅ 參考答案</summary>

**檔名：`hw4_3.cpp`**

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double a, b, c;
    cout << "請輸入三邊長（空格分隔）：";
    cin >> a >> b >> c;

    if (a <= 0 || b <= 0 || c <= 0) {
        cout << "邊長必須為正數！" << endl;
        return 1;
    }

    // 判斷能否構成三角形
    if (a + b <= c || a + c <= b || b + c <= a) {
        cout << "無法構成三角形。" << endl;
        return 0;
    }

    cout << "可以構成三角形！" << endl;

    // 判斷三角形種類
    if (a == b && b == c) {
        cout << "類型：等邊三角形" << endl;
    } else if (a == b || b == c || a == c) {
        cout << "類型：等腰三角形" << endl;
    } else {
        cout << "類型：一般三角形" << endl;
    }

    // 判斷直角三角形（找最長邊）
    double s1 = a, s2 = b, hyp = c;
    if (b >= a && b >= c) { s1 = a; s2 = c; hyp = b; }
    else if (a >= b && a >= c) { s1 = b; s2 = c; hyp = a; }

    const double EPS = 1e-9;
    if (fabs(s1*s1 + s2*s2 - hyp*hyp) < EPS) {
        cout << "同時也是直角三角形！" << endl;
    }

    return 0;
}
```
</details>

---

#### 練習 4-4：星期幾計算（Zeller 公式）

**題目：** 輸入西元年、月、日，使用以下公式計算星期幾並輸出。

**Zeller 公式（格里曆）：**  
若月份為 1 月或 2 月，將年份減 1，月份加 12。

```
h = (q + ⌊13(m+1)/5⌋ + K + ⌊K/4⌋ + ⌊J/4⌋ - 2J) mod 7
```

其中：h=0為週六, h=1為週日, h=2為週一...h=6為週五；  
q=日, m=月(3=3月,...,14=2月), K=年份後兩位, J=年份前兩位

**輸入範例：**
```
2024 4 20
```
**輸出範例：**
```
2024年4月20日是 星期六
```

<details>
<summary>✅ 參考答案</summary>

**檔名：`hw4_4.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int year, month, day;
    cout << "請輸入日期（年 月 日）：";
    cin >> year >> month >> day;

    if (month <= 2) {
        year--;
        month += 12;
    }

    int K = year % 100;
    int J = year / 100;
    int h = (day + (13*(month+1)/5) + K + K/4 + J/4 - 2*J) % 7;
    if (h < 0) h += 7;

    string days[] = {"星期六","星期日","星期一","星期二","星期三","星期四","星期五"};

    cout << year << "年" << month << "月" << day << "日是 "
         << days[h] << endl;

    return 0;
}
```
</details>

---

#### 練習 4-5：分段計費（電費計算）

**題目：** 台電分段電費如下，輸入當月用電度數，計算應繳電費（保留 2 位小數）：

| 度數範圍 | 每度單價（元） |
|----------|---------------|
| 1 ~ 120 度 | 1.63 |
| 121 ~ 330 度 | 2.38 |
| 331 ~ 500 度 | 3.52 |
| 501 ~ 700 度 | 4.80 |
| 701 度以上 | 5.66 |

**輸入範例：**
```
請輸入用電度數：450
```
**輸出範例：**
```
用電：450 度
電費明細：
  1 ~ 120 度（120度）：NT$ 195.60
  121 ~ 330 度（210度）：NT$ 499.80
  331 ~ 500 度（120度）：NT$ 422.40
應繳電費：NT$ 1117.80
```

<details>
<summary>✅ 參考答案</summary>

**檔名：`hw4_5.cpp`**

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double kwh;
    cout << "請輸入用電度數：";
    cin >> kwh;

    if (kwh < 0) {
        cout << "錯誤：度數不能為負數" << endl;
        return 1;
    }

    double total = 0;
    double remaining = kwh;

    cout << fixed << setprecision(2);
    cout << "用電：" << kwh << " 度" << endl;
    cout << "電費明細：" << endl;

    // 第一段：1~120
    if (remaining > 0) {
        double used = (remaining > 120) ? 120 : remaining;
        double cost = used * 1.63;
        total += cost;
        remaining -= used;
        cout << "  1 ~ 120 度（" << used << "度）：NT$ " << cost << endl;
    }
    // 第二段：121~330
    if (remaining > 0) {
        double used = (remaining > 210) ? 210 : remaining;
        double cost = used * 2.38;
        total += cost;
        remaining -= used;
        cout << "  121 ~ 330 度（" << used << "度）：NT$ " << cost << endl;
    }
    // 第三段：331~500
    if (remaining > 0) {
        double used = (remaining > 170) ? 170 : remaining;
        double cost = used * 3.52;
        total += cost;
        remaining -= used;
        cout << "  331 ~ 500 度（" << used << "度）：NT$ " << cost << endl;
    }
    // 第四段：501~700
    if (remaining > 0) {
        double used = (remaining > 200) ? 200 : remaining;
        double cost = used * 4.80;
        total += cost;
        remaining -= used;
        cout << "  501 ~ 700 度（" << used << "度）：NT$ " << cost << endl;
    }
    // 第五段：701以上
    if (remaining > 0) {
        double cost = remaining * 5.66;
        total += cost;
        cout << "  701 度以上（" << remaining << "度）：NT$ " << cost << endl;
    }

    cout << "應繳電費：NT$ " << total << endl;

    return 0;
}
```
</details>

---

#### 練習 4-6：石頭剪刀布

**題目：** 玩家輸入 1（石頭）、2（剪刀）、3（布），電腦隨機出拳，判斷勝負。

**提示：** 使用 `rand() % 3 + 1` 產生 1-3 的隨機數（需 `#include <cstdlib>`）。

<details>
<summary>✅ 參考答案</summary>

**檔名：`hw4_6.cpp`**

```cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

int main() {
    srand(static_cast<unsigned>(time(nullptr)));  // 設定隨機種子

    string names[] = {"", "石頭", "剪刀", "布"};

    int player;
    cout << "=== 石頭剪刀布 ===" << endl;
    cout << "1. 石頭  2. 剪刀  3. 布" << endl;
    cout << "請出拳：";
    cin >> player;

    if (player < 1 || player > 3) {
        cout << "輸入無效！" << endl;
        return 1;
    }

    int computer = rand() % 3 + 1;

    cout << "你出：" << names[player]   << endl;
    cout << "電腦出：" << names[computer] << endl;

    if (player == computer) {
        cout << "結果：平手！" << endl;
    } else if ((player == 1 && computer == 2) ||  // 石頭贏剪刀
               (player == 2 && computer == 3) ||  // 剪刀贏布
               (player == 3 && computer == 1)) {  // 布贏石頭
        cout << "結果：你贏了！🎉" << endl;
    } else {
        cout << "結果：你輸了！😢" << endl;
    }

    return 0;
}
```
</details>

---

#### 練習 4-7：成績等第轉換

**題目：** 輸入字母等第（A、B、C、D、F），使用 `switch` 輸出對應的中文說明與分數範圍。並將輸入不合法的情況也處理好。

<details>
<summary>✅ 參考答案</summary>

**檔名：`hw4_7.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    char grade;
    cout << "請輸入成績等第（A/B/C/D/F）：";
    cin >> grade;
    grade = toupper(grade);  // 轉大寫，接受小寫輸入

    switch (grade) {
        case 'A':
            cout << "優秀（90-100分）：表現傑出，繼續保持！" << endl;
            break;
        case 'B':
            cout << "良好（80-89分）：表現不錯，再加把勁！" << endl;
            break;
        case 'C':
            cout << "普通（70-79分）：尚可，仍有進步空間。" << endl;
            break;
        case 'D':
            cout << "及格（60-69分）：剛好過關，需要加強。" << endl;
            break;
        case 'F':
            cout << "不及格（0-59分）：需要補考或補救教學。" << endl;
            break;
        default:
            cout << "無效的等第「" << grade << "」，請輸入 A/B/C/D/F。" << endl;
    }

    return 0;
}
```
</details>

---

### 進階題

#### 練習 4-8：二次方程式求解

**題目：** 輸入二次方程式 ax² + bx + c = 0 的係數 a, b, c，求解並分類輸出。

**分類：**
- a = 0：退化為一次方程式
- 判別式 Δ = b² - 4ac > 0：兩相異實數根
- Δ = 0：兩相等實數根
- Δ < 0：兩共軛複數根

<details>
<summary>✅ 參考答案</summary>

**檔名：`hw4_8.cpp`**

```cpp
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    double a, b, c;
    cout << "請輸入 ax² + bx + c = 0 的係數 a, b, c：";
    cin >> a >> b >> c;

    cout << fixed << setprecision(4);

    if (a == 0) {
        // 一次方程式 bx + c = 0
        if (b == 0) {
            if (c == 0) cout << "無限多解（0 = 0）" << endl;
            else        cout << "無解（" << c << " = 0 矛盾）" << endl;
        } else {
            cout << "一次方程式，解：x = " << -c/b << endl;
        }
        return 0;
    }

    double delta = b*b - 4*a*c;
    cout << "判別式 Δ = " << delta << endl;

    if (delta > 0) {
        double x1 = (-b + sqrt(delta)) / (2*a);
        double x2 = (-b - sqrt(delta)) / (2*a);
        cout << "兩相異實數根：" << endl;
        cout << "  x1 = " << x1 << endl;
        cout << "  x2 = " << x2 << endl;
    } else if (delta == 0) {
        double x = -b / (2*a);
        cout << "兩相等實數根：x = " << x << endl;
    } else {
        double real = -b / (2*a);
        double imag = sqrt(-delta) / (2*a);
        cout << "兩共軛複數根：" << endl;
        cout << "  x1 = " << real << " + " << imag << "i" << endl;
        cout << "  x2 = " << real << " - " << imag << "i" << endl;
    }

    return 0;
}
```
</details>

---

#### 練習 4-9：簡易 ATM 存提款

**題目：** 模擬 ATM 操作。  
初始餘額 10,000 元，輸入密碼（正確密碼為 1234）。  
密碼正確後，選擇 1.查詢餘額、2.存款、3.提款、4.離開。  
- 密碼錯誤超過 3 次：鎖定帳戶
- 提款金額需為 1000 的倍數
- 餘額不足時拒絕提款

<details>
<summary>✅ 參考答案</summary>

**檔名：`hw4_9.cpp`**

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    const int CORRECT_PIN = 1234;
    double balance = 10000.0;
    int pin;
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;

    cout << "╔══════════════════╗" << endl;
    cout << "║    歡迎使用 ATM   ║" << endl;
    cout << "╚══════════════════╝" << endl;

    // 密碼驗證
    bool unlocked = false;
    while (attempts < MAX_ATTEMPTS) {
        cout << "請輸入密碼：";
        cin >> pin;
        attempts++;

        if (pin == CORRECT_PIN) {
            unlocked = true;
            break;
        } else {
            int remaining = MAX_ATTEMPTS - attempts;
            if (remaining > 0) {
                cout << "密碼錯誤，剩餘 " << remaining << " 次機會。" << endl;
            }
        }
    }

    if (!unlocked) {
        cout << "密碼錯誤次數過多，帳戶已鎖定！" << endl;
        return 0;
    }

    cout << "驗證成功！歡迎！" << endl;

    // 功能選單
    int choice;
    cout << "\n請選擇服務：" << endl;
    cout << "1. 查詢餘額" << endl;
    cout << "2. 存款" << endl;
    cout << "3. 提款" << endl;
    cout << "4. 離開" << endl;
    cout << "請輸入選項：";
    cin >> choice;

    cout << fixed << setprecision(0);

    switch (choice) {
        case 1:
            cout << "目前餘額：NT$ " << balance << endl;
            break;
        case 2: {
            double amount;
            cout << "請輸入存款金額：NT$ ";
            cin >> amount;
            if (amount <= 0) {
                cout << "存款金額必須為正數！" << endl;
            } else {
                balance += amount;
                cout << "存款成功！" << endl;
                cout << "目前餘額：NT$ " << balance << endl;
            }
            break;
        }
        case 3: {
            double amount;
            cout << "請輸入提款金額（1000 的倍數）：NT$ ";
            cin >> amount;
            if (amount <= 0) {
                cout << "提款金額必須為正數！" << endl;
            } else if (static_cast<int>(amount) % 1000 != 0) {
                cout << "提款金額必須是 1000 的倍數！" << endl;
            } else if (amount > balance) {
                cout << "餘額不足！目前餘額：NT$ " << balance << endl;
            } else {
                balance -= amount;
                cout << "提款成功！" << endl;
                cout << "目前餘額：NT$ " << balance << endl;
            }
            break;
        }
        case 4:
            cout << "感謝使用，再見！" << endl;
            break;
        default:
            cout << "無效的選項！" << endl;
    }

    return 0;
}
```
</details>

---

#### 練習 4-10：身分證字號驗證

**題目：** 輸入台灣身分證字號，驗證格式是否正確。

**驗證規則：**
1. 第一個字元為英文字母（A-Z），代表縣市
2. 第二個字元為 1（男）或 2（女）
3. 後 8 個字元全為數字
4. 英文字母對應的數字：A=10, B=11, ..., Z=35（依序對應）
5. 驗證碼公式：  
   設首字母對應數字為兩位數，十位數 × 1 + 個位數 × 9 + 第2碼 × 8 + 第3碼 × 7 + ... + 第9碼 × 1 + 第10碼  
   結果 mod 10 應 == 0

<details>
<summary>✅ 參考答案</summary>

**檔名：`hw4_10.cpp`**

```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string id;
    cout << "請輸入身分證字號：";
    cin >> id;

    // 基本格式檢查
    bool valid = true;
    string reason = "";

    if (id.length() != 10) {
        valid = false;
        reason = "長度必須為 10 碼";
    } else if (!isalpha(id[0]) || !isupper(id[0])) {
        valid = false;
        reason = "第一碼必須為大寫英文字母";
    } else if (id[1] != '1' && id[1] != '2') {
        valid = false;
        reason = "第二碼必須為 1（男）或 2（女）";
    } else {
        for (int i = 2; i < 10; i++) {
            if (!isdigit(id[i])) {
                valid = false;
                reason = "第 3~10 碼必須全為數字";
                break;
            }
        }
    }

    if (!valid) {
        cout << "格式錯誤：" << reason << endl;
        return 0;
    }

    // 驗證碼計算
    // 英文字母 A=10, B=11, ..., Z=35
    int letterCode = (id[0] - 'A') + 10;
    int sum = (letterCode / 10) * 1 + (letterCode % 10) * 9;

    int weights[] = {8, 7, 6, 5, 4, 3, 2, 1, 1};
    for (int i = 0; i < 9; i++) {
        sum += (id[i+1] - '0') * weights[i];
    }

    if (sum % 10 == 0) {
        string gender = (id[1] == '1') ? "男性" : "女性";
        cout << "驗證通過！" << gender << "，縣市代碼：" << id[0] << endl;
    } else {
        cout << "驗證失敗：驗證碼錯誤（" << id << " 不是有效的身分證字號）" << endl;
    }

    return 0;
}
```
</details>

---

## 💼 面試考題

**Q1. 以下程式的輸出為何？**

```cpp
int x = 5;
if (x = 3) {
    cout << "A" << endl;
} else {
    cout << "B" << endl;
}
cout << x << endl;
```

> **答：** 輸出 `A` 和 `3`。`x = 3` 是賦值運算式，將 3 賦給 x，運算式的值為 3（非零，即 true）。這是常見的 bug，應使用 `x == 3`。

---

**Q2. `switch` 和 `if-else if` 各自的優缺點？**

> **答：**
> - `switch`：可讀性佳（多值分支時），編譯器通常能生成跳躍表（jump table）效率較高；但只能判斷等值，不能判斷範圍，且不支援浮點數和字串。
> - `if-else if`：更靈活，可以判斷任意條件（範圍、邏輯組合）；但條件多時可讀性下降，效率通常是線性搜尋。

---

**Q3. 短路求值（Short-circuit Evaluation）是什麼？有什麼實際應用？**

> **答：** 邏輯運算子 `&&` 和 `||` 在確定結果後不再計算後續運算式。  
> 應用：
> 1. 防止空指標解參考：`if (ptr != nullptr && ptr->value > 0)`
> 2. 防止除以零：`if (b != 0 && a / b > 2)`
> 3. 效能優化：將最快確定為 false（&&）或 true（||）的條件放前面

---

**Q4. 為什麼不能用 `==` 比較浮點數？該怎麼做？**

> **答：** 浮點數以 IEEE 754 二進位格式儲存，某些十進位小數（如 0.1、0.3）無法精確表示，會有微小誤差。直接比較可能因誤差而失敗。  
> 正確做法：比較差值的絕對值是否小於容忍誤差（epsilon）：
> ```cpp
> if (fabs(a - b) < 1e-9) { /* 相等 */ }
> ```

---

**Q5. 以下程式中，`else` 對應哪個 `if`？**

```cpp
if (a > 0)
    if (b > 0)
        cout << "A" << endl;
else
    cout << "B" << endl;
```

> **答：** `else` 對應**內層的 `if (b > 0)`**，這是 C++ 的「dangling else」規則——`else` 永遠與最近的未配對 `if` 配對。因此，只有當 `a > 0` 且 `b <= 0` 時，才會輸出 "B"；`a <= 0` 時什麼都不輸出。  
> 解決方法：加上大括號明確指定配對關係。

---

**Q6. 三元運算子 `? :` 和 `if-else` 的主要區別？**

> **答：**
> - 三元運算子是**運算式**，有回傳值，可用在需要值的地方（如初始化、函式參數）
> - `if-else` 是**陳述式**（statement），沒有回傳值
> - 三元運算子適合簡單的值選擇；複雜邏輯仍應用 `if-else`
> - C++17 的 `if constexpr` 是另一個選擇（用於編譯期條件）

---

**Q7. 以下兩段程式是否等價？說明差異。**

```cpp
// 版本一
if (score >= 90) cout << "A";
else if (score >= 80) cout << "B";

// 版本二
if (score >= 90) cout << "A";
if (score >= 80) cout << "B";
```

> **答：** 不等價。  
> - 版本一：互斥，score=95 只輸出 "A"  
> - 版本二：兩個獨立 if，score=95 輸出 "AB"（因為 95 同時 ≥ 90 和 ≥ 80）  
> 這是初學者常見的錯誤，多分支判斷務必使用 `else if`。

---

## 🚀 專案：文字冒險遊戲

### 專案說明

建立一個簡單的**文字冒險遊戲**。玩家扮演一位旅行者，到達一個岔路口，根據選擇進入不同的劇情分支，最終有多種結局。這個專案充分練習多層巢狀 if、switch，以及邏輯運算子。

### 功能需求

1. 玩家先建立角色（輸入名字、選擇職業）
2. 職業不同，能力值不同（影響後面的選項）
3. 至少 3 個故事節點，每個節點 2-3 個選項
4. 至少 4 種不同結局（好結局、壞結局、隱藏結局等）
5. 所有選項都要有邊界檢查（輸入不合法時重新提示）

### 遊戲流程圖

```
開始
  ↓
角色建立（輸入名字、選擇職業：1.戰士 2.法師 3.盜賊）
  ↓
節點1：進入黑暗森林
  ├── 1. 正面突破（戰士加成）
  │      ↓
  │   節點2A：遇到巨龍
  │      ├── 1. 戰鬥（戰士勝率高）→ 寶藏結局 / 陣亡結局
  │      └── 2. 逃跑 → 逃脫結局
  │
  └── 2. 秘密繞行（盜賊加成）
         ↓
      節點2B：發現神秘神殿
         ├── 1. 進入（法師能解讀銘文）→ 古代秘術結局
         └── 2. 忽視 → 平淡結局
```

<details>
<summary>✅ 完整參考答案（點擊展開）</summary>

**檔名：`project4_adventure.cpp`**

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string name;
    int job;  // 1=戰士, 2=法師, 3=盜賊
    int attack, magic, agility;

    // ── 角色建立 ─────────────────────────────────────
    cout << "╔══════════════════════════════╗" << endl;
    cout << "║     黑暗森林 - 文字冒險      ║" << endl;
    cout << "╚══════════════════════════════╝" << endl;
    cout << "\n請輸入你的名字：";
    getline(cin, name);

    cout << "\n請選擇職業：" << endl;
    cout << "1. 戰士（攻擊+3，魔法-1，敏捷+0）" << endl;
    cout << "2. 法師（攻擊-1，魔法+3，敏捷+0）" << endl;
    cout << "3. 盜賊（攻擊+0，魔法-1，敏捷+3）" << endl;
    cout << "選擇：";
    cin >> job;

    string jobName;
    if (job == 1) {
        jobName = "戰士"; attack = 8; magic = 2; agility = 5;
    } else if (job == 2) {
        jobName = "法師"; attack = 4; magic = 9; agility = 5;
    } else if (job == 3) {
        jobName = "盜賊"; attack = 5; magic = 2; agility = 9;
    } else {
        cout << "無效選擇，預設為戰士。" << endl;
        jobName = "戰士"; attack = 8; magic = 2; agility = 5;
        job = 1;
    }

    cout << "\n歡迎，" << jobName << " " << name << "！" << endl;
    cout << "能力值 → 攻擊：" << attack << "  魔法：" << magic << "  敏捷：" << agility << endl;

    // ── 節點 1：進入黑暗森林 ──────────────────────────
    cout << "\n════════════════════════════════" << endl;
    cout << "你站在黑暗森林的入口。" << endl;
    cout << "前方有一條筆直的主路，樹叢中隱約可見一條小徑。" << endl;
    cout << "\n你選擇：" << endl;
    cout << "1. 走主路，正面突破" << endl;
    cout << "2. 走小徑，秘密繞行" << endl;
    cout << "選擇：";

    int choice1;
    cin >> choice1;
    while (choice1 != 1 && choice1 != 2) {
        cout << "無效選擇，請輸入 1 或 2：";
        cin >> choice1;
    }

    if (choice1 == 1) {
        // ── 主路分支 ──────────────────────────────────
        if (job == 1) {
            cout << "\n你的戰士體魄讓你輕鬆穿越荊棘，" << endl;
        } else {
            cout << "\n荊棘刮破了你的衣物，但你還是穿越了，" << endl;
        }
        cout << "深處，一頭巨龍擋住了你的去路！" << endl;

        cout << "\n龍發出震耳欲聾的咆哮！" << endl;
        cout << "你選擇：" << endl;
        cout << "1. 拔出武器，與龍一戰！" << endl;
        cout << "2. 趁龍不注意，悄悄逃走" << endl;
        cout << "選擇：";

        int choice2;
        cin >> choice2;
        while (choice2 != 1 && choice2 != 2) {
            cout << "無效選擇，請輸入 1 或 2：";
            cin >> choice2;
        }

        if (choice2 == 1) {
            // 戰鬥結局
            if (job == 1 && attack >= 8) {
                // 戰士的好結局
                cout << "\n════════════════════════════════" << endl;
                cout << "⚔️ 結局：英雄的榮耀" << endl;
                cout << "你揮舞巨劍，" << name << " 戰士的力量震驚了巨龍！" << endl;
                cout << "最終一劍刺穿龍心，龍窟中的寶藏全歸你了！" << endl;
                cout << "你成為了整個王國傳頌的英雄。" << endl;
            } else if (magic >= 9) {
                // 法師的隱藏結局
                cout << "\n════════════════════════════════" << endl;
                cout << "✨ 隱藏結局：龍與法師的盟約" << endl;
                cout << name << " 法師，你釋放了古老的「龍語術」！" << endl;
                cout << "巨龍竟然……停止了攻擊，俯下了牠的頭。" << endl;
                cout << "你不但沒有殺死牠，還成為了唯一能與龍溝通的人。" << endl;
                cout << "兩人結成同盟，拯救了即將滅亡的王國。" << endl;
            } else {
                // 其他職業的壞結局
                cout << "\n════════════════════════════════" << endl;
                cout << "💀 結局：勇敢的犧牲" << endl;
                cout << name << " 奮力一戰，但面對古老的巨龍，實力差距太大。" << endl;
                cout << "在最後一刻，你的身影化為了守護森林的光芒。" << endl;
                cout << "後來的旅人，都說這片森林有位英勇的守護靈。" << endl;
            }
        } else {
            // 逃跑結局
            if (agility >= 9) {
                cout << "\n════════════════════════════════" << endl;
                cout << "💨 結局：疾風盜賊" << endl;
                cout << name << " 盜賊的身手讓你如鬼魅般消失在龍的視野中，" << endl;
                cout << "順帶還從龍背上的鱗片縫隙中摸走了一枚古幣。" << endl;
                cout << "小贏，算是今天的成果了。" << endl;
            } else {
                cout << "\n════════════════════════════════" << endl;
                cout << "🏃 結局：狼狽逃跑" << endl;
                cout << "你拚命奔跑，龍的火焰燒掉了你半件外套，" << endl;
                cout << "但你活著跑出了森林。今天，保命第一！" << endl;
            }
        }

    } else {
        // ── 小徑分支 ──────────────────────────────────
        if (job == 3) {
            cout << "\n你的盜賊直覺引導你踏上了小徑，" << endl;
        } else {
            cout << "\n你謹慎地踏上了隱密的小徑，" << endl;
        }
        cout << "繞過了危險地帶，卻發現了一座長滿苔蘚的古老神殿！" << endl;

        cout << "\n神殿入口刻著難以辨認的古代銘文……" << endl;
        cout << "你選擇：" << endl;
        cout << "1. 嘗試解讀銘文並進入神殿" << endl;
        cout << "2. 這太危險了，還是繼續趕路吧" << endl;
        cout << "選擇：";

        int choice2;
        cin >> choice2;
        while (choice2 != 1 && choice2 != 2) {
            cout << "無效選擇，請輸入 1 或 2：";
            cin >> choice2;
        }

        if (choice2 == 1) {
            if (job == 2 && magic >= 9) {
                // 法師的最好結局
                cout << "\n════════════════════════════════" << endl;
                cout << "📖 結局：古代秘術的傳承者" << endl;
                cout << name << " 法師，你輕易讀出了銘文的意涵：" << endl;
                cout << "「唯有智慧之人方可進入」。" << endl;
                cout << "神殿內封印著上古法術典籍，你成為了三百年來" << endl;
                cout << "第一位讀懂它的人，並獲得了強大的魔法傳承。" << endl;
            } else if (agility >= 9) {
                cout << "\n════════════════════════════════" << endl;
                cout << "💎 結局：盜賊的眼光" << endl;
                cout << "雖然" << name << " 看不懂銘文，" << endl;
                cout << "但敏銳的直覺讓你迴避了所有陷阱，" << endl;
                cout << "你帶著一袋古代金幣，瀟灑地離開了神殿。" << endl;
            } else {
                cout << "\n════════════════════════════════" << endl;
                cout << "😵 結局：觸發陷阱" << endl;
                cout << "你搞不懂銘文的意思，誤觸了封印陷阱，" << endl;
                cout << name << " 被傳送到了完全陌生的地方……" << endl;
                cout << "這大概是另一段冒險的開始了。" << endl;
            }
        } else {
            cout << "\n════════════════════════════════" << endl;
            cout << "🌅 結局：平淡的旅程" << endl;
            cout << name << " 搖了搖頭，繞過神殿繼續趕路。" << endl;
            cout << "雖然沒有驚天動地的冒險，" << endl;
            cout << "你平安地抵達了目的地。" << endl;
            cout << "有時候，平凡也是一種幸福。" << endl;
        }
    }

    cout << "\n════════════════════════════════" << endl;
    cout << "感謝遊玩！按 Enter 結束……";
    cin.ignore();
    cin.get();

    return 0;
}
```
</details>

---

## 🔑 章節重點整理

```
┌─────────────────────────────────────────────────────┐
│                  第四章重點摘要                      │
├─────────────────────────────────────────────────────┤
│ if 語法                                             │
│  • if / if-else / if-else if-else / 巢狀 if         │
│  • 多重條件要從最嚴格的開始判斷（由大到小）          │
│  • 永遠加大括號，避免 dangling else                  │
│  • switch 適合整數/字元等值比較，必須記得 break      │
├─────────────────────────────────────────────────────┤
│ 判斷式值                                            │
│  • 比較運算子回傳 bool（true/false）                 │
│  • 非零值為 true，零值為 false                       │
│  • && 和 || 有短路求值，善加利用可防 crash           │
│  • 三元運算子 ?: 是運算式，有回傳值                  │
├─────────────────────────────────────────────────────┤
│ 常見陷阱                                            │
│  • = 是賦值，== 才是比較                             │
│  • 連鎖比較 0<x<10 在 C++ 不是你想的那樣            │
│  • 浮點數絕對不能用 == 比較                          │
│  • switch 忘記 break → fall-through bug             │
└─────────────────────────────────────────────────────┘
```

---

*教材版本：v1.0 | 適用對象：大學程式設計初學者 | 建議學習時間：6-8 小時*
