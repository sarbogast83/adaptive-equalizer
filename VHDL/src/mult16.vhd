-- S ARbogast
-- JHU 677 
-- 16 bit multiplier design

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;
use work.all;

entity mult16 is
  Port (a: in signed(15 downto 0 );
        b: in signed(15 downto 0 );
        c: out signed(31 downto 0 )
        );
end mult16;

architecture Behavioral of mult16 is

begin

    c <= a * b;

end Behavioral;
