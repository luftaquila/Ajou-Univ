#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define HAVE_STRUCT_TIMESPEC
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
#include <Windows.h>
#include <conio.h>
#define getch() _getch()

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void wait(int msec) {
	Sleep(msec);
}
void clear() {
	system("cls");
}
clock_t getClock() {
	return clock();
}
#elif __linux__
// linux
#include <unistd.h>
#include <termio.h>
int getch(void)
{
	int c;
	struct termios oldattr, newattr;
	tcgetattr(STDIN_FILENO, &oldattr);           // ���� �͹̳� ���� ����
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);         // CANONICAL�� ECHO ��
	newattr.c_cc[VMIN] = 1;                      // �ּ� �Է� ���� ���� 1�� ����
	newattr.c_cc[VTIME] = 0;                     // �ּ� �б� ��� �ð��� 0���� ����
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // �͹̳ο� ���� �Է�
	c = getchar();                               // Ű���� �Է� ����
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // ������ �������� ����
	return c;
}
void gotoxy(int x, int y) {
	printf("\033[%d;%df", y, x);
	fflush(stdout);
}
void wait(int msec) {
	usleep(msec * 1000);
}
void clear() {
	printf("\033[H\033[J");
}
clock_t getClock() {
	return clock() / 10;
}
#elif __unix__ // all unices not caught above
// Unix
#include <unistd.h>
#include <termio.h>
int getch(void)
{
	int c;
	struct termios oldattr, newattr;
	tcgetattr(STDIN_FILENO, &oldattr);           // ���� �͹̳� ���� ����
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);         // CANONICAL�� ECHO ��
	newattr.c_cc[VMIN] = 1;                      // �ּ� �Է� ���� ���� 1�� ����
	newattr.c_cc[VTIME] = 0;                     // �ּ� �б� ��� �ð��� 0���� ����
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // �͹̳ο� ���� �Է�
	c = getchar();                               // Ű���� �Է� ����
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // ������ �������� ����
	return c;
}
void gotoxy(int x, int y) {
	printf("\033[%d;%df", y, x);
	fflush(stdout);
}
void wait(int msec) {
	usleep(msec * 1000);
}
void clear() {
	printf("\033[H\033[J");
}
clock_t getClock() {
	return clock() / 10;
}
#endif

///////////////////////////////// ���� ū ��� ���� ��ũ��
#define MAX_LENGTH_OF_STRING 100
#define SCORE_X 30
#define SPEED_X 50
#define DESCRIPTION_Y 1
#define REMAIN_SPECIAL_Y 2

///////////////////////////////// �ؼ��� �� ������ ���� ��ũ��
#define TRUE 1
#define FALSE 0
#define MAX_COUNT_OF_RAINDROPS 20								//����� �ִ� ����
#define GENERATE_PERIOD 2000									//����� ���� �ֱ�
#define DROP_PERIOD_MIN 500										//����� �������� �ֱ� �ּ�
#define DROP_PERIOD_MAX 700										//����� �������� �ֱ� �ִ�
//#define FILE_NAME "word.txt"									//�ܾ ����Ǿ� �ִ� ���� �̸�(�ѱ� �ܾ�)
#define FILE_NAME "english.txt"								//�ܾ ����Ǿ� �ִ� ���� �̸�(���� �ܾ�)
#define MAX_X 70												//����� X ��ǥ �ִ� ��
#define MAX_Y 25												//����� Y ��ǥ �ִ� ��
#define MIN_Y 5													//����� Y ��ǥ �ּ� ��

///////////////////////////////// ������ �κп� ������ ��ũ��
#define PAUSE 3													//"����"�ܾ� ���� Ƚ�� �ʱ� ��
#define BOMB 3													//"��ź"�ܾ� ���� Ƚ�� �ʱ� ��
#define PAUSE_TIME 3000											//"����"�ܾ� �Է� �� ���� �ð�(ms)
#define LIFE 3													//ü�� �ʱ� ��

