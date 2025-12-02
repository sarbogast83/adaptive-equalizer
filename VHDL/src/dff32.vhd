-- S ARbogast
-- JHU 677 
-- 32 bit d flip-flop design

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;
use work.all;

entity dff32 is 
port(
    reset : in std_logic ;
    clk : in std_logic ;
    d : in signed (31 downto 0);
    q : out signed(31 downto 0)
    );
end dff32;

architecture Behavioral of dff32 is

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