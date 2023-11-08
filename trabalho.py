class Aluno:
    def __init__(self, nome, cpf, peso, altura, idAluno):
        self.nome = nome
        self.cpf = cpf
        self.peso = peso
        self.altura = altura
        self.status = False  # Inicialmente, o aluno não tem treino
        self.idAluno = idAluno

    def alunoString(self): # Exibe as informações do aluno
        return "Nome: {}\nCPF: {}\nPeso: {:.2f}kg\nAltura: {:.2f}cm\nStatus: {}\nID: {}\n------------------------------------------------------".format(
            self.nome, self.cpf, self.peso, self.altura, self.status, self.idAluno
        )


class Exercicio:
    def __init__(self, nomeExercicio, numRepeticoes, pesoExercicio):
        self.nomeExercicio = nomeExercicio
        self.numRepeticoes = numRepeticoes
        self.pesoExercicio = pesoExercicio

    def exercicioString(self): # Exibe as informações do exercício
        return "Nome do exercício: {}\nNúmero de repetições: {}\nPeso do exercício: {}kg\n------------------------------------------------------".format(
            self.nomeExercicio, self.numRepeticoes, self.pesoExercicio
        )


# Variáveis globais:
cadAlunos = []  # Lista de alunos
treinoAlunos = []  # Matriz de treinos




def cadastroAluno():
    nome = input("Insira o nome do aluno.\n")
    if nome.isspace():
        print("Nome inválido. Reiniciando cadastro de aluno...")
        print("------------------------------------------------------")
    cpf = input("Insira o CPF do aluno.\n")
    if validaCPF(cpf):
        cpf = formataCPF(cpf) # Formata o CPF, caso já não esteja formatado
        peso = float(input("Insira o peso do aluno (em kg).\n"))
        if peso !=0:
            altura = float(input("Insira a altura do aluno (em cm).\n"))
            if altura !=0:
                cadAlunos.append(Aluno(nome, cpf, peso, altura, len(cadAlunos) + 1))  # Cadastra o aluno
                treinoAlunos.append([])  # Insere um treino vazio
                print("------------------------------------------------------")
                print("Aluno cadastrado com sucesso.")
            else:
                print("Altura inválida. Reiniciando cadastro de aluno...")
                print("------------------------------------------------------")
                cadastroAluno()
        else:
            print("Peso inválido. Reiniciando cadastro de aluno...")
            print("------------------------------------------------------")
            cadastroAluno()
    else:
        print("-------------------------------------------------------------------------------------------------")
        print("CPF inválido ou já cadastrado. Por favor, insira um CPF válido. Reiniciando cadastro...")
        print("-------------------------------------------------------------------------------------------------")
        cadastroAluno()
    
    
def validaCPF(cpf):
    for aluno in cadAlunos:
        if aluno.cpf == cpf or aluno.cpf == formataCPF(cpf):
            print("Já existe um aluno cadastrado com esse CPF.")
            return False
    
    cpf = cpf.replace(".", "").replace("-", "")  # Remove pontos e traços do CPF
    

    # Verifica se o CPF possui 11 dígitos
    if len(cpf) != 11:
        return False

    # Verifica se todos os dígitos são iguais, o que torna o CPF inválido
    if cpf == cpf[0] * 11:
        return False

    # Calcula o primeiro dígito verificador
    soma = 0
    for i in range(9):
        soma += int(cpf[i]) * (10 - i)
    resto = soma % 11
    digito_verificador1 = 0 if resto < 2 else 11 - resto

    # Verifica se o primeiro dígito verificador está correto
    if int(cpf[9]) != digito_verificador1:
        return False

    # Calcula o segundo dígito verificador
    soma = 0
    for i in range(10):
        soma += int(cpf[i]) * (11 - i)
    resto = soma % 11
    digito_verificador2 = 0 if resto < 2 else 11 - resto

    # Verifica se o segundo dígito verificador está correto
    if int(cpf[10]) != digito_verificador2:
        return False

    return True


def formataCPF(cpf):
    cpf = cpf.replace(".", "").replace("-", "")  # Remove pontos e traços do CPF

    # Formata o CPF no padrão xxx.xxx.xxx-xx
    return f"{cpf[:3]}.{cpf[3:6]}.{cpf[6:9]}-{cpf[9:]}"

