> 使用以下所有函式前，必須在程式開頭加上：
>
> ```c
> #include <string.h>
> ```

### 10.1 strlen：取得字串長度

**語法：** `size_t strlen(const char *str);`

- 回傳字串中的字元個數，**不含 `\0`**
- 回傳型別是 `size_t`（無號整數），`printf` 輸出時建議加 `(int)` 轉型

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    char s1[] = "Hello";
    char s2[] = "Hello, World!";
    char s3[] = "";         /* 空字串 */

    printf("strlen(\"%s\") = %d\n", s1, (int)strlen(s1));  /* 5 */
    printf("strlen(\"%s\") = %d\n", s2, (int)strlen(s2));  /* 13 */
    printf("strlen(\"%s\") = %d\n", s3, (int)strlen(s3));  /* 0 */

    /* 應用：取得最後一個字元 */
    int len = (int)strlen(s1);
    printf("最後一個字元：%c\n", s1[len - 1]);  /* o */

    return 0;
}
```

### 10.2 strcpy / strncpy：字串複製

**⚠️ 為什麼不能用 `=` 複製字串？**

```c
char src[] = "Hello";
char dst[20];

dst = src;   /* ❌ 編譯錯誤！陣列名稱是位址（左值），不能被指定 */
```

**必須用 `strcpy` 或 `strncpy`：**

```c
/* strcpy：字串複製（不安全版）*/
char *strcpy(char *dst, const char *src);
/* 把 src 的內容複製到 dst，包含 \0 */
/* 不會檢查 dst 是否夠大！ */

/* strncpy：字串複製（安全版，推薦）*/
char *strncpy(char *dst, const char *src, size_t n);
/* 最多複製 n 個字元，不會超出 dst 的大小 */
/* 若 src 長度 < n，剩餘位置填 \0 */
/* 若 src 長度 >= n，dst 末尾不會自動加 \0！ */
```

**完整示範：**

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void)
{
    char src[]   = "Hello, C!";
    char dst1[20] = "";
    char dst2[20] = "";

    /* strcpy：直接複製 */
    strcpy(dst1, src);
    printf("strcpy  結果：%s\n", dst1);   /* Hello, C! */

    /* strncpy：限制複製長度（推薦）*/
    strncpy(dst2, src, sizeof(dst2) - 1);  /* 最多複製 19 個字元 */
    dst2[sizeof(dst2) - 1] = '\0';         /* 確保結尾有 \0 */
    printf("strncpy 結果：%s\n", dst2);   /* Hello, C! */

    /* 複製部分字串（只複製前 5 個字元）*/
    char partial[10] = "";
    strncpy(partial, src, 5);
    partial[5] = '\0';                     /* 手動加 \0 */
    printf("前 5 字元：%s\n", partial);   /* Hello */

    return 0;
}
```

> 💡 **安全習慣：** 使用 `strncpy` 後，永遠手動在陣列末尾加上 `'\0'`，以防萬一：
>
> ```c
> strncpy(dst, src, sizeof(dst) - 1);
> dst[sizeof(dst) - 1] = '\0';
> ```

### 10.3 strcat / strncat：字串串接

```c
/* strcat：字串串接（不安全版）*/
char *strcat(char *dst, const char *src);
/* 把 src 接在 dst 的末尾，dst 必須有足夠空間 */

/* strncat：字串串接（安全版，推薦）*/
char *strncat(char *dst, const char *src, size_t n);
/* 最多從 src 串接 n 個字元，並自動加上 \0 */
```

**完整示範：**

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    char greeting[50] = "Hello";
    char name[]       = "Einstein";
    char punctuation[] = "!";

    /* 用 strncat 安全串接 */
    strncat(greeting, ", ", sizeof(greeting) - strlen(greeting) - 1);
    strncat(greeting, name, sizeof(greeting) - strlen(greeting) - 1);
    strncat(greeting, punctuation, sizeof(greeting) - strlen(greeting) - 1);

    printf("結果：%s\n", greeting);   /* Hello, Einstein! */
    printf("長度：%d\n", (int)strlen(greeting));  /* 17 */

    /* 實際應用：組合路徑 */
    char path[100] = "C:\\Users\\";
    char username[] = "Student";

    strncat(path, username, sizeof(path) - strlen(path) - 1);
    strncat(path, "\\Desktop", sizeof(path) - strlen(path) - 1);

    printf("路徑：%s\n", path);   /* C:\Users\Student\Desktop */

    return 0;
}
```

### 10.4 strcmp / strncmp：字串比較

**為什麼不能用 `==` 比較字串？**

```c
char s1[] = "Hello";
char s2[] = "Hello";

