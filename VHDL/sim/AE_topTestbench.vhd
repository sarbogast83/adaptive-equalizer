library IEEE;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use STD.textio.all;
use ieee.std_logic_textio.all;
use work.all;

library STD;
use std.textio.all;

entity AE_topTestbench is
-- empty entity			
end AE_topTestbench;

architecture testbench of AE_topTestbench is
   

signal clock    : std_logic := '0';
signal reset    : std_logic := '1';
signal dn, un   : signed(15 downto 0);
signal dhatOut, enOut       : signed(15 downto 0);
--signal wn0, wn1, wn2, wn3, wn4, wn5, wn6, wn7, wn8, wn9, wn10, wn11: signed(15 downto 0);
signal clk_count: unsigned(9 downto 0); -- 10 bit counter for clock
type array_type is array (0 to 11) of signed(15 downto 0);
signal wn       : array_type;

component AE_top is 
port( 
	clk, reset: in std_logic;
	dn, un: in signed(15 downto 0);
	dhatOut, enOut: out signed (15 downto 0);
	wn0, wn1, wn2, wn3, wn4, wn5, wn6, wn7, wn8, wn9, wn10, wn11: out signed(15 downto 0)
	);
end component;

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
        clock <= not clock;
        wait for 10 ns;
        clock <= not clock;
        wait for 10 ns;
    end process;
    
    -- process to open file and read each data sample on every riding edge of the clock
    -- dn
	process(reset, clock)
    
        file dn_fp          : text open read_mode is "C:\vivado_DSP\adaptiveFIR\data\dn_int.txt";
        variable v_ILINE    : line;
        variable dn_data    : integer;
    
    begin
        if(reset = '1') then
            dn <= (others => '0');
        elsif(rising_edge(clock)) then
            readline(dn_fp, v_ILINE);
            read(v_ILINE, dn_data);
            dn <= to_signed(dn_data, 16);
        end if;
    end process;
	-- un
	process(reset, clock)
    
        file un_fp          : text open read_mode is "C:\vivado_DSP\adaptiveFIR\data\un_int.txt";
        variable v_ILINE    : line;
        variable un_data    : integer;
    
    begin
        if(reset = '1') then
            un <= (others => '0');
        elsif(rising_edge(clock)) then
            readline(un_fp, v_ILINE);
            read(v_ILINE, un_data);
            un <= to_signed(un_data, 16);
        end if;
    end process;
    
    -- Instantiate Filter here
    DUT: AE_top port map( 
		clk => clock, 
		reset => reset, 
		dn => dn, 
		un => un,
		dhatOut => dhatOut, 
		enOut => enOut,
		wn0 => wn(0), wn1 => wn(1), wn2 => wn(2), wn3 => wn(3), wn4 => wn(4), wn5 => wn(5), wn6 => wn(6), wn7 => wn(7), wn8 => wn(8), wn9 => wn(9), wn10 => wn(10), wn11=> wn(11)
	);
    
    -- process to open file and write each data sample on every rising edge of the clock
    -- en
	process(reset, clock)
    
        file en_fp          : text open write_mode is "C:\vivado_DSP\adaptiveFIR\data\en_int.txt";
        variable v_OLINE    : line;
        variable en_data    : integer;
    
    begin
        if(rising_edge(clock)) then
            en_data := to_integer(signed(enOut));
            write(v_OLINE, en_data);
            writeline(en_fp, v_OLINE);
        end if;
    end process;
	
	-- dhat
	process(reset, clock)
    
        file dhatn_fp          : text open write_mode is "C:\vivado_DSP\adaptiveFIR\data\dhat_int.txt";
        variable v_OLINE    : line;
        variable dhatn_data    : integer;
    
    begin
        if(rising_edge(clock)) then
            dhatn_data := to_integer(signed(dhatOut));
            write(v_OLINE, dhatn_data);
            writeline(dhatn_fp, v_OLINE);
        end if;
    end process;
	
	-- process to write the W coefficants on clock 1012
	-- clock counter
	process(reset,clock)
	begin
		if reset = '1' then
			clk_count <= (others => '0');
		else 
			if (rising_edge(clock)) then
			    clk_count <= clk_count + 1;
			end if;
		end if;
	end process;
	
	-- open file and write
	process (clk_count, clock)
		file w_fp          : text open write_mode is "C:\vivado_DSP\adaptiveFIR\data\w_int.txt";
        variable v_OLINE   : line;
        variable w_data    : integer;
        variable k         : integer := 0;
	begin
		if(rising_edge(clock)) then 
			if (clk_count = 1012) then
				while(k < 12) loop
					w_data := to_integer(signed(wn(k)));
					write(v_OLINE, w_data);
					writeline(w_fp, v_OLINE);
					k := k+1;
				end loop;
			end if;
		end if;
	end process;
	
end testbench;
