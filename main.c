#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <bits/types/sig_atomic_t.h>

#include "randomizer.h"
#include "monty_hall.h"

#ifndef MAX_ITERATOR_MULTIPLIER
    #define MAX_ITERATOR_MULTIPLIER 8
#endif

#ifndef MAX_DOORS
    #define MAX_DOORS 8
#endif

#ifndef INIT_DOORS
    #define INIT_DOORS 3
#endif

#if INIT_DOORS < 3
#error "The game requires at least 3 doors"
#endif

#if INIT_DOORS > MAX_DOORS
#error "Maximum door count cannot be smaller than initial door count"
#endif

/* Just to avoid magic numbers */
#define STRATEGIES_NUMBER 6

typedef struct {
    int iterations;
    int doorsCount;
    host_strategy_type_t hostStrategy;
    player_strategy_type_t playerStrategy;
    int wins;
    int games;
    sig_atomic_t end;
    pthread_t thread;
}game_t;

static game_t *launchGames(int doorCount, host_strategy_type_t hostStrategy, player_strategy_type_t playerStrategy);
static int runGame(int iterations, int doorCount, host_strategy_type_t hostStrategy, player_strategy_type_t playerStrategy);
static void *runGameThread(void *arg);
static void waitForThreadsToFinish(game_t *games[6][MAX_DOORS - INIT_DOORS]);
static void printResults(game_t *games[6][MAX_DOORS - INIT_DOORS]);

int main(void) {
    int doorCount;
    int door;
    game_t *games[STRATEGIES_NUMBER][MAX_DOORS - INIT_DOORS];

    /* Randomizer must be seeded before use */
    rand_init();

    printf("Strategies:\n");
    printf("1: Host:%-14s / Player:%s\n", getHostStrategyName(choose_llama), getPlayerStrategyName(switch_door));
    printf("2: Host:%-14s / Player:%s\n", getHostStrategyName(choose_llama), getPlayerStrategyName(keep_door));
    printf("3: Host:%-14s / Player:%s\n", getHostStrategyName(choose_llama), getPlayerStrategyName(toss_coin));
    printf("4: Host:%-14s / Player:%s\n", getHostStrategyName(choose_random), getPlayerStrategyName(switch_door));
    printf("5: Host:%-14s / Player:%s\n", getHostStrategyName(choose_random), getPlayerStrategyName(keep_door));
    printf("6: Host:%-14s / Player:%s\n", getHostStrategyName(choose_random), getPlayerStrategyName(toss_coin));
    printf("Please wait...\n\n");

    /* We want to verify how probability varies with different door count */
    for (door=0, doorCount = INIT_DOORS; doorCount < MAX_DOORS; doorCount++, door++) {
        /* Monty Hall common game - player winning strategy */
        games[0][door] = launchGames(doorCount, choose_llama, switch_door);

        /* Monty Hall common game - player losing strategy */
        games[1][door] = launchGames(doorCount, choose_llama, keep_door);

        /* Monty Hall common game - player coin strategy */
        games[2][door] = launchGames(doorCount, choose_llama, toss_coin);

        /* Monty Hall with random opening door - player switch strategy */
        games[3][door] = launchGames(doorCount, choose_random, switch_door);

        /* Monty Hall with random opening door - player keep strategy */
        games[4][door] = launchGames(doorCount, choose_random, keep_door);

        /* Monty Hall with random opening door - player coin strategy */
        games[5][door] = launchGames(doorCount, choose_random, toss_coin);
    }

    /* Let's wait some time until all games are over */
    waitForThreadsToFinish(games);

    /* All games ended. Let's see the results */
    printResults(games);

    /* Took a lot of resources. It's time to give them back! */
    for (int strategy_combination = 0; strategy_combination < STRATEGIES_NUMBER; strategy_combination++)
        for (door = 0; door < MAX_DOORS-INIT_DOORS; door++)
            free(games[strategy_combination][door]);

    return 0;
}

/* Runs a single game session */
static int runGame(int iterations, int doorCount, host_strategy_type_t hostStrategy, player_strategy_type_t playerStrategy){
    int game, wins;

    for(wins = 0, game = 0; game < iterations; game++){
        wins += gameSession(doorCount, hostStrategy, playerStrategy);
    }

    return wins;
}

/* Thread for a given game session */
static void *runGameThread(void *arg){
    game_t *game = (game_t *)arg;

    game->wins = runGame(game->iterations, game->doorsCount, game->hostStrategy, game->playerStrategy);
    game->end = 1;

    return NULL;
}

/* Launches all iterations for a given combination of strategies.
 * It creates an independent thread to run them.
 * */
