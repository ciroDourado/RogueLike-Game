#include <stdio.h>
#include <dirent.h>  ///* struct DIR, struct dirent  */
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

#include "Fisica.h"

void react_potion(Lista **nivel, player *Explorador){
    Explorador->HP = Explorador->HP + 4;
    if( Explorador->HP > 60 )
        Explorador->HP = 60;
    (*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo = personagem;
}

int react_gnome(Lista **nivel, player *Explorador, int L, int A){
    setlocale(LC_ALL,"Portuguese");
    gotoxy(L+5,23);
    printf("                                         ");
    gotoxy(L+5,25);
    printf("                                           ");
    gotoxy(L+5,27);
    printf("                                  ");
    gotoxy(L+5,29);
    printf("          ");

    int ouro_perdido = 3 + rand()%8;
    int ouro_ganho = rand()%5;
    int vida_perdida = rand()%13;

    gotoxy(L+5,13);
    printf("Você acabou de pisar em um gnomo!");
    gotoxy(L+5,15);
    printf("Ele parece estar bem puto com você...");
    gotoxy(L+5,17);
    printf("Gnomo: Me pague %d moedas ou vou morder sua perna",ouro_perdido);
    gotoxy(L+5,19);
    printf("Aperte F para matar o gnomo e pegar a moeda");
    gotoxy(L+5,21);
    printf("Ou aperte P para pagá-lo e deixar você em paz");
    char c = 's';
    inicio:
    fflush(stdin);
    c = getch();
    switch(tolower(c)){
        case 'f':
            Explorador->HP=(Explorador->HP)-vida_perdida;
            if((Explorador->HP)<0)
                return 1;
            Explorador->gold = Explorador->gold + 1 + ouro_ganho;
            gotoxy(L+5,23);
            printf("Você matou o gnomo e levou %d moedas dele",ouro_ganho+1);
            gotoxy(L+5,25);
            printf("Mas durante a briga, você perdeu %d de vida",vida_perdida);
            gotoxy(L+5,27);
            printf("Você cospe em seu cadáver e diz...");
            gotoxy(L+5,29);
            printf("Seu bostão");
            break;
        case 'p':
            if( (Explorador->gold) < ouro_perdido ){
                gotoxy(L+5,23);
                printf("Como você não tinha %d moedas,",ouro_perdido);
                gotoxy(L+5,25);
                printf("o gnomo levou tudo e te mordeu");
                Explorador->HP = Explorador->HP - (ouro_perdido-Explorador->gold);
                Explorador->gold=0;
            }
            else
                Explorador->gold=(Explorador->gold)-ouro_perdido;
            break;
        default:
            goto inicio;
    }
    (*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo = personagem;
    setlocale(LC_ALL,"C");
    return 0;
}



int movimento(Lista **nivel, terreno **mapa, player *Explorador,int L,int A){

    int key = 0;
    fflush(stdin);
    key = getch();

//    if(key == KEY_UP){
    if( tolower(key) == 'w' || tolower(key) == 'i' ){
        (*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo = chao;
        *(Explorador->pos_Y) = *(Explorador->pos_Y) - 1;
        ///react_bedrock
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == bedrock)
            *(Explorador->pos_Y) = *(Explorador->pos_Y) + 1;
        ///react_wall
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == parede)
            *(Explorador->pos_Y) = *(Explorador->pos_Y) + 1;
        ///react_gold
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == ouro)
            (Explorador->gold)++;
        ///react_gnome
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == gnome)
            return react_gnome(nivel,Explorador,L,A);
        ///react_potion
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == potion)
            react_potion(nivel,Explorador);
        (*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo = personagem;

        return 0;
    }

