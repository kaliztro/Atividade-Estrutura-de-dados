/*
05/05/2023 01:52
Nome: Guilherme Magalhães Lopes
Matricula: 202213147
curso: ADS
Instituição: Unilasalle
*/


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
char nome[20];
float nota;
int turma;
} Aluno;

struct Nodo {
    Aluno dado; //variavel Aluno armazena os dados do aluno, como nome, nota e turma
    struct Nodo *ant; //aponta para o endereco do elemento anterior
    struct Nodo *prox; //aponta o endereco do proximo elemento
};
typedef struct Nodo nodo;

struct Descritor{
    int n; //armazena a quantidade de elementos da lista
    struct Nodo *prim; //armazena o endereco de memoria do primeiro elemento da lista
    struct Nodo *ult; //armazena o endereco de memoria do ultimo elemento da lista
};
typedef struct Descritor descritor;

// inicializando a lista
void iniciar (nodo *L, descritor *D) {
    L->ant= NULL;
    L->prox= NULL;

    D->n= 0;
    D->prim = NULL;
    D->ult= NULL;
}

//verificando se a lista está vazia
int estVazia (descritor *D) {
    if (D->n == 0)
        return 1;
    else
        return 0;
}

// acessando o primeiro elemnto
Aluno primeiroElemento(descritor *D) {
    nodo *no= D->prim;
    return no->dado;
}

//acessando o ultimo elemnto
Aluno ultimoElemento(descritor *D) {
    nodo *no= D->ult;
    return no->dado;
}

//incluir no inicio
void inserirInicio(nodo *L, descritor *D, Aluno *dado) {
    nodo *novo= (nodo *) malloc(sizeof(nodo));

    strcpy(novo->dado.nome, dado->nome);
    novo->dado.turma= dado->turma;
    novo->dado.nota= dado->nota;

    if (estVazia (D)) {
        L->prox= novo;
        novo->prox= NULL;
        D->ult= novo;
    } else {
        nodo *primeiro= L->prox;
        L->prox= novo;
        novo->prox= primeiro;
        primeiro->ant= novo;
    }
    D->n++;
    D->prim= novo;
    novo->ant= NULL;
}

//inserir no final
void inserirFinal(nodo *L, descritor *D, Aluno *dado) {
    nodo *novo= (nodo *) malloc(sizeof(nodo));

    strcpy(novo->dado.nome, dado->nome);
    novo->dado.turma= dado->turma;
    novo->dado.nota= dado->nota;

    if (estVazia (D)) {
        L->prox= novo;

        novo->ant= NULL;
        D->prim= novo;
    } else {
        nodo *no= D->ult;
        novo->ant= no;
        no->prox= novo;
    }
    novo->prox= NULL;
    D->ult= novo;
    D->n++;
}

//incluir elemento no meio da lista
void inserirMeio(nodo *L, descritor *D, Aluno *dado) {
    nodo *novo= (nodo *) malloc(sizeof(nodo));
    strcpy(novo->dado.nome, dado->nome);
    novo->dado.turma= dado->turma;
    novo->dado.nota= dado->nota;

    if (estVazia(D)) { // se a lista estiver vazia, insere no início
        inserirInicio(L, D, dado);
        return;
    }

    nodo *no = L->prox;
    while (no != NULL && no->dado.nota < dado->nota) { // procura o nó onde o aluno deve ser inserido
        no = no->prox;
    }

    if (no == NULL) { // se não encontrou o nó, insere no final
        inserirFinal(L, D, dado);
        return;
    }

    // insere o novo nó antes do nó encontrado
    novo->ant = no->ant;
    novo->prox = no;
    no->ant = novo;
    if (novo->ant == NULL) { // se o novo nó for o primeiro da lista
        L->prox = novo;
    } else {
        novo->ant->prox = novo;
    }
    D->n++;
}


//exluir primeiro elemento da lista
void exluirInicio(nodo *L, descritor *D) {
    nodo *primeiro= L->prox;
    nodo *segundo= primeiro->prox;
    L->prox= segundo;
    segundo->ant= NULL;
    D->prim= segundo;
    D->n--;
    free(primeiro);
}

//excluir ultimo elemento da lista
void excluirFinal(nodo *L, descritor *D) {
    nodo *ultimo= D->ult;
    nodo *penultimo= ultimo->ant;
    penultimo->prox= NULL;
    D->ult= penultimo;
    D->n--;
    free(ultimo);
}

