#include <stdio.h>
#include <stdlib.h>

#include "../include/inflation_lk.h"
#include "../include/inflation_values_lk.h"


int generateInflationRate(void){

    int values[] = {-3, 0, 2, 5, 8, 12};

    int index = rand() % 6;

    return values[index];

}

void applyInflation(EconomicState *economy, Board board[]){

    if(economy == NULL || board == NULL){
        return;
    }

    int newRate = generateInflationRate();

    economy->previousInflationRate = economy->inflationRate;

    economy->inflationRate = newRate;

    updatePropertyValuesForInflation(board, newRate);

    printf("\n");
    printf("=====================================\n");
    printf("Inflation\n");
    printf("=====================================\n");

    printf("Previous Inflation Rate : %d%%\n", economy->previousInflationRate);

    printf("New Inflation Rate : %d%%\n", economy->inflationRate);


    if(newRate < 0){

        printf("Deflation has occurred.\n");

    }
    else if(newRate == 0){

        printf("No inflation or deflation this period.\n");

    }else{

        printf("Inflation has increased financial values.\n");

    }

    printf("=====================================\n");

}