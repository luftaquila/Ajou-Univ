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

void updateMap(int map[][MAP_WIDTH], t_ship *ship, t_rock *rock, t_fill *fill, int MAX_ROCK)
{	//updateMap 함수는 우주선과 돌의 위치를 map배열에 기입해주는 기능
	//맵을 EMPTY영역으로 바꾸어준다.
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
			map[i][j] = EMPTY;

	map[ship->ypos][ship->xpos] = SHIP; // 필드에서 우주선 위치에 우주선 기록
	map[fill->ypos][fill->xpos] = FILL; // 필드에서 회복 아이템 위치에 기록

	for (int i = 0; i < MAX_ROCK; i++) // 모든 운석에 대하여
	{
		if(rock[i].rock_size > 80) // 피해량이 80 이상인 운석은
		{ // 4칸 배정
			map[rock[i].ypos][rock[i].xpos] = BIG_ROCK;
			map[rock[i].ypos + 1][rock[i].xpos] = BIG_ROCK;
			map[rock[i].ypos][rock[i].xpos + 1] = BIG_ROCK;
			map[rock[i].ypos + 1][rock[i].xpos + 1] = BIG_ROCK;
		}

		else
			map[rock[i].ypos][rock[i].xpos] = ROCK; // 일반 돌은 1칸 배정
	}
}

void printMap(int map[][MAP_WIDTH], t_ship *ship, char *icon)
{	//현재 map배열의 정보를 화면에 띄워주는 함수로 기본 제공코드
   COORD console_pos = { 0, 0 };	//기본 제공 코드 내용
	//system("cls"); 화면을 지우는 명령, 하지만 화면이 깜빡임이 심해서 아래 SetConsoleCursorPostion함수를 사용
	SetConsoleCursorPosition(consoleHandle, console_pos);   //이 함수는 커서를 [0,0]에 위치시키고 기존 문자를 덮어씌움, 즉 내용이 작성되어 가장 밑에가있는 커서를 맨위로 끌어올려 다시 덮어씌움
	printSquare(MAP_WIDTH + 2); // 필드 상단 경계 출력
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		printf("□"); // 필드 좌측 경계 출력
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (map[i][j])
			{ // 필드 요소 출력
				case EMPTY:		printf("  "); 	 break;
				case ROCK:		printf("＊");	break;
				case BIG_ROCK:	printf("●");	 break;
				case SHIP:		printf(icon);	 break;
				case FILL:		printf("♣");	 break;
			}
		}
		printf("□"); // 필드 우측 경계 출력

		switch (i) // 화면 우측 인터페이스 출력
		{
			case 2:	printf("\t    조작 방법");	break;
			case 3:	printf("\t\tUP");	break;
			case 4:	printf("\t\t↑");	break;
			case 5:	printf("\t LEFT← ◆ → RIGHT");	break;
			case 6:	printf("\t\t↓");	break;
			case 7:	printf("\t       DOWN");	break;
			case 10:	printf("\t   health : %d   ", ship->health);	break;
			case 15:	printf("\t   ESC KEY 게임 종료!");	break;
			case 17:	printf("\t \b\b\b\b일시정지하려면 p키를 누르세요     ");	break;
			case 19: printf("   s키를 누르면 현재 상태를 저장하고 종료합니다"); break;
		}
		printf("\n");
	}
	printSquare(MAP_WIDTH + 2); // 필드 하단 경계 출력
}

void printSquare(int num)	//제공코드로 num개만큼의 사각형을 화면에 띄워줌
{
	for ( ; num > 0; num--)
		printf("□");
	printf("\n");
}

void moveRock(t_rock *rock, int MAX_ROCK)
{
	int cng_x, cng_y; // 변화량 지정 변수
	for(int i = 0; i < MAX_ROCK; i++) // 모든 운석에 대하여
	{
		cng_x = rand() % 3 - 1; // x축 변화량, y축 변화량 -1, 0, 1 중 하나로 설정
		cng_y = rand() % 3 - 1;

		rock[i].xpos += cng_x; // 좌표에 변화량 적용
		rock[i].ypos += cng_y;

		if(rock[i].rock_size < 80) // 피해량이 80 이상인 4칸짜리 운석에 대해서 맵 바깥으로 이탈시 복귀
		{
			if(rock[i].xpos < 0 || rock[i].xpos > 29)	rock[i].xpos -= cng_x * 2;
			if(rock[i].ypos < 0 || rock[i].ypos > 29)	rock[i].ypos -= cng_y * 2;
		}

		else // 피해량 80 미만 운석에 대해서 맵 이탈시 복귀
		{
			if(rock[i].xpos < 0 || rock[i].xpos > 28)	rock[i].xpos -= cng_x * 2;
			if(rock[i].ypos < 0 || rock[i].ypos > 28)	rock[i].ypos -= cng_y * 2;
		}
	}
}
