library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;

entity project is
 port(a, b, c, d, e, f, g, h, i : in std_logic;
      oddparity, evenparity : out std_logic);
end project;

architecture paritycheck of project is
 begin
  process(a, b, c, d, e, f, g, h, i)
   variable odd,even : std_logic;
    begin

if (a='0'and b ='0' and c='0' and d='0' and e='0' and f='0' and g='0' and h='0' and i='0') then
odd <= '0';
else 
(odd:='0');
end if;



oddparity <= odd;
evenparity <= even;
    end process;
end paritycheck;