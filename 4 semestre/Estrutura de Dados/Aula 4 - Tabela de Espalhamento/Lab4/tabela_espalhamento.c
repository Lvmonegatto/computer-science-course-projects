#include <stdio.h>
#include <stdlib.h>

#define tam_hash 11

typedef struct Celula{
  int valor;
  struct Celula* proximo;
}Celula;

typedef struct {
  Celula* inicio;
}Lista;

typedef struct {
  Lista* table[tam_hash];
}Hash;

// Inicializa a tabela hash e aloca as listas encadeadas para cada bucket
Hash* start_hash(){
  Hash* hash = (Hash*) malloc(sizeof(Hash));
  if (hash == NULL) {
    exit(1);
  }
  
  for (int i = 0; i < tam_hash; i++) {
    hash->table[i] = (Lista*) malloc(sizeof(Lista));
    if (hash->table[i] == NULL) {
      exit(1);
    }
    hash->table[i]->inicio = NULL; // Lista vazia inicialmente
  }
  
  return hash;
}

// Inserção no início da lista usando a função hash h(k) = valor % tam_hash
void inserir_hash(Hash* hash, int valor){
  if (hash == NULL) return;
  
  int idx = valor % tam_hash;
  
  Celula* nova = (Celula*) malloc(sizeof(Celula));
  if (nova == NULL) {
    exit(1);
  }
  nova->valor = valor;
  
  // Conecta a nova célula no início da lista encadeada
  nova->proximo = hash->table[idx]->inicio;
  hash->table[idx]->inicio = nova;
}

// Remoção de um elemento da tabela hash
void remover_hash(Hash* hash, int valor){
  if (hash == NULL) return;
  
  int idx = valor % tam_hash;
  Celula* atual = hash->table[idx]->inicio;
  Celula* anterior = NULL;
  
  while (atual != NULL) {
    if (atual->valor == valor) {
      if (anterior == NULL) {
        // Remoção do elemento no início da lista
        hash->table[idx]->inicio = atual->proximo;
      } else {
        // Remoção no meio ou fim da lista
        anterior->proximo = atual->proximo;
      }
      free(atual); // Libera memória da célula removida
      return;
    }
    anterior = atual;
    atual = atual->proximo;
  }
}

// Exibe a tabela hash conforme a formatação especificada
void imprimir(Hash* hash){
  if (hash == NULL) return;
  
  printf("--------------------\n");
  for (int i = 0; i < tam_hash; i++) {
    printf("%d -> ", i);
    Celula* atual = hash->table[i]->inicio;
    while (atual != NULL) {
      printf("%d ", atual->valor);
      atual = atual->proximo;
    }
    printf("\n");
  }
  printf("--------------------\n");
}

int main(void) {
  Hash* hash = start_hash();
  int valor;
  
  // Leitura e inserção dos valores até digitar 0
  while(1){
    scanf("%d", &valor);
    if(valor == 0)
      break;
    inserir_hash(hash, valor);
  }
  
  imprimir(hash);
  
  // Leitura e remoção dos valores até digitar 0
  while(1){
    scanf("%d", &valor);
    if(valor == 0)
      break;
    remover_hash(hash, valor);
  }
  
  imprimir(hash);
  
  return 0;
}

// ### Passo a Passo Lógico da Implementação

// 1. **`start_hash`**: Aloca a estrutura `Hash` e cada um dos \\(11\\) ponteiros do tipo `Lista*`, inicializando o ponteiro `inicio` de cada lista como `NULL`.
// 2. **`inserir_hash`**: 
//    - Calcula o índice `idx = valor % tam_hash`.
//    - Aloca dinamicamente uma nova `Celula`.
//    - Ajusta os ponteiros para que a nova célula aponte para o antigo `inicio` e, em seguida, torna a nova célula o novo `inicio` daquela posição.
// 3. **`remover_hash`**:
//    - Localiza o índice correspondente `idx = valor % tam_hash`.
//    - Percorre a lista encadeada mantendo o nó `anterior` e o `atual`.
//    - Ao encontrar o valor, desvincula o nó da lista e chama `free(atual)` para desalocar a memória.
// 4. **`imprimir`**:
//    - Imprime a barra superior de \\(20\\) hífens.
//    - Percorre cada posição de \\(0\\) a \\(10\\), imprimindo `i -> ` e encadeando a impressão dos valores armazenados no bucket.
//    - Imprime a barra inferior de \\(20\\) hífens.

// ---

// 💡 Quer testar a simulação dessa tabela hash com outros valores de entrada para observar o comportamento do fator de carga e das colisões?