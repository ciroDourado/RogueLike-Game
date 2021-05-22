#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <locale.h>

#include "cores.h"
#include "Mapa.h"
#include "Personagem.h"
#include "Fisica.h"
#include "tristto.h"
#include "BancoDados.h"

void fullscreen()
{
    keybd_event(VK_MENU,0x38,0,0);
    keybd_event(VK_RETURN,0x1c,0,0);
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

int main(){
//    int escolha=0;
//
//    while(escolha!=1){
//            escolha=escolhaDoMenu();
//            if (escolha==4)
//                goto fim;
//    }

//    fullscreen();
    inicializaTela("Roguelike Engine");
//    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE),CONSOLE_FULLSCREEN_MODE,0);
    srand(time(NULL));

    Lista *nivel = NULL;

    terreno **mapa = NULL;
    terreno **visao = NULL;
    player *Explorador = NULL;

    int a = Largura + 2*(limiteCampoDeVisao+1);
    int b = Altura + 2*(limiteCampoDeVisao+1);

    printf("\nline of sight status:\n");
    int lim_visao = 3 + 2*limiteCampoDeVisao;
    init_matriz(&visao,lim_visao,lim_visao);

    char slot1[100] = "", slot2[100] = "", slot3[100] = "", loaded[100] = "";




    char opcao = 'y';
    while(opcao != '4'){
        menu:
        system("cls");
        printf("\n\n");
        SetColor(14);
        printf("------------------------------------SEJA BEM VINDO----------------------------------------- \n\n\n\n\n");
        SetColor(14);
        printf("                              1.");
        SetColor(15);
        printf("NOVO JOGO\n\n");
        SetColor(14);
        printf("                              2.");
        SetColor(15);
        printf("CARREGAR JOGO SALVO\n\n");
        SetColor(14);
        printf("                              3.");
        SetColor(15);
        printf("INSTRUCOES\n\n");
        SetColor(14);
        printf("                              4.");
        SetColor(15);
        printf("SAIR \n\n");
        setlocale(LC_ALL,"Portuguese");
        printf("\n\n\n\n\n\n");
        printf("                               Desenvolvedores:\n\n");
        printf("                           Ciro Dourado de Oliveira\n\n");
        printf("                              Felipe Scandelari\n\n");
        printf("                         Engenharia Eletrônica - UTFPR\n\n\n\n");
        printf("                            Professor/Orientador:\n\n");
        printf("                                Daniel Rossato\n\n");
        setlocale(LC_ALL,"C");

        opcao = getch();
        switch(opcao){
            case '1':
                nivel = NULL;
                mapa = NULL;
                Explorador = NULL;
                init_Level(&nivel,&mapa,&Explorador,&a,&b);

                game:
                print_map(nivel,a,b);

                int saida = 0;
                while( saida != 1 ){
                    atualiza_line_of_sight(visao,Explorador,nivel);
                    processoLOS(&visao,&nivel,Explorador);
                    while( !kbhit() )
                        draw_matriz(nivel,visao,Explorador,a);
                    saida = movimento(&nivel,mapa,Explorador,a,b);

                    if( Explorador->gold >= 30 ){
                        setlocale(LC_ALL,"Portuguese");
                        system("cls");
                        gotoxy(0,1);
                        printf("\n\nParabéns, você venceu! :D\n\n\n\n\n\n");
                        system("pause");
                        setlocale(LC_ALL,"C");
                        saida = 1;
                    }
                    if( Explorador->HP <= 0){
                        setlocale(LC_ALL,"Portuguese");
                        system("cls");
                        gotoxy(0,1);
                        printf("\n\nGame over\n\n\n\n\n\n");
                        system("pause");
                        setlocale(LC_ALL,"C");
                        saida = 1;
                    }
                }
                break;

            case '2':
                system("cls");
                search_game_directory(slot1,slot2,slot3);
                FILE *arq1 = NULL, *arq2 = NULL, *arq3 = NULL;
                arq1 = fopen(slot1,"r+");
                arq2 = fopen(slot2,"r+");
                arq3 = fopen(slot3,"r+");

                choose:

                printf("\nJogos salvos:\n\n");

                if( arq1 == NULL && arq2 == NULL && arq3 == NULL ){
                    setlocale(LC_ALL,"Portuguese");
                    printf("\n   Não há jogos salvos\n");
                    printf("\n   Aperte qualquer tecla para voltar ao menu\n");
                    char z;
                    z = getch();
                    setlocale(LC_ALL,"C");
                    goto menu;
                }

                if(arq1 == NULL)
                    printf("\t1. Slot1\n");
                else{
                    printf("\t1. ");
                    puts(slot1);
                }
                if(arq2 == NULL)
                    printf("\t2. Slot2\n");
                else{
                    printf("\t2. ");
                    puts(slot2);
                }
                if(arq3 == NULL)
                    printf("\t3. Slot3\n");
                else{
                    printf("\t3. ");
                    puts(slot3);
                }

                FILE *arq = NULL;

                setlocale(LC_ALL,"Portuguese");

                printf("\nEscolha o slot que você deseja carregar\n");
                printf("\nOu aperte qualquer tecla para voltar ao menu principal\n");
                char i;
                i = getch();
                switch(i){
                    case '1':
                        if( arq1 != NULL ){
                            strcpy(loaded,slot1);
                            arq = arq1;
                            break;
                        }
                        else{
                            system("cls");
                            printf("\nNão é possível acessar o slot!\n");
                            goto choose;
                        }
                    case '2':
                        if( arq2 != NULL ){
                            strcpy(loaded,slot2);
                            arq = arq2;
                            break;
                        }
                        else{
                            system("cls");
                            printf("\nNão é possível acessar o slot!\n");
                            goto choose;
                        }
                    case '3':
                        if( arq3 != NULL ){
                            strcpy(loaded,slot3);
                            arq = arq3;
                            break;
                        }
                        else{
                            system("cls");
                            printf("\nNão é possível acessar o slot!\n");
                            goto choose;
                        }
                    default:
                        goto menu;
                }
                setlocale(LC_ALL,"C");

                if( arq == NULL )
                    printf("ERRO");
                else
                    printf("carregando...");

                nivel = NULL;
                mapa = NULL;
                Explorador = NULL;

                init_Level(&nivel,&mapa,&Explorador,&a,&b);

                rewind(arq);

                fscanf(arq,"%d %d",&Explorador->HP,&Explorador->gold);

                int j, k;

                while( !feof(arq) ){
                    fscanf(arq,"%d %d %d %d",nivel->spawnX,nivel->spawnY,nivel->endX,nivel->endY);
                    for( k = 0 ; k < 2 ; k++ ){
                        for( j = 0 ; j < b ; j++ ){
                            for( i = 0 ; i < a ; i++ ){
                                if( k == 0 )
                                    fscanf(arq,"%d ",&(mapa[i][j].tipo));
                                if( k == 1 )
                                    fscanf(arq,"%d ",&(mapa[i][j].explorado));
                            }
                        }
                    }
                    init_Level(&nivel,&mapa,&Explorador,&a,&b);
                    nivel = nivel->proximo;
                }

                while( nivel->anterior != NULL )
                    nivel = nivel->anterior;
                *(Explorador->pos_X) = *(nivel->spawnX);
                *(Explorador->pos_Y) = *(nivel->spawnY);


                fclose(arq1);
                fclose(arq2);
                fclose(arq3);
                fclose(arq);

                goto game;

            case '3':
                screen:
                system("cls");
                printf("\n");
                SetColor(12);
                printf("                            -> ->  I N S T R U C O E S  <- <- \n\n");
                SetColor(15);
                printf("    OLA JOGADOR. SUA MISSAO EH COLETAR 30 MOEDAS - FEITAS DO OURO MAIS PURO JA ENCONTRADO NA TERRA.\n\n");
                printf("    MAS VOCE NAO EH O UNICO ATRAS DELAS!!!\n ");
                printf("   GNOMOS VIOLENTOS ESTAO POR TODA PARTE DISPOSTOS A ARRISCAR A VIDA PELA MOEDA PRECIOSA.\n");
                SetColor(12);
                printf("\n-------------------------------------MOVIMENTACAO------------------------------------------------------\n\n");
                SetColor(14);
                printf("                                          (CIMA)\n");
                SetColor(15);
                printf("                                          W ou I\n\n");
                SetColor(14);
                printf("                     (ESQUERDA)                                  (DIREITA)\n");
                SetColor(15);
                printf("                       A ou J                                     D ou L\n\n");
                SetColor(14);
                printf("                                         (BAIXO)\n");
                SetColor(15);
                printf("                                         S ou K\n\n\n");

                printf("   QUANDO ENCONTRAR UM GNOMO: \n\n");
                SetColor(14);
                printf("         CLIQUE (F) PARA LUTAR");
                SetColor(15);
                 printf(" ou ");
                 SetColor(14);
                 printf("CLIQUE (P) PARA FUGIR");
                  SetColor(15);
                  printf(" - PERDERA MOEDAS CASO ESCOLHA FUGIR, MAS NAO SOFRERA DANO.\n");
                SetColor(12);
                printf("\n              PRESTE ATENCAO: CASO ESTEJA COM POUCA VIDA, COLETE POCOES DE VIDA ESPALHADAS PELO MAPA!!! ");
                SetColor(15);
                printf("\n\n\n                                   BOA SORTE!!!!\n\n");

                printf("  --> Aperte ENTER para voltar ao menu inicial.\n");

                int key = 0;
                fflush(stdin);
                key = getch();
                if (key == KEY_ENTER)
                    goto menu;
                else
                    goto screen;
            case '4':
                SetColor(14);
                printf("                   ATE LOGO!!!\n\n\n");
                SetColor(15);
                break;
            default:
                goto menu;
        }
    }

    finalizaTela();
    gotoxy(0,0);
    system("pause");
    return 0;

}
