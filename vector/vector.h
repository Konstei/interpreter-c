#pragma once

#include <stdlib.h>

#define DECLARE_VECTOR(type) typedef struct { \
  unsigned int length; \
  size_t bytesize; \
  type *data; \
} Vector_##type; \
Vector_##type *vectorCreate_##type(unsigned int initialSize, type *initialElements); \
void vectorPush_##type(Vector_##type *v, type element); \
void vectorFree_##type(Vector_##type *v); \
Vector_##type *vectorSlice_##type(Vector_##type *v, unsigned int start, unsigned int end);

#define DEFINE_VECTOR(type) \
Vector_##type *vectorCreate_##type(unsigned int initialSize, type *initialElements) { \
  Vector_##type *v = (Vector_##type*)malloc(sizeof(Vector_##type)); \
  v->length = initialSize; \
  v->bytesize = initialSize * sizeof(type); \
  v->data = (type*)malloc(v->bytesize); \
  for (unsigned int i=0; i<initialSize; i++) v->data[i] = initialElements[i]; \
  return v; \
} \
void vectorPush_##type(Vector_##type *v, type element) { \
  v->length++; \
  v->bytesize += sizeof(type); \
  v->data = (type*)realloc(v->data, v->bytesize); \
  v->data[v->length-1] = element; \
} \
void vectorFree_##type(Vector_##type *v) { \
  free(v->data); \
  free(v); \
} \
Vector_##type *vectorSlice_##type(Vector_##type *v, unsigned int start, unsigned int end) { \
  Vector_##type *slice = (Vector_##type*)malloc(sizeof(Vector_##type)); \
  slice->length = end - start; \
  slice->bytesize = slice->length * sizeof(type); \
  slice->data = (type*)malloc(slice->bytesize); \
  for (unsigned int i=0; i<slice->length; i++) slice->data[i] = v->data[start + i]; \
  return slice; \
}


#define Vector(type) Vector_##type
#define vectorCreate(type, initialSize, initialElements) vectorCreate_##type(initialSize, initialElements)
#define vectorPush(type, vector, element) vectorPush_##type(vector, element)
#define vectorFree(type, vector) vectorFree_##type(vector)
#define vectorSlice(type, vector, start, end) vectorSlice_##type(vector, start, end)