///////////////////////////////// ���� ������� �ڵ� 
void printWord(int x, int y, char* word) {					//�Է¹��� x, y ��ǥ�� �Է¹��� word ���
	gotoxy(x, y);
	printf("%s", word);
	gotoxy(MAX_X, DESCRIPTION_Y);
	wait(2);
}



#ifdef _WIN32
///////////////////////////////////////////////////////////////////////// ���� Ȯ��
//define something for Windows (32-bit and 64-bit, this part is common)
////////////////////////////////// Version 1

typedef struct {
	char temp[MAX_LENGTH_OF_STRING + 1][2];
	char word[MAX_LENGTH_OF_STRING + 1];
	int length;
	char flag;
}INPUT_WORD;
void*wordScan(void* data) {
	INPUT_WORD *input = (INPUT_WORD*)data;
	char temp;
	int itr, cnt;
	input->length = 0;
	while (TRUE) {
		if (!input->flag) {
			temp = getch();
			if (temp == 13) {		//Enter �Է�
				cnt = 0;
				for (itr = 0; itr < input->length; itr++) {
					input->word[cnt++] = input->temp[itr][0];
					if (input->temp[itr][1] != 0)
						input->word[cnt++] = input->temp[itr][1];
				}
				input->word[cnt] = '\0';
				input->length = 0;
				input->flag = TRUE;
			}
			else if (temp == 8) {	//backspace
				if (input->length > 0)
					input->length--;
			}
			else {
				input->temp[input->length][0] = temp;
				temp = getch();
				input->temp[input->length][1] = temp;
				input->length++;
			}
		}
	}
	gotoxy(0, MAX_Y + 2);
	return NULL;
}

/*
////////////////////////////////// Version 2
typedef struct {
	char temp[MAX_LENGTH_OF_STRING + 1][2];
	char word[MAX_LENGTH_OF_STRING + 1];
	int length;
	char flag;
}INPUT_WORD;
void*wordScan(void* data) {
	INPUT_WORD *input = (INPUT_WORD*)data;
	char temp;
	int itr, cnt;
	input->length = 0;
	while (TRUE) {
		if (!input->flag) {
			temp = getch();
			if (temp == 13) {		//Enter �Է�
				temp = getch();
				cnt = 0;
				for (itr = 0; itr < input->length; itr++) {
					input->word[cnt++] = input->temp[itr][0];
					if (input->temp[itr][1] != 0)
						input->word[cnt++] = input->temp[itr][1];
				}
				input->word[cnt] = '\0';
				input->length = 0;
				input->flag = TRUE;
			}
			else if (temp == 8) {	//backspace
				temp = getch();
				if (input->length > 0)
					input->length--;
			}
			else {
				input->temp[input->length][0] = temp;
				temp = getch();
				input->temp[input->length][1] = temp;
				if (temp != 0)
					temp = getch();
				input->length++;
			}
		}
	}
	gotoxy(0, MAX_Y + 2);
	return NULL;
}
*/
/*
////////////////////////////////// Version 3
typedef struct {
	char word[MAX_LENGTH_OF_STRING + 1];
	char flag;
}INPUT_WORD;
void*wordScan(void* data) {
	INPUT_WORD *input = (INPUT_WORD*)data;
	while (TRUE) {
		if (!input->flag) {
			scanf("%s", input->word);
			input->flag = TRUE;
		}
	}
	gotoxy(0, MAX_Y + 2);
	return NULL;
}
*/
#elif __linux__
// linux
typedef struct {
	char word[MAX_LENGTH_OF_STRING + 1];
	char flag;
}INPUT_WORD;
void*wordScan(void* data) {
	INPUT_WORD *input = (INPUT_WORD*)data;
	while (TRUE) {
		if (!input->flag) {
			scanf("%s", input->word);
			input->flag = TRUE;
		}
	}
	gotoxy(0, MAX_Y + 2);
	return NULL;
}
#elif __unix__ // all unices not caught above
// Unix
typedef struct {
	char word[MAX_LENGTH_OF_STRING + 1];
	char flag;
}INPUT_WORD;
void*wordScan(void* data) {
	INPUT_WORD *input = (INPUT_WORD*)data;
	while (TRUE) {
		if (!input->flag) {
			scanf("%s", input->word);
			input->flag = TRUE;
		}
	}
	gotoxy(0, MAX_Y + 2);
	return NULL;
}
#endif
/////////////////////////////////

