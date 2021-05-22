#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<pthread.h>
#include "tristto.h"

struct _Tela {
    CHAR_INFO buffer_tela[ALTURA_TELA*LARGURA_TELA];
    COORD characterBufferSize;
    COORD characterPosition;
    SMALL_RECT consoleWriteArea;
    HANDLE wHnd;
    HANDLE rHnd;
    pthread_t pth;
    char running;
    clock_t tempo;
    unsigned char keyState[256];
};


static struct _Tela _tela_;
static void *backgroundUpdate();
void setaFonteVarredura();

BOOL WINAPI SetCurrentConsoleFontEx(
   HANDLE               hConsoleOutput,
   BOOL                 bMaximumWindow,
   CONSOLE_FONT_INFOEX* lpConsoleCurrentFontEx
);


void atualizaTela() {
   WriteConsoleOutputA(
       _tela_.wHnd               , 
       _tela_.buffer_tela        , 
       _tela_.characterBufferSize, 
       _tela_.characterPosition  , 
       &(_tela_.consoleWriteArea)
    );
} // end atualizaTela


void imprimeMapa(int x0, int y0, char *mapa, int *coresFonte, int *coresFundo, int altura, int largura) {
    int x, y;
    for(y=0;y<altura;y++) {
        for(x=0;x<largura;x++) {
            tputchar(mapa[y*largura + x], x0+x, y0+y, coresFonte[y*largura + x], coresFundo[y*largura+x]);
        }
    }
} // end imprimeMapa


void tprintf(int x, int y, COR corLetra, COR corFundo, const char* s, ...) {
    va_list args;
    int i=0, tam;
    char buffer[ALTURA_TELA*LARGURA_TELA]; 
    va_start(args, s);

    //gera a string formatada
    tam = vsprintf(buffer, s, args);
    va_end(args);

    while(tam-- && tputchar(buffer[i++], x++, y, corLetra, corFundo));
} // end tprintf


void tprintf_v(int x, int y, COR corLetra, COR corFundo, const char* s, ...) {
    va_list args;
    int i=0, tam;
    char buffer[ALTURA_TELA*LARGURA_TELA]; 
    va_start(args, s);

    //gera a string formatada
    tam = vsprintf(buffer, s, args);
    va_end(args);

    while(tam-- && tputchar(buffer[i++], x, y++, corLetra, corFundo));
} // end tprintf_v


int tscanf(int x, int y, COR corLetra, COR corFundo, const char* s, ...) {
    va_list args;
    va_start(args, s);
    int retorno;

    char buffer[LARGURA_TELA]; //nao aceita strings maiores que a largura da tela

    while(kbhit()) getch(); //limpa o buffer poluido por leTecla

    char c;
    int i=0;
    do {
        c = getch();
        if(c=='\b') {
            if(i>0) tputchar(' ', x+ --i, y, corLetra, corFundo);
        }
        else if(c!='\r' && c>31) {
            tputchar(c, x+i, y, corLetra, corFundo);
            buffer[i++] = c;
        }

    } while(c!='\r'); //enquanto nao recebe um ENTER

    buffer[i] = '\0';

    retorno = vsscanf(buffer, s, args);
    va_end(args);
    return retorno;
} // end tscanf


void tgets(int x, int y, COR corLetra, COR corFundo, char *str) {
    while(kbhit()) getch(); //limpa o buffer poluido por leTecla
    char c;
    int i=0;
    do {
        c = getch();
        if(c=='\b') {
            if(i>0) tputchar(' ', x+ --i, y, corLetra, corFundo);
        }
        else if(c!='\r' && c>31) {
            tputchar(c, x+i, y, corLetra, corFundo);
            str[i++] = c;
        }
    } while(c!='\r'); //enquanto nao recebe um ENTER
    str[i]='\0';
} // end tgets


char tgetch() {
    while(kbhit()) getch(); //limpa o buffer poluido por leTecla
    return getch();
} // end tgetch


char tputchar(unsigned char c, int posX, int posY, COR corLetra, COR corFundo) {
    if(posX < LARGURA_TELA && posY < ALTURA_TELA && posX >= 0 && posY >= 0) {
        _tela_.buffer_tela[LARGURA_TELA*posY + posX].Attributes = (corLetra & 0x0F) | ((corFundo & 0x0F) << 4);
        _tela_.buffer_tela[LARGURA_TELA*(posY++) + posX].Char.AsciiChar = c;
        return c;
    }
    else return 0;
} // end tputchar


void limpa_tela(COR corFundo) {
    int x=LARGURA_TELA*ALTURA_TELA;
    while(x--) {
        _tela_.buffer_tela[x].Char.AsciiChar = ' ';
        _tela_.buffer_tela[x].Attributes = ((corFundo & 0x0F) << 4);
    }
} // end limpa_tela


