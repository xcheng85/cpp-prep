# Multithreading in C++


lock-free queue for inter-thread communication

Concurrent data processing: 

Concurrent task dispatch




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