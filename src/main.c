#include <stdio.h>

#include "../include/board.h"


int main(){

    Board board[40];

    initializeBoard(board);
    displayBoard(board);

    return 0;

}