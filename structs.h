#define CONFIG_SIZE 11
#define AMOUNT_OF_CONFIGS_TO_TEST 100
#define POPULATION_SIZE 100
#define RULE_SIZE 128

typedef struct gene {
    int priority;
    int position;
} gene;

typedef struct species {
    int update[CONFIG_SIZE];
    float fitness;
} species;
