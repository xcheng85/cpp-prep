# Design of project
structure, managing deps and abstraction
minimizing deps through abstraction

# three levels
arch -> design -> impl

## c++ features
raii, algo, lamda, modules,
std::enable_if: SFINAE
copy and swap idiom
Non-virtual Interface idiom: Template Method
pimp idiom

## keywords
structure
change/test/extend code
coupling and deps
how to test private function: move out srp

## SOLID

### I: Interface segragation (goal: separation of concern)
### O: open for extension but close for modification

dynamic poly version: multiple virtual base class

static poly version: multiple concept 
### D: inversion of dependencies
Stable layer should not depends on unstable layer (such as ui), introduce abstraction layer and put it in the layer of stable layer
example: 

// way 1: inheritance
// way 2: concept of template, caller to satisfy concept
// way3: 


## Visitor pattern
Goal: Extension not for object type but for operation

How to add more operation but adhere to OCP (without modify base class)

ask question about wether extend type or operation

visitor bad for type extension

## Strategy pattern
1. figure out all the variable point
2. follow SRP, each variable point will be 1 abstraction
3. good for add new types not new operations

## Strategy pattern + template meta
through concept

## command pattern
command base class: invoke
command pattern class carry state to support undo

## strategy vs command pattern
strategy: how to be done
command: what to be done

## strategy pattern without using runtime polymorphism
use std::function

std::function performance issue in gcc
and re-implemented with Type Erasure


## Adapter pattern
stack: adapter deque
queue: adapter deque
pq: adapter vector


object adapter: based on composition, good, template 
class adapter: based on inheritance, bad
function adapter: based on function overload

## observer pattern

event: job added to the queue, config change

decouple from event and observer, redis

1 to N: 

single responsibility: a subject that changed 

## Bridge Pattern
hide detail, avoid re-compilaition
pimp: ptr imp idiom
ABI: application binary interface stability

## Prototype Pattern, clone the right object in the hierachy chain

## Decorator Pattern
flexible combination of different function through composition
every layer of decorator is SRP
and OCP