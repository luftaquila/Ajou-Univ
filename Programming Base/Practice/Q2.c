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
	Student s1 = {"ȫ�浿", "LOL", 33, 72.3, 174.9};
	Student s2;
	Student s3 = {"�ڱ浿", "Soccer", 27, 82.3, 182.9};

	strcpy(s2.name, "����");
	strcpy(s2.hobby, "Crazy Arcade");
	s2.age = 22;
	s2.weight = 42.3;
	s2.height = 154.9;

   return 0;
}
