
library ieee;                                 -- IEEE 라이브러리 사용
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

entity tb is                                  -- 테스트벤치 entity 선언
end tb;

architecture tb_arch of tb is                 -- 테스트벤치 아키텍쳐 선언
  component toParity                          -- 시뮬레이션할 toParity 모듈 불러오기
  port(                                       -- 입력 포트 9개, 출력 포트 2개 선언.
    I0, I1, I2, I3, I4, I5, I6, I7, I8 : in std_logic;
    Q0, Q1 : out std_logic
  );
  end component;

  signal I0, I1, I2, I3, I4, I5, I6, I7, I8 : std_logic;    -- 시그널 선언
  signal Q0, Q1 : std_logic;

  -- integer 타입을 std_logic 타입으로 변환해 전달하기 위한 사용자 함수 선언
  function to_std_logic(i : in integer) return std_logic is
  begin
      if i = 0 then         -- 입력이 0이면 std_logic '0' 반환
          return '0';
      end if;
      return '1';           -- 입력이 0이 아니면 std_logic '1' 반환
  end function;

begin
  -- toParity 컴포넌트의 포트와 시그널을 연결
  UUT : toParity port map (
    I0 => I0, I1 => I1, I2 => I2, I3 => I3,
    I4 => I4, I5 => I5, I6 => I6, I7 => I7, I8 => I8,
    Q0 => Q0, Q1 => Q1
  );

  -- 포트에 입력값 전달 : 학번 각 자리를 2로 mod 연산하여 std_logic 타입으로 변환, 입력값으로 전달
  I0 <= to_std_logic(2 mod 2);
  I1 <= to_std_logic(0 mod 2);
  I2 <= to_std_logic(1 mod 2);
  I3 <= to_std_logic(8 mod 2);
  I4 <= to_std_logic(2 mod 2);
  I5 <= to_std_logic(0 mod 2);
  I6 <= to_std_logic(9 mod 2);
  I7 <= to_std_logic(0 mod 2);
  I8 <= to_std_logic(8 mod 2);
end tb_arch;
