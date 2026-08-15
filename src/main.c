#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/board.h"
#include "../include/players.h"
#include "../include/game.h"


int main(){

    srand(time(NULL));

    Board board[40];

    Player players[4];

    initializeBoard(board);

    createPlayer(&players[0], 0, "Player 1");
    createPlayer(&players[1], 1, "Player 2");
    createPlayer(&players[2], 2, "Player 3");
    createPlayer(&players[3], 3, "Player 4");

    setPlayers(players, 4);

    printf("====================================\n");
    printf("       MONOPOLY LK\n");
    printf("====================================\n");

    printf("\nPlayers:\n");

    for(int i = 0; i < 4; i++){

        printf("%d. %s - LKR %d\n", players[i].id, players[i].name, players[i].money);

    }

    printf("\nStarting game...\n");

    startGame(players, 4, board);

    return 0;

}