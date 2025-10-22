#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// === Estrutura que representa uma peça ===
typedef struct {
    char nome; // Tipo da peça ('I', 'O', 'T', 'L')
    int id;    // ID único
} Peca;

// === Variáveis globais ===
Peca fila[TAM_FILA];
int frente = 0, tras = 0, totalFila = 0;

Peca pilha[TAM_PILHA];
int topo = -1;

int contadorID = 0; // Controla ID único de cada peça

// === Gera uma nova peça aleatória ===
Peca gerarPeca() {
    char tipos[] = { 'I', 'O', 'T', 'L' };
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = contadorID++;
    return p;
}

// === Fila ===
int filaCheia() { return totalFila == TAM_FILA; }
int filaVazia() { return totalFila == 0; }

void enfileirar(Peca p) {
    if (!filaCheia()) {
        fila[tras] = p;
        tras = (tras + 1) % TAM_FILA;
        totalFila++;
    }
}

Peca desenfileirar() {
    Peca p = { '-', -1 };
    if (!filaVazia()) {
        p = fila[frente];
        frente = (frente + 1) % TAM_FILA;
        totalFila--;
    }
    return p;
}

// === Pilha ===
int pilhaCheia() { return topo == TAM_PILHA - 1; }
int pilhaVazia() { return topo == -1; }

void empilhar(Peca p) {
    if (!pilhaCheia()) {
        pilha[++topo] = p;
    }
}

Peca desempilhar() {
    Peca p = { '-', -1 };
    if (!pilhaVazia()) {
        p = pilha[topo--];
    }
    return p;
}

// === Mostra o estado atual da fila e da pilha ===
void mostrarEstado() {
    printf("\n--- Estado Atual ---\n");
    printf("Fila de peças:    ");
    int i = frente;
    for (int c = 0; c < totalFila; c++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");

    printf("Pilha de reserva (Topo -> Base): ");
    for (int j = topo; j >= 0; j--) {
        printf("[%c %d] ", pilha[j].nome, pilha[j].id);
    }
    printf("\n");
}

// === Menu de opções ===
void menu() {
    printf("\n--- Menu de Ações ---\n");
    printf("1 - Jogar peça da frente da fila\n");
    printf("2 - Reservar peça (fila -> pilha)\n");
    printf("3 - Usar peça da pilha\n");
    printf("4 - Trocar peça da fila com topo da pilha\n");
    printf("5 - Troca múltipla (3 da fila <-> 3 da pilha)\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

// === Inicializa a fila com 5 peças ===
void inicializarFila() {
    while (!filaCheia()) {
        enfileirar(gerarPeca());
    }
}

// === Trocar frente da fila com topo da pilha ===
void trocarFrentePilha() {
    if (!filaVazia() && !pilhaVazia()) {
        int idx = frente;
        Peca temp = fila[idx];
        fila[idx] = pilha[topo];
        pilha[topo] = temp;
        printf("Troca realizada entre frente da fila e topo da pilha.\n");
    } else {
        printf("Impossível realizar a troca (estrutura vazia).\n");
    }
}

// === Troca múltipla de 3 peças ===
void trocaMultipla() {
    if (totalFila >= 3 && topo >= 2) {
        int idx = frente;
        for (int i = 0; i < 3; i++) {
            Peca temp = fila[idx];
            fila[idx] = pilha[topo - i];
            pilha[topo - i] = temp;
            idx = (idx + 1) % TAM_FILA;
        }
        printf("Troca múltipla realizada com sucesso.\n");
    } else {
        printf("Troca múltipla não permitida. Verifique se há 3 peças em cada estrutura.\n");
    }
}

// === Função principal ===
int main() {
    srand(time(NULL));
    int opcao;

    inicializarFila();

    do {
        mostrarEstado();
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                if (!filaVazia()) {
                    Peca p = desenfileirar();
                    printf("Peça [%c %d] jogada da fila.\n", p.nome, p.id);
                    enfileirar(gerarPeca()); // Mantém a fila cheia
                } else {
                    printf("Fila vazia. Não há peças para jogar.\n");
                }
                break;
            }
            case 2: {
                if (!filaVazia() && !pilhaCheia()) {
                    Peca p = desenfileirar();
                    empilhar(p);
                    printf("Peça [%c %d] reservada na pilha.\n", p.nome, p.id);
                    enfileirar(gerarPeca());
                } else {
                    printf("Não foi possível reservar (fila vazia ou pilha cheia).\n");
                }
                break;
            }
            case 3: {
                if (!pilhaVazia()) {
                    Peca p = desempilhar();
                    printf("Peça [%c %d] da pilha foi usada.\n", p.nome, p.id);
                } else {
                    printf("Pilha vazia. Nenhuma peça para usar.\n");
                }
                break;
            }
            case 4:
                trocarFrentePilha();
                break;
            case 5:
                trocaMultipla();
                break;
            case 0:
                printf("Encerrando o programa. Até logo!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

