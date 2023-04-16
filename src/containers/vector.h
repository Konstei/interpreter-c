#pragma once

#include <stdlib.h>

#define DECLARE_VECTOR(type) typedef struct { \
  unsigned long long length; \
  unsigned long long bytesize; \
  type *data; \
} Vector_##type; \
Vector_##type *vectorCreate_##type(unsigned long long initialSize, type *initialElements); \
void vectorPush_##type(Vector_##type *v, type element); \
void vectorFree_##type(Vector_##type *v); \
Vector_##type *vectorSlice_##type(Vector_##type *v, unsigned long long start, unsigned long long end);

#define DEFINE_VECTOR(type) \
Vector_##type *vectorCreate_##type(unsigned long long initialSize, type *initialElements) { \
  Vector_##type *v = malloc(sizeof(Vector_##type)); \
  v->length = initialSize; \
  v->bytesize = initialSize * sizeof(type); \
  v->data = malloc(v->bytesize); \
  for (unsigned long long i=0; i<initialSize; i++) v->data[i] = initialElements[i]; \
  return v; \
} \
void vectorPush_##type(Vector_##type *v, type element) { \
  v->length++; \
  v->bytesize += sizeof(type); \
  v->data = realloc(v->data, v->bytesize); \
  v->data[v->length-1] = element; \
} \
void vectorFree_##type(Vector_##type *v) { \
  free(v->data); \
  free(v); \
} \
Vector_##type *vectorSlice_##type(Vector_##type *v, unsigned long long start, unsigned long long end) { \
  Vector_##type *slice = malloc(sizeof(Vector_##type)); \
  slice->length = end - start; \
  slice->bytesize = slice->length * sizeof(type); \
  slice->data = malloc(slice->bytesize); \
  for (unsigned long long i=0; i<slice->length; i++) slice->data[i] = v->data[start + i]; \
  return slice; \
}


#define Vector(type) Vector_##type
#define vectorCreate(type) vectorCreate_##type
#define vectorPush(type) vectorPush_##type
#define vectorFree(type) vectorFree_##type
#define vectorSlice(type) vectorSlice_##type