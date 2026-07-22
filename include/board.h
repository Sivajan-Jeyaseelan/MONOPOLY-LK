#ifndef BOARD_H
#define BOARD_H


#include "types.h"


void createSquare(Board *square, int id, char name[], SquareType type);
void createProperty(Board *square, int id, char name[], int group, int price, int mortgage, int rent, int house, int hotel);
void initializeBoard(Board board[]);
void displayBoard(Board board[]);



#endif