// Hashing implementation, based on BST code - might be a bit of
// leftover rubbish from that

// support different versions with -DALGM=XXX
#define LINEARPROBE 1
#define DOUBLEHASH 2

#ifndef ALGM
    #define ALGM LINEARPROBE // default is LINEARPROBE
#endif

#if !(ALGM == LINEARPROBE || ALGM == DOUBLEHASH)
ALG flag should be 1..2 // compile error
#endif

#include<stdio.h>
#include<stdlib.h>

#define NEW(type) (type *) malloc(sizeof(type))
#define demand(fact, remark)\
    {   if (!(fact))\
        {   fprintf(stderr, "%s\n", remark); exit(1);   }\
    }

#define BIGPRIME 3457 // for hash function
#define MEDIUMPRIME 97 // for table size
#define BIGPRIME2 1429 // for secondary hash function
#define SMALLISHPRIME 23 // for secondary hash function

#define TableSize MEDIUMPRIME // fixed size

// hash table T, status flag for to tell if slot is Empty
// (see #defines below) and number of Insertions
int T[TableSize], status[TableSize], Insertions;

#define Empty 0
#define Full 1
#define Deleted 2 // currently unsed but useful for future

int printprobes=0; // debugging output for search

int
HashInsert(int T[], int k) {
    int i, Increment;

    if (Insertions > TableSize-2)
        return 0;
    Insertions++;
    // XXX k better be positive! C % is not 'modulo'
    i = (k * BIGPRIME) % TableSize;
#if ALGM == LINEARPROBE
    Increment = 1;
#else
    Increment = (k * BIGPRIME2) % SMALLISHPRIME + 1;
#endif
    while (status[i] != Empty) {
        i = (i + Increment) % TableSize;
    }
    T[i] = k;
    status[i] = Full;
    return 1;
}

#define NOTFOUND -1 // indicates not found; otherwise index returned
int
HashSearch(int T[], int k) {
    int i, Increment;

    i = (k * BIGPRIME) % TableSize;
#if ALGM == LINEARPROBE
    Increment = 1;
#else
    Increment = (k * BIGPRIME2) % SMALLISHPRIME + 1;
#endif
    if (printprobes) printf("Increment %2d; hash(%d) = %d... ", Increment, k, i);
    while (!(status[i] == Empty || T[i] == k)) {
        i = (i + Increment) % TableSize;
        if (printprobes) printf("%d ", i);
    }
    if (printprobes) printf("\n");
    if (T[i] == k)
        return i;
    else
        return NOTFOUND;
}
void
HashPrint() {
    int i;
    for (i = 0; i < TableSize; i++) {
        if (i % 20 == 0) // newline before each 20 elements
            printf("\n %3d", i);
        printf("%4d", T[i]);
    }
    printf("\n");
}


int main() {
    int i, n, x;

    // init empty table
    Insertions = 0;
    for (i = 0; i < TableSize; i++) {
        status[i] = Empty;
        T[i] = 0;  // not really needed but we cheat with printing T
    }

    // we read the initial load factor and fill the table with
    // random positive numbers less than 1000 - makes printing easier
    // and zero means slot is empty.
    // XXX Could call srandom if SEED is defined
    scanf("%d", &n);
    demand(n>0 && n < 100, "Initial load factor must be 0-99");
    n = n * TableSize / 100;
    for (i = 0; i < n; ) {
        x = random() % 999 + 1;
        if (HashSearch(T, x) == NOTFOUND) { // avoid duplicates
                HashInsert(T, x);
                i++;
        }
    }
    // HashPrint(); // print hash table

    // insert elements from user
    scanf("%d", &n);
    demand(n>=0, "Number of elements to insert must be >=0");
    for (i=0; i<n; i++) {
        scanf("%d", &x);
        demand(x>=0, "Number to insert must be >=0");
        if (!HashInsert(T, x))
            printf("Insert failed!\n");
    }
    HashPrint(); // print hash table
    
    printprobes = 1; // turn on debug output
    // repeatedly search for numbers until we read 0
    scanf("%d", &x);
    while (x > 0) {
        if ( (n = HashSearch(T, x)) != NOTFOUND)
            printf("Found  %d\n", n);
        else
            printf("Not found\n");
        scanf("%d", &x);
    } 

    return 0;
}
 
/* Example of test input


This yields the following output:

*/
