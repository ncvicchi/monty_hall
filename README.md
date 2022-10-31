# wazuh_monty_hall

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
The Monty Hall game its a game proposed to Von Savant (guinness record for the highest IQ) in one of her columns at the 
Parade magazine. It was a probability calculation problem, and her answer, although correct, create much controversy along
common people and mathematicians. It takes its name from a similar show, although not exactly the same, that was hosted 
by a tv celebrity known by Monty Hall. 

## The game
We are at a TV Show where 3 doors are presented to us. Behind one of the doors, its the golden price, generally a brand
new card. Behind the other 2 doors, in the original game there are 2 goats, but we love llamas, so we will say there are
llamas instead! Awesome plot twist!

![image](https://user-images.githubusercontent.com/69121070/198913751-ce6802b0-e7d5-4e1e-9651-b7b2f9eb518d.png)

The location of the car and llamas is known to the host of the show, but of course, unknown to us. We are asked to
choose one of the door.

Immediately after, the host, who as said before knows where the car is, open one of the remaining doors, knowing 
beforehand that behind it there is a llama (and a pretty one!).

At this point in the game, we are left with only 2 doors unopened, one selected by us, and the car is still behind any
one of them. The host then asks us if we would like to:
- Keep the door we choose
- Change to the other door

The question then is, what should we do, or what would be the best choice?
1. Keep the door we have already chosen
2. Change out choice and select the door left unopened
3. No action will have any benefit
4. Toss a coin to decide

## Probabilities

Intuitively, option 3 arises as the most common and intuitive response. We are left with just 2 doors, one with the
prize, the other with our beloved llama, so there would be a 50/50 chance to choose car, right?.

Well... no. 

When we choose the door, we have 3 doors to choose from, the llamas and the car were (we assumed) randomly selected, and
out choice was equally random since we have no other information (sound, smell, a corrupt show producer) that would 
allow us to make a more educated guess.

Then, the probability of the car to be behind the door we've chosen is $\frac{1}{3}$, while the probability of the car
to be in ***any*** of the other two doors, will be the sum of the individual probabilities, that is, $\frac{2}{3}$. 

It will be better to understand if we consider the door we chosen as 1 group, and the 2 not chosen doors as another
group.

There is then 1/3 of possibilities that the car will be in group 1, while there are $\frac{2}{3}$ of probabilities that
the card will be in group 2.

When our friendly host reveals in group 2 where a llama was, he simplifies the group, but the original probabilities of
the groups doesn't change. Group 1 still has 1/3, while group 2 has 2/3. Then, option 2 reveals itself as the optimal
choice. We should change the door we chose for the door we didn't choose.

It is simple to visualize if instead of 3 doors, we have a million doors. Then the groups are divided in 1 group with 
1/1.000.000 of possibilities of having the door (the one we choosed) and a group with 999.999/1.000.000 of having the
car. Then the host removes 999.998 door from group 2, all of them with llamas. We end up with group one, which may or
may not have the car, with a 1/1.000.000 chances, and group 2, with only one door too, which may or may not have the
car, but with a 999.999/1.000.000 chances of containing the car. The option is obvious then. Change the door.

If this is not so easy to understand, a probability table with all possible moves and outcomes can be done to calculate 
them:

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

What if the host would open randomly the door (not knowing either where the car is), and not neccesarily the door with
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

Our possibilities doesn't change at all now. Since the host chooses randomly, he can not add any new information by
selecting a door, but takes for himself 1/3 of the chances from group 2.
This is the same as to assing 50% of probability if we keep the door, or 50% if we change the door.
Option 3 would be the answer in this case.

A similar analisis could be done with the tossing of a coin. 3 and 4 are essentially the same situation. In this case,
since the choice is random, the probability no longer be $\frac{1}{3}$, neither $\frac{2}{3}$, but it will be become 
$\frac{1}{3}$. Why? Simple.

The tossing of the coin has $\frac{1}{2}$ probabilities to come cross or head. And it being applied on 2 doors, one
with a car, and one with a llama. The tossing of the coin is indeed and independent random event, so it replicates its
probability.

## References

Some references on the game:

- [Movie "21"](https://www.youtube.com/watch?v=iBdjqtR2iK4): Not the best explanation.
- [Numberphile](https://www.youtube.com/watch?v=4Lb-6rxZxx0): Very good explanation, with the concept of "probability
compression" to help understand and also the use of 100 doors to present a more intuitive situation.
- [A Statistical Illusion](https://statisticsbyjim.com/fun/monty-hall-problem/): A very good explanation of why we
 assume incorrectly.

## The application:

I will make an application that will try to demonstrate that the game probabilities we've just calculated actually 
works.

I will support this by applying the "Law of large numbers"
([1](https://www.investopedia.com/terms/l/lawoflargenumbers.asp#:~:text=What%20Is%20the%20Law%20of,as%20the%20sample%20become%20larger.) 
 or [2](https://en.wikipedia.org/wiki/Law_of_large_numbers) ) and a 
[Monte Carlo Simulation approach](https://en.wikipedia.org/wiki/Monte_Carlo_method).

Basically, I will make a simulation where the location of the cars and the llamas, and the selection of the player will
be done randomly.

I will present then 3 strategies:
- The host chooses always the door with the llama. This is the first idea and should give a 1/3 chances if the 
player doesn't change the door, and 2/3 chances if the door it's changed.
- The host chooses randomly. In this strategy, the odds would be a 50%/50% chances of winning the car.





