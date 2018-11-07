#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <stdbool.h>

#define MAP_WIDTH		30      //맵의 가로길이
#define MAP_HEIGHT	30      //맵의 세로길이
//#define MAX_ROCK	20      //최대 돌맹이 개수
#define PLAYER_LIFE	100     //우주선 최대체력
#define MIN_SCORE		5       //점수판에 기록될 최소 점수
#define UNIT_SLEEP	5       //딜레이
#define NAME_LENGHT	20
#define MAX_LIST		20

//맵의 상태 비어있으면 0 , 돌맹이가 있으면 1 , 우주선이 있으면 2
#define EMPTY		0
#define ROCK		1
#define BIG_ROCK	2
#define SHIP		3
#define FILL		4

// 키의 값
#define ESC_KEY	27
#define RIGHT_KEY	77
#define LEFT_KEY	75
#define DOWN_KEY	80
#define UP_KEY		72
#define P_KEY		'p'
#define S_KEY		's'

HANDLE consoleHandle;	//기본제공 코드 내용

typedef struct {
	int	xpos, ypos;	//우주선의 x, y 좌표
	int	health;	//우주선의 수명
} t_ship;

typedef struct {
	int	xpos, ypos;	//돌의 x, y 좌표
	int	rock_size;	//돌 크기가 크면, 우주선과 충돌하였을 때 더 많은 피해가 간다.
} t_rock;

typedef struct {
	int	rank;
	char	name[NAME_LENGHT];
	float	time;
} Player; //GameScore.txt에서 데이터를 불러와 저장할 구조체

typedef struct {
	int xpos, ypos;
	int refill;
} t_fill;

float startGame(float *game_speed, int *MAX_ROCK, char *icon, bool *cheatMode, int map[][MAP_WIDTH], t_ship *ship, t_rock *rock, t_fill *fill, time_t *start_time, time_t *mid_time, time_t *pause_start_time, time_t *pause_time, float *live_time);
void initGame();

void gameSettings(float *game_speed, char *icon, int *MAX_ROCK, bool *cheatMode);

void viewScore(char *name, float score);
void addScore(float score);

void updateShipHealth(t_ship *, t_rock *, t_fill *, int MAX_ROCK, float live_time);

void moveShip(t_ship *ship, int direction);
void moveRock(t_rock *rock, int MAX_ROCK);

void printMap(int map[][MAP_WIDTH], t_ship *ship, char *icon);
void updateMap(int map[][MAP_WIDTH], t_ship *ship, t_rock *rock, t_fill *fill, int MAX_ROCK);
void printSquare(int num);

void gotoXY(int x, int y);
float loadSave(float *live_time, int *MAX_ROCK, float *game_speed, bool *cheatMode, char *icon, t_ship *ship, t_rock *rock, t_fill *fill, time_t *start_time, time_t *mid_time, time_t *pause_start_time, time_t *pause_time, int map[][MAP_WIDTH]);
