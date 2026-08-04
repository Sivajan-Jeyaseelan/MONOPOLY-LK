#include <stdio.h>

#include "../include/building.h"
#include "../include/monopoly.h"


void buildHouse(Player *player, Board *propertySquare, Board board[]){

    if(canBuild(player, propertySquare, board) == 0){

        printf("Construction not allowed on %s\n", propertySquare->name);
        return;

    }

    if(propertySquare->property.buildings == HOTEL){

        printf("%s already has a hotel\n", propertySquare->name);
        return;

    }

    int cost = propertySquare->property.houseCost;

    if(player->money < cost){

        printf("Not enough money to build a house\n");
        return;

    }

    player->money -= cost;

    propertySquare->property.buildings = HOUSE;

    printf("%s built a house on %s\n", player->name, propertySquare->name);

}


void buildHotel(Player *player, Board *propertySquare, Board board[]){

    if(canBuild(player, propertySquare, board) == 0){

        printf("Cannot build hotel on %s\n", propertySquare->name);
        return;

    }


    if(propertySquare->property.buildings != HOUSE){

        printf("Cannot build hotel. Build a house first\n");
        return;

    }


    int cost = propertySquare->property.hotelCost;


    if(player->money < cost){

        printf("Not enough money to build hotel\n");
        return;

    }


    player->money -= cost;

    propertySquare->property.buildings = HOTEL;

    printf("%s built a hotel on %s\n", player->name, propertySquare->name);

}


void checkBuilding(Player *player, Board board[]){

    for(int i = 0; i < 40; i++){

        if(board[i].type == PROPERTY && board[i].property.ownerID == player->id){

            if(canBuild(player, &board[i], board)){

                if(board[i].property.buildings == NO_BUILDING){

                    buildHouse(player, &board[i], board);

                }else if(board[i].property.buildings == HOUSE){

                    buildHotel(player, &board[i], board);

                }

            }

        }

    }
    
}