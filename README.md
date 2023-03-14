# CList
**CList** is a [compound](https://en.wikipedia.org/wiki/Composite_data_type) data structure developed to emulate the Python-style [list](https://docs.python.org/3/tutorial/introduction.html#lists) as closely as possible within C.


## How?
Installing CList into your project is as easy as including it within your header files and source. Place it wherever you'd like, include the header file as needed, and make sure to compile it alongside everything else.

To use it, see the example below for the steps recommended:

```C
// Initialise the new list.
LIST_T *list = list_new();
// Create an item to add to the list, and append it.
unsigned long a = 0xffffffff;
list_append(list, a);
// ...
char b = 'c';
list_append(list, b);
// ...
short c = 0x0fff;
list_append(list, c);

// ...

// Retrieve items from the list as needed.
list_get(list, 0);  // Returns an unsigned long equalling a
list_get(list, 1);  // Returns a char equalling b
list_get(list, 2);  // Returns a short equalling c

// When you are finished with it, free the memory used by the list.
free(list);
```

**Further documentation coming soon ...**


## Who?
CList was originally developed by Charlotte Lockett as an experiment in pushing the boundaries of C's static typing as much as possible.

Both it and its concept (as far as being implemented for use in C) are released under the [MIT License](https://github.com/char-lock/clist/blob/main/LICENSE).


## What?
The proof-of-concept functionality for CList is currently available -- that is to say, data can be stored and retrieved with its original typing.

However, there are plans to implement all of the features provided by the Python-style list as much as possible. The currently unimplemented features that are planned are:

* Quality-of-Life methods: set, pop, remove, insert, clear, sort, reverse, and index_of.

* General bounds checking to minimise the potential for encountering errors or memory-management problems.

* Reverse traversal, where a negative index will begin at the end of the array.

* Other improvements or ideas as they are brought to light.


## Why?
At first blush, the list data structure is by no means a perfect one. It has a decently high overhead for memory, and it doesn't really store any one set of data efficiently. Instead, the list is an extremely flexible, general-purpose data structure useful for stockpiling data of any type for future use. It provides an easy-to-use and type-agnostic place to store what you need.

While it is unlikely to see much use outside of niche applications, it was a worthwhile experiment into what is possible within C, even when it seems to break the rules.