if (s1 == s2)    /* ❌ 比較的是兩個陣列的記憶體位址，不是內容！ */
    printf("相同\n");   /* 這行永遠不會執行！位址不同 */
```

**必須用 `strcmp` 或 `strncmp`：**

```c
/* strcmp：字串比較（區分大小寫）*/
int strcmp(const char *s1, const char *s2);

/* 回傳值：
   0    → s1 == s2（完全相同）
   < 0  → s1 < s2（s1 在字典序中較前）
   > 0  → s1 > s2（s1 在字典序中較後）
*/

/* strncmp：只比較前 n 個字元 */
int strncmp(const char *s1, const char *s2, size_t n);
```

**完整示範：**

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    char s1[] = "Apple";
    char s2[] = "Apple";
    char s3[] = "Banana";
    char s4[] = "apple";   /* 小寫 a */

    /* strcmp：完全相同 */
    printf("strcmp(\"%s\", \"%s\") = %d\n", s1, s2, strcmp(s1, s2));
    /* 輸出：0（相同）*/

    /* strcmp：字典序比較 */
    printf("strcmp(\"%s\", \"%s\") = %d\n", s1, s3, strcmp(s1, s3));
    /* 輸出：負數（Apple < Banana，因為 A < B）*/

    printf("strcmp(\"%s\", \"%s\") = %d\n", s3, s1, strcmp(s3, s1));
    /* 輸出：正數（Banana > Apple）*/

    /* strcmp：大小寫有別 */
    printf("strcmp(\"%s\", \"%s\") = %d\n", s1, s4, strcmp(s1, s4));
    /* 輸出：負數（Apple < apple，因為 A(65) < a(97)）*/

    /* 正確的字串相等比較方式 */
    if (strcmp(s1, s2) == 0)
        printf("\"%s\" 與 \"%s\" 相同！\n", s1, s2);
    else
        printf("不同。\n");

    /* strncmp：只比較前 3 個字元 */
    char a[] = "Apple Pie";
    char b[] = "Apple Cider";
    printf("strncmp 前 5 字元：%d\n", strncmp(a, b, 5));   /* 0，前5字元相同 */
    printf("strncmp 前 6 字元：%d\n", strncmp(a, b, 6));   /* 非0，第6字元不同 */

    return 0;
}
```

**應用：密碼驗證**

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define CORRECT_PASSWORD "Tr0ub4dor"

int main(void)
{
    char input[50] = "";

    printf("請輸入密碼：");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';   /* 去除 \n */

    if (strcmp(input, CORRECT_PASSWORD) == 0)
        printf("密碼正確，歡迎登入！\n");
    else
        printf("密碼錯誤，存取被拒絕。\n");

    return 0;
}
```

### 10.5 strchr：尋找字元

```c
/* 在字串中尋找某個字元，回傳第一次出現的位置（指標）*/
char *strchr(const char *str, int c);
/* 找不到時回傳 NULL */
```

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    char email[] = "student@example.com";
    char *at_sign;

    /* 尋找 @ 符號 */
    at_sign = strchr(email, '@');

    if (at_sign != NULL)
    {
        printf("找到 '@'！\n");
        printf("@ 之後的部分：%s\n", at_sign + 1);  /* example.com */
        printf("@ 的位置（索引）：%d\n", (int)(at_sign - email));  /* 7 */
    }
    else
        printf("找不到 '@'，不是合法的 email。\n");

    /* 尋找最後一次出現的字元：strrchr */
    char path[] = "C:\\Users\\Student\\readme.txt";
    char *last_slash = strrchr(path, '\\');
    if (last_slash)
        printf("檔名：%s\n", last_slash + 1);  /* readme.txt */

    return 0;
}
```

