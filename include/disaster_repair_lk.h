#ifndef DISASTER_REPAIR_LK_H
#define DISASTER_REPAIR_LK_H

#include "types.h"

int lkCalculateRepairCost(Property *property);
void lkRepairDamagedProperties(Player *player, Board board[]);

#endif