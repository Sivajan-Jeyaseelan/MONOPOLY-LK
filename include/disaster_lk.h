#ifndef DISASTER_LK_H
#define DISASTER_LK_H

#include "types.h"

DisasterType generateDisaster(void);
int shouldTriggerDisaster(int round);
void applyDisaster(DisasterType disaster, Board board[], Player players[]);

#endif