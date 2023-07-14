// 234-tree implementation and simple testing based on two34tree.real
/*
echo 15 4 6 18 5 13 2 7 17 9 8 19 11 10 15 16    11 5 16 6 2 3 12 22 1 0 | ./a.out

Inorder traversal yields:
  (4.1)2
  (4.2)4
  (4.3)5
 (2.1)6
  (2.1)7
(2.1)8
  (4.1)9
  (4.2)10
  (4.3)11
 (3.1)13
  (4.1)15
  (4.2)16
  (4.3)17
 (3.2)18
  (2.1)19

Found  11
Found  5
Found  16
Found  6
Found  2
Missed 3
Missed 12
Missed 22
Missed 1
*/

#include<stdio.h>
#include<stdlib.h>

typedef int k234;
typedef struct node234 {
    int node_kind; // 2, 3 or 4
    struct node234 *child1;
    k234 key1;
    struct node234 *child2;
    k234 key2;
    struct node234 *child3;
    k234 key3;
    struct node234 *child4;
    } n234, *t234;

#define NEW(type) (type *) malloc(sizeof(type))
#define demand(fact, remark)\
    {   if (!(fact))\
        {   fprintf(stderr, "%s\n", remark); exit(1);   }\
    }

#define SIZE 30      /* Allow for a tree with up to 30 keys */

// list (and other) code from bst.c
typedef struct lnode {
    int elt;
    struct lnode *next;
} ELT;

// change node to particular kind with given fields
// Braces used to avoid potential bugs with use in "else" so
// no ";" needed/wanted.  Temp vars used in case arguments are fields of
// struct being updated (its a macro so call by name, not value)
#define mkThree(c, c1, k1, c2, k2, c3) \
    {t234 c1t=c1, c2t=c2, c3t=c3; k234 k1t=k1, k2t=k2; \
    c->node_kind = 3; c->child1 = c1t; c->key1 = k1t; c->child2 = c2t; \
    c->key2 = k2t; c->child3 = c3t;}
#define mkFour(c, c1, k1, c2, k2, c3, k3, c4) \
    {t234 c1t=c1, c2t=c2, c3t=c3, c4t=c4; k234 k1t=k1, k2t=k2, k3t=k3; \
    c->node_kind = 4; c->child1 = c1t; c->key1 = k1t; c->child2 = c2t; \
    c->key2 = k2t; c->child3 = c3t; c->key3 = k3t; c->child4 = c4t;}

void build_t234(ELT *lst, t234 *tp);
t234 find_child(t234 c, k234 k);
t234 Two(t234 c1, k234 k1, t234 c2);
void t234_insert(t234 *tp, k234 k);
void inorder(t234 t, int indent);

// create new two-node with given contents
t234
Two(t234 c1, k234 k1, t234 c2) {
    t234 c;

    c = NEW(n234);
    c->node_kind = 2;
    c->child1 = c1;
    c->key1 = k1;
    c->child2 = c2;
    return c;
}

