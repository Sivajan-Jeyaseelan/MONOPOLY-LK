#ifndef BANK_H
#define BANK_H

#include "types.h"

int calculateMaxLoan(Player player, Board board[]);
void obtainLoan(Player *player, Board board[]);
void repayLoan(Player *player, int amount);
void applyLoanInterest(Player players[], int playerCount);
void foreclosure(Player *player, Board board[]);
void bankTransaction(Player *player, Board board[]);
void refinanceLoan(Player *player, Board board[]);
void increaseLoan(Player *player, Board board[]);
void repayFullLoan(Player *player);
void checkLoanMaturity(Player players[], int playerCount, Board board[]);



#endif