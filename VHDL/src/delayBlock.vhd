------------------------------------------------------
-- S Arbogast
-- JHU 677 
-- requires: dff16
--
--  delay unit produces output at time T(6)
--
--------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;
use work.all;

entity delayBlock is 
	port( clk, reset: in std_logic;
		  rk: in signed (15 downto 0);
		  rkp5: out signed (15 downto 0)
		  );
end delayBlock;

architecture Behavioral of delayBlock is 

signal rkp1, rkp2, rkp3, rkp4: signed(15 downto 0);

component dff16 is 
port(
    reset : in std_logic ;
    clk : in std_logic ;
    d : in signed (15 downto 0);
    q : out signed(15 downto 0)
    );
end component;
begin

U0_dff:  dff16 port map( reset => reset, clk => clk, d => rk,   q => rkp1); 
U1_dff:  dff16 port map( reset => reset, clk => clk, d => rkp1, q => rkp2); 
U2_dff:  dff16 port map( reset => reset, clk => clk, d => rkp2, q => rkp3); 
U3_dff:  dff16 port map( reset => reset, clk => clk, d => rkp3, q => rkp4); 
U4_dff:  dff16 port map( reset => reset, clk => clk, d => rkp4, q => rkp5); 

end Behavioral;
		