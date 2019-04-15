#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//메모와 해시태그의 최대 개수 및 길이 정의
#define MAX_COUNT_MEMO 100
#define MAX_LENGTH_TEXT 200
#define MAX_COUNT_HASHTAG 100
#define MAX_LENGTH_HASHTAG 30

//메모 구조체
typedef struct {
	char text[MAX_LENGTH_TEXT+1];
	char hashtag[MAX_COUNT_HASHTAG][MAX_LENGTH_HASHTAG+1];
	int nHashtag;
}MEMO;

/*
함수 정의
매개변수 memo : 메모를 저장하는 배열의 시작 주소
         nMemo : 현재 저장된 메모의 개수 or 해당 변수의 주소
*/
void printMenu();
void insertMemo(MEMO *memo, int *nMemo);
void printAllMemo(MEMO *memo, int nMemo);
void searchByHashtag(MEMO *memo, int nMemo);
void deleteMemo(MEMO *memo, int *nMemo);

int main(void) {
	MEMO memo[MAX_COUNT_MEMO];
	int nMemo = 0;
	char temp[100];
	int menu;

	do {
		printMenu();
		gets(temp);
		menu = atoi(temp);
		printf("\n");
		switch (menu)
		{
		case 1:
			insertMemo(memo, &nMemo);
			break;
		case 2:
			printAllMemo(memo, nMemo);
			break;
		case 3:
			searchByHashtag(memo, nMemo);
			break;
		case 4:
			deleteMemo(memo, &nMemo);
			break;
		case 0:
			printf("Program Ended\n\n");
			break;
		default:
			printf("Incorrect Input\n\n");
			break;
		}
	} while (menu != 0);

	return 0;
}

void printMenu() {
	//메뉴 출력 함수
	printf("********** Menu **********\n");
	printf("1. Insert\n");
	printf("2. Print All Memo\n");
	printf("3. Search by Tag\n");
	printf("4. Delete\n");
	printf("0. Exit Program\n");
	printf("Choose the Item: ");
	return;
}

void insertMemo(MEMO *memo, int *nMemo) {
	/*
	메모 생성 함수
	생성자에게서 메모 내용과 #으로 구분된 해시태그를 입력 받음
	해시태그는 #을 기준으로 나누어 저장, #은 저장하지 않음
	입력 받은 메모를 출력
	ex) 메모 입력     : 메모 입력 테스트
	해시태그 입력 : #해시태그#입력#테스트

	저장된 메모     : "메모 입력 테스트"
	저장된 해시태그 : {"해시태그","입력","테스트"}

	출력
	Num Memo / Hashtag
	  1 메모 입력 테스트
	    #해시태그 #입력 #테스트
	*/
	return;
}

void printAllMemo(MEMO *memo, int nMemo) {
	/*
	현재 저장된 모든 메모 출력 함수
	Num Memo / Hashtag 형태로 출력
	Num은 메모의 번호, 1부터 시작
	해시태그는 #을 붙여서 출력
	*/
	return;
}

void searchByHashtag(MEMO *memo, int nMemo) {
	/*
	해시태그로 메모 검색하는 함수
	검색할 때 입력받는 해시태그는 #을 포함하지 않음
	Num Memo / Hashtag 형태로 출력
	*/
	return;
}

void deleteMemo(MEMO *memo, int *nMemo) {
	/*
	메모의 Num을 입력 받아 메모를 삭제하는 함수
	printAllMemo 에서 출력되는 Num을 이용해 메모를 삭제
	삭제된 메모보다 뒤에 있는 메모를 앞으로 한칸씩 이동하여 저장한다.
	*/
	return;
}
