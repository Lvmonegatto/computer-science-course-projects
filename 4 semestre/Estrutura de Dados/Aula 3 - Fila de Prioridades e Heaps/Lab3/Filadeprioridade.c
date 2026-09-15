#include <stdio.h>
#include <stdlib.h>

#define LEN 10

// Estrutura que representa um Heap.
//
// valores[] = vetor onde os elementos do Heap são armazenados.
// qtde      = quantidade atual de elementos no Heap.
typedef struct {
    int valores[LEN];
    int qtde;
} heap;


/*
    ============================
    CÁLCULO DOS ÍNDICES NO HEAP
    ============================

    O Heap é armazenado em um vetor, mas representa uma árvore.

    Para um elemento na posição "pai":

             pai
            /   \
         esq     dir

    Os índices são calculados assim:

    filho esquerdo = 2 * pai + 1
    filho direito  = 2 * pai + 2

    E para descobrir o pai:

    pai = (filho - 1) / 2
*/


// Retorna o índice do filho esquerdo.
int filho_esq(int pai){
    return 2 * pai + 1;
}


// Retorna o índice do filho direito.
int filho_dir(int pai){
    return 2 * pai + 2;
}


// Retorna o índice do pai de um filho.
int pai(int filho){
    return (filho - 1) / 2;
}


/*
    Retorna o índice do último elemento que possui filhos.

    Exemplo:

    Heap com 10 elementos:

    índices:
    0 1 2 3 4 5 6 7 8 9

    Os últimos elementos do vetor são folhas e não possuem filhos.

    A fórmula para encontrar o último pai é:

    (qtde / 2) - 1

    Isso é útil para construir um Heap.
*/
int ultimo_pai(heap *h){
    return (h->qtde / 2) - 1;
}


/*
    =================
    PENEIRAR PARA BAIXO
    =================

    Essa função é usada quando um elemento pode estar MENOR
    que algum de seus filhos.

    Como estamos trabalhando com um HEAP DE MÁXIMO:

        pai >= filhos

    Se algum filho for maior que o pai:

        1. Descobrimos qual filho é o maior.
        2. Trocamos o pai com esse filho.
        3. Continuamos verificando para baixo.

    Exemplo:

           3
          / \
         8   5

    O pai deveria ser o maior.

    Então trocamos:

           8
          / \
         3   5

    Depois verificamos novamente o 3 em sua nova posição.
*/
void peneirar(heap *h, int pai_idx){

    // Calcula as posições dos dois filhos.
    int esq = filho_esq(pai_idx);
    int dir = filho_dir(pai_idx);

    // Inicialmente assumimos que o pai é o maior.
    int maior = pai_idx;


    // Verifica se o filho esquerdo existe
    // e se ele é maior que o elemento atual.
    if (esq < h->qtde &&
        h->valores[esq] > h->valores[maior]) {

        maior = esq;
    }


    // Verifica se o filho direito existe
    // e se ele é maior que o maior encontrado até agora.
    if (dir < h->qtde &&
        h->valores[dir] > h->valores[maior]) {

        maior = dir;
    }


    /*
        Se "maior" ainda for pai_idx, significa que:

            pai >= filho esquerdo
            pai >= filho direito

        Portanto, a propriedade do Heap está correta.

        Caso contrário, precisamos trocar o pai
        pelo maior dos filhos.
    */
    if (maior != pai_idx) {

        // Faz a troca entre o pai e o maior filho.
        int temp = h->valores[pai_idx];

        h->valores[pai_idx] = h->valores[maior];

        h->valores[maior] = temp;


        /*
            Depois da troca, o elemento que estava no pai
            foi parar mais abaixo.

            Portanto, precisamos continuar verificando
            se ele ainda é maior que seus novos filhos.
        */
        peneirar(h, maior);
    }
}


/*
    ===============
    PENEIRAR PARA CIMA
    ===============

    Essa função é usada principalmente após inserir
    um novo elemento no final do Heap.

    O novo elemento pode ser maior que seu pai.

    Como estamos em um Heap de Máximo:

        filho <= pai

    Se:

        filho > pai

    fazemos a troca e continuamos subindo.

    Exemplo:

        Antes:

             10
            /
           15

        O 15 não pode ficar abaixo do 10.

        Depois da troca:

             15
            /
           10
*/
void peneirar_para_cima(heap *h, int filho_idx){

    /*
        Se chegamos ao índice 0,
        significa que chegamos à raiz.

        A raiz não possui pai.
    */
    if (filho_idx <= 0) {
        return;
    }


    // Descobre a posição do pai.
    int p_idx = pai(filho_idx);


    /*
        Se o filho for maior que o pai,
        a propriedade do Heap foi violada.

        Então fazemos a troca.
    */
    if (h->valores[filho_idx] > h->valores[p_idx]) {

        int temp = h->valores[filho_idx];

        h->valores[filho_idx] = h->valores[p_idx];

        h->valores[p_idx] = temp;


        /*
            Depois da troca, o elemento continua
            podendo ser maior que seu novo pai.

            Por isso continuamos o processo para cima.
        */
        peneirar_para_cima(h, p_idx);
    }
}


