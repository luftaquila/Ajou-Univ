#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME 20
#include <stdio.h>
#include <string.h>

struct student
{
	char name[MAX_NAME];
	char hobby[MAX_NAME];
	int age;
	double weight;
	double height;
};
int main()
{
	struct student s1 = {"È«±æµ¿", "LOL", 33, 72.3, 174.9};
	struct student s2;
	struct student s3 = {"¹Ú±æµ¿", "Soccer", 27, 82.3, 182.9};

	strcpy(s2.name, "±è±æ¼ø");
	strcpy(s2.hobby, "Crazy Arcade");
	s2.age = 22;
	s2.weight = 42.3;
	s2.height = 154.9;

   return 0;
}
