#include <string.h>
#include "heavy_monsoon_lk.h"


void applyHeavyMonsoon(Board board[], int boardSize){

    int i;

    for(i = 0; i < boardSize; i++){

        if(board[i].type != PROPERTY){
            continue;
        }

        if(board[i].property.insurance.type != NO_INSURANCE){

            board[i].property.insurance.premium = (board[i].property.insurance.premium * 110) / 100;

        }

        if(strcmp(board[i].property.name, "Galle Fort") == 0 || strcmp(board[i].property.name, "Unawatuna") == 0 || strcmp(board[i].property.name, "Hikkaduwa") == 0){

            board[i].property.currentValue = (board[i].property.currentValue * 90) / 100;

        }

    }

}

void removeHeavyMonsoon(Board board[], int boardSize){

    int i;

    for(i = 0; i < boardSize; i++){

        if(board[i].type != PROPERTY){
            continue;
        }

        if(board[i].property.insurance.type != NO_INSURANCE){

            board[i].property.insurance.premium = (board[i].property.insurance.premium * 100) / 110;
        
        }

        if(strcmp(board[i].property.name, "Galle Fort") == 0 || strcmp(board[i].property.name, "Unawatuna") == 0 || strcmp(board[i].property.name, "Hikkaduwa") == 0){

            board[i].property.currentValue = (board[i].property.currentValue * 100) / 90;

        }

    }
    
}