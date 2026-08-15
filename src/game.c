#include <stdio.h>

#include "../include/game.h"
#include "../include/dice.h"
#include "../include/property.h"
#include "../include/building.h"
#include "../include/dept.h"



Player *allPlayers;
int totalPlayers;


void setPlayers(Player players[], int playerCount){

    allPlayers = players;
    totalPlayers = playerCount;

}

int countActivePlayers(Player players[], int totalPlayers){

    int count = 0;

    for(int i=0;i<totalPlayers;i++){

        if(players[i].bankrupt == 0){
            count++;
        }

    }

    return count;

}

int checkGameOver(Player players[], int totalPlayers){

    return countActivePlayers(players,totalPlayers) == 1;

}

Player* findWinner(Player players[], int totalPlayers, Board board[]){

    int highest = -1;
    Player *winner = NULL;

    for(int i=0;i<totalPlayers;i++){

        if(players[i].bankrupt == 0){

            int worth = calculateAssets(&players[i],board);

            if(worth > highest){
                highest = worth;
                winner = &players[i];
            }

        }

    }

    return winner;

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
    checkBuilding(player, board);

    printf("Completing financial transactions...\n");

    printf("Turn ended\n");

}