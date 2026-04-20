# 第三章：運算

> **學習目標**
> - 掌握指定運算子的語義與各種複合形式
> - 熟練使用算術、遞增遞減、關係、邏輯運算子
> - 理解位元運算子的原理與實務應用
> - 善用三元運算子撰寫簡潔條件表達式
> - 理解運算子優先順序與結合律，避免常見陷阱

---

## 3.1 指定運算子

### 3.1.1 基本指定運算子 `=`

在數學中，`=` 代表「等於」；但在 C++ 中，`=` 是**指定運算子（Assignment Operator）**，意思是「把右邊的值，放進左邊的變數」。

```
變數 = 運算式;
```

```cpp
int x = 10;     // 宣告 x，並指定值為 10
x = 20;         // 把 x 的值改成 20
x = x + 5;      // 先算右邊 (20 + 5 = 25)，再指定給 x
```

**重要：指定的方向是從右到左。**

```
x = x + 5;
│   └──┬──┘
│      │  ① 先計算右側：x 的舊值 + 5
└──────┘  ② 再把結果存進 x
```

> ⚠️ 初學者常見錯誤：把 `==`（比較）寫成 `=`（指定），這不會報錯但邏輯完全不同，是極危險的 bug。

---

### 3.1.2 左值與右值（lvalue / rvalue）

`=` 的左邊必須是**左值（lvalue）**，即「可被賦值的記憶體位置」；右邊必須是**右值（rvalue）**，即「有值的運算式」。

```cpp
int x = 5;   // ✅ x 是左值，5 是右值
5 = x;       // ❌ 編譯錯誤：5 不是左值，不能被賦值
x + 1 = 10;  // ❌ 編譯錯誤：x+1 是暫時值，不是左值
```

---

### 3.1.3 連鎖指定（Chained Assignment）

`=` 的結合律是**由右向左**，因此可以連鎖指定：

```cpp
int a, b, c;
a = b = c = 0;   // 等同於 a = (b = (c = 0))
                 // 先把 0 指定給 c，再把 c 的值指定給 b，再給 a
```

**範例檔：`ex3_1_assign.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b, c;

    // 連鎖指定：同時初始化多個變數
    a = b = c = 100;
    cout << "a=" << a << " b=" << b << " c=" << c << endl;

    // 指定的方向
    int x = 5;
    x = x * 2 + 1;  // 先算 5 * 2 + 1 = 11，再存入 x
    cout << "x = " << x << endl;

    // 型別不同時的指定（隱性轉換）
    double d = 3.99;
    int i = d;  // 小數被截斷，i = 3
    cout << "d=" << d << " 指定給 int 後=" << i << endl;

    return 0;
}
```

**輸出結果：**
```
a=100 b=100 c=100
x = 11
d=3.99 指定給 int 後=3
```

---

### 3.1.4 複合指定運算子

「先對自己運算，再存回去」是程式設計中非常常見的操作。C++ 提供**複合指定運算子**讓程式碼更簡潔。

#### 算術複合指定

| 運算子 | 等同於 | 說明 |
|--------|--------|------|
| `a += b` | `a = a + b` | 加後指定 |
| `a -= b` | `a = a - b` | 減後指定 |
| `a *= b` | `a = a * b` | 乘後指定 |
| `a /= b` | `a = a / b` | 除後指定 |
| `a %= b` | `a = a % b` | 取餘後指定 |

#### 位元複合指定（詳見 3.2.5）

| 運算子 | 等同於 |
|--------|--------|
| `a &= b` | `a = a & b` |
| `a \|= b` | `a = a \| b` |
| `a ^= b` | `a = a ^ b` |
| `a <<= n` | `a = a << n` |
| `a >>= n` | `a = a >> n` |

**範例檔：`ex3_1_compound.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int score = 100;

    score -= 10;  // 扣 10 分
    cout << "扣 10 分後：" << score << endl;   // 90

    score *= 2;   // 雙倍
    cout << "雙倍後：" << score << endl;        // 180

    score /= 3;   // 除以 3（整數除法）
    cout << "除以 3 後：" << score << endl;     // 60

    score += 5;
    score %= 7;   // 取 7 的餘數
    cout << "加 5 再 mod 7：" << score << endl; // 65 % 7 = 2

    // 字串也可以用 +=（字串串接）
    string greeting = "Hello";
    greeting += ", World!";
    cout << greeting << endl;   // Hello, World!

    return 0;
}
```

**輸出結果：**
```
扣 10 分後：90
雙倍後：180
除以 3 後：60
加 5 再 mod 7：2
Hello, World!
```

---

## 3.2 運算子

### 3.2.1 算術運算子（Arithmetic Operators）

| 運算子 | 名稱 | 說明 | 範例（a=10, b=3） | 結果 |
|--------|------|------|-------------------|------|
| `+` | 加法 | 兩數相加 | `a + b` | `13` |
| `-` | 減法 | 兩數相減 | `a - b` | `7` |
| `*` | 乘法 | 兩數相乘 | `a * b` | `30` |
| `/` | 除法 | 兩數相除 | `a / b` | `3`（整數除法！） |
| `%` | 取餘數 | 除法的餘數 | `a % b` | `1` |
| `-` | 負號 | 取負值（一元） | `-a` | `-10` |
| `+` | 正號 | 取正值（一元） | `+a` | `10` |

#### 整數除法與取餘數

這是初學者**最容易踩到的陷阱**：

```cpp
int a = 7, b = 2;
cout << a / b;    // 輸出 3，不是 3.5！小數部分直接丟棄（不是四捨五入）
cout << a % b;    // 輸出 1（7 = 2 × 3 + 1）
```

**整數除法規則**：兩個運算元都是整數時，結果也是整數，小數部分**直接截斷**（向零截斷）。

```cpp
int x = -7, y = 2;
cout << x / y;   // -3（不是 -4，是向零截斷）
cout << x % y;   // -1（符號跟隨被除數）
```

**取餘數的數學關係**：`a % b` 的結果 `r` 滿足：`a = (a/b) * b + r`

```
-7 = (-7/2) * 2 + r
-7 = (-3)   * 2 + r
r  = -7 - (-6) = -1
```

#### 浮點數運算

```cpp
double a = 7.0, b = 2.0;
cout << a / b;   // 3.5 ✅（浮點數除法）

// 混合型別：int 會自動提升為 double
int x = 7;
double y = 2.0;
cout << x / y;   // 3.5 ✅
```

> **黃金法則**：只要除法的兩個運算元中**至少一個是浮點數**，結果就是浮點數。

#### 常見數學運算（需要 `<cmath>`）

```cpp
#include <cmath>

sqrt(9.0)        // 3.0，平方根
pow(2.0, 10.0)   // 1024.0，次方
abs(-5)          // 5，整數絕對值（<cstdlib>）
fabs(-3.14)      // 3.14，浮點數絕對值
ceil(3.2)        // 4.0，無條件進位
floor(3.9)       // 3.0，無條件捨去
round(3.5)       // 4.0，四捨五入
fmod(7.5, 2.0)   // 1.5，浮點數取餘（% 只能用於整數）
log(M_E)         // 1.0，自然對數
log10(100.0)     // 2.0，以 10 為底對數
sin(M_PI / 6)    // 0.5，正弦（參數為弧度）
```

**範例檔：`ex3_2_arithmetic.cpp`**

```cpp
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    // 整數算術
    int a = 17, b = 5;
    cout << "=== 整數算術（a=17, b=5）===" << endl;
    cout << "a + b = " << a + b << endl;   // 22
    cout << "a - b = " << a - b << endl;   // 12
    cout << "a * b = " << a * b << endl;   // 85
    cout << "a / b = " << a / b << endl;   // 3（整數除法）
    cout << "a % b = " << a % b << endl;   // 2

    // 負數的除法與取餘
    cout << "\n=== 負數除法 ===" << endl;
    cout << "-17 /  5 = " << -17 /  5 << endl;   // -3
    cout << " 17 / -5 = " <<  17 / -5 << endl;   // -3
    cout << "-17 / -5 = " << -17 / -5 << endl;   //  3
    cout << "-17 %  5 = " << -17 %  5 << endl;   // -2
    cout << " 17 % -5 = " <<  17 % -5 << endl;   //  2

    // 浮點數運算
    cout << "\n=== 浮點數運算 ===" << endl;
    double x = 17.0, y = 5.0;
    cout << fixed << setprecision(4);
    cout << "17.0 / 5.0 = " << x / y << endl;    // 3.4000
    cout << "fmod(17.0, 5.0) = " << fmod(x, y) << endl;  // 2.0000

    // 數學函式
    cout << "\n=== 數學函式 ===" << endl;
    cout << "sqrt(144) = " << sqrt(144.0) << endl;       // 12.0000
    cout << "pow(2, 8) = " << pow(2.0, 8.0) << endl;    // 256.0000
    cout << "ceil(3.2) = " << ceil(3.2) << endl;         // 4.0000
    cout << "floor(3.9) = " << floor(3.9) << endl;       // 3.0000
    cout << "round(3.5) = " << round(3.5) << endl;       // 4.0000
    cout << "abs(-42) = " << abs(-42) << endl;            // 42.0000

    return 0;
}
```

