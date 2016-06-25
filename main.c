/*
 * ************* Tic Tac Toe ***************
 *
 * Ecrit par Yassir Karroum [ukarroum17@gmail.com]
 * Le 25 juin 2016
 *
 * Un simple jeu de tic tac toe implémenté en C avec la bibliothéque Allegro5
 * Il utilise l'algorithme MiniMax pour la partie joueur contre machine
 * L'algorithme en question a été altéré dans le but de laisser des possibilités où le joueur
 * pourra éventuellement gagner.
 */

#include <allegro5/allegro.h>
#include <stdio.h>

#include "game.h"

int main()
{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue;

    initGame(&display, &queue);
    loopGame(display, queue);
    destroyGame(&display);

    //printf("%d", minimax());
    return 0;
}
