#ifndef REGIONAL_EXPIRY_LK_H
#define REGIONAL_EXPIRY_LK_H

#include "types.h"

void expireRegionalDevelopment(MonopolyLKState *state, Board board[], int boardSize);
void restoreRegionalValues(Board board[], int boardSize);

#endif