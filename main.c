#include <allegro5/allegro.h>

#include "game.h"

int main()
{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue;

    initGame(&display, &queue, GAME_WIDTH, GAME_HEIGHT);
    loopGame(display, queue);
    destroyGame(&display);


    return 0;
}
