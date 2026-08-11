# C++

## 1. Basic

- [ ] типы;
- [ ] initialization;
- [ ] conversions;
- [ ] references;
- [ ] pointers;
- [ ] arrays;
- [ ] `const`;
- [ ] functions;
- [ ] overloads;
- [ ] scopes;
- [ ] namespaces;
- [ ] linkage;
- [ ] ODR;
- [ ] value categories;
- [ ] copy semantics;
- [ ] move semantics;
- [ ] special member functions;
- [ ] Rule of Zero;
- [ ] Rule of Five;
- [ ] RAII;
- [ ] exceptions;
- [ ] `noexcept`;
- [ ] inheritance;
- [ ] virtual functions;
- [ ] RTTI;
- [ ] lambdas;
- [ ] STL containers;
- [ ] iterators;
- [ ] algorithms;
- [ ] smart pointers.

---

# 2. C++ object model

- [ ] object lifetime;
- [ ] storage duration;
- [ ] temporary objects;
- [ ] lifetime extension;
- [ ] copy elision;
- [ ] construction/destruction order;
- [ ] manual lifetime management;
- [ ] placement new;
- [ ] `construct_at`;
- [ ] `destroy_at`;
- [ ] `std::launder`;
- [ ] alignment;
- [ ] padding;
- [ ] object representation;
- [ ] trivial types;
- [ ] trivially copyable;
- [ ] standard-layout;
- [ ] aggregates;
- [ ] strict aliasing;
- [ ] pointer provenance;
- [ ] class layout;
- [ ] vtable/vptr;
- [ ] ABI basics;
- [ ] name mangling;
- [ ] ODR;
- [ ] linkage.

---

# 3. Type deduction и overload resolution

- [ ] `auto`;
- [ ] `decltype`;
- [ ] `decltype(auto)`;
- [ ] template argument deduction;
- [ ] reference collapsing;
- [ ] forwarding references;
- [ ] `std::move`;
- [ ] `std::forward`;
- [ ] perfect forwarding;
- [ ] overload resolution;
- [ ] conversion sequences;
- [ ] user-defined conversions;
- [ ] ADL;
- [ ] hidden friends;
- [ ] partial ordering.

---

# 4. Templates

- [ ] function templates;
- [ ] class templates;
- [ ] alias templates;
- [ ] variable templates;
- [ ] variadic templates;
- [ ] parameter packs;
- [ ] fold expressions;
- [ ] full specialization;
- [ ] partial specialization;
- [ ] specialization vs overloading;
- [ ] dependent names;
- [ ] two-phase lookup;
- [ ] instantiation;
- [ ] SFINAE;
- [ ] detection idiom;
- [ ] type traits;
- [ ] tag dispatch;
- [ ] policy-based design;
- [ ] CRTP;
- [ ] mixins;
- [ ] static polymorphism;
- [ ] type erasure.

---

# 5. Concepts и generic programming

- [ ] requires-expressions;
- [ ] concepts;
- [ ] constraints;
- [ ] constraint normalization;
- [ ] subsumption;
- [ ] constrained overloads;
- [ ] generic API design;
- [ ] customization points;
- [ ] policy design.

---

# 6. Exception safety

- [ ] basic guarantee;
- [ ] strong guarantee;
- [ ] no-throw guarantee;
- [ ] copy-and-swap;
- [ ] commit/rollback;
- [ ] conditional `noexcept`;
- [ ] throwing constructors;
- [ ] throwing move;
- [ ] exception safety containers;
- [ ] `std::expected`.

---

# 7. Compile-time C++

- [ ] `constexpr`;
- [ ] `consteval`;
- [ ] `constinit`;
- [ ] `if constexpr`;
- [ ] `if consteval`;
- [ ] constexpr allocation;
- [ ] constexpr containers;
- [ ] template metaprogramming;
- [ ] compile-time programming.

---

# 8. STL-like implementations

- [ ] dynamic array;
- [ ] `small_vector`;
- [ ] intrusive list;
- [ ] `optional`;
- [ ] `expected`;
- [ ] `variant`;
- [ ] `function`;
- [ ] `unique_ptr`;
- [ ] учебный `shared_ptr`;
- [ ] allocator;
- [ ] `allocator_traits`;
- [ ] memory resource;
- [ ] iterator;
- [ ] range/view;
- [ ] coroutine generator.

---

# Standarts

## C++11

- [ ] move semantics;
- [ ] lambdas;
- [ ] variadic templates;
- [ ] smart pointers;
- [ ] `auto`;
- [ ] `decltype`;
- [ ] type traits;
- [ ] concurrency;
- [ ] memory model;
- [ ] `constexpr`.

## C++14

- [ ] generic lambdas;
- [ ] return type deduction;
- [ ] variable templates;
- [ ] relaxed constexpr;
- [ ] `make_unique`.

## C++17

- [ ] structured bindings;
- [ ] `if constexpr`;
- [ ] fold expressions;
- [ ] CTAD;
- [ ] `optional`;
- [ ] `variant`;
- [ ] `string_view`;
- [ ] filesystem;
- [ ] PMR;
- [ ] guaranteed copy elision.

