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
	strcpy(icon, "��");

	bool cheatMode = FALSE;
	int map[MAP_HEIGHT][MAP_WIDTH] = { 0 };	//map�迭���� ������ �ϳ��� ��ϵ�. ROCK(1), EMPTY(0) SHIP(2)

	time_t start_time, mid_time;  // ������ ������ �ð�, �߰��߰� �ð��� üũ�ϴ� ����
	time_t pause_start_time, pause_time = 0;
	float live_time;

	initGame();	//�⺻ �ܼ� �����Լ��� �����Ǿ���
	while(1)
	{
		t_ship ship = { MAP_HEIGHT / 2, MAP_WIDTH / 2, PLAYER_LIFE }; // ���ּ��� ó�� ���ӽ��۶� �߾ӿ��� ����, PLAYER_LIFE��ŭ�� ü�����ν���
		t_rock **rock = NULL;	// ����ü �迭 ����
		t_fill fill;

		rock = malloc(sizeof(t_rock) * MAX_ROCK);
		for(int i = 0; i < MAX_ROCK; i++)
			rock[i] = malloc(sizeof(t_rock));

		Sleep(300);	//1000ms ���� = 1�ʰ� ����
		system("cls");  //ȭ���� �����.
		printf("� ���ϱ� ����\n");
		printf("�޴��� ���� ���ּ���!\n");
		printf("\t[1] ���� ����\n\t[2] ������ Ȯ��\n\t[3] ���� ����\n\t[4] ���� �ҷ�����\n\t[0] ���� ����\n\n");      //�޴� ����
		printf("�� : ");
		scanf("%d%*c", &menu_sel); //%*c �� ����Ű ����
		switch (menu_sel)
		{
			case 0:
				printf("\n������ �����մϴ�\n");
				Sleep(2000);
				return 0;

			case 1:
				score = startGame(&game_speed, &MAX_ROCK, icon, &cheatMode, map, &ship, rock, &fill, &start_time, &mid_time, &pause_start_time, &pause_time, &live_time);
				if (score > MIN_SCORE)
					addScore(score); //�����ǿ� ��ϵǷ���, MIN_SCORE���� ���ƾ��Ѵ�. //addScore �Լ��� GameScore.txt�� �����ϴ� �Լ�
				break;

			case 2:
				viewScore("-", 0); //GameScore.txt�� ���� �о�� �� ����ϴ� �Լ�
				break;

			case 3:
				gameSettings(&game_speed, icon, &MAX_ROCK, &cheatMode); //���Ӽ������� �����ϴ� �Լ�
				break;

			case 4:
				score = loadSave(&live_time, &MAX_ROCK, &game_speed, &cheatMode, icon, &ship, rock, &fill, &start_time, &mid_time, &pause_start_time, &pause_time, map);
				if (score > MIN_SCORE)
					addScore(score); //�����ǿ� ��ϵǷ���, MIN_SCORE���� ���ƾ��Ѵ�. //addScore �Լ��� GameScore.txt�� �����ϴ� �Լ�
				break;

			default:	break;
		}
	}
	return 0;
}
