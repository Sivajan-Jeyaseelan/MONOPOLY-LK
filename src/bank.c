#include <stdio.h>

#include "../include/bank.h"

int calculateMaxLoan(Player player, Board board[]){

    int totalMortgageValue = 0;

    for(int i = 0; i < 40; i++){

        if(board[i].type == PROPERTY){

            if(board[i].property.ownerID == player.id && board[i].property.mortgageStatus == 0){

                totalMortgageValue += board[i].property.mortgageValue;

            }

        }

    }

    return totalMortgageValue * 0.75;

}

void obtainLoan(Player *player, Board board[]){

    int maxLoan = calculateMaxLoan(*player, board);

    if(player->loan.active == 1){

        printf("Player already has an active loan\n");
        return;

    }

    if(maxLoan <= 0){

        printf("No available collateral\n");
        return;

    }

    player->loan.active = 1;

    player->loan.loanAmount = maxLoan;

    player->loan.collateralValue = maxLoan / 0.75;

    player->loan.interest = 0;

    player->loan.maturity = 10;

    player->money += maxLoan;

    printf("Loan obtained: LKR %d\n", maxLoan);

}

void repayLoan(Player *player, int amount){

    if(player->loan.active == 0){

        printf("No active loan\n");
        return;

    }

    if(amount > player->money){

        printf("Insufficient money\n");
        return;

    }

    player->money -= amount;

    player->loan.loanAmount -= amount;


    if(player->loan.loanAmount <= 0){

        player->loan.active = 0;

        player->loan.loanAmount = 0;

        printf("Loan fully repaid\n");

    }

}

void applyLoanInterest(Player players[], int playerCount){

    for(int i = 0; i < playerCount; i++){

        if(players[i].loan.active == 1){

            int interest = players[i].loan.loanAmount * 10 / 100;

            players[i].loan.interest += interest;

            players[i].loan.loanAmount += interest;

        }

    }

}

void foreclosure(Player *player, Board board[]){

    printf("Foreclosure started for player %s\n", player->name);

    for(int i = 0; i < 40; i++){

        if(board[i].type == PROPERTY){

            if(board[i].property.ownerID == player->id){

                board[i].property.ownerID = -1;

                board[i].property.buildings = 0;

                board[i].property.insuranceStatus = 0;

            }

        }

    }

    player->loan.active = 0;

    player->loan.loanAmount = 0;

    printf("Debt cancelled\n");

}

void bankTransaction(Player *player, Board board[]){

    int choice;

    printf("\nBank of Ceylon\n");
    printf("1. Obtain Loan\n");
    printf("2. Repay Loan\n");
    printf("3. Refinance Loan\n");
    printf("4. Increase Loan Amount\n");
    printf("5. Repay Loan Fully\n");

    printf("Select transaction: ");
    scanf("%d",&choice);


    switch(choice){

        case 1:
            obtainLoan(player, board);
            break;

        case 2:
            printf("Enter repayment amount: ");
            int amount;
            scanf("%d",&amount);

            repayLoan(player, amount);
            break;

        case 3:
            refinanceLoan(player, board);
            break;

        case 4:
            increaseLoan(player, board);
            break;

        case 5:
            repayFullLoan(player);
            break;

        default:
            printf("Invalid option\n");

    }

}

void refinanceLoan(Player *player, Board board[]){

    if(player->loan.active == 0){

        printf("No active loan\n");
        return;

    }

    int newLoan = calculateMaxLoan(*player, board);

    if(newLoan <= player->loan.loanAmount){

        printf("Cannot refinance\n");
        return;

    }

    int difference = newLoan - player->loan.loanAmount;

    player->loan.loanAmount = newLoan;

    player->money += difference;

    printf("Loan refinanced. Additional money: LKR %d\n",difference);

}

void increaseLoan(Player *player, Board board[]){

    if(player->loan.active == 0){

        printf("No active loan\n");
        return;

    }

    int maxLoan = calculateMaxLoan(*player, board);

    if(maxLoan <= player->loan.loanAmount){

        printf("Maximum loan already reached\n");
        return;

    }

    int increase = maxLoan - player->loan.loanAmount;

    player->loan.loanAmount = maxLoan;

    player->money += increase;

    printf("Loan increased by LKR %d\n",increase);

}

void repayFullLoan(Player *player){

    if(player->loan.active == 0){

        printf("No active loan\n");
        return;

    }

    if(player->money < player->loan.loanAmount){

        printf("Not enough money\n");
        return;

    }

    player->money -= player->loan.loanAmount;

    player->loan.loanAmount = 0;

    player->loan.active = 0;

    printf("Loan completely repaid\n");

}

void checkLoanMaturity(Player players[], int playerCount, Board board[]){

    for(int i=0;i<playerCount;i++){

        if(players[i].loan.active == 1){

            players[i].loan.maturity--;


            if(players[i].loan.maturity <= 0){

                foreclosure(&players[i], board);

            }

        }

    }

}