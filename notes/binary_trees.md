### Binary Tree
• Pointer-based data structures (like Linked List) can achieve worst-case performance
• Binary tree is pointer-based data structure with three pointers per node
• Node representation: node.{item, parent, left, right}

           _____<A>____
       ___<B>___      <C>
  ___<D>       <E>  
<F>

### Terminology
• The root of a tree has no parent (Ex: <A>)
• A leaf of a tree has no children (Ex: <C>, <E>, and <F>)
• Define depth(<X>) of node <X> in a tree rooted at <R> to be length of path from <X> to <R>
• Define height(<X>) of node <X> to be max depth of any node in the subtree rooted at <X>
• Idea: Design operations to run in O(h) time for root height h, and maintain h = O(log n)
• A binary tree has an inherent order: its traversal order
    – every node in node <X>’s left subtree is before <X>
    – every node in node <X>’s right subtree is after <X>
• List nodes in traversal order via a recursive algorithm starting at root:
    – Recursively list left subtree, list self, then recursively list right subtree
    – Runs in O(n) time, since O(1) work is done to list each node
    – Example: Traversal order is (<F>, <D>, <B>, <E>, <A>, <C>)
• Right now, traversal order has no meaning relative to the stored items
• Later, assign semantic meaning to traversal order to implement Sequence/Set interfaces

### Tree Navigation
• Find first node in the traversal order of node <X>’s subtree (last is symmetric)
    – If <X> has left child, recursively return the first node in the left subtree
    – Otherwise, <X> is the first node, so return it
    – Running time is O(h) where h is the height of the tree
    – Example: first node in <A>’s subtree is <F>

• Find successor of node <X> in the traversal order (predecessor is symmetric)
    – If <X> has right child, return first of right subtree
    – Otherwise, return lowest ancestor of <X> for which <X> is in its left subtree
    – Running time is O(h) where h is the height of the tree
    – Example: Successor of: <B> is <E>, <E> is <A>, and <C> is None


### Dynamic Operations
• Change single item in the tree
• Insert node <Y> after node <X> in the traversal order
• Delete the item in node <X> from <X>'s subtree
    – If <X> is a leaf, detach from parent and return
    – Otherwise, <X> has a child
        ∗ If <X> has a left child, swap items with the predecessor of <X> and recurse
        ∗ Otherwise <X> has a right child, swap items with the successor of <X> and recurse
    – Running time is O(h) where h is the height of the tree


### Application Set


### Application Sequence
 Idea! Sequence Binary Tree: Traversal order is sequence order
• How do we find i
th node in traversal order of a subtree? Call this operation subtree at(i)
• Could just iterate through entire traversal order, but that’s bad, O(n)
• However, if we could compute a subtree’s size in O(1), then can solve in O(h) time
    – How? Check the size nL of the left subtree and compare to i
    – If i < nL, recurse on the left subtree
    – If i > nL, recurse on the right subtree with i'= i − nL − 1
    – Otherwise, i = nL, and you’ve reached the desired node!
• Maintain the size of each node’s subtree at the node via augmentation
    – Add node.size field to each node
    – When adding new leaf, add +1 to a.size for all ancestors a in O(h) time
    – When deleting a leaf, add −1 to a.size for all ancestors a in O(h) time
• Sequence operations follow directly from a fast subtree at(i) operation 



