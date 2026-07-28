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