# c++ learning: examples, libraries and notes

This repository records various small c/c++ programs when I am learning!

* [stl](./stl) learning to implement the **standard template library**!

* [aligned_malloc](./aligned_malloc) aligned malloc.

* [func_pointer](./func_pointer) simple function pointer dispatch example.

* [registry](./registry) simple registry example.

* [python_call](./python_call) python call c/c++ example.

* [dynamic_lib](./dynamic_lib) dynamic library example.

* compiler and OS macro can be refer to [./macro/README.md](./macro/README.md),  cpu arch can be refer to [./macro/cpu_arch.h](./macro/cpu_arch.h)

* [cpuinfo](./cpuinfo) get cpu isa.

## c++ learning
### What's the difference between initializer list vs constructor?

A: They are not the same if objects are *non-POD* (i.e. non-Plain Old Data) types:
```c++
public: 
  Thing(int _foo, int _bar){
    member1 = _foo;
    member2 = _bar;
}
```
is equivalent to
```c++
public: 
  Thing(int _foo, int _bar) : member1(), member2(){
    member1 = _foo;
    member2 = _bar;
}
```
because they will be initialized before the constructor body starts executing, so basically twice the work is done. That also means, if the type of these members don't have default constructor, then your code will not compile.

ps: Initializer List is the only way to initialize const members! 

### What is meant by Resource Acquisition is Initialization (RAII)?

A: It's a really terrible name. It truely means **Scope-Bound Resource Management!**



