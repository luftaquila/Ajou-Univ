library ieee;                                 -- IEEE 라이브러리 사용
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

entity toParity is                            -- entity 선언
  port(                                       -- 입력 포트 학번 각 자리 9개, 출력 포트 2개 선언.
    I0, I1, I2, I3, I4, I5, I6, I7, I8 : in std_logic;
    Q0, Q1 : out std_logic
  );
end toParity;

architecture run of toParity is               -- toParity 아키텍쳐 선언
  begin                                       -- 패리티 비트 생성
    Q0 <= I0 XOR I1 XOR I2 XOR I3 XOR I4 XOR I5 XOR I6 XOR I7 XOR I8;
        -- 짝수 패리티 생성 : 입력의 각 자리를 XOR 연산하여 짝수 패리티를 생성한 후 Q0에 저장.

    Q1 <= NOT Q0;
        -- 홀수 패리티 생성 : 한 입력에 대해 짝수 패리티와 홀수 패리티는 항상 다르므로
        -- 짝수 패리티를 NOT 연산한 수 Q1에 저장.
end architecture run;
