#ifndef INSURANCE_COMPANY_H
#define INSURANCE_COMPANY_H


#include "../types.h"


void purchaseInsurance(Player *player, Board board[]);
void renewInsurance(Player *player, Board *property);
void updateInsurance(Board board[]);


#endif