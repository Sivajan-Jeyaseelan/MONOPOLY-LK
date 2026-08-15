#include <stddef.h>

#include "../include/inflation_values_lk.h"


/*
 * Rule-LK 14
 *
 * New Value =
 * Previous Value × (1 + Inflation Rate)
 *
 * Percentage implementation:
 *
 * New Value =
 * Previous Value × (100 + Inflation Rate) / 100
 */
static int applyInflationRate(int value, int inflationRate){

    if(value <= 0){
        return value;
    }

    return value * (100 + inflationRate) / 100;

}

void updatePropertyValuesForInflation(Board board[], int inflationRate){

    if(board == NULL){
        return;
    }

    for(int i = 0; i < 40; i++){

        if(board[i].type != PROPERTY){
            continue;
        }


        Property *property = &board[i].property;


        property->purchasePrice = applyInflationRate(property->purchasePrice, inflationRate);

        property->houseCost = applyInflationRate(property->houseCost, inflationRate);

        property->hotelCost = applyInflationRate(property->hotelCost, inflationRate);

        property->baseRent = applyInflationRate(property->baseRent, inflationRate);

        property->currentRent = applyInflationRate(property->currentRent, inflationRate);

        property->repairCost = applyInflationRate(property->repairCost, inflationRate);

        property->currentValue = applyInflationRate(property->currentValue, inflationRate);

        property->mortgageValue = applyInflationRate(property->mortgageValue, inflationRate);

        if(property->insurance.active == 1){

            property->insurance.premium = applyInflationRate(property->insurance.premium, inflationRate);

            property->insurance.propertyValue = applyInflationRate(property->insurance.propertyValue, inflationRate);
        
        }
    }


    for(int i = 0; i < 40; i++){

        if(board[i].type != RAILWAY){
            continue;
        }


        board[i].railway.purchasePrice = applyInflationRate(board[i].railway.purchasePrice, inflationRate);

        board[i].railway.mortgageValue = applyInflationRate(board[i].railway.mortgageValue, inflationRate);
    
    }


    for(int i = 0; i < 40; i++){

        if(board[i].type != UTILITY){
            continue;
        }

        board[i].utility.purchasePrice = applyInflationRate(board[i].utility.purchasePrice, inflationRate);

        board[i].utility.mortgageValue = applyInflationRate(board[i].utility.mortgageValue, inflationRate);

    }

}