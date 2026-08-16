#include <stdio.h>

#include "../include/insurance_lk.h"


int lkCalculateInsurancePremium(Property *property, InsuranceType type){

    if(property == NULL){
        return 0;
    }

    if(property->currentValue <= 0){
        return 0;
    }

    int premium = 0;

    if(type == BASIC_INSURANCE){

        premium = property->currentValue * 5 / 100;

    }else if(type == COMPREHENSIVE_INSURANCE){

        premium = property->currentValue * 10 / 100;

    }else if(type == BUSINESS_INTERRUPTION_INSURANCE){

        premium = property->currentValue * 15 / 100;

    }else{

        return 0;
        
    }

    return premium;

}


int lkGetInsuranceCoverage(InsuranceType type){

    if(type == BASIC_INSURANCE){
        return 80;
    }

    if(type == COMPREHENSIVE_INSURANCE){
        return 100;
    }

    if(type == BUSINESS_INTERRUPTION_INSURANCE){
        return 100;
    }

    return 0;

}

int lkCanPurchaseInsurance(Player *player, Board board[]){

    if(player == NULL || board == NULL){
        return 0;
    }

    if(player->position < 0 || player->position >= 40){
        return 0;
    }

    if(board[player->position].type != INSURANCE){
        return 0;
    }

    return 1;

}

int lkPurchaseInsurance(Player *player, Board board[], int propertyIndex, InsuranceType type){

    if(player == NULL || board == NULL){
        return 0;
    }

    if(!lkCanPurchaseInsurance(player, board)){

        printf("%s cannot purchase insurance here.\n", player->name);
        return 0;

    }

    if(propertyIndex < 0 || propertyIndex >= 40){

        printf("Invalid property index.\n");
        return 0;

    }

    if(board[propertyIndex].type != PROPERTY){

        printf("Selected asset is not a property.\n");
        return 0;

    }


    Property *property = &board[propertyIndex].property;

    if(property->ownerID != player->id){

        printf("%s does not own %s.\n", player->name, property->name);
        return 0;

    }

    if(property->insurance.active == 1){

        printf("%s already has an active insurance policy.\n", property->name);
        return 0;

    }

    if(type != BASIC_INSURANCE && type != COMPREHENSIVE_INSURANCE && type != BUSINESS_INTERRUPTION_INSURANCE){

        printf("Invalid insurance type.\n");
        return 0;

    }

    int premium = lkCalculateInsurancePremium(property, type);

    if(premium <= 0){

        printf("Unable to calculate insurance premium.\n");
        return 0;

    }

    if(player->money < premium){

        printf("%s does not have enough money for insurance.\n", player->name);
        return 0;

    }

    player->money -= premium;

    property->insurance.type = type;
    property->insurance.premium = premium;
    property->insurance.remainingRounds = 20;
    property->insurance.lostIncomeRounds = 0;
    property->insurance.disasterActive = 0;

    property->insurance.active = 1;
    property->insurance.propertyValue = property->currentValue;
    property->insurance.coveragePercent = lkGetInsuranceCoverage(type);

    property->insurance.renewalReminderShown = 0;

    property->insuranceStatus = type;

    printf("\n");
    printf("Insurance Purchased\n");
    printf("%s purchased insurance for %s.\n", player->name, property->name);

    printf("Insurance Type : ");

    if(type == BASIC_INSURANCE){

        printf("Basic Insurance\n");

    }else if(type == COMPREHENSIVE_INSURANCE){

        printf("Comprehensive Insurance\n");

    }else{

        printf("Business Interruption Insurance\n");

    }

    printf("Premium : LKR %d\n", premium);

    printf("Coverage : %d%%\n", property->insurance.coveragePercent);

    printf("Duration : 20 Rounds\n");

    printf("Remaining Balance : LKR %d\n", player->money);

    return 1;

}