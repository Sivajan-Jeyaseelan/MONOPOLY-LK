#ifndef LOAN_TRANSACTION_LK_H
#define LOAN_TRANSACTION_LK_H

#include "types.h"

int executeLoanAction(Player *player, Board board[], LoanAction action);
int canExecuteLoanAction(Player *player, Board board[], LoanAction action);

#endif