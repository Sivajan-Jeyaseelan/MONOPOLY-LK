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

    player->taxesDue = 0;

    player->insuranceClaims = 0;

    player->inJail = 0;

    player->jailTurns = 0;



    player->loan.active = 0;

    player->loan.loanAmount = 0;

    player->loan.interest = 0;

    player->loan.collateralValue = 0;

    player->loan.maturity = 20;

    player->loan.originalAmount = 0;

    player->loan.remainingRounds = 0;

    player->loan.accumulatedInterest = 0;



    
    player->loanLockedAssetCount = 0;

}