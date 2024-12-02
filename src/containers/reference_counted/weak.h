#pragma once

#include "ctrl_block/ctrl_block.h"
#include "common.h"

/// rcv<Type, StrongRC, WeakRC>::*METHOD
#define WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, METHOD)\
    TYPE_METHOD(WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC), METHOD)
/// rcv<Type, StrongRC=usize, WeakRC=usize>::*METHOD
#define WEAK_METHOD(TYPE, METHOD)\
    TYPE_METHOD(WEAK_TYPE(TYPE), METHOD)


// types
/// struct rcv<Type, StrongRC, WeakRC>
#define DEFINE_WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)\
DECLARE_STRUCT_SUBTYPE(WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC), value_type, TYPE);\
typedef struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) {\
    struct RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC)* pctrl_block;\
    STRUCT_SUBTYPE(WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC), value_type)* pvalue;\
} WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)
/// struct rc<Type, StrongRC=usize, WeakRC=usize>
#define DEFINE_WEAK_TYPE(TYPE)\
    DEFINE_WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, usize, usize)

// methods declarations
#define DECLARE_WEAK__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC)\
DECLARE_DEFAULT_LIFECYCLE_METHODS_WITH_MODIFIER(MODIFIER, WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC));\
/* --- Non-default methods --- */\
MODIFIER struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)*\
    WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, construct_from_rc_at)(\
        struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this,\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) const* const rc);\
MODIFIER struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)*\
    WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, assign_from_rc_at)(\
        struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this,\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) const* const rc);\
MODIFIER struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)\
    WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, lock)(\
        struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) const* const this);\
MODIFIER STRUCT_SUBTYPE(RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC), strong_rc_type)\
    WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, count_owners)(\
        struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) const* const this);\
MODIFIER bool\
    WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, expired)(\
        struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) const* const this)

#define DECLARE_WEAK_METHODS_WITH_MODIFIER(MODIFIER, TYPE)\
    DECLARE_WEAK__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, usize, usize)

// methods definitions
#define DEFINE_WEAK__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, STRONG_RC, WEAK_RC)\
/* --- Construction/Destruction functions --- */\
MODIFIER struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)*\
    WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, construct_at)(\
        struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this) {\
    ASSERT(this);\
    this->pctrl_block = NULL;\
    this->pvalue = NULL;\
    return this;\
}\
MODIFIER struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)*\
    WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, construct_copy_at)(\
        struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this,\
        struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->pctrl_block = source->pctrl_block;\
    if (this->pctrl_block) {\
        ++this->pctrl_block->weak_rc;\
    }\
    this->pvalue = source->pvalue;\
    return this;\
}\
MODIFIER struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)*\
    WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, construct_move_at)(\
        struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this,\
        struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->pctrl_block = source->pctrl_block; source->pctrl_block = NULL;\
    this->pvalue = source->pvalue; source->pvalue = NULL;\
    return this;\
}\
MODIFIER void*\
    WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, destroy_at)(\
        struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this) {\
    ASSERT(this);\
    do {\
        if (!this->pctrl_block) {\
            break;\
        }\
        if (--this->pctrl_block->weak_rc) {\
            break;\
        }\
        if (this->pctrl_block->strong_rc) {\
            break;\
        }\
        RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC_METHOD(STRONG_RC, WEAK_RC, destroy_at)(this->pctrl_block);\
        RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC_METHOD(STRONG_RC, WEAK_RC, dispose_this)(this->pctrl_block);\
    } while(false);\
    return this;\
}\
/* --- Assign functions --- */\
DEFINE_DEFAULT_ASSIGNMENT_METHODS_WITH_MODIFIER(MODIFIER, WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC))\
/* --- Swap --- */\
MODIFIER void\
    WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, swap)(\
        struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this,\
        struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    TYPE_METHOD(voidptr, swap)((voidptr*)&this->pctrl_block, (voidptr*)&source->pctrl_block);\
    TYPE_METHOD(voidptr, swap)((voidptr*)&this->pvalue, (voidptr*)&source->pvalue);\
}\
/* --- Non-default methods --- */\
MODIFIER struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)*\
    WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, construct_from_rc_at)(\
        struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this,\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) const* const rc) {\
    ASSERT(this);\
    ASSERT(rc);\
    this->pctrl_block = rc->pctrl_block;\
    this->pvalue = rc->pvalue;\
    if (this->pctrl_block) {\
        ++this->pctrl_block->weak_rc;\
    }\
    return this;\
}\
MODIFIER struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)*\
    WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, assign_from_rc_at)(\
        struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)* const this,\
        struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) const* const rc) {\
    ASSERT(this);\
    WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) temporary;\
    WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, construct_from_rc_at)(&temporary, rc);\
    WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, swap)(&temporary, this);\
    WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, destroy_at)(&temporary);\
    return this;\
}\
MODIFIER struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)\
    WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, lock)(\
        struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) const* const this) {\
    ASSERT(this);\
    if (WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, expired)(this)) {\
        return (struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)){\
            .pctrl_block = NULL,\
            .pvalue = NULL\
        };\
    }\
    ++this->pctrl_block->strong_rc;\
    return (struct RC_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC)){\
        .pctrl_block = this->pctrl_block,\
        .pvalue = this->pvalue\
    };\
}\
MODIFIER STRUCT_SUBTYPE(RC_CTRL_BLOCK_INTERFACE_TYPE__STRONG_RC__WEAK_RC(STRONG_RC, WEAK_RC), strong_rc_type)\
    WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, count_owners)(\
        struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) const* const this) {\
    ASSERT(this);\
    return this->pctrl_block ? this->pctrl_block->strong_rc : 0u;\
}\
MODIFIER bool\
    WEAK__STRONG_RC__WEAK_RC_METHOD(TYPE, STRONG_RC, WEAK_RC, expired)(\
        struct WEAK_TYPE__STRONG_RC__WEAK_RC(TYPE, STRONG_RC, WEAK_RC) const* const this) {\
    ASSERT(this);\
    return !this->pctrl_block || !this->pctrl_block->strong_rc;\
}

#define DEFINE_WEAK_METHODS_WITH_MODIFIER(MODIFIER, TYPE)\
    DEFINE_WEAK__STRONG_RC__WEAK_RC_METHODS_WITH_MODIFIER(MODIFIER, TYPE, usize, usize)
