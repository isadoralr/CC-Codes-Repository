###############################################################
# Aluna: Isadora Lais Ruschel
###############################################################
	
	.data
matriz_jogo: .space 216 #coluna x linha

columns: .word 7
rows: .word 6

current_player: .word 0 #0 é o jogador, 1 é o computador/jogador2
qtd_jogadores: .word 1 #Padrão

pontuacao_player1: .word 0
pontuacao_player2: .word 0 #muda se for contra o computador

txtPlayer: .asciz "X"
txtPlayer2: .asciz "O"
txtJ1Vitorias: .asciz "J1 venceu: "
txtJ2Vitorias: .asciz "J2 venceu: "
txtEmpty: .asciz "-"
txtEspaco: .asciz " "
txtMenu: .asciz "\n------------------------------------------------------\nEscolha uma opção:\n1) Configurações\n2) Jogar\n3) Sair\n------------------------------------------------------\n"
txtConfiguracao: .asciz "\n------------------------------------------------------\nEscolha uma opção:\n1) Mudar quantidade de jogadores\n2) Mudar tamanho do tabuleiro\n3) Zerar contadores\n4) Mostrar configurações atuais e contadores\n5) Voltar\n------------------------------------------------------\n"
txtQTD: .asciz "\n------------------------------------------------------\nEscolha uma opção:\n1) 1 Jogador\n2) 2 Jogadores\n3) Voltar\n------------------------------------------------------\n"
txtTamanho: .asciz "\n------------------------------------------------------\nEscolha uma opção:\n1) 7x6\n2) 9x6\n3) Voltar\n------------------------------------------------------\n"
txtDificuldade: .asciz "\n------------------------------------------------------\nEscolha uma opção:\n1) Fácil\n2) Médio\n------------------------------------------------------\n"
txtFinal: .asciz "\n------------------------------------------------------\nFinalizando...\n------------------------------------------------------\n"
txtOpcaoInvalida: .asciz "Opção inválida. Insira novamente.\n"
txtJogadaJogador: .asciz "Digite o número de uma coluna para jogar uma ficha:\n"
txtJogadaComputador: .asciz "Vez do computador.\n"
txtVoltandoMain: .asciz "Configuração salva. Voltando para o menu principal...\n"
txtContadores: .asciz "Contadores zerados. Voltando para o menu principal...\n"
txtConfiguracoes:  .asciz "Configuraçoes:\n"
txtQTDJogadores:  .asciz "Quantidade de jogadores: "
txtTamanhoTabuleiro: .asciz "Tamanho do tabuleiro: "
txtColunaInvalida: .asciz "Coluna inválida ou cheia. Tente novamente.\n"
txtEscolherJogador: .asciz "\n------------------------------------------------------\nEscolha quem vai começar:\n1) Jogador\n2) Computador\n------------------------------------------------------\n"
txtVencedor1: .asciz "\n------------------------------------------------------\nO vencedor é o Jogador 1. Reiniciando...\n------------------------------------------------------\n"
txtVencedor2: .asciz "\n------------------------------------------------------\nO vencedor é o Jogador 2. Reiniciando...\n------------------------------------------------------\n"
txtEmpate: .asciz "\n------------------------------------------------------\nTabuleiro cheio. Sem ganhadores. Reiniciando...\n------------------------------------------------------\n"
txtConfiguracaoInvalida: .asciz "Esta já é a configuração atual. Tente novamente.\n"
txtQuebraLinha: .asciz "\n"

#Ignorar o que escrevi na entrega intermediária pq peguei outro código que fiz como base e esqueci de apagar o comentário

	.text
main:
	jal inicializa_registradores
