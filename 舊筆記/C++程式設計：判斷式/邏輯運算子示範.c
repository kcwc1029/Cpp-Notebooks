#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int ix = 3, iy = 2, iz = 2;

    /* 3 && (4>5)：3 為 true(非0)，4>5 為 false(0)，AND → false */
    printf("3 && 4>5           = %d\n", 3 && 4 > 5);    /* 0 */

    /* (3>2) || (1>2)：true || false → true */
    printf("3>2 || 1>2         = %d\n", 3 > 2 || 1 > 2); /* 1 */

    /* !(3>2)：!(true) → false */
    printf("!(3>2)             = %d\n", !(3 > 2));         /* 0 */

    /* (3>2 || 3>2) && (3 > 2*2)：(true) && (3>4=false) → false */
    printf("(ix>iy||ix>iz)&&(ix>iy*iz) = %d\n",
           (ix > iy || ix > iz) && (ix > iy * iz));        /* 0 */

    system("pause");
    return 0;
}