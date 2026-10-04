# Script auxiliar (nao faz parte da implementacao dos algoritmos em si).
# Le o resultados.csv e gera um grafico PNG por exercicio, alem de um
# grafico comparando o pior caso de todos os 5 algoritmos juntos.

import csv                            # para ler o arquivo CSV com os resultados
import matplotlib.pyplot as plt       # biblioteca usada para desenhar os graficos
from collections import defaultdict   # dicionario que ja vem com lista vazia por padrao

def carregar_dados():
    # Le o resultados.csv e organiza os dados num dicionario.
    # Chave: (numero_do_exercicio, caso) -- Valor: lista de pares (tamanho, tempo)
    dados = defaultdict(list)  # cria o dicionario vazio (com listas vazias por padrao)

    with open("resultados.csv") as f:            # abre o arquivo CSV para leitura
        reader = csv.DictReader(f)                 # le cada linha como um dicionario
        for linha in reader:                        # percorre cada linha do arquivo
            chave = (int(linha["exercicio"]), linha["caso"])  # monta a chave (numero, "m" ou "p")
            # adiciona o par (tamanho, tempo) na lista correspondente a essa chave
            dados[chave].append((int(linha["n"]), float(linha["tempo_ns"])))

    return dados  # devolve o dicionario completo

def plotar_exercicio(dados, num_exercicio, nome_algoritmo):
    # Cria e salva um grafico PNG para UM exercicio, com melhor caso e pior caso juntos
    plt.figure()  # cria uma figura nova (evita misturar com outros graficos)

    # Repete duas vezes: uma para o melhor caso, outra para o pior caso
    for caso, rotulo in [("m", "Melhor caso"), ("p", "Pior caso")]:
        # Pega os pontos (tamanho, tempo) desse exercicio e desse caso, ja ordenados por tamanho
        pontos = sorted(dados[(num_exercicio, caso)])

        if not pontos:
            # Se a lista estiver vazia, nao ha nada para desenhar: pula
            continue

        xs = [p[0] for p in pontos]  # extrai so os tamanhos de vetor (eixo X)
        ys = [p[1] for p in pontos]  # extrai so os tempos medidos (eixo Y)

        # Desenha a linha no grafico, com um marcador (bolinha) em cada ponto medido
        plt.plot(xs, ys, label=rotulo, marker="o", markersize=3)

    plt.title(f"Desempenho - {nome_algoritmo}")   # titulo do grafico
    plt.xlabel("Tamanho do vetor (n)")               # nome do eixo X
    plt.ylabel("Tempo (nanossegundos)")               # nome do eixo Y
    plt.legend()                                        # mostra a legenda (melhor/pior caso)
    plt.grid(True)                                       # adiciona grade para facilitar leitura

    plt.savefig(f"grafico_ex{num_exercicio}.png")  # salva o grafico como arquivo PNG
    plt.close()                                        # fecha a figura (libera memoria)

def plotar_comparacao_geral(dados, nomes):
    # Cria e salva o grafico comparativo do Exercicio 6 (comparacao),
    # juntando o PIOR CASO de todos os 5 algoritmos num unico grafico
    plt.figure(figsize=(10, 6))  # cria uma figura maior, ja que tem mais linhas

    # Percorre cada exercicio e seu nome (nomes.items() devolve pares numero-nome)
    for num_exercicio, nome_algoritmo in nomes.items():
        # Pega so os pontos do PIOR caso ("p") desse exercicio, ja ordenados
        pontos = sorted(dados[(num_exercicio, "p")])

        if not pontos:
            # Se nao houver pontos, pula esse exercicio
            continue

        xs = [p[0] for p in pontos]  # tamanhos de vetor
        ys = [p[1] for p in pontos]  # tempos medidos

        # Desenha a linha desse algoritmo no grafico, usando o nome dele na legenda
        plt.plot(xs, ys, label=nome_algoritmo, marker="o", markersize=2)

    plt.title("Comparacao geral - Pior caso de todos os algoritmos")  # titulo
    plt.xlabel("Tamanho do vetor (n)")   # eixo X
    plt.ylabel("Tempo (nanossegundos)")   # eixo Y
    plt.legend(fontsize=8)                  # legenda com letra um pouco menor (sao 5 linhas)
    plt.grid(True)                           # grade de fundo

    plt.savefig("grafico_comparacao_geral.png")  # salva o grafico comparativo
    plt.close()                                     # fecha a figura

# So executa o bloco abaixo se este arquivo for rodado diretamente
if __name__ == "__main__":
    dados = carregar_dados()  # le todos os dados do resultados.csv

    # Dicionario com o nome de cada exercicio, usado nos titulos e legendas
    nomes = {
        1: "Insertion Sort",
        2: "Selection Sort",
        3: "Bubble Sort",
        4: "Quick Sort",
        5: "Merge Sort",
    }

    # Gera um grafico individual para cada um dos 5 exercicios
    for num, nome in nomes.items():
        plotar_exercicio(dados, num, nome)

    # Gera o grafico comparativo final, usado no Exercicio 6
    plotar_comparacao_geral(dados, nomes)

    print("Graficos salvos: grafico_ex1.png ate grafico_ex5.png, e grafico_comparacao_geral.png")