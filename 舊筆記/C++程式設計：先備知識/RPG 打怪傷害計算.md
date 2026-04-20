## 範例：RPG 打怪傷害計算

**需求說明：**

- 玩家輸入角色的攻擊力
- 傷害計算公式：傷害值 = 攻擊力 × 2 − 怪物防禦力（預設為 15）
- 輸出對怪物的傷害值

**先用數學公式思考：**

```
假設攻擊力 = x
傷害值 = x × 2 - 15
```

**轉換成 C++ 程式碼：**

```cpp
// cpp
#include <iostream>
using namespace std;

int main(){
    int x;  // 宣告變數 x：用來儲存玩家輸入的攻擊力
    cout << "輸入攻擊力：";
    cin >> x;  // 接受使用者的輸入
    cout << "對怪物的傷害值為：" << x * 2 - 15 << endl;
    return 0;
}
```

## 範例：加入怪物防禦力的輸入

讓程式更靈活，讓玩家也能輸入怪物的防禦力：

```cpp
#include <iostream>
using namespace std;

int main(){
    int attack;   // 儲存玩家輸入的攻擊力
    int defence;  // 儲存怪物的防禦力
    cout << "輸入角色攻擊力：";
    cin >> attack;
    cout << "輸入怪物防禦力：";
    cin >> defence;
    cout << "對怪物的傷害值為：" << attack * 3 - defence * 2 << endl;
    return 0;
}
```
