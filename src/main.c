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

    setPlayers(players,4);



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







    // Rule 3 + Rule 4 + Rule 5 + Rule 6 Test
    printf("\n===== RULE 3, RULE 4, RULE 5, RULE 6 TEST =====\n");

    players[0].position = 38;   //for rule 4 test

    playTurn(&players[0],board);



    printf("\nAfter movement\n");

    printf("Position : %d\n",players[0].position);

    printf("Money : %d\n",players[0].money);




    // Rule 5 + Rule 6 Test
    printf("\n===== RULE 5, RULE 6 PURCHASE BY CURRENT PLAYER OR AUCTION TEST FOR UNOWNED PROPERTIES =====\n");

    players[0].position = 1;

    resolveProperty(&players[0], players, 4, board);

    printf("\nAfter purchase\n");

    printf("Owner ID : %d\n", board[1].property.ownerID);

    printf("Player WHo Buy money : %d\n", players[board[1].property.ownerID].money);



    //(Rule 5 + Rule 6) Rent Test

    printf("\n===== RENT TEST =====\n");

    board[1].property.ownerID = players[0].id;

    players[1].position = 1;

    resolveProperty(&players[1], players, 4, board);


    printf("Player 2 money : %d\n", players[1].money);

    printf("Player 1 money : %d\n", players[0].money);

    

    return 0;

}