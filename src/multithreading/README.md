# Multithreading in C++
system-level concurrency: offered by os

higher-level concurrency: go-routine

memory-model of multi-threading

## concept
### 1. thread and task ? 
thread is system representation of task

### 2. conceptual level vs lower-level
level level: thread, lock
conceptual level: future, promise, packaged_task

### 3. transfer ownership 

### 4. each thread has its storage
related to std::ref and std::cref
thread local storage

### 5. wait and not wait
join: wait
detach: daemon

### 6. 


## thread

task in thread can be:
1. function
2. functor
3. member function of instance
4. lamda
exception handling

### Passing data into task of thread

### fetching data from the task of thread
pass non-const ref or pointer to the functor/function 

std::cref
std::ref

### data race protection
1. std::cout 

mutex + lock (raii)

raii lock: (template class) 
1. lock_guard
2. scoped_lock

### scoped_lock vs lock_guard
scoped_lock: variadic mutex, avoid deadlock

### unique_lock vs lock_guard
unique_lock: deferred locking and try-locking

### multiple-reader and single writer


## packaged_task and future + promise
future: get value
promise: set value/exception

packaged_task: wrapper 

## packaged_task vs async() launch
async cannot use lock


lock-free: atomic

### atomic
<atomic>
template struct


lock-free queue for inter-thread communication

Concurrent data processing: 

Concurrent task dispatch

## Helpful from thread lib
1. get the hardware core number
2. thread id: std::thread::id, operator overload and hash are natively supported
custom object as key of hashmap

3. thread sleep

## thread-safe container with lock 
more than mutex and lock
the interface of stl single-threaded version is quite limited 

### stack

### double-linked-list


## Q&A


### problem1: dangling pointer/reference in task of a thread

### problem2: ways to wait for a thread

1. join
2. cv
3. future

### problem3: detach daemon thread use case
1. monitoring filesystem
2. clearing cache
3. optimizing data structure
4. open a vs code gui is a new detached thread of a same application

### problem4: three ways to deal with data race
1. lock-free programming
2. mutex
3. transaction

### problem5: tricky for protecting shared data
1. mutex + raii lock
2. no return pointer to external: either caller or 3rd lib

### problem6: thread-safe initialization issues
1. singleton instance() // c++11 support
2. third party: like db connection init //

### problem7: single write and multiple read case
#include <shared_mutex>

shared_mutex
shared_timed_mutex

for write: lock_guard, scoped_lock 

for read only: shared_lock

### problem8: inter-thread communication
1. busy check with lock
2. check with sleep 
3. cv and notify_one, notify_all
#include <conditional_variable>

pattern1: consumer group style, notify_one
pattern2: pub-sub style, notify_all

### problem 9: future vs threads. 
use bpop in thread-safe queue as example: 

1. thread-based impl: cv, unique_lock, wait, predict
2. task-based impl: future and blocking get call.



future with global func
future with linstance function
future with functor
future with lamda

### problem 10: building block of task management scheme (use case async streaming texture)
packaged_task<>: tie future to a function or functor

parallel mode: std::launch::async

sequence mode: on a thread

packaged_task: is the interface between task scheduler and the explict function

packaged_task + thread_safe_queue: 

main thread: load gltf and use packaged_task to submit the reading texture requests

streaming thread (>=1): access the task from the queue and execute and store the result and 
be retrieved by get_future().

### problem 11: value of promise




## libraries
taskflow: dependency graph






C++:
1. system resource control
2. template meta-programming: compiling computation
3. concurrency
4. lamda and function template for callback
5. RAII
6. Async I/O
7. data structure friendly for cpu cache
8. hardware affinity. CPU pinning for mt, SIMD
9. deterministic memory management
10. CPU cache: memory alighment, memory layout optimization
11. inline: avoid call stack
12. move: avoid copy
13. Direct memory access, bespoke memory allocation
14. constexpr functions
15. compiler optimzation: -O3
16. GPROF, VALGRIND, Perf
17. GCC Data prefetch
18. stl parallel 
19. Memory and thread pool


Networking: 
1. Market data feed, 
websocket/FICX

2. client to execute order

3. kernel bypass





quantitive analysis, assigned/idel ratio


System Design:
1. fault-tolerant: redundancy, low-latency failover


## Simulation









## threads on linux
thread affinity (pthread)

### daemon threads application
new window in word/vs code

### thread id & unordered_map

### multi-thread implementation of pub-sub, producer/consumer pattern

communication pattern between threads

### consumers (consumer group) with conditional variable + notify_one 

mimic redis/kafka

### future,promise and http request/response

### future + daemon threads

### promise functor and class template: packaged_task + future



## Memory pool

### overload operator new and operator delete

new class


### placement new operator (key to memory pool)
invoke constructor on the allocated piece of memory

## Lock-free queue (communication between threads)

### pattern: one write and one read

atomic: 

mutex, lock: heavy, 


## Logger multi-thread logger

mainthread --> logger thread (lock-free queue for communication)

separate thread to log to files: i/o slow, string format slow

## tcp/ip network programming (socket programming)

### concept

1. network interface: 
point of connection between a computer and a network.

list all ni
```shell
ls /sys/class/net
ip link
ip addr
```

2. Hardware timestamping and software timestamping
Hardware support from NIC

Exchange gateway connectivity (ideally with options exchanges).
Networking protocols familiarity (tcp/ip/udp, multicast, sequencer architecture, kernel bypass).

matching engine development.
Familiar with high performance computing & memory management.

Software Engineer, Backend, 7+ Years of Experience
Snap Inc.

Experience using various profling tools (e.g., gdb, Nsight, Valgrind, fame graph) to optimize the code.

Software Engineer, Robot Cloud Platform