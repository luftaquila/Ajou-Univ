library ieee;                                 -- IEEE 라이브러리 사용
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

entity decoder2x4 is
  port(
    e : in STD_LOGIC;
    I : in STD_LOGIC_VECTOR(1 downto 0);
    Q : out STD_LOGIC_VECTOR(3 downto 0)
  );
end decoder2x4;

architecture D2x4 of decoder2x4 is
  begin
    process
      begin
        if e = '1' then
             if I = "00" then Q <= "0001";
          elsif I = "01" then Q <= "0010";
          elsif I = "10" then Q <= "0100";
          elsif I = "11" then Q <= "1000";
        end if;
      else Q <= "0000";
    end if;
  end process;
end architecture D2x4;
