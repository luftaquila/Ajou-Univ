#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COUNT_MEMO 100
#define MAX_LENGTH_TEXT 200
#define MAX_COUNT_HASHTAG 100
#define MAX_LENGTH_HASHTAG 30

typedef struct {
	char text[MAX_LENGTH_TEXT + 1];
	char hashtag[MAX_COUNT_HASHTAG][MAX_LENGTH_HASHTAG + 1];
	int nHashtag;
}MEMO;

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
		switch (menu) {
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
	char hashInput[MAX_LENGTH_HASHTAG + 1], *token;
	memo[*nMemo].nHashtag = 0;
	printf("Write the Memo : ");
	gets(memo[*nMemo].text);
	printf("Write the Hashtag : ");
	gets(hashInput);
	if(strlen(hashInput)) {
		token = strtok(hashInput, "#");
		while(token) {
			strcpy(memo[*nMemo].hashtag[memo[*nMemo].nHashtag++], token);
			token = strtok(NULL, "#");
		}
	}
	printf("Num Memo / Hashtag\n");
	printf("\t%d %s\n\t", *nMemo + 1, memo[*nMemo].text);
	for(int i = 0; i < memo[*nMemo].nHashtag; i++)
		printf("#%s ", memo[*nMemo].hashtag[i]);
	printf("\n\n");
	(*nMemo)++;
	rewind(stdin);
	return;
}

void printAllMemo(MEMO *memo, int nMemo) {
	printf("Num Memo / Hashtag\n");
	for(int i = 0; i < nMemo; i++) {
		printf("\t%d %s\n\t", i + 1, memo[i].text);
		for(int j = 0; j < memo[i].nHashtag; j++)
			printf("#%s ", memo[i].hashtag[j]);
		printf("\n\n");
	}
	return;
}

void searchByHashtag(MEMO *memo, int nMemo) {
	char schQuery[MAX_LENGTH_HASHTAG + 1];
	printf("Input Hashtag : ");
	scanf("%s", schQuery);
	printf("\nNum Memo / Hashtag\n");
	for(int i = 0; i < nMemo; i++) {
		for(int j = 0; j < memo[i].nHashtag; j++) {
			if(!strcmp(schQuery, memo[i].hashtag[j])) {
				printf("\t%d %s\n\t", i + 1, memo[i].text);
				for(int k = 0; k < memo[i].nHashtag; k++)
					printf("#%s ", memo[i].hashtag[k]);
				printf("\n\n");
			}
		}
	}
	rewind(stdin);
	return;
}

void deleteMemo(MEMO *memo, int *nMemo) {
	int delQuery;
	printf("Input Num : ");
	scanf("%d", &delQuery);
	for(int i = delQuery; i < *nMemo; i++)
		memcpy(&memo[i - 1], &memo[i], sizeof(MEMO));
	(*nMemo)--;
	rewind(stdin);
	return;
}
