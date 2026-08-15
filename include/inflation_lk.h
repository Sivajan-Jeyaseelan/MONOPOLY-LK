#ifndef INFLATION_LK_H
#define INFLATION_LK_H

#include "types.h"

int generateInflationRate(void);
void applyInflation(EconomicState *economy, Board board[]);

#endif