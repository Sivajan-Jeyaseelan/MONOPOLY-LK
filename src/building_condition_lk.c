#include <stdio.h>

#include "building_condition_lk.h"

#define MAX_BOARD_SIZE 40

/*
 * The current types.h does not store a Building inside Property.
 *
 * Therefore building state is maintained here.
 *
 * [propertyID][0] = house
 * [propertyID][1] = hotel
 */
static Building buildingState[MAX_BOARD_SIZE][2];


/*
 * Return the rent percentage according to Rule-LK 26.
 *
 * 90-100  -> 100%
 * 75-89   -> 90%
 * 50-74   -> 75%
 * 25-49   -> 50%
 * <25     -> 0%
 */
int getConditionRentMultiplier(int condition){

    if(condition >= 90){
        return 100;
    }

    if(condition >= 75){
        return 90;
    }

    if(condition >= 50){
        return 75;
    }

    if(condition >= 25){
        return 50;
    }

    return 0;
}


/*
 * Update building condition at the end of every round.
 *
 * Rule-LK 25:
 * Every building starts at 100%.
 * Condition decreases by 2% every round.
 */
void updateBuildingCondition(Board board[], int boardSize){

    if(board == NULL){
        return;
    }

    if(boardSize > MAX_BOARD_SIZE){
        boardSize = MAX_BOARD_SIZE;
    }

    printf("\n");
    printf("------------------------------------\n");
    printf("Building Condition Processing\n");
    printf("------------------------------------\n");

    for(int i = 0; i < boardSize; i++){

        if(board[i].type != PROPERTY){
            continue;
        }

        Property *property = &board[i].property;

        /*
         * No building on this property.
         */
        if(property->houseCount <= 0 &&
           property->buildings != HOTEL){

            continue;
        }


        /*
         * HOUSE
         */
        if(property->houseCount > 0){

            Building *house = &buildingState[i][0];

            /*
             * First time seeing this building.
             */
            if(house->condition == 0 &&
               house->age == 0 &&
               house->maintenanceSkipped == 0){

                house->condition = 100;
            }


            if(house->condition > 0){

                house->condition -= 2;

                if(house->condition < 0){
                    house->condition = 0;
                }

            }

            house->age++;
            house->maintenanceSkipped++;


            /*
             * Structural damage after more than
             * 20 consecutive rounds without maintenance.
             */
            if(house->maintenanceSkipped > 20 &&
               house->damaged == 0){

                house->damaged = 1;
                house->renovationRequired = 1;

                /*
                 * Rule-LK 28:
                 * Property value decreases by 15%.
                 */
                property->currentValue = (property->currentValue * 85) / 100;

                property->currentRent = (property->currentRent * 75) / 100;

       
                property->repairCost = (property->repairCost * 150) / 100;

                printf("\n");
                printf("=====================================\n");
                printf("STRUCTURAL DAMAGE\n");
                printf("=====================================\n");
                printf("Property : %s\n", property->name);
                printf("Building : House\n");
                printf("Condition: %d%%\n", house->condition);
                printf("Property value reduced by 15%%.\n");
                printf("Maximum rent reduced by 25%%.\n");
                printf("Future maintenance cost increased by 50%%.\n");
                printf("Renovation required.\n");
                printf("=====================================\n");

            }

        }


        /*
         * HOTEL
         */
        if(property->buildings == HOTEL){

            Building *hotel = &buildingState[i][1];

            if(hotel->condition == 0 &&
               hotel->age == 0 &&
               hotel->maintenanceSkipped == 0){

                hotel->condition = 100;
            }


            if(hotel->condition > 0){

                hotel->condition -= 2;

                if(hotel->condition < 0){
                    hotel->condition = 0;
                }

            }

            hotel->age++;
            hotel->maintenanceSkipped++;


            if(hotel->maintenanceSkipped > 20 &&
               hotel->damaged == 0){

                hotel->damaged = 1;
                hotel->renovationRequired = 1;

                property->currentValue =
                    (property->currentValue * 85) / 100;

                property->currentRent =
                    (property->currentRent * 75) / 100;

                property->repairCost =
                    (property->repairCost * 150) / 100;

                printf("\n");
                printf("=====================================\n");
                printf("STRUCTURAL DAMAGE\n");
                printf("=====================================\n");
                printf("Property : %s\n", property->name);
                printf("Building : Hotel\n");
                printf("Condition: %d%%\n", hotel->condition);
                printf("Property value reduced by 15%%.\n");
                printf("Maximum rent reduced by 25%%.\n");
                printf("Future maintenance cost increased by 50%%.\n");
                printf("Renovation required.\n");
                printf("=====================================\n");

            }

        }

    }

}