inicio:
	jal prepara_funcao
	jal inicia_tabuleiro
	
	li a7, 4 # Imprimir string
	la a0, txtMenu #Exibe o menu
	ecall
	li a7, 5 # Le um inteiro que vai ser a escolha do usuario, vai estar no a0
	ecall
	li t0, 1
	beq a0, t0, configuracao
	li t0, 2 # nao for 1, carrega o 2
	beq a0, t0, escolhe_jogador
	li t0, 3 # nao for 2, carrega o 3
	beq a0, t0, finaliza
	li a7, 4 # Imprimir string
	la a0, txtOpcaoInvalida #Opção inválida
	ecall
	j inicio

inicializa_registradores:
	la s0,matriz_jogo #coloca o endereco da matriz em s0 pra não perder na hora de imprimir e etc
	lw s1,columns # s1: colunas
	lw s2,qtd_jogadores #s2: qtd jogadores
	lw s3,current_player #s3: jogador atual
	la s4,txtEmpty
	lw s6,rows
	ret
prepara_funcao:#Coloca o endereco e a qtd de colunas nos registradores corretos para as funcoes
	mv a0,s0 
	mv a1,s1
	ret
inicia_tabuleiro:
	mul t3,s6,a1 #t3 = colunas * linha 
	slli t3,t3,2 #t3= linha*coluna*4
	add t3,t3,a0 #t3 tem o endereco do final da matriz
preenche_tabuleiro:
	bge a0,t3,retorna
	sw s4,0(a0) 
	addi a0,a0,4 
	j preenche_tabuleiro

configuracao:
	li a7, 4 # Imprimir string
	la a0, txtConfiguracao #Exibe o menu
	ecall
	li a7, 5 # Le um inteiro que vai ser a escolha do usuario, vai estar no a0
	ecall
	li t0, 1
	beq a0, t0, muda_qtd_jogador
	li t0, 2 # nao for 1, carrega o 2
	beq a0, t0, muda_tabuleiro
	li t0, 3 # nao for 2, carrega o 3
	beq a0, t0, zera_contadores
	li t0, 4 # nao for 3, carrega o 4
	beq a0, t0, exibe_configuracoes
	li t0, 5 # nao for 4, carrega o 5
	beq a0, t0, inicio
	li a7, 4 # Imprimir string
	la a0, txtOpcaoInvalida #Opção inválida
	ecall
	j configuracao
	
muda_qtd_jogador:
	li a7, 4 # Imprimir string
	la a0, txtQTD 
	ecall
	li a7, 5 # Le um inteiro que vai ser a escolha do usuario, vai estar no a0
	ecall
	li t0, 1
	beq a0, t0, um_jogador
	li t0, 2 # nao for 1, carrega o 2
	beq a0, t0, dois_jogadores
	li t0, 3 # nao for 2, carrega o 3
	beq a0, t0, configuracao
	li a7, 4 # Imprimir string
	la a0, txtOpcaoInvalida #Opção inválida
	ecall
	j muda_qtd_jogador
	
um_jogador:
	addi t2,zero,1 
	la t3,qtd_jogadores
	lw t0, 0(t3)
	beq t2,t0,configuracao_invalida
	sw t2, 0(t3)
	add s2,t2,zero #atualiza o s2
	j zera_contadores
	
dois_jogadores:
	addi t2,zero,2
	la t3,qtd_jogadores
	lw t0, 0(t3)
	beq t2,t0,configuracao_invalida
	sw t2, 0(t3)
	add s2,t2,zero #atualiza o s2
	j zera_contadores
	
muda_tabuleiro:
	li a7, 4 # Imprimir string
	la a0, txtTamanho
	ecall
	li a7, 5 # Le um inteiro que vai ser a escolha do usuario, vai estar no a0
	ecall
	li t0, 1
	beq a0, t0, sete_colunas
	li t0, 2 # nao for 1, carrega o 2
	beq a0, t0, nove_colunas
	li t0, 3 # nao for 2, carrega o 3
	beq a0, t0, configuracao
	li a7, 4 # Imprimir string
	la a0, txtOpcaoInvalida #Opção inválida
	ecall
	j muda_qtd_jogador

