#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

int varX[] = {1,0,0,-1};
int varY[] = {0,-1,1,0};

typedef int bool;

typedef struct {
    int linhas;
    int colunas;
    int inicioX;
    int fimX;
    int inicioY;
    int fimY;
    char** labirinto;
} LABIRINTO;

bool resolveLabirintoAux(LABIRINTO lab, int x, int y);



void printf123(){
    
}

LABIRINTO criarLabirintoBase(int lin, int col, int iniX, int iniY, int fimX, int fimY){
    int x, y;
    printf("##### Criando labirindo de tamanho %i x %i, com inicio na posicao (%i,%i) e fim na posicao (%i,%i). #####\n", lin, col, iniX, iniY, fimX, fimY);
    LABIRINTO lab;
    lab.linhas = lin;
    lab.colunas = col;
    lab.inicioX = iniX;
    lab.fimX = fimX;
    lab.inicioY = iniY;
    lab.fimY = fimY;
    lab.labirinto = (char**) malloc(sizeof(char*)*lin);
    for (x=0;x<lin;x++)
        lab.labirinto[x] = (char*) malloc(sizeof(char)*col);  
    for (x=0;x<lin;x++)
        for (y=0;y<col;y++)
            lab.labirinto[x][y] = ' ';

    for (x=0;x<lin;x++){
        lab.labirinto[x][0] = '#';
        lab.labirinto[x][col-1] = '#';
    }

    for (y=0;y<col;y++){
        lab.labirinto[0][y] = '#';
        lab.labirinto[lin-1][y] = '#';
    }
    lab.labirinto[lab.inicioX][lab.inicioY] = 'I';
    lab.labirinto[lab.fimX][lab.fimY] = 'F';
    return lab;
}



void gerarParedes(LABIRINTO lab, int paredes){
    int px;
    int py;
    int p;
    for (p=0;p<paredes;p++){
        px = 1+rand() % (lab.linhas-1);
        py = 1+rand() % (lab.colunas-1);
        lab.labirinto[px][py] = '#';
    }
    lab.labirinto[lab.inicioX][lab.inicioY] = 'I';
    lab.labirinto[lab.fimX][lab.fimY] = 'F';
}





void imprimirLabirinto(LABIRINTO lab){
    int x, y;
    printf("Imprimindo o labirinto\n");
    for (x=0;x<lab.linhas;x++){
        for (y=0;y<lab.colunas;y++)
            printf("%c",lab.labirinto[x][y]);
        printf("\n");
    }
    printf("\n");
}


bool resolveLabirintoAux(LABIRINTO lab, int x, int y) {
    for (int a = 0; a < 4; a++) {
        //analisa a próxima posição da posição inicial, e a próxima da próxima.
        //condição de parada: achar o Fim
        if (lab.labirinto[x + varX[a]][y + varY[a]] == 'F'){
          return true;
        } 
        //se a próxima posição for livre, marque-a e chame a função para a próxima dessa casa
        if (lab.labirinto[x + varX[a]][y + varY[a]] == ' ') {
            lab.labirinto[x + varX[a]][y + varY[a]] = '.';
            if (resolveLabirintoAux(lab, x + varX[a], y + varY[a])){
              return true;
            }
            else {
              //se não for possível completar o caminho, volte e tente outro
              lab.labirinto[x + varX[a]][y + varY[a]] = ' ';
            }
        }
    }
    return false;
}

bool resolveLabirinto(LABIRINTO lab) {
    //retorn false a não ser que a condição de true seja ativada na função 
    bool cond = false;
    cond = resolveLabirintoAux(lab,lab.inicioX, lab.inicioY);
    return cond;
}







int main() {
    // Inicializando gerador de numeros pseudo aleatorios
    srand(42);
    LABIRINTO lab1;

    lab1 = criarLabirintoBase(4,4,1,1,2,2);
    printf("Labirinto vazio\n");
    imprimirLabirinto(lab1);
    printf("Gerando paredes aleatoriamente\n");
    gerarParedes(lab1, 1);
    imprimirLabirinto(lab1);
    if (resolveLabirinto(lab1)) printf("Saida encontrada!\n");
    else printf("Saida nao encontrada!\n");
    imprimirLabirinto(lab1);


    lab1 = criarLabirintoBase(5,5,1,1,3,3);
    printf("Labirinto vazio\n");
    imprimirLabirinto(lab1);
    if (resolveLabirinto(lab1)) printf("Saida encontrada!\n");
    else printf("Saida nao encontrada!\n");
    imprimirLabirinto(lab1);



    lab1 = criarLabirintoBase(5,5,3,3,1,1);
    printf("Labirinto vazio\n");
    imprimirLabirinto(lab1);
    if (resolveLabirinto(lab1)) printf("Saida encontrada!\n");
    else printf("Saida nao encontrada!\n");
    imprimirLabirinto(lab1);


    lab1 = criarLabirintoBase(10,20,8,1,8,18);
    printf("Labirinto vazio\n");
    imprimirLabirinto(lab1);
    printf("Gerando paredes aleatoriamente\n");
    gerarParedes(lab1, 60);
    imprimirLabirinto(lab1);
    if (resolveLabirinto(lab1)) printf("Saida encontrada!\n");
    else printf("Saida nao encontrada!\n");
    imprimirLabirinto(lab1);


    lab1 = criarLabirintoBase(4,4,1,1,2,2);
    printf("Labirinto vazio\n");
    imprimirLabirinto(lab1);
    lab1.labirinto[1][2] = '#';
    lab1.labirinto[2][1] = '#';
    imprimirLabirinto(lab1);
    if (resolveLabirinto(lab1)) printf("Saida encontrada!\n");
    else printf("Saida nao encontrada!\n");
    imprimirLabirinto(lab1);


    return 0;
}