**輸出結果：**
```
=== 整數算術（a=17, b=5）===
a + b = 22
a - b = 12
a * b = 85
a / b = 3
a % b = 2

=== 負數除法 ===
-17 /  5 = -3
 17 / -5 = -3
-17 / -5 =  3
-17 %  5 = -2
 17 % -5 =  2

=== 浮點數運算 ===
17.0 / 5.0 = 3.4000
fmod(17.0, 5.0) = 2.0000

=== 數學函式 ===
sqrt(144) = 12.0000
pow(2, 8) = 256.0000
ceil(3.2) = 4.0000
floor(3.9) = 3.0000
round(3.5) = 4.0000
abs(-42) = 42.0000
```

#### 整數溢位（Integer Overflow）

整數型別有最大值，超過時會發生**溢位（Overflow）**，結果會「繞回來」（wrapping），這是**未定義行為（Undefined Behavior）**，需要特別注意：

```cpp
int maxInt = 2147483647;    // INT_MAX
cout << maxInt + 1;         // ❌ 溢位！結果不確定（通常變成 -2147483648）

// 正確做法：使用更大的型別
long long big = 2147483647LL;
cout << big + 1;            // ✅ 2147483648
```

---

### 3.2.2 遞增遞減運算子（Increment / Decrement）

遞增 `++` 和遞減 `--` 是把變數加 1 或減 1 的捷徑，分為**前置**與**後置**兩種形式。

| 形式 | 語法 | 行為 |
|------|------|------|
| 前置遞增 | `++x` | **先加 1**，再使用 x 的值 |
| 後置遞增 | `x++` | **先使用** x 的值，再加 1 |
| 前置遞減 | `--x` | **先減 1**，再使用 x 的值 |
| 後置遞減 | `x--` | **先使用** x 的值，再減 1 |

**記憶口訣**：`++` 在前就「先加再用」，`++` 在後就「先用再加」。

```cpp
int a = 5;
int b = ++a;   // a 先變 6，b = 6
// 此時 a = 6, b = 6

int c = 5;
int d = c++;   // d = 5（c 的舊值），然後 c 變 6
// 此時 c = 6, d = 5
```

**範例檔：`ex3_2_increment.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 10;

    // 前置遞增
    cout << "x = " << x << endl;        // 10
    cout << "++x = " << ++x << endl;    // 11（x 先加 1，再輸出）
    cout << "x = " << x << endl;        // 11

    cout << "---" << endl;

    // 後置遞增
    int y = 10;
    cout << "y = " << y << endl;        // 10
    cout << "y++ = " << y++ << endl;    // 10（先輸出 y 的舊值，再加 1）
    cout << "y = " << y << endl;        // 11

    cout << "---" << endl;

    // 前後置的差異在運算式中
    int a = 5, b = 5;
    int ra = ++a * 2;   // a 先變 6，ra = 6 * 2 = 12
    int rb = b++ * 2;   // rb = 5 * 2 = 10，b 再變 6

    cout << "前置：a=" << a << " ra=" << ra << endl;  // a=6 ra=12
    cout << "後置：b=" << b << " rb=" << rb << endl;  // b=6 rb=10

    return 0;
}
```

**輸出結果：**
```
x = 10
++x = 11
x = 11
---
y = 10
y++ = 10
y = 11
---
前置：a=6 ra=12
後置：b=6 rb=10
```

> **工程師建議**：如果只是要「讓變數加 1」而不需要舊值，前置（`++i`）的效率通常和後置相同（對基本型別）。但對**物件**（如疊代器）來說，前置效率更高，因為後置需要製造一份副本儲存舊值。**養成習慣優先使用前置遞增。**

> ⚠️ 不要在同一個運算式中對同一變數使用多次 `++`，如 `i++ + ++i`，這是未定義行為！

---

### 3.2.3 關係運算子（Relational Operators）

關係運算子用於**比較兩個值**，結果是 `bool`（`true` 或 `false`）。

| 運算子 | 意義 | 範例（a=5, b=3） | 結果 |
|--------|------|-----------------|------|
| `==` | 等於 | `a == b` | `false` |
| `!=` | 不等於 | `a != b` | `true` |
| `>` | 大於 | `a > b` | `true` |
| `<` | 小於 | `a < b` | `false` |
| `>=` | 大於等於 | `a >= 5` | `true` |
| `<=` | 小於等於 | `b <= 3` | `true` |

**範例檔：`ex3_2_relational.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20;

    cout << boolalpha;  // 讓 bool 輸出 true/false 而非 1/0

    cout << "a = " << a << ", b = " << b << endl;
    cout << "a == b : " << (a == b) << endl;   // false
    cout << "a != b : " << (a != b) << endl;   // true
    cout << "a >  b : " << (a >  b) << endl;   // false
    cout << "a <  b : " << (a <  b) << endl;   // true
    cout << "a >= b : " << (a >= b) << endl;   // false
    cout << "a <= b : " << (a <= b) << endl;   // true

    // 關係運算的結果可以存進 bool
    bool isAdult = (a >= 18);
    cout << "\n" << a << " 歲是否成年：" << isAdult << endl;  // false

    // 字元比較（依 ASCII 值）
    char c1 = 'A', c2 = 'Z';
    cout << "'A' < 'Z' : " << (c1 < c2) << endl;   // true（65 < 90）

    // 浮點數比較的陷阱
    double x = 0.1 + 0.2;
    double y = 0.3;
    cout << "\n0.1 + 0.2 == 0.3 : " << (x == y) << endl;  // false！！！

    // 正確的浮點數比較：檢查差值是否夠小
    double epsilon = 1e-9;
    cout << "誤差比較法：" << (fabs(x - y) < epsilon) << endl;  // true

    return 0;
}
```

**輸出結果：**
```
a = 10, b = 20
a == b : false
a != b : true
a >  b : false
a <  b : true
a >= b : false
a <= b : true

10 歲是否成年：false
'A' < 'Z' : true

0.1 + 0.2 == 0.3 : false！！！
誤差比較法：true
```

> ⚠️ **浮點數比較陷阱**：由於浮點數在電腦中的表示方式，`0.1 + 0.2` 的結果不精確等於 `0.3`（實際是 `0.30000000000000004`）。**永遠不要用 `==` 直接比較兩個浮點數**，應改用「差值是否在容許誤差（epsilon）以內」。

---

### 3.2.4 邏輯運算子（Logical Operators）

邏輯運算子用於**組合多個條件**，運算元和結果皆為 `bool`。

| 運算子 | 名稱 | 語法 | 說明 |
|--------|------|------|------|
| `&&` | 邏輯且（AND） | `A && B` | A 且 B 均為 true，結果才是 true |
| `\|\|` | 邏輯或（OR） | `A \|\| B` | A 或 B 其中一個為 true，結果就是 true |
| `!` | 邏輯非（NOT） | `!A` | 取反：true 變 false，false 變 true |

**真值表：**

| A | B | A && B | A \|\| B | !A |
|---|---|--------|----------|-----|
| T | T | T | T | F |
| T | F | F | T | F |
| F | T | F | T | T |
| F | F | F | F | T |

**範例檔：`ex3_2_logical.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int age = 20;
    double gpa = 3.5;
    bool hasScholarship = true;

    cout << boolalpha;

    // && 應用：所有條件都要成立
    bool canApply = (age >= 18) && (gpa >= 3.0);
    cout << "可申請（18歲以上且GPA≥3.0）：" << canApply << endl;  // true

    // || 應用：至少一個條件成立
    bool getBonus = (gpa >= 3.8) || hasScholarship;
    cout << "獲得獎金（GPA≥3.8 或有獎學金）：" << getBonus << endl; // true

    // ! 應用：條件取反
    bool isMinor = !(age >= 18);
    cout << "是否未成年：" << isMinor << endl;  // false

    // 複合條件
    bool isEligible = (age >= 18) && (age <= 35) && (gpa >= 3.0) && !isMinor;
    cout << "完整資格審查：" << isEligible << endl;  // true

    // 短路求值示範
    cout << "\n=== 短路求值 ===" << endl;
    int x = 0;
    // && 短路：左側為 false，右側不執行
    bool r1 = (x != 0) && (10 / x > 1);   // 不會除以零！
    cout << "短路 &&：" << r1 << endl;     // false（安全）

    // || 短路：左側為 true，右側不執行
    int count = 0;
    bool r2 = (count >= 0) || (++count > 0);  // count 不會被遞增
    cout << "短路 ||：" << r2 << " count=" << count << endl;  // true, count=0

    return 0;
}
```

