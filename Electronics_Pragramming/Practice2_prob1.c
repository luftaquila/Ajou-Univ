#include <stdio.h>
int main() {
	int tmp, num;
	printf("정수를 입력하세요 : ");
	scanf("%d", &num);
	for(int i = 31; i > -1; i--) {
		tmp = (num >> i) & 1;
		printf("%d", tmp);
	}
	printf("\n");
}
