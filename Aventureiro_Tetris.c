#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Para inserir uma peça aleatoria entre as opções


typedef struct {
    char letra[30];
    int tipo;
} PECAS;


#define MAX 5

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
    printf("Fila: ");

    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%s, %d] ", f->itens[idx].letra, f->itens[idx].tipo);
    }
    printf("\n");
}

PECAS gerarPeca() { //gera peças aleaorias
    char opcoes[] = {'I', 'O', 'T', 'L'};
    int sorteio = rand() % 4;
    PECAS nova;
    nova.letra[0] = opcoes[sorteio];
    nova.letra[1] = '\0';
    nova.tipo = sorteio;
    return nova;
}

int main () {

    Fila f;
    inicializarFila(&f); //Inicializa a fila do programa
    srand(time(NULL));
    int opcao;
    int contadorTipo = MAX;
    
    for (int i = 0; i < MAX; i++) { //adiciona 5 peças aleatoria na fila ao iniciar o programa
        PECAS nova = gerarPeca();
        inserir(&f, nova);
    }

 
    //MENU
    do {
    printf("============= T E T R I S ============\n\n");
    printf("1. Excluir peça\n");
    printf("2. Inserir nova peça\n");
    printf("0. Sair\n");
    printf("Esolha uma opção: ");
    scanf("%d", &opcao);
    getchar();

   


    switch (opcao) {
    
    case 1: //remover peça
    PECAS removida;
    remover (&f, &removida); // Aqui usamos a função de remoção
    printf("Peça removida: %s, %d\n", removida.letra, removida.tipo);

    mostrarFila(&f); //mostra a fila

    break;
    
    case 2: //inserir peça

    //colocar uma peça aleatoria entre essas opções
    PECAS pecas[4] = {
        {"I", 0}, {"O", 1}, {"T",2}, {"L",3}
    };

    //Sortear uma peça aleatória
    int sorteio = rand() % 4;
    inserir(&f, pecas[sorteio]);
    printf("Peça inserida: %s, %d\n", pecas[sorteio].letra,pecas[sorteio].tipo);
    mostrarFila(&f);
    
    break;

    case 0: 
        printf("Saindo do jogo...\n");
    break;

    default:
        printf("Esolha uma opção válida\n");
        
    break;
    } } while (opcao != 0);
 
return 0;
}