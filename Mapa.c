#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <locale.h>

#include "Mapa.h"
#include "cores.h"
#include "Personagem.h"

void init_matriz(terreno ***matriz, int L, int A){
//    printf("\tinit_matrix...");
    int i;
    *matriz = (terreno**)malloc(L*sizeof(terreno*));
    for( i = 0 ; i < L ; i++ ){
        (*matriz)[i] = (terreno*)malloc(A*sizeof(terreno));
    }
    if( (**matriz) == NULL ){
        printf("Memória insuficiente\n");
        exit(0);
    }
    int j;
    for( j = 0 ; j < A ; j++ ){
        for( i = 0 ; i < L ; i++ ){
            (*matriz)[i][j].tipo = vazio;
            (*matriz)[i][j].explorado = 0;
            (*matriz)[i][j].visivel = 0;
            (*matriz)[i][j].B = L;
            (*matriz)[i][j].H = A;
            (*matriz)[i][j].aux = 0;
        }
    }
//    printf("finished\n");
}

void draw_matriz(Lista *nivel, terreno **visao, player *Explorador, int L){
    setlocale(LC_ALL,"C");
    gotoxy(0,0);
    int i, j;
    for( j = 0 ; j < 3 + 2*limiteCampoDeVisao ; j++ ){
        gotoxy( (*(Explorador->pos_X) - (limiteCampoDeVisao+1)), (*(Explorador->pos_Y) - (limiteCampoDeVisao+1) + j) );
        for( i = 0 ; i < 3 + 2*limiteCampoDeVisao ; i++ ){
            if( visao[i][j].explorado == 1 ){
                if( visao[i][j].visivel == 1 ){
                    if( visao[i][j].tipo == bedrock ){
                        SetBack(0);
                        SetColor(15);
                        printf("%c",178);
                    }
                    else if( visao[i][j].tipo == personagem ){
                        SetBack(0);
                        if( (*(Explorador->pos_X) - (limiteCampoDeVisao+1) + i ) == *(nivel->spawnX) && (*(Explorador->pos_Y) - (limiteCampoDeVisao+1) + j ) == *(nivel->spawnY) ){
                            SetBack(12);
                        }
                        SetColor(3);
                        printf("o");
                    }
                    else if( visao[i][j].tipo == chao ){
                        SetBack(0);
                        if( (*(Explorador->pos_X) - (limiteCampoDeVisao+1) + i ) == *(nivel->spawnX) && (*(Explorador->pos_Y) - (limiteCampoDeVisao+1) + j ) == *(nivel->spawnY) )
                            SetBack(12);
                        if( (*(Explorador->pos_X) - (limiteCampoDeVisao+1) + i ) == *(nivel->endX) && (*(Explorador->pos_Y) - (limiteCampoDeVisao+1) + j ) == *(nivel->endY) )
                            SetBack(9);
                        SetColor(15);
                        printf("%c",176);
                    }
                    else if( visao[i][j].tipo == parede ){
                        SetBack(0);
                        SetColor(15);
                        printf("%c",177);
                    }
                    else if( visao[i][j].tipo == ouro ){
                        SetBack(0);
                        SetColor(14);
                        printf("%c",4);
                    }
                    else if( visao[i][j].tipo == vazio ){
                        SetBack(0);
                        SetBack(0);
                        printf(" ");
                    }
                    else if( visao[i][j].tipo == gnome ){
                        SetBack(0);
                        SetColor(14);
                        printf("%c",4);
                    }
                    else if( visao[i][j].tipo == potion ){
                        SetBack(8);
                        SetColor(12);
                        printf("%c",3);
                    }
                }
                if( visao[i][j].visivel == 0 ){
                    if( visao[i][j].tipo == bedrock ){
                        SetBack(0);
                        SetColor(8);
                        printf("%c",178);
                    }
                    else if( visao[i][j].tipo == chao ){
                        SetBack(0);
                        if( (*(Explorador->pos_X) - (limiteCampoDeVisao+1) + i ) == *(nivel->spawnX) && (*(Explorador->pos_Y) - (limiteCampoDeVisao+1) + j ) == *(nivel->spawnY) )
                            SetBack(12);
                        if( (*(Explorador->pos_X) - (limiteCampoDeVisao+1) + i ) == *(nivel->endX) && (*(Explorador->pos_Y) - (limiteCampoDeVisao+1) + j ) == *(nivel->endY) )
                            SetBack(9);
                        SetColor(8);
                        printf("%c",176);
                    }
                    else if( visao[i][j].tipo == parede ){
                        SetBack(0);
                        SetColor(8);
                        printf("%c",177);
                    }
                    else if( visao[i][j].tipo == ouro ){
                        SetBack(0);
                        SetColor(8);
                        printf("%c",176);
                    }
                    else if( visao[i][j].tipo == potion ){
                        SetBack(0);
                        SetColor(8);
                        printf("%c",176);
                    }
                    else if( visao[i][j].tipo == gnome ){
                        SetBack(0);
                        SetColor(8);
                        printf("%c",176);
                    }
                    else if( visao[i][j].tipo == vazio ){
                        SetBack(0);
                        SetBack(0);
                        printf(" ");
                    }
                }
            }
            if( visao[i][j].explorado == 0 ){
                SetBack(0);
                SetBack(0);
                printf(" ");
            }
        }
    }
    SetBack(0);
//    gotoxy(L+5,2);
//    SetColor(15);
//    printf("x = %d // y = %d",*(Explorador->pos_X),*(Explorador->pos_Y));
//    gotoxy(L+5,3);
//    printf("sX = %d // sY = %d // eX = %d // eY = %d",*(nivel->spawnX),*(nivel->spawnY),*(nivel->endX),*(nivel->endY));
    SetColor(14);
    gotoxy(L+5,2);
    printf("Moedas = %d ",Explorador->gold);
    SetColor(12);
    gotoxy(L+5,4);
    printf("        ");
    gotoxy(L+5,4);
    printf("Vida: %d",Explorador->HP);
    SetColor(15);
    gotoxy(L+5,6);
    printf("Aperte: ESC no spawn para salvar e sair");
    gotoxy(L+5,8);
    printf("ENTER em cima do ");
    SetBack(9);SetColor(8);printf("%c",176);
    SetBack(0);SetColor(15);
    printf(" para subir");
    gotoxy(L+5,10);
    printf("ENTER em cima do ");
    SetBack(12);SetColor(8);printf("%c",176);
    SetBack(0);SetColor(15);
    printf(" para voltar");
}

