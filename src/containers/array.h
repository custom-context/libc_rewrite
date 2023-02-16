#pragma once

#include <construct/numeric_helpers.h>

#include <utils/macros.h>

#define ARRAY_TYPE_(TYPE, SIZE) CONCAT5(array, _, TYPE, _, SIZE)
#define ARRAY_TYPE(TYPE, SIZE) ARRAY_TYPE_(TYPE, SIZE)

#define ARRAY_METHOD_(TYPE, SIZE, METHOD) TYPE_METHOD(ARRAY_TYPE(TYPE, SIZE), METHOD)
#define ARRAY_METHOD(TYPE, SIZE, METHOD) ARRAY_METHOD_(TYPE, SIZE, METHOD)

#define ARRAY_STRUCT_TYPE_(TYPE, SIZE) struct ARRAY_TYPE(TYPE, SIZE)
#define ARRAY_STRUCT_TYPE(TYPE, SIZE) ARRAY_STRUCT_TYPE_(TYPE, SIZE)

#define DECLARE_ARRAY_(TYPE, SIZE)\
ARRAY_STRUCT_TYPE(TYPE, SIZE);\
\
ARRAY_STRUCT_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this);\
ARRAY_STRUCT_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_copy_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this, ARRAY_STRUCT_TYPE(TYPE, SIZE) const* const source);\
ARRAY_STRUCT_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_by_value_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this, TYPE const* const value);\
ARRAY_STRUCT_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_from_buffer_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this, TYPE const (*buffer)[SIZE]);\
void* ARRAY_METHOD(TYPE, SIZE, destroy_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this);\
\
uint ARRAY_METHOD(TYPE, SIZE, size)(ARRAY_STRUCT_TYPE(TYPE, SIZE) const* const this);\
TYPE const* ARRAY_METHOD(TYPE, SIZE, data)(ARRAY_STRUCT_TYPE(TYPE, SIZE) const* const this);\
TYPE const* ARRAY_METHOD(TYPE, SIZE, at)(ARRAY_STRUCT_TYPE(TYPE, SIZE) const* const this, uint index);\
TYPE * ARRAY_METHOD(TYPE, SIZE, mut_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this, uint index);\
\
typedef ARRAY_STRUCT_TYPE(TYPE, SIZE) {\
/*private:*/\
    TYPE buffer_[SIZE];\
} ARRAY_TYPE(TYPE, SIZE)
#define DECLARE_ARRAY(TYPE, SIZE) DECLARE_ARRAY_(TYPE, SIZE)

#define IMPLEMENT_ARRAY_(TYPE, SIZE)\
ARRAY_STRUCT_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this) {\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, construct_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index));\
    }\
    return this;\
}\
ARRAY_STRUCT_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_copy_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this, ARRAY_STRUCT_TYPE(TYPE, SIZE) const* const source) {\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index), ARRAY_METHOD(TYPE, SIZE, at)(source, index));\
    }\
    return this;\
}\
ARRAY_STRUCT_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_by_value_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this, TYPE const* const value) {\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index), value);\
    }\
    return this;\
}\
ARRAY_STRUCT_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_from_buffer_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this, TYPE const (*buffer)[SIZE]){\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index), buffer[index]);\
    }\
    return this;\
}\
void* ARRAY_METHOD(TYPE, SIZE, destroy_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this){\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, destroy_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index));\
    }\
    return this;\
}\
\
uint ARRAY_METHOD(TYPE, SIZE, size)(ARRAY_STRUCT_TYPE(TYPE, SIZE) const* const this) {\
    ASSERT(this);\
    return SIZE;\
}\
TYPE const* ARRAY_METHOD(TYPE, SIZE, data)(ARRAY_STRUCT_TYPE(TYPE, SIZE) const* const this) {\
    ASSERT(this);\
    return this->buffer_;\
}\
TYPE * ARRAY_METHOD(TYPE, SIZE, mut_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this, uint index) {\
    ASSERT(this);\
    return this->buffer_ + index;\
}\
TYPE const* ARRAY_METHOD(TYPE, SIZE, at)(ARRAY_STRUCT_TYPE(TYPE, SIZE) const* const this, uint index) {\
    ASSERT(this);\
    return this->buffer_ + index;\
}
#define IMPLEMENT_ARRAY(TYPE, SIZE) IMPLEMENT_ARRAY_(TYPE, SIZE)

