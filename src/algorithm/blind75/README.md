## two pointers

### from two ends to the middle

sort, compare value and move two pointers in the range

nsum is 2sum + recursive

end condition: l > r

### from middle to the side

### app1: max length of palindrome
palindrome, consider odd and even
end condition: left < 0 || right >

### app2: number of all palindrome substrings
similar idea

### fast-slow two pointers

### merge list, dummy

### how to decide move left pt or right pt ? 

max area, container, water fall, whatever

 // key: 双指针技巧，移动较低的一边,

### container vs water ?

## sliding window (subrange problem)

### needs to ask yourself
when to shift left ? 
when to update the local optimal result? 

### no duplicate in subrange
### max sum in subrange
### min length of substring which meet some requirements
### subranage max product (positive negative)

### when to shift left end 

some restrictions: no duplicates, etc.
negative contribution for subrange-sum problems


[left, right)
extra data structures: unordered_set, insert and erase while sliding and update the optimal result during the sliding

## ds: stack
valid expression

linked-list operation involves head and tail nodes, reorder nodes, 

crash if pop, top on empty stack


## ds: pq

application: k element with some priority
// ascending, minQueue
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
// descending
priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>> pq;


## binary search in a rotated sorted array

### min value in a rotated sorted array

1. find the sorted section

if target is within sorted section, move one end
if not, move another end



## in-place

### rotate image
transpose and then reverse per row


## custom hashing

### string Anagrams

definition of anagram: same character different shuffle

counter per character (26)
26 bit counter string has hash key, 


## simulation 

find the correct state definition

state machine: state and mutation of state

### matrix spiral

1. see through the repeat pattern 
2. how many state changes are involved in each repeatable iteration ? 4 bounds are the four state

## sorting 

### 1. intervals 

## tree

### 1. figure out recursive solution 

the end condition, divide and conquer

### build tree recursive

preorder and inorder. root node --> left and right tree, and recursive

postorder and inorder, last one is root node --> left and right tree, and recursive

preorder and postorder, root --> left and right tree and recursive

## dfs vs backtracking


backtracking: path, maxDepth of tree, you carry the depth value along the path

dfs: node. 130_surround region, you don't carry state along the path, just go to each node and do some operation clean

### backtracking

a state global optiomal result
a state push and pop during tree traversal 

both of them pass to the dfs recursive as reference

1. restore path
2. end condition
3. out of bound path trim
4. state of each iteration: espectially the current path. 


## bfs

every while loop iteration, deal with entire tree level

## dfs vs perorder traversal
same concept

### island number
multi-source undirected graph, need visited map
dfs, preorder traversal, 
action is: grid[i][j] = '0';

### why island is not a backtracking, because it only cares about the node not the path

## union set

great at check loops in the graph ()

### lis, largest increasing number

each number as a node in the graph, 
if continue, merge. 

extra sauce: is the state of counter, could be setsize

### valid tree 
the undirect edge == union merge, in the end check if it is one union set


## dp 

### max subarray (continuous) multiplication

consider both negative and positive extreme at subproblem

// third one is restart the subarray

minmax<double>({dpMax[i - 1] * nums[i], dpMin[i - 1] * nums[i], (double)nums[i]});



### stock 
// ith day
// buy k times
// 0: not own stock; 1 own stock
 dp[n-1][k][0]


## graph 

### dfs(preorder traversal) : clone graph
hash map between two graphs

unordered_set to avoid visited node


## bit manip

1. how to parse one bit 
    // 1. get the last bit: n & 0x1
    //    get the 2nd last bet: (n >> 1) & 0x1


2. how to write one bit

    // 2. write to a certain ith bit: res |= 1<<i

### xor: missing number

find the diff, 


## trie 

treeNode, leaf boolean, map kv, 

key is char or c - 'a'

every word inserted will create/update a node to be leaf true

### when trie + preorder traversal dfs 

a wild card * which trigger multiple paths to search . is it dfs or backtracking ? it is dfs because it only care about the node states not the path, there is no carry over between parent to child

for dfs: 

1. end condition: 

2. parent to 1 child or to n children based on some conditions. 

### perorder vs postorder traversal

when you care about the result of children and do sth about it, it is time to use postorder traversal

### world search in a grid

grid: multi source, undirected graph, this means a way to record visit is needed. 

world search it carries the path: due to a world is from multiple charactors, so it is a backtracking

## Binary search 

1. search kth element
2. find common acester

in order traversal ascending


## DifferenceArray: 差分数组的主要适用场景是频繁对原始数组的某个区间的元素进行增减

build difference array
rebuild array from difference array

### minMeetingRooms == maximum overlap 

### application: wether meeting overlap (==maximum overlap > 1) and maximum overlap



## graph

### tree vs graph

In other words, any connected, undirected graph without simple cycles is a tree.

tree should be single source which is the root.

### what is a valid tree ? 

1. single source
2. all the nodes should be visited by exactly once

Now, you have a need to record the visit path, so it become the dfs(backtracking)

// path due to undirected graph, avoid child back to parent due to undirect graph properties

### adj list


## bfs & topology sort



### application: alienOrder

1. create graph nodes and directional edges
2. build the adj list (directional)

3. starting topology sorting
a. indegree 0
b. neighbor indegree--

good result is topology outcome cover all the characters


## string operations
to_string

stoi

find_first_of: s.find_first_of("#", i); after position i

substr: starting position and length

s.substr(delim + 1, length); 

### string encode/decode: 

using string length for parsing ability 


## priority queue

### application: find median 
what is the median ? odd or even, 

always maintain two part and their difference is 0: even

there difference is 1: odd, easy case

min-pq: std::greater

max-pq: std::less

min-pq all the elements > max-pq.

cut half of a primad: min-pq on top of max-pq

findMedian: function is simple, either average or the top one of larger queue
maintain two pqs function: 

how to maintain the balance: 

if sizeof max-pq >= min-pq, we know we are going to add one to the min-pq to balance. which one to add, the new max one from the max-pq


## preorder-traversal recursive imp

### app: tree traversal encoding and decoding, serialization and deserialization
1. what to represent null node 
2. what to represent delimiter


// stringstream parsing with delimiter
    std::istringstream input2;
    input2.str("a;b;c;d");
    for (std::string line; std::getline(input2, line, ';');)

### subtree which is the extension of sametree

subtree could happen in any node in a original tree, that is why it is a full tree traversal until find one


## greedy algo

### interval problems
sorting by ending of [], so you only need to the the end and the start of next one