#define CONFIG_SIZE 5
#define AMOUNT_OF_CONFIGS_TO_TEST 1
#define POPULATION_SIZE 2
#define RULE_SIZE 8

typedef struct gene {
    int priority;
    int position;
} gene;

typedef struct species {
    int update[CONFIG_SIZE];
    float fitness;
} species;
