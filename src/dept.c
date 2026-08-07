#include <stdio.h>
    
#include "../include/dept.h"


void recoverDebt(Player *player, int amount, Board board[]){

    printf("%s needs to pay LKR %d\n", player->name, amount);

    sellBuildings(player, board);

    if(player->money >= amount){

        player->money -= amount;
        printf("%s paid the debt\n", player->name);
        return;

    }


    mortgageProperties(player, board);

    if(player->money >= amount){

        player->money -= amount;
        printf("%s paid the debt after mortgaging properties\n", player->name);
        return;

    }


    // Cannot pay even after selling assets
    printf("%s cannot recover the debt\n", player->name);

    player->bankrupt = 1;

    printf("%s declared bankrupt\n", player->name);

}

void sellBuildings(Player *player, Board board[]){

    for(int i = 0; i < 40; i++){

        if(board[i].type == PROPERTY && board[i].property.ownerID == player->id){

            if(board[i].property.buildings == HOTEL){

                player->money += board[i].property.hotelCost;

                board[i].property.buildings = NO_BUILDING;
                board[i].property.houseCount = 0;

                printf("%s sold hotel on %s and received LKR %d\n", player->name, board[i].name, board[i].property.hotelCost);
            
            }else if(board[i].property.houseCount > 0){

                int refund = board[i].property.houseCount * board[i].property.houseCost;

                player->money += refund;


                printf("%s sold %d houses on %s and received LKR %d\n", player->name, board[i].property.houseCount, board[i].name, refund);

                board[i].property.houseCount = 0;
                board[i].property.buildings = NO_BUILDING;

            }

        }

    }

}

void mortgageProperties(Player *player, Board board[]){

    for(int i = 0; i < 40; i++){

        if(board[i].type == PROPERTY && board[i].property.ownerID == player->id){

            if(board[i].property.mortgageStatus == 0){

                player->money += board[i].property.mortgageValue;

                board[i].property.mortgageStatus = 1;

                printf("%s mortgaged %s and received LKR %d\n", player->name, board[i].name, board[i].property.mortgageValue);


            }

        }

    }

}

int calculateAssets(Player *player, Board board[]){

    int total = player->money;

    for(int i = 0; i < 40; i++){

        if(board[i].type == PROPERTY && board[i].property.ownerID == player->id) {

            total += board[i].property.purchasePrice;

            total += board[i].property.houseCount * board[i].property.houseCost;


            if(board[i].property.buildings == HOTEL){
                total += board[i].property.hotelCost;
            }

        }

    }

    if(player->loan.active){
        total -= player->loan.loanAmount;
    }

    return total;

}
