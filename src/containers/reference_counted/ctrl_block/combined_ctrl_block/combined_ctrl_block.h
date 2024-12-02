#pragma once

#include "combined_ctrl_block_allocator.h"
#include <containers/reference_counted/ctrl_block/ictrl_block.h>
#include "combined_ctrl_block_common.h"
#include <memory/common.h>

/// struct rc<Type, StrongRC, WeakRC>::DefaultCombinedCtrlBlock<Allocator<Type>>
#define DEFINE_RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)\
DECLARE_STRUCT_SUBTYPE(RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR), value_type, TYPE);\
DECLARE_STRUCT_SUBTYPE(RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR), allocator_type, ALLOCATOR);\
/* here we expect that its interface was defined before*/\
typedef struct RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR) {\
    struct RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC) inherited_abstract_object;\
    STRUCT_SUBTYPE(RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR), value_type) value;\
    STRUCT_SUBTYPE(RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR), allocator_type) allocator;\
} RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)
/// struct rc<Type, StrongRC, WeakRC>::DefaultCombinedCtrlBlock<Allocator<Type>=DefaultAllocator<Type>>
#define DEFINE_RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)\
    DEFINE_RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC,\
        ALLOCATOR_TYPE__RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC))
/// struct rc<Type, StrongRC=usize, WeakRC=usize>::DefaultCombinedCtrlBlock<Allocator<Type>=DefaultAllocator<Type>>
#define DEFINE_RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE(TYPE)\
    DEFINE_RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC(TYPE, usize, usize)
/// struct rc<Type, StrongRC, WeakRC>::DefaultCombinedCtrlBlock<Allocator<Type>>::vtable variable
#define DECLARE_RC_DEFAULT_COMBINED_CTRL_BLOCK_INTERFACE_VTABLE_VARIABLE__STRONG_RC__WEAK_RC__ALLOCATOR_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)\
    DECLARE_CONTAINER_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(\
        MODIFIER,\
        RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR),\
        RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC)\
    )
/// struct rc<Type, StrongRC, WeakRC>::DefaultCombinedCtrlBlock<Allocator<Type>=DefaultAllocator<Type>>::vtable variable
#define DECLARE_RC_DEFAULT_COMBINED_CTRL_BLOCK_INTERFACE_VTABLE_VARIABLE__STRONG_RC__WEAK_RC_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC)\
    DECLARE_RC_DEFAULT_COMBINED_CTRL_BLOCK_INTERFACE_VTABLE_VARIABLE__STRONG_RC__WEAK_RC__ALLOCATOR_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC,\
        ALLOCATOR_TYPE__RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC))
/// struct rc<Type, StrongRC=usize, WeakRC=usize>::DefaultCombinedCtrlBlock<Allocator<Type>=DefaultAllocator<Type>>::vtable variable
#define DECLARE_RC_DEFAULT_COMBINED_CTRL_BLOCK_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, TYPE)\
    DECLARE_RC_DEFAULT_COMBINED_CTRL_BLOCK_INTERFACE_VTABLE_VARIABLE__STRONG_RC__WEAK_RC_WITH_MODIFIER(MODIFIER, TYPE, usize, usize)
///
/// struct rc<Type, StrongRC, WeakRC>::DefaultCombinedCtrlBlock<Allocator<Type>> methods
#define DECLARE_RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHODS_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)\
DECLARE_DEFAULT_LIFECYCLE_METHODS_WITH_MODIFIER(MODIFIER, RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR));\
MODIFIER RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)*\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, PRIVATE(construct_without_value_construction_at))(\
        struct RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)* const this);\
MODIFIER void\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, dispose_value)(\
        struct RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)* const this);\
MODIFIER void\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, dispose_this)(\
        struct RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)* const this);\
MODIFIER void*\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, VTABLE_MEMBER(destroy_at))(\
        struct RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC)* const this);\
MODIFIER void\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, VTABLE_MEMBER(dispose_this))(\
        struct RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC)* const this);\
MODIFIER void\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, VTABLE_MEMBER(dispose_value))(\
        struct RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC)* const this)
/// struct rc<Type, StrongRC, WeakRC>::DefaultCombinedCtrlBlock<Allocator<Type>=DefaultAllocator<Type>> methods
#define DECLARE_RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC)\
    DECLARE_RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHODS_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC,\
        ALLOCATOR_TYPE__RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC))
