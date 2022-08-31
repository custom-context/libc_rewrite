#pragma once

#include <construct/numeric_helpers.h>

#define DECLARE_ARRAY(TYPE, SIZE)\
struct array_##TYPE##_##SIZE;\
\
struct array_##TYPE##_##SIZE* array_##TYPE##_##SIZE##_construct_at(struct array_##TYPE##_##SIZE* const this);\
struct array_##TYPE##_##SIZE* array_##TYPE##_##SIZE##_construct_copy_at(struct array_##TYPE##_##SIZE* const this, struct array_##TYPE##_##SIZE const* const source);\
struct array_##TYPE##_##SIZE* array_##TYPE##_##SIZE##_construct_by_value_at(struct array_##TYPE##_##SIZE* const this, TYPE const* const value);\
struct array_##TYPE##_##SIZE* array_##TYPE##_##SIZE##_construct_from_buffer_at(struct array_##TYPE##_##SIZE* const this, TYPE const (*buffer)[SIZE]);\
void array_##TYPE##_##SIZE##_destroy_at(struct array_##TYPE##_##SIZE* const this);\
\
uint array_##TYPE##_##SIZE##_size(struct array_##TYPE##_##SIZE const* const this);\
TYPE const* array_##TYPE##_##SIZE##_data(struct array_##TYPE##_##SIZE const* const this);\
TYPE const* array_##TYPE##_##SIZE##_at(struct array_##TYPE##_##SIZE const* const this, uint index);\
TYPE * array_##TYPE##_##SIZE##_mut_at(struct array_##TYPE##_##SIZE* const this, uint index);\
\
typedef struct array_##TYPE##_##SIZE {\
/*private:*/\
    TYPE buffer_[SIZE];\
} array_##TYPE##_##SIZE

#define IMPLEMENT_ARRAY(TYPE, SIZE)\
struct array_##TYPE##_##SIZE* array_##TYPE##_##SIZE##_construct_at(struct array_##TYPE##_##SIZE* const this) {\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE##_construct_at(array_##TYPE##_##SIZE##_mut_at(this, index));\
    }\
    return this;\
}\
struct array_##TYPE##_##SIZE* array_##TYPE##_##SIZE##_construct_copy_at(struct array_##TYPE##_##SIZE* const this, struct array_##TYPE##_##SIZE const* const source) {\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE##_construct_copy_at(array_##TYPE##_##SIZE##_mut_at(this, index), array_##TYPE##_##SIZE##_at(source, index));\
    }\
    return this;\
}\
struct array_##TYPE##_##SIZE* array_##TYPE##_##SIZE##_construct_by_value_at(struct array_##TYPE##_##SIZE* const this, TYPE const* const value) {\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE##_construct_copy_at(array_##TYPE##_##SIZE##_mut_at(this, index), value);\
    }\
    return this;\
}\
struct array_##TYPE##_##SIZE* array_##TYPE##_##SIZE##_construct_from_buffer_at(struct array_##TYPE##_##SIZE* const this, TYPE const (*buffer)[SIZE]){\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE##_construct_copy_at(array_##TYPE##_##SIZE##_mut_at(this, index), buffer[index]);\
    }\
    return this;\
}\
void array_##TYPE##_##SIZE##_destroy_at(struct array_##TYPE##_##SIZE* const this){\
    for (uint index = 0u; index < SIZE; ++index) {\
        TYPE##_destroy_at(array_##TYPE##_##SIZE##_mut_at(this, index));\
    }\
}\
\
uint array_##TYPE##_##SIZE##_size(struct array_##TYPE##_##SIZE const* const this) {\
    return SIZE;\
}\
TYPE const* array_##TYPE##_##SIZE##_data(struct array_##TYPE##_##SIZE const* const this) {\
    return this->buffer_;\
}\
TYPE * array_##TYPE##_##SIZE##_mut_at(struct array_##TYPE##_##SIZE* const this, uint index) {\
    return this->buffer_ + index;\
}\
TYPE const* array_##TYPE##_##SIZE##_at(struct array_##TYPE##_##SIZE const* const this, uint index) {\
    return this->buffer_ + index;\
}
