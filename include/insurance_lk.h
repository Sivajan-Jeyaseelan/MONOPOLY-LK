#ifndef INSURANCE_LK_H
#define INSURANCE_LK_H

#include "types.h"

int calculateInsurancePremium(Property *property, InsuranceType type);
int getInsuranceCoverage(InsuranceType type);

int canPurchaseInsurance(Player *player, Board board[]);
int purchaseInsurance(Player *player, Board board[], int propertyIndex, InsuranceType type);

#endif