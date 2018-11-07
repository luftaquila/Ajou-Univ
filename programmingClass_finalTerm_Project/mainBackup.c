#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <stdbool.h>

#define MAP_WIDTH		30      //���� ���α���
#define MAP_HEIGHT	30      //���� ���α���
//#define MAX_ROCK	20      //�ִ� ������ ����
#define PLAYER_LIFE	100     //���ּ� �ִ�ü��
#define MIN_SCORE		5       //�����ǿ� ��ϵ� �ּ� ����
#define UNIT_SLEEP	5       //������
#define NAME_LENGHT	20
#define MAX_LIST		20

//���� ���� ��������� 0 , �����̰� ������ 1 , ���ּ��� ������ 2
#define EMPTY		0
#define ROCK		1
#define BIG_ROCK	2
#define SHIP		3
#define FILL		4

// Ű�� ��
#define ESC_KEY	27
#define RIGHT_KEY	77
#define LEFT_KEY	75
#define DOWN_KEY	80
#define UP_KEY		72
#define P_KEY		'p'
#define S_KEY		's'

HANDLE consoleHandle;	//�⺻���� �ڵ� ����
COORD console_pos = { 0, 0 };	//�⺻ ���� �ڵ� ����

typedef struct {
	int	xpos, ypos;	//���ּ��� x, y ��ǥ
	int	health;	//���ּ��� ����
} t_ship;

typedef struct {
	int	xpos, ypos;	//���� x, y ��ǥ
	int	rock_size;	//�� ũ�Ⱑ ũ��, ���ּ��� �浹�Ͽ��� �� �� ���� ���ذ� ����.
} t_rock;

