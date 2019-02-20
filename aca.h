//
//  aca.h
//  DCT_Asynchronous_Automaton
//
//  Created by Osniel Lopes Teixeira on 15/11/18.
//  Copyright © 2018 Osniel Lopes Teixeira. All rights reserved.
//

#include <math.h>

#define DELTA_T 200
#define NUMBER_OF_NEIGHBOURS 1

int binToInt(int *binary) {
    int i = 0, sum = 0, j = 0;
    for(i = NUMBER_OF_NEIGHBOURS*2; i >= 0; i--){
        sum = sum + (pow(2,i) * binary[j]);
        j++;
    }
    return sum;
}

int didConverge(int config[CONFIG_SIZE], gene chromossome[], int *rule) {
    
    int i = 0;
    
    int amountOfZero = 0, amountOfOne = 0;
    for (i = 0; i < CONFIG_SIZE; i++)
        if (config[i] == 0) amountOfZero++;
        else amountOfOne++;
    int initialDensity = (amountOfZero > amountOfOne) ? 0 : 1;
    
    for (i = 0; i < DELTA_T; i++) {
        int aux[CONFIG_SIZE];
        int j;
        for (j = 0; j < CONFIG_SIZE; j++) aux[j] = config[j];
        for (j = 0; j < CONFIG_SIZE; j++) { //Iterates over the configuration
            int k, l = 0;
            int state[(2*NUMBER_OF_NEIGHBOURS)+1] = {0};
            for (k = j-NUMBER_OF_NEIGHBOURS; k <= j+NUMBER_OF_NEIGHBOURS ; k++) {
                if (k >= 0)
                    if (k < CONFIG_SIZE) state[l] = config[k];
                    else state[l] = config[k-CONFIG_SIZE];
                else state[l] = config[CONFIG_SIZE+k];
                l++;
            }
            aux[j] = rule[binToInt(state)];
            
            if (j < CONFIG_SIZE - 1)
                if (chromossome[j].priority != chromossome[j+1].priority) // Verifies if the level of priority will change
                    for (k = 0; k < CONFIG_SIZE; k++) config[k] = aux[k]; // If so, copies aux into config
            
        }
        
        for (j = 0; j < CONFIG_SIZE; j++) config[j] = aux[j]; //Copies aux to config
        
        //Verifies if the config did converge
        amountOfZero = 0;
        amountOfOne = 0;
        for (j = 0; j < CONFIG_SIZE; j++)
            if (config[j] == 0) amountOfZero++;
            else amountOfOne++;
        
        if (amountOfOne == CONFIG_SIZE) return initialDensity == 1;
        else if (amountOfZero == CONFIG_SIZE) return initialDensity == 0;
    }
    return 0;
}
