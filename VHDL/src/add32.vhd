-- S ARbogast
-- JHU 677 
-- 32 bit adder design

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;
use work.all;

entity add32 is
  Port ( a: in signed(31 downto 0 );
         b: in signed(31 downto 0 );
         c: out signed(31 downto 0 )
         );
end add32;

architecture Behavioral of add32 is

begin
 
    c <= a + b;

end Behavioral;
