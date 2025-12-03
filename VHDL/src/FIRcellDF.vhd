-- Direct Form FIR cell
library IEEE;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.all;

entity FIRcellDF is port (
    reset   : in std_logic;
    clk     : in std_logic;
    rk      : in signed(15 downto 0);
    sk      : in signed(31 downto 0);
    bk      : in signed(15 downto 0);
    rkp1    : out signed(15 downto 0);
    skp1    : out signed(31 downto 0));
end FIRcellDF;

architecture rtl of FIRcellDF is

signal mk : signed(31 downto 0);

component dff16 is 
port(
    reset : in std_logic ;
    clk : in std_logic ;
    d : in signed (15 downto 0);
    q : out signed(15 downto 0)
    );
end component;
component add32 is
  Port ( a: in signed(31 downto 0 );
         b: in signed(31 downto 0 );
         c: out signed(31 downto 0 )
         );
end component;
component mult16 is
  Port (a: in signed(15 downto 0 );
        b: in signed(15 downto 0 );
        c: out signed(31 downto 0 )
        );
end component;
   
begin
   
    U_dff16: dff16 port map (reset => reset, clk => clk, d => rk, q => rkp1);
    U_mult16: mult16 port map ( a => rk, b => bk, c => mk);
    U_add32: add32 port map ( a => sk, b => mk, c => skp1);
	
end rtl;
