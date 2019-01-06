#include <stdio.h> //defines input and output
#include <string.h> //basic functions of the system
#include <stdlib.h> //functions envolving memory alocation
#include <time.h>
#include "quickSort.h"
#include "aca.h"

// Function to print a chromossome
void print(gene arr[], int size) {
    printf("positions  [");
    for (int i = 0; i < size; i++) printf("%d ", arr[i].position);
    printf("]\n");
    printf("priorities [");
    for (i = 0; i < size; i++) printf("%d ", arr[i].priority);
    printf("]\n");
}

void selection(species population[]){
    
    srand(time(NULL));
    
    float totalFitness = 0.0;
    int i;
    for (i = 0; i<POPULATION_SIZE; i++) totalFitness += population[i].fitness;
    
    species aux [POPULATION_SIZE];
    for (i = 0; i<POPULATION_SIZE; i++) {
        float randomFitness = totalFitness*(float)rand()/(float)RAND_MAX;
        int selectedIndex = 0;
        float deltaFitness = population[selectedIndex].fitness;
        while (randomFitness > deltaFitness) {
            selectedIndex++;
            deltaFitness += population[selectedIndex].fitness;
        }
        aux[i].fitness = population[selectedIndex].fitness;
        int j;
        for (j=0; j<CONFIG_SIZE; j++) aux[i].update[j] = population[selectedIndex].update[j];
    }
}

int main(int argc, char *argv[]) {
    
    int rule [RULE_SIZE] = {
        1,0,0,1,0,1,1,0
    };
    
    species population[POPULATION_SIZE];
    population[0].update[0] = 2;
    population[0].update[1] = 1;
    population[0].update[2] = 2;
    population[0].update[3] = 1;
    population[0].update[4] = 2;
    
    int i, j;
    for (i = 0; i < POPULATION_SIZE; i++) { // Iterates over each species in the population
        
        int configurations [AMOUNT_OF_CONFIGS_TO_TEST][CONFIG_SIZE];
        for (j = 0; j < CONFIG_SIZE; j++) configurations[0][j] = (j%2 == 0)?1:0;
        
        // Converts the species' array of priority to an ordered array of genes
        gene chromossome[CONFIG_SIZE];
        for (j = 0; j<CONFIG_SIZE; j++) {
            chromossome[j].position = j;
            chromossome[j].priority = population[i].update[j];
        }
        quicksort(chromossome, 0, CONFIG_SIZE-1);
        
        // Computes the fitness for each species
        float amountOfConfigsThatDidConverge = 0;
        for (j = 0; j < AMOUNT_OF_CONFIGS_TO_TEST; j++)
            amountOfConfigsThatDidConverge += didConverge(configurations[j], chromossome, rule);
        population[i].fitness = amountOfConfigsThatDidConverge / AMOUNT_OF_CONFIGS_TO_TEST;
        
        
    }
    
    exit(EXIT_SUCCESS);
}

