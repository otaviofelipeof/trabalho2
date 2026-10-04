// Trabalho 2 - EDB1 (DIM0119)
// Exercicio 5: Merge Sort
// Autor: Otávio Felipe

#include <iostream>   
#include <vector>     
#include <chrono>     
using namespace std;  

// Intercala dois vetores ORDENADOS (L e R) escrevendo direto dentro de A,
// a partir da posicao 'esq'. nL e nR sao os tamanhos de L e R, respectivamente.
void intercala(int L[], int nL, int R[], int nR, int A[], int esq) {
    int i = 0;    // indice para percorrer o vetor L
    int j = 0;    // indice para percorrer o vetor R
    int k = esq;  // indice para preencher A, comecando na posicao 'esq'

    // enquanto ainda existem elementos nos DOIS vetores (L e R),
    // compara as "frentes" de cada um e copia o menor para A
    while (i < nL && j < nR) {
        if (L[i] <= R[j]) {
            A[k] = L[i];  // elemento da esquerda e menor ou igual: vai primeiro
            i++;           // avanca o indice de L
        } else {
            A[k] = R[j];  // elemento da direita e menor: vai primeiro
            j++;           // avanca o indice de R
        }
        k++;  // avanca o indice de A, independente de qual lado veio o elemento
    }

    // nesse ponto, um dos dois vetores (L ou R) ja foi totalmente consumido.
    // copia o que sobrou de L, se sobrou algo
    while (i < nL) {
        A[k] = L[i];
        i++;
        k++;
    }

    // copia o que sobrou de R, se sobrou algo
    while (j < nR) {
        A[k] = R[j];
        j++;
        k++;
    }
}

// Ordena o vetor A no intervalo [esq, dir) usando merge sort.
// Ideia (divisao e conquista): divide o vetor ao meio, ordena cada
// metade recursivamente, e depois intercala as duas metades ordenadas.
void mergeSort(int A[], int esq, int dir) {
    int n = dir - esq;  // quantidade de elementos no intervalo atual

    // caso base: 0 ou 1 elemento ja esta ordenado, nao ha nada a fazer
    if (n < 2) {
        return;
    }

    int mid = esq + n / 2;  // indice que divide o intervalo ao meio

    int nL = mid - esq;   // tamanho da metade esquerda
    int nR = dir - mid;   // tamanho da metade direita

    // aloca dois vetores auxiliares temporarios para guardar cada metade.
    // isso e necessario porque o merge sort NAO e in-place: precisa de
    // espaco extra para intercalar sem sobrescrever dados que ainda nao foram lidos
    int* L = new int[nL];
    int* R = new int[nR];

    // copia os elementos da metade esquerda de A para L
    for (int i = 0; i < nL; i++) {
        L[i] = A[esq + i];
    }

    // copia os elementos da metade direita de A para R
    for (int i = 0; i < nR; i++) {
        R[i] = A[mid + i];
    }

    // ordena cada metade recursivamente (sempre comecando do indice 0,
    // porque L e R sao vetores novos e independentes do vetor original)
    mergeSort(L, 0, nL);
    mergeSort(R, 0, nR);

    // intercala as duas metades ja ordenadas de volta dentro de A,
    // escrevendo a partir da posicao 'esq'
    intercala(L, nL, R, nR, A, esq);

    // libera a memoria alocada para os vetores auxiliares,
    // evitando vazamento de memoria (o enunciado penaliza isso)
    delete[] L;
    delete[] R;
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
    mergeSort(A.data(), 0, n);

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