sete_colunas:
	addi t2,zero,7
	la t3,columns
	sw t2, 0(t3)
	add s1,t2,zero # atualiza s1
	li a7, 4 # Imprimir string
	la a0, txtVoltandoMain
	ecall
	j inicio

nove_colunas:
	addi t2,zero,9
	la t3,columns
	sw t2, 0(t3)
	add s1,t2,zero # s1: atualiza s1
	li a7, 4 # Imprimir string
	la a0, txtVoltandoMain
	ecall
	j inicio
	
zera_contadores:
	la t3,pontuacao_player1
	sw zero, 0(t3)
	la t3,pontuacao_player2
	sw zero, 0(t3)
	li a7, 4 # Imprimir string
	la a0, txtContadores
	ecall
	j inicio

exibe_configuracoes:
	li a7, 4 # Imprimir string
	la a0, txtJ1Vitorias
	ecall
	lw a0,pontuacao_player1
	li a7,1 #imprimir inteiro
	ecall
	li a7, 4 # Imprimir string
	la a0, txtQuebraLinha
	ecall
	la a0, txtJ2Vitorias
	ecall
	lw a0,pontuacao_player2
	li a7,1 #imprimir inteiro
	ecall
	li a7, 4 # Imprimir string
	la a0, txtQuebraLinha
	ecall
	la a0, txtQTDJogadores
	ecall
	lw a0, qtd_jogadores
	li a7,1 #imprimir inteiro
	ecall
	li a7, 4 # Imprimir string
	la a0, txtQuebraLinha
	ecall
	la a0, txtTamanhoTabuleiro
	ecall
	lw a0, rows
	li a7,1 #imprimir inteiro
	ecall
	li a7, 4 # Imprimir string
	la a0, txtPlayer
	ecall
	lw a0, columns
	li a7,1 #imprimir inteiro
	ecall
	j inicio
	
configuracao_invalida:
	li a7, 4 # Imprimir string
	la a0, txtConfiguracaoInvalida
	ecall
	j configuracao
	
imprime_tabuleiro:
	addi t2,zero,0 #contador pra percorrer as linhas
	mv t0,a0 #coloca o endereco do vetor em t0 pra não perder na hora de imprimir
	mul t3,s6,a1 #t3 = colunas * linhas 
	slli t3,t3,2 #t3= linha*coluna*4
	add t3,t3,t0 #t3 tem o final da matriz
	
	li a7,4
	la a0, txtJ1Vitorias
	ecall
	li a7,1 #imprimir inteiro
	lw a0,pontuacao_player1
	ecall
	li a7,4
	la a0, txtQuebraLinha
	ecall
	la a0, txtJ2Vitorias
	ecall
	li a7,1 #imprimir inteiro
	lw a0,pontuacao_player2
	ecall
	li a7,4
	la a0, txtQuebraLinha
	ecall
imprime_num_colunas:
	bge t2,a1, reseta_contador
	add a0,zero,t2
	li a7,1#Imprime inteiro
	ecall 
	li a7,4
	la a0, txtEspaco
	ecall
	addi t2,t2,1
	j imprime_num_colunas
reseta_contador:#reseta o contador e imprime quebra de linha
	addi t2,zero,0 
	la a0, txtQuebraLinha
	ecall
percorre_imprimindo:
	bge t2, a1, imprime_quebra # imprime quebra de linha e reseta o contador de linha se chegar na ultima coluna
	bge t0, t3, retorna# retorna se ja imprimiu todas as linhas 
	lw a0, 0(t0)
	li a7,4
	ecall
	la a0, txtEspaco
	ecall
	addi t0,t0,4
	addi t2, t2,1
	j percorre_imprimindo
imprime_quebra:
	la a0, txtQuebraLinha
	ecall
	addi t2,zero,0
	j percorre_imprimindo
	
