#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <allegro5/allegro_font.h>

#define DEBUG //définir si en phase de débogage

#define GAME_WIDTH 400
#define GAME_HEIGHT 400
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 500
#define RESSOURCES_PATH

/*********************
 * *** Couleurs ******
 * *******************
 */
#define WHITE al_map_rgb( 255, 255, 255)

/**********************************
 * *** Enumerations jugés utiles **
 * ********************************
 */
enum Motif
{
    CERCLE, CROIX
};
typedef enum Motif Motif;
enum Mode
{
    SOLO, MULTI
};
typedef enum Mode Mode;

void error(const char *err);
void initGame(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **queue);
void loopGame(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *queue);
void destroyGame(ALLEGRO_DISPLAY **display);

void draw_motif(int x, int y, int w, int h, Motif motif);
void draw_x(int x1, int y1, int x2, int y2);
bool checkWin(bool draw);
bool checkFull();
void debugBoard();
void newGame(int scoreX, int scoreO);
void updatesScorePlayers(int scoreX, int scoreY);
int minimax();
int score(int depth);


extern int onmove;
extern char board[3][3];
extern char firstPlayer;
extern ALLEGRO_FONT *openSans12;
extern Mode mode;


#endif // GAME_H_INCLUDED
