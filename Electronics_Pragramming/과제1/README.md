전자공학프로그래밍 과제 1 보고서
=============================
> 전자공학과  
201820908 오병준  

## 1. 개발 요구 사항  
보드 게임 프로그램 개발하기  

### 1. 게임 규칙
* 0 ~ 7의 무작위 숫자가 적힌 5*5 사이즈 보드
* 보드의 좌상단 첫 번째 칸에서 시작.
* 동전이 위치한 칸의 숫자만큼 상하좌우 중 하나의 방향으로 이동.
* 동전이 보드 바깥으로 나가거나, 동전이 있는 칸의 숫자가 0일 경우 게임 종료.
* 동전의 최대 이동 가능 횟수 출력
  * 동전이 무한 번 움직일 수 있다면 -1 출력
        
### 2. 프로그램 구조
#### 1. 매크로 변수  
1. `Width` : 보드의 행 길이 지정  
2. `Depth` : 보드의 열 길이 지정  
3. `MAX_MOVEMENT` : 이동 가능 횟수의 최대치 지정

#### 2. 전역 변수  
1. `square_board` : 보드 데이터 저장 배열  
2. `max_movement` : 최대 이동 가능 횟수 저장 변수  

#### 3. 함수  
1. `setBoard(int max_width, int max_depth)`  
   보드의 크기에 맞게, 각 칸에 무작위 난수를 채워 넣어 보드를 생성한다.  
     * 반환형 : **void**
     * `max_width` : 생성할 보드의 행 길이  
     * `max_depth` : 생성할 보드의 열 길이
     <br>
     
2. `printBoard(int max_width, int max_depth)`  
   생성한 보드를 화면에 출력한다.  
     * 반환형 : **void**
     * `max_width` : 생성할 보드의 행 길이  
     * `max_depth` : 생성할 보드의 열 길이
     <br>
     
3. `playBoard(int width, int depth, int movement_count)`  
   규칙에 따라 동전을 움직여 게임을 실행한다.  
     * 반환형 : **void**
     * `width`, `depth` : 동전의 현재 좌표  
     * `movement_count` : 동전이 현재까지 움직인 횟수  
           
## 2. 코드 분석
### 1. `main()`
![main](/Electronics_Pragramming/과제1/images/main.png)  <br>

* * * * *

```C
setBoard(Width, Depth);
```
`setBoard` 함수를 호출해 난수 보드를 생성한다.  

* * * * *

```C
printBoard(Width, Depth);
```
`printBoard` 함수를 호출해 생성한 보드를 화면에 출력한다.

* * * * *

```C
playBoard(0, 0, 0);
```
`playBoard` 함수를 호출해 시작 위치를 `0, 0`으로 지정하고, 게임을 시작한다.

* * * * *

```C
printf("최대 이동 횟수: %d\n\n", max_movement_count);
```
`printf` 함수를 통해 최대 이동 횟수를 출력하고, 프로그램을 종료한다.

* * * * *

### 2. `setBoard()`  
![setBoard](/Electronics_Pragramming/과제1/images/setBoard.png)  <br>

* * * * *

```C
srand(time(NULL));
```
`rand` 함수의 시드값을 설정한다.

* * * * *

```C
for(int d = 0; d < max_depth; d++) {
  for(int w = 0; w < max_width; w++)
   square_board[w][d] = rand() % 8;
}
```
보드 배열 `square_board` 의 모든 요소에 대해 난수를 생성해 대입한다.  
`rand() % 8`은 생성한 난수를 8로 나눈 나머지이므로 0 ~ 7 사이의 무작위 값이 된다.

* * * * *

### 3. `playBoard()`  
![playBoard](/Electronics_Pragramming/과제1/images/playBoard.png)  <br>

* * * * *

```C
char flag[5] = { 0, };
```
상하좌우 각 방향에 대해 이동 가능한지 여부를 저장하는 배열 `flag`를 선언하고 모든 요소를 0으로 초기화한다.
* `flag[0]` : 해당 칸에서 이동 가능한 방향이 하나라도 존재하는지 여부를 저장한다.  
0이면 이동 가능한 방향이 존재하지 않는다는 의미이다.  

* `flag[1] ~ flag[4]` : 순서대로 오른쪽, 왼쪽, 아래, 위 방향으로 이동할 수 있는지 여부를 저장한다.

* * * * *

```C
if(!square_board[width][depth]) return;
else if(max_movement_count < 0) return;
else movement_count++;
```
현재 동전이 위치한 칸의 숫자가 `0`이거나, 최대 이동 가능 횟수를 초과했다면 함수를 종료한다.  
해당사항이 없다면, 1회 이동할 수 있다는 의미이므로 이동 횟수를 1회 증가시킨다.

* * * * *

```C
if(movement_count > max_movement_count) max_movement_count = movement_count;
if(movement_count > MAX_MOVEMENT) max_movement_count = -1;
```
현재 이동 횟수가 저장된 최대 이동 횟수보다 크다면, 최대 이동 횟수를 갱신한다.
만약 현재 이동 횟수가 최대 이동 가능 횟수를 초과했다면, 최대 이동 횟수에 `-1` 을 저장한다.

* * * * *

```C
if(width + square_board[width][depth] < Width)	flag[0] = flag[1] = 1;
if(width - square_board[width][depth] >= 0)     flag[0] = flag[2] = 1;
if(depth + square_board[width][depth] < Depth)	flag[0] = flag[3] = 1;
if(depth - square_board[width][depth] >= 0)     flag[0] = flag[4] = 1;
```
상하좌우 각 방향으로 이동할 수 있는지 여부를 판단하고,  
각 방향에 대한 이동 가능 여부를 `flag` 배열의 해당하는 요소에 저장한다.

* * * * *

```C
if(flag[0]) {
	if(flag[1]) playBoard(width + square_board[width][depth], depth, movement_count);
	if(flag[2]) playBoard(width - square_board[width][depth], depth, movement_count);
	if(flag[3]) playBoard(width, depth + square_board[width][depth], movement_count);
	if(flag[4]) playBoard(width, depth - square_board[width][depth], movement_count);
}
```
`flag[0]`이 참인지 판단해 이동 가능한 방향이 존재하는지 확인한다.  
이동 가능한 방향이 하나라도 존재한다면, 각 방향에 대한 이동 가능 여부를 확인한다.  
이후, 이동 가능한 모든 방향으로 동전의 위치를 갱신해 `playBoard` 함수를 재귀 호출한다.  
<br>
재귀 호출된 함수에서 다시 이동 가능 여부를 조사하므로, 더 이상 이동이 불가능할 때까지 재귀 호출이 이루어진다.  

* * * * *

### 4. `printBoard()`  
![printBoard](/Electronics_Pragramming/과제1/images/printBoard.png)  <br>

* * * * *

```C
for (int d = 0; d < max_depth; d++) {
  for (int w = 0; w < max_width; w++)
    printf("%2d", square_board[w][d]);
  printf("\n");
}
printf("\n");
```
`square_board` 2차원 배열의 구조를 그대로 화면에 출력한다.  
한 행의 출력이 끝나면 한 줄을 개행한다.
