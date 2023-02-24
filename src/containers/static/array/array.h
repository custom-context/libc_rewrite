#pragma once

#include <containers/static/common.h>

#define ARRAY_TYPE(TYPE, SIZE) NAMESPACE_CONTAINERS_STATIC(CONCAT5(array, _, TYPE, _, SIZE))
#define ARRAY_METHOD(TYPE, SIZE, METHOD) TYPE_METHOD(ARRAY_TYPE(TYPE, SIZE), METHOD)

#define DECLARE_ARRAY(TYPE, SIZE)\
struct ARRAY_TYPE(TYPE, SIZE);\
\
struct ARRAY_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this);\
struct ARRAY_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_copy_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this, struct ARRAY_TYPE(TYPE, SIZE) const* const source);\
struct ARRAY_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_move_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this, struct ARRAY_TYPE(TYPE, SIZE)* const source);\
struct ARRAY_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_by_value_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this, TYPE const* const value);\
struct ARRAY_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_from_buffer_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this, TYPE const (*buffer)[SIZE]);\
void* ARRAY_METHOD(TYPE, SIZE, destroy_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this);\
\
uint ARRAY_METHOD(TYPE, SIZE, size)(struct ARRAY_TYPE(TYPE, SIZE) const* const this);\
TYPE const* ARRAY_METHOD(TYPE, SIZE, data)(struct ARRAY_TYPE(TYPE, SIZE) const* const this);\
TYPE const* ARRAY_METHOD(TYPE, SIZE, at)(struct ARRAY_TYPE(TYPE, SIZE) const* const this, uint index);\
TYPE * ARRAY_METHOD(TYPE, SIZE, mut_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this, uint index);\
\
typedef struct ARRAY_TYPE(TYPE, SIZE) {\
/*private:*/\
    TYPE buffer_[SIZE];\
} ARRAY_TYPE(TYPE, SIZE)

#define IMPLEMENT_ARRAY(TYPE, SIZE)\
struct ARRAY_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this) {\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, construct_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index));\
    }\
    return this;\
}\
struct ARRAY_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_copy_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this, struct ARRAY_TYPE(TYPE, SIZE) const* const source) {\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index), ARRAY_METHOD(TYPE, SIZE, at)(source, index));\
    }\
    return this;\
}\
struct ARRAY_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_move_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this, struct ARRAY_TYPE(TYPE, SIZE)* const source) {\
    ASSERT(this);\
    return ARRAY_METHOD(TYPE, SIZE, construct_copy_at)(this, source);\
}\
struct ARRAY_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_by_value_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this, TYPE const* const value) {\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index), value);\
    }\
    return this;\
}\
struct ARRAY_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_from_buffer_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this, TYPE const (*buffer)[SIZE]){\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index), buffer[index]);\
    }\
    return this;\
}\
void* ARRAY_METHOD(TYPE, SIZE, destroy_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this){\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, destroy_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index));\
    }\
    return this;\
}\
\
uint ARRAY_METHOD(TYPE, SIZE, size)(struct ARRAY_TYPE(TYPE, SIZE) const* const this) {\
    ASSERT(this);\
    return SIZE;\
}\
TYPE const* ARRAY_METHOD(TYPE, SIZE, data)(struct ARRAY_TYPE(TYPE, SIZE) const* const this) {\
    ASSERT(this);\
    return this->buffer_;\
}\
TYPE * ARRAY_METHOD(TYPE, SIZE, mut_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this, uint index) {\
    ASSERT(this);\
    ASSERT(index < SIZE);\
    return this->buffer_ + index;\
}\
TYPE const* ARRAY_METHOD(TYPE, SIZE, at)(struct ARRAY_TYPE(TYPE, SIZE) const* const this, uint index) {\
    ASSERT(this);\
    ASSERT(index < SIZE);\
    return this->buffer_ + index;\
}

#define DEFINE_ARRAY(TYPE, SIZE)\
struct ARRAY_TYPE(TYPE, SIZE);\
\
static struct ARRAY_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this);\
static struct ARRAY_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_copy_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this, struct ARRAY_TYPE(TYPE, SIZE) const* const source);\
static struct ARRAY_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_by_value_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this, TYPE const* const value);\
static struct ARRAY_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_from_buffer_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this, TYPE const (*buffer)[SIZE]);\
void* ARRAY_METHOD(TYPE, SIZE, destroy_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this);\
\
static uint ARRAY_METHOD(TYPE, SIZE, size)(struct ARRAY_TYPE(TYPE, SIZE) const* const this);\
static TYPE const* ARRAY_METHOD(TYPE, SIZE, data)(struct ARRAY_TYPE(TYPE, SIZE) const* const this);\
static TYPE const* ARRAY_METHOD(TYPE, SIZE, at)(struct ARRAY_TYPE(TYPE, SIZE) const* const this, uint index);\
static TYPE * ARRAY_METHOD(TYPE, SIZE, mut_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this, uint index);\
typedef struct ARRAY_TYPE(TYPE, SIZE) {\
/*private:*/\
    TYPE buffer_[SIZE];\
} ARRAY_TYPE(TYPE, SIZE);\
\
static struct ARRAY_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this) {\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, construct_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index));\
    }\
    return this;\
}\
static struct ARRAY_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_copy_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this, struct ARRAY_TYPE(TYPE, SIZE) const* const source) {\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index), ARRAY_METHOD(TYPE, SIZE, at)(source, index));\
    }\
    return this;\
}\
static struct ARRAY_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_by_value_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this, TYPE const* const value) {\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index), value);\
    }\
    return this;\
}\
static struct ARRAY_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_from_buffer_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this, TYPE const (*buffer)[SIZE]){\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index), buffer[index]);\
    }\
    return this;\
}\
void* ARRAY_METHOD(TYPE, SIZE, destroy_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this){\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, destroy_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index));\
    }\
    return this;\
}\
\
static uint ARRAY_METHOD(TYPE, SIZE, size)(struct ARRAY_TYPE(TYPE, SIZE) const* const this) {\
    ASSERT(this);\
    return SIZE;\
}\
static TYPE const* ARRAY_METHOD(TYPE, SIZE, data)(struct ARRAY_TYPE(TYPE, SIZE) const* const this) {\
    ASSERT(this);\
    return this->buffer_;\
}\
static TYPE * ARRAY_METHOD(TYPE, SIZE, mut_at)(struct ARRAY_TYPE(TYPE, SIZE)* const this, uint index) {\
    ASSERT(this);\
    return this->buffer_ + index;\
}\
static TYPE const* ARRAY_METHOD(TYPE, SIZE, at)(struct ARRAY_TYPE(TYPE, SIZE) const* const this, uint index) {\
    ASSERT(this);\
    return this->buffer_ + index;\
}
