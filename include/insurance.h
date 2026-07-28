#ifndef INSURANCE_H
#define INSURANCE_H

#include "types.h"


int calculatePremium(Board *property, InsuranceType type);
int calculateLostRentalIncome(Board *property);
int calculateCompensation(Board *property, int repairCost);
void applyDisaster(Board *property, Player *owner, int repairCost);
void purchaseInsurance(Player *player, Board board[]);
void renewInsurance(Player *player, Board *property);
void updateInsurance(Board board[]);



#endif