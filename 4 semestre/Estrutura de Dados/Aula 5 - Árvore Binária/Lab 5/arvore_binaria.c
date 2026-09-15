#include <stdio.h>
#include <stdlib.h>

#define tam_hash 11

// Cada Celula representa um elemento da lista encadeada
typedef struct Celula{
    int valor;
    struct Celula* proximo;
} Celula;

// Cada posição da tabela hash possui uma lista
typedef struct {
    Celula* inicio;
} Lista;

// A tabela hash possui 11 posições
typedef struct {
    Lista* table[tam_hash];
} Hash;


// Cria e inicializa a tabela hash
Hash* start_hash(){

    // Aloca memória para a tabela hash
    Hash* hash = (Hash*) malloc(sizeof(Hash));

    // Verifica se a memória foi alocada
    if (hash == NULL) {
        exit(1);
    }

    // Percorre todas as posições da tabela
    for (int i = 0; i < tam_hash; i++) {

        // Cria uma lista para cada posição
        hash->table[i] = (Lista*) malloc(sizeof(Lista));

        // Verifica se a memória foi alocada
        if (hash->table[i] == NULL) {
            exit(1);
        }

        // Inicialmente a lista está vazia
        hash->table[i]->inicio = NULL;
    }

    // Retorna a tabela criada
    return hash;
}


// Insere um valor na tabela hash
void inserir_hash(Hash* hash, int valor){

    // Se a tabela não existir, não faz nada
    if (hash == NULL) return;

    // Calcula a posição onde o valor será armazenado
    // O resto da divisão determina o índice
    int idx = valor % tam_hash;

    // Cria uma nova célula
    Celula* nova = (Celula*) malloc(sizeof(Celula));

    // Verifica se a memória foi alocada
    if (nova == NULL) {
        exit(1);
    }

    // Guarda o valor na nova célula
    nova->valor = valor;

    // A nova célula aponta para o primeiro elemento atual da lista
    nova->proximo = hash->table[idx]->inicio;

    // A nova célula passa a ser o primeiro elemento da lista
    hash->table[idx]->inicio = nova;
}


// Remove um valor da tabela hash
void remover_hash(Hash* hash, int valor){

    // Se a tabela não existir, não faz nada
    if (hash == NULL) return;

    // Calcula em qual posição o valor deveria estar
    int idx = valor % tam_hash;

    // Começa pelo primeiro elemento da lista
    Celula* atual = hash->table[idx]->inicio;

    // Guarda o elemento anterior
    // No início não existe anterior
    Celula* anterior = NULL;

    // Percorre a lista
    while (atual != NULL) {

        // Verifica se encontrou o valor
        if (atual->valor == valor) {

            // Se anterior é NULL, estamos removendo o primeiro elemento
            if (anterior == NULL) {
                hash->table[idx]->inicio = atual->proximo;
            }

            // Caso contrário, o elemento anterior
            // passa a apontar para o próximo
            else {
                anterior->proximo = atual->proximo;
            }

            // Libera a memória do elemento removido
            free(atual);

            // Termina a função
            return;
        }

        // Avança o anterior
        anterior = atual;

        // Avança o atual
        atual = atual->proximo;
    }
}


// Imprime toda a tabela hash
void imprimir(Hash* hash){

    // Se a tabela não existir, não faz nada
    if (hash == NULL) return;

    printf("---------------------\n");

    // Percorre todas as posições da tabela
    for (int i = 0; i < tam_hash; i++) {

        // Mostra o índice atual
        printf("%d -> ", i);

        // Começa pelo primeiro elemento da lista
        Celula* atual = hash->table[i]->inicio;

        // Percorre os elementos daquela posição
        while (atual != NULL) {

            // Mostra o valor
            printf("%d ", atual->valor);

            // Vai para o próximo elemento
            atual = atual->proximo;
        }

        printf("\n");
    }

    printf("---------------------\n");
}


