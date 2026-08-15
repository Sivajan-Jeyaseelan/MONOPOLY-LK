#include <stdio.h>
#include <stddef.h>

#include "../include/loan_lk.h"
#include "../include/loan_locked_lk.h"

int calculateEligibleCollateral(Player *player, Board board[]){

    int totalCollateral = 0;

    for(int i = 0; i < 40; i++){

        if(board[i].type == PROPERTY){

            if(board[i].property.ownerID == player->id){

                if(board[i].property.loanLocked == 0){

                    totalCollateral += board[i].property.mortgageValue;

                }

            }

        }else if(board[i].type == RAILWAY){

            if(board[i].railway.ownerID == player->id){

                if(board[i].railway.loanLocked == 0){

                    totalCollateral += board[i].railway.mortgageValue;

                }

            }

        }else if(board[i].type == UTILITY){

            if(board[i].utility.ownerID == player->id){

                if(board[i].utility.loanLocked == 0){

                    totalCollateral += board[i].utility.mortgageValue;

                }

            }

        }

    }

    return totalCollateral;

}

int hasLoanCollateral(Player *player, Board board[]){

    int collateral = calculateEligibleCollateral(player, board);

    if(collateral > 0){
        return 1;
    }

    return 0;

}

int calculateMaximumLoan(Player *player, Board board[]){

    int collateral = calculateEligibleCollateral(player, board);

    int maximumLoan = collateral * 75 / 100;

    return maximumLoan;
    
}

void obtainLKLoan(Player *player, Board board[]){

    if(player == NULL || board == NULL){
        return;
    }

    if(player->loan.active == 1){

        printf("%s already has an active loan.\n", player->name);
        return;

    }

    int collateral = calculateEligibleCollateral(player, board);

    if(collateral <= 0){

        printf("%s has no eligible collateral.\n", player->name);
        return;

    }

    int maximumLoan = collateral * 75 / 100;

    if(maximumLoan <= 0){

        printf("Eligible collateral is insufficient for a loan.\n");
        return;

    }

    player->loan.active = 1;

    player->loan.loanAmount = maximumLoan;

    player->loan.originalAmount = maximumLoan;

    player->loan.collateralValue = collateral;


    //Set the MONOPOLY-LK interest rate here. Change this value if your specification gives a different rate.
    player->loan.interest = 10;

    player->loan.maturity = 20;

    player->loan.remainingRounds = 20;

    player->loan.accumulatedInterest = 0;

    player->loanLockedAssetCount = 0;

    lockLoanCollateral(player, board);

    printf("\n=====================================\n");
    printf("MONOPOLY-LK Loan Approved\n");
    printf("=====================================\n");

    printf("Collateral Value : LKR %d\n", collateral);
    printf("Maximum Loan     : LKR %d\n", maximumLoan);
    printf("Interest Rate    : %d%%\n", player->loan.interest);
    printf("Duration         : %d rounds\n", player->loan.remainingRounds);

    printf("=====================================\n");

}