///////////////////////////////// �ؼ��� �ʿ��� �ڵ�
typedef struct {
	char* word;												//�ܾ� ����
	int x, y;												//�ܾ��� ù ������ ��ǥ
	int length;												//�ܾ��� ����
	int period;												//������Ʈ �ֱ�(ms����, 100~300���� ������ ��, main�� speed�� ����)
	clock_t lastUpdatedTime;								//�ֱ� ������Ʈ �ð�
}RAINDROP;													//ȭ�鿡�� �������� �ܾ ������ ����ü

typedef struct {
	RAINDROP raindrops[MAX_COUNT_OF_RAINDROPS];				//���� ȭ�鿡 ǥ�õ� �ܾ��
	int cntRaindrop;										//�������� �ܾ��� ����
}RAINDROP_LIST;												//�������� �ܾ��� ����� ������ ����ü

typedef struct {
	char** words;											//���Ͽ� �ִ� �ܾ ������ ���� ����
	int cntWord;											//�ܾ ����Ǿ� �ִ� ����
}WORD_LIST;													//�ܾ��� ����� ������ ����ü

void setWordList(WORD_LIST * wordList);													//�ܾ ����� ������ �ҷ��ͼ� WORD_LIST�� �ܾ��� ����� �����ϴ� �Լ�
int findRaindropIdx(RAINDROP_LIST raindropList, char *word);							//�Ű������� word�� ��ġ�ϴ� �ܾ ���� ������� ã�� �ε����� ��ȯ�ϴ� �Լ� (���� ��� -1 ��ȯ)
void removeRaindropFromConsol(RAINDROP_LIST *raindropList, int idx);					//�־��� �ε����� ������� �ܼ�â���� ����
void removeRaindropFromList(RAINDROP_LIST *raindropList, int idx);					//�־��� �ε����� ������� ����Ʈ���� �����ϰ� �� �ڿ� �����ϴ� �������� ��ĭ�� ������ �ű�� �Լ�
void addRaindrop(RAINDROP_LIST *raindropList, WORD_LIST wordList, clock_t time);		//WORD_LIST�� ����� �ܾ��� ������ �ܾ�� ���ο� ������� ����� �Լ�
int calculateScore(RAINDROP raindrop, int speed);										//�߰��� ���� ���

