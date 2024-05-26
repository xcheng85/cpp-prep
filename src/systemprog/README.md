# All about system programming

## enable coredump on ubuntu
```shell
ulimit -S -c unlimited
sudo apt install systemd-coredump
coredumpctl list
coredumpctl info -1
```

## time choice
boost
posix api
<time.h>

c++ chrono:
1. system_clock
2. steady_clock
3. high_resolution_clock

## signal
<signal.h>
### list all the signals

kill -l 
15) SIGTERM   catchable (no coredump)
9) SIGKILL     uncatchable (app cannot trap it)
6) SIGABORT   terminate with core dump
11) SIGSEGV   terminate with core dump



application ignore a signal
application catch(trap) a signal: 

crashed, upload stack, instrumenting

### send signal between processes



## io/file operation
istream: cin, ifstream, isstringstream

getline: any istream, customize delimiter

sstringstream: both in and out

## time auditing

## os signal

## os scheduler (realtime process)

### containerization settings
https://docs.docker.com/config/containers/resource_constraints/#configure-the-real-time-scheduler

1. default CFS scheduler:
The CFS is the Linux kernel CPU scheduler for normal Linux processes.

2. real-time scheduler: make sure the host machine's kernel is configured correctly 
configuring the kernel real-time scheduler



--cpu-rt-runtime: set to the maximum number of microseconds reserved for real-time tasks per runtime period, run for 950000 microseconds for every 1000000-microsecond period, leaving at least 50000 microseconds available for non-real-time tasks

--ulimit: The maximum real-time priority allowed for the container.

linux capability:
CAP_SYS_NICE: which allows the container to raise process nice values, set real-time scheduling policies, set CPU affinity, and other operations.

RR_SCHED policy in k8s

docker

securityContext:
      capabilities:
        add:
        - SYS_NICE



## ipc
a lot copy back and forth between user-space and kernel-space

### pipe
### named pipe
application: chat
size limit: 4kb atomic guarentee

### message queue (POSIX)
system header: <mqueue.h>

needs to link against: /usr/lib/x86_64-linux-gnu/librt.a

number of messages in the queue
byte size of each message

message queue descriptor, like fd
messageattributes: like vkInstanceDescription

mode: write-only, read-only
permission to acccess the message queue

### shared memory
no kernel involved
need synchronization mech
based on mmap, map a file to a memory

### ipc in boost
https://theboostcpplibraries.com/boost.interprocess

## memory

custom deleter with unique_ptr: case

size of shared_ptr is 16 bytes
size of unique_ptr == size of normal pointer == 32 bit = 8 bytes

### aligned memory

how to allocate aligned memory ? 
 
how to check if the memory is aligned ? 

### aligned memory without using modern c++ 
also utilize the placement new ? 

alignMemoryAddress (bit manipulation) to move address to the alignment, waste some addresses.

also, return the void * to the caller and let them do the typecast


std::byte *: enum class byte : unsigned char
uchar8 *
malloc vs new
// “new” does call the constructor of a class whereas “malloc()” does not.


StackLinearAllocator: 

HeapPoolAllocator: external library, multiple pool size, ...

### memory-mapped io
memory not in heap and stack, a separate memory area of virtual space of this process. 


### memory allocator + memory-mapped io