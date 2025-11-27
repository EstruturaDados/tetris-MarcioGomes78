#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 10

// Estrutura para representar uma peça
struct Peca {
    char nome;
    int id;
};

// Estrutura da fila
struct Fila {
    struct Peca pecas[MAX_FILA];
    int frente;
    int tras;
    int tamanho;
};

// Protótipos das funções
void inicializarFila(struct Fila *fila);
int filaVazia(struct Fila *fila);
int filaCheia(struct Fila *fila);
void enqueue(struct Fila *fila, struct Peca peca);
struct Peca dequeue(struct Fila *fila);
void exibirFila(struct Fila *fila);
struct Peca gerarPeca(int proximoId);
void exibirMenu();

int main() {
    struct Fila fila;
    int opcao;
    int proximoId = 0;
    int i;
    
    // Inicializar gerador de números aleatórios
    srand(time(NULL));
    
    // Inicializar a fila
    inicializarFila(&fila);
    
    // Preencher a fila com 5 peças iniciais
    printf("========================================\n");
    printf("       TETRIS STACK - FILA DE PECAS\n");
    printf("========================================\n\n");
    printf("Inicializando fila com 5 pecas...\n\n");
    
    for(i = 0; i < 5; i++) {
        struct Peca novaPeca = gerarPeca(proximoId);
        enqueue(&fila, novaPeca);
        proximoId++;
    }
    
    // Loop principal
    do {
        exibirFila(&fila);
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: // Jogar peça (dequeue)
                if(filaVazia(&fila)) {
                    printf("\n[ERRO] Fila vazia! Nao ha pecas para jogar.\n\n");
                } else {
                    struct Peca pecaJogada = dequeue(&fila);
                    printf("\nPeca jogada: [%c %d]\n\n", pecaJogada.nome, pecaJogada.id);
                }
                break;
                
            case 2: // Inserir nova peça (enqueue)
                if(filaCheia(&fila)) {
                    printf("\n[ERRO] Fila cheia! Nao e possivel adicionar mais pecas.\n\n");
                } else {
                    struct Peca novaPeca = gerarPeca(proximoId);
                    enqueue(&fila, novaPeca);
                    printf("\nNova peca adicionada: [%c %d]\n\n", novaPeca.nome, novaPeca.id);
                    proximoId++;
                }
                break;
                
            case 0: // Sair
                printf("\nEncerrando o programa...\n");
                break;
                
            default:
                printf("\n[ERRO] Opcao invalida! Tente novamente.\n\n");
        }
        
    } while(opcao != 0);
    
    return 0;
}

void inicializarFila(struct Fila *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;
}

int filaVazia(struct Fila *fila) {
    return fila->tamanho == 0;
}

int filaCheia(struct Fila *fila) {
    return fila->tamanho == MAX_FILA;
}

void enqueue(struct Fila *fila, struct Peca peca) {
    if(filaCheia(fila)) {
        printf("[ERRO] Fila cheia!\n");
        return;
    }
    
    fila->tras = (fila->tras + 1) % MAX_FILA;
    fila->pecas[fila->tras] = peca;
    fila->tamanho++;
}

struct Peca dequeue(struct Fila *fila) {
    struct Peca pecaRemovida;
    
    if(filaVazia(fila)) {
        printf("[ERRO] Fila vazia!\n");
        pecaRemovida.nome = '?';
        pecaRemovida.id = -1;
        return pecaRemovida;
    }
    
    pecaRemovida = fila->pecas[fila->frente];
    fila->frente = (fila->frente + 1) % MAX_FILA;
    fila->tamanho--;
    
    return pecaRemovida;
}

void exibirFila(struct Fila *fila) {
    int i, indice;
    
    printf("========================================\n");
    printf("         FILA DE PECAS\n");
    printf("========================================\n");
    
    if(filaVazia(fila)) {
        printf("Fila vazia!\n");
    } else {
        for(i = 0; i < fila->tamanho; i++) {
            indice = (fila->frente + i) % MAX_FILA;
            printf("[%c %d] ", fila->pecas[indice].nome, fila->pecas[indice].id);
        }
        printf("\n");
    }
    
    printf("========================================\n");
    printf("Pecas na fila: %d/%d\n", fila->tamanho, MAX_FILA);
    printf("========================================\n\n");
}

struct Peca gerarPeca(int proximoId) {
    struct Peca peca;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indiceAleatorio = rand() % 4;
    
    peca.nome = tipos[indiceAleatorio];
    peca.id = proximoId;
    
    return peca;
}

void exibirMenu() {
    printf("ACOES:\n");
    printf("1 - Jogar peca (dequeue)\n");
    printf("2 - Inserir nova peca (enqueue)\n");
    printf("0 - Sair\n");
    printf("----------------------------------------\n");
}
