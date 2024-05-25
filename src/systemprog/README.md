# All about system programming

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