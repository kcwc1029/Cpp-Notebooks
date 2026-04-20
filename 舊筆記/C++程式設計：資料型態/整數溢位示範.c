#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /* char 溢位示範 */
    char cx = 127;   /* char 的最大值 */
    printf("char cx = %d\n", cx);
    cx = cx + 1;     /* 127 + 1 → 溢位！ */
    printf("cx + 1  = %d\n", cx);   /* 結果不是 128，而是 -128 */

    /* short 溢位示範 */
    short sx = -32766;
    printf("\nshort sx = %d\n", sx);
    sx = sx - 4;     /* -32766 - 4 → -32770，超出 short 最小值 -32768 */
    printf("sx - 4   = %d\n", sx);  /* 結果不是 -32770 */

    /* unsigned int 溢位示範（從 0 往下減）*/
    unsigned int uix = 0;
    printf("\nunsigned int uix = %u\n", uix);
    uix = uix - 2;   /* 0 - 2 → 溢位！unsigned 沒有負數 */
    printf("uix - 2  = %u\n", uix); /* 結果是 4294967294 */

    system("pause");
    return 0;
}