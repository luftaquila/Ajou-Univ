#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME    20
#include <stdio.h>
#include <string.h>

typedef struct student {
	char	name[MAX_NAME];
	char	hobby[MAX_NAME];
	int	age;
	double	weight;
	double	height;
} Student;
int main()
{
	Student s1 = { "ȫ�浿", "LOL", 33, 72.3, 174.9 };
	Student s2;
	Student s3 = { "�ڱ浿", "Soccer", 27, 82.3, 182.9 };

	strcpy(s2.name, "����");
	strcpy(s2.hobby, "Crazy Arcade");
	s2.age = 22;
	s2.weight = 42.3;
	s2.height = 154.9;

	printf("1 - �̸� : %s, ��� : %s, ���� : %d, ������ : %.1lf, Ű : %.1lf\n",
	    s1.name, s1.hobby, s1.age, s1.weight, s1.height);
	printf("2 - �̸� : %s, ��� : %s, ���� : %d, ������ : %.1lf, Ű : %.1lf\n",
	    s2.name, s2.hobby, s2.age, s2.weight, s2.height);
	printf("3 - �̸� : %s, ��� : %s, ���� : %d, ������ : %.1lf, Ű : %.1lf\n",
	    s3.name, s3.hobby, s3.age, s3.weight, s3.height);
	return (0);
}
