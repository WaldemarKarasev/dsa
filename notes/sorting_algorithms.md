|---------------|-----------|------------|------------------------|---------------------------------------------------|
|               | Container |   Static   |        Dynamic         |                   Order                           |
|---------------|-----------|------------|------------------------|-----------------------|---------------------------| 
| dsa           | build(x)  |   find(k)  |  insert(x) delete(k)   | find_min() find_max() | find_prev(k) find_next(k) |
|---------------|-----------|------------|------------------------|-----------------------|---------------------------|
| Array         |    n      |     n      |           n            |          n            |            n              |
| Sorted Array  |  n log n  |   log n    |           n            |          1            |          log n            |


Sort is **in place** if it uses O(1) extra space
Sort is **destructive** if it overwrites initial container

### Permutation Sort O(n!*n)
- There are n! permutations of A, at least one of which is sorted
- For each permutation, check whether sorted in Θ(n)
- Example: [2, 3, 1] → {[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]}

```python
def permutation_sort(A):
’’’Sort A’’’
for B in permutations(A): # O(n!)
    if is_sorted(B): # O(n)
        return B # O(1)
```
- permutation sort analysis:
    - Correct by case analysis: try all possibilities (Brute Force)
    - Running time: **Ω(n! · n)** which is exponential
---


### Selection Sort O(n^2)
- Find a largest number in prefix A[:i + 1] and swap it to A[i]
- Recursively sort prefix A[:i]
- Example: [8, 2, 4, 9, 3], [8, 2, 4, 3, 9], [3, 2, 4, 8, 9], [3, 2, 4, 8, 9], [2, 3, 4, 8, 9]

```python
def selection_sort(A, i = None): # T(i)
    # ’’’Sort A[:i + 1]’’’
    if i is None: i = len(A) - 1 # O(1)
        if i > 0: # O(1)
            j = prefix_max(A, i) # S(i)
            A[i], A[j] = A[j], A[i] # O(1)
            selection_sort(A, i - 1) # T(i - 1)

def prefix_max(A, i): # S(i)
    # ’’’Return index of maximum in A[:i + 1]’’’
    if i > 0: # O(1)
        j = prefix_max(A, i - 1) # S(i - 1)
        if A[i] < A[j]: # O(1)
            return j # O(1)
        return i # O(1)
```
- prefix max analysis:
    - Base case: for i = 0, array has one element, so index of max is i
    - Induction: assume correct for i, maximum is either the maximum of A[:i] or A[i],
    returns correct index in either case. $\square$

    - S(1) = Θ(1), S(n) = S(n − 1) + Θ(1)
    ∗ Substitution: S(n) = Θ(n), cn = Θ(1) + c(n − 1) =⇒ 1 = Θ(1)
    ∗ Recurrence tree: chain of n nodes with Θ(1) work per node, $\sum_{i=0}^{n-1}1 = O(n)$

- selection sort analysis:
    - Base case: for i = 0, array has one element so is sorted
    - Induction: assume correct for i, last number of a sorted output is a largest number of
    the array, and the algorithm puts one there; then A[:i] is sorted by induction $\square$
    
    - T(1) = Θ(1), T(n) = T(n − 1) + Θ(n)
    ∗ Substitution: $T(n) = Θ(n^2), cn^2 = Θ(n) + c(n − 1)^2 =⇒ c(2n − 1) = Θ(n)$
    Pn−1
    ∗ Recurrence tree: chain of n nodes with Θ(i) work per node, $\sum_{i=0}^{n-1}i = Θ(n^2)$

---


### Insertion Sort O(n^2)
- Recursively sort prefix A[:i]
- Sort prefix A[:i + 1] assuming that prefix A[:i] is sorted by repeated swaps
- Example: [8, 2, 4, 9, 3], [2, 8, 4, 9, 3], [2, 4, 8, 9, 3], [2, 4, 8, 9, 3], [2, 3, 4, 8, 9]
```python
def insertion_sort(A, i = None):    # T(i)
    # ’’’Sort A[:i + 1]’’’
    if i is None: i = len(A) - 1    # O(1)
    if i > 0:                       # O(1)
        insertion_sort(A, i - 1)    # T(i - 1)
        insert_last(A, i)           # S(i)

def insert_last(A, i):                      # S(i)
    # ’’’Sort A[:i + 1] assuming sorted A[:i]’’’
    if i > 0 and A[i] < A[i - 1]:           # O(1)
        A[i], A[i - 1] = A[i - 1], A[i]     # O(1)
        insert_last(A, i - 1)               # S(i - 1)
```

