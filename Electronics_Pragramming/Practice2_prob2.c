#include <stdio.h>

int isPrimeNumber(int test);
void PrintPrimeNumbers(int N, int M);

void main()
{

	int N, M;

	printf("범위를 입력하세요:");
	scanf("%d,%d", &N, &M);

	PrintPrimeNumbers(N, M);

	printf("\n");

}
int isPrimeNumber(int test)
{
	for(int i = test - 1; i > 1; i--) {
		if(!(test % i)) return 0;
		else continue;
	}
	return 1;
}

void PrintPrimeNumbers(int N, int M)
{
	for(int i = N; i < M; i++) {
		if(isPrimeNumber(i)) printf("%d, ", i);
	}
}
