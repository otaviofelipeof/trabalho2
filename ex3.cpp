// Trabalho 2 - EDB1 (DIM0119)
// Exercicio 3: Bubble Sort (versao otimizada)
// Autor: Otávio Felipe

#include <iostream>   
#include <vector>     
#include <chrono>     
using namespace std;  

// Ordena o vetor A no intervalo [esq, dir) usando bubble sort otimizado.
// Ideia: percorre o vetor repetidamente comparando pares adjacentes e
// trocando-os se estiverem fora de ordem. Duas otimizacoes:
// 1) Para assim que uma passada inteira nao faz nenhuma troca (ja esta ordenado).
// 2) A cada passada, o maior elemento "borbulha" para o final, entao o
//    limite direito do intervalo util diminui 1 a cada passada.
void bubbleSort(int A[], int esq, int dir) {
    // 'limite' comeca no ultimo indice valido (dir - 1) e vai diminuindo
    // conforme os maiores elementos vao se acomodando no final do vetor
    int limite = dir - 1;

    bool houveTroca;  // controla se ainda precisamos continuar as passadas

    // 'do...while' porque sempre precisamos fazer pelo menos 1 passada,
    // mesmo que o vetor ja esteja ordenado (para descobrir que esta)
    do {
        houveTroca = false;  // assume, no inicio da passada, que nao vai haver troca

        // percorre do inicio ate o limite atual, comparando pares adjacentes
        for (int i = esq; i < limite; i++) {
            if (A[i + 1] < A[i]) {
                // par fora de ordem: troca os dois elementos de posicao
                int temp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = temp;

                houveTroca = true;  // registra que aconteceu troca nesta passada
            }
            // se o par ja estiver na ordem certa, nao faz nada e segue adiante
        }

        // depois de cada passada completa, o elemento que estava na posicao
        // 'limite' ja esta garantidamente na sua posicao final correta,
        // entao reduzimos o intervalo util em 1
        limite--;

    } while (houveTroca);  // repete enquanto ainda houver trocas a fazer
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
    bubbleSort(A.data(), 0, n);

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