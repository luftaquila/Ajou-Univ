#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // system() 함수 사용을 위해 포함
#include <time.h> // time_t 자료형과 time() 함수 사용을 위해 포함
#define MAX_CLASS 5		//class의 수
#define MAX_NUMBER 20	//각 class당 학생 수

//개발환경 : Microsoft Visual Studio 2017
//학번 : 201820908
//이름 : 오병준
//점수 관리를 위한 함수 선언
// printGrade();	각 반별로 점수를 출력하기 위한 함수
// updateGrade();	반 번호를 입력받아 점수를 수정하기 위한 함수
// averageGrade();	각 반별로 평균점수를 출력하기 위한 함수

/**
 * 과제 압축파일 안에 있던 main.c의 함수에는 배열 list가 매개변수로 전달되는 방식으로 작성되어 있길래 그렇게 작성했는데,
 * pdf 안내 파일에 제시된 예시 코드에는 함수에 전달하는 매개 변수 없이 바로 전역 배열에 접근하게 되어 있네요.
 * 어느 쪽에 맞춰 작성해야 할 지 모르겠고 이미 매개변수 전달하는 식으로 작성한 코드가 너무 많아서 매개변수 전달하는 식으로 작성했습니다.
**/

//학생들의 점수를 저장할 리스트(배열) 선언
int list[MAX_CLASS][MAX_NUMBER] = {
	{ 30,16,21,43,89,16,48,55,30,74,61,100,70,17,95,45,69,38,43,81 },
{ 90,29,13,47,46,68,30,37,3, 74,67, 33,86,72,60,15,83,29,95,25 },
{ 39,36,8, 57,56,86,28,7, 72,30,88,12, 11,27,9, 49,21,38,58,75 },
{ 30,3, 26,72,8, 72,17,70,29,69,44,47, 6, 77,80,59,8, 77,95,22 },
{ 80,98,20,44,54,93,32,86,69,91,38,17, 83,13,92,74,77,11,90,44 } };

int changeCount = 0, changeLog[1000][4] = { 0 };
// 성적 변경 횟수를 저장하는 changeCount, 변경 기록 정보를 저장하는 changeLog 배열 선언. 0으로 초기화.
time_t changeTime[1000] = { 0 }; // 성적 변경 시간 정보를 저장하는 time_t형 배열 선언, 0으로 초기화


void printGrade(int array[][MAX_NUMBER]);
void updateGrade(int array[][MAX_NUMBER]);
void averageGrade(int array[][MAX_NUMBER]);
void graphGrade(int array[][MAX_NUMBER]);
void writeGradeChangeLog(int class, int num, int before, int after);
void readGradeChangeLog();
// 사용 함수 원형 명시

int main(void)
{
	int menu;
	while (1)
	{
		printf("1 : 점수 출력  |  2 : 점수 수정  |  3 : 평균 점수 출력  |  4 : 그래프 출력  ");
		printf("|  5 : 성적 변경 기록 열람  |  0 : 종료\n메뉴를 입력하세요 : ");
		scanf("%d", &menu); // 메뉴 선택 번호 입력받아 menu에 저장

		switch (menu) // 메뉴 선택 변수 입력값으로 swtich문 판별, 각 메뉴에 해당하는 함수 실행.
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
			printf("\n프로그램을 종료합니다\n\n"); return 0; // 0 입력시 종료 문구 출력, 종료
		default:
			printf("\n잘못된 입력입니다\n\n"); // 잘못 입력시 에러 문구 출력
		}
	}
}

