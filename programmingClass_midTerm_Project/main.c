#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // system() �Լ� ����� ���� ����
#include <time.h> // time_t �ڷ����� time() �Լ� ����� ���� ����
#define MAX_CLASS 5		//class�� ��
#define MAX_NUMBER 20	//�� class�� �л� ��

//����ȯ�� : Microsoft Visual Studio 2017
//�й� : 201820908
//�̸� : ������
//���� ������ ���� �Լ� ����
// printGrade();	�� �ݺ��� ������ ����ϱ� ���� �Լ�
// updateGrade();	�� ��ȣ�� �Է¹޾� ������ �����ϱ� ���� �Լ�
// averageGrade();	�� �ݺ��� ��������� ����ϱ� ���� �Լ�

/**
 * ���� �������� �ȿ� �ִ� main.c�� �Լ����� �迭 list�� �Ű������� ���޵Ǵ� ������� �ۼ��Ǿ� �ֱ淡 �׷��� �ۼ��ߴµ�,
 * pdf �ȳ� ���Ͽ� ���õ� ���� �ڵ忡�� �Լ��� �����ϴ� �Ű� ���� ���� �ٷ� ���� �迭�� �����ϰ� �Ǿ� �ֳ׿�.
 * ��� �ʿ� ���� �ۼ��ؾ� �� �� �𸣰ڰ� �̹� �Ű����� �����ϴ� ������ �ۼ��� �ڵ尡 �ʹ� ���Ƽ� �Ű����� �����ϴ� ������ �ۼ��߽��ϴ�.
**/

//�л����� ������ ������ ����Ʈ(�迭) ����
int list[MAX_CLASS][MAX_NUMBER] = {
	{ 30,16,21,43,89,16,48,55,30,74,61,100,70,17,95,45,69,38,43,81 },
{ 90,29,13,47,46,68,30,37,3, 74,67, 33,86,72,60,15,83,29,95,25 },
{ 39,36,8, 57,56,86,28,7, 72,30,88,12, 11,27,9, 49,21,38,58,75 },
{ 30,3, 26,72,8, 72,17,70,29,69,44,47, 6, 77,80,59,8, 77,95,22 },
{ 80,98,20,44,54,93,32,86,69,91,38,17, 83,13,92,74,77,11,90,44 } };

int changeCount = 0, changeLog[1000][4] = { 0 };
// ���� ���� Ƚ���� �����ϴ� changeCount, ���� ��� ������ �����ϴ� changeLog �迭 ����. 0���� �ʱ�ȭ.
time_t changeTime[1000] = { 0 }; // ���� ���� �ð� ������ �����ϴ� time_t�� �迭 ����, 0���� �ʱ�ȭ


void printGrade(int array[][MAX_NUMBER]);
void updateGrade(int array[][MAX_NUMBER]);
void averageGrade(int array[][MAX_NUMBER]);
void graphGrade(int array[][MAX_NUMBER]);
void writeGradeChangeLog(int class, int num, int before, int after);
void readGradeChangeLog();
// ��� �Լ� ���� ���

int main(void)
{
	int menu;
	while (1)
	{
		printf("1 : ���� ���  |  2 : ���� ����  |  3 : ��� ���� ���  |  4 : �׷��� ���  ");
		printf("|  5 : ���� ���� ��� ����  |  0 : ����\n�޴��� �Է��ϼ��� : ");
		scanf("%d", &menu); // �޴� ���� ��ȣ �Է¹޾� menu�� ����

		switch (menu) // �޴� ���� ���� �Է°����� swtich�� �Ǻ�, �� �޴��� �ش��ϴ� �Լ� ����.
		{
		case 1:
			printGrade(list); break;
		case 2:
			updateGrade(list); break;
		case 3:
			averageGrade(list); break;
		case 4:
			graphGrade(list); break;
		case 5:
			readGradeChangeLog(); break;
		case 0:
			printf("\n���α׷��� �����մϴ�\n\n"); return 0; // 0 �Է½� ���� ���� ���, ����
		default:
			printf("\n�߸��� �Է��Դϴ�\n\n"); // �߸� �Է½� ���� ���� ���
		}
	}
}

