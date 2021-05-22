#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

///tipos de terreno/elementos----
#define vazio 0
#define bedrock 1
#define chao 2
#define parede 3
#define personagem 4
#define ouro 5
#define gnome 6
#define potion 7
///------------------------------

#define Largura 90
#define Altura 50

#define limiteCampoDeVisao 7

typedef struct terreno{
    ///definicao de explorado
    /// 1 se ja foi explorado, caso contrario 0
    int explorado;
    ///definicao de visivel
    /// 1 se o elemento é visivel, caso contrario 0
    int visivel;
    int tipo;
    int B;
    int H;
    int aux;
}terreno;

typedef struct player{
    int *pos_X;
    int *pos_Y;
    int gold;
    int HP;
}player;

typedef struct Lista{
    terreno **mapa;
    int *spawnX;
    int *spawnY;
    int *endX;
    int *endY;
    struct Lista *proximo;
    struct Lista *anterior;
} Lista;

void init_matriz(terreno ***mapa, int L, int A);
void draw_matriz(Lista *niveis, terreno **visao, player *Explorador, int L);

void put_bedrock(terreno ***mapa, int L, int A);
void put_walls(terreno ***mapa, int L, int A);
void put_cavern_paths(terreno ***mapa, int posX, int posY);
int call_put_paths(terreno ***mapa, int L, int A, int spawn_X, int fator);
void put_items_ground_enemies(terreno ***mapa, int x, int y);

void init_Level(Lista **nivel, terreno ***mapa, player **Explorador, int *L, int *A);

int add(Lista **caverna, terreno **mapa, int *spawnX, int *spawnY, int *endX, int *endY);
int get(Lista *caverna, int posicao);
int tamanho(Lista *caverna);

void print_map(Lista *nivel,int L,int A);

int percorre_chao(terreno ***mapa, int sX, int sY, int eX, int eY, int L, int A, int *key);

#endif // MAPA_H_INCLUDED
