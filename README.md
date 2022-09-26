# freecell
AI-prepared implementation of [FreeCell](https://en.wikipedia.org/wiki/FreeCell).
It serves as a basis for student homework in Artificial Intelligence and Machine Learning [course at FIT BUT](https://www.fit.vut.cz/study/course/SUI/.en).

## Compilation
Simply run `make`.
Requires C++17-able compiler.
The Makefile assumes POSIX threads as available implementation for `std::thread`, but this can be replaced in the linking step.
For Windows users it is required to link PSAPI library in the makefile with `-lpsapi` in `fc-sui:`.

## Usage
The build process results in binary `fc-sui`, which expects two positional arguments:
Number of card deals to run and seed used for pseudo-random deal generation, thus allowing repeatable experiments.

On top of that, a solver can be picked (`--solver`), currently allowing:
* restarting greedy 1-path search (`dummy`)
* breadth-first search (`bfs`)
* depth-first search (`dfs`)
  * has a depth limit controlled by `--depth-limit`
* and A* (`a_star`) which allows to select heuristic:
  * Number of cards not in their home destinations (`nb_not_home`). BEWARE: This is not a proper optimistic heuristic!
  * Custom one (`student`).

Note that in this public repository, BFS, DFS and A* are not implemented.

#### Deal difficulty
By default, cards are dealt in a fully random fashion.
While most of such games can be solved (estimates are well over 99.9 %), such solutions can be quite deep, esp. as this implementation does not expose super-moves.
Therefore, blind search strategies can not be expected to find solutions to such games.
For this purpose, easier deals can be produced by making a given number of reverse moves.
This is controlled by `--easy-mode N`, where `N` is the maximal number of reverse moves made.
Note that the depth of the solution is oftentimes much smaller than `N` because of automatic moves.
Blind search strategies can be expected to solve deals up to `N` around 20.
The A* with the default `nb_not_home` heuristic can realistically solve deals up to `N` around 35.

#### Memory usage
Breadth-first strategies can get really wild allocating all the states to explore.
Maximal memory consumption can be limited using `--mem-limit NB_BYTES`.
If the program takes more than `NB_BYTES` in resident memory usage, it aborts itself.
