// heapsort/quicksort/...
// C code pretty much equivalent to pseudocode version for testing purposes

// pick ONE of the following:
// #define HEAPSORT
#define QUICKSORT // some version of quicksort

#ifdef QUICKSORT
// pick ONE of the following:
// #define QUICKSORT_S // simple version of quicksort
#define QUICKSORT_M3 // median of 3 version of quicksort
#endif // QUICKSORT

#include <stdlib.h>
#include <stdio.h>

#define False 0
#define True 1
#define Swap(a,b) {int tmp; tmp=a; a=b; b=tmp;}

#define Size 10
int A[Size];
// int i1; // for debugging
// for (i1=1; i1 < Size; i1++) printf("%d ", A[i1]); printf("\n");

#ifdef HEAPSORT
int IndexOfLargestChild(int *A, int i, int n);
void heapsort(int A[], int n);
#endif // HEAPSORT

#ifdef QUICKSORT
int partition(int *A, int left, int right);
void quicksort(int A[], int left, int right);
#endif // QUICKSORT


void
main() {
        int i = 1;
        // read A[1]..A[Size-1] from stdin
        while (i < Size)
                scanf("%d", &A[i++]);
#ifdef HEAPSORT
        heapsort(A, Size-1);
#endif // HEAPSORT
#ifdef QUICKSORT
        quicksort(A, 1, Size-1);
#endif // QUICKSORT
        for (i=1; i < Size; i++) printf("%d ", A[i]); printf("\n");
}

#ifdef HEAPSORT
void
heapsort(int A[], int n) { // sort A[1]..A[n]
        int i, j, k, heap;

        // BuildHeap
        for (k = n/2; k>=1; k--) {
                // DownHeap(A,k,n)
                i = k;
                heap = False;
                while (i<=n/2 && !heap) {
                        j = IndexOfLargestChild(A,i,n);
                        if (A[i] >= A[j])
                                heap = True;
                        else {
                                Swap(A[i], A[j])
                                i = j;
                        }
                }
        }
        // SortHeap
        while (n>1) {
                Swap(A[n], A[1])
                n = n-1;
                // DownHeap(A,1,n)
                i = 1;
                heap = False;
                while (i<=n/2 && !heap) {
                        j = IndexOfLargestChild(A,i,n);
                        if (A[i] >= A[j])
                                heap = True;
                        else {
                                Swap(A[i], A[j])
                                i = j;
                        }
                }
        }
}

int
IndexOfLargestChild(int *A, int i, int n) {
        if ((2*i+1 <= n) && (A[2*i+1] > A[2*i]))
                return 2*i+1;
        else
                return 2*i;
}
#endif // HEAPSORT

#ifdef QUICKSORT
// Sort array A[left]..A[right] in ascending order
void
quicksort(int A[], int left, int right) {
        int i;

        if (left < right) {
                i = partition(A, left, right);
printf("after partition %d %d returned %d:", left, right, i);
{int i; for (i=1; i < Size; i++) printf("%d ", A[i]); printf("\n");}
                quicksort(A, left, i-1);
                quicksort(A, i+1, right);
        }
}

int
partition(int A[], int left, int right) {
        int i, j;
        int pivot;

#ifdef QUICKSORT_S
        pivot = A[right]; // choose pivot (simple version)
        i = left-1;
        j = right;
#endif // QUICKSORT_S
#ifdef QUICKSORT_M3
    {int mid = (left+right)/2;
    if (A[left] > A[mid])
        Swap(A[left], A[mid]);
    if (A[mid] > A[right]) {
        Swap(A[right], A[mid]);
        if (A[left] > A[mid])
            Swap(A[left], A[mid]);
    }
    // now A[left] <= A[mid] <= A[right]
    Swap(A[mid], A[right-1]);
        pivot = A[right-1];
        i = left;
        j = right-1;
printf("partition %d %d with mid %d:", left, right, mid);
{int i; for (i=1; i < Size; i++) printf("%d ", A[i]); printf("\n");}
    }
#endif // QUICKSORT_M3
        // invariant:
        // A[left]..A[i] are all <= pivot
        // A[j]..A[right-1] are all >= pivot
        while (i < j) {
                do {
                        i++;
                } while (A[i] < pivot); // note A[right] acts as a sentinel
                do {
                        j--;
                } while (A[j] > pivot && j > i);
                if (j > i) {
                        Swap(A[i], A[j]);
                }
        }
#ifdef QUICKSORT_S
        Swap(A[i], A[right]);
#endif // QUICKSORT_S
#ifdef QUICKSORT_M3
        Swap(A[i], A[right-1]);
#endif // QUICKSORT_M3
        return i;
}
#endif // QUICKSORT
