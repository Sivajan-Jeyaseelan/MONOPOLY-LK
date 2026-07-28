#ifndef BOARD_FACTORY_H
#define BOARD_FACTORY_H

#include "../types.h"

void createSquare(Board *square, int id, char name[], SquareType type);
void createProperty(Board *square, int id, char name[], int group, int price, int mortgage, int rent, int house, int hotel);
void createRailway(Board *square, int id, char name[], int purchasePrice, int mortgageValue);
void createUtility(Board *square, int id, char name[], int purchasePrice, int mortgageValue);

#endif