int main(void) {
	/*
	���� ����
	*/
	int speed = 100;											//%����, 100���� �����Ͽ� �ð��� �������� speed ���
	int itr;													//�ݺ����� ���
	int idx;													//�ε��� ���忡 ���
	INPUT_WORD input;											//Ű���� �Է� ����
	char tempstring[MAX_LENGTH_OF_STRING + 1];					//���ڿ� �ӽ� ����
	WORD_LIST wordList;											//���Ͽ� �ִ� �ܾ� ��� ����
	RAINDROP_LIST raindropList;									//����� ���
	pthread_t thread;											//Ű���� �Է��� ���� ������
	int joinStatus;												//������ ����
	int score = 0;												//����
	clock_t lastRaindropTime = 0;								//���� �ֱٿ� ������� ������ �ð�
	clock_t currentTime;										//�ð� ����
	char run = TRUE;											//���� �ݺ� ����(����Ǹ� FALSE)
	int remainPause = PAUSE;									//���� ���� Ƚ��
	int remainBomb = BOMB;										//���� ��ź Ƚ��
	int remainLife = LIFE;										//���� ü��

	/*
	�ʱ�ȭ
	*/
	srand(time(NULL));
	setWordList(&wordList);										//���Ͽ��� �ܾ� ��� �о��
	raindropList.cntRaindrop = 0;
	input.flag = FALSE;

	/*
	�ʱ� ȭ�� ���
	*/
	clear();
	sprintf(tempstring, "���� ü��: %2d ���� ���� Ƚ��: %2d ���� ��ź Ƚ��: %2d", remainLife, remainPause, remainBomb);
	printWord(0, REMAIN_SPECIAL_Y, tempstring);

	//////////////////////////////////////////////////////////////////
	//���� ������� �ڵ�
	printWord(0, DESCRIPTION_Y, "�������� '����'�� �Է��ϼ���.");
	sprintf(tempstring, "SCORE: %8d", score);
	printWord(SCORE_X, DESCRIPTION_Y, tempstring);
	sprintf(tempstring, "SPEED: %5d%%", speed);
	printWord(SPEED_X, DESCRIPTION_Y, tempstring);
	for (itr = 0; itr < MAX_X + 10; itr++)
		printWord(itr++, MAX_Y, "��");							//������ ������ �κ� ǥ��

	/*
	����� �Է� ���� ������ ����
	*/
	pthread_create(&thread, NULL, wordScan, (void*)&input);		//�����带 �����ϰ� �۵���Ų�� (����� �Է� ���� ������)
	pthread_detach(thread);										//������ ����
																//////////////////////////////////////////////////////////////////

	while (run) {
		if (input.flag) {										//�ܾ� �Է� ����
			if (strcmp(input.word, "����") == 0) {
				/////////////////////////////////
				//���� ������� �ڵ�
				pthread_cancel(thread);
				/////////////////////////////////
				break;
			}
			do {
				idx = findRaindropIdx(raindropList, input.word);						//������� �Էµ� �ܾ� ã��
				if (idx != -1) {
					score += calculateScore(raindropList.raindrops[idx], speed);		//���� ���
					sprintf(tempstring, "SCORE: %8d", score);
					printWord(SCORE_X, DESCRIPTION_Y, tempstring);
					speed = 100 + score / 100;											//�ӵ� ���
					sprintf(tempstring, "SPEED: %5d%%", speed);
					printWord(SPEED_X, DESCRIPTION_Y, tempstring);
					removeRaindropFromConsol(&raindropList, idx);						//��ġ�� �ܾ� �ܼ� ȭ�鿡�� ����
					removeRaindropFromList(&raindropList, idx);							//��ġ�� �ܾ� ����Ʈ���� ����
				}
			} while (idx != -1);

			input.flag = FALSE;
		}

		currentTime = getClock();

		//����� ����
		for (itr = 0; itr < raindropList.cntRaindrop; itr++) {
			if (raindropList.raindrops[itr].lastUpdatedTime + (double)raindropList.raindrops[itr].period / speed * 100 <= currentTime) {
				//������� �� �� �Ʒ��� ������
				raindropList.raindrops[itr].lastUpdatedTime = currentTime;
				removeRaindropFromConsol(&raindropList, itr);						//��ġ�� �ܾ� ȭ�鿡�� ����
				raindropList.raindrops[itr].y++;
				if (raindropList.raindrops[itr].y >= MAX_Y) {
					/////////////////////////////////
					//���� ������� �ڵ�
					pthread_cancel(thread);
					/////////////////////////////////
					run = FALSE;
				}
				else {
					printWord(raindropList.raindrops[itr].x, raindropList.raindrops[itr].y, raindropList.raindrops[itr].word);
				}
			}
		}

		if (lastRaindropTime + (double)GENERATE_PERIOD / speed * 100 <= currentTime && raindropList.cntRaindrop < MAX_COUNT_OF_RAINDROPS) {
			//���ο� ����� �߰�
			lastRaindropTime = currentTime;
			addRaindrop(&raindropList, wordList, currentTime);
		}

		sprintf(tempstring, "���� ü��: %2d ���� ���� Ƚ��: %2d ���� ��ź Ƚ��: %2d", remainLife, remainPause, remainBomb);
		printWord(0, REMAIN_SPECIAL_Y, tempstring);
	}

	/////////////////////////////////
	//���� ������� �ڵ�
	pthread_join(thread, (void**)&joinStatus); //�����尡 ���������� ��ٸ���
											   /////////////////////////////////

	for (itr = 0; itr < wordList.cntWord; itr++)
		free(wordList.words[itr]);
	free(wordList.words);

	for (itr = 0; itr < raindropList.cntRaindrop; itr++) {
		free(raindropList.raindrops[itr].word);
	}

	printWord(0, MAX_Y + 1, "�����մϴ�.");
	gotoxy(0, MAX_Y + 2);
	return 0;
}

