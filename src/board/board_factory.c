#include <stdio.h>
#include <string.h>

#include "../../include/board.h"


void createSquare(Board *square, int id, char name[], SquareType type){

    square->id = id;
    strcpy(square->name,name);
    square->type = type;

}


void createProperty(Board *square, int id, char name[], int group, int price, int mortgage, int rent, int house, int hotel){

    square->id = id;
    strcpy(square->name,name);
    square->type = PROPERTY;
    square->property.groupID = group;
    square->property.purchasePrice = price;
    square->property.mortgageValue = mortgage;
    square->property.baseRent = rent;
    square->property.houseCost = house;
    square->property.hotelCost = hotel;
    square->property.ownerID = -1;
    square->property.mortgageStatus = 0;
    square->property.insuranceStatus = 0;
    square->property.insurance.lostIncomeRounds = 0;
    square->property.insurance.type = NO_INSURANCE;
    square->property.insurance.premium = 0;
    square->property.insurance.remainingRounds = 0;
    square->property.insurance.lostIncomeRounds = 0;
    square->property.insurance.disasterActive = 0;
    square->property.buildings = NO_BUILDING;

}

void createRailway(Board *square, int id, char name[], int purchasePrice, int mortgageValue){

    square->id = id;

    strcpy(square->name,name);

    square->type = RAILWAY;


    strcpy(square->railway.name,name);


    square->railway.purchasePrice = purchasePrice;

    square->railway.mortgageValue = mortgageValue;

    square->railway.ownerID = -1; //doubt

    square->railway.mortgageStatus = 0;

}

void createUtility(Board *square, int id, char name[], int purchasePrice, int mortgageValue){

    square->id = id;

    strcpy(square->name,name);

    square->type = UTILITY;


    strcpy(square->utility.name,name);


    square->utility.purchasePrice = purchasePrice;

    square->utility.mortgageValue = mortgageValue;

    square->utility.ownerID = -1;

    square->utility.mortgageStatus = 0;

}