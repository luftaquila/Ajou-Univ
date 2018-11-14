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

float loadSave(float *live_time, int *MAX_ROCK, float *game_speed, bool *cheatMode, char *icon, t_ship *ship, t_rock *rock, t_fill *fill, time_t *start_time, time_t *mid_time, time_t *pause_start_time, time_t *pause_time, int map[][MAP_WIDTH])
{
	char filename[100], buffer[10]; // 입력 버퍼 문자열 선언
	unsigned char key = 0;	//사용자의 키 입력을 저장할 변수
	FILE *fp; // 파일 포인터 선언
	printf("\n");
	system("dir"); // 현재 디렉토리 구성 요소 출력
	printf("\n불러올 파일 이름을 입력하세요 : "); // 파일 이름을 입력받아
	gets(filename);

	if(fp = fopen(filename, "r")) //해당 파일 읽기 모드로 열기
	{
		fgets(buffer, sizeof(buffer), fp); // 게임 저장 시 파일에 출력한 순서대로 한 줄씩 읽어 저장
		*live_time = atof(buffer);

		fgets(buffer, sizeof(buffer), fp);
		*MAX_ROCK = atoi(buffer);

		fgets(buffer, sizeof(buffer), fp);
		*game_speed = atof(buffer);

		fgets(buffer, sizeof(buffer), fp);
		*cheatMode = atoi(buffer);

		fgets(buffer, sizeof(buffer), fp);
		*start_time = atoi(buffer);

		fgets(buffer, sizeof(buffer), fp);
		*mid_time = atoi(buffer);

		fgets(buffer, sizeof(buffer), fp);
		*pause_start_time = atoi(buffer);

		fgets(buffer, sizeof(buffer), fp);
		*pause_time = atoi(buffer);

		fgets(buffer, sizeof(buffer), fp);
		ship->xpos = atoi(buffer);

		fgets(buffer, sizeof(buffer), fp);
		ship->ypos = atoi(buffer);

		fgets(buffer, sizeof(buffer), fp);
		ship->health = atoi(buffer);

		for(int i = 0; i < *MAX_ROCK; i++)
		{
			fgets(buffer, sizeof(buffer), fp);
			rock[i].xpos = atoi(buffer);

			fgets(buffer, sizeof(buffer), fp);
			rock[i].ypos = atoi(buffer);

			fgets(buffer, sizeof(buffer), fp);
			rock[i].rock_size = atoi(buffer);
		}

		fgets(buffer, sizeof(buffer), fp);
		fill->xpos = atoi(buffer);

		fgets(buffer, sizeof(buffer), fp);
		fill->ypos = atoi(buffer);

		fgets(buffer, sizeof(buffer), fp);
		fill->refill = atoi(buffer);

		for(int i = 0; i < MAP_HEIGHT; i++)
			for(int j = 0; j < MAP_WIDTH; j++)
			{
				fgets(buffer, sizeof(buffer), fp);
				map[i][j] = atoi(buffer);
			}

		fgets(buffer, sizeof(buffer), fp);
		strcpy(icon, buffer);

		fclose(fp); // 모두 읽어오면 파일 닫기.
		printf("\n처음 불러오는 세이브 파일은 로딩에 시간이 소요됩니다. 다음 화면에서 화면이 움직일 때까지 기다려 주세요.\n");
      // 로딩 후 운석들이 움직이기까지 시간이 소요되는 경우가 있어 출력.

		system("pause&&cls"); // 엔터를 누르면 화면에 게임 출력
		gotoXY(0, 0); // 커서 원점 이동
		icon[2] = '\0'; // 불러온 icon에서 개행 문자 제거

		while (ship->health > 0) // startGame함수와 동일하게 동작
		{
			if(*cheatMode == FALSE)
				updateShipHealth(ship, rock, fill, *MAX_ROCK, *live_time);
			if ((float)(clock() - *mid_time) / CLOCKS_PER_SEC > 1 / *game_speed)
			{
				moveRock(rock, *MAX_ROCK);
				*mid_time = clock();
			}

			updateMap(map, ship, rock, fill, *MAX_ROCK);
			printMap(map, ship, icon);

			*live_time = (float)(*mid_time - *start_time - *pause_time) / CLOCKS_PER_SEC;
			printf("게임 시간: \n%.3f\n", *live_time);

			if (_kbhit())
			{
				key = _getch();
				if (key == 224)
				{
					key = _getch();
					switch (key)
					{
						case LEFT_KEY:		moveShip(ship, LEFT_KEY);		break;
						case RIGHT_KEY:	moveShip(ship, RIGHT_KEY);	break;
						case UP_KEY:		moveShip(ship, UP_KEY); 		break;
						case DOWN_KEY:		moveShip(ship, DOWN_KEY); 	break;
					}
				}
				else
				{
					switch (key)
					{
						case S_KEY:
						{
							FILE *filesave;
							char filename[100];

							system("cls");
							printf("저장할 파일 이름을 입력하세요 : ");
							gets(filename);
							filesave = fopen(filename, "w");

							fprintf(filesave, "%.3f\n%d\n%.2f\n%d\n", *live_time, *MAX_ROCK, *game_speed, *cheatMode);
							fprintf(filesave, "%d\n%d\n%d\n%d\n", *start_time, *mid_time, *pause_start_time, *pause_time);
							fprintf(filesave, "%d\n%d\n%d\n", ship->xpos, ship->ypos, ship->health);

							for(int i = 0; i < *MAX_ROCK; i++)
								fprintf(filesave, "%d\n%d\n%d\n", rock[i].xpos, rock[i].ypos, rock[i].rock_size);

							fprintf(filesave, "%d\n%d\n%d\n", fill->xpos, fill->ypos, fill->refill);

							for(int i = 0; i < MAP_HEIGHT; i++)
								for(int j = 0; j < MAP_WIDTH; j++)
									fprintf(filesave, "%d\n", map[i][j]);

							fprintf(filesave, "%s\n", icon);

							printf("현재 상태가 %s 파일에 저장되었습니다.\n", filename);
							fclose(filesave);
							exit(0);
						}

						case P_KEY:
							*pause_start_time = clock();
							gotoXY(68, 18);
							printf("게임을 계속하려면 아무 키나 누르세요");
							getch();
							*pause_time += clock() - *pause_start_time;
							break;

						case ESC_KEY:
							return 0;
					}
				}
			}
		}
		gotoXY(27, 15);
		puts("GAME OVER");
		for(int i = 3; i > 0; i--)
		{
			gotoXY(17, 16);
			printf("%d초 뒤 점수 창으로 이동합니다.", i);
			Sleep(1000);
		}
		system("cls");
		return *live_time;
	}
	else // 입력한 파일 이름에 해당하는 파일이 없는 경우 에러 메시지 출력
	{
		printf("\n입력한 이름은 없는 파일입니다. ");
		system("pause");
	}
}
