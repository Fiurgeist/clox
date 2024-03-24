#include <stdio.h>

#include "object.h"
#include "memory.h"
#include "value.h"

void initValueArray(ValueArray *array) {
  array->capacity = 0;
  array->count = 0;
  array->values = NULL;
}

void writeValueArray(ValueArray *array, Value value) {
  if (array->count >= array->capacity) {
    int oldCapacity = array->capacity;
    array->capacity = GROW_CAPACITY(oldCapacity);
    array->values = GROW_ARRAY(Value, array->values, oldCapacity, array->capacity);
  }
  array->values[array->count] = value;
  array->count++;
}

void freeValueArray(ValueArray *array) {
  FREE_ARRAY(Value, array->values, array->capacity);
  initValueArray(array);
}

void printValue(Value value) {
#ifdef NAN_BOXING
  if (IS_BOOL(value)) {
    printf(AS_BOOL(value) ? "true" : "false");
  } else if (IS_NIL(value)) {
    printf("nil");
  } else if (IS_NUMBER(value)) {
    printf("%g", AS_NUMBER(value));
  } else if (IS_OBJ(value)) {
    printObject(value);
  } else {
    printf("Unhandled value type of value '&d'\n", value);
  }
#else
  switch (value.type) {
  case VAL_BOOL: printf(AS_BOOL(value) ? "true" : "false"); break;
  case VAL_NIL: printf("nil"); break;
  case VAL_NUMBER: printf("%g", AS_NUMBER(value)); break;
  case VAL_OBJ: printObject(value); break;
  default:
    printf("Unhandled value type &d\n", value.type);
  }
#endif
}

bool valuesEqual(Value a, Value b) {
#ifdef NAN_BOXING
  // IEEE 754: NANs should not be equal, so numbers need to be converted to doubles to correctly check that.
  if (IS_NUMBER(a) && IS_NUMBER(b)) {
    return AS_NUMBER(a) == AS_NUMBER(b);
  }

  return a == b;
#else
  if (a.type != b.type) {
    return false;
  }

  switch (a.type)
  {
  case VAL_BOOL:   return AS_BOOL(a) == AS_BOOL(b);
  case VAL_NIL:    return true;
  case VAL_NUMBER: return AS_NUMBER(a) == AS_NUMBER(b);
  case VAL_OBJ:    return AS_OBJ(a) == AS_OBJ(b);
  default:
    printf("Unhandled value type &d\n", a.type);
  }
#endif
}
