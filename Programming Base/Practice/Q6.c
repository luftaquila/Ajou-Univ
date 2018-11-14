#define _CRT_SECURE_NO_WARNINGS
#define NAME_LENGTH 20
#include <stdio.h>

int main()
{
   FILE *fp;
   fp = fopen("GameScore.txt", "w");
   if(fp == NULL)
   {
      printf("cannot write to file\n");
      return -1;
   }
   else
   {
      char name[NAME_LENGTH];
      printf("이름 : ");
      scanf("%s", name);
      int score;
      printf("점수를 입력하세요 : ");
      scanf("%d", &score);

      fprintf(fp, "사용자의 이름 %s 점수 %d", name, score);
      printf("저장완료!\n");
      fclose(fp);
   }
   return 0;
}
