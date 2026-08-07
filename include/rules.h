#ifndef RULES_H
#define RULES_H

#include "types.h"

void resolveSquare(Player *player, Board board[]);
void handleIncomeTax(Player *player, Board *taxSquare);
void sendPlayerToJail(Player *player);
void handleJail(Player *player);

#endif