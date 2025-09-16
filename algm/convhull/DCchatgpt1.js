// ---------- Geometry helpers ----------

// Cross product orientation test
// >0 = left turn, <0 = right turn, 0 = collinear
function orientation(a, b, c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// Get index of leftmost point
function leftmostIndex(hull) {
  let idx = 0;
  for (let i = 1; i < hull.length; i++) {
    if (hull[i].x < hull[idx].x ||
       (hull[i].x === hull[idx].x && hull[i].y < hull[idx].y)) {
      idx = i;
    }
  }
  return idx;
}

// Get index of rightmost point
function rightmostIndex(hull) {
  let idx = 0;
  for (let i = 1; i < hull.length; i++) {
    if (hull[i].x > hull[idx].x ||
       (hull[i].x === hull[idx].x && hull[i].y > hull[idx].y)) {
      idx = i;
    }
  }
  return idx;
}

// ---------- Tangent finding ----------

function findUpperTangent(HL, HR) {
  let i = rightmostIndex(HL);
  let j = leftmostIndex(HR);
  let done = false;

  while (!done) {
    done = true;

    // Move j clockwise on HR
    while (orientation(HL[i], HR[j], HR[(j + 1) % HR.length]) > 0) {
      j = (j + 1) % HR.length;
      done = false;
    }

    // Move i counterclockwise on HL
    while (orientation(HR[j], HL[i], HL[(i - 1 + HL.length) % HL.length]) < 0) {
      i = (i - 1 + HL.length) % HL.length;
      done = false;
    }
  }

  return [i, j];
}

function findLowerTangent(HL, HR) {
  let i = rightmostIndex(HL);
  let j = leftmostIndex(HR);
  let done = false;

  while (!done) {
    done = true;

    // Move j counterclockwise on HR
    while (orientation(HL[i], HR[j], HR[(j - 1 + HR.length) % HR.length]) < 0) {
      j = (j - 1 + HR.length) % HR.length;
      done = false;
    }

    // Move i clockwise on HL
    while (orientation(HR[j], HL[i], HL[(i + 1) % HL.length]) > 0) {
      i = (i + 1) % HL.length;
      done = false;
    }
  }

  return [i, j];
}

// ---------- Convex hull core ----------

function convexHull(points) {
  if (points.length <= 3) {
    // Base case: sort counterclockwise
    return points.slice().sort((a, b) => a.x - b.x || a.y - b.y);
  }

  // Sort by x-coordinate
  points.sort((a, b) => a.x - b.x || a.y - b.y);
  const mid = Math.floor(points.length / 2);
  const leftHull = convexHull(points.slice(0, mid));
  const rightHull = convexHull(points.slice(mid));

  return mergeHulls(leftHull, rightHull);
}

function mergeHulls(HL, HR) {
  // Find upper and lower tangents
  const [ui, uj] = findUpperTangent(HL, HR);
  const [li, lj] = findLowerTangent(HL, HR);

  // Collect hull points from HL between li -> ui
  let hull = [];
  let i = ui;
  hull.push(HL[i]);
  while (i !== li) {
    i = (i + 1) % HL.length;
    hull.push(HL[i]);
  }

  // Collect hull points from HR between lj -> uj
  let j = lj;
  hull.push(HR[j]);
  while (j !== uj) {
    j = (j + 1) % HR.length;
    hull.push(HR[j]);
  }

  return hull;
}

// ---------- Test data ----------

const points = [
/*
  {x: 0, y: 0},
  {x: 1, y: 2},
  {x: 2, y: 1},
  {x: 2, y: 4},
  {x: 3, y: 3},
  {x: 4, y: 0},
  {x: 5, y: 2},
  {x: 3, y: -1},
  {x: 1, y: -2}
*/
    {x: 0, y:  3},
    {x: 2, y:  3},
    {x: 2, y:  2},
    {x: 2, y:  1},
    {x: 2, y:  4},
    {x: 2, y:  0},
    {x: 2, y:  5},
    {x: 2, y:  6},
    {x: 3, y:  3},
];


const hull = convexHull(points);
console.log("Convex Hull:");
console.log(hull);
