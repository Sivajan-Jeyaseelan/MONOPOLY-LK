#ifndef AUCTION_LK_H
#define AUCTION_LK_H

#include "types.h"

void startAuction(Auction *auction, Board *property);
int conductAuction(Auction *auction, Player players[], int playerCount, Board *property);

#endif