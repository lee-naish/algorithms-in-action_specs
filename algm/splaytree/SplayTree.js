import parse from '../../pseudocode/parse';

export default parse(`
    
\\Note{  REAL specification of Splay tree insertion and search
 Early version - updated version in proper AIA repository
\\Note}

\\Note{ Animation should be as consistent
as possible with BST/AVL trees
\\Note}

\\Code{
Main
ST_Insert(t, k) // insert key k into tree t; return result
\\In{
  splay(t, k) // move node k to root (if it exists)
  if t.key = k
  \\In{
    return t
  \\In}
  \\In{
    return NotFound
  \\In}
\\Code}

\\Code{
ST_Search
ST_Search(t, k) // return subtree of t with k at root or NotFound 
\\In{
  splay(t, k) // move node k to root (if it exists)
  if t.key = k
  \\In{
    return t
  \\In}
  \\In{
    return NotFound
  \\In}
\\Code}

\\Code{
SPLAY
splay(t, k) // move node with key k to root of tree t \\B Splay
\\Expl{ If key k doesn't exist in t, the next larger key is
  moved to the root. If there are no larger keys the next smaller key is
  moved to the root. If t is Empty, nothing is done.
\\Expl}
  \\In{
    switch startOfPathTo(k) of \\B switchPath
    \\Expl{ We determine the start of the path to key k in the binary
      search tree t
      (going left, or right at each node). We want the first two nodes of the
      path (if there are at least two nodes), otherwise one node (if there is
      at least one node), otherwise we do nothing.
    \\Expl}
    case Left-Left:// Left-Left path \\B left-left
    \\Expl{
      Key k is in the left subtree of the left subtree (if k exists).
    \\Expl}
    \\In{
        Move k to the top of the left-left subtree \\R LL-recurse
        t <- rightRotate(t) // Move node k to the left of the root \\B LL-rot1
        \\Expl{
          This moves the whole left-left subtree (with k at the top, assuming
          k exists in the tree) up so it becomes the (new) left subtree.
        \\Expl}
        return rightRotate(t) // Move node k to root \\B LL-rot2
        \\Expl}
    \\In}
    case Left-Right:// Left-Right path \\B left-right
    \\Expl{
      Key k is in the right subtree of the left subtree (if k exists).
    \\Expl}
    \\In{
        Move k to the top of the left-right subtree \\R LR-recurse
        t.left <- leftRotate(t.left) // Move node k to the left of the root \\B LR-rot1
        \\Expl{
          This moves the whole left-right node (containing k, assuming
          k exists in the tree) up so it becomes the (new) left subtree.
        \\Expl}
        return rightRotate(t) // Move node k to root \\B LR-rot2
    \\In}
    case Right-Right:// Right-Right path \\B right-right
    \\Expl{
      Key k is in the right subtree of the right subtree (if k exists).
    \\Expl}
    \\In{
        Move k to the top of the right-right subtree \\R LL-recurse
        t <- leftRotate(t) // Move node k to the right of the root \\B LL-rot1
        \\Expl{
          This moves the whole right-right subtree (with k at the top, assuming
          k exists in the tree) up so it becomes the (new) right subtree.
        \\Expl}
        return leftRotate(t) // Move node k to root \\B LL-rot2
        \\Expl}
    \\In}
    case Right-Left:// Right-Left path \\B right-left
    \\Expl{
      Key k is in the left subtree of the right subtree (if k exists).
    \\Expl}
    \\In{
        Move k to the top of the right-left subtree \\R LR-recurse
        t.right <- rightRotate(t.right) // Move node k to the right of the root \\B LR-rot1
        \\Expl{
          This moves the whole right-left node (containing k, assuming
          k exists in the tree) up so it becomes the (new) right subtree.
        \\Expl}
        return leftRotate(t) // Move node k to root \\B LR-rot2
    \\In}
    case Left-Empty:// Left (and no further) \\B left-empty
    \\Expl{
      Key k is at the top of the left subtree or the subtree in which
      it would occur (left-left or left-right) is Empty.
    \\Expl}
    \\In{
        return rightRotate(t) // Move node k to root \\B LE-rot1
    \\In}
    case Right-Empty:// Right (and no further) \\B right-empty
    \\Expl{
      Key k is at the top of the right subtree or the subtree in which
      it would occur (right-left or right-right) is Empty.
    \\Expl}
    \\In{
        return leftRotate(t) // Move node k to root \\B RE-rot1
    \\In}
    case Empty: // t is Empty or k is at root already \\B case-empty
    \\In{
        return t // nothing to do \\B E-return
    \\In}
  \\In}
  // Done \\B DoneSplay

// ==== rotation functions ====
leftRotate(t2) // raises Right-Right + lowers Left-Left subtrees \\B leftRotate(t2)
\\Expl{
The edge between t2 and its right child is "rotated" to the left
(counter-clockwise), and the right child becomes the new root.
See Background (click at the top of the right panel)
for diagrams etc explaining rotations.
\\Expl}
  \\In{
    t6 <- t2.right \\B t6 = right(t2)
    t4 <- t6.left // may be Empty \\B t4 = left(t6)
    t6.left <- t2 \\B t6.left = t2
    t2.right <- t4 // may be Empty \\B t2.right = t4
    return (pointer to) t6 // new root \\B return t6
  \\In} 
rightRotate(t6) // inverse of leftRotate \\B rightRotate(t6)
\\Expl{
The edge between t6 and its left child is "rotated" to the right
(clockwise), and the left child becomes the new root.
See Background (click at the top of the right panel)
for diagrams etc explaining rotations.
\\Expl}
  \\In{
    t2 <- t6.left \\B t2 = left(t6)
    t4 <- t2.right // may be Empty \\B t4 = right(t2)
    t2.right <- t6 \\B t2.right = t6
    t6.left <- t4 // may be Empty \\B t6.left = t4
    return (pointer to) t2 // new root \\B return t2
  \\In} 
\\Code}

\\Note{
Animation stops at comments before recursion so user can prepare mentally for
recursive call plus we need a chunk at this level of recursion just
before the call so we can step back to it
\\Note}

\\Code{
LL-recurse
// *recursively* call splay with the left-left subtree \\B pre-recurseLL
t.left.left <- splay(t.left.left, k) \\B recurse-LL
\\Expl{
The (possibly empty) left-left subtree is replaced by the result of this recursive call.
\\Expl}
\\Code}

\\Code{
LR-recurse
// *recursively* call splay with the left-right subtree \\B pre-recurseLR
t.left.right <- splay(t.left.right, k) \\B recurseLR
\\Expl{
The (possibly empty) left-right subtree is replaced by the result of this recursive call.
\\Expl}
\\Code}

\\Code{
RL-recurse
// *recursively* call splay with the right-left subtree \\B pre-recurseRL
t.right.left <- splay(t.right.left, k) \\B recurse-RL
\\Expl{
The (possibly empty) right-left subtree is replaced by the result of this recursive call.
\\Expl}
\\Code}

\\Code{
RR-recurse
// *recursively* call splay with the right-right subtree \\B pre-recurseRR
t.right.right <- splay(t.right.right, k) \\B recurseRR
\\Expl{
The (possibly empty) right-right subtree is replaced by the result of this recursive call.
\\Expl}
\\Code}



`);
