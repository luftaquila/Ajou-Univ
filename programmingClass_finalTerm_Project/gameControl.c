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

float startGame(float *game_speed, int *MAX_ROCK, char *icon, bool *cheatMode, int map[][MAP_WIDTH], t_ship *ship, t_rock *rock, t_fill *fill, time_t *start_time, time_t *mid_time, time_t *pause_start_time, time_t *pause_time, float *live_time)
{
	*start_time = clock();	//현재시간이 start_time에 기록된다.
	*mid_time = clock();

	//돌맹이의 위치와 크기를 랜덤으로 배정한다.
	for (int i = 0; i < *MAX_ROCK; i++)
	{
		rock[i].rock_size = (rand() % 99) + 1; //피해량이 1~99까지이다.
		rock[i].xpos = rand() % MAP_WIDTH;
		rock[i].ypos = rand() % MAP_HEIGHT;
		if(rock[i].xpos == 15 && rock[i].ypos == 15) // 운석의 초기 위치가 우주선 초기 시작점과 같으면
		{
			rock[i].xpos = rand() % MAP_WIDTH; // 위치 재설정
			rock[i].ypos = rand() % MAP_HEIGHT;
		}
	}

	fill->xpos = rand() % MAP_WIDTH;	// 회복 아이템의 위치 및 회복량을 무작위로 결정.
	fill->ypos = rand() % MAP_HEIGHT;
	fill->refill = rand() % 30 + 30;

	unsigned char key = 0;	//사용자의 키 입력을 저장할 변수
	while (ship->health > 0) //우주선의 체력이 0보다 클때 게임을 계속진행
	{
		if(*cheatMode == FALSE)	// 개발자 모드가 비활성화 된 경우에만 updateShipHealth 함수 실행
			updateShipHealth(ship, rock, fill, *MAX_ROCK, *live_time);
		if ((float)(clock() - *mid_time) / CLOCKS_PER_SEC > 1 / *game_speed)
		{    // (1/game_speed) 초마다 돌맹이를 움직인다
			//게임 속도 game_speed 는 1초회 돌맹이가 몇칸움직이는지 지표, 즉 1칸움직이는데 시간은 1/game_speed
			moveRock(rock, *MAX_ROCK);	//돌맹이를 상하 좌우로 움직이는 함수
			*mid_time = clock();	//돌맹이를 움직인 시간 체크
		}

		updateMap(map, ship, rock, fill, *MAX_ROCK);    //map배열에 돌맹이, 우주선 정보를 저장
		printMap(map, ship, icon);	//바뀐 정보를 출력한다.

		*live_time = (float)(*mid_time - *start_time - *pause_time) / CLOCKS_PER_SEC;
		// p 키를 눌러 정지한 시간을 제외한 플레이 시간 계산
		printf("게임 시간: \n%.3f\n", *live_time);   //화면에 시간 출력

		if (_kbhit()) //키보드가 눌리면
		{
			key = _getch();	// 키보드로부터 하나의 숫자를 읽는다. 0~255까지의 수가 반환이 된다!
			if (key == 224)  	//방향키가 눌리면 224와 방향고유키의 값이 2개가 반환됨,
			{						// 예를들어 오른쪽 방향키를 누를시 224, 77 이라는 값 2개를 확인해야함!
				key = _getch(); //두번째 방향키값을 키보드로부터 읽는다.
				switch (key)
				{ // moveShip 함수에 움직인 방향과 우주선의 정보를 전달
					case LEFT_KEY:		moveShip(ship, LEFT_KEY);		break;
					case RIGHT_KEY:	moveShip(ship, RIGHT_KEY);		break;
					case UP_KEY:		moveShip(ship, UP_KEY); 		break;
					case DOWN_KEY:		moveShip(ship, DOWN_KEY); 		break;
				}
			}
			else // 방향키가 눌리지 않으면, 즉 일반키가 눌리면
			{
				switch (key)
				{
					case S_KEY: // s 키가 눌린 경우
					{
						FILE *filesave; // 파일 포인터 선언
						char filename[100]; // 파일 이름을 입력받을 문자열 선언

						system("cls"); // 화면 초기화
						printf("저장할 파일 이름을 입력하세요 : "); // 파일 이름 입력
						gets(filename);
						filesave = fopen(filename, "w"); // 입력한 이름으로 파일을 생성하고 쓰기 모드로 접근

						// 모든 플레이 상태와 설정을 파일에 출력
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

						printf("현재 상태를 파일 %s에 성공적으로 저장했습니다. 프로그램을 종료합니다.\n\n", filename);
						fclose(filesave); // 파일 닫고 프로그램 종료
						Sleep(2000);
						exit(0);
					}

					case P_KEY: // p 키가 눌리면
						*pause_start_time = clock(); // 일시정지 개시 시간 측정
						gotoXY(68, 18); // 커서를 옮기고 안내 문구 출력
						printf("게임을 계속하려면 아무 키나 누르세요");
						getch(); // 아무 키나 누를 때까지 대기
						*pause_time += clock() - *pause_start_time; // 일시정지한 시간 계산
						break;	//중지하는 알고리즘 구현

					case ESC_KEY:
						return 0;	// 종료
				}
			}
		}
		Sleep(UNIT_SLEEP);
	}
	gotoXY(27, 15); // 체력이 0 밑으로 떨어지면
	puts("GAME OVER"); // 커서를 옮겨 게임 종료 문구 출력
	for(int i = 3; i > 0; i--)
	{
		gotoXY(17, 16);
		printf("%d초 뒤 점수 창으로 이동합니다.", i);
		Sleep(1000);
	}
	system("cls");
	return *live_time; // 화면을 지우고 생존 시간 반환
}

