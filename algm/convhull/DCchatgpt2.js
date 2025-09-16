// Point class
class Point {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }
}

// Orientation test: returns positive for left turn, negative for right, 0 for collinear
function orientation(a, b, c) {
    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

// Rightmost point index
function rightmost(points) {
    let idx = 0;
    for (let i = 1; i < points.length; i++) {
        if (points[i].x > points[idx].x ||
           (points[i].x === points[idx].x && points[i].y > points[idx].y)) {
            idx = i;
        }
    }
    return idx;
}

// Leftmost point index
function leftmost(points) {
    let idx = 0;
    for (let i = 1; i < points.length; i++) {
        if (points[i].x < points[idx].x ||
           (points[i].x === points[idx].x && points[i].y < points[idx].y)) {
            idx = i;
        }
    }
    return idx;
}

// Find upper tangent
function findUpperTangent(HL, HR) {
    let i = rightmost(HL);
    let j = leftmost(HR);
    let done = false;

    while (!done) {
        done = true;

        while (orientation(HL[i], HR[j], HR[(j+1) % HR.length]) > 0) {
            j = (j+1) % HR.length;
            done = false;
        }

        while (orientation(HR[j], HL[i], HL[(i-1+HL.length) % HL.length]) < 0) {
            i = (i-1+HL.length) % HL.length;
            done = false;
        }
    }

    return { i, j };
}

// Find lower tangent
function findLowerTangent(HL, HR) {
    let i = rightmost(HL);
    let j = leftmost(HR);
    let done = false;

    while (!done) {
        done = true;

        while (orientation(HL[i], HR[j], HR[(j-1+HR.length) % HR.length]) < 0) {
            j = (j-1+HR.length) % HR.length;
            done = false;
        }

        while (orientation(HR[j], HL[i], HL[(i+1) % HL.length]) > 0) {
            i = (i+1) % HL.length;
            done = false;
        }
    }

    return { i, j };
}

// Merge two hulls HL and HR
function mergeHulls(HL, HR) {
    const upper = findUpperTangent(HL, HR);
    const lower = findLowerTangent(HL, HR);

    const hull = [];

    // HL from upper.i to lower.i (inclusive)
    let idx = upper.i;
    hull.push(HL[idx]);
    while (idx !== lower.i) {
        idx = (idx+1) % HL.length;
        hull.push(HL[idx]);
    }

    // HR from lower.j to upper.j (inclusive)
    idx = lower.j;
    hull.push(HR[idx]);
    while (idx !== upper.j) {
        idx = (idx+1) % HR.length;
        hull.push(HR[idx]);
    }

    return hull;
}

// Base case hull for ≤ 3 points
function baseHull(points) {
    if (points.length <= 1) return points.slice();

    // Remove duplicates
    const unique = [];
    for (const p of points) {
        if (!unique.some(q => q.x === p.x && q.y === p.y)) {
            unique.push(p);
        }
    }
    points = unique;

    // Sort CCW (Graham scan-like)
    if (points.length === 2) return points;

    // For 3 points, return them in CCW order
    const [a, b, c] = points;
    if (orientation(a, b, c) < 0) {
        return [a, c, b]; // swap b and c
    }
    return points;
}

// Main divide-and-conquer convex hull
function convexHull(points) {
    if (points.length <= 3) {
        return baseHull(points);
    }

    // Sort by x, then y
    points.sort((p, q) => p.x !== q.x ? p.x - q.x : p.y - q.y);

    const mid = Math.floor(points.length / 2);
    const left = points.slice(0, mid);
    const right = points.slice(mid);

    const HL = convexHull(left);
    const HR = convexHull(right);

    return mergeHulls(HL, HR);
}

// Example points
const points = [
/*
    new Point(0, 3),
    new Point(1, 1),
    new Point(2, 2),
    new Point(4, 4),
    new Point(0, 0),
    new Point(1, 2),
    new Point(3, 1),
    new Point(3, 3)
*/
    new Point(0, 3),
    new Point(2, 3),
    new Point(2, 2),
    new Point(2, 1),
    new Point(2, 4),
    new Point(2, 0),
    new Point(2, 5),
    new Point(2, 6),
    new Point(3, 3),
];

// Compute convex hull
const hull = convexHull(points);

// Output result
console.log("Convex Hull:");
hull.forEach(p => {
    console.log(`(${p.x}, ${p.y})`);
});

