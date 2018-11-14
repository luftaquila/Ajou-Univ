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
	*start_time = clock();	//����ð��� start_time�� ��ϵȴ�.
	*mid_time = clock();

	//�������� ��ġ�� ũ�⸦ �������� �����Ѵ�.
	for (int i = 0; i < *MAX_ROCK; i++)
	{
		rock[i].rock_size = (rand() % 99) + 1; //���ط��� 1~99�����̴�.
		rock[i].xpos = rand() % MAP_WIDTH;
		rock[i].ypos = rand() % MAP_HEIGHT;
		if(rock[i].xpos == 15 && rock[i].ypos == 15) // ��� �ʱ� ��ġ�� ���ּ� �ʱ� �������� ������
		{
			rock[i].xpos = rand() % MAP_WIDTH; // ��ġ �缳��
			rock[i].ypos = rand() % MAP_HEIGHT;
		}
	}

	fill->xpos = rand() % MAP_WIDTH;	// ȸ�� �������� ��ġ �� ȸ������ �������� ����.
	fill->ypos = rand() % MAP_HEIGHT;
	fill->refill = rand() % 30 + 30;

	unsigned char key = 0;	//������� Ű �Է��� ������ ����
	while (ship->health > 0) //���ּ��� ü���� 0���� Ŭ�� ������ �������
	{
		if(*cheatMode == FALSE)	// ������ ��尡 ��Ȱ��ȭ �� ��쿡�� updateShipHealth �Լ� ����
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
		// p Ű�� ���� ������ �ð��� ������ �÷��� �ð� ���
		printf("���� �ð�: \n%.3f\n", *live_time);   //ȭ�鿡 �ð� ���

		if (_kbhit()) //Ű���尡 ������
		{
			key = _getch();	// Ű����κ��� �ϳ��� ���ڸ� �д´�. 0~255������ ���� ��ȯ�� �ȴ�!
			if (key == 224)  	//����Ű�� ������ 224�� �������Ű�� ���� 2���� ��ȯ��,
			{						// ������� ������ ����Ű�� ������ 224, 77 �̶�� �� 2���� Ȯ���ؾ���!
				key = _getch(); //�ι�° ����Ű���� Ű����κ��� �д´�.
				switch (key)
				{ // moveShip �Լ��� ������ ����� ���ּ��� ������ ����
					case LEFT_KEY:		moveShip(ship, LEFT_KEY);		break;
					case RIGHT_KEY:	moveShip(ship, RIGHT_KEY);		break;
					case UP_KEY:		moveShip(ship, UP_KEY); 		break;
					case DOWN_KEY:		moveShip(ship, DOWN_KEY); 		break;
				}
			}
			else // ����Ű�� ������ ������, �� �Ϲ�Ű�� ������
			{
				switch (key)
				{
					case S_KEY: // s Ű�� ���� ���
					{
						FILE *filesave; // ���� ������ ����
						char filename[100]; // ���� �̸��� �Է¹��� ���ڿ� ����

						system("cls"); // ȭ�� �ʱ�ȭ
						printf("������ ���� �̸��� �Է��ϼ��� : "); // ���� �̸� �Է�
						gets(filename);
						filesave = fopen(filename, "w"); // �Է��� �̸����� ������ �����ϰ� ���� ���� ����

						// ��� �÷��� ���¿� ������ ���Ͽ� ���
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
						fclose(filesave); // ���� �ݰ� ���α׷� ����
						Sleep(2000);
						exit(0);
					}

					case P_KEY: // p Ű�� ������
						*pause_start_time = clock(); // �Ͻ����� ���� �ð� ����
						gotoXY(68, 18); // Ŀ���� �ű�� �ȳ� ���� ���
						printf("������ ����Ϸ��� �ƹ� Ű�� ��������");
						getch(); // �ƹ� Ű�� ���� ������ ���
						*pause_time += clock() - *pause_start_time; // �Ͻ������� �ð� ���
						break;	//�����ϴ� �˰��� ����

					case ESC_KEY:
						return 0;	// ����
				}
			}
		}
		Sleep(UNIT_SLEEP);
	}
	gotoXY(27, 15); // ü���� 0 ������ ��������
	puts("GAME OVER"); // Ŀ���� �Ű� ���� ���� ���� ���
	for(int i = 3; i > 0; i--)
	{
		gotoXY(17, 16);
		printf("%d�� �� ���� â���� �̵��մϴ�.", i);
		Sleep(1000);
	}
	system("cls");
	return *live_time; // ȭ���� ����� ���� �ð� ��ȯ
}

void gameSettings(float *game_speed, char *icon, int *MAX_ROCK, bool *cheatMode)	//���� �ӵ� ���� & �߰����� �߰� ����
{
	int iconInput; // ���� �Է¹��� ���� ����
	char cheatModeInput[50];
	printf("Game Speed (Default : 15) : \n"); // ���� �׸� ���
	printf("Ship Icon - ��(1) ��(2) ��(3) : \n");
	printf("Number of rocks (Default : 30) : \n");
	printf("Toggle cheat mode : \n");
	gotoXY(28, 9); // Ŀ���� �Ű� �� ���� �׸� �Է�
	scanf("%f", game_speed);

	gotoXY(32, 10);
	scanf("%d", &iconInput);

	gotoXY(33, 11);
	scanf("%d", MAX_ROCK);
	fflush(stdin);

	gotoXY(20, 12);
	gets(cheatModeInput);

	if(iconInput == 1) // ������ �Է¿� ���� ������ ����
		strcpy(icon, "��");
	else if(iconInput == 2)
		strcpy(icon, "��");
	else if(iconInput == 3)
		strcpy(icon, "��");

	if(strcmp(cheatModeInput, "CHEAT") == 0) // ������ ��� Ȱ��ȭ ���� �Է½�
	{
		*cheatMode = TRUE; // ������ ��� Ȱ��ȭ
		SetConsoleTitle("����ϱ� ���� - DEVELOPER MODE"); // �ܼ� Ÿ��Ʋ ����
	}
	else if(strcmp(cheatModeInput, "DECHEAT") == 0) // ��Ȱ��ȭ ���� �Է½� ��Ȱ��ȭ
	{
		*cheatMode = FALSE;
		SetConsoleTitle("����ϱ� ����");
	}
}

void gotoXY(int x, int y) // windows.h�� ����� ����ü COORD�� �̿��Ͽ� ���� ��ǥ�� Ŀ�� �̵�
{
	COORD cursor;

	cursor.X = x;
	cursor.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
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
