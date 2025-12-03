-- S ARbogast
-- JHU 677 
-- 16 bit subtraction design
-- difference = minuend - subtrahend

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;
use work.all;

entity sub16 is
  Port ( minu: in signed(15 downto 0 );
         subt: in signed(15 downto 0 );
         diff: out signed(15 downto 0 )
         );
end add16;

architecture Behavioral of sub16 is

begin
    
diff <= minu - subt;

end Behavioral;
