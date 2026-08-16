#ifndef PROPERTY_MARKET_LK_H
#define PROPERTY_MARKET_LK_H

#include "types.h"

void updatePropertyMarket(MonopolyLKState *state, Board board[], int boardSize, int currentRound);
void displayPropertyMarket(PropertyMarketState *market);

#endif