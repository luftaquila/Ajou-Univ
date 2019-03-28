#include<stdio.h>

#define MAX_SIZE 30

int RabbitNumber[MAX_SIZE];

int fib(int value);
void setArray(int N);
void printArray(int N);

void main()
{
	int month;

	printf("관찰한 기간을 입력하세요:");
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
	// 실습2. 문제(3)-1 fib 함수 완성하기
}

void setArray(int N)
{
	for(int i = 0; i < MAX_SIZE; i++) {
		RabbitNumber[i] = fib(i);
	}
}

void printArray(int N)
{
	// 실습2. 문제(3)-3 printArray 함수 완성하기
}
