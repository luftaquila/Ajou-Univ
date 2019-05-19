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
	tcgetattr(STDIN_FILENO, &oldattr);           // 현재 터미널 설정 읽음
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);         // CANONICAL과 ECHO 끔
	newattr.c_cc[VMIN] = 1;                      // 최소 입력 문자 수를 1로 설정
	newattr.c_cc[VTIME] = 0;                     // 최소 읽기 대기 시간을 0으로 설정
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // 터미널에 설정 입력
	c = getchar();                               // 키보드 입력 읽음
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // 원래의 설정으로 복구
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
	tcgetattr(STDIN_FILENO, &oldattr);           // 현재 터미널 설정 읽음
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);         // CANONICAL과 ECHO 끔
	newattr.c_cc[VMIN] = 1;                      // 최소 입력 문자 수를 1로 설정
	newattr.c_cc[VTIME] = 0;                     // 최소 읽기 대기 시간을 0으로 설정
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // 터미널에 설정 입력
	c = getchar();                               // 키보드 입력 읽음
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // 원래의 설정으로 복구
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

///////////////////////////////// 몰라도 큰 상관 없는 매크로
#define MAX_LENGTH_OF_STRING 100
#define SCORE_X 30
#define SPEED_X 50
#define DESCRIPTION_Y 1
#define REMAIN_SPECIAL_Y 2

///////////////////////////////// 해석할 때 참고할 만한 매크로
#define TRUE 1
#define FALSE 0
#define MAX_COUNT_OF_RAINDROPS 20								//빗방울 최대 개수
#define GENERATE_PERIOD 2000									//빗방울 생성 주기
#define DROP_PERIOD_MIN 500										//빗방울 떨어지는 주기 최소
#define DROP_PERIOD_MAX 700										//빗방울 떨어지는 주기 최대
//#define FILE_NAME "word.txt"									//단어가 저장되어 있는 파일 이름(한글 단어)
#define FILE_NAME "english.txt"								//단어가 저장되어 있는 파일 이름(영어 단어)
#define MAX_X 70												//빗방울 X 좌표 최대 값
#define MAX_Y 25												//빗방울 Y 좌표 최대 값
#define MIN_Y 5													//빗방울 Y 좌표 최소 값

///////////////////////////////// 구현할 부분에 관련한 매크로
#define PAUSE 3													//"정지"단어 가능 횟수 초기 값
#define BOMB 3													//"폭탄"단어 가능 횟수 초기 값
#define PAUSE_TIME 3000											//"정지"단어 입력 시 정지 시간(ms)
#define LIFE 3													//체력 초기 값

///////////////////////////////// 몰라도 상관없는 코드 
void printWord(int x, int y, char* word) {					//입력받은 x, y 좌표에 입력받은 word 출력
	gotoxy(x, y);
	printf("%s", word);
	gotoxy(MAX_X, DESCRIPTION_Y);
	wait(2);
}



