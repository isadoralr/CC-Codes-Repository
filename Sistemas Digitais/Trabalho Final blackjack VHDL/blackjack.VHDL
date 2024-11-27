library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity blackjack is
    port (
        sw : in std_logic_vector (9 downto 0); -- cards
        HEX0 : out std_logic_vector (6 downto 0); -- card
		  HEX1 : out std_logic_vector (6 downto 0); -- NADA
        HEX2 : out std_logic_vector (6 downto 0); -- sumDec1
        HEX3 : out std_logic_vector (6 downto 0); -- sumDec2
        ledG : out std_logic_vector (7 downto 0); -- win(4)/tie(2)/lose(0)
        key : in std_logic_vector(3 downto 0) -- hit(3)/stay(2)/start(1)/clock(0)
    );
end entity blackjack;

architecture comport_blackjack of blackjack is
    TYPE estado IS (inicio, carta1Jogador, carta2Jogador, esperaJogador, hitJogador, carta1Dealer, carta2Dealer, hitDealer, win, tie, lose);
    signal atual : estado := inicio;
    signal sumJogador: integer range 31 downto 0 := 0;
    signal sumDealer: integer range 31 downto 0 := 0;
    signal ases11Jogador : boolean := false;
    signal ases11Dealer : boolean := false;

    -- Converte os números para o display de 7 segmentos
    function convert_to_hex(num : integer) return std_logic_vector is
        variable hex_value : std_logic_vector(6 downto 0);
    begin
        case num is
            when 0 => hex_value := "1000000"; -- 0
            when 1 => hex_value := "1111001"; -- 1
            when 2 => hex_value := "0100100"; -- 2
            when 3 => hex_value := "0110000"; -- 3
            when 4 => hex_value := "0011001"; -- 4
            when 5 => hex_value := "0010010"; -- 5
            when 6 => hex_value := "0000010"; -- 6
            when 7 => hex_value := "1111000"; -- 7
            when 8 => hex_value := "0000000"; -- 8
            when 9 => hex_value := "0010000"; -- 9
            when 10 => hex_value := "0001000"; -- A
            when 11 => hex_value := "0000011"; -- b
            when 12 => hex_value := "1000110"; -- C
            when 13 => hex_value := "0100001"; -- d
            when others => hex_value := "1111111"; -- desligado
        end case;
        return hex_value;
    end function convert_to_hex;
