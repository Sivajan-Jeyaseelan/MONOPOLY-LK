#include <stdio.h>

#include "../include/board.h"


void displayBoard(Board board[]){

    for(int i = 0; i < 40; i++)    {

        printf("Square %d : %s\n", board[i].id, board[i].name);

        if(board[i].type == PROPERTY){

            printf("Type : Property\n");
            printf("Purchase Price : LKR %d\n", board[i].property.purchasePrice);
            printf("Mortgage Value : LKR %d\n", board[i].property.mortgageValue);
            printf("Owner ID : %d\n\n", board[i].property.ownerID);

        }else if(board[i].type == RAILWAY){

            printf("Type : Railway Station\n");
            printf("Purchase Price : LKR %d\n", board[i].railway.purchasePrice);
            printf("Mortgage Value : LKR %d\n", board[i].railway.mortgageValue);
            printf("Owner ID : %d\n", board[i].railway.ownerID);
            printf("Mortgage Status : %d\n\n", board[i].railway.mortgageStatus);

        }else if(board[i].type == UTILITY){

            printf("Type : Utility\n");            
            printf("Purchase Price : LKR %d\n", board[i].utility.purchasePrice);
            printf("Mortgage Value : LKR %d\n", board[i].utility.mortgageValue);
            printf("Owner ID : %d\n", board[i].utility.ownerID);
            printf("Mortgage Status : %d\n\n", board[i].utility.mortgageStatus);

        }else if(board[i].type == START){

            printf("Type : Start\n\n");

        }

        else if(board[i].type == EVENT){

            printf("Type : Event\n\n");

        }else if(board[i].type == TAX){

            printf("Type : Tax\n\n");

        }else if(board[i].type == INSURANCE){

            printf("Type : Insurance\n\n");

        }else if(board[i].type == BANK){

            printf("Type : Bank\n\n");

        }else if(board[i].type == SPECIAL){
        
            printf("Type : Special\n\n");

        }

    }

}