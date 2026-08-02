#include <stdio.h>

#include "../include/game.h"
#include "../include/dice.h"
#include "../include/property.h"



Player *allPlayers;
int totalPlayers;


void setPlayers(Player players[], int playerCount){

    allPlayers = players;
    totalPlayers = playerCount;

}


void determineFirstPlayer(Player players[], int turnOrder[]){

    int highest = -1;
    int firstPlayer = -1;

    for(int i = 0; i < 4; i++){

        int roll = rollDice();

        printf("%s rolled %d\n", players[i].name, roll);

        if(roll > highest){

            highest = roll;
            firstPlayer = i;

        }

    }


    printf("\n%s will begin the game.\n", players[firstPlayer].name);


    for(int i = 0; i < 4; i++){

        turnOrder[i] = (firstPlayer + i) % 4;

    }


    printf("\nTurn Order:\n");


    for(int i = 0; i < 4; i++){

        printf("%s\n", players[turnOrder[i]].name);

    }

}

void playTurn(Player *player, Board board[]){

    printf("\n%s's turn\n", player->name);

    printf("Checking penalties...\n");

    int dice = rollDice();

    printf("%s rolled %d\n", player->name, dice);


    player->position += dice;

    if(player->position >= 40){

        player->position -= 40;

        player->money += 2000;

        printf("%s passed GO and received LKR 2000\n", player->name);

    }

    printf("Current position: %d\n", player->position);

    printf("Resolving landing action...\n");

    resolveProperty(player, allPlayers, totalPlayers, board);

    printf("Checking building construction...\n");

    printf("Completing financial transactions...\n");

    printf("Turn ended\n");

}