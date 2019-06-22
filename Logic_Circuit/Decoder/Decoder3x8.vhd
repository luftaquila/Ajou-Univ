library ieee;                                 -- IEEE 라이브러리 사용
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

entity decoder3x8 is
  port(
    e : in STD_LOGIC;
    I : in STD_LOGIC_VECTOR(2 downto 0);
    Q : out STD_LOGIC_VECTOR(7 downto 0)
  );
end decoder3x8;

architecture D3x8 of decoder3x8 is
  begin
    process
      begin
        if e = '1' then
          if I = "000" then    Q <= "00000001";
          elsif I = "001" then Q <= "00000010";
          elsif I = "010" then Q <= "00000100";
          elsif I = "011" then Q <= "00001000";
          elsif I = "100" then Q <= "00010000";
          elsif I = "101" then Q <= "00100000";
          elsif I = "110" then Q <= "01000000";
          elsif I = "111" then Q <= "10000000";
        end if;
      else Q <= "00000000";
    end if;
  end process;
end architecture D3x8;
