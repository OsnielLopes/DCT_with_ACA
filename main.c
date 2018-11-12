#include <stdio.h> //defines input and output
#include <string.h> //basic functions of the system
#include <stdlib.h> //functions envolving memory alocation

#define NUMBER_OF_NEIGHBOURS 2
#define DELTA_T 200

#define CONFIG_SIZE 5
#define POPULATION_SIZE 1
#define AMOUNT_OF_CONFIGS_TO_TEST 1

typedef struct gene {
    int priority;
    int position;
} gene;

typedef struct species {
    int update[CONFIG_SIZE];
    float fitness;
} species;

// Function to print a chromossome
void print(gene arr[], int size) {
    printf("positions  [");
    for (int i = 0; i < size; i++) printf("%d ", arr[i].position);
    printf("]\n");
    printf("priorities [");
    for (i = 0; i < size; i++) printf("%d ", arr[i].priority);
    printf("]\n");
}

// Function to swap two pointers
void swap(gene *a, gene *b) {
    gene temp = *a;
    *a = *b;
    *b = temp;
}

// Function to run quicksort
// l is the leftmost starting index, which begins at 0
// r is the rightmost starting index, which begins at array length - 1
void quicksort(gene chromossome[], int l, int r) {
    
    if (l >= r) return;

    int pivot = chromossome[r].priority;
    int slipt = l;
    
    for (int i = l; i <= r; i++)
        if (chromossome[i].priority <= pivot) {
            swap(&chromossome[slipt], &chromossome[i]);
            slipt++;
        }
    
    quicksort(chromossome, l, slipt-2);
    quicksort(chromossome, slipt, r);
}

int didConverge(int *config, gene chromossome[]) {
    
    int i=0;
    
    int amountOfZero = 0, amountOfOne = 0;
    for (i = 0; i < CONFIG_SIZE; i++)
        if (i == 0) amountOfZero++;
        else amountOfOne++;
    int initialDensity = (amountOfZero > amountOfOne) ? 0 : 1;
    
    //TODO: asynchronous cellular automata update
//    for (i = 0; i<t; i++) { //iterates t times
//        int j;
//        for (j = 0; j<sizeof(update+j); j++) { //iterates over each subupdate
//            *int placeholderConfig = (int *) malloc(CONFIG_SIZE * sizeof(int));
//            int k;
//            for (k = 0; k < sizeof(update+j); k++) { //iterates over each index in subupdate
//            }
//        }
//    }
    
    //FIXME: The final density must be computed only if the automaton converge
    amountOfZero = 0;
    amountOfOne = 0;
    for (i = 0; i < CONFIG_SIZE; i++)
        if (i == 0) amountOfZero++;
        else amountOfOne++;
    int finalDensity = (amountOfZero > amountOfOne) ? 0 : 1;
    return finalDensity == initialDensity;
}

int main(int argc, char *argv[]) {
    
    species population[POPULATION_SIZE];
    population[0].update[0] = 0;
    population[0].update[0] = 1;
    population[0].update[0] = 0;
    population[0].update[0] = 1;
    population[0].update[0] = 0;
    
    int configurations [AMOUNT_OF_CONFIGS_TO_TEST][CONFIG_SIZE] = {
        0,1,0,1,0
    };
    
    int i, j;
    for (i = 0; i < POPULATION_SIZE; i++) { // Iterates over each species in the population
        
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
            amountOfConfigsThatDidConverge += didConverge(configurations[j], chromossome);
        population[i].fitness = amountOfConfigsThatDidConverge / AMOUNT_OF_CONFIGS_TO_TEST;
    }
    
    exit(EXIT_SUCCESS);
}