#define DEFINE_ARRAY_(TYPE, SIZE)\
ARRAY_STRUCT_TYPE(TYPE, SIZE);\
\
static ARRAY_STRUCT_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this);\
static ARRAY_STRUCT_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_copy_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this, ARRAY_STRUCT_TYPE(TYPE, SIZE) const* const source);\
static ARRAY_STRUCT_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_by_value_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this, TYPE const* const value);\
static ARRAY_STRUCT_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_from_buffer_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this, TYPE const (*buffer)[SIZE]);\
void* ARRAY_METHOD(TYPE, SIZE, destroy_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this);\
\
static uint ARRAY_METHOD(TYPE, SIZE, size)(ARRAY_STRUCT_TYPE(TYPE, SIZE) const* const this);\
static TYPE const* ARRAY_METHOD(TYPE, SIZE, data)(ARRAY_STRUCT_TYPE(TYPE, SIZE) const* const this);\
static TYPE const* ARRAY_METHOD(TYPE, SIZE, at)(ARRAY_STRUCT_TYPE(TYPE, SIZE) const* const this, uint index);\
static TYPE * ARRAY_METHOD(TYPE, SIZE, mut_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this, uint index);\
typedef ARRAY_STRUCT_TYPE(TYPE, SIZE) {\
/*private:*/\
    TYPE buffer_[SIZE];\
} ARRAY_TYPE(TYPE, SIZE);\
\
static ARRAY_STRUCT_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this) {\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, construct_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index));\
    }\
    return this;\
}\
static ARRAY_STRUCT_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_copy_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this, ARRAY_STRUCT_TYPE(TYPE, SIZE) const* const source) {\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index), ARRAY_METHOD(TYPE, SIZE, at)(source, index));\
    }\
    return this;\
}\
static ARRAY_STRUCT_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_by_value_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this, TYPE const* const value) {\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index), value);\
    }\
    return this;\
}\
static ARRAY_STRUCT_TYPE(TYPE, SIZE)* ARRAY_METHOD(TYPE, SIZE, construct_from_buffer_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this, TYPE const (*buffer)[SIZE]){\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index), buffer[index]);\
    }\
    return this;\
}\
void* ARRAY_METHOD(TYPE, SIZE, destroy_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this){\
    ASSERT(this);\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE_METHOD(TYPE, destroy_at)(ARRAY_METHOD(TYPE, SIZE, mut_at)(this, index));\
    }\
    return this;\
}\
\
static uint ARRAY_METHOD(TYPE, SIZE, size)(ARRAY_STRUCT_TYPE(TYPE, SIZE) const* const this) {\
    ASSERT(this);\
    return SIZE;\
}\
static TYPE const* ARRAY_METHOD(TYPE, SIZE, data)(ARRAY_STRUCT_TYPE(TYPE, SIZE) const* const this) {\
    ASSERT(this);\
    return this->buffer_;\
}\
static TYPE * ARRAY_METHOD(TYPE, SIZE, mut_at)(ARRAY_STRUCT_TYPE(TYPE, SIZE)* const this, uint index) {\
    ASSERT(this);\
    return this->buffer_ + index;\
}\
static TYPE const* ARRAY_METHOD(TYPE, SIZE, at)(ARRAY_STRUCT_TYPE(TYPE, SIZE) const* const this, uint index) {\
    ASSERT(this);\
    return this->buffer_ + index;\
}
#define DEFINE_ARRAY(TYPE, SIZE) DEFINE_ARRAY_(TYPE, SIZE)