/// struct rc<Type, StrongRC=usize, WeakRC=usize>::DefaultCombinedCtrlBlock methods
#define DECLARE_RC_DEFAULT_COMBINED_CTRL_BLOCK_METHODS_WITH_MODIFIER(MODIFIER, TYPE)\
    DECLARE_RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, usize, usize)
/// struct rc<Type, StrongRC, WeakRC>::DefaultCombinedCtrlBlock<Allocator<Type>>::vtable variable init
#define DEFINE_RC_DEFAULT_COMBINED_CTRL_BLOCK_INTERFACE_VTABLE_VARIABLE__STRONG_RC__WEAK_RC__ALLOCATOR_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)\
    DECLARE_CONTAINER_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(\
        MODIFIER,\
        RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR),\
        RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC)\
    ) = {\
        .dispose_value = RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, VTABLE_MEMBER(dispose_value)),\
        .dispose_this = RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, VTABLE_MEMBER(dispose_this)),\
        .destroy_at = RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, VTABLE_MEMBER(destroy_at))\
    }
/// struct rc<Type, StrongRC, WeakRC>::DefaultCombinedCtrlBlock<Allocator<Type>=DefaultAllocator<Type>>::vtable variable init
#define DEFINE_RC_DEFAULT_COMBINED_CTRL_BLOCK_INTERFACE_VTABLE_VARIABLE__STRONG_RC__WEAK_RC_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC)\
    DEFINE_RC_DEFAULT_COMBINED_CTRL_BLOCK_INTERFACE_VTABLE_VARIABLE__STRONG_RC__WEAK_RC__ALLOCATOR_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC,\
        ALLOCATOR_TYPE__RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC))
/// struct rc<Type, StrongRC=usize, WeakRC=usize>::DefaultCombinedCtrlBlock<Allocator<Type>=DefaultAllocator<Type>>::vtable variable init
#define DEFINE_RC_DEFAULT_COMBINED_CTRL_BLOCK_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, TYPE)\
    DEFINE_RC_DEFAULT_COMBINED_CTRL_BLOCK_INTERFACE_VTABLE_VARIABLE__STRONG_RC__WEAK_RC_WITH_MODIFIER(MODIFIER, TYPE, usize, usize)

