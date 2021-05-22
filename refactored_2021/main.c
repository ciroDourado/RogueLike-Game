#include "tristto.h"

typedef struct Posicao {
    int x;
    int y;
} Posicao;

Posicao* new_Posicao(int x, int y) {
    Posicao* posicao = (Posicao*)malloc(sizeof(Posicao));
    if( posicao != NULL ) {
        posicao->x = x;
        posicao->y = y;
    }
    return posicao;
} // end new_Dimensoes




typedef struct Dimensoes {
    int altura;
    int largura;
} Dimensoes;

Dimensoes* new_Dimensoes(int altura, int largura) {
    Dimensoes* dimensoes = (Dimensoes*)malloc(sizeof(Dimensoes));
    if( dimensoes != NULL ) {
        dimensoes->altura  = altura;
        dimensoes->largura = largura;
    }
    return dimensoes;
} // end new_Dimensoes




typedef struct Preenchimento {
    char* caracter; // entenda isso como pixel
    int*  cor;
    int*  fundo;
} Preenchimento;

Preenchimento* new_Preenchimento() {
    Preenchimento* preenchimento = (Preenchimento*)malloc(sizeof(Preenchimento));
    if( preenchimento != NULL ) {
        preenchimento->caracter = NULL;
        preenchimento->cor      = NULL;
        preenchimento->fundo    = NULL;
    }
    return preenchimento;
} // end new_Dimensoes




typedef struct Caixa {
    Posicao*       posicao;
    Dimensoes*     dimensoes;
    Preenchimento* preenchimento;
} Caixa;

Caixa* new_Caixa() {
    Caixa* caixa = (Caixa*)malloc(sizeof(Caixa));
    if( caixa != NULL ) {
        caixa->posicao       = NULL;
        caixa->dimensoes     = NULL;
        caixa->preenchimento = NULL;
    } 
    return caixa;
} // end new_Caixa




typedef struct Tela {
    Caixa* mapa;
    Caixa* jogador;
    Caixa* dialogo;
} Tela;

Caixa* new_mapa();
Caixa* new_jogador();
Caixa* new_dialogo();

Tela* new_Tela() {
    Tela* tela = (Tela*)malloc(sizeof(Tela));
    if( tela != NULL ) {
        tela->mapa    = new_mapa();
        tela->jogador = new_jogador();
        tela->dialogo = new_dialogo();
    }
    return tela;
} // end new_Tela



Caixa* new_mapa() {
    Caixa* mapa = new_Caixa();
    if( mapa != NULL ) {
        mapa->posicao   = new_Posicao(0, 0);
        mapa->dimensoes = new_Dimensoes(60, 90);
        mapa->preenchimento = new_Preenchimento();
    }
    return mapa;
} // end new_mapa


Caixa* new_jogador() {
    Caixa* jogador = new_Caixa();
    if( jogador != NULL ) {
        jogador->posicao   = new_Posicao(90, 0);
        jogador->dimensoes = new_Dimensoes(25, 30);
        jogador->preenchimento = new_Preenchimento();
    }
    return jogador;
} // end new_jogador


Caixa* new_dialogo() {
    Caixa* dialogo = new_Caixa();
    if( dialogo != NULL ) {
        dialogo->posicao   = new_Posicao(90, 25);
        dialogo->dimensoes = new_Dimensoes(35, 30);
        dialogo->preenchimento = new_Preenchimento();
    }
    return dialogo;
} // end new_dialogo


void preencher(Caixa* caixa) {
    if( caixa != NULL ) {
        int altura  = caixa->dimensoes->altura;
        int largura = caixa->dimensoes->largura;
        int dimensoes = altura*largura;

        caixa->preenchimento->caracter = (char*)calloc(dimensoes,sizeof(char));
        caixa->preenchimento->cor      = (int*)calloc(dimensoes,sizeof(int));
        caixa->preenchimento->fundo    = (int*)calloc(dimensoes,sizeof(int));
    }
} // end preencher

void _set_cor(Preenchimento*, Dimensoes*, int);
void _set_cor_(int**, Dimensoes*, int);

void set_cor(Caixa* caixa, int cor) {
    caixa != NULL? 
        _set_cor(caixa->preenchimento, caixa->dimensoes, cor):
        0;
} // end set_cor

void _set_cor(Preenchimento* preenchimento, Dimensoes* dimensoes, int cor) {
    (preenchimento != NULL) && (dimensoes != NULL)? 
        _set_cor_(&preenchimento->cor, dimensoes, cor):
        0;
} // end _set_cor

void _set_cor_(int** vetor_cor, Dimensoes* dimensoes, int cor) {
    int altura  = dimensoes->altura;
    int largura = dimensoes->largura;
    int max = altura*largura;

    if( *vetor_cor != NULL) {
        int i; for(i = 0; i < max; i++) {
            (*vetor_cor)[i] = cor;
        }
    }
} // end _set_cor_

void _set_fundo(Preenchimento*, Dimensoes*, int);

void set_fundo(Caixa* caixa, int fundo) {
    caixa != NULL? 
        _set_fundo(caixa->preenchimento, caixa->dimensoes, fundo):
        0;
} // end set_fundo

void _set_fundo(Preenchimento* preenchimento, Dimensoes* dimensoes, int fundo) {
    (preenchimento != NULL) && (dimensoes != NULL)? 
        _set_cor_(&preenchimento->fundo, dimensoes, fundo):
        0;
} // end _set_fundo





void imprimeCaixa(Caixa* caixa) {
    imprimeMapa(
        caixa->posicao->x,
        caixa->posicao->y,
        caixa->preenchimento->caracter,
        caixa->preenchimento->cor     ,
        caixa->preenchimento->fundo   ,
        caixa->dimensoes->altura ,
        caixa->dimensoes->largura
    );
} // end imprimeCaixa


void imprimeTela(Tela* tela) {
    imprimeCaixa(tela->mapa);
    imprimeCaixa(tela->jogador);
    imprimeCaixa(tela->dialogo);
} // end imprimeTela


int main() {
    inicializaTela("Testing Box");
    
    Tela* tela = new_Tela();

    preencher(tela->mapa);
    set_fundo(tela->mapa, CINZA_ESCURO);

    preencher(tela->jogador);
    set_fundo(tela->jogador, BRANCO);

    preencher(tela->dialogo);
    set_fundo(tela->dialogo, ROXO_ESCURO);

    imprimeTela(tela);
    
    finalizaTela();
    system("pause");
    return 0;
}