finaliza:
	la a0, txtFinal #Exibe mensagem de finalizacao
	li a7, 4
	ecall
	li a7,10#Finaliza o programa
	ecall
retorna:
	ret


escolhe_jogador:
	li t0,2
	beq s2,t0,jogar #Se forem 2 jogadores, nao precisa pedir quem comeca
	li a7,4
	la a0, txtEscolherJogador
	ecall
	li a7, 5 # Le um inteiro que vai ser a escolha do usuario, vai estar no a0
	ecall
	li t0,1
	beq a0,t0,jogar
	li t0,2
	bne a0,t0,jogador_invalido
	mv a0,s3
	jal muda_jogador #se for o computador quem comeca, precisa mudar o jogador atual padrao
	j jogar
jogador_invalido:
	li a7,4
	la a0, txtOpcaoInvalida
	ecall
	j escolhe_jogador
jogar: #s0: endereco matriz | s1: colunas | s2: qtd jogadores | s3: jogador atual | s4: txtEmpty | s5: indice coluna | s6: linhas
	lw s3,current_player #atualiza sempre o s3: jogador atual
	jal prepara_funcao
	jal imprime_tabuleiro 

	beq s2,s3,computador_joga # se a quantidade de jogadores for 1 e o jogador atual for o computador
	li a7,4
	la a0, txtJogadaJogador
	ecall
	li a7, 5 # Le um inteiro que vai ser a escolha do usuario, vai estar no a0
	ecall
	mv s5,a0 # coluna selecionada copiada para o s5
verifica_coluna: #verifica se o indice em a0 é valido | s5: indice coluna 
	bge s5,s1,coluna_invalida
	bltz s5,coluna_invalida
	add a0,s0,zero #copia o endereco da matriz em a0 para a funcao
	add a1,s5,zero #copia a coluna selecionada em a1 para a funcao
	jal verifica_coluna_cheia #verifica se a coluna ja esta cheia | retorna a0: 1 se cheia e 0 caso contrário
	bnez a0,coluna_invalida #se o retorno for 1, coluna cheia 
	
fazer_jogada:#s0: endereco matriz | s1: colunas | s2: qtd jogadores | s3: jogador atual | s4: txtEmpty | s5: indice coluna | s6: linhas
	# Passagem de parametros
	add a0,s0,zero
	add a1,s5,zero
	add a2,s1,zero
	add a3,s6,zero
	
	jal encontra_linha # retorna -> a0: endereco posicao na matriz
	add a1,s3,zero #coloca o jogador atual no a1 para a funcao coloca_ficha
	jal coloca_ficha # sem retorno
	add a0,s0,zero
	add a1,s1,zero
	add a2,s3,zero
	jal verifica_vencedor
	bgtz a0,incrementa_contador 
	jal prepara_funcao
	jal verifica_empate
	bgtz a0,retorna_empate
	add a0,s3,zero # coloca o jogador atual no a0 para a funcao muda_jogador
	jal muda_jogador
	j jogar
	
coluna_invalida:
	li a7,4
	la a0, txtColunaInvalida
	ecall
	j jogar
	
verifica_coluna_cheia:#verifica se a coluna esta cheia(muda o valor de a0 para 1 se positivo) |a0: endereço matriz | a1: indice coluna || retorna -> a0=1 se estiver cheia e a0=0 caso contrário
	slli t5,a1,2 #multiplica o indice por 4
	add t5,t5,a0  #t5 tem o endereco da posicao correspondente
	lw t5,0(t5) #t5 tem o caracter da posicao correspondente
	addi a0,zero,0 #inicialmente é dada como não-cheia
	beq t5,s4,retorna #se não estiver cheia retorna, senao, coloca 1 no a0
	addi a0,zero,1
	ret

