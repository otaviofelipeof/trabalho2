# Script auxiliar (nao faz parte da implementacao dos algoritmos em si).
# Gera arquivos de teste de melhor e pior caso para os 5 algoritmos de
# ordenacao, com tamanhos de 0 ate 500.000 elementos.
# Formato de cada arquivo: primeira linha = n, segunda linha = os n numeros.

import random  # biblioteca usada para embaralhar o vetor do melhor caso do quick sort

START_SIZE = 0        # menor tamanho de vetor a ser testado
END_SIZE = 500000      # maior tamanho de vetor a ser testado
STEP = 10000            # intervalo entre um tamanho e outro

# Gera a lista de tamanhos: 0, 10000, 20000, ..., 500000
# O "+1" no END_SIZE garante que 500000 seja incluido (range exclui o limite superior)
TAMANHOS = list(range(START_SIZE, END_SIZE + 1, STEP))

def vetor_crescente(n):
    # Gera um vetor ja ordenado em ordem crescente: 0, 1, 2, ..., n-1
    # range(n) ja gera exatamente essa sequencia, so precisamos converter para lista
    return list(range(n))

def vetor_decrescente(n):
    # Gera um vetor em ordem decrescente: n-1, n-2, ..., 1, 0
    # range(n-1, -1, -1) comeca em n-1, termina antes de -1, andando de -1 em -1
    return list(range(n - 1, -1, -1))

def vetor_aleatorio(n):
    # Gera um vetor com os mesmos numeros de 0 a n-1, mas em ordem embaralhada
    vetor = list(range(n))   # comeca com a sequencia ordenada
    random.shuffle(vetor)     # embaralha a lista "no lugar" (modifica a propria lista)
    return vetor

def escrever_arquivo(nome_arquivo, vetor):
    # Escreve um arquivo de teste no formato exigido pelo enunciado:
    # primeira linha = tamanho, segunda linha = elementos separados por espaco
    with open(nome_arquivo, "w") as f:                      # abre o arquivo para escrita
        f.write(f"{len(vetor)}\n")                            # primeira linha: tamanho do vetor
        f.write(" ".join(str(x) for x in vetor) + "\n")        # segunda linha: elementos

def gerar_para_insertion_selection_bubble(numero_exercicio):
    # Usado para os exercicios 1 (insertion), 2 (selection) e 3 (bubble):
    # melhor caso = vetor crescente, pior caso = vetor decrescente
    for n in TAMANHOS:                                                      # para cada tamanho da lista
        escrever_arquivo(f"m{numero_exercicio}v{n}.txt", vetor_crescente(n))    # melhor caso
        escrever_arquivo(f"p{numero_exercicio}v{n}.txt", vetor_decrescente(n))  # pior caso

def gerar_para_quicksort(numero_exercicio):
    # Exercicio 4 (quick sort): melhor caso = vetor aleatorio (particoes
    # balanceadas), pior caso = vetor crescente (pivo = ultimo elemento
    # gera particoes extremamente desbalanceadas nesse cenario)
    for n in TAMANHOS:
        escrever_arquivo(f"m{numero_exercicio}v{n}.txt", vetor_aleatorio(n))   # melhor caso
        escrever_arquivo(f"p{numero_exercicio}v{n}.txt", vetor_crescente(n))   # pior caso

def gerar_para_mergesort(numero_exercicio):
    # Exercicio 5 (merge sort): teoricamente nao tem melhor/pior caso real
    # (sempre Theta(n log n)), mas geramos crescente e decrescente mesmo
    # assim, para seguir o padrao do enunciado e confirmar empiricamente
    # que os tempos ficam parecidos nos dois casos
    for n in TAMANHOS:
        escrever_arquivo(f"m{numero_exercicio}v{n}.txt", vetor_crescente(n))
        escrever_arquivo(f"p{numero_exercicio}v{n}.txt", vetor_decrescente(n))

# Este bloco so executa se o arquivo for rodado diretamente (nao se for importado)
if __name__ == "__main__":
    gerar_para_insertion_selection_bubble(1)  # exercicio 1: insertion sort
    gerar_para_insertion_selection_bubble(2)  # exercicio 2: selection sort
    gerar_para_insertion_selection_bubble(3)  # exercicio 3: bubble sort
    gerar_para_quicksort(4)                    # exercicio 4: quick sort
    gerar_para_mergesort(5)                    # exercicio 5: merge sort
    print("Arquivos de teste gerados!")          # confirma que terminou tudo