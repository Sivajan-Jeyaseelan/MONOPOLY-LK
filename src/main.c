#include <stdio.h>

#include "../include/board.h"
#include "../include/players.h"
#include "../include/dice.h"
#include "../include/movement.h"
#include "../include/game.h"


int main(){

    Board board[40];

    Player players[4];

    int turnOrder[4];


    // Rule 1: Create 4 Players
    createPlayer(&players[0], 0, "Player 1");
    createPlayer(&players[1], 1, "Player 2");
    createPlayer(&players[2], 2, "Player 3");
    createPlayer(&players[3], 3, "Player 4");

    // Temporary test for Rule 4: Passing GO
    players[0].position = 38;


    printf("\n===== RULE 1 TEST =====\n");

    for(int i = 0; i < 4; i++){

        printf("%s\n", players[i].name);
        printf("Money: LKR %d\n", players[i].money);
        printf("Position: %d\n", players[i].position);
        printf("Properties: %d\n", players[i].propertyCount);
        printf("Loan Active: %d\n", players[i].loan.active);

        printf("-------------------\n");

    }




    initializeBoard(board);




    // Rule 2: First Player Order
    printf("\n===== RULE 2 TEST =====\n");

    determineFirstPlayer(players, turnOrder);







    // Rule 3 + Rule 4 Test


    printf("\n===== RULE 3 & RULE 4 TEST =====\n");

    for(int i=0;i<4;i++){

        int currentPlayerID = turnOrder[i];

        Player *currentPlayer = &players[currentPlayerID];

        playTurn(currentPlayer, board);

    }

    

    return 0;

}