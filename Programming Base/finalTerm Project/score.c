#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <stdbool.h>
#include "function.h"

void addScore(float score)
{
	FILE *fp; // 파일 포인터 선언
	char name[NAME_LENGHT], **str, *buffer, *ptrLine, *ptrObject;
	// 이름 입력을 위한 문자열, 파일 입출력을 위한 문자열 포인터 선언
	int size, counter = 0; // 파일의 크기와 줄 수를 세는 변수
	Player **player = NULL, *temp; // 구조체 포인터 배열을 위한 이중 포인터, 정렬을 위한 구조체 포인터 선언

	fflush(stdin);
	printf("당신의 점수는 %.3f점 입니다. 점수를 저장하기 위해서는 이름이 필요합니다.\n", score);
	printf("이름 ☞ : ");
	scanf("%s", name);

	fp = fopen("GameScore.csv", "a+"); // 파일이 없으면 생성하고 r/w 모드로 열기

	fseek(fp, 0, SEEK_END); // 파일의 끝으로 포인터를 이동
	size = ftell(fp); // 파일 크기를 size에 저장

	buffer = (char *)malloc(size + 1); // 입력 버퍼를 파일 크기만큼 동적 할당
	memset(buffer, 0, size + 1); // // 버퍼 초기화

	fseek(fp, 0, SEEK_SET); // 파일의 처음으로 포인터를 이동
	fread(buffer, size, 1, fp); // 파일 내용을 입력 버퍼로 이동

	for (int i = 0; i < size; i++) // 버퍼에서 개행 문자를 찾아서 줄 수 카운트
	{
		if (buffer[i] == '\n')
			counter++;
	}

	player = (Player **)calloc(counter + 2, sizeof(*player));
	// 기존 파일 줄 수(플레이어 기록 수)에 추가할 플레이어 기록까지 더하여 구조체 배열 동적 할당
	str = (char **)calloc(counter + 2, sizeof(*str)); // 입력 버퍼에서 한 줄씩 읽어올 버퍼

	ptrLine = strtok(buffer, "\n"); // 입력 버퍼를 한 줄씩 쪼개서 str에 저장
	for (int i = 0; ptrLine != NULL; i++)
	{
		str[i] = ptrLine;
		ptrLine = strtok(NULL, "\n");
	}

	for (int i = 0; str[i]; i++) // 한 줄씩 저장된 각 str을 ,로 쪼개서 구조체에 저장
	{
		player[i] = (Player *)malloc(sizeof(**player)); // 구조체 배열 요소 크기 동적 할당

		ptrObject = strtok(str[i], ",");
		player[i]->rank = atoi(ptrObject);

		ptrObject = strtok(NULL, ",");
		strcpy(player[i]->name, ptrObject);

		ptrObject = strtok(NULL, ",");
		player[i]->time = atof(ptrObject);
	}

	player[counter] = (Player *)malloc(sizeof(**player)); // 구조체의 끝에 새로운 플레이어 기록 공간 할당
	player[counter]->rank = 0; // 순위는 0으로 초기화
	strcpy(player[counter]->name, name); // 구조체에 이름과 기록 저장
	player[counter]->time = score;

	for (int i = 0; i < counter + 1; i++) // 구조체를 기록 순으로 내림차 정렬
	{
		for (int j = 0; j < i; j++)
		{
			if (player[i]->time > player[j]->time)
			{
				temp = player[i];
				player[i] = player[j];
				player[j] = temp;
			}
		}
	}

	for (int i = 0; i < counter + 1; i++) // 정렬이 완료된 구조체에 순위 매기기
		player[i]->rank = i + 1;

	fp = fopen("GameScore.csv", "w"); // 파일을 쓰기 모드로 다시 열기

	for (int i = 0; player[i]; i++) // 구조체 내용을 한 줄씩 csv 형식으로 파일에 출력
		fprintf(fp, "%d,%s,%.3f\n", player[i]->rank, player[i]->name, player[i]->time);
	fclose(fp); // 파일 닫기

	free(player); // 동적할당 공간 반납
	free(str);

	viewScore(&name, score); // 기록 열람 함수 호출
}

void viewScore(char *name, float score)
{	//함수를 호출시 화면을 지우고 화면에 GameScore.txt 파일로부터 점수를 읽은후 화면에 출력하는 함수
	FILE *fp;
	char **str, *buffer, *ptrLine, *ptrObject;
	int size, counter = 0;
	Player **player = NULL; // addScore와 동일한 변수 선언.

	fp = fopen("GameScore.csv", "r"); // 파일을 읽기 모드로 열기
	if (fp == NULL) // 파일이 존재하지 않을 경우 오류 문구 출력.
	{
		printf("저장된 데이터가 없습니다!\n");
		Sleep(1000);
		return;
	}

	else // 파일이 존재할 경우
	{
		system("cls");
		printf("등수\t이름\t점수\n"); // 레이아웃 출력

		fseek(fp, 0, SEEK_END); // addScore 함수와 동일한 파일 읽기 동작
		size = ftell(fp);

		buffer = (char *)malloc(size + 1);
		memset(buffer, 0, size + 1);

		fseek(fp, 0, SEEK_SET);
		fread(buffer, size, 1, fp);

		for (int i = 0; i < size; i++)
		{
			if (buffer[i] == '\n')
				counter++;
		}

		player = (Player **)calloc(counter + 2, sizeof(*player));
		str = (char **)calloc(counter + 2, sizeof(*str));

		ptrLine = strtok(buffer, "\n");
		for (int i = 0; ptrLine != NULL; i++)
		{
			str[i] = ptrLine;
			ptrLine = strtok(NULL, "\n");
		}
		fclose(fp); // 버퍼에 복사 후 파일 닫기

		for (int i = 0; str[i]; i++) // 버퍼에서 분리하여 구조체에 저장
		{
			player[i] = (Player *)malloc(sizeof(**player));

			ptrObject = strtok(str[i], ",");
			player[i]->rank = atoi(ptrObject);

			ptrObject = strtok(NULL, ",");
			strcpy(player[i]->name, ptrObject);

			ptrObject = strtok(NULL, ",");
			player[i]->time = atof(ptrObject);
		}

		for (int i = 0; player[i]; i++) // 화면에 출력
		{
			printf(" %2d\t%s\t%.3f", player[i]->rank, player[i]->name, player[i]->time);
			if((player[i]->time == score)) // 기록이 일치하는 플레이어 레코드에 자신임을 표시
				printf("\t← YOU");
			printf("\n");
		}

		free(player); // 동적 할당 메모리 반납
		free(str);

		system("PAUSE && cls"); // 일시 정지 후 화면 초기화
	}
}