**輸出結果：**
```
可申請（18歲以上且GPA≥3.0）：true
獲得獎金（GPA≥3.8 或有獎學金）：true
是否未成年：false
完整資格審查：true

=== 短路求值 ===
短路 &&：false
短路 ||：true count=0
```

#### 短路求值（Short-circuit Evaluation）

這是邏輯運算子的重要特性，不只是效率問題，更是安全性保障：

- **`A && B`**：若 A 為 `false`，**B 一定不執行**（整體已確定為 false）
- **`A || B`**：若 A 為 `true`，**B 一定不執行**（整體已確定為 true）

```cpp
// 常見的安全性應用：先確認指標不為 nullptr，再存取
Node* ptr = nullptr;
if (ptr != nullptr && ptr->value > 0) {  // 短路保護，不會造成存取錯誤
    // ...
}

// 常見的安全性應用：先確認分母不為零
int divisor = 0;
if (divisor != 0 && 100 / divisor > 2) {  // 短路保護，不會除以零
    // ...
}
```

---

### 3.2.5 位元運算子（Bitwise Operators）

位元運算子直接對整數的**每個二進位位元（bit）**進行操作，是底層程式設計、嵌入式系統、演算法最佳化的重要工具。

> **前置知識**：整數在記憶體中以二進位（0 和 1）表示。例如 `int a = 13` 在 32 位元中是 `00000000 00000000 00000000 00001101`，為求簡潔以下用 8 位元示範。

| 運算子 | 名稱 | 說明 |
|--------|------|------|
| `&` | 位元 AND | 對應位元都是 1，結果才是 1 |
| `\|` | 位元 OR | 對應位元有一個是 1，結果就是 1 |
| `^` | 位元 XOR | 對應位元相同為 0，不同為 1 |
| `~` | 位元 NOT | 所有位元取反（一元運算子） |
| `<<` | 左移 | 所有位元向左移 n 位，右側補 0 |
| `>>` | 右移 | 所有位元向右移 n 位，無號數左側補 0，有號數補符號位 |

#### 位元 AND（`&`）

```
  13:  0000 1101
&  9:  0000 1001
       ---------
    =  0000 1001  (= 9)
```

規則：**兩個位元都是 1，結果才是 1**（類比：串聯開關，兩個都要開才亮燈）

**用途**：**遮罩（masking）**——提取特定位元的值

```cpp
int flags = 0b10110101;   // 某個狀態暫存器
int mask  = 0b00001111;   // 只保留低 4 位
int low4  = flags & mask; // 提取低 4 位：0b00000101 = 5
```

#### 位元 OR（`|`）

```
  13:  0000 1101
|  9:  0000 1001
       ---------
    =  0000 1101  (= 13)
```

規則：**兩個位元有一個是 1，結果就是 1**（類比：並聯開關，一個開就亮）

**用途**：**設定（set）特定位元**

```cpp
int flags = 0b00000000;
flags = flags | 0b00000100;  // 把第 2 位設為 1
// 或更簡潔：flags |= (1 << 2);
```

#### 位元 XOR（`^`）

```
  13:  0000 1101
^  9:  0000 1001
       ---------
    =  0000 0100  (= 4)
```

規則：**兩個位元相同為 0，不同為 1**

**用途**：
1. **切換（toggle）特定位元**：`x ^= mask;`（0 變 1，1 變 0）
2. **不用暫存變數交換兩個整數**：

```cpp
int a = 5, b = 3;
a ^= b;  // a = 5^3 = 6
b ^= a;  // b = 3^6 = 5
a ^= b;  // a = 6^5 = 3
// 結果 a = 3, b = 5（已交換）
```

#### 位元 NOT（`~`）

```
 ~13:  ~0000 1101
    =   1111 0010  (= -14，因為補數表示法)
```

規則：所有位元取反（0→1, 1→0）

> ⚠️ 結果可能出乎意料，因為有號整數使用「2 的補數」表示法：`~n = -(n+1)`

#### 左移（`<<`）與右移（`>>`）

```
13 << 2 :  0000 1101 → 0011 0100  (= 52，等於 13 × 4)
13 >> 1 :  0000 1101 → 0000 0110  (= 6，等於 13 / 2 取整)
```

**數學意義：**
- `n << k` 等於 `n × 2^k`（比乘法快！）
- `n >> k` 等於 `n / 2^k`（比除法快，但向下取整，負數行為因編譯器而異）

```cpp
int x = 1;
cout << (x << 0);  // 1  = 1 × 2^0
cout << (x << 1);  // 2  = 1 × 2^1
cout << (x << 2);  // 4  = 1 × 2^2
cout << (x << 8);  // 256 = 1 × 2^8
```

**範例檔：`ex3_2_bitwise.cpp`**

```cpp
#include <iostream>
#include <bitset>
using namespace std;

// 輔助函式：以二進位顯示 8 位整數
void printBinary(const string& label, int val) {
    cout << label << " = " << bitset<8>(val) << " (十進位: " << val << ")" << endl;
}

int main() {
    int a = 0b00001101;  // 13
    int b = 0b00001001;  // 9

    cout << "=== 位元運算 ===" << endl;
    printBinary("a       ", a);
    printBinary("b       ", b);
    cout << endl;
    printBinary("a & b   ", a & b);   // 9
    printBinary("a | b   ", a | b);   // 13
    printBinary("a ^ b   ", a ^ b);   // 4
    printBinary("~a (低8)", ~a & 0xFF); // 242（只看低8位）

    cout << "\n=== 移位運算 ===" << endl;
    printBinary("a << 1  ", a << 1);  // 26（×2）
    printBinary("a << 2  ", a << 2);  // 52（×4）
    printBinary("a >> 1  ", a >> 1);  // 6（÷2）

    cout << "\n=== 實用技巧 ===" << endl;

    // 判斷第 n 個 bit 是否為 1
    int flags = 0b10110101;
    int n = 2;  // 檢查第 2 bit（從 0 開始數）
    bool isSet = (flags >> n) & 1;
    cout << "flags 的第 " << n << " 位是 " << (isSet ? "1" : "0") << endl;

    // 設定第 n 個 bit 為 1
    flags |= (1 << 4);
    printBinary("設定第4位後", flags & 0xFF);

    // 清除第 n 個 bit（設為 0）
    flags &= ~(1 << 2);
    printBinary("清除第2位後", flags & 0xFF);

    // 切換第 n 個 bit
    flags ^= (1 << 0);
    printBinary("切換第0位後", flags & 0xFF);

    cout << "\n=== 移位作快速乘除 ===" << endl;
    int x = 7;
    cout << x << " × 8 = " << (x << 3) << endl;   // 56
    cout << x << " × 4 = " << (x << 2) << endl;   // 28
    cout << "64 ÷ 4 = " << (64 >> 2) << endl;      // 16

    return 0;
}
```

**輸出結果：**
```
=== 位元運算 ===
a        = 00001101 (十進位: 13)
b        = 00001001 (十進位: 9)

a & b    = 00001001 (十進位: 9)
a | b    = 00001101 (十進位: 13)
a ^ b    = 00000100 (十進位: 4)
~a (低8) = 11110010 (十進位: 242)

=== 移位運算 ===
a << 1   = 00011010 (十進位: 26)
a << 2   = 00110100 (十進位: 52)
a >> 1   = 00000110 (十進位: 6)

=== 實用技巧 ===
flags 的第 2 位是 1
設定第4位後 = 10110101 (十進位: ...)
清除第2位後 = ...
切換第0位後 = ...

=== 移位作快速乘除 ===
7 × 8 = 56
7 × 4 = 28
64 ÷ 4 = 16
```

#### 位元運算的實務應用：旗標（Flags）

使用單一整數的每個 bit 代表不同的布林狀態，節省記憶體並加速比較：

**範例檔：`ex3_2_flags.cpp`**

