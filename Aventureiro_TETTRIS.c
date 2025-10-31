#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Para inserir uma peça aleatoria entre as opções


typedef struct {
    char letra[30];
    int id; //o id deve ser nomeado conforme o lugar na fila que ele será inserido
} PECAS;


#define MAX 5


// ---------- FILA
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

PECAS gerarPeca() { //gera peças aleaorias
    char opcoes[] = {'I', 'O', 'T', 'L'};
    int sorteio = rand() % 4;

    PECAS nova;
    nova.letra[0] = opcoes[sorteio];
    nova.letra[1] = '\0';
    nova.id = -1; // o id deve ser nomeado conforme o lugar na fila que ele será inserido;
    return nova;
}


// ----------- PILHA 
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

void push(Pilha *p, PECAS nova){ //INSERIR
    if (pilhaCheia(p)){
        printf("Pilha cheia.\n");
        return;
    }

    p->topo++;
    p->reserva[p->topo] = nova;
}

void pop(Pilha *p, PECAS *removida ) { //REMOVER
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
        printf("[%s, %d]\n", p->reserva[i].letra, p->reserva[i].id);
    } }
    printf("\n");
}
int main () {

    Fila f;
    inicializarFila(&f); //Inicializa a fila do programa
    srand(time(NULL));
    int opcao;
    
    Pilha p;
    inicializarPilha(&p);
    
    for (int i = 0; i < MAX; i++) { //adiciona 5 peças aleatoria na fila ao iniciar o programa
        PECAS nova = gerarPeca();
        inserir(&f, nova);
    }

 
    //MENU
    do {
    

    printf("================= T E T R I S ================\n\n");
    mostrarFila(&f);
    mostrarPilha(&p);
    printf("\n");
   
    printf("1. Jogar peça\n");
    printf("2. Reservar peça da fila\n");
    printf("3. Usar peça reserva\n");
    printf("0. Sair\n");
    printf("Esolha uma opção: ");
    scanf("%d", &opcao);
    getchar();

   


    switch (opcao) {
    
    case 1:{ //remover peça da fila
    PECAS removida; 
    remover (&f, &removida); // Aqui usamos a função de remoção
    printf("Peça removida: %s, %d\n", removida.letra, removida.id);

    mostrarFila(&f); //mostra a fila

    PECAS nova = gerarPeca(); //inserir automaticamente uma nova peça na fila
    inserir (&f, nova);
    printf("Nova peça gerada: [%s, %d]\n", nova.letra, nova.id);


    break; }
    case 2:{ //reservar peça da fila na pila

    if (filaVazia(&f)) {
             printf("Não há peças na fila para reservar.\n");
    }

    PECAS removida;
    remover(&f, &removida); //remover peça da fila
    push(&p, removida); //adicionar peça removida da pilha
    printf("Peça na reserva: [%s, %d]\n", removida.letra, removida.id);

    
     PECAS nova = gerarPeca(); //gerar nova peça na fila
     inserir(&f, nova);
                
    mostrarPilha(&p);
    mostrarFila(&f);

    break;}
        case 3:{ //jogar a peça da reserva da pilha
    if (pilhaVazia(&p)) {
                    printf("Não há peças reservadas.\n"); }

    
        PECAS removida;
        pop(&p, &removida);
        printf("Peça reserva utilizada: [%s, %d]\n", removida.letra, removida.id);

        mostrarPilha(&p);
        mostrarFila(&f);
    }
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

