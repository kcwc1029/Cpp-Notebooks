double pi = 3.14159265358979;

/* double 轉 float（降低精確度）*/
float  fpi = (float)pi;
printf("float  pi = %.10f\n", fpi);   /* 精確度較低 */
printf("double pi = %.10f\n", pi);    /* 精確度較高 */

/* 浮點數轉整數（捨去小數部分）*/
float score = 87.9f;
int   intScore = (int)score;
printf("%.1f 轉整數 = %d\n", score, intScore);  /* 87（不是四捨五入！）*/

/* 四捨五入的正確做法 */
int roundScore = (int)(score + 0.5f);
printf("%.1f 四捨五入 = %d\n", score, roundScore);  /* 88 */