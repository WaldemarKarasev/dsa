### Direct Access Array


---

### Hashing

keys = {0,...,u-1}
n - # of elements in hash table
m - # of cells in keys of hash table

• Idea! If n << u, map keys to a smaller range m = Θ(n) and use smaller direct access array
• Hash function: h(k) : {0, . . . , u − 1} → {0, . . . , m − 1} (also hash map)
• Direct access array called hash table, h(k) called the hash of key k
• If m << u, no hash function is injective by pigeonhole principle 
 Always exists keys a, b such that h(a) = h(b) → Collision! :(
• Can’t store both items at same index, so where to store? Either:
– store somewhere else in the array (open addressing)
∗ complicated analysis, but common and practical
– store in another data structure supporting dynamic set interface (chaining)

---

### Chaining
• Idea! Store collisions in another data structure (a chain)
• If keys roughly evenly distributed over indices, chain size is n/m = n/Ω(n) = O(1)!
• If chain has O(1) size, all operations take O(1) time! Yay!
• If not, many items may map to same location, e.g. h(k) = constant, chain size is Θ(n) :(
• Need good hash function! So what’s a good hash function? 

---

### Hash Functions

#### Division (bad): h(k) = (k mod m)
• Heuristic, good when keys are uniformly distributed!
• m should avoid symmetries of the stored keys
• Large primes far from powers of 2 and 10 can be reasonable
• Python uses a version of this with some additional mixing
• If u >> n, every hash function will have some input set that will a create O(n) size chain
• Idea! Don’t use a fixed hash function! Choose one randomly (but carefully)!


#### Universal (good, theoretically): hab(k) = (((ak + b) mod p) mod m)
• Hash Family H(p, m) = {hab | a, b ∈ {0, . . . , p − 1} and a 6= 0}
• Parameterized by a fixed prime p > u, with a and b chosen from range {0, . . . , p − 1}
• H is a Universal family: Pr {h(ki) = h(kj )} ≤ 1/m ∀ki =6 kj ∈ {0, . . . , u − 1} h∈H
• Why is universality useful? Implies short chain lengths! (in expectation)
• Xij indicator random variable over h ∈ H: Xij = 1 if h(ki) = h(kj ), Xij = 0 otherwise
• Size of chain at index $h(k_i)$ is random variable $X_i = \sum_{j}X_{ij}$
• Since m = Ω(n), load factor α = n/m = O(1), so O(1) in expectation! 


### Dynamic
• If n/m far from 1, rebuild with new randomly chosen hash function for new size m
• Same analysis as dynamic arrays, cost can be amortized over many dynamic operations
• So a hash table can implement dynamic set operations in expected amortized O(1) time! :) 

|----------------------|-----------|------------|------------------------|---------------------------------------------------|
|                      | Container |   Static   |        Dynamic         |                   Order                           |
|----------------------|-----------|------------|------------------------|-----------------------|---------------------------|
| dsa                  | build(x)  |   find(k)  |  insert(x) delete(k)   | find_min() find_max() | find_prev(k) find_next(k) |
|----------------------|-----------|------------|------------------------|-----------------------|---------------------------|
| Array                |    n      |     n      |           n            |          n            |            n              |
| Sorted Array         |  n log n  |   log n    |           n            |          1            |          log n            |
| Direct Access Array  |    u      |     1      |           1            |          u            |            u              |
| Hash Table           |    n(e)   |    1(e)    |        1(e)(a)         |          n            |            n              |
