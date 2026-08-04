#ifndef MONOPOLY_H
#define MONOPOLY_H

#include "types.h"


int checkMonopoly(Player *player, Board board[], int groupID);
int canBuild(Player *player, Board *property, Board board[]);


#endif