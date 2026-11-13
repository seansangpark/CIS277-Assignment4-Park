# CIS-277 Assignment 4: Binary Tree Explorer

## Student

Sean Park

## Design

Initial plan. A node stores `value`, `left`, and `right`. An empty tree is a null root. Each visit appends one value to a vector. Level order uses a queue. `main` links the nodes with `new`. Tree B is linked by hand. `destroyTree` deletes both subtrees, then the node, and sets the caller's pointer to null.

Tree A. Root 50. Leaves 20, 40, 60, and 80. Preorder visits 50, then 30, 20, 40, then 70, 60, 80.

```text
        50
       /  \
     30    70
    / \   / \
   20 40 60 80
```

Prediction: pre 50 30 20 40 70 60 80; in 20 30 40 50 60 70 80; post 20 40 30 60 80 70 50; level 50 30 70 20 40 60 80. Nodes 7, leaves 4, height 3, sum 350.

Tree B. Root 10. Leaves 5 and 15.

```text
        10
       /  \
     30    20
       \     \
        5     15
```

Prediction: pre 10 30 5 20 15; in 30 5 10 20 15; post 5 30 15 20 10; level 10 30 20 5 15. Nodes 5, leaves 2, height 3, sum 80.

## How to Compile

```bash
g++ -std=c++23 -Wall -Wextra -pedantic main.cpp TreeExplorer.cpp -o tree_explorer
g++ -std=c++23 -Wall -Wextra -pedantic -I. tests/student_tests.cpp TreeExplorer.cpp -o student_tests
```

## How to Run

```bash
./tree_explorer
./student_tests
python3 validate.py
```

## Tests and Results

Runs matched. Both roots were null. No corrections. `leaks --atExit` reported 0 leaks. AddressSanitizer reported no errors. `python3 validate.py` passed.

| Case | Expected | Actual |
| --- | --- | --- |
| Empty tree, destroy twice | empty; all 0; root null | matched |
| Singleton -4 | -4; 1 node; 1 leaf; height 1; sum -4 | matched |
| Left chain 3-2-1-0 | in/post 0 1 2 3; height 4; 1 leaf; sum 6 | matched |
| Right chain 0-1-2-3 | post 3 2 1 0; height 4; 1 leaf; sum 6 | matched |
| Mixed: 5, left 0 with -3 and 0, right 5 | 5 nodes; 3 leaves; both 5s and both 0s kept; sum 7 | matched |
| Edited vector, then rebuild -4 | preorder unchanged; null, then -4, then null | matched |
| Extra: 7, 4's left is 2 with right 2, right is 9 | 5 nodes; 2 leaves; height 4; sum 24 | matched |

## Analysis Questions

1. Trace the preorder, inorder, and postorder processing steps for the subtree rooted at 30 in Tree A. Explain why the sequences change while the sum does not.

    Preorder is 30 20 40, inorder is 20 30 40, and postorder is 20 40 30. The visit step moves. The sum stays 90.

2. Explain why Tree B is a binary tree but not a BST, using a specific violated ordering relationship. Why is its inorder sequence not sorted?

    Each node has at most two children. 30 is the left child of 10 and is greater than 10, so inorder records 30 before 10.

3. Give the depth of node 40 in Tree A and distinguish depth in edges from this assignment's height in levels.

    Depth is 2 edges. Height counts levels, so Tree A is 3 and node 40 is on level 3.

4. Explain how the FIFO queue produces level order. Connect this to the queue behavior from earlier work.

    The queue takes the front node and adds its children at the back, so one level finishes before the next. That is the same oldest-first order as the packet queue.

5. For n nodes, height h, and maximum level width w, explain the time and auxiliary space for depth-first traversal, level-order traversal, measurements, and destruction. Discuss the O(n) returned vector separately from the call stack or queue. Compare the height of a balanced tree with a chain. Explain why a normal traversal does not need dynamic-programming tabulation.

    Traversals, counts, height, sum, and destruction are O(n) time and O(h) stack space. Level order's queue is O(w). The returned vector is a separate O(n). A balanced tree is about log n tall, and a chain is n tall. Each node is visited once.

6. Explain why deletion uses postorder and what TreeNode*& changes in the caller. What would go wrong if the parent were deleted before reading its child pointers?

    Children are deleted before the parent. `TreeNode*&` sets the caller's pointer to null. Deleting the parent first would read freed child pointers, and the children would stay allocated.

## AI Use

Cursor was used to help write the tree functions, the demonstration, and the student tests. I checked the result by compiling, running `./tree_explorer`, running `./student_tests`, and running `python3 validate.py`. Each value is appended once, and `destroyTree` clears the caller's pointer.