void printGrade(int array[][MAX_NUMBER]) // ���� ��� �Լ�. �迭 list�� ������ �ּҸ� �Ű������� ����.
{
	int class;

	system("cls");
	printf("1 ~ 5���� ������, 6�� ��ü ���\n");
	printf("������ ����ϰ� ���� ���� �Է��ϼ��� : ");
	scanf("%d", &class); // ����� �� ������ �Է¹޾� ������ class ������ ����.
	printf("\n");

	for (int i = 0; i < MAX_CLASS; i++) // �� ������ŭ ��� �ݺ�
	{
		if (class > 0 && class < 6)	i = class - 1; // ���� �Է��� ���� 1 ~ 5�� �����̸� i���� �ش� �ݿ� �����ϴ� ������ ����.
		else if (class <= 0 || class > 6)
		// �Է��� ���� 1 ~ 6�� ���� �ٱ��̸�, �� �Է� ���� ���. 6�� ��� ��� if���� �ش���� �����Ƿ� i =0���� 5���� ��� �ݺ�.
		{
			printf("�߸��� �� �Է��Դϴ�.\n\n");
			break;
		}

		for (int j = 0; j < MAX_NUMBER; j++) // �Է��� �� ������ �����ϴ� i���� ���� �� �л� ���� ���� ���.
			printf("%d�� %2d�� : %3d��\n", i + 1, j + 1, array[i][j]);
		printf("\n");

		if (class > 0 && class < 6) break; // �Է��� ���� 1 ~ 5�� �����̸�, �ݺ��� ó������ ������ i�� 1ȸ�� ���� �ݺ��� �����ϰ� ����.
	}
}

void updateGrade(int array[][MAX_NUMBER]) // ���� ���� �Լ�.
{
	int class, num, score;

	system("cls");
	printf("������ ������ �л��� �� ��ȣ ������ �Է��ϼ��� : ");
	scanf("%d%d%d", &class, &num, &score); // ������ ������ �л��� ��, ��ȣ, ������ ���� ���� �Է¹޾� ����.

	if (class < 0 || class > MAX_CLASS) // �Է¹��� �� ������ ���� �ٱ��� ��� ���� ���.
	{
		printf("\n�߸��� �� �Է��Դϴ�.\n\n");
		return;
	}

	if (num < 0 || num > MAX_NUMBER) // �Է¹��� ��ȣ ������ ���� �ٱ��� ��� ���� ���.
	{
		printf("\n�߸��� ��ȣ �Է��Դϴ�.\n\n");
		return;
	}

	if (score < 0 || score > 100) // �Է¹��� ���� ������ ���� �ٱ��� ��� ���� ���.
	{
		printf("\n�߸��� ���� �Է��Դϴ�.\n\n");
		return;
	}

	writeGradeChangeLog(class, num, array[class - 1][num - 1], score);
	// ���� ���� ������ ��� �Լ� ȣ��. ������ �л��� ��, ��ȣ, ���� �� ����, ���� �� ���� ����.

	printf("\n���� �� %d�� %2d�� : %3d��\n", class, num, array[class - 1][num - 1]); // ���� �� ���� ���.
	array[class - 1][num - 1] = score; // �Լ��� �Ű������� ���� ���� list�� �ּ��̹Ƿ� ���� list���� �� ������Ʈ
	printf("���� �� %d�� %2d�� : %3d��\n", class, num, array[class - 1][num - 1]); // ���� �� ���� ���

	printf("\n");
}

void averageGrade(int array[][MAX_NUMBER]) // ��� ���� ��� �Լ�.
{
	int class, avg, sum = 0, totSum = 0;

	system("cls");
	printf("1 ~ 5���� ������, 6�� ��ü ���\n");
	printf("��� ������ ����� ���� �Է��ϼ��� : ");
	scanf("%d", &class);

	for (int i = 0; i < MAX_CLASS; i++)
	{
		if (class > 0 && class < 6)	i = class - 1;
		else if (class <= 0 || class > 6)
		// printGrade �Լ��� ������ ��Ŀ�������� 1 ~ 5�� ��� �ش� �� ������� ���, 6�� ��� ��ü ���, �̿� ���� ���.
		{
			printf("\n�߸��� �� �Է��Դϴ�.");
			break;
		}

		for (int j = 0; j < MAX_NUMBER; j++) // �Է¹��� �ݿ� �����ϴ� i�� ���� array �迭�� i��° row�� �ִ� ��� ���� ���� sum�� ����.
			sum += array[i][j];
		avg = sum / MAX_NUMBER; // ���� �հ� sum�� �л� ���� ���� ��հ��� avg�� ����, ���

		totSum += avg; // ��ü ��� ����� ���� �� ����� �հ�

		printf("\n%d�� ��� ���� : %3d��", i + 1, avg);
		sum = 0; // ���� �հ� �ʱ�ȭ.

		if (class > 0 && class < 6)	break; // �Է¹��� �� ������ 1 ~ 5 �̳��� ��� �ش� i���� �ݺ��ϰ� Ż��.
	}
	if(class == 6) printf("\n\n1 ~ 5�� ��ü ��� ���� : %d��", totSum / MAX_CLASS); // ��ü �� ��� ���
	printf("\n\n");
}

