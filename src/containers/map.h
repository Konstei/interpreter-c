#pragma once

#include <stdlib.h>

#define DECLARE_MAP(keytype, valuetype) typedef struct { \
  unsigned long long length; \
  unsigned long long bytesize; \
  keytype *keys; \
  valuetype *values; \
} Map_##keytype##_##valuetype; \
Map_##keytype##_##valuetype *mapCreate_##keytype##_##valuetype(unsigned long long initialSize, keytype *keys, valuetype *values, int (*compare)(keytype*, keytype*)); \
void mapSet_##keytype##_##valuetype(Map_##keytype##_##valuetype *m, keytype key, valuetype value); \
valuetype mapGet_##keytype##_##valuetype(Map_##keytype##_##valuetype *m, keytype key); \
short mapHas_##keytype##_##valuetype(Map_##keytype##_##valuetype *m, keytype key); \
void mapFree_##keytype##_##valuetype(Map_##keytype##_##valuetype *m);

#define DEFINE_MAP(keytype, valuetype) \
Map_##keytype##_##valuetype *mapCreate_##keytype##_##valuetype(unsigned long long initialSize, keytype *keys, valuetype *values, int (*compare)(keytype, keytype)) { \
  Map_##keytype##_##valuetype *m = (Map_##keytype##_##valuetype*)malloc(sizeof(Map_##keytype##_##valuetype)); \
  m->length = initialSize; \
  m->bytesize = initialSize * sizeof(keytype) + initialSize * sizeof(valuetype); \
  m->keys = (keytype*)malloc(initialSize * sizeof(keytype)); \
  m->values = (valuetype*)malloc(initialSize * sizeof(valuetype)); \
  memcpy(m->keys, keys, initialSize * sizeof(keytype)); \
  memcpy(m->values, values, initialSize * sizeof(valuetype)); \
  unsigned long long currSize, leftStart, mid, rightEnd, i, j, k, n1, n2; \
  for (currSize = 1; currSize < initialSize; currSize *= 2) { \
    for (leftStart = 0; leftStart < initialSize-1; leftStart += 2*currSize) { \
      mid = (leftStart + currSize - 1 < initialSize-1) ? leftStart + currSize - 1 : initialSize-1; \
      rightEnd = (leftStart + 2*currSize - 1 < initialSize-1) ? leftStart + 2*currSize - 1 : initialSize-1; \
      n1 = mid - leftStart + 1; \
      n2 = rightEnd - mid; \
      keytype L[n1], R[n2]; \
      for (i=0; i<n1; i++) L[i] = m->keys[leftStart + i]; \
      for (j=0; j<n2; j++) R[j] = m->keys[mid + j + 1]; \
      i = 0; \
      j = 0; \
      k = leftStart; \
      /* also sort values */ \
      while (i < n1 && j < n2) { \
        if (compare(L[i], R[j]) < 0) { \
          m->keys[k] = L[i]; \
          i++; \
        } else { \
          m->keys[k] = R[j]; \
          j++; \
        } \
        k++; \
      } \
      while (i < n1) { \
        m->keys[k] = L[i]; \
        i++; \
        k++; \
      } \
      while (j < n2) { \
        m->keys[k] = R[j]; \
        j++; \
        k++; \
      } \
    } \
  } \
  \
  return m; \
} \
void mapSet_##keytype##_##valuetype(Map_##keytype##_##valuetype *m, keytype key, valuetype value) { \
  for (unsigned long long i=0; i<m->length; i++) { \
    if (m->keys[i] == key) { \
      m->values[i] = value; \
      return; \
    } \
  } \
  m->length++; \
  m->bytesize += sizeof(keytype) + sizeof(valuetype); \
  m->keys = (keytype*)realloc(m->keys, m->bytesize); \
  m->values = (valuetype*)realloc(m->values, m->bytesize); \
  m->keys[m->length-1] = key; \
  m->values[m->length-1] = value; \
} \
valuetype mapGet_##keytype##_##valuetype(Map_##keytype##_##valuetype *m, keytype key) { \
  for (unsigned long long i=0; i<m->length; i++) { \
    if (m->keys[i] == key) return m->values[i]; \
  } \
  return (valuetype)NULL; \
} \
short mapHas_##keytype##_##valuetype(Map_##keytype##_##valuetype *m, keytype key) { \
  for (unsigned long long i=0; i<m->length; i++) { \
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