### 10.6 strstr：尋找子字串

```c
/* 在字串中尋找子字串，回傳第一次出現的位置（指標）*/
char *strstr(const char *haystack, const char *needle);
/* 找不到時回傳 NULL */
```

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    char sentence[] = "The quick brown fox jumps over the lazy dog";
    char *pos;

    /* 尋找子字串 "fox" */
    pos = strstr(sentence, "fox");
    if (pos)
    {
        printf("找到 \"fox\"！\n");
        printf("位置（索引）：%d\n", (int)(pos - sentence));  /* 16 */
        printf("從 \"fox\" 開始的內容：%s\n", pos);  /* fox jumps over the lazy dog */
    }

    /* 判斷字串是否包含子字串 */
    if (strstr(sentence, "cat") == NULL)
        printf("沒有找到 \"cat\"。\n");

    /* 不區分大小寫搜尋（需要先轉換大小寫，或用 strcasestr 非標準函式）*/
    /* 標準 C 沒有提供不區分大小寫的 strstr，可自行實作 */

    return 0;
}
```

### 10.7 strtok：字串切割

`strtok`（string tokenize）用於把字串依照分隔符號切割成多個「token（語彙單元）」。

```c
char *strtok(char *str, const char *delim);
/* 第一次呼叫：傳入要切割的字串和分隔符號字串
   之後呼叫：第一個參數改傳 NULL，繼續切割同一個字串
   回傳：每次回傳下一個 token 的起始位址，切割完畢回傳 NULL */
```

> ⚠️ **注意：** `strtok` 會**修改原始字串**（把分隔符號位置換成 `\0`），操作前建議複製一份。

```c
#include <stdio.h>
#include <string.h>

int main(void)
{
    /* 範例一：用空格切割 */
    char sentence[] = "The quick brown fox";
    char *token;

    token = strtok(sentence, " ");    /* 第一次：傳入字串 */
    while (token != NULL)
    {
        printf("token：%s\n", token);
        token = strtok(NULL, " ");    /* 後續：傳入 NULL */
    }
    /* 輸出：
       token：The
       token：quick
       token：brown
       token：fox
    */

    /* 範例二：CSV 資料解析（逗號分隔）*/
    char csv[] = "小明,20,台北,資工系";
    char *fields[10];
    int  count = 0;

    fields[count] = strtok(csv, ",");
    while (fields[count] != NULL)
    {
        count++;
        fields[count] = strtok(NULL, ",");
    }

    printf("\n===== CSV 解析結果 =====\n");
    printf("姓名：%s\n", fields[0]);   /* 小明 */
    printf("年齡：%s\n", fields[1]);   /* 20 */
    printf("城市：%s\n", fields[2]);   /* 台北 */
    printf("科系：%s\n", fields[3]);   /* 資工系 */

    return 0;
}
```

### 10.8 string.h 函式完整速查表

| 函式                   | 用途                   | 安全版    | 說明              |
| ---------------------- | ---------------------- | --------- | ----------------- |
| `strlen(s)`            | 字串長度               | —         | 不含 `\0`         |
| `strcpy(dst, src)`     | 字串複製               | `strncpy` | 不檢查大小        |
| `strncpy(dst, src, n)` | 字串複製（安全）       | —         | 最多 n 字元       |
| `strcat(dst, src)`     | 字串串接               | `strncat` | 不檢查大小        |
| `strncat(dst, src, n)` | 字串串接（安全）       | —         | 最多串 n 字元     |
| `strcmp(s1, s2)`       | 字串比較               | `strncmp` | 0=相同，<0=s1較小 |
| `strncmp(s1, s2, n)`   | 比較前 n 字元          | —         | —                 |
| `strchr(s, c)`         | 找字元（第一次）       | —         | 找不到傳 `NULL`   |
| `strrchr(s, c)`        | 找字元（最後次）       | —         | 找不到傳 `NULL`   |
| `strstr(s, sub)`       | 找子字串               | —         | 找不到傳 `NULL`   |
| `strtok(s, delim)`     | 字串切割               | —         | 修改原字串        |
| `strcspn(s, reject)`   | 找第一個匹配字元的位置 | —         | 常用於去除 `\n`   |
