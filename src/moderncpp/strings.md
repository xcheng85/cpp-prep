# string go vs c++

## c++ 

### old 
null-terminated char array

header <cstring>
length of string: strlen
compare string: strcmp

no operator overloading

### new
stl std::string, tempalte class

operator overloading:
compare: simple as ==, <=> lexi
concat: +=
deep copy: =

.c_str(); danger, dangling pointer
.data(); danger, vulkan api


### literal

### go
strings package

## substring go vs c++

### c++

member function of string

substr(pos, len)

### go 
s = s[:len(s)-1]

## return pos(size_t, int) of matched substring
### c++

```cpp
auto pos = string.find(substr);
string::npos static = -1;

```

### go
i := strings.Index(str, substr)

##  replace substr c++ vs go

### c++
```cpp
// only 1 match, 
replace(pos, len, str)
```

### go

```go
// 3 means first 3 matches, different than c++ api
strings.Replace("gfg gfg gfg", "g", "G", 3)
```

## prefix/suffix string go vs c++

### c++

```c++
bool starts_with(std::string sub);
bool end_with(std::string sub);
```

### go

```go
func HasPrefix(str, pre string) bool
func HasSuffix(str, suf string) bool
```

## Contains substring c++ vs golang
```c++
//c++
bool contains(string sub);
```

```go
// golang
func Contains(str, substr string) bool
```

## strings literal go vs c++

```c++
// namespace std::string_literals;

// s


```