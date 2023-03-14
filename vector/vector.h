#pragma once

#include <stdlib.h>

#define DECLARE_VECTOR(type) typedef struct { \
  unsigned long long size; \
  unsigned long long bytesize; \
  type *data; \
} Vector_##type; \
Vector_##type *vectorCreate_##type(unsigned long long initialSize, type *initialElements); \
void vectorPush_##type(Vector_##type *v, type element); \
void vectorFree_##type(Vector_##type *v); \
Vector_##type *vectorSlice_##type(Vector_##type *v, unsigned long long start, unsigned long long end);

#define DEFINE_VECTOR(type) \
Vector_##type *vectorCreate_##type(unsigned long long initialSize, type *initialElements) { \
  Vector_##type *v = (Vector_##type*)malloc(sizeof(Vector_##type)); \
  v->size = initialSize; \
  v->bytesize = initialSize * sizeof(type); \
  v->data = (type*)malloc(v->bytesize); \
  for (unsigned long long i=0; i<initialSize; i++) v->data[i] = initialElements[i]; \
  return v; \
} \
void vectorPush_##type(Vector_##type *v, type element) { \
  v->size++; \
  v->bytesize += sizeof(type); \
  v->data = (type*)realloc(v->data, v->bytesize); \
  v->data[v->size-1] = element; \
} \
void vectorFree_##type(Vector_##type *v) { \
  free(v->data); \
  free(v); \
} \
Vector_##type *vectorSlice_##type(Vector_##type *v, unsigned long long start, unsigned long long end) { \
  Vector_##type *slice = (Vector_##type*)malloc(sizeof(Vector_##type)); \
  slice->size = end - start; \
  slice->bytesize = slice->size * sizeof(type); \
  slice->data = (type*)malloc(slice->bytesize); \
  for (unsigned long long i=0; i<slice->size; i++) slice->data[i] = v->data[start + i]; \
  return slice; \
}


#define Vector(type) Vector_##type
#define vectorCreate(type) vectorCreate_##type
#define vectorPush(type) vectorPush_##type
#define vectorFree(type) vectorFree_##type
#define vectorSlice(type) vectorSlice_##type