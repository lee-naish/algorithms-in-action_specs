/*
Graph search algorithms:
    DFS
    BFS
    Dijkstra's shortest path
    A*
Plus
    Prims MST algorithm

Code is very messy and probably should be tested more...
Based on code for Prim's Algorithm that had input of edge/cost matrix
and it was insensitive to graph layout.  Some the the other algorithms
at least (and probably Prims) are much more easily visualised with a
(preferably planar) graph where costs are sensitive to layout, based on
distance between nodes, so here we input a graph based on layout and
compute the cost matrix based on that.  The matrix representation is
probably not the best for practical implementations and its a bit of a
pain for input of sparse graphs but is ok for the animations and testing
the code.

Each node n has a position on a 2D grid given by xpos[n] and ypos[n];
these are input and used to compute weights and heuristic values (for the
algorithms that use them) (the weights in the input matrix are ignored,
except zero means no edge) - either Manhattan distance or straight line
(Euclidean) distance, rounded to an integer.

*/

// ALGORITHM is #defined for different versions
// 0 - Prim's MST
// 1 - BFS
// 2 - DFS
// 3 - Dijkstra's shortest path
// 4 - A*
#define PRIM 0
#define BFS 1
#define DFS 2
#define DIJK 3
#define ASTAR 4
#ifndef ALGORITHM
    #define ALGORITHM PRIM // default is Prim's MST
#endif

// WEIGHT is #defined for different versions of edge weights:
// 0 - weights as in input
// 1 - Manhattan
// 2 - Euclidean
#define W_IN 0
#define MANHATTAN 1
#define EUCLID 2
#ifndef WEIGHT
    #define WEIGHT EUCLID // default is Euclidean
#endif

#ifndef HEURISTIC
    #define HEURISTIC EUCLID // default is Euclidean
#endif

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>

#define infty INT_MAX
#define MAXSIZE 21  // max number of vertices + 1 (0 unused for nodes)
typedef int vertex;

int graphsize;     // The number of vertices (<= MAXSIZE)
int xpos[MAXSIZE]; // x coordinate of vertex
int ypos[MAXSIZE]; // y coordinate of vertex
int weight[MAXSIZE][MAXSIZE]; // edge weights computed from from xpos,ypos
int cost[MAXSIZE];         /* Keeps track of current cost for each vertex */
int finalised[MAXSIZE];  // flag - final parent has been determined
int seen[MAXSIZE];      // vertex seen for BFS...
vertex parent[MAXSIZE];    /* Specifies spanning tree or paths */
vertex end[MAXSIZE];  // defines end node(s), if any
vertex endnode; // single end node (for A*)
vertex startnode; // start node

// The frontier is kept in nodes[f_start]...nodes[f_end]
// Depending on the algorithm, it could be a stack, queue or priority
// queue.
//
// Prim's, Dijkstra, A*:
// For priority queues, coding is simplest if the PQ contains the unseen
// nodes (with cost infinity) as well as the frontier nodes (with
// smaller costs). f_end is always the end of the array. f_start = 1
// initially and is incremented each time around the main loop; elemnts
// before f_start have been finalised.
// 
// BFS:
// For queues, just the frontier is stored, with f_start = f_end = 1
// initially. f_end is incremented as elements are added and f_start is
// incremented as elements are removed.  There is no need to wrap around
// because each node is added at most once. Elements before f_start have
// been finalised.
// 
// DFS:
// For stacks, we start end of the array and grow the stack "backwards".
// f_start = f_end = graphsize initially and f_start is incremented and
// decremented as elements are removed and added, respectively.
vertex nodes[MAXSIZE];
int f_start, f_end;


// Manhattan distance between nodes
int
manhattan(int i, int j) {
    return abs(xpos[i] - xpos[j]) + abs(ypos[i] - ypos[j]);
}

// Euclidean (straight line) distance between nodes (converted to int)
int
euclid(int i, int j) {
    int dx = xpos[i]-xpos[j];
    int dy = ypos[i]-ypos[j];
    // rounding down may cause inadmissibility
    //return (int)floor(0.5 + sqrt((double)(dx*dx + dy*dy)));
    return (int)ceil(sqrt((double)(dx*dx + dy*dy)));
}