```cpp
#include <iostream>
#include <bitset>
using namespace std;

// 使用位元旗標定義權限
const int PERM_READ    = 1 << 0;  // 0001 = 1
const int PERM_WRITE   = 1 << 1;  // 0010 = 2
const int PERM_EXECUTE = 1 << 2;  // 0100 = 4
const int PERM_ADMIN   = 1 << 3;  // 1000 = 8

void printPermissions(int perm) {
    cout << "二進位：" << bitset<4>(perm) << endl;
    cout << "讀取：" << ((perm & PERM_READ)    ? "✓" : "✗") << endl;
    cout << "寫入：" << ((perm & PERM_WRITE)   ? "✓" : "✗") << endl;
    cout << "執行：" << ((perm & PERM_EXECUTE) ? "✓" : "✗") << endl;
    cout << "管理：" << ((perm & PERM_ADMIN)   ? "✓" : "✗") << endl;
}

int main() {
    // 一般使用者：只有讀取和執行權限
    int userPerm = PERM_READ | PERM_EXECUTE;  // 0001 | 0100 = 0101 = 5
    cout << "=== 一般使用者 ===" << endl;
    printPermissions(userPerm);

    cout << "\n=== 加入寫入權限 ===" << endl;
    userPerm |= PERM_WRITE;   // 設定寫入 bit
    printPermissions(userPerm);

    cout << "\n=== 移除執行權限 ===" << endl;
    userPerm &= ~PERM_EXECUTE;  // 清除執行 bit
    printPermissions(userPerm);

    // 管理員：所有權限
    int adminPerm = PERM_READ | PERM_WRITE | PERM_EXECUTE | PERM_ADMIN;
    cout << "\n=== 管理員 ===" << endl;
    printPermissions(adminPerm);

    return 0;
}
```

---

### 3.2.6 三元運算子（Ternary / Conditional Operator）

三元運算子 `? :` 是 C++ 中**唯一的三個運算元的運算子**，是 `if-else` 的簡化版。

```
條件 ? 值（當條件為 true）: 值（當條件為 false）
```

```cpp
// if-else 寫法
int abs_val;
if (x >= 0) abs_val = x;
else        abs_val = -x;

// 等同於三元運算子寫法（一行）
int abs_val = (x >= 0) ? x : -x;
```

**範例檔：`ex3_2_ternary.cpp`**

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    int score = 75;
    string result = (score >= 60) ? "及格" : "不及格";
    cout << "成績 " << score << " 分：" << result << endl;

    // 求最大值
    int a = 15, b = 28;
    int maxVal = (a > b) ? a : b;
    cout << a << " 和 " << b << " 的最大值：" << maxVal << endl;

    // 絕對值
    int x = -42;
    int absX = (x >= 0) ? x : -x;
    cout << x << " 的絕對值：" << absX << endl;

    // 巢狀三元（可讀性變差，不建議超過兩層）
    int grade = 88;
    string letter = (grade >= 90) ? "A" :
                    (grade >= 80) ? "B" :
                    (grade >= 70) ? "C" :
                    (grade >= 60) ? "D" : "F";
    cout << grade << " 分的等級：" << letter << endl;

    // 在輸出中直接使用
    bool isPrime = true;
    cout << "17 是否為質數：" << (isPrime ? "是" : "否") << endl;

    return 0;
}
```

**輸出結果：**
```
成績 75 分：及格
15 和 28 的最大值：28
-42 的絕對值：42
88 分的等級：B
17 是否為質數：是
```

> **使用時機**：三元運算子最適合**簡單的二選一**邏輯，使程式碼更緊湊。若條件複雜或有多行操作，仍建議使用 `if-else`，不要犧牲可讀性。

---

### 3.2.7 其他運算子補充

#### `sizeof` 運算子（第二章已介紹）

```cpp
sizeof(int)       // 4（bytes）
sizeof(double)    // 8（bytes）
sizeof(variable)  // 回傳變數所佔的 bytes
```

#### 逗號運算子（`,`）

逗號運算子按序計算兩個運算式，並回傳最右邊的值。主要用於 `for` 迴圈（後續章節介紹）。

```cpp
int x = (3 + 4, 10 * 2);  // x = 20（逗號左側的 3+4 被計算但捨棄）
```

#### 型別轉換運算子（第二章已介紹）

```cpp
static_cast<double>(5) / 2   // 2.5（推薦的 C++ 轉型方式）
(double)5 / 2                // 2.5（C 風格，不推薦）
```

---

### 3.2.8 運算子優先順序與結合律

當一個運算式中有多個運算子時，**優先順序（Precedence）**決定哪個先算，**結合律（Associativity）**決定相同優先順序時從哪個方向算。

**C++ 運算子優先順序表（由高到低）：**

| 優先序 | 運算子 | 說明 | 結合律 |
|--------|--------|------|--------|
| 1（最高） | `()` `[]` `->` `.` | 括號、下標、成員存取 | 左到右 |
| 2 | `++` `--`（後置）`sizeof` | 後置遞增遞減 | 左到右 |
| 3 | `++` `--`（前置）`~` `!` `-`（一元）`+`（一元）`(type)` `*` `&` | 前置運算子、位元NOT、邏輯NOT、解參考 | **右到左** |
| 4 | `*` `/` `%` | 乘除餘 | 左到右 |
| 5 | `+` `-` | 加減 | 左到右 |
| 6 | `<<` `>>` | 位元移位 | 左到右 |
| 7 | `<` `<=` `>` `>=` | 關係比較 | 左到右 |
| 8 | `==` `!=` | 相等比較 | 左到右 |
| 9 | `&` | 位元 AND | 左到右 |
| 10 | `^` | 位元 XOR | 左到右 |
| 11 | `\|` | 位元 OR | 左到右 |
| 12 | `&&` | 邏輯 AND | 左到右 |
| 13 | `\|\|` | 邏輯 OR | 左到右 |
| 14 | `?:` | 三元 | **右到左** |
| 15 | `=` `+=` `-=` 等 | 指定 | **右到左** |
| 16（最低） | `,` | 逗號 | 左到右 |

**範例檔：`ex3_2_precedence.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    // 乘除優先於加減
    cout << 2 + 3 * 4 << endl;       // 14，不是 20
    cout << (2 + 3) * 4 << endl;     // 20（括號改變優先序）

    // 混合算術與比較
    cout << (3 + 4 > 2 * 3) << endl; // true：先算 3+4=7, 2*3=6，再比較 7>6

    // 邏輯運算子的優先序：&& 高於 ||
    // A || B && C  等同於  A || (B && C)
    bool a = false, b = true, c = false;
    cout << (a || b && c) << endl;   // false：先算 b&&c=false，再 false||false
    cout << ((a || b) && c) << endl; // false：先算 a||b=true，再 true&&false

    // 位移與算術的組合
    int x = 3;
    cout << (x << 2 + 1) << endl;   // 96：先算 2+1=3，再 3<<3=24？
                                    // 不！+ 優先序 > <<，所以先算 2+1=3，3<<3=24
    // 等等，讓我們確認
    // << 的優先序（6）低於 + 的優先序（5）
    // 所以 x << (2+1) = 3 << 3 = 24
    cout << (x << (2 + 1)) << endl; // 24 ✅

    // 常見的優先序錯誤：位元運算與比較
    int flag = 5;
    // 錯誤：想要 (flag & 4) == 4
    // 但因為 == 優先序高於 &，實際變成 flag & (4 == 4) = 5 & 1 = 1
    // if (flag & 4 == 4)  ← 這是 bug！

    // 正確：加括號
    if ((flag & 4) == 4) {
        cout << "第 2 位被設定" << endl;  // ✅
    }

    // 指定運算子的右結合律
    int p, q, r;
    p = q = r = 42;  // 等同於 p = (q = (r = 42))
    cout << p << " " << q << " " << r << endl;  // 42 42 42

    return 0;
}
```

> **黃金法則**：**加括號比背優先序表更重要。** 即使你記得優先序，加括號可以讓程式碼的意圖一目瞭然，避免自己和他人讀錯。遇到位元運算子時，幾乎一定要加括號。

---

### 3.2.9 常見陷阱與最佳實踐

**範例檔：`ex3_2_pitfalls.cpp`**

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // 陷阱 1：= 和 == 混淆
    int x = 5;
    if (x = 10) {    // ❌ 這是指定，不是比較！x 被改成 10，條件永遠為 true
        cout << "x = " << x << endl;
    }
    // 防禦性寫法：把常數放左邊（Yoda Condition）
    // if (10 == x)  ← 若誤寫成 if (10 = x) 會編譯錯誤

    // 陷阱 2：整數除法
    int a = 5, b = 2;
    double result = a / b;   // ❌ result = 2.0，不是 2.5
    double correct = static_cast<double>(a) / b;  // ✅ 2.5
    cout << "整數除法錯誤：" << result << endl;
    cout << "正確結果：" << correct << endl;

    // 陷阱 3：浮點數精度
    double sum = 0.0;
    for (int i = 0; i < 10; i++) sum += 0.1;
    cout << (sum == 1.0) << endl;           // false！
    cout << fabs(sum - 1.0) < 1e-9 << endl; // true ✅

    // 陷阱 4：位元運算忘記加括號
    int flags = 0b0101;
    // if (flags & 0b0001 == 1)   ❌ 等同於 flags & (0b0001 == 1) = flags & 1
    if ((flags & 0b0001) == 1) {  // ✅ 加括號
        cout << "最低位是 1" << endl;
    }

    // 陷阱 5：有號整數溢位
    int big = 2147483647;
    // big++;  ❌ 未定義行為！
    long long safe = 2147483647LL;
    safe++;  // ✅
    cout << "安全加法：" << safe << endl;

    // 陷阱 6：++ 在複雜運算式中
    int c = 5;
    // int d = c++ + ++c;  ❌ 未定義行為！
    int c1 = 5;
    int step1 = c1++;   // step1 = 5, c1 = 6
    int step2 = ++c1;   // c1 = 7, step2 = 7
    int d = step1 + step2;   // ✅ 明確拆開
    cout << "d = " << d << endl;  // 12

    return 0;
}
```

