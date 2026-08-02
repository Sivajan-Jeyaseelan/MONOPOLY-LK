#include <stdio.h>

#include "../include/movement.h"

void movePlayer(Player *player, int steps){

    int oldPosition = player->position;

    player->position += steps;

    if(player->position >= 40){

        player->position = player->position - 40;

        player->money += 2000;

        printf("%s passed/landed on GO and received LKR 2000\n", player->name);

    }


    printf("%s moved from %d to %d\n", player->name, oldPosition, player->position);

}
