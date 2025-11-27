#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

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

// Estrutura da pilha
struct Pilha {
    struct Peca pecas[MAX_PILHA];
    int topo;
};

// Protótipos das funções - Fila
void inicializarFila(struct Fila *fila);
int filaVazia(struct Fila *fila);
int filaCheia(struct Fila *fila);
void enqueue(struct Fila *fila, struct Peca peca);
struct Peca dequeue(struct Fila *fila);

// Protótipos das funções - Pilha
void inicializarPilha(struct Pilha *pilha);
int pilhaVazia(struct Pilha *pilha);
int pilhaCheia(struct Pilha *pilha);
void push(struct Pilha *pilha, struct Peca peca);
struct Peca pop(struct Pilha *pilha);

// Protótipos das funções - Exibição e controle
void exibirEstado(struct Fila *fila, struct Pilha *pilha);
struct Peca gerarPeca(int proximoId);
void exibirMenu();
void trocarPecaAtual(struct Fila *fila, struct Pilha *pilha);
void trocaMultipla(struct Fila *fila, struct Pilha *pilha);

int main() {
    struct Fila fila;
    struct Pilha pilha;
    int opcao;
    int proximoId = 0;
    int i;
    
    // Inicializar gerador de números aleatórios
    srand(time(NULL));
    
    // Inicializar a fila e a pilha
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    
    // Preencher a fila com 5 peças iniciais
    printf("========================================\n");
    printf("  TETRIS STACK - FILA E PILHA DE PECAS\n");
    printf("========================================\n\n");
    printf("Inicializando fila com 5 pecas...\n\n");
    
    for(i = 0; i < 5; i++) {
        struct Peca novaPeca = gerarPeca(proximoId);
        enqueue(&fila, novaPeca);
        proximoId++;
    }
    
    // Loop principal
    do {
        exibirEstado(&fila, &pilha);
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: // Jogar peça (dequeue)
                if(filaVazia(&fila)) {
                    printf("\n[ERRO] Fila vazia! Nao ha pecas para jogar.\n\n");
                } else {
                    struct Peca pecaJogada = dequeue(&fila);
                    printf("\nPeca jogada: [%c %d]\n", pecaJogada.nome, pecaJogada.id);
                    
                    // Adicionar nova peça automaticamente
                    struct Peca novaPeca = gerarPeca(proximoId);
                    enqueue(&fila, novaPeca);
                    printf("Nova peca adicionada a fila: [%c %d]\n\n", novaPeca.nome, novaPeca.id);
                    proximoId++;
                }
                break;
                
            case 2: // Reservar peça (move da fila para a pilha)
                if(filaVazia(&fila)) {
                    printf("\n[ERRO] Fila vazia! Nao ha pecas para reservar.\n\n");
                } else if(pilhaCheia(&pilha)) {
                    printf("\n[ERRO] Pilha de reserva cheia! Use uma peca reservada primeiro.\n\n");
                } else {
                    struct Peca pecaReservada = dequeue(&fila);
                    push(&pilha, pecaReservada);
                    printf("\nPeca reservada: [%c %d]\n", pecaReservada.nome, pecaReservada.id);
                    
                    // Adicionar nova peça automaticamente
                    struct Peca novaPeca = gerarPeca(proximoId);
                    enqueue(&fila, novaPeca);
                    printf("Nova peca adicionada a fila: [%c %d]\n\n", novaPeca.nome, novaPeca.id);
                    proximoId++;
                }
                break;
                
            case 3: // Usar peça reservada (pop da pilha)
                if(pilhaVazia(&pilha)) {
                    printf("\n[ERRO] Pilha de reserva vazia! Nao ha pecas reservadas.\n\n");
                } else {
                    struct Peca pecaUsada = pop(&pilha);
                    printf("\nPeca reservada usada: [%c %d]\n\n", pecaUsada.nome, pecaUsada.id);
                }
                break;
                
            case 4: // Trocar peça atual (frente da fila com topo da pilha)
                trocarPecaAtual(&fila, &pilha);
                break;
                
            case 5: // Troca múltipla (3 peças da fila com 3 da pilha)
                trocaMultipla(&fila, &pilha);
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

void inicializarPilha(struct Pilha *pilha) {
    pilha->topo = -1;
}

int pilhaVazia(struct Pilha *pilha) {
    return pilha->topo == -1;
}

int pilhaCheia(struct Pilha *pilha) {
    return pilha->topo == MAX_PILHA - 1;
}

void push(struct Pilha *pilha, struct Peca peca) {
    if(pilhaCheia(pilha)) {
        printf("[ERRO] Pilha cheia!\n");
        return;
    }
    
    pilha->topo++;
    pilha->pecas[pilha->topo] = peca;
}

struct Peca pop(struct Pilha *pilha) {
    struct Peca pecaRemovida;
    
    if(pilhaVazia(pilha)) {
        printf("[ERRO] Pilha vazia!\n");
        pecaRemovida.nome = '?';
        pecaRemovida.id = -1;
        return pecaRemovida;
    }
    
    pecaRemovida = pilha->pecas[pilha->topo];
    pilha->topo--;
    
    return pecaRemovida;
}

void exibirEstado(struct Fila *fila, struct Pilha *pilha) {
    int i, indice;
    
    printf("========================================\n");
    printf("         ESTADO ATUAL\n");
    printf("========================================\n");
    
    // Exibir fila
    printf("Fila de pecas:\n");
    if(filaVazia(fila)) {
        printf("  (Vazia)\n");
    } else {
        printf("  ");
        for(i = 0; i < fila->tamanho; i++) {
            indice = (fila->frente + i) % MAX_FILA;
            printf("[%c %d] ", fila->pecas[indice].nome, fila->pecas[indice].id);
        }
        printf("\n");
    }
    printf("  Pecas: %d/%d\n\n", fila->tamanho, MAX_FILA);
    
    // Exibir pilha
    printf("Pilha de reserva (Topo -> Base):\n");
    if(pilhaVazia(pilha)) {
        printf("  (Vazia)\n");
    } else {
        printf("  ");
        for(i = pilha->topo; i >= 0; i--) {
            printf("[%c %d] ", pilha->pecas[i].nome, pilha->pecas[i].id);
        }
        printf("\n");
    }
    printf("  Pecas: %d/%d\n", pilha->topo + 1, MAX_PILHA);
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
    printf("1 - Jogar peca da frente da fila\n");
    printf("2 - Enviar peca da fila para a pilha de reserva\n");
    printf("3 - Usar peca da pilha de reserva\n");
    printf("4 - Trocar peca da frente da fila com o topo da pilha\n");
    printf("5 - Trocar os 3 primeiros da fila com as 3 pecas da pilha\n");
    printf("0 - Sair\n");
    printf("----------------------------------------\n");
}

void trocarPecaAtual(struct Fila *fila, struct Pilha *pilha) {
    if(filaVazia(fila)) {
        printf("\n[ERRO] Fila vazia! Nao ha peca para trocar.\n\n");
        return;
    }
    
    if(pilhaVazia(pilha)) {
        printf("\n[ERRO] Pilha vazia! Nao ha peca para trocar.\n\n");
        return;
    }
    
    // Remover peça da frente da fila
    struct Peca pecaFila = dequeue(fila);
    
    // Remover peça do topo da pilha
    struct Peca pecaPilha = pop(pilha);
    
    // Inserir peça da pilha na frente da fila (reposicionar)
    // Como não temos operação para inserir na frente, fazemos um truque:
    // Salvamos todas as peças, inserimos a nova na frente e recolocamos as outras
    struct Peca temp[MAX_FILA];
    int tamanhoOriginal = fila->tamanho;
    int i;
    
    // Guardar todas as peças da fila
    for(i = 0; i < tamanhoOriginal; i++) {
        temp[i] = dequeue(fila);
    }
    
    // Inserir a peça da pilha primeiro
    enqueue(fila, pecaPilha);
    
    // Reinserir as peças originais
    for(i = 0; i < tamanhoOriginal; i++) {
        enqueue(fila, temp[i]);
    }
    
    // Inserir peça da fila na pilha
    push(pilha, pecaFila);
    
    printf("\nTroca realizada!\n");
    printf("Peca [%c %d] da fila foi para a pilha\n", pecaFila.nome, pecaFila.id);
    printf("Peca [%c %d] da pilha foi para a frente da fila\n\n", pecaPilha.nome, pecaPilha.id);
}

void trocaMultipla(struct Fila *fila, struct Pilha *pilha) {
    if(fila->tamanho < 3) {
        printf("\n[ERRO] A fila precisa ter pelo menos 3 pecas! Atual: %d\n\n", fila->tamanho);
        return;
    }
    
    if(pilha->topo + 1 < 3) {
        printf("\n[ERRO] A pilha precisa ter 3 pecas! Atual: %d\n\n", pilha->topo + 1);
        return;
    }
    
    struct Peca filaTemp[3];
    struct Peca pilhaTemp[3];
    struct Peca restoFila[MAX_FILA];
    int restoTamanho = fila->tamanho - 3;
    int i;
    
    printf("\nRealizando troca multipla...\n");
    
    // Guardar as 3 primeiras peças da fila
    for(i = 0; i < 3; i++) {
        filaTemp[i] = dequeue(fila);
        printf("Removido da fila: [%c %d]\n", filaTemp[i].nome, filaTemp[i].id);
    }
    
    // Guardar o resto da fila
    for(i = 0; i < restoTamanho; i++) {
        restoFila[i] = dequeue(fila);
    }
    
    // Guardar as 3 peças da pilha (do topo para a base)
    for(i = 0; i < 3; i++) {
        pilhaTemp[i] = pop(pilha);
        printf("Removido da pilha: [%c %d]\n", pilhaTemp[i].nome, pilhaTemp[i].id);
    }
    
    printf("\n--- Realizando a troca ---\n");
    
    // Colocar as peças da pilha na frente da fila (na ordem inversa para manter a lógica)
    for(i = 2; i >= 0; i--) {
        enqueue(fila, pilhaTemp[i]);
        printf("Inserido na fila: [%c %d]\n", pilhaTemp[i].nome, pilhaTemp[i].id);
    }
    
    // Recolocar o resto das peças da fila
    for(i = 0; i < restoTamanho; i++) {
        enqueue(fila, restoFila[i]);
    }
    
    // Colocar as peças da fila na pilha (na ordem inversa para manter LIFO)
    for(i = 2; i >= 0; i--) {
        push(pilha, filaTemp[i]);
        printf("Inserido na pilha: [%c %d]\n", filaTemp[i].nome, filaTemp[i].id);
    }
    
    printf("\nTroca multipla concluida com sucesso!\n\n");
}
