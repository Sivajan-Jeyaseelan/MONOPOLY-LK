#include <stdlib.h>
#include "../include/dice.h"


int rollDice(){

    int dice1 = (rand() % 6) + 1;
    int dice2 = (rand() % 6) + 1;

    return dice1 + dice2;

}