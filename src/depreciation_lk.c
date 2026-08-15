#include <stdio.h>

#include "../include/depreciation_lk.h"

#define BOARD_SIZE 40

void increasePropertyAge(Board board[]){

    if(board == NULL){
        return;
    }

    for(int i = 0; i < BOARD_SIZE; i++){

        if(board[i].type != PROPERTY){
            continue;
        }

        Property *property = &board[i].property;

        if(property->ownerID <= 0){
            continue;
        }

        property->propertyAge++;

    }

}


void resetPropertyAge(Property *property){

    if(property == NULL){
        return;
    }

    property->propertyAge = 0;

}