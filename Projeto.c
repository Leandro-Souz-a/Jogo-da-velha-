/*  Projeto de CAP
    Leandro Souza Silva - 759079
    09/07/2025
    
    Objetivo: criar o Jogo da Velha ao Quadrado.*/

#include <stdio.h>
#include <string.h>            
#include <stdlib.h>

//Variáveis globais
char entrada[160];

//Registros
typedef struct{

    int linha;
    int coluna;
    char seletor_quadrante;

}quadrante;

// Protótipos
void cria(char t[9][9]);
void imprime(char t[9][9]);
void faz_jogada(char t[9][9], int *opcao, int *jogador, quadrante *q);
void posiciona_peca(char t[9][9], char seletor_jogada, quadrante *q, int *jogador);
void realoca_peca(char t[9][9], char seletor_jogada, quadrante *q, int *jogador);
void seleciona_quadrante_principal(quadrante *q);
void verifica_vencedor(char t[9][9], quadrante *q, int *jogador, int *opcao);

int main(){

    char tabuleiro[9][9];
    int i, j;
    int opcao = 0;
    int jogador = 0; // 0 para 'O' e 1 para 'X'
    quadrante quadrante_principal;

    // Início do jogo

    printf("Bem vindo ao (JOGO DA VELHA)²!\n");
    printf("\n");
    printf("REGRAS DO JOGO\n");
    printf("\n");
    printf("1. O jogo é jogado em um tabuleiro 9x9, dividido em 9 quadrantes 3x3.\n");
    printf("2. Por convenção, o jogo se inicia no quadrante do meio pelo jogador 'O'.\n");
    printf("3. Cada jogador joga alternadamente, posicionando ou realocando peças.\n");
    printf("4. O objetivo é vencer o jogo da velha ao quadrado, marcando uma sequência de quadrantes, assim como no jogo tradicional.\n");
    printf("\n");
    printf("Pressione ENTER para iniciar o jogo...\n");
    fgets(entrada, sizeof(entrada), stdin);


    quadrante_principal.seletor_quadrante = '5'; // A primeira jogada é sempre no quadrante 5
    quadrante_principal.linha = 3; // Inicializa a linha para o quadrante 5
    quadrante_principal.coluna = 3; // Inicializa a coluna para o quadrante 5


    cria(tabuleiro);
    do{

        imprime(tabuleiro);
        faz_jogada(tabuleiro, &opcao, &jogador, &quadrante_principal);
        verifica_vencedor(tabuleiro, &quadrante_principal, &jogador, &opcao);

    }while (opcao != 0);

    return 0;
}

// Implementações
void cria(char t[9][9]){
    
    // Objetivo: Cria o tabuleiro do jogo da velha ao quadrado.
    // Entrada: Nenhuma.
    // Saída: O tabuleiro ao quadrado preenchido com números de 1 a 9.

    int i, j;
    char k = '1';
    
    for (i=0; i<9; i++){
        for(j=0; j<9; j++){
            t[i][j] = k;
            k++;

            if (k == '4' && (j == 2 || j == 5)) {
                k = '1'; // Reinicia o contador em cada coluna
            }
            if (k == '7' && (j == 2 || j == 5)) {
                k = '4'; // Reinicia o contador em cada coluna
            }
            if (k == ':' ) {
                k = '7'; // Reinicia o contador em cada coluna
            }
        }
        if ((i == 2 || i == 5)) {
            k = '1'; // Reinicia o contador em cada jogo da velha
        }
    }
}

void imprime(char t[9][9]){
    
    // Objetivo: Imprime o tabuleiro do jogo da velha ao quadrado.
    // Entrada: Nenhuma.
    // Saída: Imprime na tela o tabuleiro atualizado após cada jogada.

    int i;
    char k = '1';
    
    printf("               |               |               \n");
    for (i=0; i<9; i++){
        printf("   %c | %c | %c   |   %c | %c | %c   |   %c | %c | %c  \n", 
            
        t[i][0], t[i][1], t[i][2], t[i][3], t[i][4], t[i][5], t[i][6], t[i][7], t[i][8]);
        
        if (i != 2 && i != 5 && i < 8)
            printf("  ---|---|---  |  ---|---|---  |  ---|---|---  \n");
        if (i == 2 || i == 5) {
            printf("             %c |             %c |             %c \n", k, k + 1, k + 2);
            printf("---------------|---------------|---------------\n");
            printf("               |               |               \n");
            k+= 3; 
        }
    }
    k = '7';   
    printf("             %c |             %c |             %c \n", k, k + 1, k + 2);
}

