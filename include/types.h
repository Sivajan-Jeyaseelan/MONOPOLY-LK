#ifndef TYPES_H
#define TYPES_H


#define NO_BUILDING 0
#define HOUSE 1
#define HOTEL 2


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


// Insurance Types
typedef enum{

    NO_INSURANCE,
    BASIC_INSURANCE,
    COMPREHENSIVE_INSURANCE,
    BUSINESS_INTERRUPTION_INSURANCE

}InsuranceType; 



// Insurance Structure
typedef struct{

    InsuranceType type;

    int premium;

    int remainingRounds;

    int lostIncomeRounds;

}Insurance;


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
    int buildings;

    int insuranceStatus;
    Insurance insurance;

    

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