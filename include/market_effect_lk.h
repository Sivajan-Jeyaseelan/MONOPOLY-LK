#ifndef MARKET_EFFECT_LK_H
#define MARKET_EFFECT_LK_H

#include "types.h"

void applyCumulativeMarketEffects(Property *property);
int calculateCombinedPercentage(int baseValue, int effects[], int effectCount);

#endif