void faz_jogada(char t[9][9], int *opcao, int *jogador, quadrante *q){

    // Objetivo: Permite que o jogador escolha a ação a ser realizada (posicionar ou realocar peça).
    // input: Tabuleiro, opção do jogador, jogador atual e quadrante principal.
    // Saída: Atualiza o tabuleiro com a jogada do jogador.
    
    char seletor_jogada;
    int linha, coluna; 
    int i, j;

    do{
        
        if (*jogador == 0){
            printf("Vez da 'O'!\n");
            printf("\n");
        }else{
            printf("Vez da 'X'!\n");
            printf("\n");
        }    

        printf("Digite a jogada que deseja executar.\n");
        printf("\n");
        printf("0. Desistir.\n");
        printf("1. Posicionar peça.\n");
        printf("2. Realocar peça para outro quadrante.\n");
        printf("> ");
        fgets(entrada, sizeof(entrada), stdin);
        sscanf(entrada, "%d", opcao);
        printf("\n");

        if(*opcao == 0){
            printf("Muito Newba, slk...\n");
            break;
        }else if(*opcao == 1){
            posiciona_peca(t, seletor_jogada, q, jogador);
        }else if(*opcao == 2){
            realoca_peca(t, seletor_jogada, q, jogador);
        }else{
            printf("Opção inválida! Tente novamente.\n");
            printf("\n");
        }

    }while(*opcao != 1);
}

void seleciona_quadrante_principal(quadrante *q){

    // Objetivo: Define a posição do quadrante selecionado.
    // Entrada: Seletor do quadrante.
    // Saída: Atualiza as coordenadas do quadrante principal.

    

    printf("Qual será o novo quadrante principal? (1-9) > ");
    fgets(entrada, sizeof(entrada), stdin);
    sscanf(entrada, "%c", &q->seletor_quadrante);
    printf("\n");
    

    if(q->seletor_quadrante != '1' && q->seletor_quadrante != '2' && q->seletor_quadrante != '3' &&
    q->seletor_quadrante != '4' && q->seletor_quadrante != '5' && q->seletor_quadrante != '6' &&
    q->seletor_quadrante != '7' && q->seletor_quadrante != '8' && q->seletor_quadrante != '9'){

        printf("Quadrante inválido! Tente novamente.\n");
        printf("\n");
            
        }

    if (q->seletor_quadrante == '1'){
        q->linha = 0; // Quadrante 1
        q->coluna = 0;
    }else if (q->seletor_quadrante == '2'){
        q->linha = 0; // Quadrante 2
        q->coluna = 3;
    }else if (q->seletor_quadrante == '3'){
        q->linha = 0; // Quadrante 3
        q->coluna = 6;
    }else if (q->seletor_quadrante == '4'){
        q->linha = 3; // Quadrante 4
        q->coluna = 0;
    }else if (q->seletor_quadrante == '5'){
        q->linha = 3; // Quadrante 5              
        q->coluna = 3;
    }else if (q->seletor_quadrante == '6'){
        q->linha = 3; // Quadrante 6
        q->coluna = 6;
    }else if (q->seletor_quadrante == '7'){
        q->linha = 6; // Quadrante 7
        q->coluna = 0;
    }else if (q->seletor_quadrante == '8'){
        q->linha = 6; // Quadrante 8
        q->coluna = 3;
    }else if (q->seletor_quadrante == '9'){
        q->linha = 6; // Quadrante 9
        q->coluna = 6;
    }
}

