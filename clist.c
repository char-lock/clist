#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define __CLIST_DEBUG 1

#define get_type(x) _Generic((x),                                                         \
  char: TYPE_CHAR, signed char: TYPE_CHAR_SIGNED, unsigned char: TYPE_CHAR_UNSIGNED,      \
  short: TYPE_SHORT_SIGNED, unsigned short: TYPE_SHORT_UNSIGNED,                          \
  int: TYPE_INT_SIGNED, unsigned int: TYPE_INT_UNSIGNED,                                  \
  long: TYPE_LONG_SIGNED, unsigned long: TYPE_LONG_UNSIGNED,                              \
  long long: TYPE_LONG_LONG_SIGNED, unsigned long long: TYPE_LONG_LONG_UNSIGNED,          \
  float: TYPE_FLOAT,                                                                      \
  double: TYPE_DOUBLE,                                                                    \
  long double: TYPE_DOUBLE_LONG)

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

LIST_T *list_new(void) {
  LIST_T *list = (LIST_T*) malloc(sizeof(LIST_T));
  list->size = 0;
  list->length = 0;
  list->data = malloc(1);
  list->el_types = (int*) malloc(sizeof(int));
  list->el_sizes = (size_t*) malloc(sizeof(size_t));
  list->el_offsets = (size_t*) malloc(sizeof(size_t));
  list->el_offsets[0] = 0;
  return list;
}

#define list_append(x, y) _list_append(x, &y, sizeof(y), get_type(y))

void _list_append(LIST_T *list, void *value, size_t value_sz, int value_type) {
  printf("[DEBUG]: _list_append:52 entered -- size: %i, type: %i\n", value_sz, value_type);

  // Reallocate memory to allow for the new element.
  size_t new_size = list->size + value_sz;
  list->data = realloc(list->data, new_size);
  printf("[DEBUG]: _list_append:52 - list->data reallocated to %i\n", new_size);

  // Calculate where to store data next.
  void *data_pos = (char *)(list->data + list->size);
  printf("[DEBUG]: _list_append:52 - next data position is %i\n", data_pos);
  // Copy value into the data array.
  memcpy(data_pos, value, value_sz);
  printf("[DEBUG]: _list_append:52 - value copied into data.\n");

  // Increment list metadata.
  list->size += value_sz;
  list->length += 1;
  
  // Reallocate the types array and store the new type ID.
  list->el_types = (int*)realloc(list->el_types, sizeof(int) * list->length);
  list->el_types[list->length - 1] = value_type;

  // Reallocate the size array and store the new element's size.
  list->el_sizes = (size_t*)realloc(list->el_types, sizeof(size_t) * list->length);
  list->el_sizes[list->length - 1] = value_sz;

  // Reallocate the offset array and store the current element's offset.
  list->el_offsets = (size_t*)realloc(list->el_offsets, sizeof(size_t) * list->length);
  if (list->length > 0)
    list->el_offsets[list->length - 1] = list->length == 1 ? 0 : (new_size - value_sz);
}

#define list_get(x, y)                                                                                  \
  ( x->el_types[y] == TYPE_CHAR               ? *(char *)((x->data + x->el_offsets[y]))                \
  : x->el_types[y] == TYPE_CHAR_SIGNED        ? *(signed char *)((x->data + x->el_offsets[y]))         \
  : x->el_types[y] == TYPE_CHAR_UNSIGNED      ? *(unsigned char *)((x->data + x->el_offsets[y]))       \
  : x->el_types[y] == TYPE_SHORT_SIGNED       ? *(short *)((x->data + x->el_offsets[y]))               \
  : x->el_types[y] == TYPE_SHORT_UNSIGNED     ? *(unsigned short *)((x->data + x->el_offsets[y]))      \
  : x->el_types[y] == TYPE_INT_SIGNED         ? *(int *)((x->data + x->el_offsets[y]))                 \
  : x->el_types[y] == TYPE_INT_UNSIGNED       ? *(unsigned int *)((x->data + x->el_offsets[y]))        \
  : x->el_types[y] == TYPE_LONG_SIGNED        ? *(long *)((x->data + x->el_offsets[y]))                \
  : x->el_types[y] == TYPE_LONG_UNSIGNED      ? *(unsigned long *)((x->data + x->el_offsets[y]))       \
  : x->el_types[y] == TYPE_LONG_LONG_SIGNED   ? *(long long *)((x->data + x->el_offsets[y]))           \
  : x->el_types[y] == TYPE_LONG_LONG_UNSIGNED ? *(unsigned long long *)((x->data + x->el_offsets[y]))  \
  : x->el_types[y] == TYPE_FLOAT              ? *(float *)((x->data + x->el_offsets[y]))               \
  : x->el_types[y] == TYPE_DOUBLE             ? *(double *)((x->data + x->el_offsets[y]))              \
  : x->el_types[y] == TYPE_DOUBLE_LONG        ? *(long double *)((x->data + x->el_offsets[y]))         \
  : 0 )

void list_free(LIST_T *list) {
  free(list->el_offsets);
  free(list->el_sizes);
  free(list->el_types);
  free(list->data);
  free(list);
}

int main() {
  LIST_T *list = list_new();
  printf("made new list\n");
  int a = 32767;
  char b = 'b';
  list_append(list, a);
  printf("appended a\n");
  list_append(list, b);
  printf("appended b\n");
  int c = list_get(list, 0);
  printf("got list[0]\n");
  char d = list_get(list, 1);
  printf("got list[1]\n");
  printf("a: %i, b: %i ... c: %i, d: %i\n", a, b, c, d);
  exit(0);
}
