#include <string.h>
#include "tourism_boom_lk.h"


void applyTourismBoom(Board board[], int boardSize){

    int i;

    for(i = 0; i < boardSize; i++){

        if(board[i].type != PROPERTY){
            continue;
        }

        if(board[i].property.buildings == HOTEL){

            board[i].property.currentRent =
                board[i].property.currentRent * 2;
        }

        if(strcmp(board[i].property.name, "Galle Fort") == 0 ||
           strcmp(board[i].property.name, "Unawatuna") == 0 ||
           strcmp(board[i].property.name, "Hikkaduwa") == 0){

            board[i].property.currentValue =
                (board[i].property.currentValue * 115) / 100;
        }

    }

}


void removeTourismBoom(Board board[], int boardSize){

    int i;

    for(i = 0; i < boardSize; i++){

        if(board[i].type != PROPERTY){
            continue;
        }

        if(board[i].property.buildings == HOTEL){

            board[i].property.currentRent = board[i].property.currentRent / 2;

        }

        if(strcmp(board[i].property.name, "Galle Fort") == 0 || strcmp(board[i].property.name, "Unawatuna") == 0 || strcmp(board[i].property.name, "Hikkaduwa") == 0){

            board[i].property.currentValue = (board[i].property.currentValue * 100) / 115;

        }

    }
    
}