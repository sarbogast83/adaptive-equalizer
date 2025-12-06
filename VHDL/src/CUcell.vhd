------------------------------------------
-- S Arbogast
-- 
-- CUcell.h
-- 
-- computationtion cell for adaptive filter coef update 
-- w(n+1) = w(n) + mu * u(n) * e(n)
-- 
-------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;
use work.all;


entity CUcell is 
port(
	clk, reset: in std_logic;
	un, en: in signed(15 downto 0);
	wnp1: out signed(15 downto 0)
	);
end CUcell;

architecture Behavioral of CUcell is

	signal ak, akp1, mk16: signed(15 downto 0):= (others => '0');
	signal mk32, shiftmk: signed(31 downto 0):= (others => '0');
	--signal mu_N: unsigned(4 downto 0);

	component dff16 is
	port(
		reset : in std_logic ;
		clk : in std_logic ;
		d : in signed (15 downto 0);
		q : out signed(15 downto 0)
		);
	end component;
	component add16 is
	  Port ( a: in signed(15 downto 0 );
			 b: in signed(15 downto 0 );
			 c: out signed(15 downto 0 )
			 );
	end component;
	component mult16 is
	  Port (a: in signed(15 downto 0 );
			b: in signed(15 downto 0 );
			c: out signed(31 downto 0 )
			);
	end component;

begin

	U0_mult: mult16 port map ( a => un, b => en, c => mk32);
	shiftmk <= (shift_right(mk32, 20));
	mk16 <= shiftmk(15 downto 0);
--	mk16 <= resize(mk32(31 downto 20),16);
	U_add: add16 port map ( a => mk16, b => akp1, c => ak);
	U_dff: dff16 port map (reset => reset, clk => clk, d => ak, q => akp1);
	wnp1 <= akp1;

end Behavioral;