#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    unsigned char ch = 53;
    int ix = 5;

    ch = ch << 1;  printf("ch <<= 1 → %d\n", ch);   /* 106（53×2）*/
    ch = ch << 1;  printf("ch <<= 1 → %d\n", ch);   /* 212（106×2）*/
    ch = ch << 1;  printf("ch <<= 1 → %d\n", ch);   /* 168（超出範圍）*/
    ch = ch >> 1;  printf("ch >>= 1 → %d\n", ch);   /* 84（168/2）*/
    ch = ch >> 1;  printf("ch >>= 1 → %d\n", ch);   /* 42（84/2）*/

    /* 整數的位移：比乘除法更快 */
    ix = ix << 5;  printf("5 << 5 = %d\n", ix);    /* 5 × 32 = 160 */
    ix = ix >> 3;  printf("160 >> 3 = %d\n", ix);  /* 160 / 8 = 20 */

    /* 複合指定也適用 */
    ix = 8;
    ix <<= 2;   printf("8 <<= 2 → %d\n", ix);    /* 8 × 4 = 32 */
    ix >>= 1;   printf("32 >>= 1 → %d\n", ix);   /* 32 / 2 = 16 */

    system("pause");
    return 0;
}




