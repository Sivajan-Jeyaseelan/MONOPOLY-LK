#ifndef GAME_H
#define GAME_H

#include "types.h"


extern Player *allPlayers;
extern int totalPlayers;

void setPlayers(Player players[], int playerCount);
void determineFirstPlayer(Player players[], int turnOrder[]);
void playTurn(Player *player, Board board[]);

int countActivePlayers(Player players[], int totalPlayers);
int checkGameOver(Player players[], int totalPlayers);
Player* findWinner(Player players[], int totalPlayers, Board board[]);


#endif