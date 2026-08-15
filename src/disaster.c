 #include <stdio.h>

#include "../include/insurance.h"


/*void applyDisaster(Board *property, Player *owner, int repairCost){

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

}*/