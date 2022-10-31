//
// Created by beto on 10/30/22.
//

#ifndef WAZUH_MONTY_HALL_MONTY_HALL_H
#define WAZUH_MONTY_HALL_MONTY_HALL_H

/*
 * Host strategy:
 * choose_llama: Will choose any of remaining doors with a llama behind
 * choose_random: Will choose any of the remaining doors
 * */
typedef enum{
    choose_llama = 0,
    choose_random
}host_strategy_type_t;

/*
 * Player strategy:
 * keep_door: Player will always choose to keep the door already selected
 * chance_door: Player will change the selected door to the one left unopened by the host
 * */
typedef enum{
    keep_door = 0,
    switch_door,
    toss_coin
}player_strategy_type_t;

/* Performs a game session with the given strategies and door count */
int gameSession(int doorCount,
                host_strategy_type_t hostStrategy,
                player_strategy_type_t playerStrategy);

/* Returns player strategy name */
char *getHostStrategyName(host_strategy_type_t strategy);

/* Returns player strategy name */
char *getPlayerStrategyName(player_strategy_type_t strategy);

#endif //WAZUH_MONTY_HALL_MONTY_HALL_H