void put_bedrock(terreno ***map, int L, int A){
//    printf("\tput_bedrock...");
    int i;
    for( i = limiteCampoDeVisao ; i <= L-1-limiteCampoDeVisao ; i++ ){
        (*map)[i][limiteCampoDeVisao].tipo = bedrock;
        (*map)[i][A-1-limiteCampoDeVisao].tipo = bedrock;
    }
    for( i = limiteCampoDeVisao ; i <= A-1-limiteCampoDeVisao ; i++ ){
        (*map)[limiteCampoDeVisao][i].tipo = bedrock;
        (*map)[L-1-limiteCampoDeVisao][i].tipo = bedrock;
    }
//    printf("finished\n");
}

void put_items_ground_enemies(terreno ***map, int x, int y){


    int a = rand()%1000;
    if ( a < 1 )
        (*map)[x][y].tipo = potion;
    if( a >= 1 && a < 2 )
        (*map)[x][y].tipo = ouro;
    if( a >= 2 && a < 5)
        (*map)[x][y].tipo = gnome;
    if( a >= 5 )
        (*map)[x][y].tipo = chao;
//    printf("finished\n");
}

void put_walls(terreno ***map, int L, int A){
//    printf("\tput_walls...");
    int i, j;
    for( j = limiteCampoDeVisao ; j <= A-1-limiteCampoDeVisao ; j++ ){
        for( i = limiteCampoDeVisao ; i <= L-1-limiteCampoDeVisao ; i++ )
            (*map)[i][j].tipo = parede;
    }
//    printf("finished\n");
}

