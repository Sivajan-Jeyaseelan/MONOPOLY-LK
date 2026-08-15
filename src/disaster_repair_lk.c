#include <stdio.h>

#include "../include/disaster_repair_lk.h"


int calculateRepairCost(Property *property){

    if(property == NULL){
        return 0;
    }

    if(property->currentValue <= 0){
        return 0;
    }

    if(property->repairCost > 0){
        return property->repairCost;
    }

    return property->currentValue * 10 / 100;

}


void repairDamagedProperties(Player *player, Board board[]){

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

        if(property->damaged == 0){
            continue;
        }


        int repairCost = calculateRepairCost(property);

        if(repairCost <= 0){
            continue;
        }

        if(player->money < repairCost){

            printf("%s cannot afford to repair %s.\n", player->name, property->name);
            printf("Repair Cost : LKR %d\n", repairCost);
            printf("Property remains damaged.\n");

            property->currentRent = 0;

            continue;

        }

        player->money -= repairCost;

        property->damaged = 0;

        property->repairCost = 0;

        property->insurance.disasterActive = 0;

        property->currentRent = property->baseRent;


        printf("\n");
        printf("=====================================\n");
        printf("Property Repair\n");
        printf("=====================================\n");

        printf("Owner : %s\n", player->name);

        printf("Property : %s\n", property->name);

        printf("Repair Cost : LKR %d\n", repairCost);

        printf("Repair completed automatically.\n");

        printf("Remaining Balance : LKR %d\n", player->money);

        printf("Rent collection restored.\n");

        printf("=====================================\n");

    }

}