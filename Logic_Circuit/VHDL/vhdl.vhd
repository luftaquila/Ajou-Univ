library ieee;                                 -- IEEE 라이브러리 사용
use ieee.std_logic_1164.all;

entity toGray is                              -- entity 선언
  port(                                       -- 입/출력 포트 각각 4개씩 선언
    D0, D1, D2, D3 : in std_logic;
    Q0, Q1, Q2, Q3 : out std_logic
  );
end toGray;

architecture cat of toGray is                 -- toGray에 대한 아키텍쳐 선언
  signal nD0, nD1, nD2, nD3 : std_logic;      -- 회로 구현에 필요한 시그널 선언
  signal P0, P1, P2, P3, P4, P5 : std_logic;

  begin                                       -- 그레이 코드 변환 회로 구현
    nD0 <= not D0;                            -- nD1 = D1'
    nD1 <= not D1;                            -- nD2 = D2'
    nD2 <= not D2;                            -- nD3 = D3'
    nD3 <= not D3;                            -- nD4 = D4'

    P0 <= D0 and nD1;                         -- P0 = D0 · D1'
    P1 <= D1 and nD0;                         -- P1 = D1 · D0'
    P2 <= D1 and nD2;                         -- P2 = D1 · D2'
    P3 <= D2 and nD1;                         -- P3 = D2 · D1'
    P4 <= D3 and nD2;                         -- P4 = D3 · D2'
    P5 <= D2 and nD3;                         -- P5 = D2 · D3'

    Q0 <= P0 or P1;                           -- Q0 = P0 + P1 = D0 · D1' + D1 · D0'
    Q1 <= P2 or P3;                           -- Q1 = P2 + P3 = D1 · D2' + D2 · D1'
    Q2 <= P4 or P5;                           -- Q2 = P4 + P5 = D3 · D2' + D2 · D3'
    Q3 <= D3;
end architecture cat;
