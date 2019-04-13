//학과 : 전자공학과
//학번 : 201820908
//이름 : 오병준
//개발환경(VisualStudio버전) : gcc 6.3.0

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Width 5
#define Depth 5
#define MAX_MOVEMENT 25

int square_board[Width][Depth];
int max_movement_count = 0;

void setBoard(int max_width, int max_depth);
void playBoard(int width, int depth, int movement_count);
void printBoard(int max_width, int max_depth);

int main(void) {
	setBoard(Width, Depth);
	printBoard(Width, Depth);
	playBoard(0, 0, 0);
	printf("최대 이동 횟수: %d\n\n", max_movement_count);
	return 0;
}

void setBoard(int max_width, int max_depth) {
	srand(time(NULL));
	for(int d = 0; d < max_depth; d++) {
		for(int w = 0; w < max_width; w++)
			square_board[w][d] = rand() % 8;
	}
}

void playBoard(int width, int depth, int movement_count) {
	char flag[5] = { 0, };
	if(!square_board[width][depth]) return;
	else if(max_movement_count < 0) return;
	else movement_count++;

	if(movement_count > max_movement_count) max_movement_count = movement_count;
	if(movement_count > MAX_MOVEMENT) max_movement_count = -1;

	//상하좌우 이동 가능 여부 조사
	if(width + square_board[width][depth] < Width)	flag[0] = flag[1] = 1;
	if(width - square_board[width][depth] >= 0) 		flag[0] = flag[2] = 1;
	if(depth + square_board[width][depth] < Depth)	flag[0] = flag[3] = 1;
	if(depth - square_board[width][depth] >= 0)			flag[0] = flag[4] = 1;

	if(flag[0] && movement_count) {
		if(flag[1]) playBoard(width + square_board[width][depth], depth, movement_count);
		if(flag[2]) playBoard(width - square_board[width][depth], depth, movement_count);
		if(flag[3]) playBoard(width, depth + square_board[width][depth], movement_count);
		if(flag[4]) playBoard(width, depth - square_board[width][depth], movement_count);
	}
}

void printBoard(int max_width, int max_depth) {
	for (int d = 0; d < max_depth; d++) {
		for (int w = 0; w < max_width; w++)
			printf("%2d", square_board[w][d]);
		printf("\n");
	}
	printf("\n");
}