static game_t * launchGames(int doorCount, host_strategy_type_t hostStrategy, player_strategy_type_t playerStrategy){
    int i;
    int iterations = 1;
    game_t *games;

    games = calloc(MAX_ITERATOR_MULTIPLIER, sizeof(game_t));
    if(!games){
        exit(-1);
    }

    for (i = 0; i < MAX_ITERATOR_MULTIPLIER; i++) {
        games[i].doorsCount = doorCount;
        games[i].hostStrategy = hostStrategy;
        games[i].playerStrategy = playerStrategy;
        games[i].end = 0;
        games[i].iterations = iterations;

        pthread_create(&(games[i].thread), NULL, runGameThread, games + i);

        iterations *= 10;
    }

    return games;
}

/* Checks games end flag to verify that all threads finished processing
 * This flag is an atomic type to allow checking it from the main thread
 * without the need of a mutex or semaphore
 * */
static void waitForThreadsToFinish(game_t *games[STRATEGIES_NUMBER][MAX_DOORS - INIT_DOORS]){
    int threadCount=0;
    int door;
    const int maxThreads = ((MAX_DOORS - INIT_DOORS) * MAX_ITERATOR_MULTIPLIER * 6);
    int i,j;
    char animation[] = "-\\|/";
    static int currentFrame = 0;

    /* Wait for launched games to finish */
    while(threadCount < maxThreads) {
        threadCount = 0;
        for (i = 0; i < 6; i++) {
            for (door = 0; door < MAX_DOORS - INIT_DOORS; door++) {
                for (j = 0; j < MAX_ITERATOR_MULTIPLIER; j++) {
                    if(games[i][door][j].end == 1)
                        threadCount++;
                }
            }
        }

        printf("\x1B[1F\x1B[2K (%2.0f %%) %6d/%d threads finished %c\n",
               100*(float)threadCount / (float)maxThreads,
               threadCount,
               maxThreads,
               animation[currentFrame++]);

        if(currentFrame == 4)
            currentFrame = 0;
        usleep(100000);
    }
}

/* Prints all game sessions in a table sorted by door count, iterations, and strategies used */
static void printResults(game_t *games[STRATEGIES_NUMBER][MAX_DOORS - INIT_DOORS]){
    int door, j;

    printf("Iterations │ Doors  │ %-*s│\n", ((13+MAX_ITERATOR_MULTIPLIER)*6)-2, "Strategies wins (Percentage)");

    // Header
    printf("           │        │ %-*s │ %-*s │ %-*s │ %-*s │ %-*s │ %-*s │\n",
           10 + MAX_ITERATOR_MULTIPLIER, "Strategy 1",
           10 + MAX_ITERATOR_MULTIPLIER, "Strategy 2",
           10 + MAX_ITERATOR_MULTIPLIER, "Strategy 3",
           10 + MAX_ITERATOR_MULTIPLIER, "Strategy 4",
           10 + MAX_ITERATOR_MULTIPLIER, "Strategy 5",
           10 + MAX_ITERATOR_MULTIPLIER, "Strategy 6"
    );

    for(door=0;door<MAX_DOORS-INIT_DOORS;door++) {
        for(j = 0; j < MAX_ITERATOR_MULTIPLIER; j++) {
            printf(
                    "%-10d │"
                    " %-6d │"
                    " %-*d (%-6.2f%%) │"
                    " %-*d (%-6.2f%%) │"
                    " %-*d (%-6.2f%%) │"
                    " %-*d (%-6.2f%%) │"
                    " %-*d (%-6.2f%%) │"
                    " %-*d (%-6.2f%%) │\n",
                    games[0][door][j].iterations,
                    INIT_DOORS + door,
                    MAX_ITERATOR_MULTIPLIER, games[0][door][j].wins,(float) games[0][door][j].wins / ((float) games[0][door][j].iterations / 100),
                    MAX_ITERATOR_MULTIPLIER, games[1][door][j].wins,(float) games[1][door][j].wins / ((float) games[1][door][j].iterations / 100),
                    MAX_ITERATOR_MULTIPLIER, games[2][door][j].wins,(float) games[2][door][j].wins / ((float) games[2][door][j].iterations / 100),
                    MAX_ITERATOR_MULTIPLIER, games[3][door][j].wins,(float) games[3][door][j].wins / ((float) games[3][door][j].iterations / 100),
                    MAX_ITERATOR_MULTIPLIER, games[4][door][j].wins,(float) games[4][door][j].wins / ((float) games[4][door][j].iterations / 100),
                    MAX_ITERATOR_MULTIPLIER, games[5][door][j].wins,(float) games[5][door][j].wins / ((float) games[5][door][j].iterations / 100)
            );
        }
    }
}