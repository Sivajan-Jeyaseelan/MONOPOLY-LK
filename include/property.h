#ifndef PROPERTY_H
#define PROPERTY_H

#include "types.h"


void purchaseProperty(Player *player, Board *property);
void auctionProperty(Player players[], int playerCount, Board *property);
void resolveProperty(Player *player, Player players[], int playerCount, Board board[]);


#endif