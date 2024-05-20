# All about DS and algorithm

# Math

## divisibility rules
1 - 19
https://www.geeksforgeeks.org/divisibility-rules/

## matrix

## number theory
application: cryptography
Hash functions

integer factorization: 
gcd

## geometry

## Combinatorics (brain teaser)
https://www.geeksforgeeks.org/mathematics-combinatorics-basics/

counting the number of available IPv4 or IPv6 addresses. 

In how many ways can 3 winning prizes be given to the top 3 players in a game played by 12 players?  12 * 11 * 10

### permutation vs combination ? 
permutation: order matters
combination: order does not matter

N numbers number of permutation: N!

### r out of n permutation

P(n, r): n!/(n-r)!

### combination: unordered selection (r out of n) 
An unordered selection of r elements from a set is called an r-combination. It is represented as C(n,r)

duplication: N!

C(n,r) = P(n, r) / r!

### 二项式系数（binomial coefficient）
![alt text](image.png)

### 二项式定理(binomial theorem)
![alt text](image-1.png)

### 容斥原理(Principle of inclusion-exclusion)
A∪B∪C = A+B+C - A∩B - B∩C - C∩A + A∩B∩C

## Probability and Statistics
mean
median
mode
Variance: Variance= ∑(Each value−Mean) 2 / Total number of values
Standard Deviation = √Variance

A or B
exlusive: P(A ∪ B) = P(A) + P(B),
un-exclusive: P(A ∪ B) = P(A) + P(B) – P(A ∩ B)

A and B: 
P(A ∩ B)=P(A)×P(B∣A)=P(B)xP(A∣B)

Bayer rules (贝叶斯公式) 条件概率:
application:
Spam Filtering:
Medical Diagnosis
Marketing and Recommendation Systems: 
Machine Learning
Decision Making:
A/B Testing

P(A|B)=P(B|A)*P(A)/P(B)。

例如：一座别墅在过去的 20 年里一共发生过 2 次被盗，别墅的主人有一条狗，狗平均每周晚上叫 3 次，在盗贼入侵时狗叫的概率被估计为 0.9，问题是：在狗叫的时候发生入侵的概率是多少？
我们假设 A 事件为狗在晚上叫，B 为盗贼入侵，则以天为单位统计，P(A) = 3/7，P(B) = 2/(20*365) = 2/7300，P(A|B) = 0.9，按照公式很容易得出结果：P(B|A) = 0.9*(2/7300) / (3/7) = 0.00058
另一个例子，现分别有 A、B 两个容器，在容器 A 里分别有 7 个红球和 3 个白球，在容器 B 里有 1 个红球和 9 个白球，现已知从这两个容器里任意抽出了一个红球，问这个球来自容器 A 的概率是多少?
假设已经抽出红球为事件 B，选中容器 A 为事件 A，则有：P(B) = 8/20，P(A) = 1/2，P(B|A) = 7/10，按照公式，则有：P(A|B) = (7/10)*(1/2) / (8/20) = 0.875

# DS

## array(vector)

move between two vectors
std::move(v1.begin(), it, std::back_inserter(v2));  // ##

max_element(v.begin(), v.end()): return itr

logging vector easy way: std::copy(std::begin(output), std::end(output), std::ostream_iterator<int>(std::cout, " "));

## string

### string compare pattern

s.compare(0, pattern.size(), pattern);
== cstring's strcmp 

comparision between string and c-string const char*
1. compare, strncmp
2. operator<=>, strcmp

## hashtable
### custom hashtable
1. hash template specialization
2. operator== const overload

## pair 
pair comparison is done in the first element

## pq (heap, adaptor)

## stack (adaptor)

## Hash Function
c++
stl: linear chaining

hash value transformed to bucket index 

more memory for less collision

custom class with hash template speciailization (functor struct)

custom class with hash: https://ianyepan.github.io/posts/cpp-custom-hash/

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
input: float between [0,1], distribution uniformly
Number of Bucket: N

floor(input * N) -> bucket
sort in each bucket increasing order
merge

## Radix Sort (linear)
get the max value to determin how many bits
integers or strings with fixed-size keys. 
count sort from least significant bit to most significant bit

## Count Sort (linear)
limited range of input values. 
range of input values is small
count the frequency of each distinct element
use that information to place the elements

## Rejection Sampling (data science and statistics domain)

## Biconnected Component (hard)
### Biconnected Graph
Even after removing any vertex the graph remains connected.



## Suffix Array 
efficient string processing

### could be used to solve "LRS(Longest Repeating Substring)" 
LRS = suffix array + LCP(longest common prefix)


Pattern Searching algorithm
They are very useful when performing a search in a database

Suffix array is an extremely useful data structure, 
string pattern match

stl string operator<=>
// substring compare without copy ? 
int compare (size_t pos, size_t len, const string& str) const;

Longest Repeating Substring


### LCP array
­­kasai’s Algorithm for Construction of LCP array from Suffix Array


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
### standard trie
### compress trie
### suffix trie

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