def alteraExercicio(idAluno):
    listaExercicios(idAluno)
    ind = int(input("Qual o índice do exercício que deseja alterar?\n"))
    print("------------------------------------------------------")
    if ind < 1 or ind > len(treinoAlunos[idAluno - 1]):
        
        print("Índice inválido, por favor tente novamente.")
        alteraExercicio(idAluno)
    else:  
        print("Digite o número da opção desejada:")
        print("1 - Alterar nome do exercício")
        print("2 - Alterar número de repetições do exercício")
        print("3 - Alterar peso do exercício")
        print("0 - Voltar")
        op = int(input())
        print("------------------------------------------------------")
        if op == 1:
            nome = input("Insira o novo nome do exercício.\n")
            if nome.isspace():
                print("Nome inválido. Reiniciando alterações...")
                print("------------------------------------------------------")
                alteraExercicio(idAluno)
            else:
                treinoAlunos[idAluno - 1][ind - 1].nomeExercicio = nome
                print("Nome do exercício alterado com sucesso.")
                listaExercicios(idAluno)
        elif op == 2:
            repeticoes = int(input("Insira o novo número de repetições do exercício.\n"))
            if repeticoes >0:
                treinoAlunos[idAluno - 1][ind - 1].numRepeticoes = repeticoes
                print("Número de repetições do exercício alterado com sucesso.")
                listaExercicios(idAluno)
            else:
                print("Número de repetições inválido. Reiniciando alterações...")
                print("--------------------------------------------------------")
                alteraExercicio(idAluno)
        elif op == 3:
            peso = float(input("Insira o novo peso do exercício (em kg).\n"))
            if peso>0:
                treinoAlunos[idAluno - 1][ind - 1].pesoExercicio = peso
                print("Peso do exercício alterado com sucesso.")
                listaExercicios(idAluno)
            else:
                print("Peso do exercício inválido. Reiniciando alterações...")
                print("--------------------------------------------------------")
                alteraExercicio(idAluno)
        elif op == 0:
            print("Voltando...")
        else:
            print("Opção inválida. Reiniciando...")
            print("--------------------------------------------------------")
            alteraExercicio(idAluno)

def listaExercicios(idAluno):
    for exercicio in treinoAlunos[idAluno - 1]:
        print("------------------------------------------------------")
        print("|",treinoAlunos[idAluno - 1].index(exercicio) + 1,"|") # Mostra o índice de cada exercício 
        print(exercicio.exercicioString())

def incluiExercicio(idAluno):
    nome = input("Insira o nome do exercício.\n")
    if nome.isspace():
        print("Nome inválido. Reiniciando cadastro de exercício...")
    else:
        rep = int(input("Insira o número de repetições.\n"))
        if rep>0:
            peso = float(input("Insira o peso do exercício.\n"))
            if peso>0:
                treinoAlunos[idAluno - 1].append(Exercicio(nome, rep, peso))  # Adiciona um novo exercício no treino do aluno
                cadAlunos[idAluno - 1].status = True 
                print("------------------------------------------------------")
                print("Exercício registrado com sucesso.")
                
            else:
                print("Peso inválido. Reiniciando cadastro de exercício...")
                print("------------------------------------------------------")
                incluiExercicio(idAluno)
        else:
            print("Número inválido de repetições. Reiniciando cadastro de exercício...")
            print("------------------------------------------------------")
            incluiExercicio(idAluno)

def listaAlunos(status=None):
    haAluno = False #Para informar caso não haja alunos com determinado status
    if status == False: 
        for aluno in cadAlunos:
            if aluno.status == False: #Verifica se há alunos inativos
                print("------------------- LISTA DE ALUNOS -------------------")
                for aluno in cadAlunos:
                    if aluno.status == False:
                        print(aluno.alunoString())
                haAluno = True
                break
        if haAluno == False:
            print("------------------------------------------------------")
            print("Não há alunos com status False. Voltando...")
            

    elif status == True:
        for aluno in cadAlunos:
            if aluno.status == True: #Verifica se há alunos ativos
                print("------------------- LISTA DE ALUNOS -------------------")
                for aluno in cadAlunos:
                    if aluno.status == True:
                        print(aluno.alunoString())
                haAluno = True
                break
        if haAluno == False:
            print("------------------------------------------------------")
            print("Não há alunos com status True. Voltando...")
            
    
    else:
        print("------------------- LISTA DE ALUNOS -------------------")
        for aluno in cadAlunos:
            print(aluno.alunoString())


