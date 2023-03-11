#pragma once

#include <stdlib.h>

#define DECLARE_MAP(keytype, valuetype) typedef struct { \
  unsigned long long size; \
  unsigned long long bytesize; \
  keytype *keys; \
  valuetype *values; \
} Map_##keytype##_##valuetype; \
Map_##keytype##_##valuetype *mapCreate_##keytype##_##valuetype(unsigned long long initialSize, keytype *keys, valuetype *values); \
void mapSet_##keytype##_##valuetype(Map_##keytype##_##valuetype *m, keytype key, valuetype value); \
valuetype mapGet_##keytype##_##valuetype(Map_##keytype##_##valuetype *m, keytype key); \
short mapHas_##keytype##_##valuetype(Map_##keytype##_##valuetype *m, keytype key); \
void mapFree_##keytype##_##valuetype(Map_##keytype##_##valuetype *m);

#define DEFINE_MAP(keytype, valuetype) \
Map_##keytype##_##valuetype *mapCreate_##keytype##_##valuetype(unsigned long long initialSize, keytype *keys, valuetype *values) { \
  Map_##keytype##_##valuetype *m = (Map_##keytype##_##valuetype*)malloc(sizeof(Map_##keytype##_##valuetype)); \
  m->size = initialSize; \
  m->bytesize = initialSize * sizeof(keytype) + initialSize * sizeof(valuetype); \
  m->keys = (keytype*)malloc(initialSize * sizeof(keytype)); \
  m->values = (valuetype*)malloc(initialSize * sizeof(valuetype)); \
  return m; \
} \
void mapSet_##keytype##_##valuetype(Map_##keytype##_##valuetype *m, keytype key, valuetype value) { \
  for (unsigned long long i=0; i<m->size; i++) { \
    if (m->keys[i] == key) { \
      m->values[i] = value; \
      return; \
    } \
  } \
  m->size++; \
  m->bytesize += sizeof(keytype) + sizeof(valuetype); \
  m->keys = (keytype*)realloc(m->keys, m->bytesize); \
  m->values = (valuetype*)realloc(m->values, m->bytesize); \
  m->keys[m->size-1] = key; \
  m->values[m->size-1] = value; \
} \
valuetype mapGet_##keytype##_##valuetype(Map_##keytype##_##valuetype *m, keytype key) { \
  for (unsigned long long i=0; i<m->size; i++) { \
    if (m->keys[i] == key) return m->values[i]; \
  } \
  return (valuetype)NULL; \
} \
short mapHas_##keytype##_##valuetype(Map_##keytype##_##valuetype *m, keytype key) { \
  for (unsigned long long i=0; i<m->size; i++) { \
    if (m->keys[i] == key) return 1; \
  } \
  return 0; \
} \
void mapFree_##keytype##_##valuetype(Map_##keytype##_##valuetype *m) { \
  free(m->keys); \
  free(m->values); \
  free(m); \
}

#define Map(keytype, valuetype) Map_##keytype##_##valuetype
#define mapCreate(keytype, valuetype) mapCreate_##keytype##_##valuetype
#define mapSet(keytype, valuetype) mapSet_##keytype##_##valuetype
#define mapGet(keytype, valuetype) mapGet_##keytype##_##valuetype
#define mapHas(keytype, valuetype) mapHas_##keytype##_##valuetype
#define mapFree(keytype, valuetype) mapFree_##keytype##_##valuetype