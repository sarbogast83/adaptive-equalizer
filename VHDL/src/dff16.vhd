-- S ARbogast
-- JHU 677 
-- 16 bit d flip-flop design

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;
use work.all;

entity dff16 is 
port(
    reset : in std_logic ;
    clk : in std_logic ;
    d : in signed (15 downto 0);
    q : out signed(15 downto 0)
    );
end dff16;

architecture Behavioral of dff16 is

begin

process(reset,clk)

begin
    if(reset = '1') then 
        q <= (others => '0');
    elsif (rising_edge (clk)) then 
        q <= d;
    end if;
end process;

end Behavioral;