def consultaAluno(nome):
    print("------------------------------------------------------")
    achou = False
    for aluno in cadAlunos:
        if aluno.nome == nome:
            print(aluno.alunoString())
            if len(treinoAlunos[aluno.idAluno - 1]) == 0:
                print("Sem treinos.")
            else:
                print("--------------------- Exercícios ---------------------")
                for exercicio in treinoAlunos[aluno.idAluno - 1]:
                    print(exercicio.exercicioString())
            achou = True
            break
    if not achou:
        print("Aluno não encontrado.")

def alteraAluno(idAluno):
    print("------------------------------------------------------")
    print("Digite o número da opção desejada:")
    print("1 - Alterar nome do aluno")
    print("2 - Alterar CPF do aluno")
    print("3 - Alterar peso do aluno")
    print("4 - Alterar altura do aluno")
    print("0 - Voltar")
    print("------------------------------------------------------")
    op = int(input())
    print("------------------------------------------------------")
    if op == 1:
        cadAlunos[idAluno - 1].nome = input("Insira o novo nome do aluno.\n")
        print("------------------------------------------------------")
        print("Nome do aluno alterado com sucesso.")
        consultaAluno(cadAlunos[idAluno - 1].nome)
    elif op == 2:
        cpf = input("Insira o novo número de CPF do aluno.\n")
        if validaCPF(cpf):
            cpf = formataCPF(cpf)
            cadAlunos[idAluno - 1].cpf = cpf
            print("------------------------------------------------------")
            print("Número de CPF do aluno alterado com sucesso.")
            consultaAluno(cadAlunos[idAluno - 1].nome)
        else:
            print("-------------------------------------------------------------------------------------------")
            print("CPF inválido ou já cadastrado. Por favor, insira um CPF válido. Reiniciando alterações...")
            alteraAluno(idAluno)
            
    elif op == 3:
        peso = float(input("Insira o novo peso do aluno.\n"))
        if peso >0:
            cadAlunos[idAluno - 1].peso = peso
            print("Peso do aluno alterado com sucesso.")
            consultaAluno(cadAlunos[idAluno - 1].nome)
        else:
            print("------------------------------------------------------")
            print("Peso inválido. Reiniciando alterações...")
            alteraAluno(idAluno)
    elif op == 4:
        altura = float(input("Insira a nova altura do aluno.\n"))
        if altura >0:
            cadAlunos[idAluno - 1].altura = altura
            print("Altura do aluno alterada com sucesso.")
            consultaAluno(cadAlunos[idAluno - 1].nome)
    elif op == 0:
        print("Voltando...")
    else:
        print("Opção inválida.")
        alteraAluno(idAluno)

def excluiAluno():
    listaAlunos()
    idAluno = int(input("Insira o ID do aluno para excluir.\n"))
    if idAluno > 0 and idAluno <= len(cadAlunos):
        print("Confirma a exclusão do aluno?")
        print("1 - Sim")
        print("2 - Não")
        op = int(input(""))
        if op == 1:
            del cadAlunos[idAluno - 1]
            del treinoAlunos[idAluno - 1]
           
            # Atualiza os IDs dos alunos subsequentes
            for i in range(idAluno - 1, len(cadAlunos)):
                cadAlunos[i].idAluno -= 1

            print("Aluno excluído e demais ID'S atualizados.")
        elif op == 0:
            print("Retornando...")
        else:
            print("Opção inválida. Tente novamente.")
            excluiAluno()
        
    else:
        print("ID inválido. Tente novamente.")
        excluiAluno()

def relatorioAlunos():
    print("---------------- RELATÓRIO DE ALUNOS -----------------")
    print("Digite o número da opção desejada:")
    print("1 - Exibir todos os alunos")
    print("2 - Exibir alunos ativos")
    print("3 - Exibir alunos inativos")
    print("0 - Voltar")
    print("------------------------------------------------------")
    op = int(input())
    if op == 1:
        listaAlunos()
        relatorioAlunos()
    elif op == 2:
        listaAlunos(True)
        relatorioAlunos()
    elif op == 3:
        listaAlunos(False)
        relatorioAlunos()
    elif op == 0:
        print("Voltando...")
    
