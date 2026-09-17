#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanho 10

typedef struct {
    char* nome;
    char* sobrenome;
    int id;
} Aluno;

typedef struct {
	Aluno* tabela[tamanho];
}EndDireto;

Aluno* criaAluno(char* nome, char* sobrenome, int id){
    Aluno* aluno = malloc(sizeof(Aluno));
    aluno->nome = nome;
    aluno->sobrenome = sobrenome;
    aluno->id = id;
    return aluno;
}

EndDireto* criaTabela(){
    EndDireto* end_direto = malloc(sizeof(EndDireto));
    for(int i = 0; i < tamanho; i++){
        end_direto->tabela[i] = NULL;
    }
    return end_direto;
}

void inserir(EndDireto* end_direto, int chave, Aluno *aluno){
    if(chave >=0 && chave < tamanho){
        if(end_direto->tabela[chave] == NULL){
            end_direto->tabela[chave] = aluno;
        }
        else{
            printf("Erro. Ja existe valor com mesma chave na tabela\n");
        }
    }
    else{
        printf("Erro. Chave inexistente na tabela\n");
    }
}

Aluno* remover(EndDireto* end_direto, int chave){
    if(chave >= 0 && chave < tamanho){
        Aluno *aluno = end_direto->tabela[chave];

        if(aluno != NULL){
            end_direto->tabela[chave] = NULL;
        }
        else{
            printf("Erro. Chave retornou NULL na tabela");
        }

        return aluno;
    }
    else{
        printf("Erro. Chave inexistente na tabela\n");
        return NULL;
    }
}

void imprimir (EndDireto* end_direto){
    printf("--- Tabela de End. Direto ---\n");
    for(int i = 0; i < tamanho; i++){
        printf("chave: %d\n", i);
        Aluno* a = end_direto->tabela[i];
        if(a != NULL)
            printf("aluno: nome - %s | sobrenome - %s | id - %d\n", a->nome, a->sobrenome, a->id);
        else
            printf("NULL\n");
    }
}

void destroi(EndDireto* end_direto){
    for(int i = 0; i < tamanho; i++){
        Aluno* a = end_direto->tabela[i];
        if(a != NULL)
            free(a);
    }
    free(end_direto);
}

int main(void){
    EndDireto* end_direto = criaTabela();
    for(int i = 0; i < tamanho; i++){
        int chave = i;
        Aluno* aluno = criaAluno("Fulano", "da Fei", i);   
        inserir(end_direto, aluno->id, aluno);
    }
   
    imprimir(end_direto);
    
    Aluno* aluno = criaAluno("Fulano", "da Fei", 1); 
    inserir(end_direto, aluno->id, aluno);

    aluno = remover(end_direto, aluno->id);
    if(aluno != NULL)
        printf("Removido: Nome - %s | Sobrenome - %s | id - %d\n", aluno->nome, aluno->sobrenome, aluno->id);

    imprimir(end_direto);

    free(aluno);
    destroi(end_direto);
    
    return 0;
}