---

### 3.2.10 綜合範例：運算綜合應用

**範例檔：`ex3_2_comprehensive.cpp`**

```cpp
#include <iostream>
#include <iomanip>
#include <cmath>
#include <bitset>
using namespace std;

int main() {
    cout << "=== 一元二次方程式求根 ===" << endl;
    // ax^2 + bx + c = 0
    double a = 1, b = -5, c = 6;
    double discriminant = b * b - 4 * a * c;  // 判別式

    if (discriminant > 0) {
        double x1 = (-b + sqrt(discriminant)) / (2 * a);
        double x2 = (-b - sqrt(discriminant)) / (2 * a);
        cout << fixed << setprecision(4);
        cout << "兩個實根：x1=" << x1 << ", x2=" << x2 << endl;
    } else if (discriminant == 0) {
        double x = -b / (2 * a);
        cout << "唯一實根：x=" << x << endl;
    } else {
        cout << "無實根（判別式 < 0）" << endl;
    }

    cout << "\n=== 位元技巧：判斷奇偶 ===" << endl;
    for (int n = 0; n <= 9; n++) {
        // n & 1：最低位是 1 就是奇數，是 0 就是偶數
        cout << n << " 是" << ((n & 1) ? "奇" : "偶") << "數  ";
    }
    cout << endl;

    cout << "\n=== 位元技巧：計算 2 的次方 ===" << endl;
    for (int k = 0; k <= 10; k++) {
        cout << "2^" << k << " = " << (1 << k) << endl;
    }

    cout << "\n=== 三元運算子：成績分析 ===" << endl;
    int scores[] = {95, 83, 67, 55, 71};
    string names[] = {"Alice", "Bob", "Charlie", "Diana", "Eve"};
    for (int i = 0; i < 5; i++) {
        string grade = (scores[i] >= 90) ? "A" :
                       (scores[i] >= 80) ? "B" :
                       (scores[i] >= 70) ? "C" :
                       (scores[i] >= 60) ? "D" : "F";
        cout << left << setw(8) << names[i]
             << "：" << scores[i] << " 分（" << grade << "）"
             << (scores[i] >= 60 ? " ✓" : " ✗") << endl;
    }

    return 0;
}
```

**輸出結果：**
```
=== 一元二次方程式求根 ===
兩個實根：x1=3.0000, x2=2.0000

=== 位元技巧：判斷奇偶 ===
0 是偶數  1 是奇數  2 是偶數  3 是奇數  4 是偶數
5 是奇數  6 是偶數  7 是奇數  8 是偶數  9 是奇數

=== 位元技巧：計算 2 的次方 ===
2^0 = 1
2^1 = 2
...
2^10 = 1024

=== 三元運算子：成績分析 ===
Alice   ：95 分（A） ✓
Bob     ：83 分（B） ✓
Charlie ：67 分（D） ✓
Diana   ：55 分（F） ✗
Eve     ：71 分（C） ✓
```

---

## 📝 實作練習

### 基礎題

#### 練習 3-1：四則運算計算機

**題目：** 輸入兩個整數 a 和 b（b ≠ 0），輸出它們的加、減、乘、整數除、浮點除、取餘數的結果。

**輸入範例：**
```
請輸入兩個整數：17 5
```

**輸出範例：**
```
a = 17, b = 5
a + b = 22
a - b = 12
a * b = 85
a / b = 3 (整數除法)
a / b = 3.4000 (浮點除法)
a % b = 2
```

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw3_1.cpp`**

```cpp
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int a, b;
    cout << "請輸入兩個整數：";
    cin >> a >> b;

    cout << fixed << setprecision(4);
    cout << "a = " << a << ", b = " << b << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "a / b = " << a / b << " (整數除法)" << endl;
    cout << "a / b = " << static_cast<double>(a) / b << " (浮點除法)" << endl;
    cout << "a % b = " << a % b << endl;

    return 0;
}
```
</details>

---

#### 練習 3-2：奇偶判斷與位元顯示

**題目：** 輸入一個 0～255 之間的整數，判斷其奇偶，並以二進位和十六進位顯示。

**輸入範例：**
```
請輸入整數（0~255）：42
```

**輸出範例：**
```
十進位：42
二進位：00101010
十六進位：2a
奇偶：偶數
最低位（bit 0）：0
最高位（bit 7）：0
```

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw3_2.cpp`**

```cpp
#include <iostream>
#include <iomanip>
#include <bitset>
using namespace std;

int main() {
    int n;
    cout << "請輸入整數（0~255）：";
    cin >> n;

    cout << "十進位：" << n << endl;
    cout << "二進位：" << bitset<8>(n) << endl;
    cout << "十六進位：" << hex << n << dec << endl;
    cout << "奇偶：" << ((n & 1) ? "奇數" : "偶數") << endl;
    cout << "最低位（bit 0）：" << (n & 1) << endl;
    cout << "最高位（bit 7）：" << ((n >> 7) & 1) << endl;

    return 0;
}
```
</details>

---

#### 練習 3-3：BMI 計算（含三元運算子）

**題目：** 輸入體重（公斤）和身高（公分），計算 BMI，使用三元運算子判斷健康狀態。
- BMI < 18.5：偏瘦
- 18.5 ≤ BMI < 24：正常
- 24 ≤ BMI < 27：過重
- BMI ≥ 27：肥胖

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw3_3.cpp`**

```cpp
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    double weight, height;
    cout << "請輸入體重（公斤）：";
    cin >> weight;
    cout << "請輸入身高（公分）：";
    cin >> height;

    double h = height / 100.0;
    double bmi = weight / (h * h);

    string status = (bmi < 18.5) ? "偏瘦" :
                    (bmi < 24.0) ? "正常" :
                    (bmi < 27.0) ? "過重" : "肥胖";

    cout << fixed << setprecision(2);
    cout << "BMI = " << bmi << endl;
    cout << "狀態：" << status << endl;

    return 0;
}
```
</details>

---

#### 練習 3-4：複合指定練習

**題目：** 從 1000 元出發，按下列步驟操作，每步都用複合指定運算子，並印出每步的結果：
1. 加上 500
2. 乘以 2
3. 減去 300
4. 除以 3（整數除法）
5. 取 7 的餘數

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw3_4.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int money = 1000;
    cout << "初始：" << money << endl;

    money += 500;
    cout << "加 500 後：" << money << endl;    // 1500

    money *= 2;
    cout << "乘以 2 後：" << money << endl;    // 3000

    money -= 300;
    cout << "減 300 後：" << money << endl;    // 2700

    money /= 3;
    cout << "除以 3 後：" << money << endl;    // 900

    money %= 7;
    cout << "取 7 的餘後：" << money << endl;  // 900 % 7 = 5

    return 0;
}
```
</details>

---

#### 練習 3-5：遞增遞減追蹤

**題目：** 看以下程式碼，在不執行的情況下，預測每行的輸出值。執行後驗證自己的答案。

```cpp
#include <iostream>
using namespace std;
int main() {
    int a = 5;
    cout << a++ << endl;   // (1)
    cout << a   << endl;   // (2)
    cout << ++a << endl;   // (3)
    cout << a   << endl;   // (4)
    int b = a--;
    cout << b   << endl;   // (5)
    cout << a   << endl;   // (6)
    int c = --a;
    cout << c   << endl;   // (7)
    cout << a   << endl;   // (8)
    return 0;
}
```

<details>
<summary>✅ 參考答案（點擊展開）</summary>

```
(1) 5    → a++ 先輸出 a 的舊值 5，再讓 a 變 6
(2) 6    → a 現在是 6
(3) 7    → ++a 先讓 a 變 7，再輸出 7
(4) 7    → a 仍是 7
(5) 7    → b = a-- 先讓 b = a 的舊值 7，再讓 a 變 6
(6) 6    → a 現在是 6
(7) 5    → c = --a 先讓 a 變 5，再讓 c = 5
(8) 5    → a 現在是 5
```
</details>

---

### 進階題

#### 練習 3-6：RGB 顏色拆解

**題目：** 網頁顏色通常以 24 位元整數表示（如 `0xFF5733`，前 8 位是紅、中 8 位是綠、後 8 位是藍）。輸入一個十六進位顏色值，拆解出 R、G、B 各分量，並輸出各分量的十進位值和二進位。