encontra_linha:#a0:endereco matriz | a1: indice coluna | a2: columns | a3: rows | s4: txtEmpty || retorna -> a0: endereco posicao na matriz
	addi a3,a3,-1
	mul t4,a3,a2
	add t4,t4,a1
	slli t4,t4,2 #(rows-1×columns+indice)* 4
	add t4,a0,t4 #endereco matriz + (rows-1×columns+a0)* 4
	lw t5,0(t4)
	bne t5,s4,encontra_linha #Se o espaço estiver livre retorna, senão continua procurando espaço
	add a0,t4,zero #coloca em a0 o endereco da posicao correspondente na matriz pra retornar
	ret
	
coloca_ficha:#a0: endereco posicao na matriz | a1: current_player || nao retorna nada, apenas coloca a ficha no lugar certo na matriz
	la t3,txtPlayer #pega o texto do jogador 1
	sw t3,0(a0) #coloca a ficha na posicao
	beqz a1,retorna #se for o jogador1 já retorna, senão, coloca o outro texto de ficha no t3
	la t3, txtPlayer2
	sw t3,0(a0) #coloca a ficha na posicao
	ret
	
muda_jogador:#a0: current_player || não retorna nada, apenas troca o numero do jogador atual
	la t3,current_player
	sw zero,0(t3) 
	bnez a0,retorna #se for 1, passa a ser vez do jogador1 e retorna, senão, passa a vez para o computador/jogador2
	addi t4,zero,1
	sw t4,0(t3)
	ret
	
computador_joga:
	li a7,4
	la a0, txtJogadaComputador
	ecall
computador_gera_coluna:
	li a7,42#gerar inteiro aleatorio entre 0 e colunas (indice correto)
	add a0,zero,zero
	mv a1,s1 #colunas para ter o numero maximo no range
	ecall
	add s5,a0,zero #copia o indice da coluna para s5
	add a0,s0,zero #copia o endereco da matriz em a0 para a funcao
	add a1,s5,zero #copia a coluna selecionada em a1 para a funcao
	jal verifica_coluna_cheia #verifica se a coluna ja esta cheia | retorna a0= 1 se cheia e a0=0 caso contrário
	bnez a0,computador_gera_coluna #se estiver cheia, gera o indice novamente
	j fazer_jogada

verifica_vencedor:#a0: posição de memória do rótulo matriz_jogo | a1: quantidade de colunas | a2: o jogador que realizou a ultima jogada | s6: qtd linhas
	mv t0, a0
	mul a3,s6,a1# numero da ultima posicao da matriz 
	
	addi t1,zero,1 #t1 contador iteracao
	li t5, 4 # t5 vai ter o 4 pra verificações
	la t2,txtPlayer #pega o texto do jogador 1
	beqz a2,verifica_linhas #se for o jogador1 já vai pra verificação, senão, coloca o outro texto de ficha no t2
	la t2, txtPlayer2
inicio_verifica_linhas:
	addi t4, zero,0 #t4 contador de fichas em sequencia
	
verifica_linhas:
	bgt t1,a3,prepara_verifica_colunas 
	lw t3,0(t0) # coloca no t3 o caractere atual
	rem t6,t1,a1 #coloca o resto da divisão do contador pelo num de colunas no t6, pra verificar se é a ultima coluna
	addi t0,t0,4
	addi t1,t1,1
	bne t3,t2,inicio_verifica_linhas #se não for o caractere do jogador, reseta as fichas seguidas
	addi t4,t4,1 #incrementa o numero de fichas seguidas
	beq t4,t5,retorna_vitoria #encontrou 4 fichas seguidas, ganhou
	beqz t6,inicio_verifica_linhas #Se terminou a linha, é preciso resetar a contagem de fichas em sequencia
	j verifica_linhas	

prepara_verifica_colunas: #Reseta contadores e endereço
	addi t1,zero,0 # t1: indice coluna
	addi t6,s6,-1# t6 tem linhas-1 
	mv t0, a0
	addi a7,zero,4 #a7 tem o num 4 pra verificacoes