void gameSettings(float *game_speed, char *icon, int *MAX_ROCK, bool *cheatMode)	//게임 속도 수정 & 추가적인 추가 설정
{
	int iconInput; // 설정 입력받을 변수 선언
	char cheatModeInput[50];
	printf("Game Speed (Default : 15) : \n"); // 설정 항목 출력
	printf("Ship Icon - ▲(1) ◈(2) ★(3) : \n");
	printf("Number of rocks (Default : 30) : \n");
	printf("Toggle cheat mode : \n");
	gotoXY(28, 9); // 커서를 옮겨 각 설정 항목 입력
	scanf("%f", game_speed);

	gotoXY(32, 10);
	scanf("%d", &iconInput);

	gotoXY(33, 11);
	scanf("%d", MAX_ROCK);
	fflush(stdin);

	gotoXY(20, 12);
	gets(cheatModeInput);

	if(iconInput == 1) // 아이콘 입력에 따라 아이콘 변경
		strcpy(icon, "▲");
	else if(iconInput == 2)
		strcpy(icon, "◈");
	else if(iconInput == 3)
		strcpy(icon, "★");

	if(strcmp(cheatModeInput, "CHEAT") == 0) // 개발자 모드 활성화 문구 입력시
	{
		*cheatMode = TRUE; // 개발자 모드 활성화
		SetConsoleTitle("운석피하기 게임 - DEVELOPER MODE"); // 콘솔 타이틀 변경
	}
	else if(strcmp(cheatModeInput, "DECHEAT") == 0) // 비활성화 문구 입력시 비활성화
	{
		*cheatMode = FALSE;
		SetConsoleTitle("운석피하기 게임");
	}
}

void gotoXY(int x, int y) // windows.h에 선언된 구조체 COORD를 이용하여 지정 좌표로 커서 이동
{
	COORD cursor;

	cursor.X = x;
	cursor.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
}

void initGame()	//기본제공코드
{
	CONSOLE_CURSOR_INFO info = { 100, FALSE };

	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(consoleHandle, &info);
	SetConsoleTitle("운석피하기 게임");
	system("mode con: cols=120 lines=60");
	srand((unsigned int)time(NULL));
}
