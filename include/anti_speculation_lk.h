#ifndef ANTI_SPECULATION_LK_H
#define ANTI_SPECULATION_LK_H

#include "types.h"

int enforceAntiSpeculation(Player *player, Board board[], int boardSize);
void removeAntiSpeculation(Player *player);

#endif