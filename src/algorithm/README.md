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

In how many ways can 3 winning prizes be given to the top 3 players in a game played by 12 players? 12 _ 11 _ 10

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

P(A|B)=P(B|A)\*P(A)/P(B)。

例如：一座别墅在过去的 20 年里一共发生过 2 次被盗，别墅的主人有一条狗，狗平均每周晚上叫 3 次，在盗贼入侵时狗叫的概率被估计为 0.9，问题是：在狗叫的时候发生入侵的概率是多少？
我们假设 A 事件为狗在晚上叫，B 为盗贼入侵，则以天为单位统计，P(A) = 3/7，P(B) = 2/(20*365) = 2/7300，P(A|B) = 0.9，按照公式很容易得出结果：P(B|A) = 0.9*(2/7300) / (3/7) = 0.00058
另一个例子，现分别有 A、B 两个容器，在容器 A 里分别有 7 个红球和 3 个白球，在容器 B 里有 1 个红球和 9 个白球，现已知从这两个容器里任意抽出了一个红球，问这个球来自容器 A 的概率是多少?
假设已经抽出红球为事件 B，选中容器 A 为事件 A，则有：P(B) = 8/20，P(A) = 1/2，P(B|A) = 7/10，按照公式，则有：P(A|B) = (7/10)\*(1/2) / (8/20) = 0.875

# DS

## array(vector)

move between two vectors
std::move(v1.begin(), it, std::back_inserter(v2)); // ##

max_element(v.begin(), v.end()): return itr

logging vector easy way: std::copy(std::begin(output), std::end(output), std::ostream_iterator<int>(std::cout, " "));

## string

reverse() //reverse string in-place

istringstream
std::getline(stream, str, ".")

string.reserve() // avoid reallocation

### string compare pattern

s.compare(0, pattern.size(), pattern);
== cstring's strcmp

comparision between string and c-string const char\*

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

## Special: Monotonic Queue (low frequency)

has to be deque

### application

sliding window
Solving dynamic programming problems such as LIS (longest increasing subsequence) and LDS (longest decreasing subsequence)

### limitation:

only those that involve finding the maximum or minimum element in a specific order

increasing monotonic queue: slide window min value

decreasing monotonic queue: slide window max value

## 单调队列 vs Max(Min)Heap

优先级队列无法满足标准队列结构「先进先出」的时间顺序，
既能够维护队列元素「先进先出」的时间顺序，又能够正确维护队列中所有元素的最值，这就是「单调队列」结构。
有些稍微复杂的滑动窗口问题不能只靠两个指针来解决，需要上更先进的数据结构

最值: two pointer slide window cannot solve

based on deque

step1: implement class DecreasingQueue

step2:

## Special: Monotonic Stack (单调栈)

### application:

next greater/smaller element
Finding Previous Greater/Smaller Element

Finding Maximum Area Histogram:
Finding Maximum Area in Binary Matrix:
Finding Sliding Window Maximum/Minimum:

Expression Evaluation:

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

floor(input \* N) -> bucket
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

## Line Sweep (hard)

computation geometry

counting intersection pts

closest pair

## Reservoir Sampling vs Selective Sampling

statistic area

Reservoir sampling is a family of randomized algorithms for randomly choosing k samples from a list of n items, where n is either a very large or unknown number.

## Strongly Connected Component (hard)

search engine
data science
network

## Eulerian Circuit (hard)

airline ticket

## Randomized

## Data Stream

## Game Theory

## Memoization

## recursion

## divide and conquer

## enumeration

## backtracking

hint: ask you return all the combination under a condition

o(n!)

1. n! unique number permutation [1, 2, 3]
2. decisition tree
3. recursive traversal n-tree

## sliding window

「左闭右开」区间
[left, right)

hint: substring-related problem

two pointers and moving accordingly

## simulation

## prefix-sum 前缀和

前缀和主要适用的场景是原始数组不会被修改的情况下，频繁查询某个区间的累加和
prefix-sum vs bit
immutable--> prefix-sum

## difference array 差分数组

差分数组的主要适用场景是频繁对原始数组的某个区间的元素进行增减。
diff 差分数组是可以反推出原始数组 nums

diff[i] += 3 意味着给 nums[i..] 所有的元素都加了 3，然后 diff[j+1] -= 3 又意味着对于 nums[j+1..] 所有元素再减 3，那

只要花费 O(1) 的时间修改 diff 数组，就相当于给 nums 的整个区间做了修改

