int totalSecs = 3725;
int hours   = totalSecs / 3600;
int minutes = (totalSecs % 3600) / 60;
int seconds = totalSecs % 60;
printf("%d 秒 = %d 小時 %d 分 %d 秒\n", totalSecs, hours, minutes, seconds);
/* 輸出：3725 秒 = 1 小時 2 分 5 秒 */
