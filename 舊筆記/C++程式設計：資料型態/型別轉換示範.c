#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int   ix = 4, iy = 3, iz = 2;
    float fy = 3.0f;
    float fr;
    int   ir;

    /* 整數 / 整數 → 整數（捨去小數）*/
    ir = 2 / 3;
    printf("2/3（整數）= %d\n", ir);             /* 0 */

    /* 整數變數 / 整數變數 → 整數，再存到 float */
    fr = iz / iy;
    printf("iz(2)/iy(3)（先整數除，再存 float）= %.5f\n", fr);  /* 0.00000 */

    /* int / float → float（ix 自動轉成 float）*/
    ir = ix / fy;   /* 1.333...，再截斷成整數 1 */
    printf("ix(4)/fy(3.0f)（存到 int）= %d\n", ir);  /* 1 */

    fr = ix / fy;   /* 4.0f / 3.0f = 1.33333 */
    printf("ix(4)/fy(3.0f)（存到 float）= %.5f\n", fr);  /* 1.33333 */

    /* 浮點數常數的預設型別示範 */
    printf("1.0f/3.0f = %.12f\n", 1.0f / 3.0f);  /* float 精確度 */
    printf("1.0 /3.0  = %.12f\n", 1.0  / 3.0);   /* double 精確度 */

    system("pause");
    return 0;
}