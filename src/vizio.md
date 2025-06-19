# Vizio c++ 

interview questions ? 

latest projects ? 
what you could done differently ? 
conflict and how to resolve
createive idea but difficlut to implement ? cuda trilinear interpolation

leetcode bulb switch


1. multithreading

gcc-based toolchain

cout: not thread-safe

poco: lib, thread pool as extra, db clients: redis, sql, mongo

pub-sub, redis stream consumer group, 

redis: polling central queue (redis stream channel, waste cpu cycle, mutex in redis)
task scheduler: push model, communication between threads

atomic and lock-free


2. debugging

core-dump: examine whiere crashed, in which thread and memory
debug info complied into binary
debug info == symbol
sudo apt install systemd-coredump

g0: no debug release
g3

gdb cli steps:
 gdb binary
 break *.cpp:line
 c: continue after breakpoint
 run
 ctrl + c : program have interupt signal implemented
 q: quit

 info threads: list all the current threads
 bt: current task for current thread

3. network programming 
boost beast websocket client
boost asio tcp/udp server and client

tcp: reliable
udp: no retransmitt

network latency and throughput
bandwidth: bits/sec
throughput: bits/sec, how to improve throughtput ? buffering
latency: roundtrip, metrics what to measure

keep-alive strategy: 

protocals
packats: paload


4. entire dev cycle, design coding, debugging, testing, integration, deployment, ci/cd




5. system performance, memory, profiling, , build systems

c++ chrono:
system_clock
steady_clock
high_resolution_clock

write performant code ? 
cache-friendly: flat ds, vector, continous memory

plf::colony
tsl::hopscotch_map
abseil: flat_hash_map, flat_hash_set over stl map

data-oriented design:
not use ood, (array objects --> object of arrays (field in the object design))
alighment of object data members, save padding

6. c++ dev tools: GDB, valgrind, perf, design pattern, software architeture, 

measure performance

compiler config

machine into performance mode: 


memory performance:
cache friendly design
fragmentation

profiling: cpu hardware event counter, count memory access and cache hits and misses

perf satate -e L1-dcache-load-misss, L1-dcache-loads


```shell
cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_available_governors 
# check performance or powersave
cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
# change to performance mode
echo performance | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

sudo cpupower frequency-set --governor performance
```

performance metrics

google micro-benchmarks: catch performance regression
simulations: sythetic data
replay: record production requests with timestamps, 
profilers: 
    instrumentation profiler: tracy
    sampling profilers: perf 
    debug symbol 
    framegraph

wall time: -Wall 
debug symbol: -g

way to profile ? 
create based line and find the delta



what code should profile ? 
measurement: google microbenchemark
understand the result of measurement: profiler

sudo perf stat ./perf-benchmark


task-clock: cpu time
context-switches: cpu and os scheduler
page fault: 


sudo perf record ./perf-benchmark

call graph: -g, sampling profile, interupt and current stack
it needs flag: -no-omit-frame-position overhead

sudo perf record -g ./perf-benchmark
sudo perf report 'graph,0.5,caller'  -g


tracing: log, correlationId, jJaeger zipkin

7. ipc, shared memory system programming

os signal: SIGINT (ctrl + c)
coredump
// 

8. static analysis & dyanmic analysis

sudo apt-get install valgrind

Memcheck command

valgrind --log-file=banking.log --read-var-info=yes --leak-check=full ./banking

==3893577== 56 bytes in 1 blocks are definitely lost in loss record 1 of 1
==3893577==    at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==3893577==    by 0x10CD3E: main (bootstrap.cpp:206)

// pthread 

valgrind --tool=helgrind --log-file=banking.log  --read-var-info=yes ./banking

able to detect the synchronization isseu of writing to std::cout

// drd

valgrind --tool=drd --log-file=banking.log  --read-var-info=yes ./banking