// 234-tree insertion.  We pass in pointer to tree so it can be modified
// and return void
void
t234_insert(t234 *tp, k234 k) {
        // p is the parent of c and follows c down the tree to a leaf
    t234 c, p;

    if (*tp == NULL) {  
        c = Two(NULL, k, NULL);
        *tp = c;
    } else {
        // Traverse
        p = NULL;
        c = *tp;
        do {
            if (c->node_kind == 4) {
                // Split
                t234 c1, c2;
                c1 = Two(c->child1, c->key1, c->child2);
                c2 = Two(c->child3, c->key3, c->child4);
                // InsertParent
                if (p == NULL)
                    *tp = Two(c1, c->key2, c2); // add new root to tree
                else if (p->node_kind == 2)
                    if (p->child1 == c)
                        mkThree(p, c1, c->key2, c2, p->key1, p->child2)
                    else
                        mkThree(p, p->child1, p->key1, c1, c->key2, c2)
                else { // p->node_kind == 3
                    if (p->child1 == c)
                        mkFour(p, c1, c->key2, c2, p->key1, p->child2, p->key2, p->child3)
                    else if (p->child2 == c)
                        mkFour(p, p->child1, p->key1, c1, c->key2, c2, p->key2, p->child3)
                    else
                        mkFour(p, p->child1, p->key1, p->child2, p->key2, c1, c->key2, c2)
                }
                if (k < c->key2) {
                    c = c1;
                } else {
                    c = c2;
                }
            }
            p = c;
            c = find_child(c, k);
        } while (c);
        // Insert
        if (p->node_kind == 2)
            if (k < p->key1)
                mkThree(p, NULL, k, NULL, p->key1, NULL)
            else
                mkThree(p, NULL, p->key1, NULL, k, NULL)
        else // p->node_kind == 3
            if (k < p->key1)
                mkFour(p, NULL, k, NULL, p->key1, NULL, p->key2, NULL)
            else if (k < p->key2)
                mkFour(p, NULL, p->key1, NULL, k, NULL, p->key2, NULL)
            else
                mkFour(p, NULL, p->key1, NULL, p->key2, NULL, k, NULL)
    }
}

// return child of node that might contain k
t234
find_child(t234 c, k234 k) {
    if (c->node_kind == 2)
        if (k < c->key1)
            return c->child1;
        else
            return c->child2;
    else if (c->node_kind == 3)
        if (k < c->key1)
            return c->child1;
        else if (k < c->key2)
            return c->child2;
        else
            return c->child3;
    else // c->node_kind == 4
        if (k < c->key1)
            return c->child1;
        else if (k < c->key2)
            return c->child2;
        else if (k < c->key3)
            return c->child3;
        else
            return c->child4;
}

// insert list elements into tree
void
build_t234(ELT *lst, t234 *tp) {
    while (lst) { 
        t234_insert(tp, lst->elt);
        lst = lst->next;
    }
} 

void search_t234(t234 t, k234 k) {
    while (t) {
        if (k == t->key1 || t->node_kind>1 && 
                (k == t->key2 || t->node_kind>2 && k == t->key3)) {
            printf("Found  %d\n", k);
            return;
        }
        t = find_child(t, k);
    }
    printf("Missed %d\n", k);
    return;
}

void inorder(t234 t, int indent) {
    int i;

    if (t) {
        inorder(t->child1, indent+1);
        for (i=0; i<indent; i++) printf(" ");
        printf("(%d.1)", t->node_kind);
        printf("%d\n", t->key1);
        inorder(t->child2, indent+1);
        if (t->node_kind>2) {
            for (i=0; i<indent; i++) printf(" ");
            printf("(%d.2)", t->node_kind);
            printf("%d\n", t->key2);
            inorder(t->child3, indent+1);
            if (t->node_kind>3) {
                for (i=0; i<indent; i++) printf(" ");
                printf("(%d.3)", t->node_kind);
                printf("%d\n", t->key3);
                inorder(t->child4, indent+1);
            }
        }
    }
}

int main() {
    t234 t=NULL;
    int i, n, x;
    ELT *e;
    ELT *first;
    ELT *last;
    scanf("%d", &n);
    demand(n>0, "n must be positive");
    first = NEW(ELT);
    first->next = NULL;
    scanf("%d", &(first->elt));
    last = first;
    
    for (i=1; i<n; i++) {
        e = NEW(ELT);
        e->next = NULL;
        scanf("%d", &(e->elt));
        last->next = e;
        last = e;
    }
    
    build_t234(first, &t);

 /* For testing only : */
    printf("\nInorder traversal yields:\n");
    inorder(t, 0);   
    printf("\n");                         
/*  */
    scanf("%d", &x);
    while (x > 0) {
        search_t234(t, x);
        scanf("%d", &x);
    } 

    return 0;
}
 
/* Example of test input with 15 keys (must be no more than 20):

15
77  13  10  46  94  49  91  88  25  62  54  59  19  44  16
62
63
94
0

This yields the following output:

Found  62
Missed 63
Found  94

*/
