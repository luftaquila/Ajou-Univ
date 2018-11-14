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
   Student s1 = {"홍길동", "배구", 30, 60.2, 179.4};
   Student *sp = &s1;
   sp->age += 1;
   sp->weight -= 33;
   strcpy(sp->hobby, "축구");
   strcpy(sp->name, "박길동");

   printf("이름 %s 취미 %s 나이 %d 몸무게 %lf 키 %lf\n", sp->name, sp->hobby, sp->age, sp->weight, sp->height);

   return 0;
}
