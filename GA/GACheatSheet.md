Basic Genetic Algorithm
=======================

1. [Start] Generate random population.
2. [Fitness] Evaluate the fitness of each individual.
3. [New Population] Create the new population by repeating the next steps until
   the new population is complete.
  1. [Selection] Select two individuals from the population.
  2. [Crossover] With a crossover probability, cross over the selected parents
     to form new offspring. If no crossover was performed, offspring is an
     exact copy of parents.
  3. [Mutation] With a mutation probability, mutate new offspring at each locus
     (position in chromossome).
  4. [Accepting] Place new offspring in the new population.
4. [Replace] Usa new generated population for the further run of algorithm.
5. [Test] If the end condition is satisfied, stop and return the best solution
   in current population.
6. [Loop] Go to step 2.

Seems that [Test] is on the wrong place.. It should be before the [New
Population] was chosen.

Cross-Over Selection
====================

Roulette Wheel Selection
------------------------

(aka Fitness Proportinate Selection)
The Roulette Wheel Selection selects the parents according to their fitness.

1. Calculate the sum of all fitness in population - sum S
2. Generate random number from interval (0, S) - random r
3. Go through the population and find the individual representing the r

Tournament Selection
--------------------

The Tournament Selection involves running several "tournaments" among few
individuals chosen at random from the population. The winner of each tournament
is selected for crossover. If the tournament size is larger, weak individuals
have a smaller chance to be selected.

1. Choose k (the tournament size) individuals at random
2. Choose the best individual from the pool with probability p
3. Choose the second best individual with probability p(1-p)
4. Choose the third best individual with probability p(1-p)^2
5. so on...

Deterministic tournament selection selects the best individual (p=1).
A 1-way tournament (k=1) selection is equivalent to random selection.
The chosen individual can be removed from the population that the selection is
made from if desired, otherwise individuals can be selected more than once for
the next generation.

Truncation Selection
--------------------

The Trucation Selection the candidate individuals are ordered by fitness, and
some portion p(e.g. p = 1/2, 1/3) of the fittest individuals are selected for
crossover 1/p times.

Ranking Selection
-----------------

The Ranking Selection first ranks the population and then every individual
receives a new fitness from this ranking. The worst will have fitness 1, the
second worst 2, etc. The best will have fitness N (population size).
After the ranking, the method procedes as the Roulette Wheel.

This method can lead to slower convergence because the best chromossomes do not
differ so much from the others.


Selection For Surviving
=======================

Elitism
-------

The Elitism first copies the best chromossomes to the new population. Thus, the
best chromossomes aren't lost for the next iteration.
Elitism can very rapidly increase performance of the GA!
