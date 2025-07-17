# Status AIA

## Current ToDo List

(see also ../doc/Lee_TODO.txt)
30 April 2025:  Wiki out-of-date 

...       

## Showcase Ready (reviewed)


+Heapsort

+Mergesort (Top-down and bottom-up)

+Quicksort


     
	+ Graph Algorithms (not all reviewed yet as at 13 July 2025)




**TopDown Mergesort** mostly good. Animation and explanation reviewed by Linda 6 July.  Noted: index disappears when off the rhs of the array (see details in Mergesort.txt status file).  As at 9 July, we decided that perhaps students who are working on insertion sort etc. might start with putting in a graphical stack representation in mergesort.  Lee is simplifying the quicksort stack, and suggest we use this as the basis for all the stacks.
Lee: stack was just a suggestion. Hmm, I might have a go at it though
Lee: fixed the index problem and the stack

**BottomUp Mergesort** good.  Animation and explanation reviewed by Linda 9 July.  One slight glitch in the animation is noted in the status file MergesortBU.txt.

(I am omitting Natural Mergesort from the Showcase Ready list, reviewed 13 July 2025, see individual file for reasons.)

**Heapsort** good. Reviewed by Linda 13 July 2025.    
Animation excellent. 
Background - a problem with Vercel noted to Lee.  Otherwise, 
it's fine.
Lee: problem went away(?)

**Quicksort** All good.  Reviewed by Linda 13 July.  Lee is planning to make the stack less multi-colored, which would be an improvement and good prototype for other algorithm stack representations, but it's OK to use as is.
Lee: stack done

**DFS Recursive**  All good.  Optional suggestion for highlighting in DFS_Recursive.txt.There is a typo in the pseudocode, either line 9 (fully expanded) uses == for equality, line 17 uses =. 
Lee: fixed = verses == versus <- in a bunch of files


**DFS iterative**   All good.  
See suggested highlighting in DFS_Iterative.txt. Would this necessitate similar highlighting in BFS for consistency -- in which case maybe just leave it alone.  BFS is clear without highlighting.

**BFS** All good. Consistency with DFS is good.
Background: Pedagogy might be improved by a few words contrasting BFS with DFS, see BFS.txt.
Animation:  Good.   


**Dijkstra's Shortest Path**  Good to go.
Background good. 
Animation: as in DFS iterative, I think there would be pedagogical mileage in highlighting the n node in the graph view after it's been removed from the PQ and while its neighbors are being examined.  Maybe a red or other color rim around the node.   

**Prim's MST**
There is an error in the Background -- see PrimMST.txt
Animation: Picks Node 1 as default Min at the beginning -- see comment in PrimMST.txt.





**Graph Algorithms** -- probably all or mostly good, still to be reviewed:


	A* Heuristic Search
	Prim's MST
	Kruskal MST
	Warshall Transitivte Closure


	










## Showcase Ready Soon

Module/ Still to be done/ Who is doing /date





## To be proposed for student projects in 2025

_Summary_ of Lee's file Github:
algorithms-in-action\_specs/projects/projs\_2025

See that file for details. 

#### BST/AVL

     + Recursive BST (same as AVL minus last two lines of code)
 
    + Improve iterative BST, maximise consistency with recursive

     + Polish AVL tree -- n.b. Lee has done much of this already, we should be specific, and Lee-TODO file has bugs to fix and ideas 

     + Consistency between BST-AVL (iterative and recursive) 


#### "UI" and Improve internal design

     + Lee to drive this -- several ideas in the projs\_2025 file, including

     + colors -- consistency
 
     + main menu

     + ?update Wiki -- students or us, depending on the topic


#### Other algorithms



           + Insertion sort pseudocode draft has been done

           + Selection sort -- students to write pseudoode, we check it before they progress to animation

     + Demonstrate recursion -- ? part of the BST/AVL group

     + ?Quicksort to be more like Radix Exchange sort in display
     

----------------------------------
#### Linked lists (again!)

    + aim for nice animation of list mergesort but try to make it general enough to be easily used/adapted for other algorithms

    + Lee has several ideas, see projs\_2025 file
    

#### Now we really need to decide on a possible fifth project if we need it.

      + Lee to decide on minimax a/o alpha-beta.  Linda not too familiar with these.  See detailed thoughts in Lee's file projs_\2025

       + Splay trees?

       + Skip lists?

       + Do more with the string searching algorithms?

       + More user interface issues -- but possibly risky to have two groups working in this area, risky enough with one!

Lee: added convex hull
