#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    float  fx;
    double dx;

    /* 儲存相同的數值，看輸出的差異 */
    fx = 0.12345678901234567890;
    dx = 0.12345678901234567890;

    printf("===== 儲存同一個數值 =====\n");
    printf("float  fx = %.20f\n", fx);  /* 顯示 20 位小數 */
    printf("double dx = %.20f\n", dx);

    /* 1/3 的精確度比較 */
    printf("\n===== 計算 1/3 =====\n");
    fx = 1.0f / 3.0f;     /* 兩邊都是 float */
    dx = 1.0  / 3.0;      /* 兩邊都是 double */
    printf("float  1.0f/3.0f = %.20f\n", fx);
    printf("double 1.0 /3.0  = %.20f\n", dx);

    system("pause");
    return 0;
}