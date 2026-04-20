#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int score = 100;
    printf("初始值  score = %d\n", score);

    score += 20;   /* score = score + 20 */
    printf("+=20   score = %d\n", score);  /* 120 */

    score -= 15;   /* score = score - 15 */
    printf("-=15   score = %d\n", score);  /* 105 */

    score *= 2;    /* score = score * 2 */
    printf("*=2    score = %d\n", score);  /* 210 */

    score /= 3;    /* score = score / 3 */
    printf("/=3    score = %d\n", score);  /* 70 */

    score %= 8;    /* score = score % 8 */
    printf("%%=8   score = %d\n", score);  /* 70 % 8 = 6 */

    system("pause");
    return 0;
}