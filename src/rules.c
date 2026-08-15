#include <stdio.h>
#include <stdlib.h>

#include "../include/rules.h"
#include "../include/dept.h"


void resolveSquare(Player *player, Board board[]){

    Board *currentSquare = &board[player->position];


    if(currentSquare->type == TAX){

        int taxAmount = currentSquare->taxAmount;


        if(player->money >= taxAmount){

            handleIncomeTax(player,currentSquare);

        }
        else{

            recoverDebt(player,taxAmount,board);

        }


    }else if(currentSquare->type == SPECIAL){

        if(currentSquare->id == 30){

            sendPlayerToJail(player);

        }

    }

}

void handleIncomeTax(Player *player, Board *taxSquare){

    int taxAmount = taxSquare->taxAmount;

    if(player->money >= taxAmount){

        player->money -= taxAmount;
        printf("%s paid Income Tax LKR %d\n", player->name, taxAmount);

    }

}

void sendPlayerToJail(Player *player){

    player->position = 10;
    player->inJail = 1;
    player->jailTurns = 0;

    printf("%s was sent to Jail\n", player->name);

}

void handleJail(Player *player){

    if(player->inJail == 0){
        return;
    }

    printf("\n%s is in Jail\n", player->name);

    /*
     * Temporary autonomous decision:
     * Pay bail if the player can afford it.
     */

    if(player->money >= 300){

        player->money -= 300;
        player->inJail = 0;
        player->jailTurns = 0;

        printf("%s paid LKR 300 bail and left Jail\n",
               player->name);

        return;
    }


    /*
     * Player cannot afford bail.
     * Try rolling doubles.
     */

    int dice1 = (rand() % 6) + 1;
    int dice2 = (rand() % 6) + 1;

    printf("%s rolled %d and %d in Jail\n", player->name, dice1, dice2);

    if(dice1 == dice2){

        player->inJail = 0;
        player->jailTurns = 0;

        printf("%s rolled doubles and left Jail\n", player->name);

        return;

    }


    /*
     * Doubles not rolled.
     * Remain in Jail.
     */

    player->jailTurns++;

    printf("%s remained in Jail (%d/3 turns)\n", player->name, player->jailTurns);


    if(player->jailTurns >= 3){

        player->inJail = 0;
        player->jailTurns = 0;

        printf("%s completed three Jail turns and left\n", player->name);

    }
    
}