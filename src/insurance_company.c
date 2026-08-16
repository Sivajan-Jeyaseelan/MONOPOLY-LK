#include <stdio.h>

#include "../include/insurance.h"


void purchaseInsurance(Player *player, Board board[]){

    int propertyID;
    int choice;

    printf("\nSelect property to insure:\n");

    for(int i = 0; i < 40; i++){

        if(board[i].type == PROPERTY && board[i].property.ownerID == player->id){

            printf("%d. %s\n", board[i].id, board[i].name);

        }

    }


    printf("Enter property ID: ");
    scanf("%d",&propertyID);

    if(board[propertyID].property.ownerID != player->id){

        printf("You do not own this property\n");
        return;

    }

    printf("\nSelect Insurance Type\n");

    printf("1. Basic Insurance\n");
    printf("2. Comprehensive Insurance\n");
    printf("3. Business Interruption Insurance\n");

    printf("Choice: ");
    scanf("%d",&choice);


    InsuranceType type;


    switch(choice){

        case 1:
            type = BASIC_INSURANCE;
            break;

        case 2:
            type = COMPREHENSIVE_INSURANCE;
            break;

        case 3:
            type = BUSINESS_INTERRUPTION_INSURANCE;
            break;

        default:

            printf("Invalid option\n");
            return;

    }



    Board *property = &board[propertyID];


    int premium = calculatePremium(property, type);


    if(player->money < premium){

        printf("Not enough money\n");
        return;

    }

    player->money -= premium;

    
    property->property.insuranceStatus = 1;

    property->property.insurance.type = type;

    property->property.insurance.premium = premium;

    property->property.insurance.remainingRounds = 20;

    property->property.insurance.lostIncomeRounds = 0;

    property->property.insurance.disasterActive = 0;

    printf("Insurance purchased for %s\n", property->name);

}


void renewInsurance(Player *player, Board *property){

    if(property->property.insuranceStatus == 0){

        printf("No active insurance\n");
        return;

    }

    int premium = property->property.insurance.premium;

    if(player->money < premium){

        printf("Not enough money\n");
        return;

    }

    player->money -= premium;

    property->property.insurance.remainingRounds = 20;

    printf("%s insurance renewed\n", property->name);

}


void updateInsurance(Board board[]){

    for(int i = 0; i < 40; i++){

        Board *property = &board[i];

        if(property->property.insurance.lostIncomeRounds > 0){

            printf("%s lost rental income compensation round\n", property->name);

            property->property.insurance.lostIncomeRounds--;

        }

        if(property->type == PROPERTY && property->property.insuranceStatus == 1){

            property->property.insurance.remainingRounds--;

            if(property->property.insurance.remainingRounds == 3){

                printf("Notification: %s insurance expires in 3 rounds\n", property->name);

            }

            if(property->property.insurance.remainingRounds <= 0){

                property->property.insuranceStatus = 0;

                property->property.insurance.type = NO_INSURANCE;

                property->property.insurance.premium = 0;

                property->property.insurance.lostIncomeRounds = 0;

                property->property.insurance.disasterActive = 0;


                printf("%s insurance expired\n", property->name);

            }

        }

    }

}