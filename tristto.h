#ifndef TRISTTO_H_INCLUDED
#define TRISTTO_H_INCLUDED

#include<windows.h>

#define LARGURA_TELA 160
#define ALTURA_TELA 88
#define FRAME_RATE 60

typedef enum _COR {PRETO, AZUL_ESCURO, VERDE_ESCURO, CIANO_ESCURO, VERMELHO_ESCURO, ROXO_ESCURO, AMARELO_ESCURO, CINZA_CLARO,
                   CINZA_ESCURO, AZUL_CLARO, VERDE_CLARO, CIANO_CLARO, VERMELHO_CLARO, ROXO_CLARO, AMARELO_CLARO, BRANCO} COR;

typedef enum _TECLA {CIMA=VK_UP, BAIXO=VK_DOWN, ESQUERDA=VK_LEFT, DIREITA=VK_RIGHT, ESC = VK_ESCAPE, ENTER=VK_RETURN, ESPACO=' ',
                     CTRL=VK_CONTROL, SHIFT=VK_SHIFT, ALT=VK_MENU, TAB=VK_TAB, F1=VK_F1, F2=VK_F2, F3=VK_F3, F4=VK_F4, F5=VK_F5,
                     F6=VK_F6, F7=VK_F7, F8=VK_F8, F9=VK_F9, F10=VK_F10, F11=VK_F11, F12=VK_F12} TECLA;



void inicializaTela(const char s[]); //Chame esta funcao no inicio do seu programa!!! Passe uma string com o nome do programa como parametro.
void limpa_tela(COR corFundo); //Limpa a tela, deixando a cor pedida no fundo
void guia(); //Mostra a tabela ASCII e a tabela de cores
void finalizaTela(); //Chame esta funcao no final de seu programa!!!

/* As funcoes a seguir funcionam exatamente como as funcoes tradicionais. Porem, recebem
 * também uma posicao na tela, e as cores que deve ser utilizadas. Utilize estas funcoes
 * em vez das tradicionais, pois estas não vão funcionar corretamente. */
int tscanf(int posX, int posY, COR corLetra, COR corFundo, const char* s, ...);
void tgets(int posX, int posY, COR corLetra, COR corFundo, char *str);
void tprintf(int posX, int posY, COR corLetra, COR corFundo, const char* s, ...);
inline char tputchar(unsigned char c, int posX, int posY, COR corLetra, COR corFundo);
//esta funcao imprime normalmente, mas na vertical
void tprintf_v(int posX, int posY, COR corLetra, COR corFundo, const char* s, ...);
//esta funcao le um caracter do usuario, mas sem imprimir o mesmo na tela
char tgetch();

/* Esta funcao recebe 3 matrizes e imprime na tela os caracteres contidas na matriz "mapa", com as cores
 * contidas nas matrizes "coresFonte" e "coresFundo". A funcao tambem recebe as dimensoes das matrizes. */
void imprimeMapa(int x0, int y0, char *mapa, int *coresFonte, int *coresFundo, int altura, int largura);

/* Esta funcao retorna 1 se a tecla pedida estiver pressionada, e 0 se não estiver. Ela não espera o usuario
 * pressionar alguma tecla, apenas avisa o programa do estado atual da tecla pedida */
int lerTecla(unsigned char tecla);

#endif // TRISTTO_H_INCLUDED
