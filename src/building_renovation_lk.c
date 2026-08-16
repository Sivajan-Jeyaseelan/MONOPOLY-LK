#include <stdio.h>
#include "building_renovation_lk.h"


/*
 * Rule-LK 29
 *
 * Renovation cost = 25% of replacement value.
 *
 * Renovation restores:
 *  - property value
 *  - rental value
 *  - building condition
 */
int calculateRenovationCost(Property *property, Building *building)
{
    if (property == NULL || building == NULL) {
        return 0;
    }

    int replacementValue = 0;


    /*
     * For a house, use the house construction cost.
     */
    if (property->buildings == HOUSE) {

        replacementValue = property->houseCost;

    }
    /*
     * For a hotel, use the hotel construction cost.
     */
    else if (property->buildings == HOTEL) {

        replacementValue = property->hotelCost;

    }
    else {

        return 0;
    }


    /*
     * Rule-LK 29:
     * Renovation costs 25% of replacement value.
     */
    return (replacementValue * 25) / 100;
}


/*
 * Rule-LK 29
 *
 * Renovate a damaged building.
 */
int renovateBuilding(
    Player *player,
    Property *property,
    Building *building
)
{
    if (player == NULL ||
        property == NULL ||
        building == NULL) {

        return 0;
    }


    /*
     * Renovation is only required for damaged buildings.
     */
    if (property->damaged == 0 &&
        property->renovationRequired == 0) {

        return 0;
    }


    int renovationCost =
        calculateRenovationCost(property, building);


    if (renovationCost <= 0) {

        return 0;
    }


    /*
     * Player must have enough money.
     */
    if (player->money < renovationCost) {

        printf(
            "%s cannot renovate %s.\n",
            player->name,
            property->name
        );

        printf(
            "Renovation Cost : LKR %d\n",
            renovationCost
        );

        printf(
            "Available Cash  : LKR %d\n",
            player->money
        );

        return 0;
    }


    /*
     * Save the original property value and rent.
     *
     * Structural damage reduced them by:
     *      value -> 85%
     *      rent  -> 75%
     *
     * Therefore, restore the approximate original values.
     *
     * value:
     *     damaged = original * 85 / 100
     *     original = damaged * 100 / 85
     *
     * rent:
     *     damaged = original * 75 / 100
     *     original = damaged * 100 / 75
     */
    int restoredValue =
        (property->currentValue * 100) / 85;

    int restoredRent =
        (property->currentRent * 100) / 75;


    /*
     * Pay renovation cost.
     */
    player->money -= renovationCost;


    /*
     * Restore property value.
     */
    property->currentValue = restoredValue;


    /*
     * Restore rental value.
     */
    property->currentRent = restoredRent;


    /*
     * Rule-LK 29:
     * Building condition restored to 100%.
     */
    building->condition = 100;


    /*
     * Reset maintenance/damage state.
     */
    building->maintenanceSkipped = 0;
    building->damaged = 0;
    building->renovationRequired = 0;


    property->damaged = 0;
    property->renovationRequired = 0;


    /*
     * Store renovation cost.
     */
    property->repairCost = renovationCost;


    /*
     * Output required for the simulation.
     */
    printf("\n");
    printf("=====================================\n");
    printf("BUILDING RENOVATION\n");
    printf("=====================================\n");

    printf("Player   : %s\n",
           player->name);

    printf("Property : %s\n",
           property->name);

    printf("Building : %s\n",
           property->buildings == HOUSE
               ? "House"
               : "Hotel");

    printf("Renovation Cost : LKR %d\n",
           renovationCost);

    printf("Property Value Restored : LKR %d\n",
           property->currentValue);

    printf("Rental Value Restored : LKR %d\n",
           property->currentRent);

    printf("Building Condition : 100%%\n");

    printf("Structural Damage : Repaired\n");

    printf("Remaining Cash : LKR %d\n",
           player->money);

    printf("=====================================\n");


    return renovationCost;
}