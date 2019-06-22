LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY tb IS
END tb;

ARCHITECTURE behavior OF tb IS

    signal a,b,c : std_logic := '0';
   signal sum,carry : std_logic;

BEGIN

    -- Instantiate the Unit Under Test (UUT)
   uut: entity work.FA PORT MAP (a,b,c,sum,carry);

   -- Applying inputs to the entity under test
   stim_proc: process
   begin
      a <= '0'; b <= '0';   c <= '0';   wait for 100 ns;
        a <= '0';   b <= '0';   c <= '1';   wait for 100 ns;
        a <= '0';   b <= '1';   c <= '0';   wait for 100 ns;
        a <= '0';   b <= '1';   c <= '1';   wait for 100 ns;
        a <= '1';   b <= '0';   c <= '0';   wait for 100 ns;
        a <= '1';   b <= '0';   c <= '1';   wait for 100 ns;
        a <= '1';   b <= '1';   c <= '0';   wait for 100 ns;
        a <= '1';   b <= '1';   c <= '1';   wait for 100 ns;
        wait;
   end process;

END;
