#include <stdio.h>

#include "../include/loan_transaction_lk.h"
#include "../include/loan_lk.h"
#include "../include/loan_locked_lk.h"


int canExecuteLoanAction(Player *player, Board board[], LoanAction action){

    if(player == NULL || board == NULL){
        return 0;
    }

    if(player->position < 0 || player->position >= 40){
        return 0;
    }

    if(board[player->position].type != BANK){
        return 0;
    }

    if(player->loan.active == 0){
        return 0;
    }

    if(player->loan.loanAmount <= 0){
        return 0;
    }

    if(action == LOAN_REPAY_PARTIAL){

        if(player->money > 0){
            return 1;
        }

        return 0;

    }

    if(action == LOAN_REPAY_FULL){

        if(player->money >= player->loan.loanAmount){
            return 1;
        }

        return 0;

    }

    if(action == LOAN_EXTEND){
        return 1;
    }

    if(action == LOAN_INCREASE){

        int availableCollateral = calculateEligibleCollateral(player, board);

        if(availableCollateral > player->loan.collateralValue){
            return 1;
        }

        return 0;

    }

    return 0;

}

int executeLoanAction(Player *player, Board board[], LoanAction action){

    if(player == NULL || board == NULL){
        return 0;
    }

    if(!canExecuteLoanAction(player, board, action)){

        printf("%s cannot perform this loan action.\n", player->name);
        return 0;

    }

    if(action == LOAN_REPAY_PARTIAL){

        int repayment;
        int maximumRepayment = player->loan.loanAmount / 2;          

        if(maximumRepayment < 1){

            maximumRepayment = 1;

        }

        if(player->money < maximumRepayment){

            repayment = player->money;

        }else{

            repayment = maximumRepayment;
        }


        player->money -= repayment;
        player->loan.loanAmount -= repayment;

        printf("%s repaid LKR %d of the loan.\n", player->name, repayment);
        printf("Outstanding Loan : LKR %d\n", player->loan.loanAmount);

        if(player->loan.loanAmount <= 0){

            player->loan.loanAmount = 0;
            player->loan.active = 0;
            player->loan.remainingRounds = 0;
            player->loan.accumulatedInterest = 0;

            unlockLoanCollateral(player, board);

            printf("%s has fully repaid the loan.\n", player->name);

        }

        return 1;

    }

    if(action == LOAN_REPAY_FULL){

        int repayment = player->loan.loanAmount;

        player->money -= repayment;

        player->loan.loanAmount = 0;
        player->loan.active = 0;
        player->loan.remainingRounds = 0;
        player->loan.accumulatedInterest = 0;

        unlockLoanCollateral(player, board);

        printf("%s repaid the entire loan.\n", player->name);
        printf("Loan Repayment : LKR %d\n", repayment);
        printf("Outstanding Loan : LKR 0\n");

        return 1;

    }

    if(action == LOAN_EXTEND){

        int extensionPeriod = player->loan.maturity;


        if(extensionPeriod <= 0){

            extensionPeriod = 20;

        }


        player->loan.remainingRounds += extensionPeriod;


        printf("%s extended the loan period.\n", player->name);
        printf("Extension : %d Rounds\n", extensionPeriod);
        printf("Remaining Rounds : %d\n", player->loan.remainingRounds);

        return 1;

    }

    if(action == LOAN_INCREASE){

        int availableCollateral;
        int additionalCollateral;
        int additionalLoan;


        availableCollateral = calculateEligibleCollateral(player, board);

        additionalCollateral = availableCollateral - player->loan.collateralValue;

        if(additionalCollateral <= 0){

            printf("%s has no additional collateral available.\n", player->name);
            return 0;

        }

        additionalLoan = additionalCollateral;

        player->loan.loanAmount += additionalLoan;

        player->loan.originalAmount += additionalLoan;

        player->loan.collateralValue += additionalLoan;  // need to check here

        player->money += additionalLoan;

        printf("%s increased the loan amount.\n", player->name);
        printf("Additional Loan : LKR %d\n", additionalLoan);
        printf("Total Outstanding Loan : LKR %d\n", player->loan.loanAmount);
        printf("Available Cash : LKR %d\n", player->money);

        return 1;

    }

    return 0;

}