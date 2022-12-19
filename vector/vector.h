#pragma once

#define DEFINE_VECTOR(type) typedef struct { \
  unsigned int size; \
  size_t bytesize; \
  type *data; \
} Vector_##type; \
Vector_##type *vectorCreate_##type(unsigned int initialSize, type *initialElements) { \
  Vector_##type *v = malloc(sizeof(Vector_##type)); \
  v->size = initialSize; \
  v->bytesize = initialSize * sizeof(type); \
  v->data = malloc(v->bytesize); \
  for (unsigned int i=0; i<initialSize; i++) v->data[i] = initialElements[i]; \
  return v; \
} \
void vectorInsert_##type(Vector_##type *v, type element) { \
  v->size++; \
  v->bytesize += sizeof(type); \
  v->data = realloc(v->data, v->bytesize); \
  v->data[v->size-1] = element; \
} \
void vectorFree_##type(Vector_##type *v) { \
  free(v->data); \
  free(v); \
}

#define Vector(type) Vector_##type
#define vectorCreate(type, initialSize, initialElements) vectorCreate_##type(initialSize, initialElements)
#define vectorInsert(type, vector, element) vectorInsert_##type(vector, element)
#define vectorFree(type, vector) vectorFree_##type(vector)

// #define COMPARE_TYPES(type1, type2) _Generic((type1), type2: 1, default: 0)