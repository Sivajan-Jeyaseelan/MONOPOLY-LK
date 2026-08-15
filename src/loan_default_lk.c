#include <stdio.h>

#include "../include/loan_default_lk.h"


int isLoanDefaulted(Player *player){

    if(player == NULL){
        return 0;
    }

    if(player->loan.active == 0){
        return 0;
    }

    if(player->loan.loanAmount <= 0){
        return 0;
    }

    if(player->loan.remainingRounds <= 0){
        return 1;
    }

    return 0;

}

void processLoanDefault(Player *player, Board board[]){

    if(player == NULL || board == NULL){
        return;
    }

    if(!isLoanDefaulted(player)){
        return;
    }

    printf("\n");
    printf("=====================================\n");
    printf("Loan Default\n");
    printf("=====================================\n");

    printf("%s has defaulted on the loan.\n", player->name);
    printf("Outstanding Debt : LKR %d\n", player->loan.loanAmount);

    for(int i = 0; i < 40; i++){

        if(board[i].type == PROPERTY){

            if(board[i].property.ownerID == player->id &&   board[i].property.loanLocked == 1){

                printf("Collateral Foreclosed : %s\n", board[i].property.name);

                board[i].property.ownerID = -1;

                board[i].property.buildings = NO_BUILDING;
                board[i].property.houseCount = 0;

                board[i].property.insuranceStatus = NO_INSURANCE;

                board[i].property.insurance.type = NO_INSURANCE;
                board[i].property.insurance.active = 0;
                board[i].property.insurance.premium = 0;
                board[i].property.insurance.remainingRounds = 0;
                board[i].property.insurance.lostIncomeRounds = 0;
                board[i].property.insurance.disasterActive = 0;
                board[i].property.insurance.propertyValue = 0;
                board[i].property.insurance.coveragePercent = 0;
                board[i].property.insurance.renewalReminderShown = 0;

                board[i].property.loanLocked = 0;
                board[i].property.mortgageStatus = 0;

                if(player->propertyCount > 0){
                    player->propertyCount--;
                }

            }

        }else if(board[i].type == RAILWAY){

            if(board[i].railway.ownerID == player->id && board[i].railway.loanLocked == 1){

                printf("Collateral Foreclosed : %s\n", board[i].railway.name);

                board[i].railway.ownerID = -1;

                board[i].railway.loanLocked = 0;
                board[i].railway.mortgageStatus = 0;

                if(player->propertyCount > 0){
                    player->propertyCount--;
                }

            }

        }else if(board[i].type == UTILITY){

            if(board[i].utility.ownerID == player->id && board[i].utility.loanLocked == 1){

                printf("Collateral Foreclosed : %s\n", board[i].utility.name);

                board[i].utility.ownerID = -1;
                board[i].utility.loanLocked = 0;
                board[i].utility.mortgageStatus = 0;

                if(player->propertyCount > 0){
                    player->propertyCount--;
                }

            }

        }

    }

    player->loanLockedAssetCount = 0;

    player->loan.loanAmount = 0;
    player->loan.active = 0;
    player->loan.remainingRounds = 0;
    player->loan.accumulatedInterest = 0;
    player->loan.collateralValue = 0;

    printf("Collateral has been foreclosed.\n");
    printf("Outstanding debt cleared.\n");

    printf("%s continues the game using remaining assets.\n", player->name);

    printf("=====================================\n");

}