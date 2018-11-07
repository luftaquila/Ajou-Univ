#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <stdbool.h>

#define MAP_WIDTH		30      //맵의 가로길이
#define MAP_HEIGHT	30      //맵의 세로길이
//#define MAX_ROCK	20      //최대 돌맹이 개수
#define PLAYER_LIFE	100     //우주선 최대체력
#define MIN_SCORE		5       //점수판에 기록될 최소 점수
#define UNIT_SLEEP	5       //딜레이
#define NAME_LENGHT	20
#define MAX_LIST		20

//맵의 상태 비어있으면 0 , 돌맹이가 있으면 1 , 우주선이 있으면 2
#define EMPTY		0
#define ROCK		1
#define BIG_ROCK	2
#define SHIP		3
#define FILL		4

// 키의 값
#define ESC_KEY	27
#define RIGHT_KEY	77
#define LEFT_KEY	75
#define DOWN_KEY	80
#define UP_KEY		72
#define P_KEY		'p'
#define S_KEY		's'

HANDLE consoleHandle;	//기본제공 코드 내용
COORD console_pos = { 0, 0 };	//기본 제공 코드 내용

typedef struct {
	int	xpos, ypos;	//우주선의 x, y 좌표
	int	health;	//우주선의 수명
} t_ship;

typedef struct {
	int	xpos, ypos;	//돌의 x, y 좌표
	int	rock_size;	//돌 크기가 크면, 우주선과 충돌하였을 때 더 많은 피해가 간다.
} t_rock;

typedef struct {
	int	rank;
	char	name[NAME_LENGHT];
	float	time;
} Player; //GameScore.txt에서 데이터를 불러와 저장할 구조체

typedef struct {
	int xpos, ypos;
	int refill;
} t_fill;

float startGame(float *game_speed, int *MAX_ROCK, char *icon, bool *cheatMode, int map[][MAP_WIDTH], t_ship *ship, t_rock *rock, t_fill *fill, time_t *start_time, time_t *mid_time, time_t *pause_start_time, time_t *pause_time, float *live_time);
void initGame();

void gameSettings(float *game_speed, char *icon, int *MAX_ROCK, bool *cheatMode);

void viewScore(char *name, float score);
void addScore(float score);

void updateShipHealth(t_ship *, t_rock *, t_fill *, int MAX_ROCK, float live_time);

void moveShip(t_ship *ship, int direction);
void moveRock(t_rock *rock, int MAX_ROCK);

void printMap(int map[][MAP_WIDTH], t_ship *ship, char *icon);
void updateMap(int map[][MAP_WIDTH], t_ship *ship, t_rock *rock, t_fill *fill, int MAX_ROCK);
void printSquare(int num);

void gotoXY(int x, int y);
float loadSave(float *live_time, int *MAX_ROCK, float *game_speed, bool *cheatMode, char *icon, t_ship *ship, t_rock *rock, t_fill *fill, time_t *start_time, time_t *mid_time, time_t *pause_start_time, time_t *pause_time, int map[][MAP_WIDTH]);

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
		t_ship ship = { MAP_HEIGHT / 2, MAP_WIDTH / 2, PLAYER_LIFE };   // 우주선이 처음 게임시작때 중앙에서 시작, PLAYER_LIFE만큼의 체력으로시작
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
		if(rock[i].xpos == 15 && rock[i].ypos == 15)
		{
			rock[i].xpos = rand() % MAP_WIDTH;
			rock[i].ypos = rand() % MAP_HEIGHT;
		}
	}

	fill->xpos = rand() % MAP_WIDTH;
	fill->ypos = rand() % MAP_HEIGHT;
	fill->refill = rand() % 30 + 30;

	unsigned char key = 0;	//사용자의 키 입력을 저장할 변수
	while (ship->health > 0) //우주선의 체력이 0보다 클때 게임을 계속진행
	{
		if(*cheatMode == FALSE)
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
		printf("게임 시간: \n%.3f\n", *live_time);   //화면에 시간 출력

		if (_kbhit()) //키보드가 눌리면
		{
			key = _getch();	// 키보드로부터 하나의 숫자를 읽는다. 0~255까지의 수가 반환이 된다!
			if (key == 224)  //방향키가 눌리면 224와 방향고유키의 값이 2개가 반환됨, 예를들어 오른쪽 방향키를 누를시 224, 77 이라는 값 2개를 확인해야함!
			{
				key = _getch(); //두번째 방향키값을 키보드로부터 읽는다.
				switch (key)
				{
					case LEFT_KEY:		moveShip(ship, LEFT_KEY);		break;
					case RIGHT_KEY:	moveShip(ship, RIGHT_KEY);	break;
					case UP_KEY:		moveShip(ship, UP_KEY); 		break;
					case DOWN_KEY:		moveShip(ship, DOWN_KEY); 	break;
				}
			}
			else // 방향키가 눌리지 않으면, 즉 일반키가 눌리면
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

						printf("현재 상태를 파일 %s에 성공적으로 저장했습니다. 프로그램을 종료합니다.\n\n", filename);
						fclose(filesave);
						Sleep(2000);
						exit(0);
					}

					case P_KEY:
						*pause_start_time = clock();
						gotoXY(68, 18);
						printf("게임을 계속하려면 아무 키나 누르세요");
						getch();
						*pause_time += clock() - *pause_start_time;
						break;	//중지하는 알고리즘 구현

					case ESC_KEY:
						return 0;	// 종료
				}
			}
		}
		Sleep(UNIT_SLEEP);
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