void setWordList(WORD_LIST *wordList) {
	FILE *fp;
	int itr;
	int tempInt;
	char tempString[MAX_LENGTH_OF_STRING + 1];

	fp = fopen(FILE_NAME, "r");
	fscanf(fp, "%d", &wordList->cntWord);
	wordList->words = (char**)malloc(sizeof(char*) * wordList->cntWord);
	for (itr = 0; itr < wordList->cntWord; itr++)
	{
		fscanf(fp, "%s", tempString);
		tempInt = strlen(tempString);
		wordList->words[itr] = (char*)malloc(sizeof(char) * tempInt + 1);
		strcpy(wordList->words[itr], tempString);
	}
	fclose(fp);
	return;
}

int findRaindropIdx(RAINDROP_LIST raindropList, char *word) {
	int itr;
	for (itr = 0; itr < raindropList.cntRaindrop; itr++) {
		if (strcmp(raindropList.raindrops[itr].word, word) == 0) {
			return itr;
		}
	}
	return -1;
}

void removeRaindropFromList(RAINDROP_LIST *raindropList, int idx) {
	int itr;
	free(raindropList->raindrops[idx].word);
	for (itr = idx; itr < raindropList->cntRaindrop - 1; itr++)
	{
		raindropList->raindrops[itr].lastUpdatedTime = raindropList->raindrops[itr + 1].lastUpdatedTime;
		raindropList->raindrops[itr].length = raindropList->raindrops[itr + 1].length;
		raindropList->raindrops[itr].period = raindropList->raindrops[itr + 1].period;
		raindropList->raindrops[itr].x = raindropList->raindrops[itr + 1].x;
		raindropList->raindrops[itr].y = raindropList->raindrops[itr + 1].y;
		raindropList->raindrops[itr].word = raindropList->raindrops[itr + 1].word;
	}
	raindropList->cntRaindrop--;
}

void addRaindrop(RAINDROP_LIST *raindropList, WORD_LIST wordList, clock_t time) {
	int idx, tempInt;
	idx = rand() % wordList.cntWord;
	raindropList->raindrops[raindropList->cntRaindrop].lastUpdatedTime = time;
	raindropList->raindrops[raindropList->cntRaindrop].period = rand() % (DROP_PERIOD_MAX - DROP_PERIOD_MIN + 1) + DROP_PERIOD_MIN;
	raindropList->raindrops[raindropList->cntRaindrop].x = rand() % MAX_X + 1;
	raindropList->raindrops[raindropList->cntRaindrop].y = MIN_Y;

	tempInt = strlen(wordList.words[idx]);
	raindropList->raindrops[raindropList->cntRaindrop].word = (char*)malloc(sizeof(char) * tempInt + 1);
	strcpy(raindropList->raindrops[raindropList->cntRaindrop].word, wordList.words[idx]);
	raindropList->raindrops[raindropList->cntRaindrop].length = tempInt;
	raindropList->cntRaindrop++;
}

int calculateScore(RAINDROP raindrop, int speed) {
	return (speed * (DROP_PERIOD_MAX - raindrop.period + 100)) / 100;
}

void removeRaindropFromConsol(RAINDROP_LIST *raindropList, int idx) {
	int itr;
	char tempstring[MAX_LENGTH_OF_STRING + 1];

	/////////////////////////////////
	//���� ������� �ڵ�
	//�ֿܼ��� �ܾ� ����
	for (itr = 0; itr < raindropList->raindrops[idx].length; itr++)
		tempstring[itr] = ' ';
	tempstring[itr] = '\0';
	printWord(raindropList->raindrops[idx].x, raindropList->raindrops[idx].y, tempstring);
	/////////////////////////////////
}