void graphGrade(int array[][MAX_NUMBER]) // �׷��� ��� �Լ�.
{
	int class, max;

	system("cls");
	printf("1 ~ 5���� ������, 6�� ��ü ���\n");
	printf("���� �׷����� ����� ���� �Է��ϼ��� : ");
	scanf("%d", &class);


	for (int i = 0; i < MAX_CLASS; i++)
	{
		if (class > 0 && class < 6)	i = class - 1;
		else if (class < 0 || class > 6)
		{
			printf("\n�߸��� �� �Է��Դϴ�.\n\n");
			break;
		} // printGrade, averageGrade�� ������ ��Ŀ�������� �ݺ� Ƚ�� ���� �� �߸� �Էµ� �� ����.

		for (int j = 0; j < 85; j++) // ���� �׷��� ��� ����
			printf("=");
		printf("\n===== %d�� ���� �׷��� ===============================================================\n", i + 1);

		max = array[class - 1][0];
		for (int j = 1; j < MAX_NUMBER; j++)
		{
			if (array[i][j] > max)
				max = array[i][j];
		} // 184����� �Է¹��� �ݿ� �����ϴ� i�� ���� array�� i��° row�� �ִ� ���� �ִ밪 max�� ����. �� �ش� ���� �ְ� ���� ����

		for (int j = 0; j < 100 / 4; j++) // �ܼ� ȭ�鿡 �� ���� ǥ���ϱ� ���� 4�� ������ 25%�� �����ϸ�.
		{
			for (int k = 0; k < MAX_NUMBER; k++) // �� �� ���
				if ((array[i][k] / 4 + j) >= 100 / 4) printf("   *"); else printf("    ");
				// �ش� �л��� ������ �� ���� ��°������ ũ�� �� ���, �ƴϸ� ���� ���
			printf("\n");
		}

		for (int j = 1; j <= MAX_NUMBER; j++) // �ڸ� ���缭 �л� ��ȣ ���
			printf(" %3d", j);

		printf("\n\n");

		if (class > 0 && class < 6)	break; // 1 ~ 5�� �Է��� ��� �ش� �ݸ� ����ϰ� Ż��.
	}
}

void writeGradeChangeLog(int class, int num, int before, int after) // ���� ���� ��� ���� �Լ�.
{
	changeCount++; // ���� Ƚ�� ī��Ʈ.

	changeLog[changeCount][0] = class; // ��, ��ȣ, ���� �� ����, ���� �� ���� �迭�� ����.
	changeLog[changeCount][1] = num;
	changeLog[changeCount][2] = before;
	changeLog[changeCount][3] = after;
	changeTime[changeCount] = time(NULL); // time_t�� �迭�� ������ �ð� ����
}

void readGradeChangeLog()
{
	struct tm t; // time.h�� ���ǵ� �ð� ����ü ����
	printf("\n");
	if(changeCount == 0) printf("���� ���� ����� �����ϴ�.\n"); // ���� Ƚ�� ī��Ʈ�� 0�̸� ���� �޽��� ���
	for (int i = 1; i < 1000; i++) // ���� ��� ���. �ִ� 1000ȸ���� ����.
	{
		if (changeLog[i][0] == 0) break; // i��° row�� �� �����Ͱ� �ʱⰪ�̸�, ���� ����
		t = *localtime(&changeTime[i]); // �ð� ����ü�� �ش� �ð� �� ����
		printf("[%4d.%2d.%2d %2d:%2d:%2d]\t%d�� %2d�� �л��� ������ %3d������ %3d������ ������.\n",
			t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec,
			changeLog[i][0], changeLog[i][1], changeLog[i][2], changeLog[i][3]);
			// ���� �ð� ����, ��, ��ȣ, ���� �� ����, ���� �� ���� ���
	}
	printf("\n");
}
