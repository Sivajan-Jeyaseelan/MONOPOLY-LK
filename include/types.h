#ifndef TYPES_H
#define TYPES_H


//Board Square categories
typedef enum{

    START,
    PROPERTY,
    EVENT,
    TAX,
    RAILWAY,
    UTILITY,
    SPECIAL,
    INSURANCE,
    BANK

}SquareType;




// Property Structure
typedef struct{

    char name[50];
    int groupID;
    int purchasePrice;
    int mortgageValue;
    int baseRent;
    int houseCost;
    int hotelCost;
    int ownerID;
    int mortgageStatus;
    int insuranceStatus;
    int buildings;

}Property;




// Railway Structure
typedef struct{

    char name[50];
    int purchasePrice;
    int mortgageValue;
    int ownerID;
    int mortgageStatus;

}Railway;


// Utility Structure
typedef struct{

    char name[50];
    int purchasePrice;
    int mortgageValue;
    int ownerID;
    int mortgageStatus;

}Utility;



// Board Structure
typedef struct{

    int id;
    char name[50];
    SquareType type;

    Property property;
    Railway railway;
    Utility utility;

}Board;



// Loan Structure
typedef struct{

    int active;
    int loanAmount;
    int interest;
    int collateralValue;
    int maturity;

}Loan;


// Player Structure
typedef struct{

    int id;
    char name[50];
    int money;
    int position;
    int bankrupt;
    int propertyCount;

    Loan loan;

}Player;   






#endif