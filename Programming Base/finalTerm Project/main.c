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

int main()
{
	int menu_sel = 0, MAX_ROCK = 30;
	float score = 0, game_speed = 15;
	char icon[2];
	strcpy(icon, "▲");

	bool cheatMode = FALSE;
	int map[MAP_HEIGHT][MAP_WIDTH] = { 0 };	//map배열에는 다음중 하나가 기록됨. ROCK(1), EMPTY(0) SHIP(2)

	time_t start_time, mid_time;  // 게임을 시작한 시간, 중간중간 시간을 체크하는 변수
	time_t pause_start_time, pause_time = 0;
	float live_time;

	initGame();	//기본 콘솔 세팅함수로 제공되어짐
	while(1)
	{
		t_ship ship = { MAP_HEIGHT / 2, MAP_WIDTH / 2, PLAYER_LIFE }; // 우주선이 처음 게임시작때 중앙에서 시작, PLAYER_LIFE만큼의 체력으로시작
		t_rock **rock = NULL;	// 구조체 배열 생성
		t_fill fill;

		rock = malloc(sizeof(t_rock) * MAX_ROCK);
		for(int i = 0; i < MAX_ROCK; i++)
			rock[i] = malloc(sizeof(t_rock));

		Sleep(300);	//1000ms 정지 = 1초간 정지
		system("cls");  //화면을 지운다.
		printf("운석 피하기 게임\n");
		printf("메뉴를 선택 해주세요!\n");
		printf("\t[1] 게임 시작\n\t[2] 점수판 확인\n\t[3] 게임 설정\n\t[4] 게임 불러오기\n\t[0] 게임 종료\n\n");      //메뉴 선택
		printf("☞ : ");
		scanf("%d%*c", &menu_sel); //%*c 는 엔터키 제외
		switch (menu_sel)
		{
			case 0:
				printf("\n게임을 종료합니다\n");
				Sleep(2000);
				return 0;

			case 1:
				score = startGame(&game_speed, &MAX_ROCK, icon, &cheatMode, map, &ship, rock, &fill, &start_time, &mid_time, &pause_start_time, &pause_time, &live_time);
				if (score > MIN_SCORE)
					addScore(score); //점수판에 기록되려면, MIN_SCORE보다 높아야한다. //addScore 함수는 GameScore.txt에 저장하는 함수
				break;

			case 2:
				viewScore("-", 0); //GameScore.txt로 부터 읽어온 후 출력하는 함수
				break;

			case 3:
				gameSettings(&game_speed, icon, &MAX_ROCK, &cheatMode); //게임설정관련 수정하는 함수
				break;

			case 4:
				score = loadSave(&live_time, &MAX_ROCK, &game_speed, &cheatMode, icon, &ship, rock, &fill, &start_time, &mid_time, &pause_start_time, &pause_time, map);
				if (score > MIN_SCORE)
					addScore(score); //점수판에 기록되려면, MIN_SCORE보다 높아야한다. //addScore 함수는 GameScore.txt에 저장하는 함수
				break;

			default:	break;
		}
	}
	return 0;
}
