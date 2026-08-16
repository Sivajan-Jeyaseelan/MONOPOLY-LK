#include <stdio.h>

#include "../include/renovation_lk.h"


/*int calculateRenovationCost(Property *property){

    if(property == NULL){
        return 0;
    }

    if(property->currentValue <= 0){
        return 0;
    }

    return property->currentValue * 10 / 100;

}


void renovateProperty(Player *player, Property *property){

    if(player == NULL || property == NULL){
        return;
    }

    if(property->ownerID != player->id){
        return;
    }

    if(property->depreciation <= 0){
        return;
    }

    int renovationCost = calculateRenovationCost(property);

    if(renovationCost <= 0){
        return;
    }

    if(player->money < renovationCost){

        printf("\n");
        printf("=====================================\n");
        printf("Renovation Failed\n");
        printf("=====================================\n");

        printf("%s cannot afford to renovate %s.\n", player->name, property->name);

        printf("Renovation Cost : LKR %d\n", renovationCost);

        printf("Current Balance : LKR %d\n", player->money);

        printf("=====================================\n");

        return;

    }

    player->money -= renovationCost;

    if(property->depreciation > 0){

        property->currentValue = property->currentValue * 100 / (100 - property->depreciation);
        
    }

    property->depreciation = 0;

    property->propertyAge = 0;

    property->renovationRequired = 0;

    property->currentRent = property->baseRent;


    printf("\n");
    printf("=====================================\n");
    printf("Property Renovation\n");
    printf("=====================================\n");

    printf("Owner : %s\n", player->name);

    printf("Property : %s\n", property->name);

    printf("Renovation Cost : LKR %d\n", renovationCost);

    printf("Depreciation : 0%%\n");

    printf("Property Age : 0 rounds\n");

    printf("Current Value : LKR %d\n", property->currentValue);

    printf("Current Rent : LKR %d\n", property->currentRent);

    printf("Remaining Balance : LKR %d\n", player->money);

    printf("Renovation completed successfully.\n");

    printf("=====================================\n");

}*/