/*
    ===================
    CONSTRUIR O HEAP
    ===================

    Essa função transforma um vetor comum
    em um Heap de Máximo.

    O processo começa no último nó que possui filhos
    e vai voltando até a raiz.

    Para cada pai, aplicamos "peneirar para baixo".

    Exemplo:

    Vetor comum:

        [3, 8, 5, 2, 10]

    Vamos corrigindo os pais até que:

        pai >= filhos

    seja verdadeiro para todos os elementos.
*/
void construir(heap *h){

    // Começa no último pai e vai até a raiz.
    for (int i = ultimo_pai(h); i >= 0; i--) {

        // Corrige o Heap a partir desse pai.
        peneirar(h, i);
    }
}


/*
    ==============
    INSERIR
    ==============

    Passos para inserir em um Heap:

    1. Colocar o novo elemento no final do vetor.
    2. Aumentar a quantidade de elementos.
    3. Comparar o novo elemento com seu pai.
    4. Se ele for maior, subir.
    5. Continuar até encontrar a posição correta.
*/
void inserir(heap *h, int valor){

    // Verifica se ainda existe espaço no Heap.
    if (h->qtde < LEN) {

        /*
            PASSO 1:

            Coloca o novo elemento na próxima posição livre.

            Exemplo:

            [10, 8, 6, _, _, ...]

            Inserindo 12:

            [10, 8, 6, 12, _, ...]
        */
        h->valores[h->qtde] = valor;


        /*
            PASSO 2:

            Agora o elemento oficialmente faz parte do Heap.
        */
        h->qtde++;


        /*
            PASSO 3:

            O novo elemento está na posição:

                qtde - 1

            Agora verificamos se ele precisa subir.
        */
        peneirar_para_cima(h, h->qtde - 1);

    }  
}


/*
    ==============
    REMOVER
    ==============

    Em um Heap de Máximo:

        O maior elemento está sempre na raiz.

    Ou seja:

        valores[0]

    Para remover a raiz:

    PASSO 1:
        Colocamos o último elemento no lugar da raiz.

    PASSO 2:
        Diminuímos a quantidade de elementos.

    PASSO 3:
        O novo elemento da raiz pode ser menor
        que seus filhos.

        Então usamos "peneirar para baixo".
*/
void remover(heap *h){

    // Verifica se existe pelo menos um elemento.
    if (h->qtde > 0) {


        /*
            PASSO 1:

            Move o último elemento para a raiz.

            Exemplo:

            Antes:

                [10, 8, 6, 5, 3]

            Removendo o 10:

                [3, 8, 6, 5]

            O 3 agora está na raiz.
        */
        h->valores[0] = h->valores[h->qtde - 1];


        /*
            PASSO 2:

            Reduz a quantidade de elementos.

            O último elemento não faz mais parte
            logicamente do Heap.
        */
        h->qtde--;


        /*
            PASSO 3:

            O elemento colocado na raiz pode
            estar menor que seus filhos.

            Exemplo:

                  3
                 / \
                8   6

            Então usamos "peneirar para baixo"
            para restaurar a propriedade do Heap.
        */
        if (h->qtde > 0) {
            peneirar(h, 0);
        }

    } 
}


/*
    ==========
    MOSTRAR
    ==========

    Percorre apenas as posições que fazem parte
    do Heap.

    Importante:

        O vetor pode possuir LEN posições,
        mas apenas "qtde" delas estão sendo usadas.
*/
void mostrar(heap *h){

    for (int i = 0; i < h->qtde; i++) {

        // Imprime cada elemento do Heap.
        printf("%d", h->valores[i]);

        // Coloca espaço somente entre os elementos.
        if (i < h->qtde - 1) {
            printf(" ");
        }
    }

    printf("\n");
}


int main(void) {


    /*
        Cria dinamicamente um Heap na memória.

        malloc(sizeof(heap))

        Reserva espaço suficiente para toda
        a estrutura heap.
    */
    heap *h = malloc(sizeof(heap));


    /*
        Inicialmente o Heap está vazio.

        Portanto, possui zero elementos.
    */
    h->qtde = 0;


    /*
        =========================
        TESTE 1: INSERÇÃO
        =========================

        Vamos inserir os números de 1 até 10.

        Após cada inserção, mostramos o Heap.

        Como é um Heap de Máximo,
        o maior número deve ir ficando
        próximo da raiz.
    */
    printf("--- TESTE 1: Inserção de elementos ---\n");

    for(int i = 1; i <= 10; i++){

        // Insere o valor i.
        inserir(h, i);

        // Mostra qual valor foi inserido.
        printf("Inserido %d: ", i);

        // Mostra como ficou o Heap.
        mostrar(h);
    }


    /*
        =========================
        TESTE 2: REMOÇÃO
        =========================

        Enquanto existirem elementos:

        1. Pegamos a raiz.
        2. A raiz é o maior elemento.
        3. Mostramos o valor que será removido.
        4. Removemos.
        5. O Heap se reorganiza.
    */
    printf("\n--- TESTE 2: Remoção de elementos ---\n");
    printf("Removendo em ordem de prioridade:\n");


    // Continua removendo enquanto o Heap não estiver vazio.
    while(h->qtde > 0) {


        /*
            Em um Heap de Máximo,
            o maior elemento está sempre na raiz.

            A raiz está na posição 0.
        */
        int max = h->valores[0];


        // Mostra qual é o maior elemento atual.
        printf("Removendo máximo %d: ", max);


        // Remove o maior elemento e reorganiza o Heap.
        remover(h);


        // Mostra como ficou o Heap após a remoção.
        mostrar(h);
    }


    /*
        Libera a memória que foi reservada com malloc.

        Sempre que usamos malloc,
        devemos liberar a memória com free.
    */
    free(h);


    // Indica que o programa terminou corretamente.
    return 0;
}