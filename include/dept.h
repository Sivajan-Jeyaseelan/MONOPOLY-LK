#ifndef DEPT_H
#define DEPT_H

#include "types.h"

void recoverDebt(Player *player, int amount, Board board[]);
void sellBuildings(Player *player, Board board[]);
void mortgageProperties(Player *player, Board board[]);
int calculateAssets(Player *player, Board board[]);

#endif