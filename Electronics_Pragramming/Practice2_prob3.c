#include<stdio.h>

#define MAX_SIZE 30

int RabbitNumber[MAX_SIZE];

int fib(int value);
void setArray(int N);
void printArray(int N);

void main()
{
	int month;

	printf("������ �Ⱓ�� �Է��ϼ���:");
	scanf("%d", &month);

	setArray(month);
	printArray(month);

	printf("\n");
}

int fib(int value)
{
	int a, b, c;
	if(value == 1) {
		printf("%d", )
	}
	// �ǽ�2. ����(3)-1 fib �Լ� �ϼ��ϱ�
}

void setArray(int N)
{
	for(int i = 0; i < MAX_SIZE; i++) {
		RabbitNumber[i] = fib(i);
	}
}

void printArray(int N)
{
	// �ǽ�2. ����(3)-3 printArray �Լ� �ϼ��ϱ�
}
