### The use of candidate moves in local search

The goal of the task is to improve the time efficiency of the steepest local search with the use of
candidate moves using the neighborhood, which turned out to be the best in the previous
assignment,

As candidate moves, we use moves that introduce at least one candidate edge to the solution. We
define the candidate edges by determining for each vertex 10 other nearest vertices. This parameter
can also be selected experimentally to obtain the best results.

As starting solutions use random solutions.

As baseline report also results of the steepest local search with random starting solutions without
these mechanisms.

Computational experiment: Run each of the methods 200 times.
Reporting results: Use tables as in the previous assignment.
The outline of the report as previously.
Include also the best solution nodes separated by commas.

In dir "evo_comp" execute:

```bash
g++ src/*.cpp lab4/main.cpp -Isrc -o lab4/myprogram -std=c++20 && ./lab4/myprogram
```