begin
    process(key(0), key(1))
        variable cartaB : std_logic_vector (9 downto 0);
        variable cartaD : integer range 13 downto 1;
        variable auxSum : integer range 31 downto 0;
    begin
        if key(1) = '0' then
            atual <= inicio;
        elsif falling_edge(key(0)) then
            cartaB := sw;
            cartaD := to_integer(unsigned(cartaB)); -- converte as cartas para decimal
            if cartaD > 10 then -- trata os valores >10
                cartaD := 10;
            end if;
            case atual is
                when inicio =>
                    sumJogador <= 0;
                    sumDealer <= 0;
                    ases11Jogador <= false;
                    ases11Dealer <= false;
                    atual <= carta1Jogador;
                when carta1Jogador =>  
                    if cartaD = 1 then -- carta é ás
                        ases11Jogador <= true;
                        sumJogador <= 11;
                    else
                        sumJogador <= cartaD;
                    end if;
                    atual <= carta1Dealer;
                when carta1Dealer =>
                    if cartaD = 1 then
                        ases11Dealer <= true;
                        sumDealer <= 11; -- se pegar um ás vai valer 11
                    else
                        sumDealer <= cartaD;
                    end if;
                    atual <= carta2Jogador;
                when carta2Jogador =>
                    if cartaD = 1 then
                        if (not ases11Jogador) then -- se não tiver ás valendo 11
                            ases11Jogador <= true;
                            sumJogador <= sumJogador + 11;
                        else
                            sumJogador <= sumJogador + 1;
                        end if;
                    else
                        sumJogador <= sumJogador + cartaD;
                    end if;
                    atual <= carta2Dealer;
                when carta2Dealer =>
                    if cartaD = 1 then
                        if (not ases11Dealer) then -- se não tiver ás valendo 11
                            ases11Dealer <= true;
                            sumDealer <= sumDealer + 11;
                        else
                            sumDealer <= sumDealer + 1;
                        end if;
                    else
                        sumDealer <= sumDealer + cartaD;
                    end if;
                    atual <= esperaJogador;
                when esperaJogador => -- espera o jogador escolher
                    if key(3) = '0' then
                        atual <= hitJogador;
                    elsif key(2) = '0' then
                        if sumDealer >= 17 then -- verifica se já pode finalizar a jogada do dealer
                            if sumDealer > sumJogador then
                                atual <= lose;
                            elsif sumDealer < sumJogador then
                                atual <= win;
                            else
                                atual <= tie;
                            end if;
                        else -- não atingiu 17
                            atual <= hitDealer; -- vai pegar + cartas
                        end if;
                    end if;
                when hitJogador =>
                    auxSum := sumJogador + cartaD; -- armazena a soma com a carta para fazer verificações
                    if auxSum > 21 then -- perdeu se não tiver ás valendo 11
                        if ases11Jogador and (auxSum - 10) <= 21 then -- se tiver ás valendo 11, verifica se adianta fazer ele voltar a valer 1
                            auxSum := auxSum - 10;
                            ases11Jogador <= false;
                            atual <= esperaJogador;
                        else
                            atual <= lose;
                        end if;
                    else -- se não tiver passado 21
                        if cartaD = 1 and not ases11Jogador and (auxSum + 10) <= 21 then  -- se tiver pegado um ás, verifica se pode fazer ele valer 11
                            ases11Jogador <= true;
                            auxSum := auxSum + 10;
                        end if;
                        atual <= esperaJogador; -- volta pro estado de espera
                    end if;
                    sumJogador <= auxSum; -- atualiza soma do jogador
                when hitDealer =>
                    auxSum := sumDealer + cartaD;
                    if auxSum > 21 then -- já verifica se extrapolou antes de tratar o valor do ás, pq se extrapolar com ele valendo 1, não adianta verificar se há ases valendo 11
                        if ases11Dealer and (auxSum - 10) <= 21 then -- se tiver ás valendo 11 e adiantar fazer ele valer 1
                            auxSum := auxSum - 10;
                            ases11Dealer <= false; -- sem ás valendo 11
                        else
                            atual <= win; -- Dealer perde e jogador ganha
                        end if;
                    else -- não extrapolou 21
                        if cartaD = 1 and (not ases11Dealer) and (auxSum + 10) <= 21 then -- se pegou ás, não tiver às valendo 11 e se ás valendo 11 não extrapolar a soma do dealer
                            ases11Dealer <= true; -- ás vai valer 11
                            auxSum := auxSum + 10; -- adiciona os 10 restantes
                        end if;
                        if auxSum >= 17 then -- finaliza jogada do dealer e vai pro resultado, se não for >17 continua pegando carta
                            if auxSum > sumJogador then
                                atual <= lose;
                            elsif auxSum < sumJogador then
                                atual <= win;
                            else
                                atual <= tie;
                            end if;
                        else
                            atual <= hitDealer; -- continua pegando cartas
                        end if;
                    end if;
                    sumDealer <= auxSum; -- atualiza a soma do dealer
                when win =>
                    atual <= inicio;
                when tie =>
                    atual <= inicio;
                when lose =>
                    atual <= inicio;
                when others =>
                    atual <= inicio;
            end case;
        end if;
    end process;

    process(atual, sumJogador, sumDealer)
    begin
        case atual is
            when inicio =>
                HEX0 <= "1111111";
					 HEX1 <= "1111111";
                HEX2 <= "1111111";
                HEX3 <= "1111111";
                ledG <= "00000000";
            when carta1Dealer | carta2Dealer | hitJogador => -- Para mostrar as cartas do jogador
                HEX0 <= convert_to_hex(to_integer(unsigned(sw(3 downto 0)))); -- Ajuste para pegar os 4 bits menos significativos de sw
                HEX3 <= "1111111";
                HEX2 <= "1111111";
            when esperaJogador => -- mostra a soma total do jogador
                HEX0 <= "1111111";
                HEX3 <= convert_to_hex(sumJogador / 10);
                HEX2 <= convert_to_hex(sumJogador mod 10);
            when win =>
                HEX0 <= "1111111";
                HEX3 <= convert_to_hex(sumDealer / 10); -- Mostra a pontuação total do dealer no final
                HEX2 <= convert_to_hex(sumDealer mod 10);
                ledG(4) <= '1';
            when tie =>
                HEX0 <= "1111111";
                HEX3 <= convert_to_hex(sumDealer / 10);
                HEX2 <= convert_to_hex(sumDealer mod 10);
                ledG(2) <= '1';
            when lose =>
                HEX0 <= "1111111";
                HEX3 <= convert_to_hex(sumDealer / 10);
                HEX2 <= convert_to_hex(sumDealer mod 10);
                ledG(0) <= '1';
            when others =>
                HEX0 <= "1111111";
                HEX2 <= "1111111";
                HEX3 <= "1111111";
                ledG <= "00000000";
        end case;
    end process;

end architecture comport_blackjack;
