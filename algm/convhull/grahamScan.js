// Graham scan convex hull algorithm
// XXX may want to remove duplicate points

// Class to represent a point
// XXX may want to change this for consistency with other CH algorithms
class Point {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }

    // Method to check equality of two points
    equals(t) {
        return this.x === t.x && this.y === t.y;
    }
}

// Function to compute orientation of the triplet (a, b, c)
// Returns -1 for clockwise, 1 for counter-clockwise, 0 for collinear
function orientation(a, b, c) {
    const v = a.x * (b.y - c.y) + 
              b.x * (c.y - a.y) + 
              c.x * (a.y - b.y);
    if (v < 0) return -1;  // clockwise
    if (v > 0) return +1;  // counter-clockwise
    return 0;              // collinear
}

// Function to compute squared distance between two points
function distSq(a, b) {
    return (a.x - b.x) * (a.x - b.x) + 
           (a.y - b.y) * (a.y - b.y);
}

// Function to find the convex hull of a set of points
function findConvexHull(points) {
    const n = points.length;

    // Convex hull is not possible if there are fewer than 3 points
    // XXX
    // if (n < 3) return [[-1]];
    if (n < 3) return points;

    // Convert input array to Point objects
    let a = points.map(p => new Point(p[0], p[1]));

    // Find the point with the lowest y-coordinate (and leftmost if tie)
    const p0 = a.reduce((min, p) => 
        (p.y < min.y || (p.y === min.y && p.x < min.x)) ? p : min, a[0]);

    // a = a.filter((p) => (p.x !== p0.x || p.y != p0.y)); // remove p0

    // Sort the points by polar angle with respect to p0
    a.sort((a, b) => {
        const o = orientation(p0, a, b);

        // If collinear, place the farther point later
        // This ensures p0 comes first in the array (we could do that
        // separately) and also avoids possible extra (colinear) points
        // at the end of the array when we have finished computing the
        // hull (this could be done separately also).
        if (o === 0) {
            return distSq(p0, a) - distSq(p0, b);
            // XXX return 0;
        }

        // Otherwise, order based on counter-clockwise direction
        // XXX return o < 0 ? -1 : 1;
        return o < 0 ? 1 : -1;
    });

    // a.unshift(p0); // put p0 back at start

    // Remove duplicate collinear points (keep farthest one)
    // XXX not needed?
/*
    let m = 1;
    for (let i = 1; i < a.length; i++) {

        // Skip closer collinear points
        while (i < a.length - 1 && orientation(p0, a[i], a[i + 1]) === 0) {
            i++;
        }

        // Keep current point in place
        a[m] = a[i];
        m++;
    }
*/
    let m = a.length;

    // If fewer than 3 points remain, hull is not possible
    // XXX not needed? (can return all)
    if (m < 3) return [[-1]];

    // Initialize the convex hull stack with first two points
    const st = [a[0], a[1]];

    // Process the remaining points
    for (let i = 2; i < m; i++) {

        // While the last three points do not make a left turn, pop the middle one
        // XXX while (st.length > 1 && orientation(st[st.length - 2], st[st.length - 1], a[i]) >= 0) {
        while (st.length > 1 && orientation(st[st.length - 2], st[st.length - 1], a[i]) <= 0) {
            console.log('Pop ', st[st.length - 2].x, st[st.length - 2].y, st[st.length - 1].x, st[st.length - 1].y, a[i].x, a[i].y);
            st.pop();
        }

        // Add current point to stack
        st.push(a[i]);
    }

    // Final validation: if fewer than 3 points in stack, hull is not valid
    // XXX not needed? (can return all)
    if (st.length < 3) return [[-1]];

    // Convert hull points to [x, y] arrays
    return st.map(p => [Math.round(p.x), Math.round(p.y)]);
}

// Test case
/*
const points = [
     [0, 0], [1, -4], [-1, -5], [-5, -3], [-3, -1],
    [-1, -3], [-2, -2], [-1, -1], [-2, -1], [-1, 1]
];
*/
// a few cases where there are ties in the sorting - all work without
// removing points 
const points = [
     // [2, 1], [0, 0], [4, 0], [5, 0], [1, 0], [6, 0], [3, 5],
     // [3, 7], [0, 0], [2, 2], [5, 5], [1, 0], [6, 6], [4, 4],
     [3, 7], [0, 0], [0, 2], [5, 5], [0, 2], [0, 1], [0, 3], [0, 6], [0, 4],
    [1, 2], [2, 4]
];

// Compute the convex hull
const hull = findConvexHull(points);

// Output the result
if (hull.length === 1 && hull[0][0] === -1) {
    console.log(-1);
} else {
    hull.forEach(point => {
        console.log(`${point[0]}, ${point[1]}`);
    });
}