int main(void) {

    // Cria a tabela hash
    Hash* hash = start_hash();

    int valor;

    // Loop para inserir valores
    while(1){

        // Lê um valor
        scanf("%d", &valor);

        // 0 indica que terminou a entrada
        if(valor == 0)
            break;

        // Insere o valor na tabela
        inserir_hash(hash, valor);
    }

    // Mostra a tabela depois das inserções
    imprimir(hash);


    // Loop para remover valores
    while(1){

        // Lê um valor
        scanf("%d", &valor);

        // 0 indica que terminou a entrada
        if(valor == 0)
            break;

        // Remove o valor da tabela
        remover_hash(hash, valor);
    }

    // Mostra a tabela depois das remoções
    imprimir(hash);

    return 0;
}

// ### Passo a Passo da Linha de Raciocínio Lógico

// #### 1. A Propriedade da Árvore Binária de Busca (BST)
// Uma **Árvore Binária de Busca** organiza seus nós de modo que, para qualquer nó \\(x\\):
// * Todos os nós na sua subárvore esquerda possuem valores **menores ou iguais** a \\(x\\).
// * Todos os nós na sua subárvore direita possuem valores **maiores ou iguais** a \\(x\\).

// ---

// #### 2. Percursos de Travessia (Travessias Recursivas)
// Para visitar e imprimir todos os vértices de uma árvore, utilizamos chamadas recursivas baseadas na ordem de visita da raiz:

// 1. **Em-Ordem (`in_ordem` / E-R-D):**
//    * Visita a subárvore esquerda \\(\rightarrow\\) Imprime o nó atual \\(\rightarrow\\) Visita a subárvore direita.
//    * *Resultado:* Exibe sempre os elementos em **ordem crescente**.
// 2. **Pré-Ordem (`pre_ordem` / R-E-D):**
//    * Imprime o nó atual \\(\rightarrow\\) Visita a subárvore esquerda \\(\rightarrow\\) Visita a subárvore direita.
// 3. **Pós-Ordem (`pos_ordem` / E-D-R):**
//    * Visita a subárvore esquerda \\(\rightarrow\\) Visita a subárvore direita \\(\rightarrow\\) Imprime o nó atual.

// ---

// #### 3. Inserção de Elementos (`inserir`)
// A inserção sempre adiciona o novo valor como uma **folha** no final de um caminho de busca:
// 1. Inicializamos dois ponteiros: `atual` (começa na raiz) e `pai` (inicialmente nulo).
// 2. Descemos na árvore comparando o novo valor com o nó `atual`: se o valor for menor, vamos para a esquerda; se for maior, vamos para a direita.
// 3. Quando `atual` se torna `NULL`, encontramos a posição vaga.
// 4. Conectamos o novo nó como filho esquerdo ou direito do ponteiro `pai` (ou como nova raiz se a árvore estiver vazia).

// ---

// #### 4. Remoção de Elementos (`remover_vertice`)
// A remoção exige tratar três cenários fundamentais para manter a propriedade de busca:

// * **Caso 1 (Folha ou sem filho esquerdo):** Se o nó a ser removido não tem filho esquerdo, ele é simplesmente substituído pelo seu filho direito (que pode ser `NULL`).
// * **Caso 2 (Sem filho direito):** Se o nó tem apenas o filho esquerdo, ele é substituído diretamente por esse filho esquerdo.
// * **Caso 3 (Dois filhos):** Quando o nó \\(z\\) possui ambos os filhos:
//   1. Encontramos o seu **sucessor em-ordem** \\(y\\) (o menor nó na subárvore direita de \\(z\\)).
//   2. O sucessor \\(y\\) toma o lugar de \\(z\\) na árvore, preservando a ordenação de todos os demais descendentes.
//   3. Utilizamos a função auxiliar `transplant` para ajustar os ponteiros de pai e filhos com segurança sem perder referências.