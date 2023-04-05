#pragma once

#include <utils/common.h>

#define NAMESPACE_PROCESS(NAME) NAMESPACE(process, NAME)
#define NAMESPACE_NATIVE_PROCESS(NAME) NAMESPACE(native, NAMESPACE_PROCESS(NAME))