**輸入範例：**
```
請輸入 RGB 色碼（十六進位，如 FF5733）：FF5733
```

**輸出範例：**
```
色碼：#FF5733
R = 255 (11111111)
G =  87 (01010111)
B =  51 (00110011)
```

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw3_6.cpp`**

```cpp
#include <iostream>
#include <iomanip>
#include <bitset>
using namespace std;

int main() {
    int color;
    cout << "請輸入 RGB 色碼（十六進位，如 FF5733）：";
    cin >> hex >> color;

    int r = (color >> 16) & 0xFF;   // 取高 8 位
    int g = (color >>  8) & 0xFF;   // 取中 8 位
    int b = (color >>  0) & 0xFF;   // 取低 8 位

    cout << "色碼：#" << uppercase << hex << setfill('0') << setw(6) << color << endl;
    cout << dec;
    cout << "R = " << setw(3) << r << " (" << bitset<8>(r) << ")" << endl;
    cout << "G = " << setw(3) << g << " (" << bitset<8>(g) << ")" << endl;
    cout << "B = " << setw(3) << b << " (" << bitset<8>(b) << ")" << endl;

    return 0;
}
```
</details>

---

#### 練習 3-7：不用暫存變數交換兩數

**題目：** 用 XOR 位元運算，不使用第三個暫存變數，交換兩個整數 a 和 b 的值。驗證交換前後的結果。

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw3_7.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b;
    cout << "請輸入兩個整數：";
    cin >> a >> b;

    cout << "交換前：a=" << a << ", b=" << b << endl;

    // XOR 交換法（不需要暫存變數）
    a ^= b;
    b ^= a;
    a ^= b;

    cout << "交換後：a=" << a << ", b=" << b << endl;

    // 驗證：也可用算術法（加減法）
    int x = 100, y = 200;
    x = x + y;  // x = 300
    y = x - y;  // y = 100 (原本的 x)
    x = x - y;  // x = 200 (原本的 y)
    cout << "算術法交換：x=" << x << ", y=" << y << endl;

    return 0;
}
```
</details>

---

#### 練習 3-8：位元旗標設計

**題目：** 設計一個簡單的學生狀態系統，用一個 `int` 的不同位元表示學生的各種狀態。實作「設定」、「清除」、「查詢」、「切換」四種操作。

狀態定義：
- Bit 0：是否在學（1=在學，0=休學）
- Bit 1：是否有獎學金
- Bit 2：是否為交換生
- Bit 3：是否為研究生

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw3_8.cpp`**

```cpp
#include <iostream>
#include <bitset>
using namespace std;

const int STATUS_ENROLLED    = 1 << 0;  // 1
const int STATUS_SCHOLARSHIP = 1 << 1;  // 2
const int STATUS_EXCHANGE    = 1 << 2;  // 4
const int STATUS_GRADUATE    = 1 << 3;  // 8

void setFlag(int& status, int flag) {
    status |= flag;
}

void clearFlag(int& status, int flag) {
    status &= ~flag;
}

bool hasFlag(int status, int flag) {
    return (status & flag) != 0;
}

void toggleFlag(int& status, int flag) {
    status ^= flag;
}

void printStatus(int status) {
    cout << "學生狀態 [" << bitset<4>(status) << "]" << endl;
    cout << "  在學中：" << (hasFlag(status, STATUS_ENROLLED)    ? "是" : "否") << endl;
    cout << "  有獎學金：" << (hasFlag(status, STATUS_SCHOLARSHIP) ? "是" : "否") << endl;
    cout << "  交換生：" << (hasFlag(status, STATUS_EXCHANGE)    ? "是" : "否") << endl;
    cout << "  研究生：" << (hasFlag(status, STATUS_GRADUATE)    ? "是" : "否") << endl;
}

int main() {
    int studentStatus = 0;

    cout << "=== 初始狀態 ===" << endl;
    printStatus(studentStatus);

    cout << "\n=== 設定「在學」和「獎學金」 ===" << endl;
    setFlag(studentStatus, STATUS_ENROLLED | STATUS_SCHOLARSHIP);
    printStatus(studentStatus);

    cout << "\n=== 清除「獎學金」 ===" << endl;
    clearFlag(studentStatus, STATUS_SCHOLARSHIP);
    printStatus(studentStatus);

    cout << "\n=== 切換「在學」狀態 ===" << endl;
    toggleFlag(studentStatus, STATUS_ENROLLED);
    printStatus(studentStatus);

    return 0;
}
```
</details>

---

#### 練習 3-9：完整四位數分解

**題目：** 輸入一個四位數整數（1000-9999），用算術運算子分解出千位、百位、十位、個位數字，並計算各位數字之和、判斷是否為對稱數（迴文數）。

**輸入範例：**
```
請輸入四位數：1221
```

**輸出範例：**
```
千位：1
百位：2
十位：2
個位：1
各位數字和：6
是否為對稱數：是
```

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw3_9.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "請輸入四位數：";
    cin >> n;

    int thousands = n / 1000;
    int hundreds  = (n / 100) % 10;
    int tens      = (n / 10)  % 10;
    int ones      = n % 10;

    cout << "千位：" << thousands << endl;
    cout << "百位：" << hundreds  << endl;
    cout << "十位：" << tens      << endl;
    cout << "個位：" << ones      << endl;
    cout << "各位數字和：" << (thousands + hundreds + tens + ones) << endl;

    bool isPalindrome = (thousands == ones) && (hundreds == tens);
    cout << "是否為對稱數：" << (isPalindrome ? "是" : "否") << endl;

    return 0;
}
```
</details>

---

#### 練習 3-10：運算式求值追蹤

**題目：** 不執行程式，分析以下各個運算式的值，說明你的推理過程，然後撰寫程式驗證。

```
(1) 2 + 3 * 4 - 1
(2) 10 / 3 * 3 + 10 % 3
(3) true && false || true
(4) !true || (3 > 2 && 5 != 5)
(5) 5 & 3 | 6
(6) 1 << 3 + 1
(7) (int)3.7 + (int)(-3.7)
(8) 5 > 3 ? 2 * 3 : 10 - 4
```

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**推理過程：**

```
(1) 2 + 3 * 4 - 1
    = 2 + 12 - 1   (* 優先)
    = 14 - 1
    = 13

(2) 10 / 3 * 3 + 10 % 3
    = 3 * 3 + 1    (整數除法 10/3=3，左至右，10%3=1)
    = 9 + 1
    = 10

(3) true && false || true
    = false || true   (&& 優先於 ||)
    = true

(4) !true || (3 > 2 && 5 != 5)
    = false || (true && false)
    = false || false
    = false

(5) 5 & 3 | 6
    = (5 & 3) | 6  (& 優先於 |)
    = 1 | 6        (0101 & 0011 = 0001)
    = 7            (0001 | 0110 = 0111)

(6) 1 << 3 + 1
    = 1 << 4       (+ 優先於 <<)
    = 16

(7) (int)3.7 + (int)(-3.7)
    = 3 + (-3)     (截斷向零)
    = 0

(8) 5 > 3 ? 2 * 3 : 10 - 4
    = true ? 6 : 6
    = 6
```

**檔名：`hw3_10.cpp`**

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << boolalpha;
    cout << "(1) " << (2 + 3 * 4 - 1)                          << endl;  // 13
    cout << "(2) " << (10 / 3 * 3 + 10 % 3)                    << endl;  // 10
    cout << "(3) " << (true && false || true)                   << endl;  // true
    cout << "(4) " << (!true || (3 > 2 && 5 != 5))              << endl;  // false
    cout << "(5) " << (5 & 3 | 6)                               << endl;  // 7
    cout << "(6) " << (1 << 3 + 1)                              << endl;  // 16
    cout << "(7) " << ((int)3.7 + (int)(-3.7))                  << endl;  // 0
    cout << "(8) " << (5 > 3 ? 2 * 3 : 10 - 4)                 << endl;  // 6
    return 0;
}
```
</details>

---

#### 練習 3-11：密碼強度檢查

**題目：** 輸入一個密碼，用邏輯運算子組合條件，檢查以下規則：
- 長度至少 8 個字元
- 包含至少一個數字（提示：用 `isdigit()`）
- 包含至少一個大寫字母（提示：用 `isupper()`）
- 包含至少一個小寫字母（提示：用 `islower()`）
- 包含至少一個特殊字元（非字母數字）

根據滿足的條件數量，評定強度：0-2 條：弱、3-4 條：中等、5 條全滿足：強。

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw3_11.cpp`**

