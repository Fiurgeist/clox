#include <stdlib.h>

#include "memory.h"
#include "vm.h"

void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
  if (newSize == 0) {
    free(pointer);

    return NULL;
  }

  return realloc(pointer, newSize);
}

static void freeObject(Obj *object) {
  switch (object->type) {
  case OBJ_STRING:
    ObjString *string = (ObjString*)object;
    FREE_ARRAY(char, string->chars, string->length + 1);
    FREE(ObjString, object);
    break;
  default:
    printf("Unhandled object type &d\n", object->type);
    break;
  }
}

void freeObjects() {
  Obj *object = vm.objects;
  while (object != NULL) {
    Obj *next = object->next;
    freeObject(object);
    object = next;
  }
}
