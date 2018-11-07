#include <stdio.h>
#include <stdlib.h>  // rand() 함수를 사용하기 위한 헤더파일
#include <time.h>


int main(void)
{
   printf("2차원 배열 출력\n\n");

   int arr[5][5];                           // 5*5 2차원 배열
   int max[5], Max[5];
   srand(time(NULL));

   for (int i = 0; i < 5; i++)
      for (int j = 0; j < 5; j++)
         arr[i][j] = rand() % 100 + 100;  // 100~199 난수 설정 범위

   for (int i = 0; i < 5; i++)              // 행 5개, 출력하는 반복문
   {
      printf("%d번째 배열\n", i + 1);

         for (int j = 0; j < 5; j++)      // 열 5개, 출력하는 반복문
            printf("%d : %d ", j + 1, arr[i][j]);
      printf("\n\n");
   }


   printf("최댓값 출력\n\n");

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
      printf("%d번째 배열의 %d번째 정수 : %d\n\n", i+1, Max[i] + 1, max[i]);
   }

   return 0;
}
