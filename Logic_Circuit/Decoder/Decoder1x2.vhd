library ieee;                                 -- IEEE 라이브러리 사용
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

entity decoder1x2 is
  port(
    e : in STD_LOGIC;
    I : in STD_LOGIC;
    Q : out STD_LOGIC_VECTOR(1 downto 0)
  );
end decoder1x2;

architecture D1x2 of decoder1x2 is
  begin
    process
      begin
      if e = '1' then
           if I = '0' then Q <= "01";
        elsif I = '1' then Q <= "10";
      end if;
      else Q <= "00";
    end if;
  end process;
end architecture D1x2;
