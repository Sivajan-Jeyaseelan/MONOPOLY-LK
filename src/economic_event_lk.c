#include <stdio.h>
#include <stdlib.h>

#include "economic_event_lk.h"

#include "tourism_boom_lk.h"
#include "fuel_crisis_lk.h"
#include "heavy_monsoon_lk.h"
#include "economic_recession_lk.h"
#include "stock_market_boom_lk.h"


void triggerEconomicEvent(MonopolyLKState *state, Board board[], Player players[], int playerCount, int currentRound){

    int event;

    if (state == NULL){
        return;
    }

    if (state->nationalEvent.active){

        if (state->nationalEvent.remainingRounds > 0){

            state->nationalEvent.remainingRounds--;

        }

        if (state->nationalEvent.remainingRounds == 0){

            switch (state->nationalEvent.type){

                case TOURISM_BOOM:
                    removeTourismBoom(board, playerCount);
                    break;

                case FUEL_CRISIS:
                    removeFuelCrisis(board, playerCount);
                    break;

                case HEAVY_MONSOON:
                    removeHeavyMonsoon(board, playerCount);
                    break;

                case ECONOMIC_RECESSION:
                    removeEconomicRecession(
                        board,
                        players,
                        playerCount
                    );
                    break;

                case STOCK_MARKET_BOOM:
                    removeStockMarketBoom(board, playerCount);
                    break;

                default:
                    break;

            }

            state->nationalEvent.type = NO_ECONOMIC_EVENT;
            state->nationalEvent.active = 0;
            state->nationalEvent.startRound = 0;

        }

    }

    if (currentRound <= 0 || currentRound % 15 != 0){
        return;
    }


    if (state->nationalEvent.active){

        switch (state->nationalEvent.type){

            case TOURISM_BOOM:
                removeTourismBoom(board, playerCount);
                break;

            case FUEL_CRISIS:
                removeFuelCrisis(board, playerCount);
                break;

            case HEAVY_MONSOON:
                removeHeavyMonsoon(board, playerCount);
                break;

            case ECONOMIC_RECESSION:
                removeEconomicRecession(
                    board,
                    players,
                    playerCount
                );
                break;

            case STOCK_MARKET_BOOM:
                removeStockMarketBoom(board, playerCount);
                break;

            default:
                break;

        }

    }

    event = (rand() % 5) + 1;

    state->nationalEvent.type = (EconomicEventType)event;
    state->nationalEvent.active = 1;
    state->nationalEvent.remainingRounds = 15;
    state->nationalEvent.startRound = currentRound;

    switch (state->nationalEvent.type){

        case TOURISM_BOOM:

            applyTourismBoom(board, playerCount);

            printf("\n==============================\n");
            printf("Economic Event\n");
            printf("==============================\n");
            printf("Tourism Boom\n");
            printf("Hotels receive double rent.\n");
            printf("Southern Province properties increase in value by 15%%.\n");

            break;


        case FUEL_CRISIS:

            applyFuelCrisis(board, playerCount);

            printf("\n==============================\n");
            printf("Economic Event\n");
            printf("==============================\n");
            printf("Fuel Crisis\n");
            printf("Railway rent doubles.\n");
            printf("Property development costs increase by 20%%.\n");

            break;


        case HEAVY_MONSOON:

            applyHeavyMonsoon(board, playerCount);

            printf("\n==============================\n");
            printf("Economic Event\n");
            printf("==============================\n");
            printf("Heavy Monsoon\n");
            printf("Flood risk increases.\n");
            printf("Insurance premiums increase.\n");
            printf("Coastal properties lose 10%% of their value.\n");

            break;


        case ECONOMIC_RECESSION:

            applyEconomicRecession(board, players, playerCount);

            printf("\n==============================\n");
            printf("Economic Event\n");
            printf("==============================\n");
            printf("Economic Recession\n");
            printf("Property values decrease by 15%%.\n");
            printf("Rent decreases by 10%%.\n");
            printf("Loan interest increases by 15%%.\n");

            break;


        case STOCK_MARKET_BOOM:

            applyStockMarketBoom(board, playerCount);

            printf("\n==============================\n");
            printf("Economic Event\n");
            printf("==============================\n");
            printf("Stock Market Boom\n");

            break;


        default:

            state->nationalEvent.type = NO_ECONOMIC_EVENT;
            state->nationalEvent.active = 0;
            state->nationalEvent.remainingRounds = 0;
            state->nationalEvent.startRound = 0;

            break;

    }

}

void displayEconomicEvent(MonopolyLKState *state){

    if (state == NULL){
        return;
    }

    if (!state->nationalEvent.active){
        return;
    }

    printf("\n==============================\n");
    printf("Current Economic Event\n");
    printf("==============================\n");

    switch (state->nationalEvent.type){

        case TOURISM_BOOM:
            printf("Tourism Boom\n");
            break;

        case FUEL_CRISIS:
            printf("Fuel Crisis\n");
            break;

        case HEAVY_MONSOON:
            printf("Heavy Monsoon\n");
            break;

        case ECONOMIC_RECESSION:
            printf("Economic Recession\n");
            break;

        case STOCK_MARKET_BOOM:
            printf("Stock Market Boom\n");
            break;

        default:
            printf("No Economic Event\n");
            break;

    }

    printf("Rounds Remaining : %d\n", state->nationalEvent.remainingRounds);

}