typedef struct {
	int	rank;
	char	name[NAME_LENGHT];
	float	time;
} Player; //GameScore.txt���� �����͸� �ҷ��� ������ ����ü

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
	strcpy(icon, "��");

	bool cheatMode = FALSE;
	int map[MAP_HEIGHT][MAP_WIDTH] = { 0 };	//map�迭���� ������ �ϳ��� ��ϵ�. ROCK(1), EMPTY(0) SHIP(2)

	time_t start_time, mid_time;  // ������ ������ �ð�, �߰��߰� �ð��� üũ�ϴ� ����
	time_t pause_start_time, pause_time = 0;
	float live_time;

	initGame();	//�⺻ �ܼ� �����Լ��� �����Ǿ���
	while(1)
	{
		t_ship ship = { MAP_HEIGHT / 2, MAP_WIDTH / 2, PLAYER_LIFE };   // ���ּ��� ó�� ���ӽ��۶� �߾ӿ��� ����, PLAYER_LIFE��ŭ�� ü�����ν���
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

float startGame(float *game_speed, int *MAX_ROCK, char *icon, bool *cheatMode, int map[][MAP_WIDTH], t_ship *ship, t_rock *rock, t_fill *fill, time_t *start_time, time_t *mid_time, time_t *pause_start_time, time_t *pause_time, float *live_time)
{
	*start_time = clock();	//����ð��� start_time�� ��ϵȴ�.
	*mid_time = clock();

	//�������� ��ġ�� ũ�⸦ �������� �����Ѵ�.
	for (int i = 0; i < *MAX_ROCK; i++)
	{
		rock[i].rock_size = (rand() % 99) + 1; //���ط��� 1~99�����̴�.
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

	unsigned char key = 0;	//������� Ű �Է��� ������ ����
	while (ship->health > 0) //���ּ��� ü���� 0���� Ŭ�� ������ �������
	{
		if(*cheatMode == FALSE)
			updateShipHealth(ship, rock, fill, *MAX_ROCK, *live_time);
		if ((float)(clock() - *mid_time) / CLOCKS_PER_SEC > 1 / *game_speed)
		{    // (1/game_speed) �ʸ��� �����̸� �����δ�
			//���� �ӵ� game_speed �� 1��ȸ �����̰� ��ĭ�����̴��� ��ǥ, �� 1ĭ�����̴µ� �ð��� 1/game_speed
			moveRock(rock, *MAX_ROCK);	//�����̸� ���� �¿�� �����̴� �Լ�
			*mid_time = clock();	//�����̸� ������ �ð� üũ
		}

		updateMap(map, ship, rock, fill, *MAX_ROCK);    //map�迭�� ������, ���ּ� ������ ����
		printMap(map, ship, icon);	//�ٲ� ������ ����Ѵ�.

		*live_time = (float)(*mid_time - *start_time - *pause_time) / CLOCKS_PER_SEC;
		printf("���� �ð�: \n%.3f\n", *live_time);   //ȭ�鿡 �ð� ���

		if (_kbhit()) //Ű���尡 ������
		{
			key = _getch();	// Ű����κ��� �ϳ��� ���ڸ� �д´�. 0~255������ ���� ��ȯ�� �ȴ�!
			if (key == 224)  //����Ű�� ������ 224�� �������Ű�� ���� 2���� ��ȯ��, ������� ������ ����Ű�� ������ 224, 77 �̶�� �� 2���� Ȯ���ؾ���!
			{
				key = _getch(); //�ι�° ����Ű���� Ű����κ��� �д´�.
				switch (key)
				{
					case LEFT_KEY:		moveShip(ship, LEFT_KEY);		break;
					case RIGHT_KEY:	moveShip(ship, RIGHT_KEY);	break;
					case UP_KEY:		moveShip(ship, UP_KEY); 		break;
					case DOWN_KEY:		moveShip(ship, DOWN_KEY); 	break;
				}
			}
			else // ����Ű�� ������ ������, �� �Ϲ�Ű�� ������
			{
				switch (key)
				{
					case S_KEY:
					{
						FILE *filesave;
						char filename[100];

						system("cls");
						printf("������ ���� �̸��� �Է��ϼ��� : ");
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

						printf("���� ���¸� ���� %s�� ���������� �����߽��ϴ�. ���α׷��� �����մϴ�.\n\n", filename);
						fclose(filesave);
						Sleep(2000);
						exit(0);
					}

					case P_KEY:
						*pause_start_time = clock();
						gotoXY(68, 18);
						printf("������ ����Ϸ��� �ƹ� Ű�� ��������");
						getch();
						*pause_time += clock() - *pause_start_time;
						break;	//�����ϴ� �˰��� ����

					case ESC_KEY:
						return 0;	// ����
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
		printf("%d�� �� ���� â���� �̵��մϴ�.", i);
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
	printf("����� ������ %.3f�� �Դϴ�. ������ �����ϱ� ���ؼ��� �̸��� �ʿ��մϴ�.\n", score);
	printf("�̸� �� : ");
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

void viewScore(char *name, float score)    //�Լ��� ȣ��� ȭ���� ����� ȭ�鿡 GameScore.txt ���Ϸκ��� ������ ������ ȭ�鿡 ����ϴ� �Լ�
{
	FILE *fp;
	char **str, *buffer, *ptrLine, *ptrObject;
	int size, counter = 0;
	Player **player = NULL;

	fp = fopen("GameScore.csv", "r");
	if (fp == NULL)
	{
		printf("����� �����Ͱ� �����ϴ�!\n");
		Sleep(1000);
		return;
	}

	else
	{
		system("cls");
		printf("���\t�̸�\t����\n");

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
				printf("\t�� YOU");
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

void gameSettings(float *game_speed, char *icon, int *MAX_ROCK, bool *cheatMode)	//���� �ӵ� ���� & �߰����� �߰� ����
{
	int iconInput;
	char cheatModeInput[50];
	printf("Game Speed (Default : 15) : \n");
	printf("Ship Icon - ��(1) ��(2) ��(3) : \n");
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
		strcpy(icon, "��");
	else if(iconInput == 2)
		strcpy(icon, "��");
	else if(iconInput == 3)
		strcpy(icon, "��");

	if(strcmp(cheatModeInput, "CHEAT") == 0)
	{
		*cheatMode = TRUE;
		SetConsoleTitle("����ϱ� ���� - DEVELOPER MODE");
	}
	else if(strcmp(cheatModeInput, "DECHEAT") == 0)
	{
		*cheatMode = FALSE;
		SetConsoleTitle("����ϱ� ����");
	}
}

void updateMap(int map[][MAP_WIDTH], t_ship *ship, t_rock *rock, t_fill *fill, int MAX_ROCK)	//updateMap �Լ��� ���ּ��� ���� ��ġ�� map�迭�� �������ִ� ���
{
	//���� EMPTY�������� �ٲپ��ش�.
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

void printMap(int map[][MAP_WIDTH], t_ship *ship, char *icon)	//���� map�迭�� ������ ȭ�鿡 ����ִ� �Լ��� �⺻ �����ڵ�
{
	//system("cls"); ȭ���� ����� ���, ������ ȭ���� �������� ���ؼ� �Ʒ� SetConsoleCursorPostion�Լ��� ���
	SetConsoleCursorPosition(consoleHandle, console_pos);   //�� �Լ��� Ŀ���� [0,0]�� ��ġ��Ű�� ���� ���ڸ� �����, �� ������ �ۼ��Ǿ� ���� �ؿ����ִ� Ŀ���� ������ ����÷� �ٽ� �����
	printSquare(MAP_WIDTH + 2);
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		printf("��");
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (map[i][j])
			{
				case EMPTY:		printf("  "); 	 break;
				case ROCK:		printf("��");	break;
				case BIG_ROCK:	printf("��");	 break;
				case SHIP:		printf(icon);	 break;
				case FILL:		printf("��");	 break;
			}
		}
		printf("��");

		switch (i)
		{
			case 2:	printf("\t    ���� ���");	break;
			case 3:	printf("\t\tUP");	break;
			case 4:	printf("\t\t��");	break;
			case 5:	printf("\t LEFT�� �� �� RIGHT");	break;
			case 6:	printf("\t\t��");	break;
			case 7:	printf("\t       DOWN");	break;
			case 10:	printf("\t   health : %d   ", ship->health);	break;
			case 15:	printf("\t   ESC KEY ���� ����!");	break;
			case 17:	printf("\t \b\b\b\b�Ͻ������Ϸ��� pŰ�� ��������     ");	break;
			case 19: printf("   sŰ�� ������ ���� ���¸� �����ϰ� �����մϴ�"); break;
		}
		printf("\n");
	}
	printSquare(MAP_WIDTH + 2);
}

void printSquare(int num)	//�����ڵ�� num����ŭ�� �簢���� ȭ�鿡 �����
{
	for ( ; num > 0; num--)
		printf("��");
	printf("\n");
}

void updateShipHealth(t_ship *ship, t_rock *rock, t_fill *fill, int MAX_ROCK, float live_time)  //���ּ��� ���� �浹�ߴ��� �Ǻ��ϰ�, �浹�ߴٸ� ���ּ��� ü�� - ���� ũ�⸦ �Ѵ�.
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

void initGame()	//�⺻�����ڵ�
{
	CONSOLE_CURSOR_INFO info = { 100, FALSE };

	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(consoleHandle, &info);
	SetConsoleTitle("����ϱ� ����");
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
	unsigned char key = 0;	//������� Ű �Է��� ������ ����
	FILE *fp;
	printf("\n");
	system("dir");
	printf("\n�ҷ��� ���� �̸��� �Է��ϼ��� : ");
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
		printf("\nó�� �ҷ����� ���̺� ������ �ε��� �ð��� �ҿ�˴ϴ�. ���� ȭ�鿡�� ȭ���� ������ ������ ��ٷ� �ּ���. ");
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
			printf("���� �ð�: \n%.3f\n", *live_time);

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
							printf("������ ���� �̸��� �Է��ϼ��� : ");
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

							printf("���� ���°� %s ���Ͽ� ����Ǿ����ϴ�.\n", filename);
							fclose(filesave);
							exit(0);
						}

						case P_KEY:
							*pause_start_time = clock();
							gotoXY(68, 18);
							printf("������ ����Ϸ��� �ƹ� Ű�� ��������");
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
			printf("%d�� �� ���� â���� �̵��մϴ�.", i);
			Sleep(1000);
		}
		system("cls");
		return *live_time;
	}
	else
	{
		printf("\n�Է��� �̸��� ���� �����Դϴ�. ");
		system("pause");
	}
}
