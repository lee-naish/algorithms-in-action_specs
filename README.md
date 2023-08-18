# Algorithms in Action Specifications

This repository is for the development of specifications etc for
Algorithms in Action (github.com/algorithms-in-action) - adding more
algorithms, etc. In would make sense to add it to the above repository
(and the content will probably be copied at some point), but that
repository is primarily for AIA developers (recently this has been teams
of students); the people using this repository act as clients for the
teams doing development; its for fleshing out how the pseudocode with
refinements, explanations etc should look like, plus C code to test
things.

There may well be some junk branches etc - clueless github user here


## Organisation of folders

- doc/\
    documents, eg definition of the Real specification language
- algm/\
    sub directories for different algorithms (some several related
algorithms); these contain Real specs + C code for testing etc typically
- algm/bst\
    binary search tree
- algm/gsearch\
    graph search (BFS, DFS, Dijkstra's shortest path, A*) and also Prim's
MST algorithm - these all have a similar structure
- algm/hash\
    hashing
- algm/kruskal\
    Kruskal's MST algorithm
- algm/sorts\
    top-down merge sort, heap sort, quicksort (simple + median of 3)
- algm/strings\
    string searching: Horspool's
- algm/tree234\
    234 trees
- algm/ufind\
    union find
- algm/warshall\
    Warshall's transitive closure algorithm
- src/\
    source code, not specific to algorithms being animated (eg script for
cleaning Real specs)
- projects/\
    discussion of how work can be divided up into separate projects for
different teams

