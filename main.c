#include <stdio.h> //defines input and output
#include <string.h> //basic functions of the system
#include <stdlib.h> //functions envolving memory alocation
#include <time.h>
#include "quickSort.h"
#include "aca.h"

// Function to print a chromossome
void print(gene arr[], int size) {
    int i;
    printf("positions  [");
    for (i = 0; i < size; i++) printf("%d ", arr[i].position);
    printf("]\n");
    printf("priorities [");
    for (i = 0; i < size; i++) printf("%d ", arr[i].priority);
    printf("]\n");
}

void prints(species specie){
    printf("update  [");
    for (int i = 0; i < CONFIG_SIZE; i++) printf("%d ", specie.update[i]);
    printf("] ");
    printf("fitness %f \n", specie.fitness);
}

void selection(species population[]){
    
    printf("Starting Selection\n");
    
    //Finds the total fitness
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
    for (i = 0; i<POPULATION_SIZE; i++) {
        population[i].fitness = aux[i].fitness;
        int j;
        for (j=0; j<CONFIG_SIZE; j++) population[i].update[j] = aux[i].update[j];
    }
//    for (i = 0; i < CONFIG_SIZE; i++) population[i] = aux[i]; //Copies aux to config
}

void calculateFitness(species population[], int rule[], int configurations[][CONFIG_SIZE]){
    int i, j, k;
    for (i = 0; i < POPULATION_SIZE; i++) { // Iterates over each species in the population
        
        // Converts the species' array of priority to an ordered array of genes
        gene chromossome[CONFIG_SIZE];
        for (j = 0; j<CONFIG_SIZE; j++) {
            chromossome[j].position = j;
            chromossome[j].priority = population[i].update[j];
        }
        quicksort(chromossome, 0, CONFIG_SIZE-1); 
        print(chromossome, 11);
        // Computes the fitness for each species
        float amountOfConfigsThatDidConverge = 0;
        for (j = 0; j < AMOUNT_OF_CONFIGS_TO_TEST; j++){
            int configSample[CONFIG_SIZE];
            for (k = 0; k < CONFIG_SIZE; k++) configSample[k] = configurations[j][k];
            amountOfConfigsThatDidConverge += didConverge(configSample, chromossome, rule);
        }
        population[i].fitness = amountOfConfigsThatDidConverge / AMOUNT_OF_CONFIGS_TO_TEST;
        printf("specime %d - fitness: %f\n", i, amountOfConfigsThatDidConverge / AMOUNT_OF_CONFIGS_TO_TEST);
    }
}

void selectionWithOffsprings(species population[POPULATION_SIZE*2], int rule[], int configurations[][CONFIG_SIZE]){
    //Finds the total fitness
    float totalFitness = 0.0;
    int i;
    for (i = 0; i<POPULATION_SIZE*2; i++) totalFitness += population[i].fitness;
    
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
    for (i = 0; i<POPULATION_SIZE; i++) {
        population[i].fitness = aux[i].fitness;
        int j;
        for (j=0; j<CONFIG_SIZE; j++) population[i].update[j] = aux[i].update[j];
    }
//    for (i = 0; i < CONFIG_SIZE; i++) population[i] = aux[i]; //Copies aux to config
}

void crossover(species population[POPULATION_SIZE], int rule[], int configurations[][CONFIG_SIZE]){
    
    printf("Starting Crossover\n");
    
    int i, j, offspringIndex = 0;
    
    // Creates the offsprings
    // From each pair of parents are generated two offsprings
    species offsprings[POPULATION_SIZE];
    for (i = 0; i<POPULATION_SIZE; i++){
        int crossoverPoint = rand() % CONFIG_SIZE;
        int k = 0;
        do {
            k = rand()%POPULATION_SIZE;
        } while (k==i);
        // New offspring
        for (j = 0; j<crossoverPoint; j++) offsprings[offspringIndex].update[j] = population[i].update[j]; // First half
        while (j<CONFIG_SIZE) { // Second half
            offsprings[offspringIndex].update[j] = population[k].update[j];
            j++;
        }
        offspringIndex++;
        // New offspring
        for (j = 0; j<crossoverPoint; j++) offsprings[offspringIndex].update[j] = population[k].update[j]; // First half
        while (j<CONFIG_SIZE) { // Second half
            offsprings[offspringIndex].update[j] = population[i].update[j];
            j++;
        }
        offspringIndex++;
    }
    
    calculateFitness(offsprings, rule, configurations);
    
    // Moves the parents and offspring to the same array
    species newPopulation[2*POPULATION_SIZE];
    for (i = 0; i<POPULATION_SIZE; i++) {
        newPopulation[i].fitness = population[i].fitness;
        for (j=0; j<CONFIG_SIZE; j++) newPopulation[i].update[j] = population[i].update[j];
    }
    for (i = 0; i<POPULATION_SIZE; i++) {
        newPopulation[i+POPULATION_SIZE].fitness = offsprings[i].fitness;
        for (j=0; j<CONFIG_SIZE; j++) newPopulation[i+POPULATION_SIZE].update[j] = offsprings[i].update[j];
    }
    
    // Performs selection in the population defined by parents and children
    selectionWithOffsprings(newPopulation, rule, configurations);
    
    // Moving the selected ones to the original array
    for (i = 0; i<POPULATION_SIZE; i++) {
        population[i].fitness = newPopulation[i].fitness;
        for (j=0; j<CONFIG_SIZE; j++) population[i].update[j] = newPopulation[i].update[j];
    }
    // FIXME: Crashes here
}

void mutation(species population[], int factor){
    printf("Starting Mutation\n");
    int i, j;
    for (i = 0; i < POPULATION_SIZE; i++)
        for (j = 0; j < CONFIG_SIZE; j++) {
            float aNumber = 100*(float)rand()/(float)RAND_MAX;
            if (aNumber < factor) {
                int newGene = rand() % CONFIG_SIZE;;
                population[i].update[j] = newGene;
            }
        }
}

int main(int argc, char *argv[]) {
    
    srand((unsigned int)time(NULL));
    
    //int rule [RULE_SIZE] = {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0};
    int rule[8] = {1,0,1,1,1,1,1,1};
    species population[POPULATION_SIZE];
    int i, j, configurations [AMOUNT_OF_CONFIGS_TO_TEST][CONFIG_SIZE];
    
    for (i = 0; i < POPULATION_SIZE; i++)
        for (j = 0; j < CONFIG_SIZE; j++) population[i].update[j] = 0;

    mutation(population, 20);
    
    for (i = 0; i < AMOUNT_OF_CONFIGS_TO_TEST; i++)
        for (j = 0; j < CONFIG_SIZE; j++) configurations[i][j] = rand() % 2;
    
    calculateFitness(population, rule, configurations);
    
    i = 0;
    while (i<100) {
        printf("AGE %d\n", i);
        selection(population);
        crossover(population, rule, configurations);
        mutation(population, 1);
        calculateFitness(population, rule, configurations);
        i++;
    }
    
    exit(EXIT_SUCCESS);
}
