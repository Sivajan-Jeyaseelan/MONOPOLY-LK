#include <stdio.h>

#include "../include/depreciation_value_lk.h"

#define BOARD_SIZE 40
#define DEPRECIATION_START_AGE 50
#define DEPRECIATION_INTERVAL 5
#define DEPRECIATION_RATE 1
#define MAX_DEPRECIATION 30


int calculateDepreciatedValue(Property *property){

    if(property == NULL){
        return 0;
    }

    if(property->currentValue <= 0){
        return 0;
    }

    return property->currentValue * (100 - DEPRECIATION_RATE) / 100;
    
}

void applyPropertyDepreciation(Board board[]){

    if(board == NULL){
        return;
    }

    for(int i = 0; i < BOARD_SIZE; i++){

        if(board[i].type != PROPERTY){
            continue;
        }

        Property *property = &board[i].property;

        if(property->ownerID <= 0){
            continue;
        }

        if(property->propertyAge <= DEPRECIATION_START_AGE){
            continue;
        }

        if(property->propertyAge % DEPRECIATION_INTERVAL != 0){
            continue;
        }

        if(property->depreciation >= MAX_DEPRECIATION){

            property->depreciation = MAX_DEPRECIATION;
            continue;

        }

        property->depreciation += DEPRECIATION_RATE;

        if(property->depreciation > MAX_DEPRECIATION){

            property->depreciation = MAX_DEPRECIATION;

        }

        property->currentValue = calculateDepreciatedValue(property);

        if(property->baseRent > 0){

            property->currentRent = property->baseRent * (100 - property->depreciation) / 100;

        }

        property->renovationRequired = 1;

        printf("\n");
        printf("=====================================\n");
        printf("Property Depreciation\n");
        printf("=====================================\n");

        printf("Property : %s\n", property->name);

        printf("Property Age : %d rounds\n", property->propertyAge);

        printf("Depreciation : %d%%\n", property->depreciation);

        printf("Current Value : LKR %d\n", property->currentValue);

        printf("Current Rent : LKR %d\n", property->currentRent);

        printf("Renovation Required : Yes\n");

        printf("=====================================\n");

    }

}