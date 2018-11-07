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

void addScore(float score)
{
	FILE *fp; // ���� ������ ����
	char name[NAME_LENGHT], **str, *buffer, *ptrLine, *ptrObject;
	// �̸� �Է��� ���� ���ڿ�, ���� ������� ���� ���ڿ� ������ ����
	int size, counter = 0; // ������ ũ��� �� ���� ���� ����
	Player **player = NULL, *temp; // ����ü ������ �迭�� ���� ���� ������, ������ ���� ����ü ������ ����

	fflush(stdin);
	printf("����� ������ %.3f�� �Դϴ�. ������ �����ϱ� ���ؼ��� �̸��� �ʿ��մϴ�.\n", score);
	printf("�̸� �� : ");
	scanf("%s", name);

	fp = fopen("GameScore.csv", "a+"); // ������ ������ �����ϰ� r/w ���� ����

	fseek(fp, 0, SEEK_END); // ������ ������ �����͸� �̵�
	size = ftell(fp); // ���� ũ�⸦ size�� ����

	buffer = (char *)malloc(size + 1); // �Է� ���۸� ���� ũ�⸸ŭ ���� �Ҵ�
	memset(buffer, 0, size + 1); // // ���� �ʱ�ȭ

	fseek(fp, 0, SEEK_SET); // ������ ó������ �����͸� �̵�
	fread(buffer, size, 1, fp); // ���� ������ �Է� ���۷� �̵�

	for (int i = 0; i < size; i++) // ���ۿ��� ���� ���ڸ� ã�Ƽ� �� �� ī��Ʈ
	{
		if (buffer[i] == '\n')
			counter++;
	}

	player = (Player **)calloc(counter + 2, sizeof(*player));
	// ���� ���� �� ��(�÷��̾� ��� ��)�� �߰��� �÷��̾� ��ϱ��� ���Ͽ� ����ü �迭 ���� �Ҵ�
	str = (char **)calloc(counter + 2, sizeof(*str)); // �Է� ���ۿ��� �� �پ� �о�� ����

	ptrLine = strtok(buffer, "\n"); // �Է� ���۸� �� �پ� �ɰ��� str�� ����
	for (int i = 0; ptrLine != NULL; i++)
	{
		str[i] = ptrLine;
		ptrLine = strtok(NULL, "\n");
	}

	for (int i = 0; str[i]; i++) // �� �پ� ����� �� str�� ,�� �ɰ��� ����ü�� ����
	{
		player[i] = (Player *)malloc(sizeof(**player)); // ����ü �迭 ��� ũ�� ���� �Ҵ�

		ptrObject = strtok(str[i], ",");
		player[i]->rank = atoi(ptrObject);

		ptrObject = strtok(NULL, ",");
		strcpy(player[i]->name, ptrObject);

		ptrObject = strtok(NULL, ",");
		player[i]->time = atof(ptrObject);
	}

	player[counter] = (Player *)malloc(sizeof(**player)); // ����ü�� ���� ���ο� �÷��̾� ��� ���� �Ҵ�
	player[counter]->rank = 0; // ������ 0���� �ʱ�ȭ
	strcpy(player[counter]->name, name); // ����ü�� �̸��� ��� ����
	player[counter]->time = score;

	for (int i = 0; i < counter + 1; i++) // ����ü�� ��� ������ ������ ����
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

	for (int i = 0; i < counter + 1; i++) // ������ �Ϸ�� ����ü�� ���� �ű��
		player[i]->rank = i + 1;

	fp = fopen("GameScore.csv", "w"); // ������ ���� ���� �ٽ� ����

	for (int i = 0; player[i]; i++) // ����ü ������ �� �پ� csv �������� ���Ͽ� ���
		fprintf(fp, "%d,%s,%.3f\n", player[i]->rank, player[i]->name, player[i]->time);
	fclose(fp); // ���� �ݱ�

	free(player); // �����Ҵ� ���� �ݳ�
	free(str);

	viewScore(&name, score); // ��� ���� �Լ� ȣ��
}

void viewScore(char *name, float score)
{	//�Լ��� ȣ��� ȭ���� ����� ȭ�鿡 GameScore.txt ���Ϸκ��� ������ ������ ȭ�鿡 ����ϴ� �Լ�
	FILE *fp;
	char **str, *buffer, *ptrLine, *ptrObject;
	int size, counter = 0;
	Player **player = NULL; // addScore�� ������ ���� ����.

	fp = fopen("GameScore.csv", "r"); // ������ �б� ���� ����
	if (fp == NULL) // ������ �������� ���� ��� ���� ���� ���.
	{
		printf("����� �����Ͱ� �����ϴ�!\n");
		Sleep(1000);
		return;
	}

	else // ������ ������ ���
	{
		system("cls");
		printf("���\t�̸�\t����\n"); // ���̾ƿ� ���

		fseek(fp, 0, SEEK_END); // addScore �Լ��� ������ ���� �б� ����
		size = ftell(fp);

		buffer = (char *)malloc(size + 1);
		memset(buffer, 0, size + 1);

		fseek(fp, 0, SEEK_SET);
		fread(buffer, size, 1, fp);

		for (int i = 0; i < size; i++)
		{
			if (buffer[i] == '\n')
				counter++;
		}

		player = (Player **)calloc(counter + 2, sizeof(*player));
		str = (char **)calloc(counter + 2, sizeof(*str));

		ptrLine = strtok(buffer, "\n");
		for (int i = 0; ptrLine != NULL; i++)
		{
			str[i] = ptrLine;
			ptrLine = strtok(NULL, "\n");
		}
		fclose(fp); // ���ۿ� ���� �� ���� �ݱ�

		for (int i = 0; str[i]; i++) // ���ۿ��� �и��Ͽ� ����ü�� ����
		{
			player[i] = (Player *)malloc(sizeof(**player));

			ptrObject = strtok(str[i], ",");
			player[i]->rank = atoi(ptrObject);

			ptrObject = strtok(NULL, ",");
			strcpy(player[i]->name, ptrObject);

			ptrObject = strtok(NULL, ",");
			player[i]->time = atof(ptrObject);
		}

		for (int i = 0; player[i]; i++) // ȭ�鿡 ���
		{
			printf(" %2d\t%s\t%.3f", player[i]->rank, player[i]->name, player[i]->time);
			if((player[i]->time == score)) // ����� ��ġ�ϴ� �÷��̾� ���ڵ忡 �ڽ����� ǥ��
				printf("\t�� YOU");
			printf("\n");
		}

		free(player); // ���� �Ҵ� �޸� �ݳ�
		free(str);

		system("PAUSE && cls"); // �Ͻ� ���� �� ȭ�� �ʱ�ȭ
	}
}