void addScore(float score)
{
	FILE *fp;
	char name[NAME_LENGHT], **str, *buffer, *ptrLine, *ptrObject;
	int size, counter = 0;
	Player **player = NULL, *temp;

	fflush(stdin);
	printf("당신의 점수는 %.3f점 입니다. 점수를 저장하기 위해서는 이름이 필요합니다.\n", score);
	printf("이름 ☞ : ");
	scanf("%s", name);

	fp = fopen("GameScore.csv", "a+");

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);

	buffer = malloc(size + 1);
	memset(buffer, 0, size + 1);

	fseek(fp, 0, SEEK_SET);
	fread(buffer, size, 1, fp);

	for (int i = 0; i < size; i++)
	{
		if (buffer[i] == '\n')
			counter++;
	}

	player = calloc(counter + 2, sizeof(*player));
	str = calloc(counter + 2, sizeof(*str));

	ptrLine = strtok(buffer, "\n");
	for (int i = 0; ptrLine != NULL; i++)
	{
		str[i] = ptrLine;
		ptrLine = strtok(NULL, "\n");
	}

	for (int i = 0; str[i]; i++)
	{
		player[i] = malloc(sizeof(**player));

		ptrObject = strtok(str[i], ",");
		player[i]->rank = atoi(ptrObject);

		ptrObject = strtok(NULL, ",");
		strcpy(player[i]->name, ptrObject);

		ptrObject = strtok(NULL, ",");
		player[i]->time = atof(ptrObject);
	}

	player[counter] = malloc(sizeof(**player));
	player[counter]->rank = 0;
	strcpy(player[counter]->name, name);
	player[counter]->time = score;

	for (int i = 0; i < counter + 1; i++)
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

	for (int i = 0; i < counter + 1; i++)
		player[i]->rank = i + 1;

	fp = fopen("GameScore.csv", "w");

	for (int i = 0; player[i]; i++)
		fprintf(fp, "%d,%s,%.3f\n", player[i]->rank, player[i]->name, player[i]->time);
	fclose(fp);

	free(player);
	free(str);

	viewScore(&name, score);
}

