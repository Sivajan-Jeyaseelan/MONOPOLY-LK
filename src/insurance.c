#include <stdio.h>

#include "../include/insurance.h"


void processDisaster(Board *property, Player *owner, int repairCost){

    applyDisaster(property, owner, repairCost);

}


void buyInsurance(Player *player, Board board[]){

    purchaseInsurance(player, board);

}


void renewPolicy(Player *player, Board *property){

    renewInsurance(player, property);

}


void updateInsuranceSystem(Board board[]){

    updateInsurance(board);

}