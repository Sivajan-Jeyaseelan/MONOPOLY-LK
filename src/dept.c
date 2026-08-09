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


        // Railways
        if(board[i].type == RAILWAY && board[i].railway.ownerID == player->id){
            total += board[i].railway.purchasePrice;
        }

        // Utilities
        if(board[i].type == UTILITY && board[i].utility.ownerID == player->id){
            total += board[i].utility.purchasePrice;
        }

    }

    total += player->insuranceClaims;

    if(player->loan.active){
        total -= player->loan.loanAmount;
    }

    total -= player->loan.interest;

    total -= player->taxesDue;

    return total;

}

void checkBankruptcy(Player *player, Board board[]){

    int assets = calculateAssets(player, board);

    if(assets < 0){
        declareBankruptcy(player, board);
    }

}

void declareBankruptcy(Player *player, Board board[]){

    printf("%s declared bankrupt\n", player->name);

    for(int i=0;i<40;i++){

        if(board[i].type == PROPERTY && board[i].property.ownerID == player->id){

            // remove buildings
            board[i].property.buildings = NO_BUILDING;

            board[i].property.houseCount = 0;

            // expire insurance
            board[i].property.insuranceStatus = 0;

            board[i].property.insurance.type = NO_INSURANCE;

            // transfer property to bank
            board[i].property.ownerID = -1;

        }

    }

    // loan cleared
    player->loan.active = 0;
    player->loan.loanAmount = 0;    
    player->bankrupt = 1;

}

