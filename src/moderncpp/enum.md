# enum c++ vs go

## enum vs enum class in c++

## enum in go
```go
type ServerState int

const (
    StateIdle ServerState = iota
    StateConnected
    StateError
    StateRetrying
)
```