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
      printf("�̸� : ");
      scanf("%s", name);
      int score;
      printf("������ �Է��ϼ��� : ");
      scanf("%d", &score);

      fprintf(fp, "������� �̸� %s ���� %d", name, score);
      printf("����Ϸ�!\n");
      fclose(fp);
   }
   return 0;
}