---

## C++20

- [ ] concepts;
- [ ] ranges;
- [ ] views;
- [ ] coroutines;
- [ ] modules;
- [ ] three-way comparison;
- [ ] expanded constexpr;
- [ ] `consteval`;
- [ ] `constinit`;
- [ ] `span`;
- [ ] `format`;
- [ ] `jthread`;
- [ ] `stop_token`;
- [ ] `atomic::wait/notify`;
- [ ] source location.

---

## C++23

- [ ] explicit object parameter;
- [ ] deducing `this`;
- [ ] `expected`;
- [ ] `generator`;
- [ ] `mdspan`;
- [ ] `print`;
- [ ] monadic operations;
- [ ] `if consteval`;
- [ ] ranges improvements;
- [ ] stacktrace;
- [ ] constexpr improvements.

---

## C++26

- [ ] reflection;
- [ ] contracts;
- [ ] execution;
- [ ] sender/receiver;
- [ ] SIMD;
- [ ] hazard pointers;
- [ ] RCU;
- [ ] новые compile-time возможности.

---

# Algorithms

- [ ] `O`;
- [ ] `Ω`;
- [ ] `Θ`;
- [ ] worst case;
- [ ] average case;
- [ ] expected complexity;
- [ ] amortized complexity;
- [ ] aggregate method;
- [ ] accounting method;
- [ ] potential method;
- [ ] recurrence relations;
- [ ] recursion tree;
- [ ] Master theorem;
- [ ] loop invariants;
- [ ] induction;
- [ ] correctness proofs;
- [ ] randomized algorithms;
- [ ] probabilistic analysis;
- [ ] lower bounds.

---

## Basic

- [ ] sorting;
- [ ] binary search;
- [ ] lower_bound / upper_bound;
- [ ] binary search on answer;
- [ ] prefix sums;
- [ ] difference arrays;
- [ ] two pointers;
- [ ] sliding window;
- [ ] divide and conquer;
- [ ] greedy;
- [ ] sweep line;
- [ ] coordinate compression;
- [ ] offline processing;
- [ ] meet-in-the-middle;
- [ ] monotonic stack;
- [ ] monotonic queue;
- [ ] bit manipulation;
- [ ] backtracking.

---

## Sorting

- [ ] insertion sort;
- [ ] selection sort;
- [ ] merge sort;
- [ ] quicksort;
- [ ] randomized quicksort;
- [ ] heap sort;
- [ ] counting sort;
- [ ] radix sort;
- [ ] bucket sort;
- [ ] quickselect;
- [ ] stability;
- [ ] comparison sorting lower bound;
- [ ] introsort idea.

---

## Linked list and sequences

- [ ] dynamic array;
- [ ] singly linked list;
- [ ] doubly linked list;
- [ ] intrusive list;
- [ ] stack;
- [ ] queue;
- [ ] deque;
- [ ] ring buffer;
- [ ] cache locality;
- [ ] iterator invalidation;
- [ ] amortized growth;
- [ ] dynamic array(prac);
- [ ] ring buffer(prac);
- [ ] intrusive list или linked list(prac).

---

## Heap / Priority Queue

- [ ] binary heap;
- [ ] heapify;
- [ ] d-ary heap;
- [ ] indexed priority queue;
- [ ] mutable priority queue;
- [ ] pairing heap;
- [ ] Fibonacci heap;
- [ ] amortized analysis;
- [ ] generic binary heap(prac);
- [ ] indexed priority queue(prac).

---

## Hashing

### Hash functions

- [ ] properties;
- [ ] distribution;
- [ ] avalanche;
- [ ] mixing;
- [ ] integer hashing;
- [ ] string hashing;
- [ ] hash combine;
- [ ] universal hashing;
- [ ] randomized hashing;
- [ ] adversarial input;
- [ ] collision probability.

### Hash tables

- [ ] separate chaining;
- [ ] open addressing;
- [ ] linear probing;
- [ ] quadratic probing;
- [ ] double hashing;
- [ ] clustering;
- [ ] tombstones;
- [ ] load factor;
- [ ] rehashing;
- [ ] Robin Hood hashing;
- [ ] cuckoo hashing;
- [ ] Swiss-table concepts;
- [ ] perfect hashing;
- [ ] heterogeneous lookup.

### Probabilistic

- [ ] Bloom filter;
- [ ] Count-Min Sketch;
- [ ] HyperLogLog.

Practice:

- [ ] chained hash table;
- [ ] linear probing;
- [ ] Robin Hood hash table;
- [ ] Bloom filter;
- [ ] hash quality lab.

## DSU

- [ ] quick union;
- [ ] union by rank;
- [ ] union by size;
- [ ] path compression;
- [ ] amortized complexity;
- [ ] rollback DSU;
- [ ] parity DSU;
- [ ] weighted DSU;
- [ ] offline connectivity;
- [ ] basic DSU;(prac)
- [ ] rollback DSU.(prac)

---

## Trees

### Basic trees

