#include <stdio.h>
#include "structural_damage_lk.h"


/*
 * Rule-LK 28
 *
 * If maintenance is ignored for more than 20 consecutive rounds:
 *
 * 1. Property value decreases by 15%
 * 2. Maximum rent decreases by 25%
 * 3. Future maintenance cost increases by 50%
 */
void checkStructuralDamage(Board board[], int boardSize)
{
    if (board == NULL || boardSize <= 0) {
        return;
    }


    for (int i = 0; i < boardSize; i++) {

        if (board[i].type != PROPERTY) {
            continue;
        }


        Property *property = &board[i].property;


        /*
         * Only properties with buildings can suffer
         * building structural damage.
         */
        if (property->buildings == NO_BUILDING) {
            continue;
        }


        /*
         * Rule-LK 28:
         * More than 20 consecutive rounds without
         * maintenance causes structural damage.
         *
         * Since Building is not stored inside Property
         * in the given types.h, renovationRequired and
         * damaged are used as the persistent state.
         *
         * propertyAge is used as the available age counter.
         */
        if (property->propertyAge <= 20) {
            continue;
        }


        /*
         * Do not apply structural damage repeatedly.
         */
        if (property->damaged == 1) {
            continue;
        }


        /*
         * Structural damage occurs.
         */
        property->damaged = 1;


        /*
         * Property value decreases by 15%.
         */
        property->currentValue =
            (property->currentValue * 85) / 100;


        /*
         * Maximum rent decreases by 25%.
         */
        property->currentRent =
            (property->currentRent * 75) / 100;


        /*
         * Renovation is now required.
         */
        property->renovationRequired = 1;


        /*
         * Existing repairCost field can be used to store
         * the new maintenance cost caused by damage.
         *
         * Future maintenance costs increase by 50%.
         */
        if (property->buildings == HOUSE) {

            property->repairCost =
                (property->houseCost * 5 * 150) / 10000;

        }
        else if (property->buildings == HOTEL) {

            property->repairCost =
                (property->hotelCost * 8 * 150) / 10000;

        }


        printf("\n");
        printf("=====================================\n");
        printf("STRUCTURAL DAMAGE\n");
        printf("=====================================\n");

        printf("Property : %s\n", property->name);

        printf("Building : %s\n",
               property->buildings == HOUSE
                   ? "House"
                   : "Hotel");

        printf("Maintenance ignored for more than 20 rounds.\n");

        printf("Property Value reduced by 15%%.\n");

        printf("New Property Value : LKR %d\n",
               property->currentValue);

        printf("Maximum Rent reduced by 25%%.\n");

        printf("New Maximum Rent : LKR %d\n",
               property->currentRent);

        printf("Future maintenance cost increased by 50%%.\n");

        printf("Maintenance Cost : LKR %d\n",
               property->repairCost);

        printf("Renovation Required : Yes\n");

        printf("=====================================\n");
    }
}