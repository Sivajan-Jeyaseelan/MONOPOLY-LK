#ifndef DISASTER_H
#define DISASTER_H


#include "../types.h"

int calculatePremium(Board *property, InsuranceType type);
int calculateLostRentalIncome(Board *property);
int calculateCompensation(Board *property, int repairCost);

void purchaseInsurance(Player *player, Board board[]);
void renewInsurance(Player *player, Board *property);
void updateInsurance(Board board[]);

void applyDisaster(Board *property, Player *owner, int repairCost);


#endif