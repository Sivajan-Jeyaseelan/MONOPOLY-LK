#include <stdio.h>

#include "../include/insurance_expiry_lk.h"


void updateInsuranceRounds(Player *player, Board board[]){

    if(player == NULL || board == NULL){
        return;
    }

    for(int i = 0; i < 40; i++){

        if(board[i].type != PROPERTY){
            continue;
        }

        Property *property = &board[i].property;

        if(property->ownerID != player->id){
            continue;
        }

        if(property->insurance.active == 0){
            continue;
        }

        if(property->insurance.remainingRounds > 0){

            property->insurance.remainingRounds--;

        }

    }

}

void checkInsuranceExpiry(Player *player, Board board[]){

    if(player == NULL || board == NULL){
        return;
    }

    for(int i = 0; i < 40; i++){

        if(board[i].type != PROPERTY){
            continue;
        }

        Property *property = &board[i].property;

        if(property->ownerID != player->id){
            continue;
        }

        if(property->insurance.active == 0){
            continue;
        }

        if(property->insurance.remainingRounds == 3 && property->insurance.renewalReminderShown == 0){

            printf("%s\n", "Insurance Renewal Reminder");
            printf("Insurance policy on %s expires in 3 rounds.\n", property->name);
            property->insurance.renewalReminderShown = 1;

        }

        if(property->insurance.remainingRounds <= 0){

            printf("Insurance policy on %s has expired.\n", property->name);

            property->insurance.active = 0;
            property->insurance.type = NO_INSURANCE;
            property->insurance.remainingRounds = 0;
            property->insurance.lostIncomeRounds = 0;
            property->insurance.disasterActive = 0;
            property->insurance.propertyValue = 0;
            property->insurance.coveragePercent = 0;
            property->insurance.premium = 0;
            property->insurance.renewalReminderShown = 0;

            property->insuranceStatus = NO_INSURANCE;
            
        }

    }

}