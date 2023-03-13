# clist
**clist** is a header-only library for a list data structure written for C.

Note: As it stands, there is very little difference between the list as it exists now and a C++-style vector. This is intended to change in the future, and the list will reflect a more similar structure as a Python-style list.


## Getting Started
Add the header file into your includes and use the following syntax to generate a typed list (the below example is for an int list):

```
list(int);

int main() {
  int_list l;
  int_list_init(&l);
  int_list_append(&l, 1);
  int_list_set(&l, 0, 2);
  int_list_get(&l, 0);
  int_list_find(&l, 2);
}
```


## To-Do
[ ] Implement ability to hold multiple types within a single list. (remove necessity to generate typed lists)
[ ] Implement reverse indexing (ability to loop around to the last value with -1)
[ ] Implement safety checks for indexing.
[ ] Implement list constructor from an array.
[ ] Implement the following quality-of-life methods: clear, copy, count, extend, index, insert, pop, remove, reverse, sort
