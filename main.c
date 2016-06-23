#include <allegro5/allegro.h>

#include "game.h"

int main()
{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue;

    initGame(&display, &queue);
    loopGame(display, queue, SOLO);
    destroyGame(&display);


    return 0;
}
