### scanf 格式語法

```
scanf("格式化字串", &變數1, &變數2, ...);

格式化字串中的控制格式：
% [width] [length] type
  ↑
 必要
```

### width：限制最大讀取字元數

```c
int code;
scanf("%4d", &code);   /* 最多只讀取 4 個字元 */
/* 若輸入 12345，只讀取 1234，剩下的 5 留在緩衝區 */
```

### length 修飾符

| 修飾符        | 對應型別         | 範例         |
| ------------- | ---------------- | ------------ |
| `h`           | `short`          | `%hd`        |
| `l`（小寫 L） | `long`、`double` | `%ld`、`%lf` |
| `ll`          | `long long`      | `%lld`       |

### 完整 scanf 示範

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int   iAge;
    short sId1, sId2;
    float fWeight;
    char  cGender;
    int   iCode;

    /* 讀取字元 */
    printf("輸入性別代碼（M:男，F:女）：");
    scanf(" %c", &cGender);    /* %c 前有空格，跳過殘留換行（詳見第 6 節）*/
    printf("輸入的是：%c\n", cGender);

    /* 讀取整數 */
    printf("輸入年齡：");
    scanf("%d", &iAge);
    printf("輸入的是：%d\n", iAge);

    /* 讀取浮點數（float 用 %f）*/
    printf("輸入體重（含小數）：");
    scanf("%f", &fWeight);
    printf("輸入的是：%.1f\n", fWeight);

    /* 讀取兩個 short 整數（用 %hd）*/
    printf("輸入兩個整數代碼（空格隔開）：");
    scanf("%hd %hd", &sId1, &sId2);
    printf("輸入的兩個數字：%d %d\n", sId1, sId2);

    /* 限制最大輸入字元數（%4d 只讀 4 位）*/
    printf("輸入身份證後四碼（多輸無效）：");
    scanf("%4d", &iCode);
    printf("讀到的四碼是：%d\n", iCode);

    system("pause");
    return 0;
}
```

### 多筆資料輸入

```c
/* Prog3-7.c：多筆資料輸入的各種分隔方式 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int ia, ib;
    float fx, fy;

    /* 方式一：空格或換行分隔（最自然）*/
    printf("輸入兩個整數（空格或換行分隔）：");
    scanf("%d %d", &ia, &ib);
    printf("讀到：%d 和 %d\n", ia, ib);

    /* 方式二：逗號分隔（格式字串中的逗號是字面匹配）*/
    printf("輸入兩個整數（逗號隔開，如 85,52）：");
    scanf("%d,%d", &ia, &ib);
    printf("讀到：%d 和 %d\n", ia, ib);

    /* 方式三：讀取整數和浮點數 */
    printf("輸入整數和浮點數（如 10 3.14）：");
    scanf("%d %f", &ia, &fx);
    printf("整數 %d，浮點數 %.2f\n", ia, fx);

    system("pause");
    return 0;
}
```

### 進位數值的輸入

```c
/* Prog3-9.c：十六進位與八進位的輸入 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int iHex, iOct;

    /* %x 接受十六進位輸入（可帶或不帶 0x 前綴）*/
    printf("輸入一個十六進位數字（如 fa 或 0xfa）：");
    scanf("%x", &iHex);
    printf("%x（16 進位）= %d（10 進位）= %o（8 進位）\n",
           iHex, iHex, iHex);

    /* %o 接受八進位輸入 */
    printf("輸入一個八進位數字（如 546）：");
    scanf("%o", &iOct);
    printf("%o（8 進位）= %d（10 進位）= %x（16 進位）\n",
           iOct, iOct, iOct);

    system("pause");
    return 0;
}
```
