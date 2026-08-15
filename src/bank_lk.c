#include <stdio.h>

#include "../include/bank_lk.h"
#include "../include/loan_lk.h"
#include "../include/loan_transaction_lk.h"

void resolveBank(Player *player, Board board[]){

    if(player == NULL || board == NULL){
        return;
    }

    printf("\n=====================================\n");
    printf("Bank of Ceylon\n");
    printf("=====================================\n");

    if(player->loan.active == 0){

        printf("%s does not have an active loan.\n", player->name);

        if(hasLoanCollateral(player, board)){

            printf("Eligible collateral : LKR %d\n", calculateEligibleCollateral(player, board));

            printf("Maximum loan : LKR %d\n", calculateMaximumLoan(player, board));

            obtainLKLoan(player, board);

        }else{

            printf("No eligible collateral available.\n");

        }

        return;

    }

    printf("Active Loan : LKR %d\n", player->loan.loanAmount);
    printf("Remaining Rounds : %d\n", player->loan.remainingRounds);

    printf("\nAvailable actions:\n");
    printf("1. Repay part of loan\n");
    printf("2. Repay entire loan\n");
    printf("3. Extend loan\n");
    printf("4. Increase loan\n");


    if(player->money >= player->loan.loanAmount){

        executeLoanAction(player, board, LOAN_REPAY_FULL);

    }else if(player->money > 0){

        executeLoanAction(player, board, LOAN_REPAY_PARTIAL);

    }else{

        executeLoanAction(player, board, LOAN_EXTEND);

    }

}