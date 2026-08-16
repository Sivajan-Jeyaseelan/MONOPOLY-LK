#include <stdio.h>

#include "../include/game.h"
#include "../include/dice.h"
#include "../include/property.h"
#include "../include/building.h"
#include "../include/dept.h"
#include "../include/bank_lk.h"
#include "../include/bankruptcy_lk.h"
#include "../include/loan_interest_lk.h"
#include "../include/loan_default_lk.h"
#include "../include/insurance_lk.h"
#include "../include/insurance_expiry_lk.h"
#include "../include/disaster_lk.h"
#include "../include/disaster_repair_lk.h"
#include "../include/inflation_lk.h"




Player *allPlayers;
int totalPlayers;


void setPlayers(Player players[], int playerCount){

    allPlayers = players;
    totalPlayers = playerCount;

}

int countActivePlayers(Player players[], int totalPlayers){

    int count = 0;

    for(int i=0;i<totalPlayers;i++){

        if(players[i].bankrupt == 0){
            count++;
        }

    }

    return count;

}

int checkGameOver(Player players[], int totalPlayers){

    return countActivePlayers(players,totalPlayers) == 1;

}

Player* findWinner(Player players[], int totalPlayers, Board board[]){

    int highest = -1;
    Player *winner = NULL;

    for(int i=0;i<totalPlayers;i++){

        if(players[i].bankrupt == 0){

            int worth = calculateAssets(&players[i],board);

            if(worth > highest){
                highest = worth;
                winner = &players[i];
            }

        }

    }

    return winner;

}

void determineFirstPlayer(Player players[], int turnOrder[]){

    int highest = -1;
    int firstPlayer = -1;

    for(int i = 0; i < 4; i++){

        int roll = rollDice();

        printf("%s rolled %d\n", players[i].name, roll);

        if(roll > highest){

            highest = roll;
            firstPlayer = i;

        }

    }


    printf("\n%s will begin the game.\n", players[firstPlayer].name);


    for(int i = 0; i < 4; i++){

        turnOrder[i] = (firstPlayer + i) % 4;

    }


    printf("\nTurn Order:\n");


    for(int i = 0; i < 4; i++){

        printf("%s\n", players[turnOrder[i]].name);

    }

}

void playTurn(Player *player, Board board[]){

    printf("\n%s's turn\n", player->name);

    printf("Checking penalties...\n");

    int dice = rollDice();

    printf("%s rolled %d\n", player->name, dice);


    player->position += dice;

    if(player->position >= 40){

        player->position -= 40;

        player->money += 2000;

        printf("%s passed GO and received LKR 2000\n", player->name);

    }

    printf("Current position: %d\n", player->position);

    printf("Resolving landing action...\n");

    if(board[player->position].type == BANK){

        resolveBank(player, board);

    }else if(board[player->position].type == INSURANCE){

        printf("%s landed on %s.\n", player->name, board[player->position].name);

        printf("Insurance is available at this location.\n");

       
        if(lkCanPurchaseInsurance(player, board)){

            printf("%s can purchase insurance here.\n", player->name);

        }

    }else{

        resolveProperty(player, allPlayers, totalPlayers, board);

    }
    

    printf("Checking building construction...\n");
    checkBuilding(player, board);

    printf("Completing financial transactions...\n");

    printf("Turn ended\n");

}

void startGame(Player players[], int playerCount, Board board[]){

    int round = 1;
    int turnOrder[4];

    EconomicState economy = {
        .inflationRate = 0,
        .previousInflationRate = 0,
        .tourismBoom = 0,
        .fuelCrisis = 0,
        .heavyMonsoon = 0,
        .economicRecession = 0,
        .stockMarketBoom = 0,
        .governmentHousingProgramme = 0,
        .foreignInvestment = 0,
        .politicalUnrest = 0
    };

    determineFirstPlayer(players, turnOrder);

    while(round <= 500){

        printf("\n============================\n");
        printf("ROUND %d\n", round);
        printf("============================\n");

        for(int i = 0; i < playerCount; i++){

            int playerIndex = turnOrder[i];

            if(players[playerIndex].bankrupt == 1){
                continue;
            }

            playTurn(&players[playerIndex], board);

            if(checkGameOver(players, playerCount)){

                Player *winner = findWinner(players, playerCount, board);

                printf("\n============================\n");
                printf("GAME OVER\n");
                printf("============================\n");

                printf("Only one solvent player remains.\n");

                if(winner != NULL){

                    printf("Winner: %s\n", winner->name);
                    printf("Net Worth: LKR %d\n", calculateAssets(winner, board));

                }

                return;

            }

        }

        printf("\n------------------------------------\n");
        printf("End of Round %d - Insurance Processing\n", round);
        printf("------------------------------------\n");

        for(int i = 0; i < playerCount; i++){

            if(players[i].bankrupt == 1){
                continue;
            }

            lkUpdateInsuranceRounds(&players[i], board);
            lkCheckInsuranceExpiry(&players[i], board);

        }


        printf("\n------------------------------------\n");
        printf("End of Round %d - Loan Processing\n", round);
        printf("------------------------------------\n");

        for(int i = 0; i < playerCount; i++){

            if(players[i].bankrupt == 1){
                continue;
            }

            if(players[i].loan.active == 1){

                advanceLoanRound(&players[i]);

                if(isLoanDefaulted(&players[i])){

                    processLoanDefault(&players[i], board);

                    checkLoanBankruptcy(&players[i], board);

                }

            }

        }


        if(lkShouldTriggerDisaster(round)){

            printf("\n------------------------------------\n");
            printf("Disaster Processing\n");
            printf("------------------------------------\n");

            DisasterType disaster = lkGenerateDisaster();

            lkApplyDisaster(disaster, board, players);

            for(int i = 0; i < playerCount; i++){

                if(players[i].bankrupt == 1){
                    continue;
                }

                lkRepairDamagedProperties(&players[i], board);

            }

        }

        if(round % 10 == 0){

            applyInflation(&economy, board);

        }

        round++;
        
    }


    printf("\n============================\n");
    printf("GAME OVER\n");
    printf("============================\n");

    printf("Maximum 500 rounds reached.\n");

    Player *winner = findWinner(players, playerCount, board);

    if(winner != NULL){

        printf("Winner: %s\n", winner->name);
        printf("Net Worth: LKR %d\n", calculateAssets(winner, board));

    }

}