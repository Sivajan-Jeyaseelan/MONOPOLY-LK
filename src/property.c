#include <stdio.h>


#include "../include/property.h"
#include "../include/dept.h"
#include "../include/auction_lk.h"


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

/*
void auctionProperty(Player players[], int playerCount, Board *property){

    int highestBid = 0;
    int winner = -1;

    for(int i = 0; i < playerCount; i++){

        if(players[i].bankrupt == 1){

            printf("%s is bankrupt. Skipping auction\n", players[i].name);
            continue;

        }

        int bid;

        if(players[i].money >= property->property.purchasePrice){

            bid = property->property.purchasePrice;

        }else{

            bid = (players[i].money / 2 / 250) * 250;

        }

        if(bid > players[i].money){

            bid = (players[i].money / 250) * 250;

        }

        if(bid > highestBid){

            highestBid = bid;
            winner = i;

            printf("%s bids LKR %d\n", players[i].name, bid);

        }

    }

    if(winner != -1 && highestBid > 0){

        players[winner].money -= highestBid;

        property->property.ownerID = players[winner].id;

        players[winner].propertyCount++;


        printf("%s won the auction for LKR %d\n", players[winner].name, highestBid);

    }else{

        printf("No valid bidder. Property remains with Bank\n");

    }

}
*/

void resolveProperty(Player *player, Player players[], int playerCount, Board board[]){

    Board *currentSquare = &board[player->position];


    if(currentSquare->type != PROPERTY){

        return;

    }

    if(currentSquare->property.ownerID == -1){

        printf("%s landed on %s\n", player->name, currentSquare->name);
        printf("Price: LKR %d\n", currentSquare->property.purchasePrice);

        if(player->money >= currentSquare->property.purchasePrice + 5000){

            printf("%s decided to buy the property.\n", player->name);

            purchaseProperty(player,currentSquare);

        }else{

            printf("%s refused to buy the property.\n", player->name);
            printf("Property goes to auction.\n");

            Auction auction;

            startAuction(
                &auction,
                currentSquare
            );

            conductAuction(
                &auction,
                players,
                playerCount,
                currentSquare
            );

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