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
	char filename[100], buffer[10]; // �Է� ���� ���ڿ� ����
	unsigned char key = 0;	//������� Ű �Է��� ������ ����
	FILE *fp; // ���� ������ ����
	printf("\n");
	system("dir"); // ���� ���丮 ���� ��� ���
	printf("\n�ҷ��� ���� �̸��� �Է��ϼ��� : "); // ���� �̸��� �Է¹޾�
	gets(filename);

	if(fp = fopen(filename, "r")) //�ش� ���� �б� ���� ����
	{
		fgets(buffer, sizeof(buffer), fp); // ���� ���� �� ���Ͽ� ����� ������� �� �پ� �о� ����
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

		fclose(fp); // ��� �о���� ���� �ݱ�.
		printf("\nó�� �ҷ����� ���̺� ������ �ε��� �ð��� �ҿ�˴ϴ�. ���� ȭ�鿡�� ȭ���� ������ ������ ��ٷ� �ּ���.\n");
      // �ε� �� ����� �����̱���� �ð��� �ҿ�Ǵ� ��찡 �־� ���.

		system("pause&&cls"); // ���͸� ������ ȭ�鿡 ���� ���
		gotoXY(0, 0); // Ŀ�� ���� �̵�
		icon[2] = '\0'; // �ҷ��� icon���� ���� ���� ����

		while (ship->health > 0) // startGame�Լ��� �����ϰ� ����
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
	else // �Է��� ���� �̸��� �ش��ϴ� ������ ���� ��� ���� �޽��� ���
	{
		printf("\n�Է��� �̸��� ���� �����Դϴ�. ");
		system("pause");
	}
}