void put_cavern_paths(terreno ***map, int posX, int posY){
    int x = rand()%4;
    if( (*map)[posX][posY].tipo == bedrock )
        return;
    if( x == 0 ){
        put_items_ground_enemies(map,posX,posY);
        put_cavern_paths(map,posX,posY+1);
    }
    if( x == 1 ){
        put_items_ground_enemies(map,posX,posY);
        put_cavern_paths(map,posX,posY-1);
    }
    if( x == 2 ){
        put_items_ground_enemies(map,posX,posY);
        put_cavern_paths(map,posX+1,posY);
    }
    if( x == 3 ){
        put_items_ground_enemies(map,posX,posY);
        put_cavern_paths(map,posX-1,posY);
    }
}

int call_put_paths(terreno ***mapa, int L, int A, int spawn_X, int fator){
    int i, j, spawn_Y;
    for( i = (1+limiteCampoDeVisao) ; i < (L-1-limiteCampoDeVisao) ; i = i+fator ){
        j = 3*(1+limiteCampoDeVisao)+(rand()%(A-7*(limiteCampoDeVisao+1)-1));
        put_cavern_paths(mapa,i,j);
        if( spawn_X == i )
            spawn_Y = j;
    }
    return spawn_Y;
}

/**
 * Insere um valor na lista
 * @param lista Lista
 * @param valor Valor a ser inserido
 * @return Sucesso da operação
 */
int add(Lista **caverna, terreno **mapa, int *sX, int *sY, int *eX, int *eY)
{
    Lista *nova = malloc(sizeof(Lista));

    nova->mapa = mapa;

    nova->spawnX = malloc(sizeof(int));
    *(nova->spawnX) = *sX;
    nova->spawnY = malloc(sizeof(int));
    *(nova->spawnY) = *sY;

    nova->endX = malloc(sizeof(int));
    *(nova->endX) = *eX;
    nova->endY = malloc(sizeof(int));
    *(nova->endY) = *eY;

    nova->proximo = NULL;

    if((*caverna) == NULL)
    {
        nova->anterior = NULL;
        (*caverna) = nova;
        return 0;
    }
    Lista *and = *caverna;
    while(and->proximo != NULL)
        and = and->proximo;
    nova->anterior = and;
    and->proximo = nova;
    return 0;
}

/**
 * Retorna o valor contido na lista na posição pedida
 * @param lista Lista
 * @param posicao Posição do elemento desejado
 * @return Valor contido na posição
 */
int get(Lista *lista, int posicao)
{
    if(lista == NULL || posicao < 0 || posicao >= tamanho(lista))
        return -1;
    Lista *and = lista;
    int i;
    for( i = 0 ; i < posicao ; i++ )
        and = and->proximo;
    return 0;
}

/**
 * Conta o número de elementos na lista e retorna este valor
 * @param lista Lista
 * @return Número de elementos na lista
 */
int tamanho(Lista *caverna)
{
    Lista *and = caverna;
    int tam = 0;
    while(and != NULL)
    {
        tam++;
        and = and->proximo;
    }
    return tam;
}

