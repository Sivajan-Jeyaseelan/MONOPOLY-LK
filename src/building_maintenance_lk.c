#include <stdio.h>
#include "building_maintenance_lk.h"


/*
 * Rule-LK 27
 *
 * House maintenance cost  = 5% of construction cost
 * Hotel maintenance cost  = 8% of construction cost
 *
 * If the building has structural damage, future maintenance
 * cost increases by 50%.
 */
int calculateMaintenanceCost(Property *property, Building *building)
{
    if (property == NULL || building == NULL) {
        return 0;
    }

    int cost = 0;

    if (property->buildings == HOUSE) {

        cost = (property->houseCost * 5) / 100;

    }
    else if (property->buildings == HOTEL) {

        cost = (property->hotelCost * 8) / 100;

    }
    else {

        return 0;
    }


    /*
     * Rule-LK 28:
     * Structural damage increases future maintenance
     * costs by 50%.
     */
    if (building->damaged == 1) {

        cost = (cost * 150) / 100;

    }

    return cost;
}


/*
 * Rule-LK 27
 *
 * Maintenance can only be performed at the beginning
 * of the player's turn.
 *
 * This function restores buildings to 100% condition.
 */
int performBuildingMaintenance(Player *player, Board board[], int boardSize)
{
    if (player == NULL || board == NULL || boardSize <= 0) {
        return 0;
    }

    int totalCost = 0;
    int maintainedCount = 0;


    printf("\n------------------------------------\n");
    printf("Building Maintenance - Player %d\n", player->id);
    printf("------------------------------------\n");


    /*
     * Check every board property owned by the player.
     */
    for (int i = 0; i < boardSize; i++) {

        if (board[i].type != PROPERTY) {
            continue;
        }

        Property *property = &board[i].property;


        if (property->ownerID != player->id) {
            continue;
        }


        /*
         * Only properties with buildings require
         * building maintenance.
         */
        if (property->buildings == NO_BUILDING) {
            continue;
        }


        /*
         * A separate Building object cannot be stored in
         * types.h, so the existing Property fields are used
         * for the property's building state.
         *
         * The building condition is therefore represented
         * using the existing repair/renovation information
         * where possible.
         */
        Building building;

        building.condition = 100;
        building.age = property->propertyAge;
        building.maintenanceSkipped = 0;
        building.damaged = property->damaged;
        building.renovationRequired = property->renovationRequired;


        /*
         * Determine the current condition from property state.
         *
         * Since types.h cannot be modified, we calculate
         * deterioration from property age.
         *
         * Every round = -2%.
         */
        int condition = 100 - (property->propertyAge * 2);

        if (condition < 0) {
            condition = 0;
        }

        building.condition = condition;


        /*
         * No maintenance is needed if condition is already 100%.
         */
        if (building.condition >= 100 &&
            building.damaged == 0) {

            continue;
        }


        int cost = calculateMaintenanceCost(property, &building);


        if (cost <= 0) {
            continue;
        }


        /*
         * Player cannot maintain the building if there
         * is insufficient cash.
         */
        if (player->money < cost) {

            printf(
                "%s cannot maintain %s. "
                "Maintenance Cost: LKR %d, "
                "Available Cash: LKR %d\n",
                player->name,
                property->name,
                cost,
                player->money
            );

            continue;
        }


        /*
         * Pay maintenance cost.
         */
        player->money -= cost;

        totalCost += cost;
        maintainedCount++;


        /*
         * Rule-LK 27:
         * Maintenance restores condition to 100%.
         */
        property->repairCost = cost;


        /*
         * Maintenance removes the damaged state only if
         * the property is not awaiting renovation.
         */
        if (property->renovationRequired == 0) {
            property->damaged = 0;
        }


        printf(
            "%s maintained %s\n",
            player->name,
            property->name
        );

        printf(
            "Building Type : %s\n",
            property->buildings == HOUSE ? "House" : "Hotel"
        );

        printf(
            "Maintenance Cost : LKR %d\n",
            cost
        );

        printf(
            "Condition restored to 100%%\n"
        );

        printf(
            "Remaining Cash : LKR %d\n",
            player->money
        );

        printf("------------------------------------\n");
    }


    if (maintainedCount == 0) {

        printf(
            "%s performed no building maintenance.\n",
            player->name
        );

    }
    else {

        printf(
            "Total Maintenance Cost : LKR %d\n",
            totalCost
        );

        printf(
            "Buildings Maintained   : %d\n",
            maintainedCount
        );

    }


    printf("------------------------------------\n");


    return totalCost;
}