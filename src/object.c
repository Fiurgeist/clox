#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(type, objectType) (type*)allocateObject(sizeof(type), objectType)

static Obj* allocateObject(size_t size, ObjType type) {
  Obj *object = (Obj*)reallocate(NULL, 0, size);
  object->type = type;
  object->next = vm.objects;

  vm.objects = object;
  return object;
}

static ObjString* allocateString(char *chars, int length) {
  ObjString *string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
  string->length = length;
  string->chars = chars;

  return string;
}

ObjString* takeString(char *chars, int length) {
  return allocateString(chars, length);
}

ObjString* copyString(const char *chars, int length) {
  char *heapChars = ALLOCATE(char, length + 1);
  memcpy(heapChars, chars, length);
  heapChars[length] = '\0';

  return allocateString(heapChars, length);
}

void printObject(Value value) {
  switch (OBJ_TYPE(value)) {
  case OBJ_STRING: printf("%s", AS_CSTRING(value)); break;
  default:
    printf("Unhandled object type &d\n", OBJ_TYPE(value));
  }
}

bool objectsEqual(Value a, Value b) {
  if (OBJ_TYPE(a) != OBJ_TYPE(b)) {
    return false;
  }

  switch (OBJ_TYPE(a)) {
  case OBJ_STRING:
    ObjString *aString = AS_STRING(a);
    ObjString *bString = AS_STRING(b);
    return aString->length == bString->length &&
      memcmp(aString->chars, bString->chars, aString->length) == 0;
  default:
    printf("Unhandled object type &d\n", OBJ_TYPE(a));
    break;
  }
}
