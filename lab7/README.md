### Large-scale neighborhood search


Destroy operator should remove a relatively large fraction of nodes/edges from the current solution, e.g. 20-30%. The removed edges could be selected at random, as a single subpath, or several subpaths. You can try to propose some heuristic rules to remove “bad” nodes/edges, e.g. long edges or costly nodes. Such heuristics should be, however, randomized not completely deterministic. For example the probability of removal should depend on the length/cost.

As repair operator use the best greedy heuristic (including greedy-regret) from previous assignments.

The destroy-repair operators should be clearly described.

As the starting solution use either random solution or solution created by a greedy heuristic. In the case of random solution local search should always be applied to this solution.

Implement two versions of LNS – using or not local search after destroy-repair operators. Use steepest local search when it is used.

Computational experiment: Run each of the methods (wit and without local search) 20 times for each instance. Use the average running time of MSLS from the previous assignment. Report also the number of iterations of the main loop.

Reporting results: Use tables as in the previous assignments. Add a table with the number of iterations of the main loop. Include results of MSLS and ILS.

The outline of the report as previously.

In dir "evo_comp" execute:

```bash
g++ src/*.cpp lab7/main.cpp -Isrc -o lab7/myprogram -std=c++20 && ./lab7/myprogram
```