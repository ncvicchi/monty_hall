//
// Created by beto on 10/30/22.
//
#include "monty_hall.h"
#include "randomizer.h"

/* Definitions */
#ifndef MAX_DOORS
    #define MAX_DOORS 3
#endif

typedef int (*host_strategy_t)(int selectedDoor, int doorWithCar, int doorsCount);
typedef int (*player_strategy_t)(int selectedDoor, int hostDoor, int doorWithCar, int doorsCount);

/* Prototypes and declarations */
static int setDoors(int doorsCount);
static int playerChoosesDoor(int doorsCount);

/* Strategies */
static int hostChooseLlamaStrategy(int selectedDoor, int doorWithCar, int doorsCount);
static int hostChooseRandomStrategy(int selectedDoor, int doorWithCar, int doorsCount);

static int playerKeepDoorStrategy(int selectedDoor, int hostDoor, int doorWithCar, int doorsCount);
static int playerSwitchDoorStrategy(int selectedDoor, int hostDoor, int doorWithCar, int doorsCount);
static int playerTossesACoin(int selectedDoor, int hostDoor, int doorWithCar, int doorsCount);

static host_strategy_t host_strategies[2] = {
        hostChooseLlamaStrategy,
        hostChooseRandomStrategy
};

static player_strategy_t player_strategies[3] = {
        playerKeepDoorStrategy,
        playerSwitchDoorStrategy,
        playerTossesACoin,
};

static char * host_strategy_name[2] = {
        "Host opens all llamas doors",
        "Host opens randomly"
};

static char * player_strategy_name[3] = {
        "Player keeps door",
        "Player switches door",
        "Player toss a coin to decide"
};

/* Public functions */
/* gameSession
 * Performs a full game session, according to passed strategies
 * It returns 1 if car player win a car, 0 if player only won a llama
 * */
int gameSession(int doorCount,
                host_strategy_type_t hostStrategy,
                 player_strategy_type_t playerStrategy){

    int openedDoor;
    int selectedDoor;
    int doorWithCar;

    /* Game cannot be played with less than 3 doors. I also specify a 100000 upper limit */
    if(MAX_DOORS > 100000 || doorCount < 3)
        return 0;

    /*Places llamas behind all doors, except for 1 with a car */
    /* The door with the car is return for optimization.
     * It prevents to swipe all doors to find it
     * */
    doorWithCar = setDoors(doorCount);

    /* Randomly chooses a door */
    selectedDoor = playerChoosesDoor(doorCount);

    /* Hosts open remaining door according to host strategy */
    openedDoor = host_strategies[hostStrategy](selectedDoor, doorWithCar, doorCount);

    /* Player plays according to player strategy and return if win (1) or lost(0) the car */
    return player_strategies[playerStrategy](selectedDoor, openedDoor, doorWithCar, doorCount);
}

/* Returns host strategy name */
char *getHostStrategyName(host_strategy_type_t strategy){
    if(strategy >= choose_llama && strategy <= choose_random)
        return host_strategy_name[strategy];
    return "";
}

/* Returns player strategy name */
char *getPlayerStrategyName(player_strategy_type_t strategy){
    if(strategy >= keep_door && strategy <= toss_coin)
        return player_strategy_name[strategy];
    return "";
}

/* Private functions */

/* Although the following function do exactly the same,
 * they have a different use.
 * Doing it like this allows increasing readability as well
 * as allowing maintainability if in the future the way
 * to implement them should change
 * */

/* Sets doors so the game can can be played */
static int setDoors(int doorsCount){
    /* Randomly assign a car to a door */
    return rand_lim(doorsCount - 1);
}

/* Chooses door randomly */
static int playerChoosesDoor(int doorsCount){
    /* Randomly select a door */
    return rand_lim(doorsCount - 1);
}

/* The host choose llamas from the unselected doors.
 * Return: the only door left unopened.
  * */
static int hostChooseLlamaStrategy(int selectedDoor, int doorWithCar, int doorsCount){
    /* The host knows where the car and llamas are. He will choose all doors with llamas in the group
     * not selected by the player, and leave only one door. The one with the car, or anyone with a llama if the selected
     * door has the car behing it.
     * For simplicity, we will always choose the leftmost door since this wouldn't change probability
     * */

    /* The player found the car! */
    if(selectedDoor == doorWithCar){
        if(selectedDoor)
            return 0;
        else
            return 1;
    }

    /* The player has a llama. The host must leave the car in group 2 (chooses all llamas)S */
    return doorWithCar;
}
/*
 * Randomly chooses host door to open.
 * If door happens to be the selected door, we will change to the leftmost door,
 * unless the host door happens to be the first one.
 * */
static int hostChooseRandomStrategy(int selectedDoor, int doorWithCar, int doorsCount){
    int hostDoor = rand_lim(doorsCount - 1);
    if (hostDoor == selectedDoor) {
        if (hostDoor)
            return hostDoor - 1;
        else
            return hostDoor + 1;
    }
}

static int playerKeepDoorStrategy(int selectedDoor, int hostDoor, int doorWithCar, int doorsCount){
    return selectedDoor == doorWithCar? 1:0;
}

static int playerSwitchDoorStrategy(int selectedDoor, int hostDoor, int doorWithCar, int doorsCount){
    return  hostDoor == doorWithCar? 1:0;
}

static int playerTossesACoin(int selectedDoor, int hostDoor, int doorWithCar, int doorsCount){
    int coin = rand_lim(1);
    if(coin)
        return playerKeepDoorStrategy(selectedDoor, hostDoor, doorWithCar, doorsCount);
    else
        return playerSwitchDoorStrategy(selectedDoor, hostDoor, doorWithCar, doorsCount);
}
