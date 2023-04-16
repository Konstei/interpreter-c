#pragma once

#include <stdlib.h>
#include "./vector.h"

#define DECLARE_MAP(keytype, valuetype) typedef struct { \
  unsigned long long length; \
  unsigned long long keybytesize; \
  unsigned long long valuebytesize; \
  keytype *keys; \
  valuetype *values; \
} Map_##keytype##_##valuetype; \
Map_##keytype##_##valuetype *mapCreate_##keytype##_##valuetype(unsigned long long initialSize, keytype *keys, valuetype *values); \
void mapSet_##keytype##_##valuetype(Map_##keytype##_##valuetype *m, keytype key, valuetype value); \
valuetype mapGet_##keytype##_##valuetype(Map_##keytype##_##valuetype *m, keytype key, valuetype fallback); \
int mapHas_##keytype##_##valuetype(Map_##keytype##_##valuetype *m, keytype key); \
Vector(keytype) *mapKeys_##keytype##_##valuetype(Map_##keytype##_##valuetype *m); \
Vector(valuetype) *mapValues_##keytype##_##valuetype(Map_##keytype##_##valuetype *m); \
void mapFree_##keytype##_##valuetype(Map_##keytype##_##valuetype *m);

#define DEFINE_MAP(keytype, valuetype, compare) \
Map_##keytype##_##valuetype *mapCreate_##keytype##_##valuetype(unsigned long long initialSize, keytype *keys, valuetype *values) { \
  Map_##keytype##_##valuetype *m = malloc(sizeof(Map_##keytype##_##valuetype)); \
  m->length = initialSize; \
  m->keybytesize = initialSize * sizeof(keytype); \
  m->valuebytesize = initialSize * sizeof(valuetype); \
  m->keys = malloc(m->keybytesize); \
  m->values = malloc(m->valuebytesize); \
  memcpy(m->keys, keys, m->keybytesize); \
  memcpy(m->values, values, m->valuebytesize); \
  unsigned long long currSize, leftStart, mid, rightEnd, i, j, k, n1, n2; \
  for (currSize = 1; currSize < initialSize; currSize *= 2) { \
    for (leftStart = 0; leftStart < initialSize-1; leftStart += 2*currSize) { \
      mid = (leftStart + currSize - 1 < initialSize-1) ? leftStart + currSize - 1 : initialSize-1; \
      rightEnd = (leftStart + 2*currSize - 1 < initialSize-1) ? leftStart + 2*currSize - 1 : initialSize-1; \
      n1 = mid - leftStart + 1; \
      n2 = rightEnd - mid; \
      keytype Lk[n1], Rk[n2], Lv[n1], Rv[n2]; \
      for (i=0; i<n1; i++) { \
        Lk[i] = m->keys[leftStart + i]; \
        Lv[i] = m->values[leftStart + i]; \
      } \
      for (j=0; j<n2; j++) { \
        Rk[j] = m->keys[mid + j + 1]; \
        Rv[j] = m->values[mid + j + 1]; \
      } \
      i = 0; \
      j = 0; \
      k = leftStart; \
      for (; i<n1 && j<n2; k++) { \
        if (compare(Lk[i], Rk[j]) <= 0) { \
          m->keys[k] = Lk[i]; \
          m->values[k] = Lv[i]; \
          i++; \
        } else { \
          m->keys[k] = Rk[j]; \
          m->values[k] = Rv[j]; \
          j++; \
        } \
      } \
      for (; i<n1; i++) { \
        m->keys[k] = Lk[i]; \
        m->values[k] = Lv[i]; \
        k++; \
      } \
      for (; j<n2; j++) { \
        m->keys[k] = Rk[j]; \
        m->values[k] = Rv[j]; \
        k++; \
      } \
    } \
  } \
  return m; \
} \
void mapSet_##keytype##_##valuetype(Map_##keytype##_##valuetype *m, keytype key, valuetype value) { \
  unsigned long long l = 0, r = m->length-1, mid, t; \
  while (l <= r) { \
    mid = (l+r)/2; \
    if (compare(m->keys[l], key) == 0) { \
      m->values[l] = value; \
      return; \
    } \
    if (compare(m->keys[mid], key) == 0) { \
      m->values[mid] = value; \
      return; \
    } \
    if (compare(m->keys[r], key) == 0) { \
      m->values[r] = value; \
      return; \
    } \
    if (compare(m->keys[mid], key) < 0) { \
      l = mid+1; \
      r--; \
    } else { \
      r = mid-1; \
      l++; \
    } \
    t = mid; \
  } \
  while (t < m->length && compare(m->keys[t], key) < 0) t++; \
  m->length++; \
  m->keybytesize += sizeof(keytype); \
  m->valuebytesize += sizeof(valuetype); \
  m->keys = realloc(m->keys, m->keybytesize); \
  m->values = realloc(m->values, m->valuebytesize); \
  for (unsigned long long i=m->length-1; i>t; i--) { \
    m->keys[i] = m->keys[i-1]; \
    m->values[i] = m->values[i-1]; \
  } \
  m->keys[t] = key; \
  m->values[t] = value; \
} \
valuetype mapGet_##keytype##_##valuetype(Map_##keytype##_##valuetype *m, keytype key, valuetype fallback) { \
  unsigned long long l = 0, r = m->length-1, mid; \
  while (l <= r) { \
    mid = (l+r)/2; \
    if (compare(m->keys[l], key) == 0) return m->values[l]; \
    if (compare(m->keys[mid], key) == 0) return m->values[mid]; \
    if (compare(m->keys[r], key) == 0) return m->values[r]; \
    if (compare(m->keys[mid], key) < 0) { \
      l = mid+1; \
      r--; \
    } else { \
      r = mid-1; \
      l++; \
    } \
  } \
  return fallback; \
} \
int mapHas_##keytype##_##valuetype(Map_##keytype##_##valuetype *m, keytype key) { \
  unsigned long long l = 0, r = m->length-1, mid; \
  while (l <= r) { \
    mid = (l+r)/2; \
    if (compare(m->keys[l], key) == 0 || compare(m->keys[mid], key) == 0 || compare(m->keys[r], key) == 0) return 1; \
    if (compare(m->keys[mid], key) < 0) { \
      l = mid+1; \
      r--; \
    } else { \
      r = mid-1; \
      l++; \
    } \
  } \
} \
Vector(keytype) *mapKeys_##keytype##_##valuetype(Map_##keytype##_##valuetype *m) { \
  Vector(keytype) *v = vectorCreate(keytype)(m->length, m->keys); \
  return v; \
} \
Vector(valuetype) *mapValues_##keytype##_##valuetype(Map_##keytype##_##valuetype *m) { \
  Vector(valuetype) *v = vectorCreate(valuetype)(m->length, m->values); \
  return v; \
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
#define mapKeys(keytype, valuetype) mapKeys_##keytype##_##valuetype
#define mapValues(keytype, valuetype) mapValues_##keytype##_##valuetype
#define mapFree(keytype, valuetype) mapFree_##keytype##_##valuetype