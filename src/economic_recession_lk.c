#include "economic_recession_lk.h"

void applyEconomicRecession(Board board[], Player players[], int playerCount){

    int i;

    for(i = 0; i < playerCount; i++){

        if(players[i].loan.active){

            players[i].loan.interest = (players[i].loan.interest * 115) / 100;

        }

    }

    for(i = 0; i < 40; i++){

        if(board[i].type == PROPERTY){

            board[i].property.currentValue = (board[i].property.currentValue * 85) / 100;

            board[i].property.currentRent = (board[i].property.currentRent * 90) / 100;

        }

    }

}


void removeEconomicRecession(Board board[], Player players[], int playerCount){

    int i;

    for(i = 0; i < playerCount; i++){

        if(players[i].loan.active){

            players[i].loan.interest = (players[i].loan.interest * 100) / 115;

        }

    }

    for(i = 0; i < 40; i++){

        if(board[i].type == PROPERTY){

            board[i].property.currentValue = (board[i].property.currentValue * 100) / 85;

            board[i].property.currentRent = (board[i].property.currentRent * 100) / 90;

        }

    }
    
}