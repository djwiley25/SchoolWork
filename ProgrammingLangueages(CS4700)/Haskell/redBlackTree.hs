-- DJ Wiley
-- A01099945
-- Haskell Red and Black Tree

-- For this assignment I used both class notes and the following website as a reference
-- https://functional.works-hub.com/blog/Persistent-Red-Black-Trees-in-Haskell

-- 1. No element in the left sub-tree is greater than the root element. (binary search tree)
-- 2. No element in the right sub-tree is less than the root element. (binary search tree)
-- 3. The root node is black
-- 4. Red nodes have black parents
-- 5. There are the same number of black nodes on every path through the tree

-- Also write:
-- Display - pretty print the tree
-- Height - find the longest path

data Color = Red | Black deriving (Show)
data Tree x = Empty | Node Color (Tree x) x (Tree x) deriving (Show)

insert Empty val = Node Red Empty val Empty
insert (Node center left val right) x
    | x == val = Node center left val right
    | x < val = balance(Node center (insert left x) val right)
    | x > val = balance(Node center left val (insert right x))

makeBlack (Node Red left val right) = Node Black left val right
makeBlack x = x

treeInsert tree val = makeBlack (insert tree val)

balance :: Color -> Tree a -> a -> Tree a -> Tree a
balance (Node Black (Node Red a x (Node Red b y c)) z d) = Node Red (Node Black a x b) y (Node Black c z d)
balance (Node Black (Node Red (Node Red a x b) y c) z d) = Node Red (Node Black a x b) y (Node Black c z d)
balance (Node Black a x (Node Red (Node Red b y c) z d)) = Node Red (Node Black a x b) y (Node Black c z d)
balance (Node Black a x (Node Red b y (Node Red c z d))) = Node Red (Node Black a x b) y (Node Black c z d)
balance t = t

display :: Tree Color -> String
display x = case x of
    Node c a num b -> show num ++ "\n" ++ display a ++ "\n" ++ display b
    Empty -> "Empty"


