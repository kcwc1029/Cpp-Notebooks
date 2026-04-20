#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    unsigned char ch1 = 21;   /* 二進位：00010101 */
    unsigned char ch2 = 11;   /* 二進位：00001011 */
    unsigned char cht;

    cht = ch1 & ch2;   printf("21 AND 11    = %d\n", cht);   /* 1  */
    cht = ch1 | ch2;   printf("21 OR  11    = %d\n", cht);   /* 31 */
    cht = ch1 ^ ch2;   printf("21 XOR 11    = %d\n", cht);   /* 30 */
    cht = ~ch1;        printf("NOT 21       = %d\n", cht);   /* 234 */

    system("pause");
    return 0;
}