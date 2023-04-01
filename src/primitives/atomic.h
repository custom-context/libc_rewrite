#pragma once

#include <concurrent/atomic/atomic.h>

// fixed-width integers
#include "fixed_size_types_aliases.h"
DEFINE_NATIVE_ATOMIC_TYPE(int8);
DEFINE_ATOMIC_TYPE(int8);
DECLARE_ATOMIC_METHODS_WITH_MODIFIER(extern, int8);
DEFINE_NATIVE_ATOMIC_TYPE(int16);
DEFINE_ATOMIC_TYPE(int16);
DECLARE_ATOMIC_METHODS_WITH_MODIFIER(extern, int16);
DEFINE_NATIVE_ATOMIC_TYPE(int32);
DEFINE_ATOMIC_TYPE(int32);
DECLARE_ATOMIC_METHODS_WITH_MODIFIER(extern, int32);
DEFINE_NATIVE_ATOMIC_TYPE(int64);
DEFINE_ATOMIC_TYPE(int64);
DECLARE_ATOMIC_METHODS_WITH_MODIFIER(extern, int64);

DEFINE_NATIVE_ATOMIC_TYPE(uint8);
DEFINE_ATOMIC_TYPE(uint8);
DECLARE_ATOMIC_METHODS_WITH_MODIFIER(extern, uint8);
DEFINE_NATIVE_ATOMIC_TYPE(uint16);
DEFINE_ATOMIC_TYPE(uint16);
DECLARE_ATOMIC_METHODS_WITH_MODIFIER(extern, uint16);
DEFINE_NATIVE_ATOMIC_TYPE(uint32);
DEFINE_ATOMIC_TYPE(uint32);
DECLARE_ATOMIC_METHODS_WITH_MODIFIER(extern, uint32);
DEFINE_NATIVE_ATOMIC_TYPE(uint64);
DEFINE_ATOMIC_TYPE(uint64);
DECLARE_ATOMIC_METHODS_WITH_MODIFIER(extern, uint64);

// character types
#include "characters_types_aliases.h"
DEFINE_NATIVE_ATOMIC_TYPE(char8);
DEFINE_ATOMIC_TYPE(char8);
DECLARE_ATOMIC_METHODS_WITH_MODIFIER(extern, char8);
DEFINE_NATIVE_ATOMIC_TYPE(char16);
DEFINE_ATOMIC_TYPE(char16);
DECLARE_ATOMIC_METHODS_WITH_MODIFIER(extern, char16);
DEFINE_NATIVE_ATOMIC_TYPE(char32);
DEFINE_ATOMIC_TYPE(char32);
DECLARE_ATOMIC_METHODS_WITH_MODIFIER(extern, char32);
DEFINE_NATIVE_ATOMIC_TYPE(char64);
DEFINE_ATOMIC_TYPE(char64);
DECLARE_ATOMIC_METHODS_WITH_MODIFIER(extern, char64);

// pointer/data related types
#include "data_model_types_aliases.h"
DEFINE_NATIVE_ATOMIC_TYPE(usize);
DEFINE_ATOMIC_TYPE(usize);
DECLARE_ATOMIC_METHODS_WITH_MODIFIER(extern, usize);
DEFINE_NATIVE_ATOMIC_TYPE(ptrdiff);
DEFINE_ATOMIC_TYPE(ptrdiff);
DECLARE_ATOMIC_METHODS_WITH_MODIFIER(extern, ptrdiff);
DEFINE_NATIVE_ATOMIC_TYPE(intptr);
DEFINE_ATOMIC_TYPE(intptr);
DECLARE_ATOMIC_METHODS_WITH_MODIFIER(extern, intptr);
DEFINE_NATIVE_ATOMIC_TYPE(uintptr);
DEFINE_ATOMIC_TYPE(uintptr);
DECLARE_ATOMIC_METHODS_WITH_MODIFIER(extern, uintptr);
