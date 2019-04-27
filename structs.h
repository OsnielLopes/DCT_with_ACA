#define CONFIG_SIZE 42
#define AMOUNT_OF_CONFIGS_TO_TEST 200
#define POPULATION_SIZE 10
#define RULE_SIZE 128

typedef struct gene {
    int priority;
    int position;
} gene;

typedef struct species {
    int update[CONFIG_SIZE];
    float fitness;
} species;
