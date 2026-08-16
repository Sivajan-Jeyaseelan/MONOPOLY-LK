#ifndef DISASTER_LK_H
#define DISASTER_LK_H

#include "types.h"

DisasterType lkGenerateDisaster(void);
int lkShouldTriggerDisaster(int round);
void lkApplyDisaster(DisasterType disaster, Board board[], Player players[]);

#endif