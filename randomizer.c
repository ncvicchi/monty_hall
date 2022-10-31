//
// Created by beto on 10/30/22.
//
#include <stdlib.h>
#include <time.h>

void rand_init(){
    /* Combining time() and clock to assure() different seeds between runs and
     * in the same second                                                    * */
    srand((unsigned int)time(NULL) + (unsigned int)clock());
}

/* Return a random number between 0 and limit inclusive, maintaining random uniformity  */
int rand_lim(int limit) {
    int divisor = RAND_MAX/(limit+1);
    int retVal;

    do {
        retVal = rand() / divisor;
    } while (retVal > limit);

    return retVal;
}