/// struct rc<Type, StrongRC, WeakRC>::DefaultCombinedCtrlBlock<Allocator<Type>> methods definition
#define DEFINE_RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHODS_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)\
MODIFIER RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)*\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, construct_at)(\
        RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)* const this) {\
    ASSERT(this);\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, PRIVATE(construct_without_value_construction_at))(this);\
    TYPE_METHOD(TYPE, construct_at)(&this->value);\
    return this;\
}\
MODIFIER RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)*\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, construct_copy_at)(\
        RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)* const this,\
        RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR) const* const src) {\
    ASSERT(this);\
    ASSERT(src);\
    RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC_METHOD(STRONG_RC, WEAK_RC, construct_copy_at)(\
        &this->inherited_abstract_object,\
        &src->inherited_abstract_object);\
    this->inherited_abstract_object.INTERFACE_VTABLE_VARIABLE(RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC)) =\
        &CONTAINER_INTERFACE_VTABLE_STATIC_VARIABLE(\
            RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR),\
            RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC)\
        );\
    TYPE_METHOD(TYPE, construct_copy_at)(&this->value, &src->value);\
    TYPE_METHOD(ALLOCATOR, construct_copy_at)(&this->allocator, &src->allocator);\
    return this;\
}\
MODIFIER RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)*\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, construct_move_at)(\
        RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)* const this,\
        RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)* const src) {\
    ASSERT(this);\
    ASSERT(src);\
    RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC_METHOD(STRONG_RC, WEAK_RC, construct_move_at)(\
        &this->inherited_abstract_object,\
        &src->inherited_abstract_object);\
    this->inherited_abstract_object.INTERFACE_VTABLE_VARIABLE(RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC)) =\
        &CONTAINER_INTERFACE_VTABLE_STATIC_VARIABLE(\
            RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR),\
            RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC)\
        );\
    TYPE_METHOD(TYPE, construct_move_at)(&this->value, &src->value);\
    TYPE_METHOD(ALLOCATOR, construct_move_at)(&this->allocator, &src->allocator);\
    return this;\
}\
DEFINE_DEFAULT_ASSIGNMENT_METHODS_WITH_MODIFIER(MODIFIER, RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR))\
MODIFIER void\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, swap)(\
        RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)* const this,\
        RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)* const src) {\
    ASSERT(this);\
    ASSERT(src);\
    RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC_METHOD(STRONG_RC, WEAK_RC, swap)(\
        &this->inherited_abstract_object,\
        &src->inherited_abstract_object\
    );\
    TYPE_METHOD(TYPE, swap)(&this->value, &src->value);\
    TYPE_METHOD(ALLOCATOR, swap)(&this->allocator, &src->allocator);\
}\
MODIFIER RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)*\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, PRIVATE(construct_without_value_construction_at))(\
        struct RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)* const this) {\
    ASSERT(this);\
    RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC_METHOD(STRONG_RC, WEAK_RC, construct_at)(&this->inherited_abstract_object);\
    this->inherited_abstract_object.INTERFACE_VTABLE_VARIABLE(RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC)) =\
        &CONTAINER_INTERFACE_VTABLE_STATIC_VARIABLE(\
            RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR),\
            RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC)\
        );\
    TYPE_METHOD(ALLOCATOR, construct_at)(&this->allocator);\
    return this;\
}\
MODIFIER void*\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, destroy_at)(\
        RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)* const this) {\
    ASSERT(this);\
    RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC_METHOD(STRONG_RC, WEAK_RC, destroy_at)(&this->inherited_abstract_object);\
    return this;\
}\
MODIFIER void\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, dispose_value)(\
        struct RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)* const this) {\
    ASSERT(this);\
    RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC_METHOD(STRONG_RC, WEAK_RC, dispose_value)(&this->inherited_abstract_object);\
}\
MODIFIER void\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, dispose_this)(\
        struct RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)* const this) {\
    ASSERT(this);\
    RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC_METHOD(STRONG_RC, WEAK_RC, dispose_this)(&this->inherited_abstract_object);\
}\
MODIFIER void*\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, VTABLE_MEMBER(destroy_at))(\
        struct RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC)* const base) {\
    /* boilerplate (base to derived) */\
    ASSERT(base);\
    void* const void_this = (char*)base -\
        offsetof(RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR), inherited_abstract_object);\
    RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)* const this =\
        (RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)*)void_this;\
    /* call this::destroy_at instructions */\
    /* nothing */\
    /* call interface::destroy_at */\
    RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC_METHOD(STRONG_RC, WEAK_RC, VTABLE_MEMBER(destroy_at))(base);\
    return this;\
}\
MODIFIER void\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, VTABLE_MEMBER(dispose_this))(\
        struct RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC)* const base) {\
    /* boilerplate (base to derived) */\
    ASSERT(base);\
    void* const void_this = (char*)base -\
        offsetof(RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR), inherited_abstract_object);\
    RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)* const this =\
        (RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)*)void_this;\
    /* move this::allocator to temporary allocator's storage (temp_allocator) & destroy this::allocator before deallocation */\
    ALLOCATOR temp_allocator;\
    TYPE_METHOD(ALLOCATOR, construct_move_at)(\
        &temp_allocator,\
        &this->allocator\
    );\
    TYPE_METHOD(ALLOCATOR, destroy_at)(&this->allocator);\
    /* deallocate memory from this by temporary allocator object (temp_allocator) */\
    TYPE_METHOD(ALLOCATOR, deallocate)(\
        &temp_allocator,\
        this,\
        1u);\
    /* destroy temporary allocator's storage (temp_allocator) */\
    TYPE_METHOD(ALLOCATOR, destroy_at)(&temp_allocator);\
}\
MODIFIER void\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHOD(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR, VTABLE_MEMBER(dispose_value))(\
        struct RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC)* const base) {\
    /* boilerplate (base to derived) */\
    ASSERT(base);\
    void* const void_this = (char*)base -\
        offsetof(RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR), inherited_abstract_object);\
    RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)* const this =\
        (RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC__ALLOCATOR(TYPE, STRONG_RC, WEAK_RC, ALLOCATOR)*)void_this;\
    /* destroy value */\
    TYPE_METHOD(TYPE, destroy_at)(&this->value);\
}

/// struct rc<Type, StrongRC, WeakRC>::DefaultCombinedCtrlBlock<Allocator<Type>=DefaultAllocator<Type>> methods definition
#define DEFINE_RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC)\
    DEFINE_RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC__ALLOCATOR_METHODS_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC,\
        ALLOCATOR_TYPE__RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC))
/// struct rc<Type, StrongRC=usize, WeakRC=usize>::DefaultCombinedCtrlBlock<Allocator<Type>=DefaultAllocator<Type>> methods definition
#define DEFINE_RC_DEFAULT_COMBINED_CTRL_BLOCK_METHODS_WITH_MODIFIER(MODIFIER, TYPE)\
    DEFINE_RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, usize, usize)