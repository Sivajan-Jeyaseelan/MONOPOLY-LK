#include <stdio.h>
#include <stdlib.h>

#include "../include/disaster_lk.h"
#include "../include/disaster_repair_lk.h"


int shouldTriggerDisaster(int round){

    if(round <= 0){
        return 0;
    }

    return (round % 10 == 0);

}

DisasterType generateDisaster(void){

    int disaster = rand() % 5;

    switch(disaster){

        case 0:
            return FIRE;

        case 1:
            return FLOOD;

        case 2:
            return RIOT;

        case 3:
            return BUILDING_COLLAPSE;

        case 4:
            return ELECTRICAL_FAILURE;

        default:
            return NO_DISASTER;

    }

}

static const char *getDisasterName(DisasterType disaster){

    switch(disaster){

        case FIRE:
            return "Fire";

        case FLOOD:
            return "Flood";

        case RIOT:
            return "Riot";

        case BUILDING_COLLAPSE:
            return "Building Collapse";

        case ELECTRICAL_FAILURE:
            return "Electrical Failure";

        default:
            return "No Disaster";

    }

}

static int calculateDisasterDamage(Property *property, DisasterType disaster){

    if(property == NULL){
        return 0;
    }

    if(property->currentValue <= 0){
        return 0;
    }

    switch(disaster){

        case FIRE:
            return property->currentValue * 20 / 100;

        case FLOOD:
            return property->currentValue * 25 / 100;

        case RIOT:
            return property->currentValue * 15 / 100;

        case BUILDING_COLLAPSE:
            return property->currentValue * 30 / 100;

        case ELECTRICAL_FAILURE:
            return property->currentValue * 10 / 100;

        default:
            return 0;

    }

}


void applyDisaster(DisasterType disaster, Board board[], Player players[]){

    if(board == NULL || players == NULL){
        return;
    }

    if(disaster == NO_DISASTER){
        return;
    }

    int developedCount = 0;

    for(int i = 0; i < 40; i++){

        if(board[i].type != PROPERTY){
            continue;
        }

        if(board[i].property.ownerID <= 0){
            continue;
        }

        if(board[i].property.buildings == NO_BUILDING){
            continue;
        }

        if(board[i].property.damaged == 1){
            continue;
        }

        developedCount++;

    }

    if(developedCount == 0){

        printf("\n");
        printf("Disaster occurred, but no developed property was available.\n");
        return;

    }

    int selected = rand() % developedCount;

    int selectedBoardIndex = -1;

    int current = 0;

    for(int i = 0; i < 40; i++){

        if(board[i].type != PROPERTY){
            continue;
        }

        if(board[i].property.ownerID <= 0){
            continue;
        }

        if(board[i].property.buildings == NO_BUILDING){
            continue;
        }

        if(board[i].property.damaged == 1){
            continue;
        }

        if(current == selected){

            selectedBoardIndex = i;
            break;
        }

        current++;

    }

    if(selectedBoardIndex == -1){
        return;
    }

    Property *property = &board[selectedBoardIndex].property;


    int ownerID = property->ownerID;

    if(ownerID <= 0){
        return;
    }

    Player *owner = NULL;

    for(int i = 0; i < 4; i++){

        if(players[i].id == ownerID){

            owner = &players[i];
            break;

        }

    }

    if(owner == NULL){
        return;
    }


    int repairCost = calculateDisasterDamage(property, disaster);

    if(repairCost <= 0){
        return;
    }

    property->damaged = 1;

    property->repairCost = repairCost;

    property->currentRent = 0;


    printf("\n");
    printf("=====================================\n");
    printf("Disaster\n");
    printf("=====================================\n");

    printf("Disaster : %s\n", getDisasterName(disaster));

    printf("Affected Property : %s\n", property->name);

    printf("Owner : %s\n", owner->name);

    printf("Repair Cost : LKR %d\n", repairCost);

    if(property->insurance.active == 1 && property->insurance.remainingRounds > 0){

        int coverage = property->insurance.coveragePercent;

        int compensation = repairCost * coverage / 100;

        owner->money += compensation;

        owner->insuranceClaims++;

        property->insurance.disasterActive = 1;

        printf("Insurance Claim Approved.\n");

        printf("Insurance Coverage : %d%%\n", coverage);

        printf("Compensation Paid : LKR %d\n", compensation);

        property->repairCost = repairCost - compensation;

    }else{

        printf("No active insurance coverage.\n");

        property->insurance.disasterActive = 0;

    }

    printf("Property is now damaged.\n");
    printf("Rent collection suspended until repair.\n");
    printf("=====================================\n");

}