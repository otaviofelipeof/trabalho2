# Script auxiliar (nao faz parte da implementacao dos algoritmos em si).
# Roda cada um dos 5 programas de ordenacao varias vezes para cada tamanho
# de vetor, calcula a media dos tempos e salva tudo em um arquivo CSV.
# AJUSTE IMPORTANTE: os algoritmos O(n^2) (insertion/bubble no pior caso,
# e selection em ambos os casos) sao testados apenas ate 100.000 elementos,
# em vez de 500.000, devido ao tempo computacional proibitivo. Essa decisao
# esta documentada no relatorio.

import subprocess  # biblioteca para rodar programas externos (os executaveis) e capturar a saida
import csv         # biblioteca para gravar os resultados em formato de tabela CSV
import os          # biblioteca para verificar se arquivos ja existem no disco

# --- Configuracao dos ranges de teste ---

# Range COMPLETO: usado para os casos rapidos, O(n) ou O(n log n)
TAMANHOS_FULL = list(range(0, 500001, 10000))   # 0, 10000, 20000, ..., 500000
REPETICOES_FULL = 10                              # 10 repeticoes por ponto

# Range REDUZIDO: usado para os casos O(n^2), computacionalmente caros
TAMANHOS_CAPPED = list(range(0, 100001, 10000))  # 0, 10000, ..., 100000
REPETICOES_CAPPED = 5                              # 5 repeticoes (minimo exigido pelo enunciado)

# Dicionario que associa o numero de cada exercicio ao nome do executavel
# correspondente. No Linux (Colab), o "./" na frente e obrigatorio para
# rodar um programa que esta na pasta atual, sem extensao ".exe"
EXECUTAVEIS = {
    1: "./ex1",  # insertion sort
    2: "./ex2",  # selection sort
    3: "./ex3",  # bubble sort
    4: "./ex4",  # quick sort
    5: "./ex5",  # merge sort
}

# Define, para cada combinacao (numero do exercicio, caso), se o teste usa
# o range completo ("full") ou o range reduzido ("capped")
CONFIGURACAO = {
    (1, "m"): "full",    # insertion sort melhor caso: O(n), rapido
    (1, "p"): "capped",  # insertion sort pior caso: O(n^2), lento
    (2, "m"): "capped",  # selection sort melhor caso: sempre O(n^2)
    (2, "p"): "capped",  # selection sort pior caso: sempre O(n^2)
    (3, "m"): "full",    # bubble sort melhor caso: O(n) otimizado, rapido
    (3, "p"): "capped",  # bubble sort pior caso: O(n^2), lento
    (4, "m"): "full",    # quick sort melhor caso: O(n log n) em media, rapido
    (4, "p"): "capped",  # quick sort pior caso: O(n^2), lento
    (5, "m"): "full",    # merge sort melhor caso: sempre O(n log n), rapido
    (5, "p"): "full",    # merge sort pior caso: sempre O(n log n), rapido
}

def rodar_uma_vez(executavel, arquivo_entrada):
    # Roda o programa UMA vez, usando o conteudo do arquivo como entrada padrao.
    # Retorna o tempo em nanossegundos, ou None se o programa falhar
    # (por exemplo, estouro de pilha em alguma recursao muito profunda)
    with open(arquivo_entrada, "r") as f:  # abre o arquivo de teste para leitura
        resultado = subprocess.run(
            [executavel],        # qual programa rodar (ex: "./ex1")
            stdin=f,              # o conteudo do arquivo vira a entrada padrao do programa
            capture_output=True,  # captura tudo que o programa imprime
            text=True             # trata a saida como texto (nao como bytes)
        )

    # returncode diferente de 0 significa que o programa terminou com erro
    if resultado.returncode != 0:
        return None  # avisa que essa execucao falhou

    # Percorre cada linha da saida do programa procurando "Tempo (ns): <numero>"
    for linha in resultado.stdout.splitlines():
        if linha.startswith("Tempo (ns):"):
            # Pega o texto depois dos dois pontos, remove espacos extras,
            # e converte de texto para numero inteiro
            return int(linha.split(":")[1].strip())

    # Se nao achou a linha esperada na saida, algo deu errado
    return None

