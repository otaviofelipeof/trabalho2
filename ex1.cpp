// Trabalho 2 - EDB1 (DIM0119)
// Exercicio 1: Insertion Sort
// Autor: Otávio Felipe

#include <iostream>   
#include <vector>     
#include <chrono>     
using namespace std;  

// Ordena o vetor A no intervalo [esq, dir) usando insertion sort.
// Ideia: a cada passo, pega o elemento na posicao i (chamado de "key")
// e insere ele na posicao correta dentro da parte ja ordenada [esq, i).
void insertionSort(int A[], int esq, int dir) {
    // Comeca em esq + 1, porque um unico elemento (posicao esq) ja esta
    // trivialmente ordenado sozinho, nao precisa de comparacao
    for (int i = esq + 1; i < dir; i++) {
        int key = A[i];       // guarda o elemento que queremos inserir na parte ordenada
        int holePos = i - 1;  // comeca comparando com o elemento imediatamente anterior

        // Desloca elementos maiores que key uma posicao para a frente,
        // abrindo espaco (um "buraco") para inserir key no lugar certo.
        // A condicao holePos >= esq impede sair do intervalo valido.
        while (holePos >= esq && A[holePos] > key) {
            A[holePos + 1] = A[holePos]; // desloca o elemento maior uma posicao a frente
            holePos--;                    // move o "cursor" de comparacao uma posicao pra tras
        }

        // Quando o laco para, holePos+1 e a posicao correta para key
        A[holePos + 1] = key; // insere key no "buraco" que sobrou
    }
}

int main() {
    // Desativa a sincronizacao entre os streams de C++ (cin/cout) e os
    // streams de C (scanf/printf). Por padrao eles ficam sincronizados,
    // o que deixa a leitura mais lenta. Como nao usamos scanf/printf
    // neste programa, podemos desativar com seguranca.
    ios::sync_with_stdio(false);

    // Remove o vinculo entre cin e cout. Por padrao, cada cin "espera"
    // qualquer cout pendente ser mostrado primeiro (flush automatico).
    // Desvincular evita esse custo extra, acelerando a leitura.
    cin.tie(nullptr);

    int n;          // vai guardar o tamanho do vetor
    cin >> n;       // le o tamanho (primeira linha do arquivo de entrada)

    vector<int> A(n);           // cria um vetor de tamanho n, ja alocado
    for (int i = 0; i < n; i++) {
        cin >> A[i];              // le cada elemento a ser ordenado
    }

    // Marca o instante de tempo imediatamente antes da ordenacao,
    // para que a leitura da entrada nao entre na medicao
    auto inicio = chrono::high_resolution_clock::now();

    // A.data() devolve o ponteiro para os dados internos do vector,
    // permitindo passar para a funcao que espera um int[].
    // Intervalo [0, n) = o vetor inteiro
    insertionSort(A.data(), 0, n);

    // Marca o instante de tempo logo apos a ordenacao terminar
    auto fim = chrono::high_resolution_clock::now();

    // Calcula a diferenca entre os dois instantes, convertendo para nanossegundos
    auto duracao = chrono::duration_cast<chrono::nanoseconds>(fim - inicio);

    // Imprime o vetor ja ordenado, mas so se for pequeno o suficiente
    // para ser util conferir visualmente (vetores grandes nao valeriam a pena)
    if (n <= 20) {
        for (int i = 0; i < n; i++) {
            cout << A[i] << " ";  // imprime cada elemento separado por espaco
        }
        cout << endl;  // quebra de linha depois do vetor
    }

    // Imprime o tempo gasto na ordenacao, sempre, independente do tamanho
    cout << "Tempo (ns): " << duracao.count() << endl;

    return 0;  
}