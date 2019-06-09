ibrary ieee;
use ieee.std_logic_1164.all;
entity parity_gate_tb is
end parity_gate_tb;

architecture sample_tb of parity_gate_tb is

component parity_gate
port(

I_0,I_1,I_2,I_3,I_4,I_5,I_6,I_7,I_8: in std_logic;

Even_parity,Odd_parity: out std_logic);

end component;

signal i_0,i_1,i_2,i_3,i_4,i_5,i_6,i_7,i_8,even_parity,odd_parity: std_logic;

begin

U0: parity_gate port map(i_0=>I_0,i_1=>I_1,i_2=>I_2,i_3=>I_3,i_4=>I_4,i_5=>I_5,i_6=>I_6,i_7=>I_7,i_8=>I_8,even_parity=>Even_parity,odd_parity=>Odd_parity);

process
begin	

i_0<='0';

i_1<='1';

i_2<='1';

i_3<='0';

i_4<='0';

i_5<='0';

i_6<='1';

i_7<='0';

i_8<='0';

wait for 10 ns;
end process;
end sample_tb;

