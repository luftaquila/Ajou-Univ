library ieee;                                 -- IEEE 라이브러리 사용
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.numeric_std.all;

entity controller is
port(
  A : in integer;
  Q : out STD_LOGIC_VECTOR(91 downto 0)
);
end controller;

architecture structure of controller is

  signal I : STD_LOGIC_VECTOR(6 downto 0);
  signal e : STD_LOGIC_VECTOR(11 downto 0);

  begin
    I <= std_logic_vector(to_unsigned(A, I'length));
    e <= "000000000000";

  process
    begin
      if (A >= 0 and A < 8) then e(0) <= '1';
      elsif (A >= 8 and A < 16)  then e(1) <= '1';
      elsif (A >= 16 and A < 24) then e(2) <= '1';
      elsif (A >= 24 and A < 28) then e(3) <= '1';
      elsif (A >= 28 and A < 32) then e(4) <= '1';
      elsif (A >= 32 and A < 36) then e(5) <= '1';
      elsif (A >= 36 and A < 40) then e(6) <= '1';
      elsif (A >= 40 and A < 56) then e(7) <= '1';
      elsif (A >= 56 and A < 72) then e(8) <= '1';
      elsif (A >= 72 and A < 88) then e(9) <= '1';
      elsif (A >= 88 and A < 90) then e(10) <= '1';
      elsif (A >= 90 and A < 92) then e(11) <= '1';
    end if;
  end process;

    DEV0 : entity work.decoder3x8 port map(e(0), , Q(7 downto 0));
    DEV1 : entity work.decoder3x8 port map(e(1), , Q(15 downto 8));
    DEV2 : entity work.decoder3x8 port map(e(2), , Q(23 downto 16));
    DEV3 : entity work.decoder2x4 port map(e(3), , Q(27 downto 24));
    DEV4 : entity work.decoder2x4 port map(e(4), , Q(31 downto 28));
    DEV5 : entity work.decoder2x4 port map(e(5), , Q(35 downto 32));
    DEV6 : entity work.decoder2x4 port map(e(6), , Q(39 downto 36));
    DEV7 : entity work.decoder4x16 port map(e(7), , Q(55 downto 40));
    DEV8 : entity work.decoder4x16 port map(e(8), , Q(71 downto 56));
    DEV9 : entity work.decoder4x16 port map(e(9), , Q(87 downto 72));
    DEV10 : entity work.decoder1x2 port map(e(10), , Q(89 downto 88));
    DEV11 : entity work.decoder1x2 port map(e(11), , Q(91 downto 90));

end architecture structure;
