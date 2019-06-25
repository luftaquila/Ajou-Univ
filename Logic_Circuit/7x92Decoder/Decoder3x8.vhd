library ieee;
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

  signal sig_Q : STD_LOGIC_VECTOR(7 downto 0);

  begin
    process(sig_Q)
      begin
        if e = '1' then
           if I = "000" then sig_Q <= "00000001";
        elsif I = "001" then sig_Q <= "00000010";
        elsif I = "010" then sig_Q <= "00000100";
        elsif I = "011" then sig_Q <= "00001000";
        elsif I = "100" then sig_Q <= "00010000";
        elsif I = "101" then sig_Q <= "00100000";
        elsif I = "110" then sig_Q <= "01000000";
        elsif I = "111" then sig_Q <= "10000000";
        end if;
      else sig_Q <= "00000000";
    end if;
  end process;

  Q <= sig_Q;

end architecture D3x8;
