----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 12/03/2025 03:26:26 PM
-- Design Name: 
-- Module Name: FIRtestbench - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------

library IEEE;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use STD.textio.all;
use ieee.std_logic_textio.all;
use work.all;

entity FIRtestbench is
end FIRtestbench;

architecture Behavioral of FIRtestbench is

    signal clk    : std_logic := '0';
    signal reset    : std_logic := '1';
    signal xn   : signed(15 downto 0);
    signal dhat32      : signed(31 downto 0);
    signal w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11: signed(15 downto 0):= (others => '0');
    signal u0, u1, u2, u3, u4, u5, u6, u7, u8, u9,u10, u11: signed(15 downto 0):= (others => '0');
--    type array_type is array (0 to 11) of signed(15 downto 0);
--    signal w       : array_type;
    
    component AE_FIR_DF is 
    port (
        reset, clk   : in std_logic;
        xn      : in signed(15 downto 0);
        b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11: in signed(15 downto 0);
        u0, u1,u2,u3,u4,u5,u6,u7,u8,u9,u10,u11: out signed(15 downto 0);
        yn      : out signed(31 downto 0)
        );
    end component ;

begin

    -- reset process
    process
	begin
		reset <= '1', '0' after 105 ns;
		wait;
	end process;

    -- clock process
    process
    begin
        clk <= not clk;
        wait for 10 ns;
        clk <= not clk;
        wait for 10 ns;
    end process;
process(reset, clk)
    
        file xn_fp          : text open read_mode is "C:\vivado_DSP\adaptiveFIR\data\xn_int.txt";
        variable v_ILINE    : line;
        variable xn_data    : integer;
    
    begin
        if(reset = '1') then
            xn <= (others => '0');
        elsif(rising_edge(clk)) then
            readline(xn_fp, v_ILINE);
            read(v_ILINE, xn_data);
            xn <= to_signed(xn_data, 16);
        end if;
    end process;




AEfirBlock: AE_FIR_DF port map(clk => clk, reset => reset, xn => xn,
									b0 => w0, b1 => w1, b2 => w2, b3 => w3, b4 => w4, b5 => w5, b6 => w6, b7 => w7, b8 => w8, b9 => w9, b10 => w10, b11 => w11, u0 => u0, u1 => u1, u2 => u2, u3 => u3, u4 => u4, u5 => u5,u6 => u6, u7 => u7, u8 => u8, u9 => u9,u10 => u10, u11 => u11,
									yn => dhat32  );


end Behavioral;