inicio_verifica_colunas: #Usa a logica do encontra_linha, vai usando os calculos e incrementando as colunas, diminuindo as linha e verificando
	addi t4, zero,0 #t4 contador de fichas em sequencia
	j verifica_fim_coluna

verifica_colunas:
	mul t3,t6,a1 #linhas-1*colunas
	add t3,t3,t1 #linhas-1*colunas+indice coluna
	slli t3,t3,2 #(rows-1×columns+indice)* 4
	add t3,t0,t3 #endereco matriz + (rows-1×columns+indice)* 4
	lw t5,0(t3)
	addi t6,t6,-1 #diminui a linha, pra procurar na posicao acima
	bne t5,t2,inicio_verifica_colunas #se não for o caractere do jogador, reseta as fichas seguidas
	addi t4, t4,1
	bge t4,a7,retorna_vitoria
verifica_fim_coluna:
	bgez t6,verifica_colunas #se estiver na ultima linha de cima, recomeca o processo com a proxima coluna, senao, continua o laco
	addi t1,t1,1
	addi t6,s6,-1 #reseta pra comecar na ultima linha da proxima coluna
	bge t1,a1, prepara_verifica_diagonais_p #condicao de finalizacao do laco(t1 = num colunas)
	j inicio_verifica_colunas
	
prepara_verifica_diagonais_p:#(\)
	addi t1,a1,-1 # t1: indice coluna
	add a6,t1,zero #a6 vai ter a proxima coluna de inicio de verificacao
	addi t6,s6,-1# t6 tem linhas-1 
	mv t0, a0
	li a7,4 #a7 tem o num 4 pra verificacoes
	li a5,2 #a5 tem num 2 para interremper laco
inicio_verifica_diagonais_p: #Usa a logica do encontra_linha, vai usando os calculos e incrementando as colunas, diminuindo as linha e verificando
	addi t4, zero,0 #t4 contador de fichas em sequencia
	j verifica_fim_diagonal_p
verifica_diagonais_p:
	mul t3,t6,a1 #linhas-1*colunas
	add t3,t3,t1 #linhas-1*colunas+indice coluna
	slli t3,t3,2 #(rows-1×columns+indice)* 4
	add t3,t0,t3 #endereco matriz + (rows-1×columns+indice)* 4
	lw t5,0(t3)
	addi t6,t6,-1 #diminui a linha, pra procurar na posicao acima
	addi t1,t1,-1 #diminui a coluna tambem para procurar na diagonal superior 
	bne t5,t2,inicio_verifica_diagonais_p #se não for o caractere do jogador, reseta as fichas seguidas
	addi t4, t4,1
	bge t4,a7,retorna_vitoria
verifica_fim_diagonal_p:
	bltz t1,proxima_diagonal_p
	bgez t6,verifica_diagonais_p #se estiver na ultima linha de cima, recomeca o processo com a proxima coluna, senao, continua o laco (t6 vai estar com -1)
proxima_diagonal_p:
	addi a6,a6,-1
	ble a6,a5,prepara_verifica_diagonais_p_direita #condicao de finalizacao (coluna = 2, não tem como ter 4 fichas na diagonal)
	add t1,a6,zero
	addi t6,s6,-1 #reseta pra comecar na ultima linha da proxima coluna
	j inicio_verifica_diagonais_p
	
prepara_verifica_diagonais_p_direita:#a7 tem o num 4 pra verificacoes | a5 tem num 2 para interremper laco | t0 tem endereco inicial da matriz |t2 tem o texto da ficha
	addi t1,a1,-1 # t1: indice coluna
	addi t6,s6,-2# t6 tem linhas-2
	add a6,t6,zero #a6 vai ter a proxima linha de inicio de verificacao
