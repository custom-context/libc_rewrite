#include "native.h"

#include <stdlib.h>

_Noreturn void NAMESPACE_NATIVE_PROCESS(abort)(void) {
    abort();
}
