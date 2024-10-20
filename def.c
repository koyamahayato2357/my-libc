#include "def.h"
#include "testing.h"
#include <stdlib.h>

void free4drop(void **pp) { free(*pp); }

test(leak) { drop void *p = malloc(100); }
