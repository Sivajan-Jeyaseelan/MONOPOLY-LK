#include "../include/finance.h"


int calculateRailwayRent(Board board[], int playerID){

    int railwayCount = 0;


    for(int i = 0; i < 40; i++){

        if(board[i].type == RAILWAY && board[i].railway.ownerID == playerID){

            railwayCount++;

        }

    }


    if(railwayCount == 1){

        return 250;

    }else if(railwayCount == 2){

        return 500;

    }else if(railwayCount == 3){

        return 1000;

    }else if(railwayCount == 4){

        return 2000;

    }


    return 0;

}


int calculateUtilityRent(Board board[], int ownerID, int diceValue){

    int utilityCount = 0;

    for(int i = 0; i < 40; i++){

        if(board[i].type == UTILITY && board[i].utility.ownerID == ownerID){

            utilityCount++;

        }

    }

    if(utilityCount == 1){

        return 4 * diceValue;

    }
    else if(utilityCount == 2){

        return 10 * diceValue;

    }

    return 0;

}