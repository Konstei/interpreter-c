#pragma once

#include <stdlib.h>

#define DECLARE_STACK(type) typedef struct { \
  unsigned long long length; \
  unsigned long long bytesize; \
  type *data; \
} Stack_##type; \
Stack_##type *stackCreate_##type(); \
void stackPush_##type(Stack_##type *v, type element); \
type stackPop_##type(Stack_##type *v); \
type stackPeek_##type(Stack_##type *v); \
void stackFree_##type(Stack_##type *v);

#define DEFINE_STACK(type) \
Stack_##type *stackCreate_##type() { \
  Stack_##type *s = malloc(sizeof(Stack_##type)); \
  s->length = 0; \
  s->bytesize = 0; \
  s->data = NULL; \
  return s; \
} \
void stackPush_##type(Stack_##type *s, type element) { \
  s->length++; \
  s->bytesize += sizeof(type); \
  s->data = realloc(s->data, s->bytesize); \
  s->data[s->length-1] = element; \
} \
type stackPop_##type(Stack_##type *s) { \
  type element = s->data[s->length-1]; \
  s->length--; \
  s->bytesize -= sizeof(type); \
  s->data = realloc(s->data, s->bytesize); \
  return element; \
} \
type stackPeek_##type(Stack_##type *s) { \
  return s->data[s->length-1]; \
} \
void stackFree_##type(Stack_##type *s) { \
  free(s->data); \
  free(s); \
}


#define Stack(type) Stack_##type
#define stackCreate(type) stackCreate_##type
#define stackPush(type) vectorPush_##type
#define stackPop(type) stackPop_##type
#define stackPeek(type) stackPeek_##type
#define stackFree(type) stackFree_##type