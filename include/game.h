#ifndef GAME_H
#define GAME_H

#include "types.h"


extern Player *allPlayers;
extern int totalPlayers;

void setPlayers(Player players[], int playerCount);
void determineFirstPlayer(Player players[], int turnOrder[]);
void playTurn(Player *player, Board board[]);


#endif