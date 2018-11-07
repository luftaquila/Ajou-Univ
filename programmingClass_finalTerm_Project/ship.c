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

void moveShip(t_ship *ship, int direction) // 우주선 구조체와 방향 정보를 인자로 전달
{
	switch (direction) // 방향 정보에 따라 맞는 방향으로 필드 영역 안에서 우주선의 위치 정보 변경.
	{
		case LEFT_KEY:		if (ship->xpos > 0)	ship->xpos--;	break;
		case RIGHT_KEY:	if (ship->xpos < 29)	ship->xpos++;	break;
		case UP_KEY:		if (ship->ypos > 0)	ship->ypos--;	break;
		case DOWN_KEY:		if (ship->ypos < 29)	ship->ypos++;	break;
	}
}

void updateShipHealth(t_ship *ship, t_rock *rock, t_fill *fill, int MAX_ROCK, float live_time)
{	  //우주선이 돌과 충돌했는지 판별하고, 충돌했다면 우주선의 체력 - 돌의 크기를 한다.
	if(live_time < 3) // 생존 시간이 3초 미만인 경우 피해를 입지 않음.
		return;

	for (int i = 0; i < MAX_ROCK; i++) // 모든 돌에 대하여 검사
	{
		if(rock[i].rock_size < 80) // 돌의 피해량이 80 미만인 경우
		{
			if ((ship->xpos == rock[i].xpos) && (ship->ypos == rock[i].ypos))
			{	// 돌과 우주선의 위치가 동일하면 돌 피해량 적용, 화면을 노란색으로 점멸
				ship->health -= rock[i].rock_size;
				system("color e0");
				system("color 0f");
			}
		}

		else // 돌의 피해량이 80 이상인 경우
		{
			if (((ship->xpos == rock[i].xpos) || (ship->xpos == rock[i].xpos + 1)) &&
				((ship->ypos == rock[i].ypos) || (ship->ypos == rock[i].ypos + 1)))
			{ // 돌의 크기 4칸 중 한 칸이라도 우주선의 위치와 일치하면
				ship->health -= rock[i].rock_size; // 피해량 적용
				system("color cf"); // 화면을 적색으로 점멸
				system("color 0f");
			}
		}
	}
	if(fill->xpos == ship->xpos && fill->ypos == ship->ypos) // 회복 아이템과 우주선의 위치가 일치하면
	{
		ship->health += fill->refill; // 회복량 적용
		fill->xpos = rand() % MAP_WIDTH; // 회복 아이템 재생성
		fill->ypos = rand() % MAP_HEIGHT;
		fill->refill = rand() % 30 + 30;

		system("color a0"); // 화면을 녹색으로 점멸
		system("color 0f");
	}
	if(ship->health > 100) // 회복 가능한 최대 체력 상한선을 100으로 설정
		ship->health = 100;
}
