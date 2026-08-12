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


// Loan transaction actions
typedef enum{

    LOAN_REPAY_PARTIAL,
    LOAN_REPAY_FULL,
    LOAN_EXTEND,
    LOAN_INCREASE

}LoanAction;


// Disaster types
typedef enum{

    NO_DISASTER,
    FIRE,
    FLOOD,
    RIOT,
    BUILDING_COLLAPSE,
    ELECTRICAL_FAILURE

}DisasterType;


// Economic event types
typedef enum{

    NO_ECONOMIC_EVENT,
    TOURISM_BOOM,
    FUEL_CRISIS,
    HEAVY_MONSOON,
    ECONOMIC_RECESSION,
    STOCK_MARKET_BOOM,
    GOVERNMENT_HOUSING_PROGRAMME,
    FOREIGN_INVESTMENT,
    POLITICAL_UNREST

}EconomicEventType;


// Auction status
typedef enum{

    AUCTION_CLOSED,
    AUCTION_OPEN

}AuctionStatus;


// Insurance Structure
typedef struct{

    InsuranceType type;
    int premium;
    int remainingRounds;
    int lostIncomeRounds;
    int disasterActive;

    /* MONOPOLY-LK */
    int active;
    int propertyValue;
    int coveragePercent;
    int renewalReminderShown;

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
    int houseCount;

    int insuranceStatus;
    Insurance insurance;

    int loanLocked;
    int damaged;
    int propertyAge;
    int depreciation;
    int currentValue;
    int currentRent;
    int repairCost;
    int renovationRequired;

    

}Property;




// Railway Structure
typedef struct{

    char name[50];
    int purchasePrice;
    int mortgageValue;
    int ownerID;
    int mortgageStatus;
    int loanLocked;

}Railway;


// Utility Structure
typedef struct{

    char name[50];
    int purchasePrice;
    int mortgageValue;
    int ownerID;
    int mortgageStatus;
    int loanLocked;

}Utility;



// Board Structure
typedef struct{

    int id;
    char name[50];
    SquareType type;

    int taxAmount;
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

    /* MONOPOLY-LK */
    int originalAmount;
    int remainingRounds;
    int accumulatedInterest;

}Loan;



// Player Structure
typedef struct{

    int id;
    char name[50];
    int money;
    int position;
    int bankrupt;
    int propertyCount;

    int taxesDue;
    int insuranceClaims;

    int inJail;    
    int jailTurns;

    Loan loan;

    int loanLockedAssetCount;

}Player;   



typedef struct{

    int inflationRate;
    int previousInflationRate;

    int tourismBoom;
    int fuelCrisis;
    int heavyMonsoon;
    int economicRecession;
    int stockMarketBoom;
    int governmentHousingProgramme;
    int foreignInvestment;
    int politicalUnrest;

}EconomicState;


#endif