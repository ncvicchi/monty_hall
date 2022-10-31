#include <stdio.h>

#include "randomizer.h"
#include "monty_hall.h"

#ifndef DOOR_COUNT
    #define DOOR_COUNT 3
#endif

#define ITERATIONS 10000

static void runGame(int iterations, int doorsCount, host_strategy_type_t hostStrategy, player_strategy_type_t playerStrategy);

int main() {
    rand_init();

    /* Monty Hall common game winning strategy */
    runGame(ITERATIONS, DOOR_COUNT, choose_llama, switch_door);

    /* Monty Hall common game - losing strategy */
    runGame(ITERATIONS, DOOR_COUNT, choose_llama, keep_door);

    /* Monty Hall common game - coin strategy */
    runGame(ITERATIONS, DOOR_COUNT, choose_llama, toss_coin);

    /* Monty Hall with random opening - switch strategy */
    runGame(ITERATIONS, DOOR_COUNT, choose_random, switch_door);

    /* Monty Hall with random opening - keep strategy */
    runGame(ITERATIONS, DOOR_COUNT, choose_random, keep_door);

    /* Monty Hall with random opening - coin strategy */
    runGame(ITERATIONS, DOOR_COUNT, choose_random, toss_coin);

    return 0;
}

static void runGame(int iterations, int doorCount, host_strategy_type_t hostStrategy, player_strategy_type_t playerStrategy){
    int game, wins;

    printf("%s. %s.\n", getHostStrategyName(hostStrategy), getPlayerStrategyName(playerStrategy));

    for(wins = 0, game = 0; game < iterations; game++){
        wins += gameSession(doorCount, hostStrategy, playerStrategy);
    }
    printf("Result. Wins/Games: %d/%d = %.3f\n\n", wins, game, (float)wins/(float)game);
}