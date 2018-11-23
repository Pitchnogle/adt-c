# adt-c

A collection of abstract data types in the C programming language

### Abstract Data Types
- [Linked-List](src/list.h)
- [Doubly Linked-List](src/dlist.h)
- [Circular Linked-List](src/clist.h)
- [Stack](src/stack.h)
- [Queue](src/queue.h)
- [Chained Hash Table](src/hashtable.h)

### Contents
- [src](src)<br>
  *Contains the source code for various adt's*
- [examples](examples)<br>
  *Contains example code using the various adt's*

### Build Instructions

The code herein is intended for an out-of-source build

```
mkdir build
cd build
cmake ..
make
```

### Notes

At this point, the collection of adt's are not made into a library, but this would be a natural next step. The code is documented using Doxygen style tags.

The code is refactored but heavily inspired by the adt's presented in [Mastering Algorithms with C](http://shop.oreilly.com/product/9781565924536.do) by O'Reilly.