void viewScore(char *name, float score)    //함수를 호출시 화면을 지우고 화면에 GameScore.txt 파일로부터 점수를 읽은후 화면에 출력하는 함수
{
	FILE *fp;
	char **str, *buffer, *ptrLine, *ptrObject;
	int size, counter = 0;
	Player **player = NULL;

	fp = fopen("GameScore.csv", "r");
	if (fp == NULL)
	{
		printf("저장된 데이터가 없습니다!\n");
		Sleep(1000);
		return;
	}

	else
	{
		system("cls");
		printf("등수\t이름\t점수\n");

		fseek(fp, 0, SEEK_END);
		size = ftell(fp);

		buffer = malloc(size + 1);
		memset(buffer, 0, size + 1);

		fseek(fp, 0, SEEK_SET);
		fread(buffer, size, 1, fp);

		for (int i = 0; i < size; i++)
		{
			if (buffer[i] == '\n')
				counter++;
		}

		player = calloc(counter + 2, sizeof(*player));
		str = calloc(counter + 2, sizeof(*str));

		ptrLine = strtok(buffer, "\n");
		for (int i = 0; ptrLine != NULL; i++)
		{
			str[i] = ptrLine;
			ptrLine = strtok(NULL, "\n");
		}
		fclose(fp);

		for (int i = 0; str[i]; i++)
		{
			player[i] = malloc(sizeof(**player));

			ptrObject = strtok(str[i], ",");
			player[i]->rank = atoi(ptrObject);

			ptrObject = strtok(NULL, ",");
			strcpy(player[i]->name, ptrObject);

			ptrObject = strtok(NULL, ",");
			player[i]->time = atof(ptrObject);
		}

		for (int i = 0; player[i]; i++)
		{
			printf(" %2d\t%s\t%.3f", player[i]->rank, player[i]->name, player[i]->time);
			if((player[i]->time == score))
				printf("\t← YOU");
			printf("\n");
		}

		free(player);
		free(str);

		system("PAUSE && cls");
	}
}

void moveShip(t_ship *ship, int direction)
{
	switch (direction)
	{
		case LEFT_KEY:		if (ship->xpos > 0)	ship->xpos--;	break;
		case RIGHT_KEY:	if (ship->xpos < 29)	ship->xpos++;	break;
		case UP_KEY:		if (ship->ypos > 0)	ship->ypos--;	break;
		case DOWN_KEY:		if (ship->ypos < 29)	ship->ypos++;	break;
	}
}

void gameSettings(float *game_speed, char *icon, int *MAX_ROCK, bool *cheatMode)	//게임 속도 수정 & 추가적인 추가 설정
{
	int iconInput;
	char cheatModeInput[50];
	printf("Game Speed (Default : 15) : \n");
	printf("Ship Icon - ▲(1) ◈(2) ★(3) : \n");
	printf("Number of rocks (Default : 30) : \n");
	printf("Toggle cheat mode : \n");
	gotoXY(28, 9);
	scanf("%f", game_speed);

	gotoXY(32, 10);
	scanf("%d", &iconInput);

	gotoXY(33, 11);
	scanf("%d", MAX_ROCK);
	fflush(stdin);

	gotoXY(20, 12);
	gets(cheatModeInput);

	if(iconInput == 1)
		strcpy(icon, "▲");
	else if(iconInput == 2)
		strcpy(icon, "◈");
	else if(iconInput == 3)
		strcpy(icon, "★");

	if(strcmp(cheatModeInput, "CHEAT") == 0)
	{
		*cheatMode = TRUE;
		SetConsoleTitle("운석피하기 게임 - DEVELOPER MODE");
	}
	else if(strcmp(cheatModeInput, "DECHEAT") == 0)
	{
		*cheatMode = FALSE;
		SetConsoleTitle("운석피하기 게임");
	}
}

void updateMap(int map[][MAP_WIDTH], t_ship *ship, t_rock *rock, t_fill *fill, int MAX_ROCK)	//updateMap 함수는 우주선과 돌의 위치를 map배열에 기입해주는 기능
{
	//맵을 EMPTY영역으로 바꾸어준다.
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
			map[i][j] = EMPTY;

	map[ship->ypos][ship->xpos] = SHIP;
	map[fill->ypos][fill->xpos] = FILL;

	for (int i = 0; i < MAX_ROCK; i++)
	{
		if(rock[i].rock_size > 80)
		{
			map[rock[i].ypos][rock[i].xpos] = BIG_ROCK;
			map[rock[i].ypos + 1][rock[i].xpos] = BIG_ROCK;
			map[rock[i].ypos][rock[i].xpos + 1] = BIG_ROCK;
			map[rock[i].ypos + 1][rock[i].xpos + 1] = BIG_ROCK;
		}

		else
			map[rock[i].ypos][rock[i].xpos] = ROCK;
	}
}

