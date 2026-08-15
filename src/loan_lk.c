#include "../include/loan_lk.h"

int calculateEligibleCollateral(Player *player, Board board[]){

    int totalCollateral = 0;

    for(int i = 0; i < 40; i++){

        if(board[i].type == PROPERTY){

            if(board[i].property.ownerID == player->id){

                if(board[i].property.loanLocked == 0){

                    totalCollateral += board[i].property.mortgageValue;

                }

            }

        }else if(board[i].type == RAILWAY){

            if(board[i].railway.ownerID == player->id){

                if(board[i].railway.loanLocked == 0){

                    totalCollateral += board[i].railway.mortgageValue;

                }

            }

        }else if(board[i].type == UTILITY){

            if(board[i].utility.ownerID == player->id){

                if(board[i].utility.loanLocked == 0){

                    totalCollateral += board[i].utility.mortgageValue;

                }

            }

        }

    }

    return totalCollateral;

}

int hasLoanCollateral(Player *player, Board board[]){

    int collateral = calculateEligibleCollateral(player, board);

    if(collateral > 0){
        return 1;
    }

    return 0;

}

int calculateMaximumLoan(Player *player, Board board[]){

    int collateral = calculateEligibleCollateral(player, board);

    int maximumLoan = collateral * 75 / 100;

    return maximumLoan;
    
}