void printGrade(int array[][MAX_NUMBER]) // 성적 출력 함수. 배열 list의 포인터 주소를 매개변수로 받음.
{
	int class;

	system("cls");
	printf("1 ~ 5반이 있으며, 6은 전체 출력\n");
	printf("점수를 출력하고 싶은 반을 입력하세요 : ");
	scanf("%d", &class); // 출력할 반 정보를 입력받아 선언한 class 변수에 저장.
	printf("\n");

	for (int i = 0; i < MAX_CLASS; i++) // 반 개수만큼 출력 반복
	{
		if (class > 0 && class < 6)	i = class - 1; // 만약 입력한 반이 1 ~ 5의 범위이면 i값을 해당 반에 대응하는 값으로 변경.
		else if (class <= 0 || class > 6)
		// 입력한 반이 1 ~ 6의 범위 바깥이면, 반 입력 오류 출력. 6일 경우 어느 if에도 해당되지 않으므로 i =0부터 5까지 모두 반복.
		{
			printf("잘못된 반 입력입니다.\n\n");
			break;
		}

		for (int j = 0; j < MAX_NUMBER; j++) // 입력한 반 정보에 대응하는 i값에 대한 각 학생 점수 정보 출력.
			printf("%d반 %2d번 : %3d점\n", i + 1, j + 1, array[i][j]);
		printf("\n");

		if (class > 0 && class < 6) break; // 입력한 반이 1 ~ 5의 범위이면, 반복문 처음에서 설정한 i값 1회에 대한 반복만 실행하고 종료.
	}
}

void updateGrade(int array[][MAX_NUMBER]) // 성적 수정 함수.
{
	int class, num, score;

	system("cls");
	printf("점수를 수정할 학생의 반 번호 점수를 입력하세요 : ");
	scanf("%d%d%d", &class, &num, &score); // 점수를 수정할 학생의 반, 번호, 수정할 점수 정보 입력받아 저장.

	if (class < 0 || class > MAX_CLASS) // 입력받은 반 정보가 범위 바깥일 경우 오류 출력.
	{
		printf("\n잘못된 반 입력입니다.\n\n");
		return;
	}

	if (num < 0 || num > MAX_NUMBER) // 입력받은 번호 정보가 범위 바깥일 경우 오류 출력.
	{
		printf("\n잘못된 번호 입력입니다.\n\n");
		return;
	}

	if (score < 0 || score > 100) // 입력받은 점수 정보가 범위 바깥일 경우 오류 출력.
	{
		printf("\n잘못된 점수 입력입니다.\n\n");
		return;
	}

	writeGradeChangeLog(class, num, array[class - 1][num - 1], score);
	// 성적 수정 데이터 기록 함수 호출. 수정한 학생의 반, 번호, 수정 전 점수, 수정 후 점수 전달.

	printf("\n변경 전 %d반 %2d번 : %3d점\n", class, num, array[class - 1][num - 1]); // 변경 전 점수 출력.
	array[class - 1][num - 1] = score; // 함수가 매개변수로 받은 값이 list의 주소이므로 기존 list에서 값 업데이트
	printf("변경 후 %d반 %2d번 : %3d점\n", class, num, array[class - 1][num - 1]); // 변경 후 점수 출력

	printf("\n");
}

void averageGrade(int array[][MAX_NUMBER]) // 평균 성적 출력 함수.
{
	int class, avg, sum = 0, totSum = 0;

	system("cls");
	printf("1 ~ 5반이 있으며, 6은 전체 출력\n");
	printf("평균 점수를 출력할 반을 입력하세요 : ");
	scanf("%d", &class);

	for (int i = 0; i < MAX_CLASS; i++)
	{
		if (class > 0 && class < 6)	i = class - 1;
		else if (class <= 0 || class > 6)
		// printGrade 함수와 동일한 메커니즘으로 1 ~ 5일 경우 해당 반 평균점수 출력, 6일 경우 전체 출력, 이외 오류 출력.
		{
			printf("\n잘못된 반 입력입니다.");
			break;
		}

		for (int j = 0; j < MAX_NUMBER; j++) // 입력받은 반에 대응하는 i에 대한 array 배열의 i번째 row에 있는 모든 값을 더해 sum에 저장.
			sum += array[i][j];
		avg = sum / MAX_NUMBER; // 점수 합계 sum을 학생 수로 나눈 평균값을 avg에 저장, 출력

		totSum += avg; // 전체 평균 계산을 위한 반 평균의 합계

		printf("\n%d반 평균 점수 : %3d점", i + 1, avg);
		sum = 0; // 점수 합계 초기화.

		if (class > 0 && class < 6)	break; // 입력받은 반 범위가 1 ~ 5 이내일 경우 해당 i값만 반복하고 탈출.
	}
	if(class == 6) printf("\n\n1 ~ 5반 전체 평균 점수 : %d점", totSum / MAX_CLASS); // 전체 반 평균 출력
	printf("\n\n");
}

