#ifndef GAME_H
#define GAME_H

#include "types.h"

void determineFirstPlayer(Player players[], int turnOrder[]);
void playTurn(Player *player, Board board[]);

#endif