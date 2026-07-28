#include <stdio.h>
#include <string.h>

#include "../include/players.h"


void createPlayer(Player *player, int id, char name[]){

    player->id = id;

    strcpy(player->name, name);

    player->money = 30000;

    player->position = 0;

    player->bankrupt = 0;

    player->propertyCount = 0;




    player->loan.active = 0;

    player->loan.loanAmount = 0;

    player->loan.interest = 0;

    player->loan.collateralValue = 0;

    player->loan.maturity = 0;

}