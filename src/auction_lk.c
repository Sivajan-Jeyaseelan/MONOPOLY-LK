#include <stdio.h>

#include "auction_lk.h"


#define AUCTION_START_PERCENT 50
#define AUCTION_MIN_INCREMENT 250
#define MAX_PLAYERS 4


int shouldPlayerBid(Player *player, Property *property, int minimumBid){

    if(player == NULL || property == NULL){
        return 0;
    }

    if(player->bankrupt == 1){
        return 0;
    }

    if(player->money < minimumBid){
        return 0;
    }

    switch(player->strategy){

        case AGGRESSIVE_INVESTOR:

            if(minimumBid <= (player->money * 80) / 100){
                return 1;
            }

            break;


        case CONSERVATIVE_BANKER:

            if(minimumBid <= (player->money * 40) / 100){
                return 1;
            }

            break;


        case RISK_TAKER:

            if(minimumBid <= (player->money * 90) / 100){
                return 1;
            }

            break;


        case OPPORTUNISTIC_TRADER:

            if(minimumBid <= property->currentValue){
                return 1;
            }

            break;


        default:
            break;

    }

    return 0;

}


void startAuction(Auction *auction, Board *property){

    if(auction == NULL || property == NULL){
        return;
    }

    auction->status = AUCTION_OPEN;

    auction->propertyID = property->id;

    if(property->property.currentValue <= 0){

        printf("ERROR: Invalid property market value: LKR %d\n",
            property->property.currentValue);

        auction->status = AUCTION_CLOSED;
        return;
    }

    auction->startingBid =
        (property->property.currentValue / 100) * 50;

    auction->minimumIncrement = 250;

    auction->highestBid = 0;
    auction->highestBidderID = -1;

    for(int i = 0; i < 4; i++){
        auction->withdrawn[i] = 0;
    }

    printf("\n========================================\n");
    printf("PROPERTY AUCTION\n");
    printf("========================================\n");

    printf("Property         : %s\n",
           property->property.name);

    printf("Market Value     : LKR %d\n",
           property->property.currentValue);

    printf("Starting Bid     : LKR %d\n",
           auction->startingBid);

    printf("Minimum Increment: LKR %d\n",
           auction->minimumIncrement);

    printf("========================================\n");
}


int conductAuction(Auction *auction, Player players[], int playerCount, Board *property){

    if(auction == NULL || players == NULL || property == NULL){
        return -1;
    }


    if(playerCount <= 0){
        return -1;
    }


    if(auction->status != AUCTION_OPEN){
        return -1;
    }


    if(playerCount > MAX_PLAYERS){
        playerCount = MAX_PLAYERS;
    }


    int activeBidders = 0;

    for(int i = 0; i < playerCount; i++){

        if(players[i].bankrupt == 1){

            auction->withdrawn[i] = 1;

        }else{

            auction->withdrawn[i] = 0;
            activeBidders++;

        }

    }


    if(activeBidders == 0){

        printf("\n");
        printf("No solvent players are available.\n");
        printf("Property remains with the Bank.\n");

        auction->status = AUCTION_CLOSED;

        return -1;

    }


    int highestBid = 0;
    int highestBidder = -1;


    while(activeBidders > 1){

        int bidWasMade = 0;


        for(int i = 0; i < playerCount; i++){

            if(auction->withdrawn[i] == 1){
                continue;
            }


            if(players[i].bankrupt == 1){

                auction->withdrawn[i] = 1;
                activeBidders--;

                continue;

            }

            int minimumBid;

            if(highestBidder == -1){

                minimumBid = auction->startingBid;

            }else{

                minimumBid = highestBid + auction->minimumIncrement;

            }


            if(players[i].money < minimumBid){

                printf("%s cannot afford LKR %d.\n", players[i].name, minimumBid);

                auction->withdrawn[i] = 1;
                activeBidders--;

                printf("%s withdraws permanently from the auction.\n", players[i].name);

                if(activeBidders <= 1){
                    break;
                }

                continue;

            }


            int wantsToBid = shouldPlayerBid(&players[i], &property->property, minimumBid);

            if(wantsToBid){

                int newBid = minimumBid;

                if(newBid > players[i].money){
                    continue;
                }


                highestBid = newBid;
                highestBidder = i;

                auction->highestBid = highestBid;

                auction->highestBidderID = players[i].id;

                bidWasMade = 1;


                printf("%s bids LKR %d\n", players[i].name, highestBid);

            }else{

                auction->withdrawn[i] = 1;

                activeBidders--;

                printf("%s declines to bid and withdraws permanently.\n", players[i].name);

            }


            if(activeBidders <= 1){
                break;
            }

        }

        if(highestBidder == -1){

            printf("\n");
            printf("No player submitted a bid.\n");
            printf("Property remains with the Bank.\n");

            auction->status = AUCTION_CLOSED;

            return -1;

        }

        if(!bidWasMade && activeBidders > 1){
            break;
        }

    }


    if(highestBidder == -1){

        for(int i = 0; i < playerCount; i++){

            if(players[i].bankrupt == 0 &&
               auction->withdrawn[i] == 0){

                highestBidder = i;
                break;
            }

        }

    }

    if(highestBidder == -1 ||
       highestBid <= 0){

        printf("\n");
        printf("========================================\n");
        printf("AUCTION RESULT\n");
        printf("========================================\n");

        printf("No successful bidder.\n");
        printf("Property remains with the Bank.\n");

        printf("========================================\n");

        auction->status = AUCTION_CLOSED;

        return -1;
    }

    if(players[highestBidder].money < highestBid){

        printf("\n");
        printf(
            "%s cannot pay the winning bid.\n",
            players[highestBidder].name
        );

        printf("Property remains with the Bank.\n");

        auction->status = AUCTION_CLOSED;

        return -1;
    }

    players[highestBidder].money -= highestBid;


    property->property.ownerID = players[highestBidder].id;


    players[highestBidder].propertyCount++;


    auction->highestBid = highestBid;

    auction->highestBidderID = players[highestBidder].id;

    auction->status = AUCTION_CLOSED;

    printf("\n");
    printf("========================================\n");
    printf("AUCTION COMPLETED\n");
    printf("========================================\n");

    printf("Property       : %s\n", property->property.name);

    printf("Winner         : %s\n", players[highestBidder].name);

    printf("Winning Bid    : LKR %d\n", highestBid);

    printf("Remaining Cash : LKR %d\n", players[highestBidder].money);

    printf("New Owner ID   : %d\n", players[highestBidder].id);

    printf("========================================\n");

    return highestBidder;

}