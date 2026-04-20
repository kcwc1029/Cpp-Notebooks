#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a, b, result;

    /* 前置遞增（++x）：先加再用 */
    a = 5;
    result = ++a;   /* 先把 a 加成 6，再把 6 指定給 result */
    printf("前置遞增：a = %d, result = %d\n", a, result);
    /* 輸出：a = 6, result = 6 */

    /* 後置遞增（x++）：先用再加 */
    b = 5;
    result = b++;   /* 先把 5 指定給 result，再把 b 加成 6 */
    printf("後置遞增：b = %d, result = %d\n", b, result);
    /* 輸出：b = 6, result = 5 */

    /* 在獨立敘述中，兩者效果相同 */
    int x = 10;
    x++;    /* 等同於 x += 1; 或 x = x + 1; */
    ++x;    /* 等同於 x += 1; 或 x = x + 1; */
    printf("x = %d\n", x);  /* 輸出 12 */

    system("pause");
    return 0;
}