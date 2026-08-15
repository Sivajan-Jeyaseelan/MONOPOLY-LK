#ifndef LOAN_DEFAULT_LK_H
#define LOAN_DEFAULT_LK_H

#include "types.h"

int isLoanDefaulted(Player *player);
void processLoanDefault(Player *player, Board board[]);

#endif