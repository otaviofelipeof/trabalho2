// Trabalho 2 - EDB1 (DIM0119)
// Exercicio 2: Selection Sort
// Autor: Otávio Felipe

#include <iostream>  
#include <vector>     
#include <chrono>     
using namespace std;  

// Ordena o vetor A no intervalo [esq, dir) usando selection sort.
// Ideia: a cada passo, encontra o MENOR elemento da parte ainda
// nao ordenada e troca ele para a frente dessa parte.
void selectionSort(int A[], int esq, int dir) {
    // Percorre cada posicao i, exceto a ultima (quando so sobra 1
    // elemento, ele ja esta automaticamente na posicao certa)
    for (int i = esq; i < dir - 1; i++) {
        int menor = i;  // assume, por enquanto, que o menor esta na posicao i

        // Percorre o restante do vetor (a partir de i+1) procurando
        // um elemento ainda menor que o atual A[menor]
        for (int j = i + 1; j < dir; j++) {
            if (A[j] < A[menor]) {
                menor = j;  // encontrou elemento menor: atualiza o indice guardado
            }
            // se A[j] nao for menor, o laco simplesmente segue para o proximo j
        }

        // Depois de percorrer tudo, troca o menor elemento encontrado
        // para a posicao i (frente da parte ainda nao-ordenada)
        int temp = A[menor];  // guarda temporariamente o valor que esta em A[menor]
        A[menor] = A[i];      // move o valor que estava em A[i] para a posicao do menor
        A[i] = temp;          // coloca o valor menor na posicao i
    }
}

int main() {
    ios::sync_with_stdio(false); // desativa sincronizacao com streams de C (acelera leitura)
    cin.tie(nullptr);             // desvincula cin de cout (acelera ainda mais)

    int n;           // vai guardar o tamanho do vetor
    cin >> n;        // le o tamanho (primeira linha do arquivo)

    vector<int> A(n);            // cria um vetor de tamanho n
    for (int i = 0; i < n; i++) {
        cin >> A[i];               // le cada elemento do vetor
    }

    // marca o instante de tempo antes de comecar a ordenacao
    auto inicio = chrono::high_resolution_clock::now();

    // ordena o vetor inteiro, no intervalo [0, n)
    selectionSort(A.data(), 0, n);

    // marca o instante de tempo depois que a ordenacao terminou
    auto fim = chrono::high_resolution_clock::now();

    // calcula a diferenca de tempo, convertendo para nanossegundos
    auto duracao = chrono::duration_cast<chrono::nanoseconds>(fim - inicio);

    // imprime o vetor ja ordenado, mas so se for pequeno o suficiente
    if (n <= 20) {
        for (int i = 0; i < n; i++) {
            cout << A[i] << " ";    // imprime cada elemento separado por espaco
        }
        cout << endl;  // quebra de linha depois do vetor
    }

    // imprime o tempo gasto na ordenacao
    cout << "Tempo (ns): " << duracao.count() << endl;

    return 0; 
}