void posiciona_peca(char t[9][9], char seletor_jogada, quadrante *q, int *jogador){
    
    // Objetivo: Permite que o jogador posicione uma peça no quadrante selecionado.
    // input: Tabuleiro, seletor de jogada, quadrante e jogador atual.
    // output: Atualiza o tabuleiro com a jogada do jogador.

    int i, j;
    
    if (*jogador == 0){

        printf("Escolha uma posição (1-9) para jogar no quadrante %c. > ", q->seletor_quadrante);
        fgets(entrada, sizeof(entrada), stdin);
        sscanf(entrada, "%c", &seletor_jogada);
        printf("\n");

        if(seletor_jogada != '1' && seletor_jogada != '2' && seletor_jogada != '3' &&
        seletor_jogada != '4' && seletor_jogada != '5' && seletor_jogada != '6' &&
        seletor_jogada != '7' && seletor_jogada != '8' && seletor_jogada != '9' ){

            printf("Posição inválida! Tente novamente.\n");
            printf("\n");
            return;
        
        }else{

            for(i=q->linha; i<q->linha+3; i++){
                for(j=q->coluna; j<q->coluna+3;j++){
                    if(seletor_jogada == t[i][j]){
                        t[i][j] = 'O';
                        *jogador = 1; // Muda para o próximo jogador
                    }
                }
            }
            if(*jogador == 0)
                printf("Posição já ocupada! Tente novamente.\n");
                printf("\n");
                return;
        }

    }else{
        
        printf("Escolha uma posição (1-9) para jogar no quadrante %c. > ", q->seletor_quadrante);
        fgets(entrada, sizeof(entrada), stdin);
        sscanf(entrada, "%c", &seletor_jogada);
        printf("\n");

        if(seletor_jogada != '1' && seletor_jogada != '2' && seletor_jogada != '3' &&
        seletor_jogada != '4' && seletor_jogada != '5' && seletor_jogada != '6' &&
        seletor_jogada != '7' && seletor_jogada != '8' && seletor_jogada != '9' ){

            printf("Posição inválida! Tente novamente.\n");
            printf("\n");
            return;
        
        }else{

            for(i=q->linha; i<q->linha+3; i++){
                for(j=q->coluna; j<q->coluna+3; j++){
                    if(seletor_jogada == t[i][j]){
                        t[i][j] = 'X';
                        *jogador = 0; // Muda para o próximo jogador
                    }
                }
            }
            if(*jogador == 1)
                printf("Posição já ocupada! Tente novamente.\n");
                printf("\n");
                return;
        }
    }
}

