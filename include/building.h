#ifndef BUILDING_H
#define BUILDING_H

#include "types.h"


void buildHouse(Player *player, Board *propertySquare, Board board[]);
void buildHotel(Player *player, Board *propertySquare, Board board[]);

void checkBuilding(Player *player, Board board[]);

int canBuildHouseEvenly(Board board[], int groupID, Board *property);


#endif