//
// Created by Norberto Vicchi on 10/30/22.
//
#include <stdlib.h>
#include <time.h>

/*
 * rand function in stdlib does not return real random values.
 * We will use it for simplicity, since we got good enough results.
 *
 * If a better randomizer is needed, its only necessary to replace rand_init and rand_lim
 * */

void rand_init(){
    /* Combining time() and clock to assure() different seeds between runs and
     * in the same second                                                    * */
    srand((unsigned int)time(NULL) + (unsigned int)clock());
}

/* Return a random number between 0 and limit inclusive, maintaining random uniformity  */
int rand_lim(int limit) {
    int divisor = RAND_MAX/(limit+1);
    int retVal;

    do
        retVal = rand() / divisor;
    while (retVal > limit);

    return retVal;
}
