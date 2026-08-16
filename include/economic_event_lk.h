#ifndef ECONOMIC_EVENT_LK_H
#define ECONOMIC_EVENT_LK_H

#include "types.h"

void triggerEconomicEvent(MonopolyLKState *state, Board board[], Player players[], int playerCount, int currentRound);
void displayEconomicEvent(MonopolyLKState *state);

#endif