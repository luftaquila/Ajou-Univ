#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME 20
#include <stdio.h>
#include <string.h>

typedef struct student
{
	char name[MAX_NAME];
	char hobby[MAX_NAME];
	int age;
	double weight;
	double height;
} Student;

int main()
{
	Student student[5];
   for(int i = 0; i < 5; i++)
   {
      printf("����� %d �̸� : ", i + 1);
      scanf("%s", student[i].name);
      printf("����� %d ��� : ", i + 1);
      scanf("%s", student[i].hobby);
      printf("����� %d ���� : ", i + 1);
      scanf("%d", &student[i].age);
      printf("����� %d ������ : ", i + 1);
      scanf("%lf", &student[i].weight);
      printf("����� %d Ű : ", i + 1);
      scanf("%lf", &student[i].height);
   }

   for(int i = 0; i < 5; i++)
   {
      printf("����� %d ���� : %s, %s, %d��, %.1lfkg, %.1lfcm\n",
         i + 1, student[i].name, student[i].hobby, student[i].age, student[i].weight, student[i].height);
   }
   return 0;
}
