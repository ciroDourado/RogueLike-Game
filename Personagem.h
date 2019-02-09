#ifndef PERSONAGEM_H_INCLUDED
#define PERSONAGEM_H_INCLUDED

#include "Mapa.h"

void init_player(player **Explorador, Lista **nivel);
void atualiza_line_of_sight(terreno **field,player *p, Lista *nivel);
void processoLOS(terreno ***visao, Lista **nivel, player *explorador);

#endif // PERSONAGEM_H_INCLUDED

