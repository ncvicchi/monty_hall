//
// Created by Norberto Vicchi on 10/30/22.
//
#include "monty_hall.h"
#include "randomizer.h"

/* Definitions */
#ifndef MAX_DOORS
    #define MAX_DOORS 3
#endif

typedef int (*host_strategy_t)(int selectedDoor, int doorWithCar, int doorsCount);
typedef int (*player_strategy_t)(int selectedDoor, int hostDoor);

/* Prototypes and declarations */
static int setDoors(int doorsCount);
static int playerChoosesDoor(int doorsCount);

/* Strategies */
static int hostChooseLlamaStrategy(int selectedDoor, int doorWithCar, int doorsCount);
static int hostChooseRandomStrategy(int selectedDoor, int doorWithCar, int doorsCount);

static int playerKeepDoorStrategy(int selectedDoor, int hostDoor);
static int playerSwitchDoorStrategy(int selectedDoor, int hostDoor);
static int playerTossesACoin(int selectedDoor, int hostDoor);
static int gameResult(int selectedDoor, int doorWithCar);

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
        "open llama's",
        "opens randomly"
};

static char * player_strategy_name[3] = {
        "keeps door",
        "switches door",
        "tosses coin"
};

/* Public functions */
/* gameSession
 * Performs a full game session, according to passed strategies
 * It returns 1 if car player wins a car, 0 if player only won a cute llama
 * */
int gameSession(int doorCount,
                host_strategy_type_t hostStrategy,
                 player_strategy_type_t playerStrategy){

    int doorKeptClosed;
    int selectedDoor;
    int doorWithCar;

    /* Game cannot be played with less than 3 doors. I also specify a 100000 upper limit */
    if(MAX_DOORS > 100000 || doorCount < 3)
        return 0;

    /* Places llamas behind all doors, except for 1 door with a car */
    /* The door with the car is return for optimization porpoises.
     * It let us avoid to swipe all doors to find it
     * */
    doorWithCar = setDoors(doorCount);

    /* Randomly chooses a door */
    selectedDoor = playerChoosesDoor(doorCount);

    /* Host opens remaining door according to host strategy */
    doorKeptClosed = host_strategies[hostStrategy](selectedDoor, doorWithCar, doorCount);

    /* Player plays according to player strategy and returns the finally selected door */
    selectedDoor = player_strategies[playerStrategy](selectedDoor, doorKeptClosed);

    /* It opens the door and returns if the player won o lost */
    return gameResult(selectedDoor, doorWithCar);
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

/* Although the following function do exactly the same, they have a different use
 * An alias could be used, but doing it like this allows increasing maintainability if in the future the way
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
    /* The host knows where the car and llamas are. He will choose all doors with llamas in the group not
     * selected by the player, and leave only one door. The one with the car, or anyone with a llama if the selected
     * door has the car behind it.
     * For simplicity, if player has selected the door with the car behind, the host will always choose the leftmost
     * door since this wouldn't change probability
     * */

    (void)doorsCount;

    /* The player found the car! Then the host removes all doors but the leftmost (except it is the door with the car)
     * */
    if(selectedDoor == doorWithCar){
        if(selectedDoor)
            return 0;
        else
            return 1;
    }

    /* The player has a llama. The host must leave the car in group 2 (opens all doors with llamas) */
    return doorWithCar;
}

/*
 * Hosts open all doors except one randomly left closed
 * If this door happens to be the selected door, we will change to the leftmost door,
 * unless the host door happens to be the first one.
 * */
static int hostChooseRandomStrategy(int selectedDoor, int doorWithCar, int doorsCount){
    int hostDoor = rand_lim(doorsCount - 1);

    (void)doorWithCar;

    if (hostDoor == selectedDoor) {
        if (hostDoor)
            return hostDoor - 1;
        else
            return hostDoor + 1;
    }

    return hostDoor;
}

static int playerKeepDoorStrategy(int selectedDoor, int hostDoor){
    (void)hostDoor;
    return selectedDoor;
}

static int playerSwitchDoorStrategy(int selectedDoor, int hostDoor){
    (void)selectedDoor;
    return hostDoor;
}

static int playerTossesACoin(int selectedDoor, int hostDoor){
    int coin = rand_lim(1);
    if(coin)
        return playerKeepDoorStrategy(selectedDoor, hostDoor);
    else
        return playerSwitchDoorStrategy(selectedDoor, hostDoor);
}

static int gameResult(int selectedDoor, int doorWithCar){
    return selectedDoor == doorWithCar? 1:0;
}