void init_Level(Lista **nivel, terreno ***mapa, player **Explorador, int *L, int *A){

    srand(time(NULL));
    int fator = limiteCampoDeVisao+1;
    int spawn_X = (2*(1+limiteCampoDeVisao)*3)+fator*(rand()%((*L-(2*(1+limiteCampoDeVisao)*3))/(2*fator)));

    printf("\nmap matrix status:\n");
    init_matriz(mapa,*L,*A);
    put_walls(mapa,*L,*A);
    put_bedrock(mapa,*L,*A);
    int spawn_Y = call_put_paths(mapa,*L,*A,spawn_X,fator);

    int endpointX;
    int endpointY;
    int *key;
    int z;

    comeco:
    z = 0;
    key = &z;
    endpointX = (limiteCampoDeVisao+2)+rand()%(*L-2*(limiteCampoDeVisao+2));
    endpointY = (limiteCampoDeVisao+2)+rand()%(*A-2*(limiteCampoDeVisao+2));
    if( (*mapa)[endpointX][endpointY].tipo != chao )
        goto comeco;
    percorre_chao(mapa,spawn_X,spawn_Y,endpointX,endpointY,*L,*A,key);
    if( *key == 1 )
        goto comeco;
    if( *key == 2 )
        goto continuacao;

    continuacao:
    add(nivel,*mapa,&spawn_X,&spawn_Y,&endpointX,&endpointY);

    printf("\nplayer status:\n");
    init_player(Explorador,nivel);

    system("cls");
}

void print_map(Lista *nivel, int L, int A){
    int i, j;
    for( j = 0 ; j < A-limiteCampoDeVisao ; j ++ ){
        for( i = 0 ; i < L ; i++ ){
            if( nivel->mapa[i][j].explorado == 1 ){
                if( nivel->mapa[i][j].tipo == bedrock ){
                    SetBack(0);
                    SetColor(8);
                    printf("%c",178);
                }
                else if( nivel->mapa[i][j].tipo == chao ){
                    SetBack(0);
                    if( i == *(nivel->spawnX) && j == *(nivel->spawnY) )
                        SetBack(12);
                    if( i == *(nivel->endX) && j == *(nivel->endY) )
                        SetBack(9);
                    SetColor(8);
                    printf("%c",176);
                }
                else if( nivel->mapa[i][j].tipo == parede ){
                    SetBack(0);
                    SetColor(8);
                    printf("%c",177);
                }
                else if( nivel->mapa[i][j].tipo == ouro ){
                    SetBack(0);
                    SetColor(8);
                    printf("%c",176);
                }
                else if( nivel->mapa[i][j].tipo == gnome ){
                    SetBack(0);
                    SetColor(8);
                    printf("%c",176);
                }
                else if( nivel->mapa[i][j].tipo == potion ){
                    SetBack(0);
                    SetColor(8);
                    printf("%c",176);
                }
                else if( nivel->mapa[i][j].tipo == vazio ){
                    SetBack(0);
                    SetColor(0);
                    printf(" ");
                }
                else if( nivel->mapa[i][j].tipo == personagem ){
                    SetBack(15);
                    SetColor(3);
                    printf(" ");
                }
            }
            else
                printf(" ");
        }
        printf("\n");
    }
}

int percorre_chao(terreno ***mapa, int sX, int sY, int eX, int eY, int L, int A, int *key){
    if( *key == 1 || *key == 2 )
        return 0;
    if( (*mapa)[sX][sY].aux != 0 )
        return 0;
    if( (*mapa)[sX][sY].tipo != chao ){
        (*mapa)[sX][sY].aux = 2;
        return 0;
    }
    if( (*mapa)[sX+1][sY].aux != 0 && (*mapa)[sX-1][sY].aux != 0 && (*mapa)[sX][sY+1].aux != 0 && (*mapa)[sX][sY-1].aux != 0 ){
        *key = 1;
        return 0;
    }
    if( sX == eX && sY == eY ){
        *key = 2;
        return 0;
    }
    (*mapa)[sX][sY].aux = 1;
    percorre_chao(mapa,sX,sY+1,eX,eY,L,A,key);
    percorre_chao(mapa,sX,sY-1,eX,eY,L,A,key);
    percorre_chao(mapa,sX+1,sY,eX,eY,L,A,key);
    percorre_chao(mapa,sX-1,sY,eX,eY,L,A,key);
    return 0;
}