//excluir elemento no meio da lista
void excluirMeio(nodo *L, descritor *D, int posicao) {
    if (posicao < 1 || posicao > D->n) { // verifica se a posição é válida
        printf("Posição inválida!\n");
        return;
    }

    nodo *no = L->prox;
    int i = 1;
    while (no != NULL && i < posicao) { // percorre a lista até a posição desejada
        no = no->prox;
        i++;
    }

    if (no == NULL) { // se não encontrou o nó, a posição é inválida
        printf("Posição inválida!\n");
        return;
    }

    if (no->ant == NULL) { // se o nó a ser excluído é o primeiro da lista
        L->prox = no->prox;
        no->prox->ant = NULL;
        D->prim = no->prox;
    } else if (no->prox == NULL) { // se o nó a ser excluído é o último da lista
        no->ant->prox = NULL;
        D->ult = no->ant;
    } else { // se o nó a ser excluído está no meio da lista
        no->ant->prox = no->prox;
        no->prox->ant = no->ant;
    }

    D->n--;
    free(no);
}


//exluir toda a lista
void liberar(nodo *L, descritor *D) {
    if (!estVazia (D)) {
        nodo *proxNodo, *atual;
        atual= L->prox;
        while(atual !=NULL) {
            proxNodo= atual->prox;
            free(atual);
            atual= proxNodo;
            D->n--;
        }
    }
}

//imprimir toda a lista
void imprimir(nodo *L, descritor *D, char ordem) {
    if(estVazia (D)) {
        printf("A lista esta vazia!\n\n");
        return;
    }

    if(ordem == 'i') { //imprimi da esquerda para a direita
        nodo *no= L->prox;
        printf("%-10s %-6s %-5s \n", "Nome", "Nota", "Turma");
        while(no != NULL) {
            printf("%-10s %-6.1f %-4d \n", no->dado.nome, 
                no->dado.nota, no->dado.turma);
            no= no->prox;
        }
    } else if (ordem == 'f') { // imprimi do direita para a esquerda
          nodo *no= D->ult;
          printf("%-10s %-6s %-5s \n", "Nome", "Nota", "Turma");
          while(no !=NULL) {
            printf("%-10s %-6.1f %-4d \n", no->dado.nome,
                    no->dado.nota, no->dado.turma);
                    no= no->ant;
          }
    }
    printf("\n\n");
}


int main() {

    nodo lista;
    descritor desc;

    iniciar(&lista, &desc);

    int opcao;
    char nome[20];
    float nota;
    int turma, posicao;
    
    do {
        printf("Digite a opcao desejada:\n\n\t0 - sair\n\t1 - Inserir no inicio\n\t2 - inserir no final\n\t3 - Inserir no meio\n\t4 - imprimir Direita\n\t5 - imprimir Esquerda\n\t6 - Excluir Primeiro elemento\n\t7 - Excluir ultimo elemento\n\t8 - Excluir toda lista\n\t9 - Excluir no meio\n\n");        
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 0:
                printf("Saindo do programa...\n");
                break;
            case 1:
                printf("Digite o nome do aluno:\n");
                scanf("%s", nome);
                printf("Digite a nota do aluno:\n");
                scanf("%f", &nota);
                printf("Digite a turma do aluno:\n");
                scanf("%d", &turma);
            
                Aluno dados;
                dados.nota = nota;
                dados.turma = turma;
                strcpy(dados.nome, nome);

                inserirInicio(&lista, &desc, &dados);
                break;
            case 2:
                printf("Digite o nome do aluno:\n");
                scanf("%s", nome);
                printf("Digite a nota do aluno:\n");
                scanf("%f", &nota);
                printf("Digite a turma do aluno:\n");
                scanf("%d", &turma);
            
                Aluno dados1;
                dados1.nota = nota;
                dados1.turma = turma;
                strcpy(dados1.nome, nome);

                inserirFinal(&lista, &desc, &dados1);
                break;
            case 3:
                printf("Digite o nome do aluno:\n");
                scanf("%s", nome);
                printf("Digite a nota do aluno:\n");
                scanf("%f", &nota);
                printf("Digite a turma do aluno:\n");
                scanf("%d", &turma);

                Aluno dados2;
                dados2.nota = nota;
                dados2.turma = turma;
                strcpy(dados2.nome, nome);

                inserirMeio(&lista, &desc, &dados2);
                break;
            case 4:
                imprimir(&lista, &desc, 'i');
                break;
            case 5:
                imprimir(&lista, &desc, 'f');
                break;
            case 6:
                exluirInicio(&lista, &desc);
                break;
            case 7:
                excluirFinal(&lista, &desc);
                break;
            case 8:
                liberar(&lista, &desc);
                break;
            case 9:
                printf("Qual a posicao do aluno que deseja remover?\n");
                scanf("%d", &posicao);
                excluirMeio(&lista, &desc, posicao);
                break;
            default:
                printf("Opcao invalida, tente novamente.\n");
                break;
        }
    } while(opcao != 0);
    
    return 0;
}

