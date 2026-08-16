#ifndef INSURANCE_LK_H
#define INSURANCE_LK_H

#include "types.h"

int lkCalculateInsurancePremium(Property *property, InsuranceType type);
int lkGetInsuranceCoverage(InsuranceType type);

int lkCanPurchaseInsurance(Player *player, Board board[]);
int lkPurchaseInsurance(Player *player, Board board[], int propertyIndex, InsuranceType type);

#endif