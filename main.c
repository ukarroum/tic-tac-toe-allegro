#include <allegro5/allegro.h>

#include "game.h"

int main()
{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue;
    char board[3][3] = {
            {'-', '-', '-'},
            {'-', '-', '-'},
            {'-', '-', '-'},
    };

    initGame(&display, &queue, GAME_WIDTH, GAME_HEIGHT);
    loopGame(display, queue, board);
    destroyGame(&display);


    return 0;
}