## bit manipulation

0x0A
0b00010001

### c-style

1. get the rightmost bit (bit algorithm)

2. remove the rightmost bit

3. counting bit 1 in a number

4. check one bit is 1

5. toggle one bit

### c++ bitset style

## two pointers (array)

## two pointers (linked list)

dummy header

1. 合并两个有序链表

2. 链表的分解

3. 合并 k 个有序链表

4、寻找单链表的倒数第 k 个节点

5、寻找单链表的中点

6、判断单链表是否包含环并找出环起点

7、判断两个单链表是否相交并找出交点

condition for loop:
if(fast == slow && fast && fast -> next != nullptr && fast -> next->next != nullptr)

## sort

## dp

duplicate subproblem
dp is like a N-tree

### remove duplicate problem == cut branches of N-tree

### Top-down with memorization

### Bottom-up

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
边的方向表示「被依赖」关系

在常规的算法题中，邻接表的使用会更频繁一些，主要是因为操作起来较为简单，但这不意味着邻接矩阵应该被轻视
有向图
入度（indegree）和出度（outdegree）
有向加权图: 1 vs weight

vector<int> graph[]; // only save index
vector<pair<int, int>> graph[]; // [index, weight]

无向图 == 双向

如果图包含环，遍历框架就要一个 visited

### dfs vs backtracking

dfs: focus on node, revoke outside the for loop

backtracking: focus on branch, revoke (看到了吧，你回溯算法必须把「做选择」和「撤销选择」的逻辑放在 for 循环里面，否则怎么拿到「树枝」的两个端点？) 「树枝」的两个端点 == branch


```c++
// DFS 算法，关注点在节点
void traverse(TreeNode* root) {
    if (root == nullptr) return;
    printf("进入节点 %s", root);
    for (TreeNode* child : root->children) {
        traverse(child);
    }
    printf("离开节点 %s", root);
}

// 回溯算法，关注点在树枝
void backtrack(TreeNode *root) {
    if (root == nullptr) return;
    for (TreeNode* child : root->children) {
        // 做选择
        printf("从 %s 到 %s", root, child);
        backtrack(child);
        // 撤销选择
        printf("从 %s 到 %s", child, root);
    }
}
```

### cycle detection (DFS)
循环依赖
in the traverse code
 // cyle detection first, then visited

course schedule problem

dfs + visited + path cache

### cycle detection (BFS)
queue keep degree0
degree 0

good: all nodes go rought degree 0
bad: left nodes with degree >= 1

extra ds: vector<int> indegree(numCourses, 0);


### union find

### topology sorting (dfs)


图中存在环，是无法进行拓扑排序的
!循环依赖 + Order
answer is not unique

1. 判断一下题目输入的课程依赖是否成环，成环的话是无法进行拓扑排序的
2. 后序遍历的结果进行反转，就是拓扑排序


拓扑排序


directed graph

BFS:

1. adjacent list
2. in-degree for each node
3. srcs to travasersal, (0 -indegree nodes)
4. all the neighbors push to queue, --degree
5. success condition: processed node == all nodes

### topology sorting (bfs)

1. only indegree 0 node can be pushed to queue

2. compare traversed node count for all the nodes, good: ==

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

## binary tree

iteration vs recursion

merge sort: postorder traversal

quick sort: preorder traversal, pivot, less/greater

二叉树题目的递归解法可以分两类思路，
第一类是遍历一遍二叉树得出答案，
第二类是通过分解问题计算出答案，这两类思路分别对应着 回溯算法核心框架 和 动态规划核心框架。

### binary tree traversal ---> backtracking (decistion tree)

### binary tree traversal ---> dp (subproblem)

举具体的例子，现在给你一棵二叉树，我问你两个简单的问题：

1、如果把根节点看做第 1 层，如何打印出每一个节点所在的层数？ (Parent pass down) lc 102

2、如何打印出每个节点的左右子树各有多少节点？ (child first than bubble up) must postorder traversal

post-order traversal: subproblem and merge

## DFS

dfs == backtracking

## BFS

a step difference == one level advancement in bFS

hint: nearest distance, min change



trick: visited cache to avoid "go back"
find the neighboring logic

bfs: all the same level advance at the same time,

## DFS vs BFS

nearest distance: BFS
space complexity: dfs o(lgn) // stack frame
bfs o(n/2) // all the leaf node

## binary search

three form

1. basic, search one element
2. search left bound
3. search right bound

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
