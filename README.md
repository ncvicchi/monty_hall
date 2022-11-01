# Wazuh Monty Hall Game Challenge

It answers Wazuh technical interview challenge to simulate and verify probabilities on the Monty Hall game

## Request
### Implement an application

Create a program that performs a numerical calculation of the Monty Hall problem. You don’t
need to implement a formula, but a simulation of the game with a random generator. Then, run
thousands or millions of games to estimate the chance to win the prize either staying or
switching the door.
Please implement this solution in the C or C++ language. Feel free to add as many features as
you want. We will value the quality and clarity of your code

## Introduction
The Monty Hall game is a game proposed to Von Savant (guinness record for the highest IQ) in one of her columns at the 
Parade magazine. It is a probability calculation problem, and her answer, although correct, create much controversy
along common people and mathematicians. It's named after a similar show, although not exactly the same, that was hosted
by a tv celebrity known by Monty Hall. 

## The game
We are at a TV Show where 3 doors are presented to us. Behind one of the doors it's the golden price, usually a 
brand-new card. Behind the other 2 doors, in the original game ,there are 2 goats. But since we love llamas (who 
doesn't?), then we will say there are cute llamas instead! Awesome plot twist!

![image](https://user-images.githubusercontent.com/69121070/198913751-ce6802b0-e7d5-4e1e-9651-b7b2f9eb518d.png)

The location of the car and llamas is known to the host of the show, but of course, unknown to us. We are asked to
choose one of the doors.

Immediately after, the host, who as said before knows where the car is, opens one of the remaining doors, knowing 
beforehand that behind it there is a llama (and a pretty one indeed!).

At this point in the game, we are left with only 2 doors unopened, one selected by us, and the car is still behind any
one of them. The host then asks us if we would like to:
- Keep the door we choose
- Change to the other door

The question then is, what should we do, or what would be the best choice?
1. Keep the door we have already chosen
2. Change our choice and select the door that was left unopened
3. No action will have any benefit
4. Toss a coin to decide

## Probabilities

Intuitively, option 3 arises as the most common and intuitive response. We are left with just 2 doors, one with the
prize, the other with our beloved llama, so there would be a 50/50 chance to win the car, right?.

Well... no. 

When we choose the door, we have 3 doors to choose from, the llamas and the car were (we assumed) randomly selected, and
our choice was equally random since we have no other information (sound, smell, a corrupt show producer) that would 
allow us to make a more educated guess.

Then, the probability of the car to be behind the door we've chosen is $\frac{1}{3}$, while the probability of the car
to be in ***any*** of the other two doors, will be the sum of the individual probabilities, that is, $\frac{2}{3}$. 

It will be better to understand if we consider the door we chose as group 1, and both not chosen doors as group 2.

There is then $\frac{1}{3}$ of possibilities that the car will be in group 1, while there are $\frac{2}{3}$ of
probabilities that the card will be in group 2.

When our friendly host revealed in group 2 where a llama was, he simplified the group, but the original probabilities of
the groups didn't change. Group 1 still has 1/3, while group 2 has 2/3. Then, option 2 reveals itself as the optimal
choice. We should change the door we chose for the door we didn't choose.

It is simple to visualize if instead of 3 doors, we have a million doors. Then the groups are divided in 1 group with 
$\frac{1}{1.000.000}$ of possibilities of having the door (the one we chose) and a group with $\frac{999.999}{1.000.000}$ of having the
car. Then the host removes 999.998 door from group 2, all of them with llamas. We end up with group one, which may or
may not have the car, with a $\frac{1}{1.000.000}$ chances, and group 2, with only one door too, which may or may not have the
car, but with a $\frac{999.999}{1.000.000}$ chances of containing the car. The option is then obvious. Change the door.

If this is not clear enough, a probability table with all possible moves and outcomes might be simpler to see:

| Door selected | Car door | Keep door                     | Change door                   |
|---------------|----------|-------------------------------|-------------------------------|
| 1             | 1        | Win                           | Loose                         |
| 1             | 2        | Loose                         | Win                           |
| 1             | 3        | Loose                         | Win                           |
| 2             | 1        | Loose                         | Win                           |
| 2             | 2        | Win                           | Loose                         |
| 2             | 3        | Loose                         | Win                           |
| 3             | 1        | Loose                         | Win                           |
| 3             | 2        | Loose                         | Win                           |
| 3             | 3        | Win                           | Loose                         |
| Probability   |          | $\frac{3}{9}$ = $\frac{1}{3}$ | $\frac{6}{9}$ = $\frac{2}{3}$ |

What if the host would open randomly the door (not knowing either where the car is), and not necessarily the door with
the llama? The table will be a little bigger, but not too much:

| Door selected | Car door | Host opens | Keep door                             | Change door                          |
|---------------|----------|------------|---------------------------------------|--------------------------------------|
| 1             | 1        | 2          | Win                                   | Loose                                |
| 1             | 1        | 3          | Win                                   | Loose                                |
| 1             | 2        | 2          | Loose                                 | Loose                                |
| 1             | 2        | 3          | Loose                                 | Win                                  |
| 1             | 3        | 2          | Loose                                 | Win                                  |
| 1             | 3        | 3          | Loose                                 | Loose                                |
| 2             | 1        | 1          | Loose                                 | Loose                                |
| 2             | 1        | 3          | Loose                                 | Win                                  |
| 2             | 2        | 1          | Win                                   | Loose                                |
| 2             | 2        | 3          | Win                                   | Loose                                |
| 2             | 3        | 1          | Loose                                 | Win                                  |
| 2             | 3        | 3          | Loose                                 | Loose                                |
| 3             | 1        | 2          | Loose                                 | Win                                  |
| 3             | 1        | 3          | Loose                                 | Win                                  |
| 3             | 2        | 2          | Loose                                 | Loose                                |
| 3             | 2        | 3          | Loose                                 | Loose                                |
| 3             | 3        | 2          | Win                                   | Loose                                |
| 3             | 3        | 3          | Win                                   | Loose                                |
| Probability   |          |            | $\frac{6}{18}$ = $\frac{1}{3}$        | $\frac{6}{18}$ =  $\frac{1}{3}$      |

Our possibilities don't change at all now. Since the host chooses randomly, he can not add any new information by
selecting a door, but takes for himself $\frac{1}{3}$ of the chances from group 2.
This is the same as to getting 50% of probability if we keep the door, or 50% if we change the door.
Option 3 would be the answer in this case.

A similar analysis could be done with the tossing of a coin.
If the host choose to open a door with a llama, there will be 2 doors to select from, but the tossing of the coin will
be an independent event, thus giving a $\frac{1}{2}$ chances of winning.
But if the host chooses randomly, then there are chances that he will open the door with the car. Then events wouldn't
be independent, and 1/3 possibilities would occur.

## Probabilities and door count

If there would be more doors in the game, would probabilities change?
If we consider the group probability discussed earlier, we can quickly realize that the more doors involved in the 
game, the more chances to win by switching doors will be (or more chances to lose if the originally selected door is 
kept).
Except for the case that we toss a coin to choose when the host chooses a door with a llama behind. In that case, we
will still have $\frac{1}{2}$ chances, no matter how many doors originally were in the game. Tossing the coin will be an
independent event for the last 2 doors left.

## References

Some references on the game:

- [Movie "21"](https://www.youtube.com/watch?v=iBdjqtR2iK4): Not the best explanation.
- [Numberphile](https://www.youtube.com/watch?v=4Lb-6rxZxx0): Very good explanation, with the concept of "probability
compression" to help understand and also the use of 100 doors to present a more intuitive situation.
- [A Statistical Illusion](https://statisticsbyjim.com/fun/monty-hall-problem/): A very good explanation of why we
 assume incorrectly.

## The application:

### Considerations
I will make an application that will try to demonstrate that the game probabilities we've just calculated actually 
works.

I will support this by applying the "Law of large numbers"
([1](https://www.investopedia.com/terms/l/lawoflargenumbers.asp#:~:text=What%20Is%20the%20Law%20of,as%20the%20sample%20become%20larger.) 
 or [2](https://en.wikipedia.org/wiki/Law_of_large_numbers) ) and a 
[Monte Carlo Simulation approach](https://en.wikipedia.org/wiki/Monte_Carlo_method).

Basically, I will make a simulation where the location of the cars and the llamas, and the selection of the player will
be done randomly.

THe host will have 2 strategies he can choose:
- Open doors with llamas and leave one door unopened.
- Open all doors except one, randomly selected (but not the one selected by the player)

The player, on the other hand, admits 3 strategies:
- Switch doors
- Keep door
- Toss a coin

Then, we have 6 possible games we can simulate:
- host choose llamas/player switch
- host choose llamas/player keep
- host choose llamas/player toss
- host choose randomly/player switch

All 6 strategies are tests for every run. Also, exponential iterations counts are performed to compare how this affects
probabilities, as well as incremental door count to check for probabilities changes.

### Compiling & running

The application was coded, tested and run on CLion (all default configs), under Ubuntu 20.04. No special considerations
are necessaries.
If using any other IDE o compiling from command line, care must be taken to include pthread lib in makefile o compiler
flags.

CLion terminal won't process ANSI Escape sequences. After compiling, please run the application from a linux terminal.

The application won't take main arguments, but parameters can be passed when compiling. If these are not passed, default
values are used:

- MAX_ITERATOR_MULTIPLIER: How many times the iterator is multiply by 10. (default: 8 -> 10.000.000 iterations for each 
game)
- MAX_DOORS: Maximum door count to be simulated. Must be equal or bigger than INIT_DOORS (default: 8 doors)
- INIT_DOORS: Minimum door count to be evaluated. Cannot be less than 3 (default: 3 doors)

### Results analysis

Application output:

    Strategies
    1: Host:open llama's   / Player:switches door
    2: Host:open llama's   / Player:keeps door
    3: Host:open llama's   / Player:tosses coin
    4: Host:opens randomly / Player:switches door
    5: Host:opens randomly / Player:keeps door
    6: Host:opens randomly / Player:tosses coin
    Please wait...

    Iterations │ Doors  │ Strategies wins (Percentage)                                                                                                │
               │        │ Strategy 1         │ Strategy 2         │ Strategy 3         │ Strategy 4         │ Strategy 5         │ Strategy 6         │
    1          │ 3      │ 1        (100.00%) │ 1        (100.00%) │ 0        (0.00  %) │ 1        (100.00%) │ 1        (100.00%) │ 0        (0.00  %) │
    10         │ 3      │ 6        (60.00 %) │ 5        (50.00 %) │ 5        (50.00 %) │ 2        (20.00 %) │ 1        (10.00 %) │ 4        (40.00 %) │
    100        │ 3      │ 54       (54.00 %) │ 31       (31.00 %) │ 56       (56.00 %) │ 32       (32.00 %) │ 34       (34.00 %) │ 32       (32.00 %) │
    1000       │ 3      │ 677      (67.70 %) │ 335      (33.50 %) │ 469      (46.90 %) │ 323      (32.30 %) │ 353      (35.30 %) │ 307      (30.70 %) │
    10000      │ 3      │ 6660     (66.60 %) │ 3417     (34.17 %) │ 4962     (49.62 %) │ 3283     (32.83 %) │ 3387     (33.87 %) │ 3276     (32.76 %) │
    100000     │ 3      │ 66512    (66.51 %) │ 33449    (33.45 %) │ 50060    (50.06 %) │ 33523    (33.52 %) │ 33414    (33.41 %) │ 33332    (33.33 %) │
    1000000    │ 3      │ 666303   (66.63 %) │ 333867   (33.39 %) │ 499669   (49.97 %) │ 333189   (33.32 %) │ 332900   (33.29 %) │ 333882   (33.39 %) │
    10000000   │ 3      │ 6666706  (66.67 %) │ 3334839  (33.35 %) │ 4997940  (49.98 %) │ 3333715  (33.34 %) │ 3334080  (33.34 %) │ 3334332  (33.34 %) │
    1          │ 4      │ 1        (100.00%) │ 0        (0.00  %) │ 1        (100.00%) │ 0        (0.00  %) │ 1        (100.00%) │ 0        (0.00  %) │
    10         │ 4      │ 8        (80.00 %) │ 3        (30.00 %) │ 5        (50.00 %) │ 1        (10.00 %) │ 1        (10.00 %) │ 2        (20.00 %) │
    100        │ 4      │ 75       (75.00 %) │ 22       (22.00 %) │ 40       (40.00 %) │ 24       (24.00 %) │ 22       (22.00 %) │ 27       (27.00 %) │
    1000       │ 4      │ 745      (74.50 %) │ 261      (26.10 %) │ 527      (52.70 %) │ 251      (25.10 %) │ 259      (25.90 %) │ 246      (24.60 %) │
    10000      │ 4      │ 7459     (74.59 %) │ 2606     (26.06 %) │ 5005     (50.05 %) │ 2442     (24.42 %) │ 2530     (25.30 %) │ 2520     (25.20 %) │
    100000     │ 4      │ 75064    (75.06 %) │ 24857    (24.86 %) │ 49958    (49.96 %) │ 24810    (24.81 %) │ 24998    (25.00 %) │ 24669    (24.67 %) │
    1000000    │ 4      │ 750089   (75.01 %) │ 249596   (24.96 %) │ 499723   (49.97 %) │ 249703   (24.97 %) │ 248920   (24.89 %) │ 249393   (24.94 %) │
    10000000   │ 4      │ 7500900  (75.01 %) │ 2500732  (25.01 %) │ 4999040  (49.99 %) │ 2499626  (25.00 %) │ 2497956  (24.98 %) │ 2499764  (25.00 %) │
    1          │ 5      │ 1        (100.00%) │ 1        (100.00%) │ 0        (0.00  %) │ 0        (0.00  %) │ 1        (100.00%) │ 1        (100.00%) │
    10         │ 5      │ 8        (80.00 %) │ 2        (20.00 %) │ 3        (30.00 %) │ 2        (20.00 %) │ 2        (20.00 %) │ 1        (10.00 %) │
    100        │ 5      │ 82       (82.00 %) │ 18       (18.00 %) │ 56       (56.00 %) │ 20       (20.00 %) │ 21       (21.00 %) │ 15       (15.00 %) │
    1000       │ 5      │ 793      (79.30 %) │ 198      (19.80 %) │ 520      (52.00 %) │ 213      (21.30 %) │ 212      (21.20 %) │ 197      (19.70 %) │
    10000      │ 5      │ 8000     (80.00 %) │ 2011     (20.11 %) │ 4996     (49.96 %) │ 1963     (19.63 %) │ 2051     (20.51 %) │ 2001     (20.01 %) │
    100000     │ 5      │ 79903    (79.90 %) │ 19950    (19.95 %) │ 50051    (50.05 %) │ 20098    (20.10 %) │ 19913    (19.91 %) │ 19871    (19.87 %) │
    1000000    │ 5      │ 800110   (80.01 %) │ 199021   (19.90 %) │ 500291   (50.03 %) │ 200187   (20.02 %) │ 199978   (20.00 %) │ 199701   (19.97 %) │
    10000000   │ 5      │ 7998772  (79.99 %) │ 1999594  (20.00 %) │ 4999267  (49.99 %) │ 1998535  (19.99 %) │ 1998302  (19.98 %) │ 1996354  (19.96 %) │
    1          │ 6      │ 1        (100.00%) │ 0        (0.00  %) │ 0        (0.00  %) │ 0        (0.00  %) │ 0        (0.00  %) │ 1        (100.00%) │
    10         │ 6      │ 10       (100.00%) │ 4        (40.00 %) │ 3        (30.00 %) │ 2        (20.00 %) │ 2        (20.00 %) │ 1        (10.00 %) │
    100        │ 6      │ 79       (79.00 %) │ 18       (18.00 %) │ 48       (48.00 %) │ 15       (15.00 %) │ 19       (19.00 %) │ 20       (20.00 %) │
    1000       │ 6      │ 843      (84.30 %) │ 164      (16.40 %) │ 509      (50.90 %) │ 155      (15.50 %) │ 173      (17.30 %) │ 182      (18.20 %) │
    10000      │ 6      │ 8330     (83.30 %) │ 1699     (16.99 %) │ 4993     (49.93 %) │ 1607     (16.07 %) │ 1690     (16.90 %) │ 1681     (16.81 %) │
    100000     │ 6      │ 83303    (83.30 %) │ 16527    (16.53 %) │ 49934    (49.93 %) │ 16717    (16.72 %) │ 16750    (16.75 %) │ 16709    (16.71 %) │
    1000000    │ 6      │ 832799   (83.28 %) │ 166010   (16.60 %) │ 499234   (49.92 %) │ 165811   (16.58 %) │ 166618   (16.66 %) │ 166619   (16.66 %) │
    10000000   │ 6      │ 8334695  (83.35 %) │ 1665558  (16.66 %) │ 4999938  (50.00 %) │ 1667818  (16.68 %) │ 1667538  (16.68 %) │ 1667212  (16.67 %) │
    1          │ 7      │ 1        (100.00%) │ 0        (0.00  %) │ 1        (100.00%) │ 0        (0.00  %) │ 0        (0.00  %) │ 0        (0.00  %) │
    10         │ 7      │ 7        (70.00 %) │ 1        (10.00 %) │ 4        (40.00 %) │ 2        (20.00 %) │ 1        (10.00 %) │ 3        (30.00 %) │
    100        │ 7      │ 80       (80.00 %) │ 12       (12.00 %) │ 50       (50.00 %) │ 17       (17.00 %) │ 15       (15.00 %) │ 14       (14.00 %) │
    1000       │ 7      │ 856      (85.60 %) │ 141      (14.10 %) │ 502      (50.20 %) │ 147      (14.70 %) │ 131      (13.10 %) │ 134      (13.40 %) │
    10000      │ 7      │ 8574     (85.74 %) │ 1526     (15.26 %) │ 5014     (50.14 %) │ 1377     (13.77 %) │ 1418     (14.18 %) │ 1393     (13.93 %) │
    100000     │ 7      │ 85751    (85.75 %) │ 14272    (14.27 %) │ 50197    (50.20 %) │ 14178    (14.18 %) │ 14175    (14.18 %) │ 14197    (14.20 %) │
    1000000    │ 7      │ 857393   (85.74 %) │ 142468   (14.25 %) │ 499467   (49.95 %) │ 142855   (14.29 %) │ 142963   (14.30 %) │ 142718   (14.27 %) │
    10000000   │ 7      │ 8572021  (85.72 %) │ 1429728  (14.30 %) │ 5003039  (50.03 %) │ 1428643  (14.29 %) │ 1428463  (14.28 %) │ 1428706  (14.29 %) │
    
    Process finished with exit code 0

**Several things can be verified:**

- Monte Carlo simulation approach seems to had been a good choice.
- With an iteration multiplier value of 4 we already have a good approximation to analytic probability. 
- Probability convergence is clearly appreciable while iteration increments. 
- Processing time increases linearly with iterations
- All theoretical conclusions are confirmed:
  - If the host chooses llamas, it's always better to switch
  - If the player tosses a coin, probability changes to $\frac{1}{2}$ (for any door amount), if the host chooses to open
  llamas doors (strategy 3) or $\frac{1}{3}$ if the hosts opens randomly. (for 3 doors).
  - All probabilities (except for strategy 3, since it's absolutely independent) will change according to door count.
  This meands that every time $\frac{1}{3}$ or $\frac{2}{3}$ was present, were indeed $\frac{1}{door count}$ or 
 $\frac{2}{door count}$ instead.
  - Switching doors it's the best strategy if the hosts always opens the doors with llamas. Even tossing a coin is a 
better strategy than keeping the door.
  - If the host chooses the door randomly, then there is no good strategy. A probability of $\frac{1}{door count}$ will
  remain as the winning probability.
- rand() standard function was used which, even it is not the best random generator, performed quite well.