void realoca_peca(char t[9][9], char seletor_jogada, quadrante *q, int *jogador){

    // Objetivo: Permite que o jogador realoque uma peça de um quadrante para outro.
    // input: Tabuleiro, seletor de jogada, quadrante e jogador atual.
    // output: Atualiza o tabuleiro com a jogada do jogador.

    char matriz_de_troca[9][9], troca;
    int troca_l, troca_c; //variaveis para armazenar a posição da peça a ser realocada
    int i, j;

    cria(matriz_de_troca);

    printf("Escolha a posição (1-9) da peça que deseja realocar no quadrante %c. > ", q->seletor_quadrante);
    fgets(entrada, sizeof(entrada), stdin);
    sscanf(entrada, "%c", &seletor_jogada);
    printf("\n");

    if(seletor_jogada != '1' && seletor_jogada != '2' && seletor_jogada != '3' &&
        seletor_jogada != '4' && seletor_jogada != '5' && seletor_jogada != '6' &&
        seletor_jogada != '7' && seletor_jogada != '8' && seletor_jogada != '9' ){

        printf("Posição inválida! Tente novamente.\n");
        printf("\n");
        return;
        
        }else{
            
            for(i=q->linha; i<q->linha+3; i++){
                for(j=q->coluna; j<q->coluna+3; j++){
                
                    if(seletor_jogada == matriz_de_troca[i][j]){
        
                        if(t[i][j] != 'O' && t[i][j] != 'X'){
                            printf("Não há peça nesta posição.\n");
                            printf("\n");
                            return; // Sai da função se não houver peça na posição selecionada
                        }else if (*jogador == 0 && t[i][j] == 'X'){
                            printf("Você não pode realocar a peça do adversário.\n");
                            printf("\n");
                            return; // Sai da função se o jogador tentar realocar peça do outro jogador
                        }else if (*jogador == 1 && t[i][j] == 'O'){
                            printf("Você não pode realocar a peça do adversário.\n");
                            printf("\n");
                            return; // Sai da função se o jogador tentar realocar peça do outro jogador    
                        }    
                    }
                }
            }

            for(i=q->linha; i<q->linha+3; i++){
                for(j=q->coluna; j<q->coluna+3; j++){
                
                    if(seletor_jogada == matriz_de_troca[i][j]){
        
                        troca = t[i][j];
                        t[i][j] = matriz_de_troca[i][j]; 
        
                    }
                }
            }
        }


    printf("Para qual quadrante deseja realocar a peça? (1-9) > ");
    fgets(entrada, sizeof(entrada), stdin);
    sscanf(entrada, "%c", &q->seletor_quadrante);
    printf("\n");
    

    if(q->seletor_quadrante != '1' && q->seletor_quadrante != '2' && q->seletor_quadrante != '3' &&
       q->seletor_quadrante != '4' && q->seletor_quadrante != '5' && q->seletor_quadrante != '6' &&
       q->seletor_quadrante != '7' && q->seletor_quadrante != '8' && q->seletor_quadrante != '9'){

        printf("Quadrante inválido! Tente novamente.\n");
        printf("\n");
        return;
    
    }else{
    
        if (q->seletor_quadrante == '1'){
           troca_l = 0; // Quadrante 1
           troca_c = 0;
       }else if (q->seletor_quadrante == '2'){
           troca_l = 0; // Quadrante 2
           troca_c = 3;
       }else if (q->seletor_quadrante == '3'){
           troca_l = 0; // Quadrante 3
           troca_c = 6;
       }else if (q->seletor_quadrante == '4'){
           troca_l = 3; // Quadrante 4
           troca_c = 0;
       }else if (q->seletor_quadrante == '5'){
           troca_l = 3; // Quadrante 5              
           troca_c = 3;
       }else if (q->seletor_quadrante == '6'){
           troca_l = 3; // Quadrante 6
           troca_c = 6;
       }else if (q->seletor_quadrante == '7'){
           troca_l = 6; // Quadrante 7
           troca_c = 0;
       }else if (q->seletor_quadrante == '8'){
           troca_l = 6; // Quadrante 8
           troca_c = 3;
       }else if (q->seletor_quadrante == '9'){
           troca_l = 6; // Quadrante 9
           troca_c = 6;
       }
    }

    printf("Digite a posição (1-9) para qual deseja realocar a peça no quadrante %c. > ", q->seletor_quadrante);
    fgets(entrada, sizeof(entrada), stdin);
    sscanf(entrada, "%c", &seletor_jogada);
    printf("\n");

    if(seletor_jogada != '1' && seletor_jogada != '2' && seletor_jogada != '3' &&
        seletor_jogada != '4' && seletor_jogada != '5' && seletor_jogada != '6' &&
        seletor_jogada != '7' && seletor_jogada != '8' && seletor_jogada != '9' ){

        printf("Posição inválida! Tente novamente.\n");
        printf("\n");
        return;
        
        }else{

            for(i=troca_l; i<troca_l+3; i++){
                for(j=troca_c; j<troca_c+3; j++){
                    
                    if(seletor_jogada == t[i][j])
                        
                        t[i][j] = troca; // Realoca a peça na nova posição
        
                }
            }
        }

        if (*jogador == 0){
            *jogador = 1; // Muda para o próximo jogador
        }else{
            *jogador = 0; // Muda para o próximo jogador
        }

    imprime(t);
}

