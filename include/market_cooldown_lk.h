#ifndef MARKET_COOLDOWN_LK_H
#define MARKET_COOLDOWN_LK_H

#include "types.h"

int canSelectMarketGroup(PropertyMarketState *market, int groupID, int currentRound);
void updateMarketCooldown(PropertyMarketState *market, int currentRound);

#endif