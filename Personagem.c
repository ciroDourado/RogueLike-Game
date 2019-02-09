#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Personagem.h"

void init_player(player **Explorador, Lista **nivel){
//    printf("\tinit_player...");

    if( *Explorador == NULL ){
        player *novo = malloc(sizeof(player));
        novo->gold = 0;
        novo->HP=60;
        (*Explorador) = novo;
    }

    (*Explorador)->pos_X = malloc(sizeof(int));
    *((*Explorador)->pos_X) = *((*nivel)->spawnX);

    (*Explorador)->pos_Y = malloc(sizeof(int));
    *((*Explorador)->pos_Y) = *((*nivel)->spawnY);

    (*nivel)->mapa[*((*nivel)->spawnX)][*((*nivel)->spawnY)].tipo = personagem;
//    printf("successful\n");
}

void processoLOS(terreno ***visao, Lista **nivel, player *explorador){
    int i,j,n;
    double versorX, versorY;
    int posX = (2+2*limiteCampoDeVisao)/2, posY = (2+2*limiteCampoDeVisao)/2;
    for( j = 0 ; j < 3+2*limiteCampoDeVisao ; j++ ){
        for( i = 0 ; i < 3+2*limiteCampoDeVisao ; i++ ){
            (*visao)[i][j].visivel = 1;
            double modulo = sqrt(1.0*((i-posX)*(i-posX)+(j-posY)*(j-posY)));
            if( modulo == 0 ){
                (*visao)[i][j].explorado = 1;
                continue;
            }
            if( modulo > limiteCampoDeVisao ){
                (*visao)[i][j].visivel = 0;
                continue;
            }

            versorX = (i-posX)/modulo;
            versorY = (j-posY)/modulo;

            for( n = 0 ; n < modulo ; n++ ){
                int stepX, stepY;
                stepX = round(posX+n*versorX);
                stepY = round(posY+n*versorY);
                if( !(stepX == i && stepY == j) && ((*visao)[stepX][stepY].tipo == parede || (*visao)[stepX][stepY].tipo == bedrock)){
                    (*visao)[i][j].visivel = 0;
                    continue;
                }
            }
            if( (*visao)[i][j].visivel == 1 ){
                (*visao)[i][j].explorado = 1;
                (*nivel)->mapa[*(explorador->pos_X) - (limiteCampoDeVisao+1) + i][*(explorador->pos_Y) - (limiteCampoDeVisao+1) + j].explorado = 1;
            }
        }
    }
}

void atualiza_line_of_sight(terreno **field, player *explorador, Lista *nivel){
//    printf("\tline_of_sight...");
    int i, j;
    for( j = 0 ; j < 3 + 2*limiteCampoDeVisao ; j++ ){
        for( i = 0 ; i < 3 + 2*limiteCampoDeVisao ; i++ ){
            field[i][j].explorado = nivel->mapa[*(explorador->pos_X) - (limiteCampoDeVisao+1) + i][*(explorador->pos_Y) - (limiteCampoDeVisao+1) + j].explorado;
            field[i][j].tipo = nivel->mapa[*(explorador->pos_X) - (limiteCampoDeVisao+1) + i][*(explorador->pos_Y) - (limiteCampoDeVisao+1) + j].tipo;
        }
    }
//    printf("updated\n");
}