inicio_verifica_diagonais_p_direita: #Usa a logica do encontra_linha, vai usando os calculos e incrementando as colunas, diminuindo as linha e verificando
	addi t4, zero,0 #t4 contador de fichas em sequencia
	j verifica_fim_diagonal_p_direita
verifica_diagonais_p_direita:
	mul t3,t6,a1 #linhas-1*colunas
	add t3,t3,t1 #linhas-1*colunas+indice coluna
	slli t3,t3,2 #(rows-1×columns+indice)* 4
	add t3,t0,t3 #endereco matriz + (rows-1×columns+indice)* 4
	lw t5,0(t3)
	addi t6,t6,-1 #diminui a linha, pra procurar na posicao acima
	addi t1,t1,-1 #diminui a coluna tambem para procurar na diagonal superior 
	bne t5,t2,inicio_verifica_diagonais_p_direita #se não for o caractere do jogador, reseta as fichas seguidas
	addi t4, t4,1
	bge t4,a7,retorna_vitoria
verifica_fim_diagonal_p_direita:
	bgez t6,verifica_diagonais_p_direita #se estiver na ultima linha de cima, recomeca o processo com a proxima coluna, senao, continua o laco (t6 vai estar com -1)
proxima_diagonal_p_direita:
	addi a6,a6,-1 #calcula a linha proxima linha ^
	ble a6,a5, prepara_verifica_diagonais_s #condicao de finalizacao (linha = 2, não tem como ter 4 fichas na diagonal)
	add t6,a6,zero
	addi t1,a1,-1 #reseta pra comecar na proxima linha da coluna
	j inicio_verifica_diagonais_p_direita

prepara_verifica_diagonais_s:#(/)
	add t1,zero,zero # t1: indice coluna
	add a6,t1,zero #a6 vai ter a proxima coluna de inicio de verificacao
	addi t6,s6,-1# t6 tem linhas-1 
	mv t0, a0
	li a7,4 #a7 tem o num 4 pra verificacoes
	addi a5,a1,-3 #a5 tem num colunas-3 para interremper laco
inicio_verifica_diagonais_s: #Usa a logica do encontra_linha, vai usando os calculos e incrementando as colunas, diminuindo as linha e verificando
	addi t4, zero,0 #t4 contador de fichas em sequencia
	j verifica_fim_diagonal_s
verifica_diagonais_s:
	mul t3,t6,a1 #linhas-1*colunas
	add t3,t3,t1 #linhas-1*colunas+indice coluna
	slli t3,t3,2 #(rows-1×columns+indice)* 4
	add t3,t0,t3 #endereco matriz + (rows-1×columns+indice)* 4
	lw t5,0(t3)
	addi t6,t6,-1 #diminui a linha, pra procurar na posicao acima
	addi t1,t1,1 #aumenta a coluna tambem para procurar na diagonal superior 
	bne t5,t2,inicio_verifica_diagonais_s #se não for o caractere do jogador, reseta as fichas seguidas
	addi t4, t4,1
	bge t4,a7,retorna_vitoria
verifica_fim_diagonal_s:
	bge t1,a1,proxima_diagonal_s #se estiver na ultima coluna
	bgez t6,verifica_diagonais_s #se estiver na ultima linha de cima, recomeca o processo com a proxima coluna, senao, continua o laco (t6 vai estar com -1)
proxima_diagonal_s:
	addi a6,a6,1
	bge a6,a5,prepara_verifica_diagonais_s_direita #condicao de finalizacao (não tem como ter 4 fichas na diagonal)
	add t1,a6,zero #t1 vai para a proxima coluna
	addi t6,s6,-1 #reseta pra comecar na ultima linha da proxima coluna
	j inicio_verifica_diagonais_s
	
prepara_verifica_diagonais_s_direita:#a7 tem o num 4 pra verificacoes | a5 tem num 2 para interremper laco | t0 tem endereco inicial da matriz |t2 tem o texto da ficha
	add t1,zero,zero # t1: indice coluna
	addi t6,s6,-2# t6 tem linhas-2
	add a6,t6,zero #a6 vai ter a proxima linha de inicio de verificacao
	addi a5,zero,2 #a5 tem 2 para interremper laco