#ifdef _WIN32
///////////////////////////////////////////////////////////////////////// 종료 확인
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
			if (temp == 13) {		//Enter 입력
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
			if (temp == 13) {		//Enter 입력
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

///////////////////////////////// 해석이 필요한 코드
typedef struct {
	char* word;												//단어 저장
	int x, y;												//단어의 첫 글자의 좌표
	int length;												//단어의 길이
	int period;												//업데이트 주기(ms단위, 100~300사이 임의의 값, main의 speed와 연동)
	clock_t lastUpdatedTime;								//최근 업데이트 시간
}RAINDROP;													//화면에서 떨어지는 단어를 저장할 구조체

typedef struct {
	RAINDROP raindrops[MAX_COUNT_OF_RAINDROPS];				//현재 화면에 표시된 단어들
	int cntRaindrop;										//떨어지는 단어의 개수
}RAINDROP_LIST;												//떨어지는 단어의 목록을 저장할 구조체

typedef struct {
	char** words;											//파일에 있는 단어를 저장해 놓을 변수
	int cntWord;											//단어가 저장되어 있는 개수
}WORD_LIST;													//단어의 목록을 저장할 구조체

void setWordList(WORD_LIST * wordList);													//단어가 저장된 파일을 불러와서 WORD_LIST에 단어의 목록을 저장하는 함수
int findRaindropIdx(RAINDROP_LIST raindropList, char *word);							//매개변수의 word와 일치하는 단어를 가진 빗방울을 찾아 인덱스를 반환하는 함수 (없을 경우 -1 반환)
void removeRaindropFromConsol(RAINDROP_LIST *raindropList, int idx);					//주어진 인덱스의 빗방울을 콘솔창에서 삭제
void removeRaindropFromList(RAINDROP_LIST *raindropList, int idx);					//주어진 인덱스의 빗방울을 리스트에서 삭제하고 그 뒤에 존재하는 빗방울들을 한칸씩 앞으로 옮기는 함수
void addRaindrop(RAINDROP_LIST *raindropList, WORD_LIST wordList, clock_t time);		//WORD_LIST에 저장된 단어중 임의의 단어로 새로운 빗방울을 만드는 함수
int calculateScore(RAINDROP raindrop, int speed);										//추가될 점수 계산

int main(void) {
	/*
	변수 선언
	*/
	int speed = 100;											//%단위, 100에서 시작하여 시간이 지날수록 speed 상승
	int itr;													//반복문에 사용
	int idx;													//인덱스 저장에 사용
	INPUT_WORD input;											//키보드 입력 저장
	char tempstring[MAX_LENGTH_OF_STRING + 1];					//문자열 임시 저장
	WORD_LIST wordList;											//파일에 있는 단어 목록 저장
	RAINDROP_LIST raindropList;									//빗방울 목록
	pthread_t thread;											//키보드 입력을 위한 쓰레드
	int joinStatus;												//쓰레드 상태
	int score = 0;												//점수
	clock_t lastRaindropTime = 0;								//가장 최근에 빗방울이 생성된 시간
	clock_t currentTime;										//시간 저장
	char run = TRUE;											//게임 반복 여부(종료되면 FALSE)
	int remainPause = PAUSE;									//남은 정지 횟수
	int remainBomb = BOMB;										//남은 폭탄 횟수
	int remainLife = LIFE;										//남은 체력

	/*
	초기화
	*/
	srand(time(NULL));
	setWordList(&wordList);										//파일에서 단어 목록 읽어옴
	raindropList.cntRaindrop = 0;
	input.flag = FALSE;

	/*
	초기 화면 출력
	*/
	clear();
	sprintf(tempstring, "남은 체력: %2d 남은 정지 횟수: %2d 남은 폭탄 횟수: %2d", remainLife, remainPause, remainBomb);
	printWord(0, REMAIN_SPECIAL_Y, tempstring);

	//////////////////////////////////////////////////////////////////
	//몰라도 상관없는 코드
	printWord(0, DESCRIPTION_Y, "끝내려면 '종료'를 입력하세요.");
	sprintf(tempstring, "SCORE: %8d", score);
	printWord(SCORE_X, DESCRIPTION_Y, tempstring);
	sprintf(tempstring, "SPEED: %5d%%", speed);
	printWord(SPEED_X, DESCRIPTION_Y, tempstring);
	for (itr = 0; itr < MAX_X + 10; itr++)
		printWord(itr++, MAX_Y, "■");							//닿으면 끝나는 부분 표시

	/*
	사용자 입력 관리 쓰레드 시작
	*/
	pthread_create(&thread, NULL, wordScan, (void*)&input);		//스레드를 생성하고 작동시킨다 (사용자 입력 관리 쓰레드)
	pthread_detach(thread);										//쓰레드 실행
																//////////////////////////////////////////////////////////////////

	while (run) {
		if (input.flag) {										//단어 입력 받음
			if (strcmp(input.word, "종료") == 0) {
				/////////////////////////////////
				//몰라도 상관없는 코드
				pthread_cancel(thread);
				/////////////////////////////////
				break;
			}
			do {
				idx = findRaindropIdx(raindropList, input.word);						//빗방울중 입력된 단어 찾기
				if (idx != -1) {
					score += calculateScore(raindropList.raindrops[idx], speed);		//점수 계산
					sprintf(tempstring, "SCORE: %8d", score);
					printWord(SCORE_X, DESCRIPTION_Y, tempstring);
					speed = 100 + score / 100;											//속도 계산
					sprintf(tempstring, "SPEED: %5d%%", speed);
					printWord(SPEED_X, DESCRIPTION_Y, tempstring);
					removeRaindropFromConsol(&raindropList, idx);						//일치한 단어 콘솔 화면에서 삭제
					removeRaindropFromList(&raindropList, idx);							//일치한 단어 리스트에서 삭제
				}
			} while (idx != -1);

			input.flag = FALSE;
		}

		currentTime = getClock();

		//빗방울 관리
		for (itr = 0; itr < raindropList.cntRaindrop; itr++) {
			if (raindropList.raindrops[itr].lastUpdatedTime + (double)raindropList.raindrops[itr].period / speed * 100 <= currentTime) {
				//빗방울이 한 줄 아래로 내려감
				raindropList.raindrops[itr].lastUpdatedTime = currentTime;
				removeRaindropFromConsol(&raindropList, itr);						//일치한 단어 화면에서 삭제
				raindropList.raindrops[itr].y++;
				if (raindropList.raindrops[itr].y >= MAX_Y) {
					/////////////////////////////////
					//몰라도 상관없는 코드
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
			//새로운 빗방울 추가
			lastRaindropTime = currentTime;
			addRaindrop(&raindropList, wordList, currentTime);
		}

		sprintf(tempstring, "남은 체력: %2d 남은 정지 횟수: %2d 남은 폭탄 횟수: %2d", remainLife, remainPause, remainBomb);
		printWord(0, REMAIN_SPECIAL_Y, tempstring);
	}

	/////////////////////////////////
	//몰라도 상관없는 코드
	pthread_join(thread, (void**)&joinStatus); //스레드가 끝날때까지 기다린다
											   /////////////////////////////////

	for (itr = 0; itr < wordList.cntWord; itr++)
		free(wordList.words[itr]);
	free(wordList.words);

	for (itr = 0; itr < raindropList.cntRaindrop; itr++) {
		free(raindropList.raindrops[itr].word);
	}

	printWord(0, MAX_Y + 1, "종료합니다.");
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
	//몰라도 상관없는 코드
	//콘솔에서 단어 지움
	for (itr = 0; itr < raindropList->raindrops[idx].length; itr++)
		tempstring[itr] = ' ';
	tempstring[itr] = '\0';
	printWord(raindropList->raindrops[idx].x, raindropList->raindrops[idx].y, tempstring);
	/////////////////////////////////
}