## Global Issues

This project addresses several desirable enhancements to AIA that affect multiple
algorithms. Some are related to making future development of the code
easier, for example, adding new algorithms modules.  Others concern the
function of AIA.

### Simplifying addition of new algorithms

This is the first task to tackle. The aim is to get at least a simple
version of this working quickly and committed to the repository to help
the teams that are adding new algorithms. Later it can be refined further
if needed, preferably in a way that does not impact the other teams. There
are two main components to this.  This first is to rationalise the
multiple lists of algorithms that appear in the code. The second is to
complete some simple code that helps with some tedious aspects.

#### Lists of algorithms in the code

Once in AIA there was a single master list of algorithms that had all the
required information.  Sadly, some modifications to the system resulted
in four separate lists, each with slightly different information etc,
and each of which needs to be edited for each new algorithm. The single
list design is what we want; the other lists should be generated from
the master list.

#### Reducing tedium

To add a new algorithm, several new files must be created (eg, for
the animation code, the pseudocode and extra information) and entries
must be added to numerous lists. We have prototype JavaScript code that
inputs the algorithm name and a unique identifier to be used in code and
outputs unix commands to create files, append to files and instructions
about what code to add to other files, allowing lots of copy and paste
rather than tedious typing.  This prototype should be completed.

### Algorithm menus

The main AIA page has a list of algorithms, divided into categories, but
depending on the window size and font size, some may not be visible. This
must be fixed. Also, due to the way the formatting is done, adding new
algorithms can be a nightmare.  Finally, there is a search function
that relies on algorithm names but ideally it should support keywords
associated with each algorithm.

### Colors

The way colors have been implemented in AIA has changed over time to
improve flexibility (eg, color choice) and consistency (eg, between
colors of array elements, graph/tree nodes and edges). Some primitives
have been added for flexible coloring of arrays and similar primitives
should be implemented for graphs. It may be worthwhile retro-fitting
the more flexible primitives to existing animation code and deleting
some legacy code.

A second issue is the choice of different color palettes supported in
AIA. The intention is for AIA to be accessible to those with different
color perception.  Some of the more recent color choices should be
re-visited with this in mind.  Also, there are some uses of color in AIA
that don't vary when different color palettes are selected; ideally this
should not be the case.

### Specialised URLs

AIA uses specialised URLS to allowing links to a particular algorithm with
particular input.  However, not all options etc can be specified with
URLS, similarly for the step of the algorithm execution and expansion
of pseudocode.  It would be desirable to extend the URL mechanism to
specify more information.

