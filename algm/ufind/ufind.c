// Union Find: simple implementation for testing animation specification
// Sample test:
/*
% cat << END > test1
f 2
u 2 3
f 2
u 1 3
p
u 5 4
u 3 4
f 2
p
u 1 0
p
END
% ./a.out < test1
Found 2 from 2
Merged 2 and 3
Found 3 from 2
Merged 1 and 3
n           0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
parent[n]   0  3  3  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
rank[n]     0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
Merged 5 and 4
Merged 3 and 4
Found 4 from 2
n           0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
parent[n]   0  3  4  4  4  4  6  7  8  9 10 11 12 13 14 15 16 17 18 19
rank[n]     0  0  0  1  2  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
Merged 1 and 0
n           0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
parent[n]   4  4  4  4  4  4  6  7  8  9 10 11 12 13 14 15 16 17 18 19
rank[n]     0  0  0  1  2  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0

*/
#include<stdio.h>
#include<stdlib.h>

#define demand(fact, remark)\
    {   if (!(fact))\
        {   fprintf(stderr, "%s\n", remark); exit(1);   }\
    }

#define SIZE 20    // (max) size of set we are partitioning
int parent[SIZE];  // parent for each node
int rank[SIZE];    // rank for each node
#ifdef NOCOMPRESS       
int compresspaths = 0;
#else
int compresspaths = 1;
#endif

// add operation; here we add all the elements in the array
// at the start, don't keep track whats in the set and don't
// expand the array
// Might be better to store max, and have int add(void)
void
add(int n) {
    demand(n < SIZE, "too big!");
    parent[n] = n;
    rank[n] = 0;
}

// find operation
int
find(int n) {
    while (parent[n] != n){
        // we want to compress paths in some way, eg path halving as
        // done here but might want the option of avoiding it so
        // students can see what happens without it
        if (compresspaths)
                parent[n] = parent[parent[n]];
        n = parent[n];
    }
    return n;
}

// union operation, called merge since union is a C keyword
void
merge(int n, int m) {
    n = find(n);
    m = find(m);
    if (n == m) // in same set - nothing to do
        return;
    if (rank[n] > rank[m]) { // if n a larger tree, swap n and m
        int tmp = m;
        m = n;
        n = tmp;
    }
    parent[n] = m; // make smaller tree (n) a subtree of larger (m)
    if (rank[n] == rank[m]) // adjust size (rank) of new root
        rank[m]++;
    return;
}

int
main() {
    int c, n1, n2;
    for (n1 = 0; n1 < SIZE; n1++)
        add(n1);
    // we have find, union + print commands
    // could have add + toggle path compression
    while ((c = getchar()) != EOF) {
        if (c == 'f') {    // find element; print root
            scanf("%d", &n1);
            demand(n1 < SIZE, "too big!");
            n2 = find(n1);
            printf("Found %d from %d\n", n2, n1);
        } else if (c == 'u') { // union/merge two sets
            scanf("%d %d", &n1, &n2);
            demand(n1 < SIZE, "too big!");
            demand(n2 < SIZE, "too big!");
            merge(n1, n2);
            printf("Merged %d and %d\n", n1, n2);
        } else if (c == 'p') { // print current state
            printf("n         ");
            for (n1 = 0; n1 < SIZE; n1++)
                printf("%3d", n1);
            printf("\n");
            printf("parent[n] ");
            for (n1 = 0; n1 < SIZE; n1++)
                printf("%3d", parent[n1]);
            printf("\n");
            printf("rank[n]   ");
            for (n1 = 0; n1 < SIZE; n1++)
                printf("%3d", rank[n1]);
            printf("\n");
        }
    }
    return 0;
}
 
/* Example of test


*/
