#pragma once

#include "ctrl_block/ctrl_block.h"
#include "common.h"

/// rc<Type, StrongRC, WeakRC>::*METHOD
#define RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, METHOD)\
    TYPE_METHOD(RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC), METHOD)
/// rc<Type, StrongRC=usize, WeakRC=usize>::*METHOD
#define RC_METHOD(TYPE, METHOD)\
    TYPE_METHOD(RC_TYPE(TYPE), METHOD)


// types
/// struct rc<Type, StrongRC, WeakRC>
#define DEFINE_RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)\
DEFINE_ALLOCATOR_TYPE__RC_DEFAULT_SEPARATED_CTRL_BLOCK__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC);\
DEFINE_RC_DEFAULT_SEPARATED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC);\
\
DEFINE_ALLOCATOR_TYPE__RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC);\
DEFINE_RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC);\
\
DECLARE_STRUCT_SUBTYPE(RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC), value_type, TYPE);\
typedef struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) {\
    struct RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC)* pctrl_block;\
    STRUCT_SUBTYPE(RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC), value_type)* pvalue;\
} RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)
/// struct rc<Type, StrongRC=usize, WeakRC=usize>
#define DEFINE_RC_TYPE(TYPE)\
    DEFINE_RC_TYPE__STRONG_RC__WEAK_RC(TYPE, usize, usize)

// methods declarations
#define DECLARE_RC__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC)\
DECLARE_ALLOCATOR__RC_DEFAULT_SEPARATED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC);\
DECLARE_RC_DEFAULT_SEPARATED_CTRL_BLOCK_INTERFACE_VTABLE_VARIABLE__STRONG_RC__WEAK_RC_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC);\
DECLARE_RC_DEFAULT_SEPARATED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC);\
\
DECLARE_ALLOCATOR__RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC);\
DECLARE_RC_DEFAULT_COMBINED_CTRL_BLOCK_INTERFACE_VTABLE_VARIABLE__STRONG_RC__WEAK_RC_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC);\
DECLARE_RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC);\
\
DECLARE_DEFAULT_LIFECYCLE_METHODS_WITH_MODIFIER(MODIFIER, RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC));\
/* --- Non-default methods --- */\
MODIFIER RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)*\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, construct_from_value_pointer_at)(\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this,\
        STRUCT_SUBTYPE(RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC), value_type)* const pointer);\
MODIFIER RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)*\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, assign_from_value_pointer_at)(\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this,\
        STRUCT_SUBTYPE(RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC), value_type)* const pointer);\
MODIFIER STRUCT_SUBTYPE(RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC), value_type) const*\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, get)(\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) const* const this);\
MODIFIER STRUCT_SUBTYPE(RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC), value_type)*\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, mut_get)(\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this);\
MODIFIER STRUCT_SUBTYPE(RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC), strong_rc_type)\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, count_owners)(\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) const* const this);\
MODIFIER struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)*\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, make_default_rc)(\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const storage)

#define DECLARE_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE)\
    DECLARE_RC__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, usize, usize)

#define MAKE_RC__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC, TYPE_CONSTRUCTOR_NAME)\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, CONCAT3(make_rc, __, TYPE_CONSTRUCTOR_NAME))

#define MAKE_RC(TYPE, TYPE_CONSTRUCTOR_NAME)\
    MAKE_RC__STRONG_RC__WEAK_RC(TYPE, usize, usize, TYPE_CONSTRUCTOR_NAME)

#define DECLARE_MAKE_RC__STRONG_RC__WEAK_RC_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC, TYPE_CONSTRUCTOR_NAME, ...)\
MODIFIER struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)*\
    MAKE_RC__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC, TYPE_CONSTRUCTOR_NAME)(\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const storage,\
        ARGS(__VA_ARGS__))

#define DECLARE_MAKE_RC_WITH_MODIFIER(MODIFIER, TYPE, TYPE_CONSTRUCTOR_NAME, ...)\
    DECLARE_MAKE_RC__STRONG_RC__WEAK_RC_WITH_MODIFIER(MODIFIER, TYPE, usize, usize, TYPE_CONSTRUCTOR_NAME, __VA_ARGS__)

