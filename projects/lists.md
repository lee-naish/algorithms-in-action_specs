## Linked lists

Currently AIA has algorithm animations that visualise arrays, various
forms of trees and graphs but none that visualise linked lists. This
project will add linked list visualisation to AIA, initially using a
version of merge sort. There should also be consideration of how the
code could be used or adapted to other linked list algorithms (some of
which may also be completed in this project).

### Prototype merge sort for lists

AIA has a prototype of merge sort for lists implemented (it doesn't
appear in the menus but can be found from the main page via the search
function). The pseudocode is written so it is independent of the way lists
are represented, and should not be changed in this project.  Some steps of
the execution are not animated and these need to be filled in.  However,
the main job is to change the way lists are visualised.  In the prototype,
lists are represented using two arrays: one for the data (the head of each
list) and another for the "next pointers" (the tail of each list). Thus
**head[i]** together with **tail[i]** represent the two components of a
single list cell.  Instead of a pointer to a list cell we use the index
of the arrays that represents the next list cell (so the integer **i**
represents a pointer to the list cell described above). Empty lists are
represented by "Null".

### Preferred visualisation of linked lists

Linked lists are better represented by either some symbol that represents
the empty list or an arrow that points to a box that is divided into
two part (or two boxes that are joined). The first will contain the
list elements and the second will contain the empty list symbol or
an arrow to the next list cell. AIA contains a module that implements
graphs, including various forms of trees, and this has similar visual
elements. Extending it to support lists seems like the best solution.

