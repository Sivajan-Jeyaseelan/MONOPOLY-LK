#ifndef BANKRUPTCY_LK_H
#define BANKRUPTCY_LK_H

#include "types.h"

int hasRemainingAssets(Player *player, Board board[]);
void checkLoanBankruptcy(Player *player, Board board[]);

#endif