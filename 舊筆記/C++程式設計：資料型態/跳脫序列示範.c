#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /* \n：換行 */
    printf("第一行\n第二行\n");

    /* \t：Tab 對齊 */
    printf("姓名\t成績\t等第\n");
    printf("小明\t95\tA\n");
    printf("小華\t82\tB\n");

    /* \\：輸出反斜線 */
    printf("路徑：C:\\Users\\Student\\Desktop\\\n");

    /* \"：輸出雙引號 */
    printf("他說：\"你好！\"\n");

    /* \'：輸出單引號 */
    printf("it\'s a pen\n");

    /* \a：警告音（執行時電腦會發出嗶聲）*/
    printf("發出警告音\a\n");

    /* \b：倒退鍵（覆蓋前一個字元）*/
    printf("AB\bX\n");   /* 輸出 AB，退一格，再輸出 X → 顯示 AX */

    system("pause");
    return 0;
}