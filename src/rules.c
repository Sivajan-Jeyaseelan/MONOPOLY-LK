#include <stdio.h>

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

    int choice;

    printf("\n%s is in Jail\n", player->name);

    printf("1. Pay bail (LKR 300)\n");
    printf("2. Try rolling doubles\n");
    printf("3. Stay in jail\n");

    printf("Choice: ");
    scanf("%d",&choice);


    if(choice == 1){

        if(player->money >= 300){

            player->money -= 300;
            player->inJail = 0;
            player->jailTurns = 0;

            printf("%s paid bail and left jail\n", player->name);

        }else{

            printf("Not enough money for bail\n");

        }

    }else if(choice == 2){

        // connect dice logic here later

        printf("Roll doubles checking not implemented yet\n");

    }else if(choice == 3){

        player->jailTurns++;

        printf("%s stayed in jail (%d/3 turns)\n", player->name, player->jailTurns);

        if(player->jailTurns >= 3){

            player->inJail = 0;

            player->jailTurns = 0;

            printf("%s completed jail time and left\n", player->name);

        }

    }

}