- [ ] binary tree;
- [ ] BST;
- [ ] traversals;
- [ ] successor/predecessor;
- [ ] insertion;
- [ ] deletion;
- [ ] iterators;
- [ ] augmentation;
- [ ] order statistics.

### Balanced

- [ ] AVL;
- [ ] red-black tree;
- [ ] treap;
- [ ] splay tree.

### External memory

- [ ] B-tree;
- [ ] B+ tree.

### Trie

- [ ] trie;
- [ ] radix tree;
- [ ] Patricia trie.

### Range structures

- [ ] Fenwick tree;
- [ ] segment tree;
- [ ] lazy propagation;
- [ ] sparse table;
- [ ] Cartesian tree.

### Persistence

- [ ] persistent BST;
- [ ] persistent segment tree;
- [ ] structural sharing.

Practice:

- [ ] BST;
- [ ] AVL;
- [ ] red-black tree;
- [ ] treap;
- [ ] Fenwick tree;
- [ ] segment tree;
- [ ] trie;
- [ ] invariant checker;
- [ ] Graphviz visualization.

---

## Graphs

### Foundations

- [ ] representations;
- [ ] adjacency list;
- [ ] adjacency matrix;
- [ ] edge list;
- [ ] directed/undirected;
- [ ] weighted;
- [ ] connectivity;
- [ ] DAG;
- [ ] bipartite graphs.

### Traversal

- [ ] BFS;
- [ ] DFS;
- [ ] topological sort;
- [ ] connected components;
- [ ] SCC;
- [ ] bridges;
- [ ] articulation points;
- [ ] Euler path/cycle.

### Shortest paths

- [ ] BFS shortest path;
- [ ] 0-1 BFS;
- [ ] Dijkstra;
- [ ] Bellman-Ford;
- [ ] Floyd-Warshall;
- [ ] DAG shortest paths;
- [ ] A* overview.

### MST

- [ ] Kruskal;
- [ ] Prim;
- [ ] Borůvka;
- [ ] cut property;
- [ ] cycle property.

### Flow / matching

- [ ] Ford-Fulkerson;
- [ ] Edmonds-Karp;
- [ ] Dinic;
- [ ] max-flow min-cut;
- [ ] bipartite matching;
- [ ] Kuhn;
- [ ] Hopcroft-Karp.

### Trees as graphs

- [ ] LCA;
- [ ] binary lifting;
- [ ] Euler tour;
- [ ] diameter;
- [ ] heavy-light decomposition;
- [ ] centroid decomposition.

Practice:

- [ ] generic graph representation;
- [ ] BFS/DFS;
- [ ] SCC;
- [ ] shortest paths;
- [ ] MST;
- [ ] LCA;
- [ ] max flow.

---

## Dynamic Programming

### Foundations

- [ ] state design;
- [ ] transitions;
- [ ] base cases;
- [ ] memoization;
- [ ] tabulation;
- [ ] correctness;
- [ ] answer reconstruction;
- [ ] memory optimization.

### Main classes

- [ ] 1D DP;
- [ ] 2D DP;
- [ ] knapsack;
- [ ] subset sum;
- [ ] coin change;
- [ ] LIS;
- [ ] LCS;
- [ ] edit distance;
- [ ] interval DP;
- [ ] DAG DP;
- [ ] tree DP;
- [ ] bitmask DP;
- [ ] digit DP;
- [ ] rerooting DP.

### Optimizations

- [ ] rolling arrays;
- [ ] prefix optimization;
- [ ] monotonic queue optimization;
- [ ] divide-and-conquer optimization;
- [ ] convex hull trick;
- [ ] Knuth optimization.

---

## String algorithms

- [ ] naive matching;
- [ ] prefix function;
- [ ] KMP;
- [ ] Z-function;
- [ ] rolling hash;
- [ ] Rabin-Karp;
- [ ] Manacher;
- [ ] trie;
- [ ] Aho-Corasick;
- [ ] suffix array;
- [ ] LCP;
- [ ] suffix automaton;
- [ ] suffix tree overview;
- [ ] edit distance;
- [ ] string periodicity.

---

## Advanced / optional structures

- [ ] skip list;
- [ ] rope;
- [ ] gap buffer;
- [ ] piece table;
- [ ] persistent vector;
- [ ] immutable map;
- [ ] Bloom filter;
- [ ] Count-Min Sketch;
- [ ] HyperLogLog;
- [ ] k-d tree;
- [ ] quadtree;
- [ ] R-tree;
- [ ] cache-oblivious structures;
- [ ] work-stealing deque.

---

## Concurrency structures

- [ ] memory models;
- [ ] atomics;
- [ ] acquire/release;
- [ ] relaxed;
- [ ] fences;
- [ ] CAS;
- [ ] ABA;
- [ ] linearizability;
- [ ] lock-free;
- [ ] wait-free;
- [ ] hazard pointers;
- [ ] epoch reclamation;
- [ ] RCU;
- [ ] SPSC queue;
- [ ] MPMC queue;
- [ ] Treiber stack;
- [ ] Michael-Scott queue.

---