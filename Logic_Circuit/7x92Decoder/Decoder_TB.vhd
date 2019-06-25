
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

entity tb is
end tb;

architecture tb_arch of tb is
  component controller
  port(
    A : in integer;
    Q : out STD_LOGIC_VECTOR(91 downto 0)
  );
  end component;

  signal A : integer := 20;
  signal Q : STD_LOGIC_VECTOR(91 downto 0);

begin
  UUT : controller port map (
    A => A, Q => Q
  );

  A <= 20;
end tb_arch;
