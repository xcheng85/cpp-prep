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

## multi-dimension array c++ vs go

### init with lateral 

```cpp
// cpp
uchar8 board[2][4]{
    {0, 1, 2, 3},
    {4, 5, 6, 7},
};


```

```go
// go array

a := [2][4]uint8{
    {0, 1, 2, 3},
    {4, 5, 6, 7},
}

// slice
a := [][]uint8{
    {0, 1, 2, 3},
    {4, 5, 6, 7},
}
```