//    if(key == KEY_DOWN){
    if(tolower(key) == 's' || tolower(key) == 'k'){
        (*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo = chao;
        *(Explorador->pos_Y) = *(Explorador->pos_Y) + 1;
        ///react_bedrock
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == bedrock)
            *(Explorador->pos_Y) = *(Explorador->pos_Y) - 1;
        ///react_wall
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == parede)
            *(Explorador->pos_Y) = *(Explorador->pos_Y) - 1;
        ///react_gold
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == ouro)
            (Explorador->gold)++;
        ///react_gnome
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == gnome)
            return react_gnome(nivel,Explorador,L,A);
        ///react_potion
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == potion)
            react_potion(nivel,Explorador);
        (*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo = personagem;
        return 0;
    }

//    if(key == KEY_RIGHT){
    if(tolower(key) == 'd' || tolower(key) == 'l' ){
        (*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo = chao;
        *(Explorador->pos_X) = *(Explorador->pos_X) + 1;
        ///react_bedrock
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == bedrock)
            *(Explorador->pos_X) = *(Explorador->pos_X) - 1;
        ///react_wall
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == parede)
            *(Explorador->pos_X) = *(Explorador->pos_X) - 1;
        ///react_gold
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == ouro)
            (Explorador->gold)++;
        ///react_gnome
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == gnome)
            return react_gnome(nivel,Explorador,L,A);
        ///react_potion
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == potion)
            react_potion(nivel,Explorador);
        (*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo = personagem;
        return 0;
    }

//    if(key == KEY_LEFT){
    if(tolower(key) == 'a' || tolower(key) == 'j'){
        (*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo = chao;
        *(Explorador->pos_X) = *(Explorador->pos_X) - 1;
        ///react_bedrock
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == bedrock)
            *(Explorador->pos_X) = *(Explorador->pos_X) + 1;
        ///react_wall
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == parede)
            *(Explorador->pos_X) = *(Explorador->pos_X) + 1;
        ///react_gold
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == ouro)
            (Explorador->gold)++;
        ///react_gnome
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == gnome)
            return react_gnome(nivel,Explorador,L,A);
        ///react_potion
        if((*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo == potion)
            react_potion(nivel,Explorador);
        (*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo = personagem;
        return 0;
    }

    if(key == KEY_ENTER){
        if( *(Explorador->pos_X) == *((*nivel)->endX) && *(Explorador->pos_Y) == *((*nivel)->endY) ){
            if( (*nivel)->proximo == NULL )
                init_Level(nivel,&mapa,&Explorador,&L,&A);
            system("cls");
            (*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo = chao;
            (*nivel) = (*nivel)->proximo;
            *(Explorador->pos_X) = *((*nivel)->spawnX);
            *(Explorador->pos_Y) = *((*nivel)->spawnY);
            (*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo = personagem;
            print_map(*nivel,L,A);
            return 0;
        }
        if( *(Explorador->pos_X) == *((*nivel)->spawnX) && *(Explorador->pos_Y) == *((*nivel)->spawnY) ){
            if( (*nivel)->anterior == NULL )
                return 0;
            system("cls");
            (*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo = chao;
            (*nivel) = (*nivel)->anterior;
            *(Explorador->pos_X) = *((*nivel)->endX);
            *(Explorador->pos_Y) = *((*nivel)->endY);
            (*nivel)->mapa[*(Explorador->pos_X)][*(Explorador->pos_Y)].tipo = personagem;
            print_map(*nivel,L,A);
            return 0;
        }
    }

//    if(key == KEY_BACKSPACE){
//        if( *(Explorador->pos_X) == *((*nivel)->spawnX) && *(Explorador->pos_Y) == *((*nivel)->spawnY) ){
//            if( (*nivel)->anterior == NULL )
//                return 0;
//            system("cls");
//            (*nivel) = (*nivel)->anterior;
//            init_player(&Explorador,nivel);
//            print_map(*nivel,L,A);
//        }
//    }

    if(key == KEY_ESC && (*(Explorador->pos_X) == *((*nivel)->spawnX) && *(Explorador->pos_Y) == *((*nivel)->spawnY)) ){
        system("cls");
        exit_current_game(*nivel,Explorador);
        return 1;
    }

    return 0;
}
