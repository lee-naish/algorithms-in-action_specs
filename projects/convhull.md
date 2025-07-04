## Convex Hull

Currently AIA has no geometric algorithm animations. This project will
add an animation of a two dimensional convex hull algorithm animation (or
more if time permits), which is particularly amenable to visualisation:
the "Jarvis March" or "gift wrapping" algorithm.  Given a set of points
in two dimensions, the convex hull is the smallest convex polygon that
contains all points. If you think of each point being a nail sticking
out of a board, the algorithm is analogous to tying a string to the
leftmost nail, pulling the string tight and wrapping it around the
collection of nails until it touches reaches the leftmost nail again.
In three dimensions it is like wrapping paper around the points, hence
"gift wrapping".  There are optimisations to this algorithm and several
other more efficient convex hull algorithms that could be tackled.

### Visualisation in AIA

We anticipate the existing AIA modules for visualising graphs will be
sufficient for animating conxex hull algorithms with little or no
modifications. The points can be depicted by graph nodes and the string
can be depicted by graph edges. We may want to adjust the size of nodes
and write new code to generate random inputs to the algorithm.  Also,
AIA animations currently do not do "tweening" for graph edges (smooth
movement between two different edge positions). If this could be
implemented it would be beneficial and could also be retro-fitted to
other algorithms.