```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string password;
    cout << "請輸入密碼：";
    cin >> password;

    bool hasLength  = (password.length() >= 8);
    bool hasDigit   = false;
    bool hasUpper   = false;
    bool hasLower   = false;
    bool hasSpecial = false;

    for (char c : password) {
        if (isdigit(c))  hasDigit   = true;
        if (isupper(c))  hasUpper   = true;
        if (islower(c))  hasLower   = true;
        if (!isalnum(c)) hasSpecial = true;
    }

    int score = hasLength + hasDigit + hasUpper + hasLower + hasSpecial;

    cout << "\n=== 密碼強度分析 ===" << endl;
    cout << "長度 ≥ 8：" << (hasLength  ? "✓" : "✗") << endl;
    cout << "含數字："   << (hasDigit   ? "✓" : "✗") << endl;
    cout << "含大寫："   << (hasUpper   ? "✓" : "✗") << endl;
    cout << "含小寫："   << (hasLower   ? "✓" : "✗") << endl;
    cout << "含特殊字元：" << (hasSpecial ? "✓" : "✗") << endl;
    cout << "滿足條件：" << score << "/5" << endl;

    string strength = (score <= 2) ? "弱" :
                      (score <= 4) ? "中等" : "強";
    cout << "密碼強度：" << strength << endl;

    return 0;
}
```
</details>

---

### 挑戰題

#### 練習 3-12：格雷碼（Gray Code）轉換

**題目：** 格雷碼是一種二進位編碼，相鄰的兩個數字只有一個位元不同（常用於旋轉編碼器）。實作：
- 二進位 → 格雷碼：`gray = n ^ (n >> 1)`
- 格雷碼 → 二進位（自行研究演算法）

輸出 0～15 的二進位、格雷碼對照表。

<details>
<summary>✅ 參考答案（點擊展開）</summary>

**檔名：`hw3_12.cpp`**

```cpp
#include <iostream>
#include <iomanip>
#include <bitset>
using namespace std;

int binaryToGray(int n) {
    return n ^ (n >> 1);
}

int grayToBinary(int gray) {
    int binary = 0;
    for (; gray; gray >>= 1)
        binary ^= gray;
    return binary;
}

int main() {
    cout << left << setw(6) << "十進位"
         << setw(10) << "二進位"
         << setw(10) << "格雷碼"
         << "格雷→二進位驗證" << endl;
    cout << string(42, '-') << endl;

    for (int n = 0; n <= 15; n++) {
        int gray = binaryToGray(n);
        int back = grayToBinary(gray);
        cout << setw(6)  << n
             << setw(10) << bitset<4>(n)
             << setw(10) << bitset<4>(gray)
             << bitset<4>(back) << endl;
    }

    return 0;
}
```
</details>

---

## 💼 面試考題

### 觀念題

**Q1. 前置遞增 `++i` 和後置遞增 `i++` 有什麼差異？在實作類別時，為何前置效率通常更好？**

> **參考答案：**
>
> **行為差異：**
> - `++i`（前置）：先將 i 加 1，然後回傳加後的值
> - `i++`（後置）：先儲存 i 的舊值，將 i 加 1，然後回傳舊值
>
> **效率差異：**
> - 對基本型別（`int`, `double`）：編譯器通常會最佳化，差異不大
> - 對**自定義類別**（如 STL 疊代器）：後置需要製作一份物件的副本來儲存舊值（呼叫複製建構子），前置只需修改物件本身並回傳參考，因此**前置效率更高**
>
> **建議**：若不需要舊值，一律用前置遞增 `++i`，是良好的編碼習慣。

---

**Q2. 解釋短路求值（Short-circuit Evaluation），並給出一個因短路求值避免了 bug 的例子。**

> **參考答案：**
>
> 短路求值：
> - `A && B`：若 A 為 false，B 不會被執行（整體已確定為 false）
> - `A || B`：若 A 為 true，B 不會被執行（整體已確定為 true）
>
> 避免 bug 的例子：
> ```cpp
> int* ptr = nullptr;
> if (ptr != nullptr && ptr->value > 0) { ... }
> // 若 ptr 為 nullptr，因短路求值，ptr->value 不會被存取，避免了空指標解參考的崩潰
> ```
>
> ```cpp
> int divisor = 0;
> if (divisor != 0 && 100 / divisor > 2) { ... }
> // 若 divisor 為 0，因短路求值，100/divisor 不會被執行，避免了除以零錯誤
> ```

---

**Q3. 以下程式的輸出為何？**

```cpp
int x = 5;
int y = x++ + ++x;
cout << x << " " << y << endl;
```

> **參考答案：**
>
> 這是**未定義行為（Undefined Behavior）**！在同一個運算式中對同一變數進行多次修改，C++ 標準未規定求值順序，不同編譯器可能產生不同結果。
>
> 在面試中，正確答案是「這是 UB，不應該這樣寫」，而不是猜測某個特定值。
>
> 正確寫法應拆開：
> ```cpp
> int x = 5;
> int a = x++;   // a = 5, x = 6
> int b = ++x;   // x = 7, b = 7
> int y = a + b; // y = 12
> ```

---

**Q4. 整數溢位（Integer Overflow）是什麼？有哪些預防方式？**

> **參考答案：**
>
> 整數溢位是指整數運算的結果超出了該型別的表示範圍，對於有號整數（`int`, `long long`）是**未定義行為**，對無號整數則是「迴繞（wrapping）」行為。
>
> **預防方式：**
> 1. 計算前先判斷是否可能超界：
>    ```cpp
>    if (a > INT_MAX - b) { /* 會溢位 */ }
>    ```
> 2. 使用更大的型別：
>    ```cpp
>    long long result = (long long)a * b;
>    ```
> 3. 使用 `__int128`（GCC 擴充）或高精度函式庫
> 4. 使用 `-fsanitize=undefined`（AddressSanitizer）偵測

---

**Q5. 為什麼不能直接用 `==` 比較兩個 `double`？應該怎麼做？**

> **參考答案：**
>
> 浮點數在電腦中以 IEEE 754 二進位表示，無法精確表示所有十進位小數。例如 `0.1` 在二進位是無限循環小數，儲存時產生微小誤差，導致 `0.1 + 0.2 != 0.3`（實際上相差約 `5.5e-17`）。
>
> 正確做法：比較差值是否在允許誤差範圍內：
> ```cpp
> bool almostEqual(double a, double b, double epsilon = 1e-9) {
>     return fabs(a - b) < epsilon;
> }
> ```
> epsilon 的選取取決於問題的精度需求，通常是 `1e-9`（相對誤差較小時）。

---

**Q6. 以下程式輸出什麼？為什麼？**

```cpp
cout << (3 > 2 > 1) << endl;
cout << (1 < 2 < 3) << endl;
cout << (3 > 2 && 2 > 1) << endl;
```

> **參考答案：**
>
> ```
> 0    ← false
> 1    ← true
> 1    ← true
> ```
>
> - `3 > 2 > 1`：先算 `3 > 2` = `true`（值為 1），再算 `1 > 1` = `false`（值為 0）。這是 C++ 不支援「數學上的連續比較」的陷阱。
> - `1 < 2 < 3`：先算 `1 < 2` = `true`（值為 1），再算 `1 < 3` = `true`（值為 1）。恰好正確，但原因不是「連續比較」！
> - `3 > 2 && 2 > 1`：邏輯 AND 連接兩個比較，正確的寫法。
>
> **結論**：C++ 不支援連續比較（不像 Python），要比較 `1 < x < 10` 應寫成 `x > 1 && x < 10`。

---

**Q7. 位元運算 `n & (n-1)` 有什麼意義？**

> **參考答案：**
>
> `n & (n-1)` 的效果是**清除 n 的最低的那個 1 位元**。
>
> 例如：`n = 12`（`1100`），`n-1 = 11`（`1011`），`12 & 11 = 8`（`1000`）—— 最低的 `1`（在第 2 位）被清除了。
>
> **常見應用**：快速判斷 n 是否為 2 的次方：
> ```cpp
> bool isPowerOfTwo(int n) {
>     return n > 0 && (n & (n - 1)) == 0;
> }
> // 2 的次方的二進位只有一個 1，清除後變 0
> ```
>
> 也可用於計算整數中有幾個 1（Kernighan 演算法）：
> ```cpp
> int countBits(int n) {
>     int count = 0;
>     while (n) { n &= (n - 1); count++; }
>     return count;
> }
> ```

---

**Q8. 解釋「2 的補數（Two's Complement）」，以及為何 `~n == -(n+1)`。**

> **參考答案：**
>
> 現代電腦用 **2 的補數**表示有號整數。正數的補數就是本身，負數 `-n` 以 `(2^位元數 - n)` 表示。
>
> 例如（8 位元）：
> - `5` = `00000101`
> - `-5` = `11111011`（把 `5` 所有位元取反，再加 1）
>
> 因此 `~n`（位元取反）= `-(n+1)`：
> - `~5` = `11111010`（取反） = `-6`（= -(5+1)）
>
> 這解釋了為什麼 `~0 = -1`，`~(-1) = 0`，以及 `~n + n + 1 = 0`。

