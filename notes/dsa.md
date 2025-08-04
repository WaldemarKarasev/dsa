### Array Sequence
[0, 1, 2, 3, 4, 5, ..., n-1]

### Linked List Sequence
- Each item stored in the node which containes a pointer to the next node in sequence
- Each node has two fields: node.item, node.next
- Maintanin pointers to the first node
- With maintaining pointers to the last node it is possible to inserting/deleting from the back efficiently

|---head--|         |---node--|
| next    | ------> | next    | -----> nullptr
| item    |         | item    |
|---------|         |---------|

### Dynamic Array Sequence
- Make an array efficient for **last** dynamic opetations
- Insert operation takes O(1) time "on average"