inicio_verifica_diagonais_s_direita: #Usa a logica do encontra_linha, vai usando os calculos e incrementando as colunas, diminuindo as linha e verificando
	addi t4, zero,0 #t4 contador de fichas em sequencia
	j verifica_fim_diagonal_s_direita
verifica_diagonais_s_direita:
	mul t3,t6,a1 #linhas-1*colunas
	add t3,t3,t1 #linhas-1*colunas+indice coluna
	slli t3,t3,2 #(rows-1×columns+indice)* 4
	add t3,t0,t3 #endereco matriz + (rows-1×columns+indice)* 4
	lw t5,0(t3)
	addi t6,t6,-1 #diminui a linha, pra procurar na posicao acima
	addi t1,t1,1 #aumenta a coluna tambem para procurar na diagonal superior 
	bne t5,t2,inicio_verifica_diagonais_s_direita #se não for o caractere do jogador, reseta as fichas seguidas
	addi t4, t4,1
	bge t4,a7,retorna_vitoria
verifica_fim_diagonal_s_direita:
	bgez t6,verifica_diagonais_s_direita #se estiver na ultima linha de cima, recomeca o processo com a proxima coluna, senao, continua o laco (t6 vai estar com -1)
proxima_diagonal_s_direita:
	addi a6,a6,-1 #calcula a linha proxima linha ^
	bge a6,a5, retorna_indefinido#condicao de finalizacao (linha inicio = 2, não tem como ter 4 fichas na diagonal)
	add t6,a6,zero
	add t1,zero,zero #reseta pra comecar na proxima linha da coluna
	j inicio_verifica_diagonais_s_direita

retorna_vitoria:
    	li a0,1
    	mv a1,a2#Coloca o jogador atual como vencedor no a1 para retornar
    	ret
retorna_indefinido:
	li a0,-1
    	ret
incrementa_contador:
	jal prepara_funcao
	jal imprime_tabuleiro
	bgtz s3, incrementa_contador_jogador2
	li a7,4
	la a0, txtVencedor1
	ecall
	la t0,pontuacao_player1
	lw t1,0(t0)
	addi t1,t1,1
	sw t1,0(t0)
	#Coloca sempre o jogador 1(0) como primeiro como padrao na memoria, ja que vai voltar pra main
	la t1,current_player
	sw zero,0(t1)
	j main
incrementa_contador_jogador2:
	li a7,4
	la a0, txtVencedor2
	ecall
	la t0,pontuacao_player2
	lw t1,0(t0)
	addi t1,t1,1
	sw t1,0(t0)
	#Coloca sempre o jogador 1(0) como primeiro como padrao na memoria, ja que vai voltar pra main
	la t1,current_player
	sw zero,0(t1)
	j main
	
verifica_empate:#a0: endereco matriz | a1: quantidade de colunas
	mv t0,a0
	li t1,0
	la t2,txtEmpty
	li a0,1 #a0 começa valendo 1 (empate), se encontrar espaço vazio, muda pra 0
verifica_empate_laco: #a0 = 0 se encontrar espaco vazio e retorna
	bge t1,a1,retorna
	lw t3,0(t0)
	addi t1,t1,1
	addi t0,t0,4
	bne t3,t2,verifica_empate_laco #encontrou espaco vazio, nao esta cheia, portanto, nao ha empate ainda
	addi a0,zero,0 
	ret
retorna_empate:
	jal prepara_funcao
	jal imprime_tabuleiro
	li a7,4
	la a0, txtEmpate
	ecall
	#Coloca sempre o jogador 1(0) como primeiro como padrao na memoria, ja que vai voltar pra main
	la t1,current_player
	sw zero,0(t1)
	j main
	




