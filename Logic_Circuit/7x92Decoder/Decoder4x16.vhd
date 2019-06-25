library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

entity decoder4x16 is
  port(
    e : in STD_LOGIC;
    I : in STD_LOGIC_VECTOR(3 downto 0);
    Q : out STD_LOGIC_VECTOR(15 downto 0)
  );
end decoder4x16;

architecture D4x16 of decoder4x16 is

  signal sig_Q : STD_LOGIC_VECTOR(15 downto 0);

  begin
    process(sig_Q)
      begin
        if e = '1' then
             if I = "0000" then sig_Q <= "0000000000000001";
          elsif I = "0001" then sig_Q <= "0000000000000010";
          elsif I = "0010" then sig_Q <= "0000000000000100";
          elsif I = "0011" then sig_Q <= "0000000000001000";
          elsif I = "0100" then sig_Q <= "0000000000010000";
          elsif I = "0101" then sig_Q <= "0000000000100000";
          elsif I = "0110" then sig_Q <= "0000000001000000";
          elsif I = "0111" then sig_Q <= "0000000010000000";
          elsif I = "1000" then sig_Q <= "0000000100000000";
          elsif I = "1001" then sig_Q <= "0000001000000000";
          elsif I = "1010" then sig_Q <= "0000010000000000";
          elsif I = "1011" then sig_Q <= "0000100000000000";
          elsif I = "1100" then sig_Q <= "0001000000000000";
          elsif I = "1101" then sig_Q <= "0010000000000000";
          elsif I = "1110" then sig_Q <= "0100000000000000";
          elsif I = "1111" then sig_Q <= "1000000000000000";
        end if;
      else sig_Q <= "0000000000000000";
    end if;
  end process;

  Q <= sig_Q;
end architecture D4x16;