- insert last analysis:
    - Base case: for i = 0, array has one element so is sorted
    - Induction: assume correct for i, if A[i] >= A[i - 1], array is sorted; otherwise,
    swapping last two elements allows us to sort A[:i] by induction $\square$
    - $S(1) = Θ(1), S(n) = S(n − 1) + Θ(1) =⇒ S(n) = Θ(n)$
- insertion sort analysis:
    - Base case: for i = 0, array has one element so is sorted
    - Induction: assume correct for i, algorithm sorts A[:i] by induction, and then
    insert last correctly sorts the rest as proved above $\square$
    - $T(1) = Θ(1), T(n) = T(n − 1) + Θ(n) =⇒ T(n) = Θ(n^2)$

    ---

### Merge Sort O(n*log(n))
- Recursively sort first half and second half (may assume power of two)
- Merge sorted halves into one sorted list (two finger algorithm)
- Example: [7, 1, 5, 6, 2, 4, 9, 3], [1, 7, 5, 6, 2, 4, 3, 9], [1, 5, 6, 7, 2, 3, 4, 9], [1, 2, 3, 4, 5, 6, 7, 9]
```python
def merge_sort(A, a = 0, b = None):                     # T(b - a = n)
    # ’’’Sort A[a:b]’’’
    if b is None: b = len(A)                            # O(1)
    if 1 < b - a:                                       # O(1)
        c = (a + b + 1) // 2                            # O(1)
        merge_sort(A, a, c)                             # T(n / 2)
        merge_sort(A, c, b)                             # T(n / 2)
        L, R = A[a:c], A[c:b]                           # O(n)
        merge(L, R, A, len(L), len(R), a, b)            # S(n)

def merge(L, R, A, i, j, a, b):                         # S(b - a = n)
    # ’’’Merge sorted L[:i] and R[:j] into A[a:b]’’’
    if a < b:                                           # O(1)
        if (j <= 0) or (i > 0 and L[i - 1] > R[j - 1]): # O(1)
            A[b - 1] = L[i - 1]                         # O(1)
            i = i - 1                                   # O(1)
        else:                                           # O(1)
            A[b - 1] = R[j - 1]                         # O(1)
            j = j - 1                                   # O(1)
        merge(L, R, A, i, j, a, b - 1)                  # S(n - 1)
```

- merge analysis:
    - Base case: for n = 0, arrays are empty, so vacuously correct
    - Induction: assume correct for n, item in A[r] must be a largest number from remaining
    prefixes of L and R, and since they are sorted, taking largest of last items suffices;
    remainder is merged by induction $\square$
    - $S(0) = Θ(1), S(n) = S(n − 1) + Θ(1) =⇒ S(n) = Θ(n)$

- merge sort analysis:
    - Base case: for n = 1, array has one element so is sorted
    - Induction: assume correct for k < n, algorithm sorts smaller halves by induction, and
    then merge merges into a sorted array as proved above. $\square$
    - $T(1) = Θ(1), T(n) = 2T(n/2) + Θ(n)$
    ∗ Substitution: Guess $T(n) = Θ(n log n)$
    $cn log n = Θ(n) + 2c(n/2)log(n/2) =⇒ cn log(2) = Θ(n)$
    ∗ Recurrence Tree: complete binary tree with depth $log_{2}n$ and n leaves, level $i$ has $2^i$ nodes with $O(n/2^i)$
    work each, total: $\sum_{i=0}^{log_{2}n}(2^i)(\frac{n}{2^i}) = \sum_{i=0}^{log_{2}n} n = O(n*log n)$