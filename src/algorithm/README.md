# All about DS and algorithm

# Math

## matrix

## number theory

## geometry

## Combinatorics

## Probability and Statistics

# DS

## array(vector)

move between two vectors
std::move(v1.begin(), it, std::back_inserter(v2));  // ##

max_element(v.begin(), v.end()): return itr

logging vector easy way: std::copy(std::begin(output), std::end(output), std::ostream_iterator<int>(std::cout, " "));


## string

## hashtable

## pair 
pair comparison is done in the first element


## pq (heap, adaptor)

## stack (adaptor)

## Hash Function

## linked list (include dlist)
splice: move between two lists by range, avoid copy


# Algorithm

## STL algorithm

1. partition: quick sort partition based on pivot value, operator overload

## Quickselect
hint: 
kth largest element 
without sorting

## Comparison-based sorting
lower bound nlgn

## Bucket Sort (linear)

## Radix Sort (linear)

## Count Sort (linear)
limited range of input values. 
range of input values is small
count the frequency of each distinct element
use that information to place the elements


## Rejection Sampling

## Biconnected Component

## Suffix Array

## Line Sweep

## Reservoir Sampling

## Strongly Connected Component

## Eulerian Circuit

## Randomized

## Monotonic Queue

## Monotonic Stack

## Data Stream

## Game Theory

## Memoization

## recursion

## divide and conquer

## enumeration

## backtracking

## sliding window

## simulation

## prefix-sum

## bit manipulation

## two pointers

## sort

## dp

## greedy

## trie


tree

1. each node in tree's memory: Node[26], leaf and internal
2. build the tree, insert one by one
3. query the tree.

### bitwise trie

## graph:

### union find

### topology sorting

directed graph

BFS:

1. adjacent list
2. in-degree for each node
3. srcs to travasersal, (0 -indegree nodes)
4. all the neighbors push to queue, --degree
5. success condition: processed node == all nodes

### greedy-based shortest path

1. dijkstra (directed or undirected, all the weight is positive)

memory footprint:

1. adj list
2. distance array for record shortestPath after each iteration and result.
3. cache array to indicated the node is popped through " get the min distance in the cache" step.

sub-component:

1. get the min distance in the cache to pop every iteration

each iteration

1. pop the min distance
2. update the neighboring node's min distance (ignore the popped the neighbor(stable))

source to dsts.

### dp based shortest path

each iteration propgate from source to destination

max step size: number of node - 1. (assume no cyclic)

memory: o(n) size array for shortest path after each iteration
dist(src) = 0

// no need to build the adajenct list
// edge represent propagate

    for i := 1; i <= maxIterationStep; i++ {
    	for _, e := range edges {

        }

### mst based on greedy

1. dsu
2. sorted edges by weight
3. starting from edge1,
4. detect no cycle
5. join nodes to one set
6. next edge.
7. end condition: number edges == #node - 1

or fail

## DFS

## BFS

## binary search

## segmentation tree.

recursive, 0 or 1-based

ss, se,
qs, qe,
node index,
min,max,sum,...

## bit (fedwick tree)

memory: 1-based array

nodeIndex & (-nodeIndex): offset

+offset: build, nodeIndex propogate to ranges

-offset: query prefix sum [0, nodeIndex]
