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
{	//updateMap �Լ��� ���ּ��� ���� ��ġ�� map�迭�� �������ִ� ���
	//���� EMPTY�������� �ٲپ��ش�.
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
			map[i][j] = EMPTY;

	map[ship->ypos][ship->xpos] = SHIP; // �ʵ忡�� ���ּ� ��ġ�� ���ּ� ���
	map[fill->ypos][fill->xpos] = FILL; // �ʵ忡�� ȸ�� ������ ��ġ�� ���

	for (int i = 0; i < MAX_ROCK; i++) // ��� ��� ���Ͽ�
	{
		if(rock[i].rock_size > 80) // ���ط��� 80 �̻��� ���
		{ // 4ĭ ����
			map[rock[i].ypos][rock[i].xpos] = BIG_ROCK;
			map[rock[i].ypos + 1][rock[i].xpos] = BIG_ROCK;
			map[rock[i].ypos][rock[i].xpos + 1] = BIG_ROCK;
			map[rock[i].ypos + 1][rock[i].xpos + 1] = BIG_ROCK;
		}

		else
			map[rock[i].ypos][rock[i].xpos] = ROCK; // �Ϲ� ���� 1ĭ ����
	}
}

void printMap(int map[][MAP_WIDTH], t_ship *ship, char *icon)
{	//���� map�迭�� ������ ȭ�鿡 ����ִ� �Լ��� �⺻ �����ڵ�
   COORD console_pos = { 0, 0 };	//�⺻ ���� �ڵ� ����
	//system("cls"); ȭ���� ����� ���, ������ ȭ���� �������� ���ؼ� �Ʒ� SetConsoleCursorPostion�Լ��� ���
	SetConsoleCursorPosition(consoleHandle, console_pos);   //�� �Լ��� Ŀ���� [0,0]�� ��ġ��Ű�� ���� ���ڸ� �����, �� ������ �ۼ��Ǿ� ���� �ؿ����ִ� Ŀ���� ������ ����÷� �ٽ� �����
	printSquare(MAP_WIDTH + 2); // �ʵ� ��� ��� ���
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		printf("��"); // �ʵ� ���� ��� ���
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (map[i][j])
			{ // �ʵ� ��� ���
				case EMPTY:		printf("  "); 	 break;
				case ROCK:		printf("��");	break;
				case BIG_ROCK:	printf("��");	 break;
				case SHIP:		printf(icon);	 break;
				case FILL:		printf("��");	 break;
			}
		}
		printf("��"); // �ʵ� ���� ��� ���

		switch (i) // ȭ�� ���� �������̽� ���
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
	printSquare(MAP_WIDTH + 2); // �ʵ� �ϴ� ��� ���
}

void printSquare(int num)	//�����ڵ�� num����ŭ�� �簢���� ȭ�鿡 �����
{
	for ( ; num > 0; num--)
		printf("��");
	printf("\n");
}

void moveRock(t_rock *rock, int MAX_ROCK)
{
	int cng_x, cng_y; // ��ȭ�� ���� ����
	for(int i = 0; i < MAX_ROCK; i++) // ��� ��� ���Ͽ�
	{
		cng_x = rand() % 3 - 1; // x�� ��ȭ��, y�� ��ȭ�� -1, 0, 1 �� �ϳ��� ����
		cng_y = rand() % 3 - 1;

		rock[i].xpos += cng_x; // ��ǥ�� ��ȭ�� ����
		rock[i].ypos += cng_y;

		if(rock[i].rock_size < 80) // ���ط��� 80 �̻��� 4ĭ¥�� ��� ���ؼ� �� �ٱ����� ��Ż�� ����
		{
			if(rock[i].xpos < 0 || rock[i].xpos > 29)	rock[i].xpos -= cng_x * 2;
			if(rock[i].ypos < 0 || rock[i].ypos > 29)	rock[i].ypos -= cng_y * 2;
		}

		else // ���ط� 80 �̸� ��� ���ؼ� �� ��Ż�� ����
		{
			if(rock[i].xpos < 0 || rock[i].xpos > 28)	rock[i].xpos -= cng_x * 2;
			if(rock[i].ypos < 0 || rock[i].ypos > 28)	rock[i].ypos -= cng_y * 2;
		}
	}
}
