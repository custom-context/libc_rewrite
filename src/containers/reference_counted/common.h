#pragma once

#include <containers/common.h>
#include <primitives/primitives.h>
#include <construct/primitives.h>

#define NAMESPACE_REFERENCE_COUNTED(NAME) NAMESPACE_CONTAINERS(CONCAT3(reference_counted, __, NAME))

/// rc<Type, StrongRC, WeakRC>
#define RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)\
    NAMESPACE_REFERENCE_COUNTED(CONCAT5(CONCAT3(rc, __, TYPE), __, STRONG_RC, __, WEAK_RC))
/// rc<Type, StrongRC=usize, WeakRC=usize>
#define RC_TYPE(TYPE)\
    RC_TYPE__STRONG_RC__WEAK_RC(TYPE, usize, usize)
