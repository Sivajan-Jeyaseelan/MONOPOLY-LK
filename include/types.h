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



// Autonomous Player Strategies
typedef enum{

    AGGRESSIVE_INVESTOR,
    CONSERVATIVE_BANKER,
    RISK_TAKER,
    OPPORTUNISTIC_TRADER

}PlayerStrategy;


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

    PlayerStrategy strategy;

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




// Rules 19-23 : Auction
typedef struct{

    AuctionStatus status;

    int propertyID;
    int startingBid;
    int minimumIncrement;
    int highestBid;
    int highestBidderID;

    int withdrawn[4];

}Auction;



// Rules 25-29 : Building Condition and Maintenance
typedef struct{

    int condition;              
    int age;                   
    int maintenanceSkipped;   
    int damaged;               
    int renovationRequired;     

}Building;



// Rules 30-34 : Dynamic Property Market
typedef enum{

    MARKET_NONE,
    MARKET_BOOM,
    MARKET_DECLINE

}MarketEffectType;


typedef struct{

    int groupID;
    MarketEffectType effect;

    int remainingRounds;
    int startRound;
    int lastSelectedRound;

}MarketGroup;


typedef struct{

    int currentRound;

    int boomGroupID;
    int declineGroupID;

    int boomRemainingRounds;
    int declineRemainingRounds;

    int lastBoomGroupID;
    int lastDeclineGroupID;

    int boomStartRound;
    int declineStartRound;

}PropertyMarketState;



// Rules 35-36 : Regional Development Cards
typedef enum{

    REGIONAL_NONE,
    SOUTHERN_TOURISM_BOOM,
    PORT_CITY_EXPANSION,
    IT_INDUSTRY_GROWTH,
    NORTHERN_DEVELOPMENT,
    TEA_EXPORT_BOOM,
    AIRPORT_EXPANSION,
    UNIVERSITY_CITY_GROWTH,
    BEACH_POLLUTION,
    FLOOD_DAMAGE,
    TRANSPORT_STRIKE,
    ELECTRICITY_TARIFF_INCREASE,
    WATER_SHORTAGE

}RegionalDevelopmentType;


typedef struct{

    RegionalDevelopmentType type;

    int active;
    int remainingRounds;
    int startRound;

}RegionalDevelopmentState;



// Rule 24 : Government Regulation
typedef enum{

    NO_REGULATION,
    INCREASE_PROPERTY_TAX,
    GOVERNMENT_HOUSING_REGULATION,
    FOREIGN_INVESTMENT_REGULATION,
    POLITICAL_UNREST_REGULATION,
    REDUCE_LOAN_INTEREST,
    HOUSING_SUBSIDY,
    LUXURY_PROPERTY_TAX,
    RAILWAY_MODERNIZATION,
    ELECTRICITY_TARIFF_REVISION,
    INSURANCE_REGULATION,
    ANTI_SPECULATION_ACT

}RegulationType;


typedef struct{

    RegulationType type;

    int active;
    int remainingRounds;
    int startRound;

}GovernmentRegulationState;



// Rule 18 : National Economic Event State
typedef struct{

    EconomicEventType type;

    int active;
    int remainingRounds;
    int startRound;

}NationalEconomicEventState;



// Rules 18-36 : Extended Economic State
typedef struct{

    NationalEconomicEventState nationalEvent;
    GovernmentRegulationState regulation;

    PropertyMarketState propertyMarket;

    RegionalDevelopmentState regionalDevelopment;

}MonopolyLKState;


#endif