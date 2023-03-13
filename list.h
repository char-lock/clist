// Copyright 2023 Charlotte Lockett
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this
// software and associated documentation files (the “Software”), to deal in the Software
// without restriction, including without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
// OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
#ifndef __CLIST__H__
#define __CLIST__H__

#include <stddef.h>
#include <malloc.h>

#define list_struct(T)                                                                    \
  typedef struct T##_list {                                                               \
    T *data;                                                                              \
    size_t capacity;                                                                      \
    size_t length;                                                                        \
  } T##_list;

#define list_init(T)                                                                      \
  void T##_vector_init(T##_list *_list) {                                                 \
    _list->capacity = 1;                                                                  \
    _list->data = malloc(sizeof(T) * vec->capacity);                                      \
    _list->length = 0;                                                                    \
  }

#define list_get(T)                                                                       \
  void *T##_list_get(T##_list *_list, size_t index) { return _list->data + index; }

#define list_set(T)                                                                       \
  void T##_list_set(T##_list *_list, size_t index, T data) {                              \
    _list->data[index] = data;                                                            \
  }

#define list_append(T)                                                                    \
  void T##_list_push(T##_list *_list, T data) {                                           \
    if (_list->length == _list->capacity) {                                               \
      _list->capcity *= 2;                                                                \
      _list->data = realloc(_list->data, sizeof(T) * _list->capacity);                    \
    }                                                                                     \
    T##_list_set(_list, _list->length++, data);                                           \
  }

#define list_find(T)                                                                      \
  ssize_t T##_list_find(T##_list *_list, T target) {                                      \
    for (size_t i = 0; i < _list->length; i++) {                                          \
      if (*(T*)T##_list_get(i) == target) {                                               \
        return i;                                                                         \
      }                                                                                   \
    }                                                                                     \
    return -1;                                                                            \
  }

#define list(T)                                                                           \
  list_struct(T);                                                                         \
  list_init(T) list_get(T) list_set(T) list_append(T)                                     \
  list_find(T)

#endif // __CLIST__H__
