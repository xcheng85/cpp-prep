# Array c++ vs go

## c++ 

### old style
```c++
// lateral init
int myArray[] {1, 2, 3, 4}; 
std::size_t s {sizeof(myArray)/sizeof(int)};
```

### modern
```c++
std::array<int, 4>
```