# concurrent programming c++ vs go

## multi-thread

two mutex different order dead lock
like shared ptr 

## 4 ways to launch threads

1. global function
2. functor
3. lamda
4. member function of an instance of a struct/class

## data races with functor
lock_guard<>


## cancel threads

## inter-communication between threads
pass reference to operator with mutex protection, or atomic

future, blocking get or polling readiness



## async io (task based)

