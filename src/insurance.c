#include <stdio.h>

#include "../include/insurance.h"


int calculatePremium(Board *property, InsuranceType type){

    int value = property->property.purchasePrice;

    switch(type){

        case BASIC_INSURANCE:
            return value * 5 / 100;


        case COMPREHENSIVE_INSURANCE:
            return value * 10 / 100;


        case BUSINESS_INTERRUPTION_INSURANCE:
            return value * 15 / 100;


        default:
            return 0;

    }

}

int calculateLostRentalIncome(Board *property){

    int rent = property->property.baseRent;

    return rent * 5;

}

int calculateCompensation(Board *property, int repairCost){

    InsuranceType type = property->property.insurance.type;

    switch(type){

        case BASIC_INSURANCE:

            return repairCost * 80 / 100;


        case COMPREHENSIVE_INSURANCE:

            return repairCost;


        case BUSINESS_INTERRUPTION_INSURANCE:

            if(property->property.buildings == HOTEL){

                int lostIncome = calculateLostRentalIncome(property);

                return repairCost + lostIncome;

            }

            return 0;


        default:

            return 0;
    }

}

void applyDisaster(Board *property, Player *owner, int repairCost){

    if(property->property.insuranceStatus == 1){

        int compensation = calculateCompensation(property, repairCost);

        owner->money += compensation;

        if(property->property.insurance.type == BUSINESS_INTERRUPTION_INSURANCE && property->property.buildings == HOTEL){

            property->property.insurance.lostIncomeRounds = 5;

        }

        printf("Insurance compensation received: LKR %d\n", compensation);

    }else{

        owner->money -= repairCost;

        printf("No insurance. Owner paid repair cost: LKR %d\n",
        repairCost);

    }

}

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