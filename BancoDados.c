#include <stdio.h>
#include <dirent.h>  ///* struct DIR, struct dirent  */
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

#include "BancoDados.h"

int find_txt_file(char *c){
    char *txt = ".txt";
    int l = strlen(c);
    if( strcmp(&c[l-4],txt) == 0 )
        return 0;
    else
        return 1;
}

void search_game_directory(char slot1[],char slot2[],char slot3[]){
    DIR *id_pasta; ///* ponteiro para o fluxo correspondente a pasta a ser analisada */
    char *nome_pasta = "."; ///* pasta a ser listada . No caso, é a pasta atual onde for executado este programa */
    struct dirent *id_nome; ///* ponteiro para um dos nomes da pasta */

    id_pasta = opendir(nome_pasta); ///* abrir o fluxo para a pasta desejada e retornar um ponteiro para esse fluxo */

    int i = 0;
    if(id_pasta != NULL){ ///* se a pasta existir */
        //id_nome = readdir(id_pasta); ///* ler um nome da pasta sendo varrida. Uma vez lido, automaticamente, a próxima leitura será do próximo nome na pasta */
        do{
            id_nome = readdir(id_pasta);
            if( i == 0 ){
               if( find_txt_file(id_pasta->dd_dta.name) == 0 ){
                    strcpy(slot1,id_pasta->dd_dta.name);
                    i++;
               }
               continue;
            }
            if( i == 1 ){
               if( find_txt_file(id_pasta->dd_dta.name) == 0 ){
                    strcpy(slot2,id_pasta->dd_dta.name);
                    i++;
               }
               continue;
            }
            if( i == 2 ){
               if( find_txt_file(id_pasta->dd_dta.name) == 0 ){
                    strcpy(slot3,id_pasta->dd_dta.name);
                    break;
               }
               continue;
            }
        }while( id_nome != NULL );///* repetir enquanto houver nomes não lidos no fluxo corresponde a pasta sendo varrida */

    }
    closedir(id_pasta);  ///* desalocar todos os recursos alocados em id_pasta */
}

void set_file_name(char n[]){
    printf("Digite o nome do arquivo a ser salvo: ");
    gets(n);

    char txt[5] = ".txt";
    strcat(n,txt);
}

void exit_current_game(Lista *nivel, player *Explorador){

    char n[100];

    char slot1[100] = "", slot2[100] = "", slot3[100] = "";
    search_game_directory(slot1,slot2,slot3);

    FILE *arq1 = NULL, *arq2 = NULL, *arq3 = NULL;
    arq1 = fopen(slot1,"r+");
    arq2 = fopen(slot2,"r+");
    arq3 = fopen(slot3,"r+");

    printf("\nJogos salvos:\n\n");

    if(arq1 == NULL)
        printf("\t1. Slot1\n");
    else{
        printf("\t");
        puts(slot1);
    }
    if(arq2 == NULL)
        printf("\t2. Slot2\n");
    else{
        printf("\t");
        puts(slot2);
    }
    if(arq3 == NULL)
        printf("\t3. Slot3\n");
    else{
        printf("\t");
        puts(slot3);
    }

    printf("\nSalvar jogo?\n\tS - sim\n\tN - não\n\n");

    char c = 'y';
    while( tolower(c) != 'n' ){
        fflush(stdin);
        c = getch();
        switch(tolower(c)){
            case 's':
                if( arq1 == NULL || arq2 == NULL || arq3 == NULL ){
                    set_file_name(n);
                    system("cls");
                    new_save(n,nivel,Explorador);
                    goto fim;
                }
                if( arq1 != NULL && arq2 != NULL && arq3 != NULL ){
                    slot:
                    printf("Escolha o slot em que você deseja sobrescrever (1,2,3)\n\n");
                    char i;
                    i = getch();
                    switch(i){
                        case '1':
                            fclose(arq1);
                            remove(slot1);
                            set_file_name(n);
                            system("cls");
                            new_save(n,nivel,Explorador);
                            goto fim2;
                        case '2':
                            fclose(arq2);
                            remove(slot2);
                            set_file_name(n);
                            system("cls");
                            new_save(n,nivel,Explorador);
                            goto fim2;
                        case '3':
                            fclose(arq3);
                            remove(slot3);
                            set_file_name(n);
                            system("cls");
                            new_save(n,nivel,Explorador);
                            goto fim2;
                        default:
                            goto slot;
                    }
                }
            case 'n':
                break;
        }
    }
    fim:
    fclose(arq1);
    fclose(arq2);
    fclose(arq3);

    fim2:
    return;
}

void new_save(char filename[], Lista *nivel, player *Explorador){

    FILE *arq = NULL;
    arq = fopen(filename,"w+");

    fprintf(arq,"%d %d \n",Explorador->HP,Explorador->gold);
    int i, j;

    while( nivel->anterior != NULL )
        nivel = nivel->anterior;

    while( nivel != NULL ){
        fprintf(arq,"%d %d %d %d\n",*(nivel->spawnX),*(nivel->spawnY),*(nivel->endX),*(nivel->endY));
        for( j = 0 ; j < nivel->mapa[0][0].H ; j++ ){
            for( i = 0 ; i < nivel->mapa[0][0].B ; i++ ){
                fprintf(arq,"%d ",nivel->mapa[i][j].tipo);
            }
            fprintf(arq,"\n");
        }
        for( j = 0 ; j < nivel->mapa[0][0].H ; j++ ){
            for( i = 0 ; i < nivel->mapa[0][0].B ; i++ ){
                fprintf(arq,"%d ",nivel->mapa[i][j].explorado);
            }
            fprintf(arq,"\n");
        }

        nivel = nivel->proximo;
    }

    fclose(arq);
    return;
}
