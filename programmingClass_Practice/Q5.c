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
   Student s1 = {"ȫ�浿", "�豸", 30, 60.2, 179.4};
   Student *sp = &s1;
   sp->age += 1;
   sp->weight -= 33;
   strcpy(sp->hobby, "�౸");
   strcpy(sp->name, "�ڱ浿");

   printf("�̸� %s ��� %s ���� %d ������ %lf Ű %lf\n", sp->name, sp->hobby, sp->age, sp->weight, sp->height);

   return 0;
}
