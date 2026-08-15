#include <stdio.h>

#include "../include/loan_locked_lk.h"


void lockLoanCollateral(Player *player, Board board[]){

    int requiredCollateral = player->loan.collateralValue;
    int lockedCollateral = 0;

    player->money += player->loan.loanAmount;
    printf("%s received LKR %d from the loan.\n", player->name, player->loan.loanAmount);

    for(int i = 0; i < 40; i++){

        if(lockedCollateral >= requiredCollateral){
            break;
        }

        if(board[i].type == PROPERTY){

            if(board[i].property.ownerID == player->id && board[i].property.loanLocked == 0){

                board[i].property.loanLocked = 1;

                lockedCollateral += board[i].property.mortgageValue;

                player->loanLockedAssetCount++;

                printf("%s is now Loan Locked.\n", board[i].property.name);

            }

        }else if(board[i].type == RAILWAY){

            if(board[i].railway.ownerID == player->id && board[i].railway.loanLocked == 0){

                board[i].railway.loanLocked = 1;

                lockedCollateral += board[i].railway.mortgageValue;

                player->loanLockedAssetCount++;

                printf("%s is now Loan Locked.\n", board[i].railway.name);

            }

        }else if(board[i].type == UTILITY){

            if(board[i].utility.ownerID == player->id && board[i].utility.loanLocked == 0){

                board[i].utility.loanLocked = 1;

                lockedCollateral += board[i].utility.mortgageValue;

                player->loanLockedAssetCount++;

                printf("%s is now Loan Locked.\n", board[i].utility.name);

            }

        }

    }

}

void unlockLoanCollateral(Player *player, Board board[]){

    for(int i = 0; i < 40; i++){

        if(board[i].type == PROPERTY){

            if(board[i].property.ownerID == player->id && board[i].property.loanLocked == 1){

                board[i].property.loanLocked = 0;

            }

        }else if(board[i].type == RAILWAY){

            if(board[i].railway.ownerID == player->id && board[i].railway.loanLocked == 1){

                board[i].railway.loanLocked = 0;

            }

        }else if(board[i].type == UTILITY){

            if(board[i].utility.ownerID == player->id && board[i].utility.loanLocked == 1){

                board[i].utility.loanLocked = 0;

            }

        }
        
    }

    player->loanLockedAssetCount = 0;
    printf("%s's loan collateral has been unlocked.\n", player->name);

}

