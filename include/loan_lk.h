#ifndef LOAN_LK_H
#define LOAN_LK_H

#include "types.h"

// Rule LK 1
int calculateEligibleCollateral(Player *player, Board board[]);
int hasLoanCollateral(Player *player, Board board[]);

// Rule LK 2 
int calculateMaximumLoan(Player *player, Board board[]);

#endif