void setaFonteVarredura() {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof cfi;
    cfi.nFont = 0;
    cfi.dwFontSize.X = 8;
    cfi.dwFontSize.Y = 8;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;

    wcscpy(cfi.FaceName, L"Terminal");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
} // end setaFonteVarredura


void inicializaTela(const char tituloJanela[]) {
    int x, y;
    HANDLE wHnd;
    HANDLE rHnd;

    SMALL_RECT windowSize = {0, 0, LARGURA_TELA - 1, ALTURA_TELA - 1};
    COORD characterBufferSize = {LARGURA_TELA, ALTURA_TELA};
    COORD characterPosition = {0,0};
    SMALL_RECT consoleWriteArea = {0, 0, LARGURA_TELA-1, ALTURA_TELA -1};
    COORD bufferSize = {LARGURA_TELA, ALTURA_TELA};
    CONSOLE_CURSOR_INFO cursor;

    system("cls");

    // pega o handle do console
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);

    //esconde o cursor
    cursor.bVisible = 0;
    cursor.dwSize = 100;
    SetConsoleCursorInfo(wHnd, &cursor);

    //muda o titulo da janela
    SetConsoleTitle(tituloJanela);

    //muda a fonte e o tamanho para Raster 8x8
    setaFonteVarredura();

    //desabilita resize da janela
    long dwStyle;
    HWND hwndGlut;
    hwndGlut = FindWindow(NULL, tituloJanela);
    dwStyle = GetWindowLong(hwndGlut, GWL_STYLE);
    dwStyle &= ~(WS_MAXIMIZEBOX | WS_SIZEBOX | WS_HSCROLL);
    SetWindowLong(hwndGlut, GWL_STYLE, dwStyle);

    //muda o tamanho da janela
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

    //muda o tamanho do buffer da janela
    SetConsoleScreenBufferSize(wHnd, bufferSize);

    //muda o tamanho da janela
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

    //guarda as informacoes na estrutura _tela_
    _tela_.wHnd = wHnd;
    _tela_.rHnd = rHnd;
    _tela_.characterBufferSize = characterBufferSize;
    _tela_.characterPosition = characterPosition;
    _tela_.consoleWriteArea = consoleWriteArea;

    //limpa o buffer da tela
    for (y = 0; y < ALTURA_TELA; ++y) {
        for (x = 0; x < LARGURA_TELA; ++x) {
            _tela_.buffer_tela[x + LARGURA_TELA * y].Char.AsciiChar = ' ';
            _tela_.buffer_tela[x + LARGURA_TELA * y].Attributes = 15;
        }
    }

//    _tela_.running = 1; //liga flag de thread de atualizacao de tela rodando
//    pthread_create(&(_tela_.pth),NULL,backgroundUpdate,NULL); //dispara thread de atualizacao
} // end inicializaTela


void finalizaTela() {
    _tela_.running = 0; //sinaliza thread de atualizacao para terminar
    pthread_join(_tela_.pth, NULL); //espera thread de atualizacao terminar
    atualizaTela(); //escreve as mudancas finais na tela
} // end finalizaTela


int lerTecla(unsigned char tecla) {
    if(_tela_.keyState[tecla]) {
        _tela_.keyState[tecla] = 0;
        return 1;
    }
    else return 0;
} // end lerTecla


static void *backgroundUpdate() {
    _tela_.tempo = clock();
    int i;
    while(_tela_.running) {
        if(((clock()-_tela_.tempo))*1000./CLOCKS_PER_SEC>500./FRAME_RATE) {
            atualizaTela();
            _tela_.tempo = clock();
            for(i=0; i<256; i++)
                if(GetAsyncKeyState(i)) _tela_.keyState[i] = 1;
                else _tela_.keyState[i] = 0;
        }
    }
    return NULL;
} // end backgroundUpdate


void guia() {
    unsigned int c;
    const char* nomes[] = {
        "PRETO", "AZUL_ESCURO", "VERDE_ESCURO", "CIANO_ESCURO", 
        "VERMELHO_ESCURO", "ROXO_ESCURO", "AMARELO_ESCURO", "CINZA_CLARO",
        "CINZA_ESCURO", "AZUL_CLARO", "VERDE_CLARO", "CIANO_CLARO", 
        "VERMELHO_CLARO", "ROXO_CLARO", "AMARELO_CLARO", "BRANCO"
    };
    char str[] = {219,219,219,219,219,219,219,219,219,219,0};

    limpa_tela(PRETO);

    //imprime tabela ascii
    for(c = 0; c<256; c++) {
        tprintf(4+12*(c/32), 4+2*(c%32), BRANCO, PRETO, "%3d - %c      ", c, c);
    }

    //imprime tabela de cores
    for(c=0;c<16;c++) {
        tprintf(120, 20+2*c, BRANCO, PRETO, " : %s", nomes[c]);
        tprintf(110, 20+2*c, c, BRANCO, str);
    }

    tprintf(59, 75, AMARELO_CLARO, PRETO, "Pressione qualquer tecla para continuar...");

    tgetch();
} // end guia
