#include <stdio.h>
#include <stdlib.h>

int main(void){
    unsigned int ix;

    printf("===== 各資料型別的大小 =====\n");
    printf("sizeof(char)      = %d byte\n",  (int)sizeof(char));
    printf("sizeof(short)     = %d bytes\n", (int)sizeof(short));
    printf("sizeof(int)       = %d bytes\n", (int)sizeof(int));
    printf("sizeof(long)      = %d bytes\n", (int)sizeof(long));
    printf("sizeof(long long) = %d bytes\n", (int)sizeof(long long));
    printf("sizeof(float)     = %d bytes\n", (int)sizeof(float));
    printf("sizeof(double)    = %d bytes\n", (int)sizeof(double));

    printf("\n===== 查詢變數與常數的大小 =====\n");
    printf("sizeof(ix)   = %d bytes\n", (int)sizeof(ix));
    printf("sizeof(12)   = %d bytes\n", (int)sizeof(12));    /* int 常數 */
    printf("sizeof(12L)  = %d bytes\n", (int)sizeof(12L));   /* long 常數 */
    printf("sizeof(1.24f) = %d bytes\n", (int)sizeof(1.24f)); /* float 常數 */
    printf("sizeof(1.24)  = %d bytes\n", (int)sizeof(1.24));  /* double 常數 */

    system("pause");
    return 0;
}