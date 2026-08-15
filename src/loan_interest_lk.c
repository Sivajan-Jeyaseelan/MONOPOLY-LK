#include <stdio.h>

#include "../include/loan_interest_lk.h"


void accumulateLoanInterest(Player *player){

    if(player == NULL){
        return;
    }

    if(player->loan.active == 0){
        return;
    }

    int interestAmount = player->loan.loanAmount * player->loan.interest / 100;

    player->loan.loanAmount += interestAmount;

    player->loan.accumulatedInterest += interestAmount;

    printf("%s's loan interest accumulated.\n", player->name);
    printf("Interest Rate : %d%%\n", player->loan.interest);
    printf("Interest Added : LKR %d\n", interestAmount);
    printf("Outstanding Loan : LKR %d\n", player->loan.loanAmount);

}

void advanceLoanRound(Player *player){

    if(player == NULL){
        return;
    }

    if(player->loan.active == 0){
        return;
    }

    accumulateLoanInterest(player);

    if(player->loan.remainingRounds > 0){

        player->loan.remainingRounds--;

    }

    printf("%s's loan has %d rounds remaining.\n", player->name, player->loan.remainingRounds);

    if(player->loan.remainingRounds == 0){

        printf("%s's loan duration has ended.\n", player->name);

    }

}