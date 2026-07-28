#ifndef INSURANCE_POLICY_H
#define INSURANCE_POLICY_H

#include "../types.h"



int calculatePremium(Board *property, InsuranceType type);
int calculateLostRentalIncome(Board *property);
int calculateCompensation(Board *property, int repairCost);


#endif