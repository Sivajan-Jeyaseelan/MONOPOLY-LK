#include <stdio.h>

#include "../include/game.h"
#include "../include/dice.h"


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