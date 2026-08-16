#include "fuel_crisis_lk.h"


void applyFuelCrisis(Board board[], int boardSize){

    int i;

    for(i = 0; i < boardSize; i++){

        if(board[i].type == PROPERTY){

            board[i].property.houseCost = (board[i].property.houseCost * 120) / 100;

            board[i].property.hotelCost = (board[i].property.hotelCost * 120) / 100;

        }

    }

}


void removeFuelCrisis(Board board[], int boardSize){

    int i;

    for(i = 0; i < boardSize; i++){

        if(board[i].type == PROPERTY){

            board[i].property.houseCost = (board[i].property.houseCost * 100) / 120;

            board[i].property.hotelCost = (board[i].property.hotelCost * 100) / 120;

        }

    }

}