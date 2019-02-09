#ifndef BANCODADOS_H_INCLUDED
#define BANCODADOS_H_INCLUDED

#include "Mapa.h"
#include "Personagem.h"

int find_txt_file(char *c);
void search_game_directory(char slot1[],char slot2[],char slot3[]);
void set_file_name(char n[]);
void exit_current_game(Lista *nivel, player *Explorador);
void new_save(char filename[], Lista *nivel, player *Explorador);

#endif // BANCODADOS_H_INCLUDED
