#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define GAME_WIDTH 400
#define GAME_HEIGHT 400

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

void error(const char *err);
void initGame(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **queue, int w, int h);
void loopGame(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *queue);
void destroyGame(ALLEGRO_DISPLAY **display);

void draw_motif(int x, int y, int w, int h, Motif motif);
void draw_x(int x1, int y1, int x2, int y2);



#endif // GAME_H_INCLUDED
