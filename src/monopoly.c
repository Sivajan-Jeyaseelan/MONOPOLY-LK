#include "../include/monopoly.h"


int checkMonopoly(Player *player, Board board[], int groupID){

    int totalProperties = 0;
    int ownedProperties = 0;

    for(int i = 0; i < 40; i++){

        if(board[i].type == PROPERTY && board[i].property.groupID == groupID){

            totalProperties++;

            if(board[i].property.ownerID == player->id){

                ownedProperties++;

            }

        }

    }

    if(totalProperties == ownedProperties){
        return 1;   
    }

    return 0; 

}


int canBuild(Player *player, Board *property, Board board[]){

    if(property->property.ownerID != player->id){
        return 0;
    }

    if(checkMonopoly(player, board, property->property.groupID) == 0){
        return 0;
    }

    if(property->property.mortgageStatus == 1){
        return 0;
    }

    return 1;

}