int
heur(vertex n) {
#if HEURISTIC==MANHATTAN
    return manhattan(n, endnode);
#else
    return euclid(n, endnode);
#endif
}

// (possibly) recompute edge weight weight[i][j]
int
weight_fn(int i, int j) {
#if WEIGHT==W_IN // use weights from input
    return weight[i][j];
#elif WEIGHT==MANHATTAN // use manhattan distance
    return manhattan(i, j);
#else // default to EUCLID
    return euclid(i, j);
#endif
}

// version of plus that handles arguments being infinity
// without overflowing to a negative number (could pick a smaller number
// to represent infinity and hope costs don't get that big)
int
infplus(int i, int j) {
    if ((float)i + (float)j >= (float)infty)
        return infty;
    else
        return i + j;
}

// sort PQ (overkill since it will be mostly sorted already when we call
// this, with just one cost updated)
void
f_sort() {
    int i, j, v;
    for (i = f_start + 1; i<=f_end; i++) {
        v = nodes[i];
#if ALGORITHM==ASTAR
        int c = infplus(cost[v], heur(v));
// printf("v %d c %d h %d\n", v, cost[v], heur(v));
        for (j = i-1; j >= f_start &&
                    c < infplus(cost[nodes[j]], heur(nodes[j])); j--) {
#else
        int c = cost[v];
        for (j = i-1; j >= f_start &&
                    c < cost[nodes[j]]; j--) {
#endif
// printf("c %d %d %d %d %d %d\n", c, cost[nodes[j]], i, j, nodes[j], heur(nodes[j]));
            nodes[j+1] = nodes[j];
        }
        nodes[j+1] = v;
    }
} 

// could refactor these
void
update_nodes(vertex n, vertex m) {
    int w;
#if ALGORITHM==PRIM
    w = weight[n][m];
    if (!finalised[m] && w < cost[m]) {
        cost[m] = w;
        f_sort();
        parent[m] = n;
    }
#elif ALGORITHM==DIJK || ALGORITHM==ASTAR
    w = cost[n] + weight[n][m];
    // printf("w %d %d %d %d %d %d\n", n, m, w, cost[n], weight[n][m], cost[m]);
    if (!finalised[m] && w < cost[m]) {
        cost[m] = w;
        f_sort();
        parent[m] = n;
    }
#elif ALGORITHM==BFS
    if (!seen[m]) {
        seen[m] = 1;
        parent[m] = n;
        nodes[++f_end] = m;  // enqueue(Nodes, m)
    }
#elif ALGORITHM==DFS
    if (!finalised[m]) {
        parent[m] = n;
        nodes[--f_start] = m;  // push(Nodes, m)
    }
//#else
#endif
}

// initialise data structures - Fontier just has just start node
// For Prim's algorithm we can use any start node (eg 1) but might be
// good for animation to allow different start nodes to show the same
// tree is computed (if there is a unique MST) and there can be more
// than one minimal MST.
void
init(void) {
    int i;
    // initialise data structures - Fontier just has startnode
    // refactor some of this???
#if ALGORITHM==PRIM || ALGORITHM==DIJK || ALGORITHM==ASTAR
    f_start = 1;
    // nodes with cost infinity are conceptually not in the frontier but
    // it makes coding simpler if we include them in the PQ
    f_end = graphsize;
    for (i=1; i<=f_end; i++) {
        nodes[i] = i;
        cost[i] = infty;
        parent[i] = 0;
        finalised[i] = 0;
    }
    // add/update start node with cost 0
    cost[startnode] = 0;
    // swap startnode to start of nodes array; all other costs are infinity
    // so no sorting is required
    nodes[startnode] = 1;
    nodes[1] = startnode;
#elif ALGORITHM==BFS
    for (i=1; i<=graphsize; i++) {
        parent[i] = 0;
        seen[i] = 0;
    }
    seen[startnode] = 1;
    nodes[1] = startnode;
    f_start = 1;
    f_end = 1;
#elif ALGORITHM==DFS
    for (i=1; i<=graphsize; i++) {
        parent[i] = 0;
        finalised[i] = 0;
    }
    nodes[graphsize] = startnode;
    f_start = graphsize;
    f_end = graphsize;
#endif
}

// some algorithms may stop before exploring the whole graph
int
task_completed(int n) {
// printf("task_completed? %d %d\n", n, end[n]);
#if ALGORITHM==PRIM
    #ifdef oneMST  // return just MST connected to startnode
        return cost[n] == infty;
    #else // return forest for whole graph
        return 0;
    #endif
#elif ALGORITHM==DIJK
    if (cost[n] == infty)
        printf("Search failed:(\n");
    return end[n] || cost[n] == infty;
#elif ALGORITHM==ASTAR // single end node
    if (cost[n] == infty)
        printf("Search failed:(\n");
    return n == endnode || cost[n] == infty;
#else // other search algorithms (BFS, DFS) can have any number of end nodes
    return end[n];
#endif
}


void
alg(void) {
    vertex n, m;
    int w;

    init();

    // by putting all nodes in the PQ and looping until the PQ is empty,
    // we end up building a minimal spanning forest if the graph is not
    // connected, which is fine. If we only included "real" frontier
    // nodes that had been seen in the PQ, we would just build a MST
    // containing the start node.
    while (f_start <= f_end) {
        n = nodes[f_start]; /* Select node i with minimal cost/... */
        f_start++;       /* Remove i from (priority) queue/stack */
#if ALGORITHM==DFS
        while (finalised[n]) {
            if (f_start > f_end) {
                printf("Search failed:(\n");
                return;
            }
            n = nodes[f_start++];
        }
#endif
printf("Finalised %d with parent %d, cost %d heur %d\n", n, parent[n], cost[n], heur(n));
        finalised[n] = 1;   /* Add i to spanning tree */
        // if cost = infinity we have built the MST that includes startnode; we
        // could stop here if we don't want to build MSTs for other
        // connected components of the graph
        if (task_completed(n))
            return;
        for (m=1; m<=graphsize; m++) {  // for each node m ...
            w = weight[n][m];
            if (w > 0) {                // that is a neighbour of n
//                printf("update_nodes(%d, %d)\n", n, m);
                update_nodes(n, m);     // update Nodes & Parent with n & m
            }
        }
    }
}

int
main() {
    int i, j, w;
    // read number of nodes
    scanf("%d",&graphsize);
    // read x-y coordinates of nodes
    for (i=1; i<=graphsize; i++)
        scanf("%d %d", &xpos[i], &ypos[i]);
    // read edge matrix (replace non-zero weights by computed ones)
    // XXX might be better to have edge list
    for (i=1; i<=graphsize; i++)
        for (j=1; j<=graphsize; j++) {
            scanf("%d", &w);
            if (w != 0) {
                weight[i][j] = w;
                weight[j][i] =                  // make matrix symmetric
                weight[i][j] = weight_fn(i, j); // recompute weight
            }
        }
    // read start node
    scanf("%d",&startnode);
    for (i=1; i<=graphsize; i++)
        end[i] = 0;
    // read end node(s), terminated with 0
    // For A* we want a single end node (we use the last one given)
    scanf("%d",&i);
    while (i != 0) {
        end[i] = 1; // ignored in Prim's, A*
        endnode = i; // used for A* only
        scanf("%d",&i);
    }
    // anything after the last zero in the file is ignored; we can add
    // comments to test data files here (XXX might be nicer to ignore
    // everything up to and including the first blank line instead so
    // comments can be at the start)

    printf("Weighted graph:\n");
    for (i=1; i<=graphsize; i++) {
        for (j=1; j<=graphsize; j++)
            printf("%3d ", weight[i][j]);
        printf("\n");
    }

    alg();
    // printf("MST:\n");
    printf("Result:\n");
    for (i=1; i<=graphsize; i++) {
        for (j=1; j<=graphsize; j++)
            if (i == parent[j] || j == parent[i])
                printf("%3d ", weight[i][j]);
            else
                printf("  0 ");
        printf("\n");
    }

    return 0;
}
 
/* Example of test input with 5 vertices (must be less than MAXSIZE):

5
1 1
1 5
6 5
2 5
3 3
0  2  6  0  0
2  0  6  5  7
6  6  0  1  4
0  5  1  0  3
0  7  4  3  0
1
4
0


This yields the following output:

Spanning tree:
0  2  0  0  0
2  0  0  5  0
0  0  0  1  0
0  5  1  0  3
0  0  0  3  0

*/