void printMap(int map[][MAP_WIDTH], t_ship *ship, char *icon)	//현재 map배열의 정보를 화면에 띄워주는 함수로 기본 제공코드
{
	//system("cls"); 화면을 지우는 명령, 하지만 화면이 깜빡임이 심해서 아래 SetConsoleCursorPostion함수를 사용
	SetConsoleCursorPosition(consoleHandle, console_pos);   //이 함수는 커서를 [0,0]에 위치시키고 기존 문자를 덮어씌움, 즉 내용이 작성되어 가장 밑에가있는 커서를 맨위로 끌어올려 다시 덮어씌움
	printSquare(MAP_WIDTH + 2);
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		printf("□");
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (map[i][j])
			{
				case EMPTY:		printf("  "); 	 break;
				case ROCK:		printf("＊");	break;
				case BIG_ROCK:	printf("●");	 break;
				case SHIP:		printf(icon);	 break;
				case FILL:		printf("♣");	 break;
			}
		}
		printf("□");

		switch (i)
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
	printSquare(MAP_WIDTH + 2);
}

void printSquare(int num)	//제공코드로 num개만큼의 사각형을 화면에 띄워줌
{
	for ( ; num > 0; num--)
		printf("□");
	printf("\n");
}

void updateShipHealth(t_ship *ship, t_rock *rock, t_fill *fill, int MAX_ROCK, float live_time)  //우주선이 돌과 충돌했는지 판별하고, 충돌했다면 우주선의 체력 - 돌의 크기를 한다.
{
	if(live_time < 3)
		return;

	for (int i = 0; i < MAX_ROCK; i++)
	{
		if(rock[i].rock_size < 80)
		{
			if ((ship->xpos == rock[i].xpos) && (ship->ypos == rock[i].ypos))
			{
				ship->health -= rock[i].rock_size;
				system("color e0");
				system("color 0f");
			}
		}

		else
		{
			if (((ship->xpos == rock[i].xpos) || (ship->xpos == rock[i].xpos + 1)) && ((ship->ypos == rock[i].ypos) || (ship->ypos == rock[i].ypos + 1)))
			{
				ship->health -= rock[i].rock_size;
				system("color cf");
				system("color 0f");
			}
		}
	}
	if(fill->xpos == ship->xpos && fill->ypos == ship->ypos)
	{
		ship->health += fill->refill;
		fill->xpos = rand() % MAP_WIDTH;
		fill->ypos = rand() % MAP_HEIGHT;
		fill->refill = rand() % 30 + 30;

		system("color a0");
		system("color 0f");
	}
	if(ship->health > 100)
		ship->health = 100;
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

void moveRock(t_rock *rock, int MAX_ROCK)
{
	int cng_x, cng_y;
	for(int i = 0; i < MAX_ROCK; i++)
	{
		cng_x = rand() % 3 - 1;
		cng_y = rand() % 3 - 1;

		rock[i].xpos += cng_x;
		rock[i].ypos += cng_y;

		if(rock[i].rock_size < 80)
		{
			if(rock[i].xpos < 0 || rock[i].xpos > 29)	rock[i].xpos -= cng_x * 2;
			if(rock[i].ypos < 0 || rock[i].ypos > 29)	rock[i].ypos -= cng_y * 2;
		}

		else
		{
			if(rock[i].xpos < 0 || rock[i].xpos > 28)	rock[i].xpos -= cng_x * 2;
			if(rock[i].ypos < 0 || rock[i].ypos > 28)	rock[i].ypos -= cng_y * 2;
		}
	}
}

void gotoXY(int x, int y)
{
	COORD cursor;

	cursor.X = x;
	cursor.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
}

float loadSave(float *live_time, int *MAX_ROCK, float *game_speed, bool *cheatMode, char *icon, t_ship *ship, t_rock *rock, t_fill *fill, time_t *start_time, time_t *mid_time, time_t *pause_start_time, time_t *pause_time, int map[][MAP_WIDTH])
{
	char filename[100], buffer[10];
	unsigned char key = 0;	//사용자의 키 입력을 저장할 변수
	FILE *fp;
	printf("\n");
	system("dir");
	printf("\n불러올 파일 이름을 입력하세요 : ");
	gets(filename);

	if(fp = fopen(filename, "r"))
	{
		fgets(buffer, sizeof(buffer), fp);
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

		fclose(fp);
		printf("\n처음 불러오는 세이브 파일은 로딩에 시간이 소요됩니다. 다음 화면에서 화면이 움직일 때까지 기다려 주세요. ");
		system("pause&&cls");
		gotoXY(0, 0);
		icon[2] = '\0';

		while (ship->health > 0)
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
	else
	{
		printf("\n입력한 이름은 없는 파일입니다. ");
		system("pause");
	}
}
