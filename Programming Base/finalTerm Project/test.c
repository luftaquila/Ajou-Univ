#include <stdio.h>
#include <stdlib.h>  // rand() �Լ��� ����ϱ� ���� �������
#include <time.h>


int main(void)
{
   printf("2���� �迭 ���\n\n");

   int arr[5][5];                           // 5*5 2���� �迭
   int max[5], Max[5];
   srand(time(NULL));

   for (int i = 0; i < 5; i++)
      for (int j = 0; j < 5; j++)
         arr[i][j] = rand() % 100 + 100;  // 100~199 ���� ���� ����

   for (int i = 0; i < 5; i++)              // �� 5��, ����ϴ� �ݺ���
   {
      printf("%d��° �迭\n", i + 1);

         for (int j = 0; j < 5; j++)      // �� 5��, ����ϴ� �ݺ���
            printf("%d : %d ", j + 1, arr[i][j]);
      printf("\n\n");
   }


   printf("�ִ� ���\n\n");

   for(int i = 0; i < 5; i++)
   {
      max[i] = arr[i][0];
      Max[i] = 0;
   }

   for (int i = 0; i < 5; i++)
   {
      if (max[i] < arr[i]) //
         max[i] = arr[i]; //
         Max[i] = i;
   }


   for (int i = 0; i < 5; i++)
   {
      printf("%d��° �迭�� %d��° ���� : %d\n\n", i+1, Max[i] + 1, max[i]);
   }

   return 0;
}
