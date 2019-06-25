library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

entity decoder1x2 is  -- 디코더 엔티티 선언
  port(
    e : in STD_LOGIC;                     -- enable 핀 입력
    I : in STD_LOGIC;                     -- 디코더 입력 신호(1비트)
    Q : out STD_LOGIC_VECTOR(1 downto 0)  -- 디코더 출력 신호(2비트)
  );
end decoder1x2;

architecture D1x2 of decoder1x2 is  -- 아키텍쳐 정의

  signal sig_Q : STD_LOGIC_VECTOR(1 downto 0);  -- 2비트 출력 시그널 정의

  begin
    process(sig_Q)
      begin
      if e = '1' then                           -- enable 되었을 경우만
           if I = '0' then sig_Q <= "01";       -- 입력에 맞는 출력 결정
        elsif I = '1' then sig_Q <= "10";
      end if;
      else sig_Q <= "00";                  -- enable이 false일 경우 출력 없음.
    end if;
  end process;

  Q <= sig_Q;  -- 출력 포트에 출력 전달

end architecture D1x2;