// methods definitions
#define DEFINE_RC__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC)\
DEFINE_ALLOCATOR__RC_DEFAULT_SEPARATED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC)\
DEFINE_RC_DEFAULT_SEPARATED_CTRL_BLOCK_INTERFACE_VTABLE_VARIABLE__STRONG_RC__WEAK_RC_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC);\
DEFINE_RC_DEFAULT_SEPARATED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC)\
\
DEFINE_ALLOCATOR__RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC)\
DEFINE_RC_DEFAULT_COMBINED_CTRL_BLOCK_INTERFACE_VTABLE_VARIABLE__STRONG_RC__WEAK_RC_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC);\
DEFINE_RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC)\
/* --- Construction/Destruction functions --- */\
MODIFIER struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)*\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, construct_at)(\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this) {\
    ASSERT(this);\
    this->pctrl_block = NULL;\
    this->pvalue = NULL;\
    return this;\
}\
MODIFIER struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)*\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, construct_copy_at)(\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this,\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->pctrl_block = source->pctrl_block;\
    if (this->pctrl_block) {\
        ++this->pctrl_block->strong_rc;\
    }\
    this->pvalue = source->pvalue;\
    return this;\
}\
MODIFIER struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)*\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, construct_move_at)(\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this,\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->pctrl_block = source->pctrl_block; source->pctrl_block = NULL;\
    this->pvalue = source->pvalue; source->pvalue = NULL;\
    return this;\
}\
MODIFIER void*\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, destroy_at)(\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this) {\
    ASSERT(this);\
    do {\
        if (!this->pctrl_block) {\
            break;\
        }\
        if (--this->pctrl_block->strong_rc) {\
            break;\
        }\
        RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC_METHOD(STRONG_RC, WEAK_RC, dispose_value)(this->pctrl_block);\
        if (this->pctrl_block->weak_rc) {\
            break;\
        }\
        RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC_METHOD(STRONG_RC, WEAK_RC, destroy_at)(this->pctrl_block);\
        RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC_METHOD(STRONG_RC, WEAK_RC, dispose_this)(this->pctrl_block);\
    } while(false);\
    return this;\
}\
/* --- Assign functions --- */\
DEFINE_DEFAULT_ASSIGNMENT_METHODS_WITH_MODIFIER(MODIFIER, RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC))\
/* --- Swap --- */\
MODIFIER void\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, swap)(\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this,\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    TYPE_METHOD(voidptr, swap)((voidptr*)&this->pctrl_block, (voidptr*)&source->pctrl_block);\
    TYPE_METHOD(voidptr, swap)((voidptr*)&this->pvalue, (voidptr*)&source->pvalue);\
}\
/* --- Non-default methods --- */\
MODIFIER RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)*\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, construct_from_value_pointer_at)(\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this,\
        STRUCT_SUBTYPE(RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC), value_type)* const pointer) {\
    ASSERT(this);\
    if (!pointer) {\
        return RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, construct_at)(this);\
    }\
    /* contruct default_separated ctrl_block with passed pointer */\
    ALLOCATOR_TYPE__RC_DEFAULT_SEPARATED_CTRL_BLOCK__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) temp_ctrl_block_allocator;\
    ALLOCATOR__RC_DEFAULT_SEPARATED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, construct_at)(&temp_ctrl_block_allocator);\
    RC_DEFAULT_SEPARATED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const pctrl_block_storage =\
        ALLOCATOR__RC_DEFAULT_SEPARATED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, allocate)(\
            &temp_ctrl_block_allocator,\
            1u\
        );\
    RC_DEFAULT_SEPARATED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, construct_at)(pctrl_block_storage);\
    pctrl_block_storage->value = pointer;\
    this->pctrl_block = &pctrl_block_storage->inherited_abstract_object;\
    this->pvalue = pointer;\
    ALLOCATOR__RC_DEFAULT_SEPARATED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, construct_at)(&temp_ctrl_block_allocator);\
    return this;\
}\
MODIFIER RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)*\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, assign_from_value_pointer_at)(\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this,\
        STRUCT_SUBTYPE(RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC), value_type)* const pointer) {\
    ASSERT(this);\
    RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) temporary;\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, construct_from_value_pointer_at)(&temporary, pointer);\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, swap)(&temporary, this);\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, destroy_at)(&temporary);\
    return this;\
}\
MODIFIER STRUCT_SUBTYPE(RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC), value_type) const*\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, get)(\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) const* const this) {\
    return this->pvalue;\
}\
MODIFIER STRUCT_SUBTYPE(RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC), value_type)*\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, mut_get)(\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this) {\
    return this->pvalue;\
}\
MODIFIER STRUCT_SUBTYPE(RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC), strong_rc_type)\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, count_owners)(\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) const* const this) {\
    return this->pctrl_block ? this->pctrl_block->strong_rc : 0u;\
}\
MODIFIER struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)*\
    RC__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, make_default_rc)(\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const storage) {\
    ASSERT(storage);\
    /* contruct default_combined ctrl_block with passed pointer */\
    ALLOCATOR_TYPE__RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) temp_ctrl_block_allocator;\
    ALLOCATOR__RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, construct_at)(&temp_ctrl_block_allocator);\
    \
    RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const pctrl_block_storage =\
        ALLOCATOR__RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, allocate)(\
            &temp_ctrl_block_allocator,\
            1u\
        );\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, construct_at)(pctrl_block_storage);\
    ALLOCATOR__RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, assign_move_at)(\
        &pctrl_block_storage->allocator,\
        &temp_ctrl_block_allocator\
    );\
    storage->pctrl_block = &pctrl_block_storage->inherited_abstract_object;\
    storage->pvalue = &pctrl_block_storage->value;\
    ALLOCATOR__RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, destroy_at)(&temp_ctrl_block_allocator);\
    return storage;\
}


