library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.numeric_std.all;

entity controller is
port(
  A : in integer;                                   -- 입력 포트
  Q : out STD_LOGIC_VECTOR(91 downto 0)             -- 출력 포트(92비트)
);
end controller;

architecture structure of controller is

  signal I : STD_LOGIC_VECTOR(6 downto 0);          -- 2진 입력 신호(7비트)
  signal e : STD_LOGIC_VECTOR(11 downto 0);         -- 개별 디코더 enable 여부 결정
  signal sig_Q : STD_LOGIC_VECTOR(91 downto 0);     -- 출력 신호(92비트)

  begin
  process(e, I)
    begin
      e <= "000000000000";                          -- 디코더 enable 신호 모두 0으로 초기화

      -- 입력 신호에 따라 몇 번 디코더를 활성화할지 여부를 결정해, enable 신호의 해당 비트 번호만 1로 변경한다.
      -- 또한, 해당 디코더에 전달할 입력값을 결정해 2진 코드로 변환한 후 저장한다.
         if (A >= 0 and A < 8)   then e(0)  <= '1'; I <= std_logic_vector(to_unsigned(A     , I'length));   -- DEV0
      elsif (A >= 8 and A < 16)  then e(1)  <= '1'; I <= std_logic_vector(to_unsigned(A - 8 , I'length));   -- DEV1
      elsif (A >= 16 and A < 24) then e(2)  <= '1'; I <= std_logic_vector(to_unsigned(A - 16, I'length));   -- DEV2
      elsif (A >= 24 and A < 28) then e(3)  <= '1'; I <= std_logic_vector(to_unsigned(A - 24, I'length));   -- DEV3
      elsif (A >= 28 and A < 32) then e(4)  <= '1'; I <= std_logic_vector(to_unsigned(A - 28, I'length));   -- DEV4
      elsif (A >= 32 and A < 36) then e(5)  <= '1'; I <= std_logic_vector(to_unsigned(A - 32, I'length));   -- DEV5
      elsif (A >= 36 and A < 40) then e(6)  <= '1'; I <= std_logic_vector(to_unsigned(A - 36, I'length));   -- DEV6
      elsif (A >= 40 and A < 56) then e(7)  <= '1'; I <= std_logic_vector(to_unsigned(A - 40, I'length));   -- DEV7
      elsif (A >= 56 and A < 72) then e(8)  <= '1'; I <= std_logic_vector(to_unsigned(A - 56, I'length));   -- DEV8
      elsif (A >= 72 and A < 88) then e(9)  <= '1'; I <= std_logic_vector(to_unsigned(A - 72, I'length));   -- DEV9
      elsif (A >= 88 and A < 90) then e(10) <= '1'; I <= std_logic_vector(to_unsigned(A - 88, I'length));   -- DEV10
      elsif (A >= 90 and A < 92) then e(11) <= '1'; I <= std_logic_vector(to_unsigned(A - 90, I'length));   -- DEV11
    end if;
  end process;

  -- 앞서 설계한 개별 디코더를 DEV 번호에 맞게 불러와 enable신호를 전달한다.
  -- 각 디코더의 입력 비트 수에 맞게 앞서 설정한 입력값을 잘라 전달한다.
  -- 각 디코더 출력 전체 출력 92비트 중 각 디코더가 담당하는 출력 부분에 저장한다.
  DEV0  : entity work.decoder3x8  port map(e(0) , I(2 downto 0), sig_Q(7  downto 0));
  DEV1  : entity work.decoder3x8  port map(e(1) , I(2 downto 0), sig_Q(15 downto 8));
  DEV2  : entity work.decoder3x8  port map(e(2) , I(2 downto 0), sig_Q(23 downto 16));
  DEV3  : entity work.decoder2x4  port map(e(3) , I(1 downto 0), sig_Q(27 downto 24));
  DEV4  : entity work.decoder2x4  port map(e(4) , I(1 downto 0), sig_Q(31 downto 28));
  DEV5  : entity work.decoder2x4  port map(e(5) , I(1 downto 0), sig_Q(35 downto 32));
  DEV6  : entity work.decoder2x4  port map(e(6) , I(1 downto 0), sig_Q(39 downto 36));
  DEV7  : entity work.decoder4x16 port map(e(7) , I(3 downto 0), sig_Q(55 downto 40));
  DEV8  : entity work.decoder4x16 port map(e(8) , I(3 downto 0), sig_Q(71 downto 56));
  DEV9  : entity work.decoder4x16 port map(e(9) , I(3 downto 0), sig_Q(87 downto 72));
  DEV10 : entity work.decoder1x2  port map(e(10), I(0)         , sig_Q(89 downto 88));
  DEV11 : entity work.decoder1x2  port map(e(11), I(0)         , sig_Q(91 downto 90));

  Q <= sig_Q;   -- 출력 신호를 출력 포트에 전달한다.

end architecture structure;
