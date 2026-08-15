#include <stdio.h>


#include "../include/property.h"
#include "../include/dept.h"


void purchaseProperty(Player *player, Board *property){

    int price = property->property.purchasePrice;

    if(player->money < price){

        printf("Not enough money\n");
        return;

    }

    player->money -= price;

    property->property.ownerID = player->id;

    player->propertyCount++;

    printf("%s purchased %s\n", player->name, property->name);

}


void auctionProperty(Player players[], int playerCount, Board *property){

    int highestBid = 0;
    int winner = -1;

    for(int i = 0; i < playerCount; i++){

        if(players[i].bankrupt == 1){

            printf("%s is bankrupt. Skipping auction\n", players[i].name);
            continue;

        }

        int bid;

        while(1){

            printf("%s enter bid: ", players[i].name);
            scanf("%d",&bid);


            if(bid % 250 != 0){

                printf("Invalid bid. Must increase by LKR 250\n");
                continue;

            }

            if(bid > players[i].money){

                printf("Insufficient money\n");
                continue;

            }


            break;

        }

        if(bid > highestBid){

            highestBid = bid;
            winner = i;

        }

    }

    if(winner != -1){

        players[winner].money -= highestBid;

        property->property.ownerID = players[winner].id;

        players[winner].propertyCount++;


        printf("%s won auction\n", players[winner].name);

    }else{

        printf("No valid bidder. Property remains with Bank\n");

    }

}


void resolveProperty(Player *player, Player players[], int playerCount, Board board[]){

    Board *currentSquare = &board[player->position];


    if(currentSquare->type != PROPERTY){

        return;

    }

    if(currentSquare->property.ownerID == -1){

        int choice;

        printf("%s landed on %s\n", player->name, currentSquare->name);

        printf("Price: LKR %d\n", currentSquare->property.purchasePrice);

        printf("1. Buy\n");
        printf("2. Refuse\n");

        printf("Choice: ");
        scanf("%d",&choice);

        if(choice == 1){

            purchaseProperty(player,currentSquare);

        }
        else{

            printf("Property goes to auction\n");

            auctionProperty(players,playerCount,currentSquare);

        }

    }else if(currentSquare->property.ownerID != player->id){

        int owner = currentSquare->property.ownerID;

        if(currentSquare->property.mortgageStatus == 1){

            printf("%s landed on %s\n", player->name, currentSquare->name);

            printf("Property is mortgaged. No rent collected.\n");

            return;

        }

        int rent = currentSquare->property.baseRent;

        printf("Rent Due : LKR %d\n", rent);
        printf("Owner : %s\n", players[owner].name);


        if(player->money >= rent){

            player->money -= rent;
            players[owner].money += rent;

            printf("%s paid LKR %d rent to %s\n", player->name, rent, players[owner].name);
            printf("Remaining Balance : LKR %d\n", player->money);

        }else{

            printf("%s cannot immediately pay the rent.\n", player->name);

            recoverDebt(player, rent, board);

        }

    }

}