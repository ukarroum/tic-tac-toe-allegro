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

    /************************
     * ** Evenements ********
     * **********************
     */

    *queue = al_create_event_queue();

    if(!*queue)
        error("al_create_event_queue");

    al_register_event_source(*queue, al_get_display_event_source(*display));

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
void loopGame(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *queue)
{
    while(1)
    {
        ALLEGRO_EVENT event = {0};

        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
    }
}
void destroyGame(ALLEGRO_DISPLAY **display)
{
    al_destroy_display(*display);
}