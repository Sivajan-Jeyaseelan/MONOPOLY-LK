#ifndef ECONOMIC_LK_H
#define ECONOMIC_LK_H

#include "types.h"

EconomicEventType generateEconomicEvent(void);
void applyEconomicEvent(EconomicEventType event, EconomicState *economy, Board board[]);

#endif