---

## 🚀 專案：簡易進制轉換工具

### 專案說明

開發一個進制轉換計算機，讓使用者輸入一個十進位整數，輸出其：
1. 二進位（Binary）表示
2. 八進位（Octal）表示
3. 十六進位（Hexadecimal）表示
4. 各位元的狀態（位元圖）
5. 進行指定的位元操作

### 功能需求

1. 接受 0～65535（16 位元無號整數範圍）的輸入
2. 顯示四種進位制
3. 顯示 16 位元的位元圖，每 4 位用空格分隔
4. 互動式選單：
   - 設定第 n 個位元
   - 清除第 n 個位元
   - 切換第 n 個位元
   - 左移 n 位
   - 右移 n 位
   - 與另一數進行 AND / OR / XOR
5. 每次操作後更新顯示

### 輸出範例

```
╔═══════════════════════════════════╗
║        進制轉換工具               ║
╚═══════════════════════════════════╝

請輸入整數（0~65535）：42

╔═══════════════════════════════════╗
║  當前值：42                       ║
╠═══════════════════════════════════╣
║  十進位：42                       ║
║  二進位：0000 0000 0010 1010       ║
║  八進位：52                       ║
║  十六進位：2a                     ║
╠═══════════════════════════════════╣
║  位元圖（bit 15 → bit 0）         ║
║  0000 0000 0010 1010               ║
╚═══════════════════════════════════╝

操作選單：
[1] 設定位元  [2] 清除位元  [3] 切換位元
[4] 左移      [5] 右移      [6] AND
[7] OR        [8] XOR       [0] 結束
請選擇操作：
```

<details>
<summary>✅ 完整參考答案（點擊展開）</summary>

**檔名：`project3_bittools.cpp`**

```cpp
#include <iostream>
#include <iomanip>
#include <bitset>
#include <string>
using namespace std;

void displayValue(int val) {
    // 格式化 16 位元位元圖（每 4 位加空格）
    string bits = bitset<16>(val).to_string();
    string formatted = bits.substr(0, 4) + " " + bits.substr(4, 4) + " "
                     + bits.substr(8, 4) + " " + bits.substr(12, 4);

    cout << "╔═══════════════════════════════════╗" << endl;
    cout << "║  當前值：" << left << setw(25) << val << "║" << endl;
    cout << "╠═══════════════════════════════════╣" << endl;
    cout << "║  十進位：" << left << setw(25) << dec << val << "║" << endl;
    cout << "║  二進位：" << left << setw(25) << formatted << "║" << endl;
    cout << "║  八進位：" << left << setw(25) << oct << val << "║" << endl;
    cout << "║  十六進位：" << left << setw(23) << hex << val << "║" << endl;
    cout << "╠═══════════════════════════════════╣" << endl;
    cout << "║  位元圖（bit 15 → bit 0）         ║" << endl;
    cout << "║  " << left << setw(33) << formatted << "║" << endl;
    cout << "╚═══════════════════════════════════╝" << endl;
    cout << dec;  // 恢復十進位
}

void showMenu() {
    cout << "\n操作選單：" << endl;
    cout << "[1] 設定位元  [2] 清除位元  [3] 切換位元" << endl;
    cout << "[4] 左移      [5] 右移      [6] AND" << endl;
    cout << "[7] OR        [8] XOR       [0] 結束" << endl;
    cout << "請選擇操作：";
}

int main() {
    cout << "╔═══════════════════════════════════╗" << endl;
    cout << "║        進制轉換工具               ║" << endl;
    cout << "╚═══════════════════════════════════╝" << endl;

    int value;
    cout << "\n請輸入整數（0~65535）：";
    cin >> value;
    value &= 0xFFFF;  // 限制在 16 位元範圍

    int choice;
    do {
        cout << endl;
        displayValue(value);
        showMenu();
        cin >> choice;

        int n, other;
        switch (choice) {
            case 1:
                cout << "要設定第幾個位元（0~15）：";
                cin >> n;
                if (n >= 0 && n <= 15) {
                    value |= (1 << n);
                    cout << "已設定第 " << n << " 個位元" << endl;
                }
                break;

            case 2:
                cout << "要清除第幾個位元（0~15）：";
                cin >> n;
                if (n >= 0 && n <= 15) {
                    value &= ~(1 << n);
                    cout << "已清除第 " << n << " 個位元" << endl;
                }
                break;

            case 3:
                cout << "要切換第幾個位元（0~15）：";
                cin >> n;
                if (n >= 0 && n <= 15) {
                    value ^= (1 << n);
                    cout << "已切換第 " << n << " 個位元" << endl;
                }
                break;

            case 4:
                cout << "左移幾位（1~15）：";
                cin >> n;
                if (n >= 1 && n <= 15) {
                    value = (value << n) & 0xFFFF;
                    cout << "已左移 " << n << " 位" << endl;
                }
                break;

            case 5:
                cout << "右移幾位（1~15）：";
                cin >> n;
                if (n >= 1 && n <= 15) {
                    value = (value >> n) & 0xFFFF;
                    cout << "已右移 " << n << " 位" << endl;
                }
                break;

            case 6:
                cout << "請輸入 AND 的運算元：";
                cin >> other;
                value = (value & other) & 0xFFFF;
                cout << "AND " << other << " 完成" << endl;
                break;

            case 7:
                cout << "請輸入 OR 的運算元：";
                cin >> other;
                value = (value | other) & 0xFFFF;
                cout << "OR " << other << " 完成" << endl;
                break;

            case 8:
                cout << "請輸入 XOR 的運算元：";
                cin >> other;
                value = (value ^ other) & 0xFFFF;
                cout << "XOR " << other << " 完成" << endl;
                break;

            case 0:
                cout << "程式結束。" << endl;
                break;

            default:
                cout << "無效選項，請重新輸入。" << endl;
        }
    } while (choice != 0);

    return 0;
}
```
</details>

---

## 🔑 章節重點整理

```
┌─────────────────────────────────────────────────────┐
│                  第三章重點摘要                      │
├─────────────────────────────────────────────────────┤
│ 3.1 指定運算子                                      │
│  • = 是從右到左的指定，不是比較                     │
│  • a = b = c = 0 是合法的連鎖指定                   │
│  • += -= *= /= %= 是複合指定的簡寫                  │
│  • 位元複合指定：&= |= ^= <<= >>=                   │
├─────────────────────────────────────────────────────┤
│ 3.2.1 算術運算子                                    │
│  • 整數除法截斷小數（向零截斷）                     │
│  • % 符號跟隨被除數                                 │
│  • 至少一個浮點數才會做浮點除法                     │
│  • 大數計算注意溢位，改用 long long                 │
├─────────────────────────────────────────────────────┤
│ 3.2.2 遞增遞減                                      │
│  • 前置（++i）先改後用；後置（i++）先用後改        │
│  • 同一運算式多次 ++ 是未定義行為                   │
│  • 對物件優先用前置，效率較高                       │
├─────────────────────────────────────────────────────┤
│ 3.2.3-3.2.4 關係與邏輯                              │
│  • == 容易誤寫成 =，造成 bug                        │
│  • 浮點數用誤差比較，不用 ==                        │
│  • && || 有短路求值，可防止 nullptr 和除零          │
│  • && 優先序高於 ||                                 │
├─────────────────────────────────────────────────────┤
│ 3.2.5 位元運算子                                    │
│  & AND：提取/遮罩特定位元                           │
│  | OR ：設定特定位元                                │
│  ^ XOR：切換位元、不用暫存變數交換                  │
│  ~ NOT：所有位元取反（~n = -(n+1)）                │
│  <<   ：左移 n 位 = ×2^n（快速乘法）               │
│  >>   ：右移 n 位 = ÷2^n（快速整除）               │
│  位元運算一定要加括號！                              │
├─────────────────────────────────────────────────────┤
│ 3.2.6 三元運算子                                    │
│  • 條件 ? 值A : 值B（簡潔的 if-else）              │
│  • 適合簡單二選一；複雜邏輯用 if-else               │
├─────────────────────────────────────────────────────┤
│ 3.2.8 優先序原則                                    │
│  單目 > 乘除模 > 加減 > 移位 > 關係 >              │
│  相等 > 位元AND > XOR > 位元OR > 邏輯AND >         │
│  邏輯OR > 三元 > 指定 > 逗號                       │
│  加括號比背表更重要！                               │
└─────────────────────────────────────────────────────┘
```

---

*教材版本：v1.0 | 適用對象：大學程式設計初學者 | 建議學習時間：6-8 小時*
