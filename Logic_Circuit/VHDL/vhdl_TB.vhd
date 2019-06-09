library ieee;                                 -- IEEE 라이브러리 사용
use ieee.std_logic_1164.all;

entity tb is                                  -- 테스트벤치 entity 선언
end tb;

architecture tb_arch of tb is                 -- 테스트벤치 아키텍쳐 선언
  component toGray                            -- 시뮬레이션할 toGray 모듈 불러오기
  port( D0, D1, D2, D3 : in std_logic;
        Q0, Q1, Q2, Q3 : out std_logic );
  end component;

  signal D0, D1, D2, D3 : std_logic;          -- 시그널 선언
  signal Q0, Q1, Q2, Q3 : std_logic;

begin
  UUT : toGray port map (                     -- toGray 컴포넌트의 포트와 시그널을 연결
    D0 => D0,
    D1 => D1,
    D2 => D2,
    D3 => D3,
    Q0 => Q0,
    Q1 => Q1,
    Q2 => Q2,
    Q3 => Q3
  );
                                              -- 0000부터 1111까지 10ns 간격으로 입력값 전달
  D0 <= '0', '1' after 10 ns,  '0' after 20 ns,  '1' after 30 ns,
             '0' after 40 ns,  '1' after 50 ns,  '0' after 60 ns,
             '1' after 70 ns,  '0' after 80 ns,  '1' after 90 ns,
             '0' after 100 ns, '1' after 110 ns, '0' after 120 ns,
             '1' after 130 ns, '0' after 140 ns, '1' after 150 ns;

  D1 <= '0', '1' after 20 ns, '0' after 40 ns,  '1' after 60 ns,
             '0' after 80 ns, '1' after 100 ns, '0' after 120 ns,
             '1' after 140 ns;

  D2 <= '0', '1' after 40 ns, '0' after 80 ns, '1' after 120 ns;

  D3 <= '0', '1' after 80 ns;
end tb_arch;
