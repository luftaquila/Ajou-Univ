#include <stdio.h>
int main() {
	int tmp, num;
	printf("������ �Է��ϼ��� : ");
	scanf("%d", &num);
	for(int i = 31; i > -1; i--) {
		tmp = (num >> i) & 1;
		printf("%d", tmp);
	}
	printf("\n");
}
