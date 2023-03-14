// Copyright 2023 Charlotte Lockett
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// “Software”), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//

///
/// A list is a compound data structure built to emulate the functionality
/// provided by a Python-style list. There are some parts that are impossible
/// to emulate using C, but many of the same features have been able to be
/// ported over without too much trouble.
///

#ifndef __CLIST__H__
#define __CLIST__H__

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

enum TYPE {
  TYPE_UNKNOWN = 0,
  TYPE_CHAR, TYPE_CHAR_SIGNED, TYPE_CHAR_UNSIGNED,
  TYPE_SHORT_SIGNED, TYPE_SHORT_UNSIGNED,
  TYPE_INT_SIGNED, TYPE_INT_UNSIGNED,
  TYPE_LONG_SIGNED, TYPE_LONG_UNSIGNED,
  TYPE_LONG_LONG_SIGNED, TYPE_LONG_LONG_UNSIGNED,
  TYPE_FLOAT,
  TYPE_DOUBLE,
  TYPE_DOUBLE_LONG
};
typedef enum TYPE TYPE_T;

typedef struct LIST {
  size_t size;
  size_t length;
  void *data;
  int *el_types;
  size_t *el_sizes;
  size_t *el_offsets;
} LIST_T;

///
/// Returns a value from the TYPE enum defining the type of a provided value.
///
#define get_type(x) _Generic((x),                                                         \
  char: TYPE_CHAR, signed char: TYPE_CHAR_SIGNED, unsigned char: TYPE_CHAR_UNSIGNED,      \
  short: TYPE_SHORT_SIGNED, unsigned short: TYPE_SHORT_UNSIGNED,                          \
  int: TYPE_INT_SIGNED, unsigned int: TYPE_INT_UNSIGNED,                                  \
  long: TYPE_LONG_SIGNED, unsigned long: TYPE_LONG_UNSIGNED,                              \
  long long: TYPE_LONG_LONG_SIGNED, unsigned long long: TYPE_LONG_LONG_UNSIGNED,          \
  float: TYPE_FLOAT,                                                                      \
  double: TYPE_DOUBLE,                                                                    \
  long double: TYPE_DOUBLE_LONG)

///
/// Returns the typed value at the requested list index.
///
/// Defining this as a macro allows us to bypass C's inherent static-typing and
/// dynamically type return values. While it makes the list less flexible in terms
/// of initial items that can be stored, the types are extendable as needed.
///
#define list_get(x, y)                                                                    \
  ( x->el_types[y] == TYPE_CHAR                                                           \
      ? *(char *)((x->data + x->el_offsets[y]))                                           \
  : x->el_types[y] == TYPE_CHAR_SIGNED                                                    \
      ? *(signed char *)((x->data + x->el_offsets[y]))                                    \
  : x->el_types[y] == TYPE_CHAR_UNSIGNED                                                  \
      ? *(unsigned char *)((x->data + x->el_offsets[y]))                                  \
  : x->el_types[y] == TYPE_SHORT_SIGNED                                                   \
      ? *(short *)((x->data + x->el_offsets[y]))                                          \
  : x->el_types[y] == TYPE_SHORT_UNSIGNED                                                 \
      ? *(unsigned short *)((x->data + x->el_offsets[y]))                                 \
  : x->el_types[y] == TYPE_INT_SIGNED                                                     \
      ? *(int *)((x->data + x->el_offsets[y]))                                            \
  : x->el_types[y] == TYPE_INT_UNSIGNED                                                   \
      ? *(unsigned int *)((x->data + x->el_offsets[y]))                                   \
  : x->el_types[y] == TYPE_LONG_SIGNED                                                    \
      ? *(long *)((x->data + x->el_offsets[y]))                                           \
  : x->el_types[y] == TYPE_LONG_UNSIGNED                                                  \
      ? *(unsigned long *)((x->data + x->el_offsets[y]))                                  \
  : x->el_types[y] == TYPE_LONG_LONG_SIGNED                                               \
      ? *(long long *)((x->data + x->el_offsets[y]))                                      \
  : x->el_types[y] == TYPE_LONG_LONG_UNSIGNED                                             \
      ? *(unsigned long long *)((x->data + x->el_offsets[y]))                             \
  : x->el_types[y] == TYPE_FLOAT                                                          \
      ? *(float *)((x->data + x->el_offsets[y]))                                          \
  : x->el_types[y] == TYPE_DOUBLE                                                         \
      ? *(double *)((x->data + x->el_offsets[y]))                                         \
  : x->el_types[y] == TYPE_DOUBLE_LONG                                                    \
      ? *(long double *)((x->data + x->el_offsets[y]))                                    \
  : 0 )

  ///
  /// Creates and allocates a new list structure into memory.
  ///
  LIST_T *list_new(void);

  ///
  /// Changes the value at a provided index.
  ///
  /// (UNIMPLEMENTED)
  ///
  #define list_set(x, y, z) _list_set(x, y, z, sizeof(z), get_type(z))

  ///
  /// Internal function used to set a value within a list.
  ///
  /// (UNIMPLEMENTED)
  ///
  void _list_set(LIST_T *list, size_t index, void *value, size_t value_sz, int value_type);

  ///
  /// Retrieves the last element of a list, removes it, and returns it.
  ///
  /// (UNIMPLEMENTED)
  ///

  #define list_pop(x) 0

  ///
  /// Appends a provided value to the end of a list.
  ///
  #define list_append(x, y) _list_append(x, &y, sizeof(y), get_type(y))

  ///
  /// Internal function used to append a value to the end of a list.
  ///
  void _list_append(LIST_T *list, void *value, size_t value_sz, int value_type);

  ///
  /// Removes an element at a provided index and shifts the entire list over by one.
  ///
  /// (UNIMPLEMENTED)
  ///
  void list_remove(LIST_T *list, size_t index);

  ///
  /// Inserts an element at a provided index and shifts the entire list over by one.
  ///
  /// (UNIMPLEMENTED)
  ///
  #define list_insert(x, y, z) _list_insert(x, y, z, sizeof(z), get_type(z))

  ///
  /// Internal function used to insert a value into an index of a list.
  ///
  /// (UNIMPLEMENTED)
  ///
  void _list_insert(LIST_T *list, size_t index, void *value, size_t value_sz, int value_type);

  ///
  /// Clears all of the data stored within a list.
  ///
  /// (UNIMPLEMENTED)
  ///
  void list_clear(LIST_T *list);

  ///
  /// Sorts all of the data stored within a list using a naive alpha-numeric approach.
  ///
  /// (UNIMPLEMENTED)
  ///
  void list_sort(LIST_T *list);

  ///
  /// Reverses the elements stored within a list.
  ///
  /// (UNIMPLEMENTED)
  ///
  void list_reverse(LIST_T *list);

  ///
  /// Searches a list for an item and returns its index if it exists.
  ///
  /// (UNIMPLEMENTED)
  ///
  #define list_index_of(x, y) _list_index_of(x, y, sizeof(y), get_type(y))

  ///
  /// Internal function to retrieve the index of an item within a list.
  ///
  /// (UNIMPLEMENTED)
  ///
  ssize_t _list_index_of(LIST_T *list, void *value, size_t value_sz, int value_type);

  ///
  /// Frees the memory used by a list structure.
  ///
  void list_free(LIST_T *list);

#endif // __CLIST__H__
