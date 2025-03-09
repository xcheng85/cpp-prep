# Memory Management c++ vs go

## c++ 
stack frame: callgraph of function

free store --> heap, smart pointers

## pointer address to be const

T* const t {new T};

## value point to const
const T* t;

## reference vs pointer
reference must be initialized, reference is not changeable

reference safer: no uninitailzed, 

reference support poly,

pointer is needed, you have pointer arithmatic,
and store pointer in stl container

## reference with rvalue (especially function parameter)

## auto cast away const reference create copy, const auto& 
## decltype(auto) keep const and reference



## smart pointers

### weaker pointer to Dealing with Circular References