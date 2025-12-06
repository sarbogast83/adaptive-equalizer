---------------------------------------
--
-- AE_top.h
-- 
-- adaptive equalizer top level design
-- 12 tap adaptive equalizer using LSM 
-- 
-- requires:
--      sub.vhd
--      AE_FIR.vhd
--      CUunit.vhd
--      
---------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.all;

entity AE_top is 
port( 
	clk, reset: in std_logic;
	dn, un: in signed(15 downto 0);
	dhatOut, enOut: out signed (15 downto 0);
	wn0, wn1, wn2, wn3, wn4, wn5, wn6, wn7, wn8, wn9, wn10, wn11: out signed(15 downto 0)
	);
end AE_top;

architecture Behavioral of AE_top is -----------------------------------------------------
  
    signal dnp5, dhat16: signed(15 downto 0):= (others => '0');
    signal dhat32: signed(31 downto 0):= (others => '0');
    signal en, u0, u1, u2, u3, u4, u5, u6, u7, u8, u9,u10, u11: signed(15 downto 0):= (others => '0');
    signal w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11: signed(15 downto 0):= (others => '0');
    --signal M: unsigned(4 downto 0);

------------------------------------------------------------------------------------------	
component CUunit is 
port(
	clk, reset: in std_logic;
	 en, u0, u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11: in signed(15 downto 0);
     w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11: out signed(15 downto 0)
	);
end component;
component delayBlock is 
	port( clk, reset: in std_logic;
		  rk: in signed (15 downto 0);
		  rkp5: out signed (15 downto 0)
		  );
end component;
component sub16 is
  Port ( minu: in signed(15 downto 0 );
         subt: in signed(15 downto 0 );
         diff: out signed(15 downto 0 )
         );
end component;
component AE_FIR_DF is 
port (
    reset, clk   : in std_logic;
    xn      : in signed(15 downto 0);
    b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11: in signed(15 downto 0);
	u0, u1,u2,u3,u4,u5,u6,u7,u8,u9,u10,u11: out signed(15 downto 0);
    yn      : out signed(31 downto 0)
	);
end component;

begin -------------------------------------------------------------------------------------
	delayline: delayBlock port map(clk => clk, reset => reset, rk => dn , rkp5 => dnp5);
	AEfirBlock: AE_FIR_DF port map(clk => clk, reset => reset, xn => un,
									b0 => w0, b1 => w1, b2 => w2, b3 => w3, b4 => w4, b5 => w5, b6 => w6, b7 => w7, b8 => w8, b9 => w9, b10 => w10, b11 => w11, 
									u0 => u0, u1 => u1, u2 => u2, u3 => u3, u4 => u4, u5 => u5,u6 => u6, u7 => u7, u8 => u8, u9 => u9,u10 => u10, u11 => u11,
									yn => dhat32  );
	 dhat16 <= dhat32(29 downto 14) ;
	
	errorBlock: sub16 port map(minu  => dnp5, subt => dhat16, diff => en);
	updateBlock: CUunit port map(clk => clk, reset => reset, en => en, 
	                               u0 => u0, u1 => u1, u2 => u2, u3 => u3, u4 => u4, u5 => u5, u6 => u6, u7 => u7, u8 => u8, u9 => u9,u10 => u10, u11 => u11, 
	                               w0 => w0, w1 => w1, w2 => w2, w3 => w3, w4 => w4, w5 => w5, w6 => w6, w7 => w7, w8 => w8, w9 => w9, w10 => w10, w11 => w11);

	dhatOut <= dhat16;
	enOut <= en;
	wn0 <= w0;
	wn1 <= w1;
	wn2 <= w2;
	wn3 <= w3;
	wn4 <= w4;
	wn5 <= w5;
	wn6 <= w6;
	wn7 <= w7;
	wn8 <= w8;
	wn9 <= w9;
	wn10 <= w10;
	wn11 <= w11;
	
end Behavioral;------------------------------------