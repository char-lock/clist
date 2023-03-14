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

# include "./clist.h"

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

void _list_append(LIST_T *list, void *value, size_t value_sz, int value_type) {
  // printf("[DEBUG]: _list_append:52 entered -- size: %i, type: %i\n", value_sz, value_type);
  // Reallocate memory to allow for the new element.
  size_t new_size = list->size + value_sz;
  list->data = realloc(list->data, new_size);
  // printf("[DEBUG]: _list_append:52 - list->data reallocated to %i\n", new_size);
  // Calculate where to store data next.
  void *data_pos = (char *)(list->data + list->size);
  // printf("[DEBUG]: _list_append:52 - next data position is %u\n", data_pos);
  // Copy value into the data array.
  memcpy(data_pos, value, value_sz);
  // printf("[DEBUG]: _list_append:52 - value %u copied into data.\n", *(unsigned long *)value);
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

void list_free(LIST_T *list) {
  free(list->el_offsets);
  free(list->el_sizes);
  free(list->el_types);
  free(list->data);
  free(list);
}
