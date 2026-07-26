#include<stdio.h>
#include <string.h>


#include "../include/board.h"


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
    square->property.buildings = 0;

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


void initializeBoard(Board board[]){

    createSquare(&board[0], 0, "GO", START);

    // this square is a property
    createProperty(&board[1],1,"Pettah",1,1500,750,100,500,2000);

    createSquare(&board[2], 2, "Community Development Fund", EVENT);

    // this square is a property
    createProperty(&board[3],3,"Maradana",1,1500,750,100,500,2000);

    createSquare(&board[4], 4, "Income Tax", TAX);

    createRailway(&board[5],5,"Colombo Fort Railway Station",2000,1000);

    // this square is a property
    createProperty(&board[6],6,"Bambalapitiya",2,1800,900,120,600,2200);

    createSquare(&board[7],7,"National Event Card",EVENT);

    // this square is a property
    createProperty(&board[8],8,"Wellawatte",2,1800,900,120,600,2200);

    // this square is a property
    createProperty(&board[9],9,"Mount Lavinia",2,2000,1000,150,700,2500);

    createSquare(&board[10],10,"Jail / Just Visiting",SPECIAL);

    // this square is a property
    createProperty(&board[11],11,"Nugegoda",3,2200,1100,160,800,2800);

    createUtility(&board[12], 12, "Ceylon Electricity Board", 3000, 1500);

    // this square is a property
    createProperty(&board[13],13,"Maharagama",3,2200,1100,160,800,2800);

    // this square is a property
    createProperty(&board[14],14,"Kottawa",3,2500,1250,180,900,3000);

    createRailway(&board[15], 15, "Kandy Railway Station", 2000, 1000);

    // this square is a property
    createProperty(&board[16],16,"Negombo",4,2600,1300,200,1000,3200);

    createSquare(&board[17],17,"Sri Lanka Insurance",INSURANCE);

    // this square is a property
    createProperty(&board[18],18,"Katunayake",4,2600,1300,200,1000,3200);

    // this square is a property
    createProperty(&board[19],19,"Ja-Ela",4,2800,1400,220,1100,3500);

    createSquare(&board[20],20,"Free Parking",SPECIAL);

    // this square is a property
    createProperty(&board[21],21,"Kandy City",5,3000,1500,250,1200,4000);

    createSquare(&board[22],22,"National Event Card",EVENT);

    // this square is a property
    createProperty(&board[23],23,"Peradeniya",5,3000,1500,250,1200,4000);

    // this square is a property
    createProperty(&board[24],24,"Katugastota",5,3200,1600,280,1300,4200);

    createRailway(&board[25], 25, "Galle Railway Station", 2000, 1000);

    // this square is a property
    createProperty(&board[26],26,"Galle Fort",6,3500,1750,300,1500,4500);

    // this square is a property
    createProperty(&board[27],27,"Unawatuna",6,3500,1750,300,1500,4500);

    createUtility(&board[28], 28, "National Water Supply and Drainage Board", 3000, 1500);

    // this square is a property
    createProperty(&board[29],29,"Hikkaduwa",6,3800,1900,350,1700,5000);

    createSquare(&board[30],30,"Go To Jail",SPECIAL);

    // this square is a property
    createProperty(&board[31],31,"Jaffna Town",7,4000,2000,400,2000,5500);

    // this square is a property
    createProperty(&board[32],32,"Nallur",7,4000,2000,400,2000,5500);

    createSquare(&board[33],33,"Ceylinco Insurance",INSURANCE);

    // this square is a property
    createProperty(&board[34],34,"Trincomalee",7,4300,2150,450,2200,6000);

    createRailway(&board[35], 35, "Jaffna Railway Station", 2000, 1000);

    createSquare(&board[36],36,"National Event Card",EVENT);

    // this square is a property
    createProperty(&board[37],37,"Nuwara Eliya",8,5000,2500,500,2500,7000);

    createSquare(&board[38],38,"Bank of Ceylon",BANK);

    // this square is a property
    createProperty(&board[39],39,"Galle Face",8,5500,2750,600,3000,8000);

}


void displayBoard(Board board[]){

    for(int i = 0; i < 40; i++)    {

        printf("Square %d : %s\n", board[i].id, board[i].name);

        if(board[i].type == PROPERTY){

            printf("Type : Property\n");
            printf("Purchase Price : LKR %d\n", board[i].property.purchasePrice);
            printf("Mortgage Value : LKR %d\n", board[i].property.mortgageValue);
            printf("Owner ID : %d\n\n", board[i].property.ownerID);

        }else if(board[i].type == RAILWAY){

            printf("Type : Railway Station\n");
            printf("Purchase Price : LKR %d\n", board[i].railway.purchasePrice);
            printf("Mortgage Value : LKR %d\n", board[i].railway.mortgageValue);
            printf("Owner ID : %d\n", board[i].railway.ownerID);
            printf("Mortgage Status : %d\n\n", board[i].railway.mortgageStatus);

        }else if(board[i].type == UTILITY){

            printf("Type : Utility\n");            
            printf("Purchase Price : LKR %d\n", board[i].utility.purchasePrice);
            printf("Mortgage Value : LKR %d\n", board[i].utility.mortgageValue);
            printf("Owner ID : %d\n", board[i].utility.ownerID);
            printf("Mortgage Status : %d\n\n", board[i].utility.mortgageStatus);

        }else if(board[i].type == START){

            printf("Type : Start\n\n");

        }

        else if(board[i].type == EVENT){

            printf("Type : Event\n\n");

        }else if(board[i].type == TAX){

            printf("Type : Tax\n\n");

        }else if(board[i].type == INSURANCE){

            printf("Type : Insurance\n\n");

        }else if(board[i].type == BANK){

            printf("Type : Bank\n\n");

        }else if(board[i].type == SPECIAL){
        
            printf("Type : Special\n\n");

        }

    }

}