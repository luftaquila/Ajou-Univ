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

void moveShip(t_ship *ship, int direction) // ���ּ� ����ü�� ���� ������ ���ڷ� ����
{
	switch (direction) // ���� ������ ���� �´� �������� �ʵ� ���� �ȿ��� ���ּ��� ��ġ ���� ����.
	{
		case LEFT_KEY:		if (ship->xpos > 0)	ship->xpos--;	break;
		case RIGHT_KEY:	if (ship->xpos < 29)	ship->xpos++;	break;
		case UP_KEY:		if (ship->ypos > 0)	ship->ypos--;	break;
		case DOWN_KEY:		if (ship->ypos < 29)	ship->ypos++;	break;
	}
}

void updateShipHealth(t_ship *ship, t_rock *rock, t_fill *fill, int MAX_ROCK, float live_time)
{	  //���ּ��� ���� �浹�ߴ��� �Ǻ��ϰ�, �浹�ߴٸ� ���ּ��� ü�� - ���� ũ�⸦ �Ѵ�.
	if(live_time < 3) // ���� �ð��� 3�� �̸��� ��� ���ظ� ���� ����.
		return;

	for (int i = 0; i < MAX_ROCK; i++) // ��� ���� ���Ͽ� �˻�
	{
		if(rock[i].rock_size < 80) // ���� ���ط��� 80 �̸��� ���
		{
			if ((ship->xpos == rock[i].xpos) && (ship->ypos == rock[i].ypos))
			{	// ���� ���ּ��� ��ġ�� �����ϸ� �� ���ط� ����, ȭ���� ��������� ����
				ship->health -= rock[i].rock_size;
				system("color e0");
				system("color 0f");
			}
		}

		else // ���� ���ط��� 80 �̻��� ���
		{
			if (((ship->xpos == rock[i].xpos) || (ship->xpos == rock[i].xpos + 1)) &&
				((ship->ypos == rock[i].ypos) || (ship->ypos == rock[i].ypos + 1)))
			{ // ���� ũ�� 4ĭ �� �� ĭ�̶� ���ּ��� ��ġ�� ��ġ�ϸ�
				ship->health -= rock[i].rock_size; // ���ط� ����
				system("color cf"); // ȭ���� �������� ����
				system("color 0f");
			}
		}
	}
	if(fill->xpos == ship->xpos && fill->ypos == ship->ypos) // ȸ�� �����۰� ���ּ��� ��ġ�� ��ġ�ϸ�
	{
		ship->health += fill->refill; // ȸ���� ����
		fill->xpos = rand() % MAP_WIDTH; // ȸ�� ������ �����
		fill->ypos = rand() % MAP_HEIGHT;
		fill->refill = rand() % 30 + 30;

		system("color a0"); // ȭ���� ������� ����
		system("color 0f");
	}
	if(ship->health > 100) // ȸ�� ������ �ִ� ü�� ���Ѽ��� 100���� ����
		ship->health = 100;
}