def media_de_execucoes(executavel, arquivo_entrada, repeticoes):
    # Roda o mesmo teste varias vezes e calcula a media, para reduzir
    # o efeito de ruido/flutuacoes do sistema operacional
    tempos = []  # lista vazia que vai guardar o tempo de cada execucao
    for _ in range(repeticoes):  # repete "repeticoes" vezes (o _ indica que nao usamos o contador)
        tempo = rodar_uma_vez(executavel, arquivo_entrada)  # roda uma vez e pega o tempo
        if tempo is None:
            # Se uma unica execucao falhar, descartamos a media inteira,
            # em vez de calcular a media so das execucoes que deram certo
            return None
        tempos.append(tempo)  # adiciona o tempo na lista
    return sum(tempos) / len(tempos)  # media = soma de tudo dividido pela quantidade

def carregar_combinacoes_ja_feitas(caminho_csv):
    # Le o resultados.csv existente (se houver) e devolve um conjunto com
    # as combinacoes (exercicio, caso, n) ja calculadas. Isso permite
    # retomar a execucao de onde parou, caso o script seja interrompido.
    feitas = set()  # conjunto vazio (nao permite duplicatas)
    if os.path.exists(caminho_csv):          # so le se o arquivo ja existir
        with open(caminho_csv, "r", newline="") as f:
            reader = csv.DictReader(f)          # le cada linha como um dicionario
            for linha in reader:                  # percorre todas as linhas do CSV
                # monta a tupla (exercicio, caso, n) e adiciona ao conjunto
                feitas.add((int(linha["exercicio"]), linha["caso"], int(linha["n"])))
    return feitas

def main():
    caminho_csv = "resultados.csv"  # nome do arquivo onde os resultados serao salvos

    # Carrega quais combinacoes ja foram calculadas em uma execucao anterior
    ja_feitas = carregar_combinacoes_ja_feitas(caminho_csv)
    if ja_feitas:
        print(f"Retomando execucao: {len(ja_feitas)} combinacoes ja calculadas serao puladas.")

    # Verifica se o arquivo CSV ja existia antes desta execucao
    arquivo_novo = not os.path.exists(caminho_csv)

    # Abre o CSV em modo "append" (adicionar ao final, sem apagar o que ja tem)
    csv_file = open(caminho_csv, "a", newline="")
    writer = csv.writer(csv_file)

    # Se o arquivo e novo, escreve o cabecalho primeiro
    if arquivo_novo:
        writer.writerow(["exercicio", "caso", "n", "tempo_ns"])
        csv_file.flush()  # forca a escrita no disco imediatamente

    # Percorre cada um dos 5 exercicios
    for num_exercicio, exe in EXECUTAVEIS.items():
        # Percorre melhor caso ("m") e pior caso ("p")
        for caso in ["m", "p"]:
            # Consulta a configuracao para saber qual range/repeticoes usar
            tipo = CONFIGURACAO[(num_exercicio, caso)]
            if tipo == "full":
                tamanhos = TAMANHOS_FULL
                repeticoes = REPETICOES_FULL
            else:
                tamanhos = TAMANHOS_CAPPED
                repeticoes = REPETICOES_CAPPED

            # Percorre cada tamanho de vetor dentro do range escolhido
            for n in tamanhos:
                # Se essa combinacao ja foi calculada antes, pula
                if (num_exercicio, caso, n) in ja_feitas:
                    continue

                # Monta o nome do arquivo de teste correspondente (ex: "p1v10000.txt")
                arquivo = f"{caso}{num_exercicio}v{n}.txt"

                # Roda o teste varias vezes e calcula a media
                media = media_de_execucoes(exe, arquivo, repeticoes)

                if media is None:
                    # Avisa no terminal que esse ponto foi pulado (ex: falha de execucao)
                    print(f"Exercicio {num_exercicio} | caso={caso} | n={n} | FALHOU (pulado)")
                    continue

                # Escreve a linha imediatamente no CSV e salva em disco (flush),
                # para nao perder progresso se o script for interrompido depois
                writer.writerow([num_exercicio, caso, n, media])
                csv_file.flush()

                # Mostra o progresso no terminal
                print(f"Exercicio {num_exercicio} | caso={caso} | n={n} | media={media:.2f}ns")

    csv_file.close()  # fecha o arquivo CSV ao final
    print("Concluido! Resultados salvos em resultados.csv")

# So executa o main() se este arquivo for rodado diretamente
if __name__ == "__main__":
    main()