#define DEFINE_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE)\
    DEFINE_RC__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, usize, usize)

#define DEFINE_MAKE_RC__STRONG_RC__WEAK_RC_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC, TYPE_CONSTRUCTOR_NAME, ...)\
MODIFIER struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)*\
    MAKE_RC__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC, TYPE_CONSTRUCTOR_NAME)(\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const storage,\
        ARGS(__VA_ARGS__)) {\
    ASSERT(storage);\
    /* contruct default_combined ctrl_block with passed pointer */\
    ALLOCATOR_TYPE__RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) temp_ctrl_block_allocator;\
    ALLOCATOR__RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, construct_at)(&temp_ctrl_block_allocator);\
    \
    RC_DEFAULT_COMBINED_CTRL_BLOCK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const pctrl_block_storage =\
        ALLOCATOR__RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, allocate)(\
            &temp_ctrl_block_allocator,\
            1u\
        );\
    RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, PRIVATE(construct_without_value_construction_at))(\
        pctrl_block_storage);\
    TYPE_METHOD(TYPE, TYPE_CONSTRUCTOR_NAME)(&pctrl_block_storage->value, PASS(__VA_ARGS__));\
    ALLOCATOR__RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, assign_move_at)(\
        &pctrl_block_storage->allocator,\
        &temp_ctrl_block_allocator\
    );\
    storage->pctrl_block = &pctrl_block_storage->inherited_abstract_object;\
    storage->pvalue = &pctrl_block_storage->value;\
    ALLOCATOR__RC_DEFAULT_COMBINED_CTRL_BLOCK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, destroy_at)(&temp_ctrl_block_allocator);\
    return storage;\
}

#define DEFINE_MAKE_RC_WITH_MODIFIER(MODIFIER, TYPE, TYPE_CONSTRUCTOR_NAME, ...)\
    DEFINE_MAKE_RC__STRONG_RC__WEAK_RC_WITH_MODIFIER(MODIFIER, TYPE, usize, usize, TYPE_CONSTRUCTOR_NAME, __VA_ARGS__)
