#ifndef BUILDING_MAINTENANCE_LK_H
#define BUILDING_MAINTENANCE_LK_H

#include "types.h"

int performBuildingMaintenance(Player *player, Board board[], int boardSize);
int calculateMaintenanceCost(Property *property, Building *building);

#endif