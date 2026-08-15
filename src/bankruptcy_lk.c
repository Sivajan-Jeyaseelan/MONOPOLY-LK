#include <stdio.h>

#include "../include/bankruptcy_lk.h"


int hasRemainingAssets(Player *player, Board board[]){

    if(player == NULL || board == NULL){
        return 0;
    }

    for(int i = 0; i < 40; i++){

        if(board[i].type == PROPERTY){

            if(board[i].property.ownerID == player->id){
                return 1;
            }

        }else if(board[i].type == RAILWAY){

            if(board[i].railway.ownerID == player->id){
                return 1;
            }

        }else if(board[i].type == UTILITY){

            if(board[i].utility.ownerID == player->id){
                return 1;
            }

        }
    }

    return 0;

}

void checkLoanBankruptcy(Player *player, Board board[]){

    if(player == NULL || board == NULL){
        return;
    }

    if(player->bankrupt){
        return;
    }

    if(hasRemainingAssets(player, board)){

        printf("%s still has remaining assets.\n", player->name);
        printf("%s continues the game.\n", player->name);
        return;

    }

    player->bankrupt = 1;

    printf("\n");
    printf("=====================================\n");
    printf("Bankruptcy\n");
    printf("=====================================\n");

    printf("%s has been declared bankrupt.\n",  player->name);

    printf("Remaining assets transferred to the Bank.\n");

    printf("%s is eliminated from the game.\n", player->name);

    printf("=====================================\n");

}