#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char letra[30];
    int id; // o id é o índice da posição na fila
} PECAS;

#define MAX 5

// ---------- FILA ----------
typedef struct {
    PECAS itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

void inicializarFila(Fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(Fila *f) {
    return f->total == MAX;
}

int filaVazia(Fila *f){
    return f->total == 0;
}

void inserir(Fila *f, PECAS p) {
    if (filaCheia(f)){
        printf("Fila Cheia\n");
        return;
    }
    p.id = f->fim;
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

void remover(Fila *f, PECAS *p){
    if (filaVazia(f)){
        printf("Fila já vazia\n");
        return;
    }
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

void mostrarFila(Fila *f){
    if (filaVazia(f)){
        printf("Fila vazia\n");
        return;
    }

    printf("Fila: ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%s, %d] ", f->itens[idx].letra, f->itens[idx].id);
    }
    printf("\n");
}

PECAS gerarPeca() {
    char opcoes[] = {'I', 'O', 'T', 'L'};
    int sorteio = rand() % 4;

    PECAS nova;
    nova.letra[0] = opcoes[sorteio];
    nova.letra[1] = '\0';
    nova.id = -1;
    return nova;
}

// ----------- PILHA ----------
typedef struct {
    PECAS reserva[MAX];
    int topo;
} Pilha;

void inicializarPilha(Pilha *p){
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX -1;
}

void push(Pilha *p, PECAS nova){
    if (pilhaCheia(p)){
        printf("Pilha cheia.\n");
        return;
    }
    p->topo++;
    p->reserva[p->topo] = nova;
}

void pop(Pilha *p, PECAS *removida) {
    if(pilhaVazia(p)){
        printf("Pilha Vazia.\n");
        return;
    }
    *removida = p->reserva[p->topo];
    p->topo--;
}

void mostrarPilha(Pilha *p){
    printf("Pilha (topo -> base): ");
    if (pilhaVazia(p)) {
        printf("Vazia");
    } else {
        for (int i = p->topo; i >= 0; i--){
            printf("[%s, %d] ", p->reserva[i].letra, p->reserva[i].id);
        }
    }
    printf("\n");
}

// ----------- MAIN ----------
int main () {

    srand(time(NULL));

    Fila f, filaInvertida;
    Pilha p, auxiliar, historico;

    inicializarFila(&f);
    inicializarFila(&filaInvertida);
    inicializarPilha(&p);
    inicializarPilha(&auxiliar);
    inicializarPilha(&historico); // guarda jogadas removidas (para desfazer)

    // Fila inicial
    for (int i = 0; i < MAX; i++) {
        PECAS nova = gerarPeca();
        inserir(&f, nova);
    }

    int opcao;
    do {
        printf("\n================= T E T R I S ================\n");
        mostrarFila(&f);
        mostrarPilha(&p);
        printf("\n1. Jogar peça\n");
        printf("2. Reservar peça da fila\n");
        printf("3. Usar peça reserva\n");
        printf("4. Trocar peça da pilha para a fila\n");
        printf("5. Desfazer Última Jogada\n");
        printf("6. Inverter Fila\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {

        case 1: { // Jogar peça
            PECAS removida;
            remover(&f, &removida);
            push(&historico, removida); // guarda no histórico
            printf("Peça jogada: [%s, %d]\n", removida.letra, removida.id);
            inserir(&f, gerarPeca());
            break;
        }

        case 2: { // Reservar peça
            if (filaVazia(&f)) {
                printf("Fila vazia.\n");
                break;
            }
            PECAS removida;
            remover(&f, &removida);
            push(&p, removida);
            printf("Peça reservada: [%s, %d]\n", removida.letra, removida.id);
            inserir(&f, gerarPeca());
            break;
        }

        case 3: { // Usar peça reserva
            if (pilhaVazia(&p)) {
                printf("Sem peças reservadas.\n");
                break;
            }
            PECAS usada;
            pop(&p, &usada);
            printf("Peça reserva usada: [%s, %d]\n", usada.letra, usada.id);
            push(&historico, usada);
            break;
        }

        case 4: { // Trocar peça da pilha para a fila
            if (pilhaVazia(&p)) {
                printf("Pilha vazia.\n");
                break;
            }
            PECAS trocada;
            pop(&p, &trocada);
            inserir(&f, trocada);
            printf("Peça [%s, %d] movida da pilha para o fim da fila.\n", trocada.letra, trocada.id);
            break;
        }

        case 5: { // Desfazer última jogada
            if (pilhaVazia(&historico)) {
                printf("Nenhuma jogada para desfazer.\n");
                break;
            }
            PECAS ultima;
            pop(&historico, &ultima);
            inserir(&f, ultima);
            printf("Desfeita jogada: [%s, %d] retornou à fila.\n", ultima.letra, ultima.id);
            break;
        }

        case 6: { // Inverter fila
            inicializarPilha(&auxiliar);
            inicializarFila(&filaInvertida);

            // move fila → pilha
            while (!filaVazia(&f)) {
                PECAS temp;
                remover(&f, &temp);
                push(&auxiliar, temp);
            }
            // move pilha → nova fila
            while (!pilhaVazia(&auxiliar)) {
                PECAS temp;
                pop(&auxiliar, &temp);
                inserir(&filaInvertida, temp);
            }

            f = filaInvertida; // substitui
            printf("Fila invertida com sucesso!\n");
            break;
        }

        case 0:
            printf("Saindo do jogo...\n");
            break;

        default:
            printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
