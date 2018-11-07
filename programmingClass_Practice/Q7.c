#define NAME_LENGTH 20
#include <stdio.h>
int main()
{
   FILE *fp;
   fp = fopen("GameScore.txt", "r");
   if(fp == NULL)
   {
      printf("cannot read file\n");
      return -1;
   }
   else
   {
      char name[NAME_LENGTH];
      int score;
      fscanf(fp, "%*s %*s %s %*s %d", name, &score);
      printf("데이터의 값 이름 : %s 점수 %d\n", name, score);

      fclose(fp);
      return 0;
   }
}
