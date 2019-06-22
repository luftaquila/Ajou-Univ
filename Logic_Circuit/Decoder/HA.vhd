library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

--half adder entity
entity HA is
port(a,b : in std_logic;
            sum,carry : out std_logic
        );
end HA;

-------------------Architecture 1 starts here.
architecture Gate_level of HA is

begin

sum <= a xor b;
carry <= a and b;

end architecture Gate_level;
-------------------Architecture 1 ends here.

-------------------Architecture 2 starts here.
architecture Behavioral of HA is

begin

process(a,b)
begin
    if(a = '0' and b = '0') then
        sum <= '0';
        carry <= '0';
    elsif(a = '0' and b = '1') then
        sum <= '1';
        carry <= '0';
    elsif(a = '1' and b = '0') then
        sum <= '1';
        carry <= '0';
    else
        sum <= '0';
        carry <= '1';
    end if;
end process;

end architecture Behavioral;
-------------------Architecture 2 ends here.