def gerenciaTreino(idAluno):
    print("--------------- GERENCIAR TREINO", idAluno, "-------------------")
    print("Digite o número da opção desejada:")
    print("1 - Incluir um novo exercício no treino deste aluno")
    print("2 - Alterar um exercício existente no treino")
    print("3 - Excluir um exercício específico do treino deste aluno")
    print("4 - Excluir todos os exercícios do treino deste aluno")
    print("0 - Voltar")
    print("------------------------------------------------------")
    op = int(input())
    
    if op == 1:
        incluiExercicio(idAluno)
        gerenciaTreino(idAluno)
    elif op == 2:
        if cadAlunos[idAluno - 1].status:
            alteraExercicio(idAluno)
        else:
            print("Não há exercícios no treino deste aluno.")
        gerenciaTreino(idAluno)

    elif op == 3:
        if cadAlunos[idAluno - 1].status:
            listaExercicios(idAluno)
            op2 = int(input("Qual o índice do exercício que deseja excluir?\n"))
            if op2 < 1 or op2 > len(treinoAlunos[idAluno - 1]):
                print("------------------------------------------------------")
                print("Índice inválido, por favor tente novamente.")
                
            else:
                del treinoAlunos[idAluno - 1][op2 - 1]
                print("Exercício nº", op2, "excluído.")

                if len(treinoAlunos[idAluno - 1]) == 0:
                    cadAlunos[idAluno - 1].status = False
        else:
            print("Não há exercícios no treino deste aluno.")
        gerenciaTreino(idAluno)

    elif op == 4:
        if cadAlunos[idAluno - 1].status:
            treinoAlunos[idAluno - 1] = []
            cadAlunos[idAluno - 1].status = False
            print("Exercícios excluídos.")
        else:
            print("Não há exercícios no treino deste aluno.")
        gerenciaTreino(idAluno)

    elif op == 0:
        print("------------------------------------------------------")
        print("Voltando...")
        
    else:
        print("------------------------------------------------------")
        print("Opção inválida.")
        gerenciaTreino(idAluno)


def menuPrincipal():
    print("----------------------- INÍCIO -----------------------")
    print("Digite o número da opção desejada:")
    print("1 - Cadastrar um aluno")
    print("2 - Gerenciar treino de um aluno")
    print("3 - Consultar um aluno")
    print("4 - Atualizar cadastro de um aluno")
    print("5 - Excluir aluno")
    print("6 - Relatório de alunos")
    print("0 - Sair do sistema")
    print("------------------------------------------------------")
    op = int(input())
    
    if op == 1:
        cadastroAluno()
        menuPrincipal()

    elif op == 2:
        if len(cadAlunos) != 0:
            print("------------------------------------------------------")
            idAluno = int(input("Insira o ID do aluno para gerenciar o treino.\n------------------------------------------------------\n"))
            
            if idAluno > 0 and idAluno <= len(cadAlunos):
                gerenciaTreino(idAluno)
            else:
                print("ID inválido.")
                print("------------------------------------------------------")
        else:
            print("------------------------------------------------------")
            print("Não há alunos para gerenciar.")
        menuPrincipal()

    elif op == 3:
        if len(cadAlunos) != 0:
            print("------------------------------------------------------")
            nome = input("Insira o nome do aluno que deseja consultar.\n")
            if nome.isspace(): # Verifica se o nome não é uma string vazia antes
                print("Nome inválido. Voltando...")
            else:
                consultaAluno(nome)
        else:
            print("Não há alunos para consultar.")
        menuPrincipal()

    elif op == 4:
        if len(cadAlunos) != 0:
            listaAlunos()
            idAluno = int(input("Insira o ID do aluno para atualizar o cadastro.\n"))
            if idAluno > 0 and idAluno <= len(cadAlunos): 
                alteraAluno(idAluno)
            else:
                print("ID inválido.")
                print("------------------------------------------------------")
                
        else:
            print("Não há alunos para atualizar.")
        menuPrincipal()

        

    elif op == 5:
        if len(cadAlunos) != 0:
            excluiAluno()
        else:
            print("Não há alunos para excluir.")
        menuPrincipal()
    elif op == 6:
        if len(cadAlunos) != 0:
            relatorioAlunos()
        else:
            print("Não há alunos cadastrados para exibir.")
        menuPrincipal()

    elif op == 0:
        print("Saindo...")
    else:
        print("Opção inválida. Tente novamente.")
        menuPrincipal()


# Execução do programa:
menuPrincipal()
