#include <stddef.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>

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
  LIST_T *list = malloc(sizeof(LIST_T));
  list->size = 1;
  list->length = 0;
  list->data = malloc(1);
  list->el_types = malloc(sizeof(int));
  list->el_sizes = malloc(sizeof(size_t));
  list->el_offsets = malloc(sizeof(size_t));
  list->el_offsets[0] = 0;
  return list;
}

#define list_append(x, y) _list_append(x, &y, sizeof(y), get_type(y))

void _list_append(LIST_T *list, void *value, size_t value_sz, int value_type) {
  printf("list_append :: value_sz: %i, value_type: %i\n", value_sz, value_type);
  list->data = realloc(list->data, list->size + value_sz + 1);
  printf("data realloc'd\n");
  void *position = (char *)(list->data) + list->size;
  printf("logged position\n");
  memcpy(position, (void *)value, value_sz);
  printf("copied memory\n");
  list->size += value_sz;
  printf("updated size\n");
  list->length += 1;
  list->el_types = realloc(list->el_types, sizeof(int) * list->length);
  list->el_types[list->length - 1] = value_type;
  list->el_sizes = realloc(list->el_types, sizeof(size_t) * list->length);
  list->el_sizes[list->length - 1] = value_sz;
  list->el_offsets = realloc(list->el_offsets, sizeof(size_t) * list->length);
  if (list->length > 0) {
    list->el_offsets[list->length] = list->el_offsets[list->length - 1] + value_sz;
  } else {
    list->el_offsets[0] = 0;
  }
}

#define list_get(x, y) (                                                                                          \
  x->el_types[y] == TYPE_CHAR ? ((char *)(x->data + x->el_offsets[y]))                                                               \
  : x->el_types[y] == TYPE_CHAR_SIGNED ? ((signed char *)x->data + x->el_offsets[y])                                 \
  : x->el_types[y] == TYPE_CHAR_UNSIGNED ? ((((unsigned char *)x->data + (sizeof(unsigned char) * y))))                                \
  : x->el_types[y] == TYPE_SHORT_SIGNED ? ((((short *)x->data + (sizeof(short) * y))))                                \
  : x->el_types[y] == TYPE_SHORT_UNSIGNED ? ((((unsigned short *)x->data + (sizeof(short) * y))))                               \
  : x->el_types[y] == TYPE_INT_SIGNED ? ((((int *)x->data + x->el_offsets[y])))                                    \
  : x->el_types[y] == TYPE_INT_UNSIGNED ? ((((unsigned int *)x->data + (sizeof(int) * y))))                                   \
  : x->el_types[y] == TYPE_LONG_SIGNED ? ((signed long *)(((char *)x->data + x->el_offsets[y])))                                  \
  : x->el_types[y] == TYPE_LONG_UNSIGNED ? ((unsigned long *)(((char *)x->data + x->el_offsets[y])))                            \
  : x->el_types[y] == TYPE_LONG_LONG_SIGNED ? ((signed long long *)(((char *)x->data + x->el_offsets[y])))                         \
  : x->el_types[y] == TYPE_LONG_LONG_UNSIGNED ? ((unsigned long long *)(((char *)x->data + x->el_offsets[y])))                    \
  : x->el_types[y] == TYPE_FLOAT ? ((float *)(((char *)x->data + x->el_offsets[y])))                                                \
  : x->el_types[y] == TYPE_DOUBLE ? ((double *)(((char *)x->data + x->el_offsets[y])))                                               \
  : x->el_types[y] == TYPE_DOUBLE_LONG ? ((long double *)(((char *)x->data + x->el_offsets[y])))                                      \
  : NULL )

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
  int a = 0xfffff;
  char b = 'b';
  list_append(list, a);
  printf("appended a\n");
  list_append(list, b);
  printf("appended b\n");
  int c = list_get(list, 0);
  printf("got list[0]\n");
  char d = list_get(list, 1);
  printf("got list[1]\n");
  printf("offsets: %i %i %i %i\n", list->el_offsets[0], list->el_offsets[1], list->el_offsets[2], list->el_offsets[3]);
  printf("a: %i, b: %i ... c: %i, d: %i\n", a, b, c, d);
  exit(0);
}