void graphGrade(int array[][MAX_NUMBER]) // 그래프 출력 함수.
{
	int class, max;

	system("cls");
	printf("1 ~ 5반이 있으며, 6은 전체 출력\n");
	printf("점수 그래프를 출력할 반을 입력하세요 : ");
	scanf("%d", &class);


	for (int i = 0; i < MAX_CLASS; i++)
	{
		if (class > 0 && class < 6)	i = class - 1;
		else if (class < 0 || class > 6)
		{
			printf("\n잘못된 반 입력입니다.\n\n");
			break;
		} // printGrade, averageGrade와 동일한 메커니즘으로 반복 횟수 결정 및 잘못 입력된 값 검출.

		for (int j = 0; j < 85; j++) // 점수 그래프 출력 개시
			printf("=");
		printf("\n===== %d반 점수 그래프 ===============================================================\n", i + 1);

		max = array[class - 1][0];
		for (int j = 1; j < MAX_NUMBER; j++)
		{
			if (array[i][j] > max)
				max = array[i][j];
		} // 184행부터 입력받은 반에 대응하는 i에 대한 array의 i번째 row에 있는 값의 최대값 max에 저장. 즉 해당 반의 최고 점수 저장

		for (int j = 0; j < 100 / 4; j++) // 콘솔 화면에 한 번에 표시하기 위해 4로 나누어 25%로 스케일링.
		{
			for (int k = 0; k < MAX_NUMBER; k++) // 한 줄 출력
				if ((array[i][k] / 4 + j) >= 100 / 4) printf("   *"); else printf("    ");
				// 해당 학생의 점수가 그 줄의 번째수보다 크면 별 출력, 아니면 공백 출력
			printf("\n");
		}

		for (int j = 1; j <= MAX_NUMBER; j++) // 자리 맞춰서 학생 번호 출력
			printf(" %3d", j);

		printf("\n\n");

		if (class > 0 && class < 6)	break; // 1 ~ 5반 입력한 경우 해당 반만 출력하고 탈출.
	}
}

void writeGradeChangeLog(int class, int num, int before, int after) // 성적 변경 기록 쓰기 함수.
{
	changeCount++; // 변경 횟수 카운트.

	changeLog[changeCount][0] = class; // 반, 번호, 변경 전 점수, 변경 후 점수 배열에 저장.
	changeLog[changeCount][1] = num;
	changeLog[changeCount][2] = before;
	changeLog[changeCount][3] = after;
	changeTime[changeCount] = time(NULL); // time_t형 배열에 변경한 시간 저장
}

void readGradeChangeLog()
{
	struct tm t; // time.h에 정의된 시간 구조체 선언
	printf("\n");
	if(changeCount == 0) printf("성적 변경 기록이 없습니다.\n"); // 변경 횟수 카운트가 0이면 오류 메시지 출력
	for (int i = 1; i < 1000; i++) // 변경 기록 출력. 최대 1000회까지 저장.
	{
		if (changeLog[i][0] == 0) break; // i번째 row의 반 데이터가 초기값이면, 이후 생략
		t = *localtime(&changeTime[i]); // 시간 구조체에 해당 시간 값 저장
		printf("[%4d.%2d.%2d %2d:%2d:%2d]\t%d반 %2d번 학생의 성적을 %3d점에서 %3d점으로 수정함.\n",
			t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec,
			changeLog[i][0], changeLog[i][1], changeLog[i][2], changeLog[i][3]);
			// 수정 시간 정보, 반, 번호, 변경 전 점수, 변경 후 점수 출력
	}
	printf("\n");
}
