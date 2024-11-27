library ieee;
use ieee.std_logic_1164.all;
entity controlador is
    port (
    req : in std_logic_vector (3 downto 0);
    aut : out std_logic_vector (3 downto 0);
    reset : in std_logic;
    clock : in std_logic
    );
end entity controlador;
architecture comport_controlador of controlador is
    TYPE Tipo_estado IS (inicio, zero, um, dois, tres);
    signal atual: Tipo_estado;
    begin
        process(clock, reset)
        begin
            if reset = '1' then
                atual <= inicio;
            elsif (clock'event and clock = '1') then
                case atual is
                    when inicio =>
                        if(req(0)='1') then
                            atual <= zero;
                        elsif (req(1)='1') then
                            atual <= um;
                        elsif (req(2)='1') then
                            atual <= dois;
                        elsif (req(3)='1') then
                            atual <= tres;
                        end if;
                    when zero =>
                        if(req(0)='0') then 
                            atual<= inicio;
                        end if;
                    when um =>
                        if(req(1)='0') then 
                            atual<= inicio;
                        end if;
                    when dois =>
                        if(req(2)='0') then 
                            atual<= inicio;
                        end if;
                    when tres =>
                        if(req(3)='0') then 
                            atual<= inicio;
                        end if;
                end case;
            end if;
        end process;
        process(atual)
        begin
            case atual is
                when inicio =>
                    aut <="0000";
                when zero =>
                    aut(0)<='1';
                when um =>
                    aut(1)<='1';
                when dois =>
                    aut(2)<='1';
                when tres =>
                    aut(3)<='1';
                when others =>
                    aut <="0000";
            end case;
        end process;
end comport_controlador; 
            
            
