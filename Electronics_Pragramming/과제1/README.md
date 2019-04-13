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
```C
int main(void) {
	setBoard(Width, Depth);
	printBoard(Width, Depth);
	playBoard(0, 0, 0);
	printf("최대 이동 횟수: %d\n\n", max_movement_count);
	return 0;
}
```

```C
setBoard(Width, Depth)
```
   * `setBoard` 함수를 호출해 난수 보드를 생성한다.
1. <code>setBoard(Width, Depth)</code> : `setBoard` 함수를 호출해 난수 보드를 생성한다.  
2. 23행에서 `printBoard(Width, Depth)` 함수를 호출해 생성한 보드를 출력한다.  
3. 24행에서 `playBoard(0, 0, 0)` 함수를 호출해 시작 위치를 `0, 0`으로 지정하고, 게임을 시작한다.
4. 25행에서 `printf` 함수를 통해 최대 이동 횟수를 출력하고, 프로그램을 종료한다.

### 2. `setBoard()`  
![setBoard](/Electronics_Pragramming/과제1/images/setBoard.png)  <br>
1. 