void verifica_vencedor(char t[9][9], quadrante *q, int *jogador, int *opcao){

    // Objetivo: Verifica se há um vencedor no jogo da velha ao quadrado.
    // Entrada: Tabuleiro, quadrante principal, jogador atual e opção do jogador.
    // Saída: Atualiza o tabuleiro com a jogada do jogador e encerra o jogo se houver vencedor.

    int i, j;

    //Quadrante 1

    if(t[0][0] != 'x' && t[0][0] != 'o'){

        if(t[0][0] == t[0][1] && t[0][1] == t[0][2] || t[1][0] == t[1][1] && t[1][1] == t[1][2] ||
           t[2][0] == t[2][1] && t[2][1] == t[2][2] || t[0][0] == t[1][0] && t[1][0] == t[2][0] ||
           t[0][1] == t[1][1] && t[1][1] == t[2][1] || t[0][2] == t[1][2] && t[1][2] == t[2][2] ||
           t[0][0] == t[1][1] && t[1][1] == t[2][2] || t[0][2] == t[1][1] && t[1][1] == t[2][0] ){
            if (*jogador == 0){
                for(i=0; i<3; i++){
                    for(j=0; j<3; j++){
                        t[i][j] = 'x'; // Marca o quadrante como vencedor
                    }
                }
                seleciona_quadrante_principal(q);
                *jogador = 1; // Continua sendo a vez do 'x'
            }else{
                for(i=0; i<3; i++){
                    for(j=0; j<3; j++){
                        t[i][j] = 'o'; // Marca o quadrante como vencedor
                    }
                }
                seleciona_quadrante_principal(q);
                *jogador = 0; // Continua sendo a vez do 'o'
            }
        }
    }

    //Quadrante 2
    if(t[0][3] != 'x' && t[0][3] != 'o'){

        if(t[0][3] == t[0][4] && t[0][4] == t[0][5] || t[1][3] == t[1][4] && t[1][4] == t[1][5] ||
           t[2][3] == t[2][4] && t[2][4] == t[2][5] || t[0][3] == t[1][3] && t[1][3] == t[2][3] ||
           t[0][4] == t[1][4] && t[1][4] == t[2][4] || t[0][5] == t[1][5] && t[1][5] == t[2][5] ||
           t[0][3] == t[1][4] && t[1][4] == t[2][5] || t[0][5] == t[1][4] && t[1][4] == t[2][3] ){
            if (*jogador == 0){
                for(i=0; i<3; i++){
                    for(j=3; j<6; j++){
                        t[i][j] = 'x'; // Marca o quadrante como vencedor
                    }
                }
                seleciona_quadrante_principal(q);
                *jogador = 1; // Continua sendo a vez do 'x'
            }else{
                for(i=0; i<3; i++){
                    for(j=3; j<6; j++){
                        t[i][j] = 'o'; // Marca o quadrante como vencedor
                    }
                }
                seleciona_quadrante_principal(q);
                *jogador = 0; // Continua sendo a vez do 'o'
            }
        }
    }

    //Quadrante 3
    
    if(t[0][6] != 'x' && t[0][6] != 'o'){

        if(t[0][6] == t[0][7] && t[0][7] == t[0][8] || t[1][6] == t[1][7] && t[1][7] == t[1][8] ||
           t[2][6] == t[2][7] && t[2][7] == t[2][8] || t[0][6] == t[1][6] && t[1][6] == t[2][6] ||
           t[0][7] == t[1][7] && t[1][7] == t[2][7] || t[0][8] == t[1][8] && t[1][8] == t[2][8] ||
           t[0][6] == t[1][7] && t[1][7] == t[2][8] || t[0][8] == t[1][7] && t[1][7] == t[2][6] ){
            if (*jogador == 0){
                for(i=0; i<3; i++){
                    for(j=6; j<9; j++){
                        t[i][j] = 'x'; // Marca o quadrante como vencedor
                    }
                }
                seleciona_quadrante_principal(q);
                *jogador = 1; // Continua sendo a vez do 'x'
            }else{
                for(i=0; i<3; i++){
                    for(j=6; j<9; j++){
                        t[i][j] = 'o'; // Marca o quadrante como vencedor
                    }
                }
                seleciona_quadrante_principal(q);
                *jogador = 0; // Continua sendo a vez do 'o'
            }
        }
    }

    //Quadrante 4

    if(t[3][0] != 'x' && t[3][0] != 'o'){

        if(t[3][0] == t[3][1] && t[3][1] == t[3][2] || t[4][0] == t[4][1] && t[4][1] == t[4][2] ||
           t[5][0] == t[5][1] && t[5][1] == t[5][2] || t[3][0] == t[4][0] && t[4][0] == t[5][0] ||
           t[3][1] == t[4][1] && t[4][1] == t[5][1] || t[3][2] == t[4][2] && t[4][2] == t[5][2] ||
           t[3][0] == t[4][1] && t[4][1] == t[5][2] || t[3][2] == t[4][1] && t[4][1] == t[5][0] ){
            if (*jogador == 0){
                for(i=3; i<6; i++){
                    for(j=0; j<3; j++){
                        t[i][j] = 'x'; // Marca o quadrante como vencedor
                    }
                }
                seleciona_quadrante_principal(q);
                *jogador = 1; // Continua sendo a vez do 'x'
            }else{
                for(i=3; i<6; i++){
                    for(j=0; j<3; j++){
                        t[i][j] = 'o'; // Marca o quadrante como vencedor
                    }
                }
                seleciona_quadrante_principal(q);
                *jogador = 0; // Continua sendo a vez do 'o'
            }
        }
    }

    //Quadrante 5

    if(t[3][3] != 'x' && t[3][3] != 'o'){

        if(t[3][3] == t[3][4] && t[3][4] == t[3][5] || t[4][3] == t[4][4] && t[4][4] == t[4][5] ||
           t[5][3] == t[5][4] && t[5][4] == t[5][5] || t[3][3] == t[4][3] && t[4][3] == t[5][3] ||
           t[3][4] == t[4][4] && t[4][4] == t[5][4] || t[3][5] == t[4][5] && t[4][5] == t[5][5] ||
           t[3][3] == t[4][4] && t[4][4] == t[5][5] || t[3][5] == t[4][4] && t[4][4] == t[5][3] ){
            if (*jogador == 0){
                for(i=3; i<6; i++){
                    for(j=3; j<6; j++){
                        t[i][j] = 'x'; // Marca o quadrante como vencedor
                    }
                }
                seleciona_quadrante_principal(q);
                *jogador = 1; // Continua sendo a vez do 'x'
            }else{
                for(i=3; i<6; i++){
                    for(j=3; j<6; j++){
                        t[i][j] = 'o'; // Marca o quadrante como vencedor
                    }
                }
                seleciona_quadrante_principal(q);
                *jogador = 0; // Continua sendo a vez do 'o'
            }
        }
    }

    //Quadrante 6

    if(t[3][6] != 'x' && t[3][6] != 'o'){

        if(t[3][6] == t[3][7] && t[3][7] == t[3][8] || t[4][6] == t[4][7] && t[4][7] == t[4][8] ||
           t[5][6] == t[5][7] && t[5][7] == t[5][8] || t[3][6] == t[4][6] && t[4][6] == t[5][6] ||
           t[3][7] == t[4][7] && t[4][7] == t[5][7] || t[3][8] == t[4][8] && t[4][8] == t[5][8] ||
           t[3][6] == t[4][7] && t[4][7] == t[5][8] || t[3][8] == t[4][7] && t[4][7] == t[5][6] ){
            if (*jogador == 0){
                for(i=3; i<6; i++){
                    for(j=6; j<9; j++){
                        t[i][j] = 'x'; // Marca o quadrante como vencedor
                    }
                }
                seleciona_quadrante_principal(q);
                *jogador = 1; // Continua sendo a vez do 'x'
            }else{
                for(i=3; i<6; i++){
                    for(j=6; j<9; j++){
                        t[i][j] = 'o'; // Marca o quadrante como vencedor
                    }
                }
                seleciona_quadrante_principal(q);
                *jogador = 0; // Continua sendo a vez do 'o'
            }
        }
    }

    //Quadrante 7

    if(t[6][0] != 'x' && t[6][0] != 'o'){

        if(t[6][0] == t[6][1] && t[6][1] == t[6][2] || t[7][0] == t[7][1] && t[7][1] == t[7][2] ||
           t[8][0] == t[8][1] && t[8][1] == t[8][2] || t[6][0] == t[7][0] && t[7][0] == t[8][0] ||
           t[6][1] == t[7][1] && t[7][1] == t[8][1] || t[6][2] == t[7][2] && t[7][2] == t[8][2] ||
           t[6][0] == t[7][1] && t[7][1] == t[8][2] || t[6][2] == t[7][1] && t[7][1] == t[8][0] ){
            if (*jogador == 0){
                for(i=6; i<9; i++){
                    for(j=0; j<3; j++){
                        t[i][j] = 'x'; // Marca o quadrante como vencedor
                    }
                }
                seleciona_quadrante_principal(q);
                *jogador = 1; // Continua sendo a vez do 'x'
            }else{
                for(i=6; i<9; i++){
                    for(j=0; j<3; j++){
                        t[i][j] = 'o'; // Marca o quadrante como vencedor
                    }
                }
                seleciona_quadrante_principal(q);
                *jogador = 0; // Continua sendo a vez do 'o'
            }
        }
    }

    //Quadrante 8

    if(t[6][3] != 'x' && t[6][3] != 'o'){

        if(t[6][3] == t[6][4] && t[6][4] == t[6][5] || t[7][3] == t[7][4] && t[7][4] == t[7][5] ||
           t[8][3] == t[8][4] && t[8][4] == t[8][5] || t[6][3] == t[7][3] && t[7][3] == t[8][3] ||
           t[6][4] == t[7][4] && t[7][4] == t[8][4] || t[6][5] == t[7][5] && t[7][5] == t[8][5] ||
           t[6][3] == t[7][4] && t[7][4] == t[8][5] || t[6][5] == t[7][4] && t[7][4] == t[8][3] ){
            if (*jogador == 0){
                for(i=6; i<9; i++){
                    for(j=3; j<6; j++){
                        t[i][j] = 'x'; // Marca o quadrante como vencedor
                    }
                }
                seleciona_quadrante_principal(q);
                *jogador = 1; // Continua sendo a vez do 'x'
            }else{
                for(i=6; i<9; i++){
                    for(j=3; j<6; j++){
                        t[i][j] = 'o'; // Marca o quadrante como vencedor
                    }
                }
                seleciona_quadrante_principal(q);
                *jogador = 0; // Continua sendo a vez do 'o'
            }
        }
    }

    //Quadrante 9

    if(t[6][6] != 'x' && t[6][6] != 'o'){

        if(t[6][6] == t[6][7] && t[6][7] == t[6][8] || t[7][6] == t[7][7] && t[7][7] == t[7][8] ||
           t[8][6] == t[8][7] && t[8][7] == t[8][8] || t[6][6] == t[7][6] && t[7][6] == t[8][6] ||
           t[6][7] == t[7][7] && t[7][7] == t[8][7] || t[6][8] == t[7][8] && t[7][8] == t[8][8] ||
           t[6][6] == t[7][7] && t[7][7] == t[8][8] || t[6][8] == t[7][7] && t[7][7] == t[8][6] ){
            if (*jogador == 0){
                for(i=6; i<9; i++){
                    for(j=6; j<9; j++){
                        t[i][j] = 'x'; // Marca o quadrante como vencedor
                    }
                }
                seleciona_quadrante_principal(q);
                *jogador = 1; // Continua sendo a vez do 'x'
            }else{
                for(i=6; i<9; i++){
                    for(j=6; j<9; j++){
                        t[i][j] = 'o'; // Marca o quadrante como vencedor
                    }
                }
                seleciona_quadrante_principal(q);
                *jogador = 0; // Continua sendo a vez do 'o'
            }
        }    
    }

    if(t[0][0] == 'x' && t[0][0] == t[0][3] && t[0][0] == t[0][6] ||
       t[3][0] == 'x' && t[3][0] == t[3][3] && t[3][0] == t[3][6] ||
       t[6][0] == 'x' && t[6][0] == t[6][3] && t[6][0] == t[6][6] ||
       t[0][0] == 'x' && t[0][0] == t[3][0] && t[0][0] == t[6][0] ||
       t[0][3] == 'x' && t[0][3] == t[3][3] && t[0][3] == t[6][3] ||
       t[0][6] == 'x' && t[0][6] == t[3][6] && t[0][6] == t[6][6] ||
       t[0][0] == 'x' && t[0][0] == t[3][3] && t[0][0] == t[6][6] ||
       t[0][6] == 'x' && t[0][6] == t[3][3] && t[0][6] == t[6][0]){
        imprime(t);
        printf("Parabéns, jogador 'X'! Você venceu!\n");
        printf("\n");
        *opcao = 0; // Encerra o jogo
    }else if(t[0][0] == 'o' && t[0][0] == t[0][3] && t[0][0] == t[0][6] ||
            t[3][0] == 'o' && t[3][0] == t[3][3] && t[3][0] == t[3][6] ||
            t[6][0] == 'o' && t[6][0] == t[6][3] && t[6][0] == t[6][6] ||
            t[0][0] == 'o' && t[0][0] == t[3][0] && t[0][0] == t[6][0] ||
            t[0][3] == 'o' && t[0][3] == t[3][3] && t[0][3] == t[6][3] ||
            t[0][6] == 'o' && t[0][6] == t[3][6] && t[0][6] == t[6][6] ||
            t[0][0] == 'o' && t[0][0] == t[3][3] && t[0][0] == t[6][6] ||
            t[0][6] == 'o' && t[0][6] == t[3][3] && t[0][6] == t[6][0]){
        imprime(t);
        printf("Parabéns, jogador 'O'! Você venceu!\n");
        printf("\n");
        *opcao = 0; // Encerra o jogo
    }
}