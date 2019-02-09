#ifndef FISICA_H_INCLUDED
#define FISICA_H_INCLUDED

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 13
#define KEY_BACKSPACE 8

#include "Mapa.h"
#include "cores.h"
#include "Personagem.h"
#include "BancoDados.h"

int movimento(Lista **nivel, terreno **mapa, player *Explorador,int L,int A);
int react_gnome(Lista **nivel, player *Explorador, int L, int A);
void react_potion(Lista **nivel, player *Explorador);

#endif // FISICA_H_INCLUDED
