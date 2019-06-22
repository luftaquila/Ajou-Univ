library IEEE;
use IEEE.std_logic_1164.all;

--full adder entity
entity FA is
port (  a,b,c : in std_logic;
            sum,carry : out std_logic
        );
end FA;

architecture struct of FA is

    signal s1,c1,c2 : std_logic;    --intermediate signals

begin

    --direct/entity instantation method.
    HA1 : entity work.HA(Gate_level)  port map(a,b,s1,c1); --use architecture 1 of HA entity
    HA2 : entity work.HA(Behavioral) port map(s1,c,sum,c2); --use architecture 2 of HA entity

    carry <= c1 or c2;

end architecture struct;
