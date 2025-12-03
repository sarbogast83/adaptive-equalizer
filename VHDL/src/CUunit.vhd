----------------------------------------
-- S Arbogast
--
-- CUunit
-- 
-- adaptive filter coef update block 
-- combination of 12 CUcells
-- requries: CUcell.vhd
-----------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;
use work.all;

entity CUunit is 
port(
	clk, reset: in std_logic;
	 en, u0, u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11: in signed(15 downto 0);
     w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11: out signed(15 downto 0)
	);
end CUunit;

architecture Behavioral of CUunit is 

component CUcell is 
	port(
		clk, reset: in std_logic;
		un, en: in signed(15 downto 0);
		wnp1: out signed(15 downto 0)
		);
end component;

begin 

	U0_CUcell = CUcell port map(clk => clk, reset => reset, en => en, un => u0, wnp1 => w0);
	U1_CUcell = CUcell port map(clk => clk, reset => reset, en => en, un => u1, wnp1 => w1);
	U2_CUcell = CUcell port map(clk => clk, reset => reset, en => en, un => u2, wnp1 => w2);
	U3_CUcell = CUcell port map(clk => clk, reset => reset, en => en, un => u3, wnp1 => w3);
	U4_CUcell = CUcell port map(clk => clk, reset => reset, en => en, un => u4, wnp1 => w4);
	U5_CUcell = CUcell port map(clk => clk, reset => reset, en => en, un => u5, wnp1 => w5);
	U6_CUcell = CUcell port map(clk => clk, reset => reset, en => en, un => u6, wnp1 => w6);
	U7_CUcell = CUcell port map(clk => clk, reset => reset, en => en, un => u7, wnp1 => w7);
	U8_CUcell = CUcell port map(clk => clk, reset => reset, en => en, un => u8, wnp1 => w8);
	U9_CUcell = CUcell port map(clk => clk, reset => reset, en => en, un => u9, wnp1 => w9);
	U10_CUcell = CUcell port map(clk => clk, reset => reset, en => en, un => u10, wnp1 => w10);
	U11_CUcell = CUcell port map(clk => clk, reset => reset, en => en, un => u11, wnp1 => w11);

end Behavioral;