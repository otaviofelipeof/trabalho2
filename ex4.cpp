// Trabalho 2 - EDB1 (DIM0119)
// Exercicio 4: Quick Sort (particao de Lomuto)
// Autor: Otávio Felipe

#include <iostream>  
#include <vector>     
#include <chrono>     
using namespace std;  

// Funcao de particao (Lomuto). Recebe o vetor A e o intervalo [esq, dir)
// (aqui 'dir' e EXCLUSIVO, entao o ultimo elemento valido e dir - 1).
// Escolhe o ULTIMO elemento do intervalo como pivo, rearranja o vetor de
// forma que tudo <= pivo fique a esquerda e tudo > pivo fique a direita,
// e retorna o indice final onde o pivo ficou posicionado.
int particiona(int A[], int esq, int dir) {
    int pivo = A[dir - 1];  // escolhe o ultimo elemento do intervalo como pivo
    int i = esq - 1;         // 'i' marca o fim da regiao dos elementos <= pivo (ainda vazia)

    // percorre do inicio ate o penultimo elemento (o ultimo e o pivo, ja separado)
    for (int j = esq; j < dir - 1; j++) {
        if (A[j] <= pivo) {
            i++;  // avanca a fronteira da regiao dos menores/iguais ao pivo

            // troca A[i] com A[j], movendo o elemento pequeno pra dentro
            // da regiao dos "menores ou iguais ao pivo"
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
        // se A[j] > pivo, nao faz nada: o elemento permanece onde esta,
        // automaticamente ficando "do lado direito" por enquanto
    }

    // depois do laco, troca o pivo (que estava em dir - 1) para a posicao
    // logo apos a regiao dos menores/iguais, colocando-o em sua posicao final
    int temp = A[i + 1];
    A[i + 1] = A[dir - 1];
    A[dir - 1] = temp;

    return i + 1;  // retorna o indice onde o pivo ficou posicionado
}

// Ordena o vetor A no intervalo [esq, dir) usando quick sort.
// Ideia: particiona o vetor em torno de um pivo, depois ordena
// recursivamente as duas metades (esquerda e direita do pivo).
void quickSort(int A[], int esq, int dir) {
    // So faz sentido particionar se houver pelo menos 2 elementos no intervalo
    if (dir - esq > 1) {
        int q = particiona(A, esq, dir);  // particiona e pega a posicao final do pivo

        quickSort(A, esq, q);      // ordena recursivamente a parte esquerda (antes do pivo)
        quickSort(A, q + 1, dir);  // ordena recursivamente a parte direita (depois do pivo)
    }
    // se o intervalo tiver 0 ou 1 elemento, ja esta "ordenado" por definicao,
    // entao nao faz nada (caso base implicito)
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
    quickSort(A.data(), 0, n);

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