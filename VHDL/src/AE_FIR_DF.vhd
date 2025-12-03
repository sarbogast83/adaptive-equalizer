---------------------------------------------------
-- S Arbogast
--
-- 12-tap adaptive fitler designed with DF FIR
-- Requires: FIRcellDF
-- input:  
-- 		xn: data
-- 	    b: coef
-- 
-- output:
-- 		un: delayed xn
-- 		yn: filtered data
-----------------------------------------------------
 
library IEEE;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.all;

entity AE_FIR_DF is 
port (
    reset, clk   : in std_logic;
    xn      : in signed(15 downto 0);
    b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11: in signed(15 downto 0);
	u0, u1,u2,u3,u4,u5,u6,u7,u8,u9,u10,u11: out signed(15 downto 0);
    yn      : out signed(31 downto 0)
	);
end AE_FIR_DF;

architecture rtl of AE_FIR_DF is

    signal r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10 : signed(15 downto 0);
    signal s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10 : signed(31 downto 0);
	signal pass: signed(15 downto 0);
    signal xq : signed(15 downto 0);
    signal yd : signed(31 downto 0);
	
	component FIRcellDF is port (
		reset   : in std_logic;
		clk     : in std_logic;
		rk      : in signed(15 downto 0);
		sk      : in signed(31 downto 0);
		bk      : in signed(15 downto 0);
		rkp1    : out signed(15 downto 0);
		skp1    : out signed(31 downto 0));
	end component;
    
       
begin
	-- fir design
    FIRcellDF_U0:  FIRcellDF port map (reset => reset, clk => clk, rk => xn, sk => (others => '0'), bk => b0, rkp1 => r0, skp1 => s0);
    FIRcellDF_U1:  FIRcellDF port map (reset => reset, clk => clk, rk => r0, sk => s0, bk => b1, rkp1 => r1, skp1 => s1);
    FIRcellDF_U2:  FIRcellDF port map (reset => reset, clk => clk, rk => r1, sk => s1, bk => b2, rkp1 => r2, skp1 => s2);
    FIRcellDF_U3:  FIRcellDF port map (reset => reset, clk => clk, rk => r2, sk => s2, bk => b3, rkp1 => r3, skp1 => s3);
    FIRcellDF_U4:  FIRcellDF port map (reset => reset, clk => clk, rk => r3, sk => s3, bk => b4, rkp1 => r4, skp1 => s4);
    FIRcellDF_U5:  FIRcellDF port map (reset => reset, clk => clk, rk => r4, sk => s4, bk => b5, rkp1 => r5, skp1 => s5);
    FIRcellDF_U6:  FIRcellDF port map (reset => reset, clk => clk, rk => r5, sk => s5, bk => b6, rkp1 => r6, skp1 => s6);
    FIRcellDF_U7:  FIRcellDF port map (reset => reset, clk => clk, rk => r6, sk => s6, bk => b7, rkp1 => r7, skp1 => s7);
    FIRcellDF_U8:  FIRcellDF port map (reset => reset, clk => clk, rk => r7, sk => s7, bk => b8, rkp1 => r8, skp1 => s8);
    FIRcellDF_U9:  FIRcellDF port map (reset => reset, clk => clk, rk => r8, sk => s8, bk => b9, rkp1 => r9, skp1 => s9);
    FIRcellDF_U10: FIRcellDF port map (reset => reset, clk => clk, rk => r9, sk => s9, bk => b10, rkp1 => r10, skp1 => s10);
	FIRcellDF_U11: FIRcellDF port map (reset => reset, clk => clk, rk => r10, sk => s10, bk => b11, rkp1 => r11, skp1 => yn);
	
	-- pass cell output to out port
	--pass <= xn;
	u0 <= xn;
	u1 <= r0;
	u2 <= r1;
	u3 <= r2;
	u4 <= r3;
	u5 <= r4;
	u6 <= r5;
	u7 <= r6;
	u8 <= r7;
	u9 <= r8;
	u10 <= r9;
	u11 <= r10;
	
	
end rtl;