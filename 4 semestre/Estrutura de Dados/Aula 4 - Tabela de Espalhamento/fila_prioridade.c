#include <stdio.h>
#include <stdlib.h>

typedef struct Celula{
	struct Celula *anterior;
	struct Celula *proximo;
	int valor;
    int prioridade;
}Celula;

typedef struct Priority_Queue{
	Celula *primeiro;
	int qtde;
}Priority_Queue;

Priority_Queue *inicializa_pq(){
	Priority_Queue *lista = malloc(sizeof(Priority_Queue));
	lista->primeiro = NULL;
	lista->qtde = 0;
	return lista;
}

Celula *inicializa_celula(int valor, int prioridade){
	Celula *celula = malloc(sizeof(Celula));
	celula->anterior = NULL;
	celula->proximo = NULL;
	celula->valor = valor;
    celula->prioridade = prioridade;
	return celula;
}

void infileira(Priority_Queue *pq, int valor, int prioridade) {
    Celula *novo = inicializa_celula(valor, prioridade);
    if (novo == NULL) {
        printf("Erro ao alocar memória para novo nó.\n");
        exit(1);
    }

    Celula *atual = pq->primeiro;
    Celula *anterior = NULL;

    // Encontra posição correta
    while (atual != NULL && atual->prioridade <= prioridade) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Ajusta ponteiros do novo nó
    novo->proximo = atual;
    novo->anterior = anterior;

    // Ajusta ponteiro do nó seguinte, se houver
    if (atual != NULL) {
        atual->anterior = novo;
    }

    // Ajusta ponteiro do nó anterior, se houver
    if (anterior != NULL) {
        anterior->proximo = novo;
    } else {
        // Novo nó é o primeiro da lista
        pq->primeiro = novo;
    }

    pq->qtde++;
}


void imprimir(Priority_Queue *pq){
	Celula *atual = pq->primeiro;
	while(atual != NULL){
		printf("(%d, %d)", atual->prioridade, atual->valor);
		atual = atual->proximo;
	}
	printf("\n");
}

int buscar(Priority_Queue *pq, int valor){
	Celula *atual = pq->primeiro;
    int i = 1;
	while(atual != NULL && atual->valor != valor){
		atual = atual->proximo;
        i++;
	}
	return i;
}

int desenfileira(Priority_Queue *pq){
	// Verifica se a fila está vazia
	if(pq->primeiro == NULL){
		return -1;	// Código de erro para fila vazia
	} 
	else {
		// Salva o valor do primeiro elemento
		int valor = pq->primeiro->valor;
		Celula *head = pq->primeiro;
		
		// Move head para o próximo elemento
		if(pq->qtde == 1){
			pq->primeiro = NULL;
		}
		else{
			pq->primeiro = pq->primeiro->proximo;
			pq->primeiro->anterior = NULL;
		}
		
		// Atualiza contador e libera memória
		pq->qtde--;
		free(head);
		
		return valor;	// Retorna o valor removido
	}
}


int main(void) {
  	Priority_Queue *pq = inicializa_pq();
	int in[] = {2, 3, 9, 6, 7, 4, 1, 8, 0, 5};
	int out[] = {0, 9, 1, 8, 5, 5, 6, 2, 3, 4, 7};
	int len_in = sizeof(in) / sizeof(int);
	int len_out = sizeof(out) / sizeof(int);
	
    for(int i = 0; i < len_in; i ++){
		infileira(pq, in[i], out[i]);
		imprimir(pq);
	}

	printf("%d\n", desenfileira(pq));
	imprimir(pq);

  return 0;
}
