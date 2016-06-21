#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "game.h"

void error(const char *err)
{
    ALLEGRO_DISPLAY *dialogErr;
    dialogErr=al_is_system_installed()?al_get_current_display():NULL;
    al_show_native_message_box(dialogErr,"ERREUR", "Erreur", err,NULL,0);
    exit(EXIT_FAILURE);
}
void initGame(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **queue, int w, int h)
{
    /*******************************
     * ***** Initialisation ********
     * *****************************
     */
    if(!al_init())
        error("al_init()");

    *display = al_create_display(w, h);

    if(!*display)
        error("creation display");

    al_set_window_title(*display, "Tic Tac Toe");

    al_clear_to_color(al_map_rgb(0, 0, 0));

    if(!al_install_mouse())
        error("al_install_keyboard()");

    /************************
     * ** Evenements ********
     * **********************
     */

    *queue = al_create_event_queue();

    if(!*queue)
        error("al_create_event_queue");

    al_register_event_source(*queue, al_get_display_event_source(*display));
    al_register_event_source(*queue, al_get_mouse_event_source());
    /*************************************
     * ***** Tracer les lignes blanches **
     * ***********************************
     */
    if(!al_init_primitives_addon())
        error("al_primitives_addon()");

    al_draw_line(w/3, h*0.05, w/3, h*0.95, WHITE, 10);
    al_draw_line(2*(w/3), h*0.05, 2*(w/3), h*0.95, WHITE, 10);

    al_draw_line(w*0.05, h/3, w*0.95, h/3, WHITE, 10);
    al_draw_line(w*0.05, 2*(h/3), w*0.95, 2*(h/3), WHITE, 10);

    al_flip_display();

}
void loopGame(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *queue, char board[3][3])
{
    int fin = 1;
    int onmove = 0;
    while(fin)
    {
        ALLEGRO_EVENT event = {0};

        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fin = 0;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if(event.mouse.button == 1)
                {
                    if(onmove%2 == 0) {
                        draw_motif(event.mouse.x / (GAME_WIDTH / 3),
                                   event.mouse.y / (GAME_HEIGHT / 3),
                                   GAME_WIDTH,
                                   GAME_HEIGHT,
                                   CROIX);
                        board[event.mouse.x / (GAME_WIDTH / 3)][event.mouse.y / (GAME_HEIGHT / 3)] = 'X';
                    }
                    else {
                        draw_motif(event.mouse.x / (GAME_WIDTH / 3),
                                   event.mouse.y / (GAME_HEIGHT / 3),
                                   GAME_WIDTH,
                                   GAME_HEIGHT,
                                   CERCLE);
                        board[event.mouse.x / (GAME_WIDTH / 3)][event.mouse.y / (GAME_HEIGHT / 3)] = 'O';
                    }
                    onmove++;

                    #ifdef DEBUG
                        debugBoard(board);
                    #endif
                }
                break;
        }
    }
}
void destroyGame(ALLEGRO_DISPLAY **display)
{
    al_destroy_display(*display);
}
void draw_motif(int x, int y, int w, int h, Motif motif)
{
    /*
     * Dessine un motif (X ou O)
     *
     * x : ligne
     * y : colonne
     * w : largeur de la grille
     * h : hauteur de la grille
     */
    if(motif == CROIX)
        draw_x(w*0.1 + x*(w/3)*0.9, h*0.1 + y*(h/3)*0.9, (w/3)*0.90 + x*(w/3)*0.9, (h/3)*0.90 + y*(h/3)*0.9);
    else if(motif == CERCLE)
        al_draw_circle(w/6 + x*(w/3)*0.9, h/6 + y*(h/3), (w/6)*0.6, WHITE, 10);

    al_flip_display();
}
void draw_x(int x1, int y1, int x2, int y2)
{
    /*
     * Dessine un X
     *
     * (x1, y1) : cordonnées de l'extrémité haut gauche du x
     * (x2, y2) : cordonnées de l'extrémité bas droite du x
     */
    al_draw_line(x1, y1, x2, y2, WHITE, 10);
    al_draw_line(x2, y1, x1, y2, WHITE, 10);
}
void debugBoard(char board[3][3])
{
    /*
     * Affiche la grille du jeu sous une forme plus plaisante à l'oeil
     * Pour faciliter le débogage
     *
     *  Ex :
     *
     *   X|O|
     *    |X|
     *   X| |O
     */
    int i, j;
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            printf("%c", board[i][j]);
            if(j != 2)
                printf("|");
            else
                printf("\n");
        }
    }
}