#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <stdio.h>
#include <time.h>
#include <string.h>

#include "game.h"

int onmove = 0;
char board[3][3] = {
        {'-', '-', '-'},
        {'-', '-', '-'},
        {'-', '-', '-'},
};
ALLEGRO_FONT *openSans12 = NULL;
Mode mode = SOLO;
Diff diff = MEDIUM;

void error(const char *err)
{
    ALLEGRO_DISPLAY *dialogErr;
    dialogErr=al_is_system_installed()?al_get_current_display():NULL;
    al_show_native_message_box(dialogErr,"ERREUR", "Erreur", err,NULL,0);
    exit(EXIT_FAILURE);
}
void initGame(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **queue)
{
    /*******************************
     * ***** Initialisation ********
     * *****************************
     */
    if(!al_init())
        error("al_init()");

    *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

    if(!*display)
        error("creation display");

    al_set_window_title(*display, "Tic Tac Toe");

    if(!al_install_mouse())
        error("al_install_keyboard()");

    if(!al_install_keyboard())
        error("al_install_keyboard()");

    if(!al_init_font_addon())
        error("al_init_font_addon()");

    if(!al_init_ttf_addon())
        error("al_init_ttf_addon()");

    openSans12 = al_load_ttf_font("/home/karroum/Projets/allegro/tic-tac-toe-allegro/fonts/OpenSans-Light.ttf", 24, 0);
    if(!openSans12)
        error("al_load_font()");


    /************************
     * ** Evenements ********
     * **********************
     */

    *queue = al_create_event_queue();

    if(!*queue)
        error("al_create_event_queue");

    al_register_event_source(*queue, al_get_display_event_source(*display));
    al_register_event_source(*queue, al_get_mouse_event_source());
    al_register_event_source(*queue, al_get_keyboard_event_source());

    /*************************************
     * ***** Tracer les lignes blanches **
     * ***********************************
     */
    if(!al_init_primitives_addon())
        error("al_primitives_addon()");

    drawMenu(*queue);
    //drawGrid();

}
void drawMenu(ALLEGRO_EVENT_QUEUE *queue)
{
    ALLEGRO_FONT *openSans62;
    openSans62 = al_load_ttf_font("/home/karroum/Projets/allegro/tic-tac-toe-allegro/fonts/OpenSans-Light.ttf", 62, 0);
    if(!openSans62)
        error("al_load_font()");

    al_draw_text(openSans62, WHITE, SCREEN_WIDTH*0.1, SCREEN_HEIGHT*0.1, 0, "Tic Tac Toe");

    al_draw_text(openSans12, WHITE, SCREEN_WIDTH*0.1, SCREEN_HEIGHT*0.5, 0, "1)    Solo : Easy");
    al_draw_text(openSans12, WHITE, SCREEN_WIDTH*0.1, SCREEN_HEIGHT*0.6, 0, "2)    Solo : Medium");
    al_draw_text(openSans12, WHITE, SCREEN_WIDTH*0.1, SCREEN_HEIGHT*0.7, 0, "3)    Solo : Impossible");

    al_draw_text(openSans12, WHITE, SCREEN_WIDTH*0.1, SCREEN_HEIGHT*0.8, 0, "4)    Multiplayer");

    al_flip_display();

    loopMenu(queue);
};
void drawGrid()
{
    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_draw_line(GAME_WIDTH/3, GAME_HEIGHT*0.05, GAME_WIDTH/3, GAME_HEIGHT*0.95, WHITE, 2);
    al_draw_line(2*(GAME_WIDTH/3), GAME_HEIGHT*0.05, 2*(GAME_WIDTH/3), GAME_HEIGHT*0.95, WHITE, 2);

    al_draw_line(GAME_WIDTH*0.05, GAME_HEIGHT/3, GAME_WIDTH*0.95, GAME_HEIGHT/3, WHITE, 2);
    al_draw_line(GAME_WIDTH*0.05, 2*(GAME_HEIGHT/3), GAME_WIDTH*0.95, 2*(GAME_HEIGHT/3), WHITE, 2);

    updatesScorePlayers(0, 0);

    al_flip_display();

    srand(time(NULL));
}
void loopMenu(ALLEGRO_EVENT_QUEUE *queue)
{
    int fin = 1;
    while(fin)
    {
        ALLEGRO_EVENT event = {0};

        al_wait_for_event(queue, &event);

        switch(event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fin = 0;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_1) {
                    mode = SOLO;
                    diff = EASY;
                    fin = 0;
                    drawGrid();
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_2) {
                    mode = SOLO;
                    diff = MEDIUM;
                    fin = 0;
                    drawGrid();
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_3) {
                    mode = SOLO;
                    diff = IMPOSSIBLE;
                    fin = 0;
                    drawGrid();
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_4) {
                    mode = MULTI;
                    fin = 0;
                    drawGrid();
                }
                break;
        }
    }
}
void loopGame(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *queue)
{
    int scoreX = 0;
    int scoreO = 0;
    int fin = 1;
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
                if(event.mouse.button == 1 &&
                        board[event.mouse.y / (GAME_HEIGHT / 3)][event.mouse.x / (GAME_WIDTH / 3)] == '-')
                {
                    if(onmove%2 == 0) {
                        draw_motif(event.mouse.x / (GAME_WIDTH / 3),
                                   event.mouse.y / (GAME_HEIGHT / 3),
                                   GAME_WIDTH,
                                   GAME_HEIGHT,
                                   CROIX);
                        board[event.mouse.y / (GAME_HEIGHT / 3)][event.mouse.x / (GAME_WIDTH / 3)] = 'X';
                    }
                    else {
                        draw_motif(event.mouse.x / (GAME_WIDTH / 3),
                                   event.mouse.y / (GAME_HEIGHT / 3),
                                   GAME_WIDTH,
                                   GAME_HEIGHT,
                                   CERCLE);
                        board[event.mouse.y / (GAME_HEIGHT / 3)][event.mouse.x / (GAME_WIDTH / 3)] = 'O';
                    }
                    /* Deux cas se presentent:
                     * 1 cas : Joueur contre joueur => La condition marche pour les deux
                     * 2 cas : Joueur contre machine => cette condition ne teste que si le joueur a gagné
                     * */
                    if(checkWin(true))
                    {
                        al_show_native_message_box(display,"You Win !", "You Win !", "Vous avez gagné !",NULL,0);
                        if(onmove%2 == 0)
                            scoreX++;
                        else
                            scoreO++;
                        newGame(scoreX, scoreO);

                        continue;
                    }
                    else if(checkFull())
                    {
                        al_show_native_message_box(display,"Draw !", "Draw !", "Egalite !",NULL,0);
                        newGame(scoreX, scoreO);

                        continue;
                    }
                    if(mode == SOLO)
                    {
                        int index;

                        if(diff == EASY)
                            index = easy();
                        else if(diff == MEDIUM)
                            index = medium();
                        else if(diff == IMPOSSIBLE)
                            index = minimax();

                        draw_motif(index % 3, index / 3, GAME_WIDTH, GAME_HEIGHT, CERCLE);
                        board[index / 3][index % 3] = 'O';

                        if(checkWin(true))
                        {
                            al_show_native_message_box(display,"You Lose !", "You Lose !", "Vous avez perdu :( !",NULL,0);
                            scoreO++;
                            newGame(scoreX, scoreO);

                            continue;
                        }
                    }
                    else
                        onmove++;

                    #ifdef DEBUG
                        debugBoard();
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
        al_draw_circle(w/6 + x*(w/3)*0.9 + x*10, h/6 + y*(h/3), (w/6)*0.6, WHITE, 10);

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
void debugBoard()
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
bool checkWin(bool draw)
{
    /*
     * Permet de vérifier si un des deux joueurs à gagné
     *
     */
    int i;
    for (i = 0; i < 3; i++)
    {
        if(board[i][0] != '-' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if(draw) {
                al_draw_line(GAME_WIDTH * 0.05, (GAME_HEIGHT/3) * (i + 0.5), GAME_WIDTH * 0.95, (GAME_HEIGHT/3) * (i + 0.5), WHITE,
                         10);
                al_flip_display();
            }
            return true;
        }
        if(board[0][i] != '-' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if(draw) {
                al_draw_line((GAME_WIDTH / 3) * (i + 0.5), GAME_HEIGHT * 0.05, (GAME_WIDTH / 3) * (i + 0.5),
                             GAME_HEIGHT * 0.95, WHITE,
                             10);
                al_flip_display();
            }
            return true;
        }
    }
    if(board[0][0] != '-' && board[0][0] == board[1][1] && board[1][1] == board[2][2]){
        if(draw) {
            al_draw_line(GAME_WIDTH * 0.05, GAME_HEIGHT * 0.05, GAME_WIDTH * 0.95, GAME_HEIGHT * 0.95, WHITE,
                         10);
            al_flip_display();
        }
        return true;
    }
    if(board[0][2] != '-' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if(draw) {
            al_draw_line(GAME_WIDTH * 0.95, GAME_HEIGHT * 0.05, GAME_WIDTH * 0.05, GAME_HEIGHT * 0.95, WHITE,
                         10);
            al_flip_display();
        }
        return true;
    }
    return false;

}
bool checkFull()
{
    int i, j;
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            if(board[i][j] == '-')
                return false;
    return true;
}
void newGame(int scoreX, int scoreO)
{
    static char firstPlayer = 'X';
    int i, j;
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
            board[i][j] = '-';
    if(mode == MULTI) {
        if(firstPlayer == 'X') {
            firstPlayer = 'O';
            onmove = 1;
        }
        else
        {
            firstPlayer = 'X';
            onmove = 0;
        }
    }

    //Inistialisation de l'affichage
    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_draw_line(GAME_WIDTH/3, GAME_HEIGHT*0.05, GAME_WIDTH/3, GAME_HEIGHT*0.95, WHITE, 2);
    al_draw_line(2*(GAME_WIDTH/3), GAME_HEIGHT*0.05, 2*(GAME_WIDTH/3), GAME_HEIGHT*0.95, WHITE, 2);

    al_draw_line(GAME_WIDTH*0.05, GAME_HEIGHT/3, GAME_WIDTH*0.95, GAME_HEIGHT/3, WHITE, 2);
    al_draw_line(GAME_WIDTH*0.05, 2*(GAME_HEIGHT/3), GAME_WIDTH*0.95, 2*(GAME_HEIGHT/3), WHITE, 2);

    updatesScorePlayers(scoreX, scoreO);

    al_flip_display();
}
void updatesScorePlayers(int scoreX, int scoreO)
{
    if(mode == MULTI){
        al_draw_textf(openSans12, WHITE, SCREEN_WIDTH*0.1, GAME_HEIGHT + 10, 0, "Joueur X : %d", scoreX);
        al_draw_textf(openSans12, WHITE, SCREEN_WIDTH*0.1, GAME_HEIGHT + 50, 0, "Joueur O : %d", scoreO);
    }
    else{
        al_draw_textf(openSans12, WHITE, SCREEN_WIDTH*0.1, GAME_HEIGHT + 10, 0, "Joueur : %d", scoreX);
        al_draw_textf(openSans12, WHITE, SCREEN_WIDTH*0.1, GAME_HEIGHT + 50, 0, "Machine : %d", scoreO);
    }


    al_flip_display();
}
int minimax()
{
    /****************************************
     * Calcul le meilleur jeu pour la machine
     * et renvoie l'indice de la case que la machine devra jouer
     * pour gagner
     *
     * Les scores sont réparties comme suit :
     *
     * Gagner la partie : 10
     * Partie nulle : 0
     * Perdre la partie : -10
     */
    int i, j;
    int bestMove = -20;
    int bestI = 100, bestJ = 100;

    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(board[i][j] != '-')
                continue;

            board[i][j] = 'O';
            /********** Calcul du score par minimax *************/
            if(score(1) > bestMove)
            {
                bestI = i;
                bestJ = j;
                bestMove = score(1);
            }
            /****************************************************/
            board[i][j] = '-';

        }
    }
    return bestI*3 + bestJ;
}
int score(int depth)
{
    int i, j, bestScore;
    if(depth % 2 == 1)
        bestScore = 20;
    else
        bestScore = -20;

    if(checkWin(false))
        return depth % 2 == 1 ? 10 : -10;
    if(checkFull())
        return 0;
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(board[i][j] != '-')
                continue;

            board[i][j] = depth % 2 == 1 ? 'X' : 'O';
            /********** Calcul du score par minimax *************/
            if(depth % 2 == 1 && score(depth + 1) < bestScore)
            {
                bestScore = score(depth + 1);
            }
            else if(depth % 2 == 0 && score(depth + 1) > bestScore)
            {
                bestScore = score(depth + 1);
            }
            /****************************************************/
            board[i][j] = '-';
        }
    }

    return bestScore;
}
int easy()
{
    /**************************************
     * Le mode le plus facile
     * Choisit des cases aléatoirement
     * en vérifiant tout de meme qu'elles
     * sont bel et bien vides
     * ************************************
     */
    int r;
    do {
        r = random() % 9;
    }while(board[r/3][r%3] != '-');

    return r;

}
int medium()
{
    /**********************************
     * Un mode interemediaire qui vérifie
     * à chaque tour si il est possible
     * de gagner ou d'empecher l'autre joueur de gagner
     * **********************************
     */

    /********** Recherche de victoire ****************/
    int i;
    for(i = 0; i < 3; i++)
    {
        if(board[i][0] == '-' && board[i][1] == 'O' && board[i][2] == 'O')
            return i*3 + 0;
        if(board[i][0] == 'O' && board[i][1] == '-' && board[i][2] == 'O')
            return i*3 + 1;
        if(board[i][0] == 'O' && board[i][1] == 'O' && board[i][2] == '-')
            return i*3 + 2;

        if(board[0][i] == '-' && board[1][i] == 'O' && board[2][3] == 'O')
            return 0*3 + i;
        if(board[0][i] == 'O' && board[1][i] == '-' && board[2][3] == 'O')
            return 1*3 + i;
        if(board[0][i] == 'O' && board[1][i] == 'O' && board[2][3] == '-')
            return 2*3 + i;

    }

    //Diagonales
    if(board[0][0] == '-' && board[1][1] == 'O' && board[2][2] == 'O')
        return 0*3 + 0;
    if(board[0][0] == 'O' && board[1][1] == '-' && board[2][2] == 'O')
        return 1*3 + 1;
    if(board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == '-')
        return 2*3 + 2;

    if(board[0][2] == '-' && board[1][1] == 'O' && board[2][0] == 'O')
        return 0*3 + 2;
    if(board[0][2] == 'O' && board[1][1] == '-' && board[2][0] == 'O')
        return 1*3 + 1;
    if(board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == '-')
        return 2*3 + 0;

    /********** Impossible de gagner dans ce tour => Eviter de perdre ****************/
    for(i = 0; i < 3; i++)
    {

        if(board[i][0] == '-' && board[i][1] == 'X' && board[i][2] == 'X')
            return i*3 + 0;
        if(board[i][0] == 'X' && board[i][1] == '-' && board[i][2] == 'X')
            return i*3 + 1;
        if(board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == '-')
            return i*3 + 2;

        if(board[0][i] == '-' && board[1][i] == 'X' && board[2][i] == 'X')
            return 0*3 + i;
        if(board[0][i] == 'X' && board[1][i] == '-' && board[2][i] == 'X')
            return 1*3 + i;
        if(board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] == '-')
            return 2*3 + i;

    }

    //Diagonales
    if(board[0][0] == '-' && board[1][1] == 'X' && board[2][2] == 'X')
        return 0*3 + 0;
    if(board[0][0] == 'X' && board[1][1] == '-' && board[2][2] == 'X')
        return 1*3 + 1;
    if(board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == '-')
        return 2*3 + 2;

    if(board[0][2] == '-' && board[1][1] == 'X' && board[2][0] == 'X')
        return 0*3 + 2;
    if(board[0][2] == 'X' && board[1][1] == '-' && board[2][0] == 'X')
        return 1*3 + 1;
    if(board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == '-')
        return 2*3 + 0;

    /********* Arrivé là il est encore tot pour gagner ou éviter une défaite => Mouvement aléatoire ***********/
    return easy();
}