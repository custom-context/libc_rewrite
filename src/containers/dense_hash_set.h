#pragma once

#include <utils/macros.h>

// dense_hash_map<type>
#define DENSE_HASH_SET_(TYPE) CONCAT3(dense_hash_set, _, TYPE)
#define DENSE_HASH_SET(TYPE) DENSE_HASH_SET_(TYPE)

// struct dense_hash_map<type>
#define DENSE_HASH_SET_STRUCT_(TYPE) struct DENSE_HASH_SET(TYPE)
#define DENSE_HASH_SET_STRUCT(TYPE) DENSE_HASH_SET_STRUCT_(TYPE)

// dense_hash_map<type>::method(...)
#define DENSE_HASH_SET_METHOD_(TYPE, METHOD) TYPE_METHOD(DENSE_HASH_SET(TYPE), METHOD)
#define DENSE_HASH_SET_METHOD(TYPE, METHOD) DENSE_HASH_SET_METHOD_(TYPE, METHOD)

// default dense_hash_map<type> count of buckets
#define DENSE_HASH_SET_BUFFER_DEFAULT_SIZE 16
// default dense_hash_map<type> max load factor
#define DENSE_HASH_SET_BUFFER_DEFAULT_MAX_LOAD_FACTOR .5f

// dense_hash_map<type>::iterator
#define DENSE_HASH_SET_ITERATOR_(TYPE) CONCAT3(DENSE_HASH_SET(TYPE), _, iterator)
#define DENSE_HASH_SET_ITERATOR(TYPE) DENSE_HASH_SET_ITERATOR_(TYPE)

// struct dense_hash_map<type>::iterator
#define DENSE_HASH_SET_ITERATOR_STRUCT_(TYPE) struct DENSE_HASH_SET_ITERATOR(TYPE)
#define DENSE_HASH_SET_ITERATOR_STRUCT(TYPE) DENSE_HASH_SET_ITERATOR_STRUCT_(TYPE)

// struct dense_hash_map<type>::iterator::method(...)
#define DENSE_HASH_SET_ITERATOR_METHOD_(TYPE) TYPE_METHOD(DENSE_HASH_SET_ITERATOR(TYPE), METHOD)
#define DENSE_HASH_SET_ITERATOR_METHOD(TYPE) DENSE_HASH_SET_ITERATOR_METHOD_(TYPE)


// dense_hash_map<type>::const_iterator
#define DENSE_HASH_SET_CONST_ITERATOR_(TYPE) CONCAT3(DENSE_HASH_SET(TYPE), _, const_iterator)
#define DENSE_HASH_SET_CONST_ITERATOR(TYPE) DENSE_HASH_SET_CONST_ITERATOR_(TYPE)

// struct dense_hash_map<type>::const_iterator
#define DENSE_HASH_SET_CONST_ITERATOR_STRUCT_(TYPE) struct DENSE_HASH_SET_CONST_ITERATOR(TYPE)
#define DENSE_HASH_SET_CONST_ITERATOR_STRUCT(TYPE) DENSE_HASH_SET_CONST_ITERATOR_STRUCT_(TYPE)

// struct dense_hash_map<type>::const_iterator::method(...)
#define DENSE_HASH_SET_CONST_ITERATOR_METHOD_(TYPE) TYPE_METHOD(DENSE_HASH_SET_CONST_ITERATOR(TYPE), METHOD)
#define DENSE_HASH_SET_CONST_ITERATOR_METHOD(TYPE) DENSE_HASH_SET_CONST_ITERATOR_METHOD_(TYPE)


// dense_hash_map<type>:hash function
#define DENSE_HASH_SET_HASH_FUNCTION_FOR_TYPE_(TYPE) FUNCTION_FOR_TYPE(hash, CONCAT3(DENSE_HASH_SET_STRUCT(TYPE), _, type))
#define DENSE_HASH_SET_HASH_FUNCTION_FOR_TYPE(TYPE) DENSE_HASH_SET_HASH_FUNCTION_FOR_TYPE_(TYPE)

// static uint dense_hash_map<type>:hash(type const* const value)
#define DEFINE_DENSE_HASH_SET_HASH_FUNCTION_FOR_TYPE_(TYPE)\
static uint DENSE_HASH_SET_HASH_FUNCTION_FOR_TYPE(TYPE)(TYPE const* const value)
#define DEFINE_DENSE_HASH_SET_HASH_FUNCTION_FOR_TYPE(TYPE) DEFINE_DENSE_HASH_SET_HASH_FUNCTION_FOR_TYPE_(TYPE)

// dense_hash_map<type>:hash_pointer_type
#define POINTER_TO_DENSE_HASH_SET_HASH_FUNCTION_FOR_TYPE_(TYPE) CONCAT3(DENSE_HASH_SET_HASH_FUNCTION_FOR_TYPE(TYPE), _, pointer_type)
#define POINTER_TO_DENSE_HASH_SET_HASH_FUNCTION_FOR_TYPE(TYPE) POINTER_TO_DENSE_HASH_SET_HASH_FUNCTION_FOR_TYPE_(TYPE)

// dense_hash_map<type>:hash_pointer_type = uint (*)(type const* const)
#define DEFINE_POINTER_TO_DENSE_HASH_SET_HASH_FUNCTION_FOR_TYPE_(TYPE)\
typedef uint (*POINTER_TO_DENSE_HASH_SET_HASH_FUNCTION_FOR_TYPE(TYPE))(TYPE const* const)
#define DEFINE_POINTER_TO_DENSE_HASH_SET_HASH_FUNCTION_FOR_TYPE(TYPE) DEFINE_POINTER_TO_DENSE_HASH_SET_HASH_FUNCTION_FOR_TYPE_(TYPE)


// dense_hash_map<type>::node
#define DENSE_HASH_SET_NODE_(TYPE) CONCAT3(DENSE_HASH_SET(TYPE), _, node)
#define DENSE_HASH_SET_NODE(TYPE) DENSE_HASH_SET_NODE_(TYPE)

#define DENSE_HASH_SET_NODE_STRUCT_(TYPE) struct DENSE_HASH_SET_NODE(TYPE)
#define DENSE_HASH_SET_NODE_STRUCT(TYPE) DENSE_HASH_SET_NODE_STRUCT_(TYPE)


// dense_hash_map<type>::node::state
#define DENSE_HASH_SET_NODE_STATE_(TYPE) CONCAT3(DENSE_HASH_SET_NODE(TYPE), _, node)
#define DENSE_HASH_SET_NODE_STATE(TYPE) DENSE_HASH_SET_NODE_STATE_(TYPE)

// enum dense_hash_map<type>::node::state
#define DENSE_HASH_SET_NODE_STATE_ENUM_(TYPE) enum DENSE_HASH_SET_NODE_STATE(TYPE)
#define DENSE_HASH_SET_NODE_STATE_ENUM(TYPE) DENSE_HASH_SET_NODE_STATE_(TYPE)

// dense_hash_map<type>::node::state::value
#define DENSE_HASH_SET_NODE_STATE_VALUE_(TYPE, VALUE) TYPE_MEMBER(DENSE_HASH_SET_NODE_STATE_ENUM(TYPE), VALUE)
#define DENSE_HASH_SET_NODE_STATE_VALUE(TYPE, VALUE) DENSE_HASH_SET_NODE_STATE_(TYPE, VALUE)

#define DEFINE_DENSE_HASH_SET_(TYPE)\
DENSE_HASH_SET_STRUCT(TYPE);\
DENSE_HASH_SET_NODE_STATE_ENUM(TYPE);\
DENSE_HASH_SET_NODE_STRUCT(TYPE);\
DENSE_HASH_SET_ITERATOR_STRUCT(TYPE);\
/* --- Iterator(s) functions --- */\
static DENSE_HASH_SET_ITERATOR_STRUCT(TYPE)* DENSE_HASH_SET_ITERATOR_METHOD(TYPE, construct_end_at)(DENSE_HASH_SET_ITERATOR_STRUCT(TYPE)* const this, DENSE_HASH_SET_STRUCT(TYPE)* const container);\
static DENSE_HASH_SET_ITERATOR_STRUCT(TYPE)* DENSE_HASH_SET_ITERATOR_METHOD(TYPE, construct_begin_at)(DENSE_HASH_SET_ITERATOR_STRUCT(TYPE)* const this, DENSE_HASH_SET_STRUCT(TYPE)* const container);\
static DENSE_HASH_SET_CONST_ITERATOR_STRUCT(TYPE)* DENSE_HASH_SET_CONST_ITERATOR_METHOD(TYPE, construct_cend_at)(DENSE_HASH_SET_CONST_ITERATOR_STRUCT(TYPE)* const this, DENSE_HASH_SET_STRUCT(TYPE) const* const container);\
static DENSE_HASH_SET_CONST_ITERATOR_STRUCT(TYPE)* DENSE_HASH_SET_CONST_ITERATOR_METHOD(TYPE, construct_cbegin_at)(DENSE_HASH_SET_CONST_ITERATOR_STRUCT(TYPE)* const this, DENSE_HASH_SET_STRUCT(TYPE) const* const container);\
static TYPE const* DENSE_HASH_SET_CONST_ITERATOR_METHOD(TYPE, unwrap)(DENSE_HASH_SET_CONST_ITERATOR_STRUCT(TYPE) const* const this);\
static TYPE* DENSE_HASH_SET_ITERATOR_METHOD(TYPE, unwrap)(DENSE_HASH_SET_ITERATOR_STRUCT(TYPE) const* const this);\
static uint FUNCTION_FOR_TYPE2(equals, DENSE_HASH_SET_CONST_ITERATOR(TYPE), DENSE_HASH_SET_CONST_ITERATOR(TYPE))(DENSE_HASH_SET_CONST_ITERATOR(TYPE) const* const iterator1, DENSE_HASH_SET_CONST_ITERATOR(TYPE) const* const iterator2);\
static uint FUNCTION_FOR_TYPE2(equals, DENSE_HASH_SET_ITERATOR(TYPE), DENSE_HASH_SET_CONST_ITERATOR(TYPE))(DENSE_HASH_SET_ITERATOR(TYPE) const* const iterator1, DENSE_HASH_SET_CONST_ITERATOR(TYPE) const* const iterator2);\
static uint FUNCTION_FOR_TYPE2(equals, DENSE_HASH_SET_CONST_ITERATOR(TYPE), DENSE_HASH_SET_ITERATOR(TYPE))(DENSE_HASH_SET_ITERATOR(TYPE) const* const iterator1, DENSE_HASH_SET_CONST_ITERATOR(TYPE) const* const iterator2);\
static uint FUNCTION_FOR_TYPE2(equals, DENSE_HASH_SET_ITERATOR(TYPE), DENSE_HASH_SET_ITERATOR(TYPE))(DENSE_HASH_SET_ITERATOR(TYPE) const* const iterator1, DENSE_HASH_SET_ITERATOR(TYPE) const* const iterator2);\
/* --- Construction/Destruction functions --- */\
static DENSE_HASH_SET_STRUCT(TYPE)* DENSE_HASH_SET_METHOD(TYPE, construct_at)(DENSE_HASH_SET_STRUCT(TYPE)* const this);\
static DENSE_HASH_SET_STRUCT(TYPE)* DENSE_HASH_SET_METHOD(TYPE, construct_copy_at)(DENSE_HASH_SET_STRUCT(TYPE)* const this, DENSE_HASH_SET_STRUCT(TYPE) const* const source);\
static DENSE_HASH_SET_STRUCT(TYPE)* DENSE_HASH_SET_METHOD(TYPE, construct_move_at)(DENSE_HASH_SET_STRUCT(TYPE)* const this, DENSE_HASH_SET_STRUCT(TYPE)* const source);\
static DENSE_HASH_SET_STRUCT(TYPE)* DENSE_HASH_SET_METHOD(TYPE, construct_with_size_at)(DENSE_HASH_SET_STRUCT(TYPE)* const this, uint const size);\
static DENSE_HASH_SET_STRUCT(TYPE)* DENSE_HASH_SET_METHOD(TYPE, construct_from_buffer_at)(DENSE_HASH_SET_STRUCT(TYPE)* const this, uint const buffer_size, TYPE const* const buffer);\
static void DENSE_HASH_SET_METHOD(TYPE, destroy_at)(DENSE_HASH_SET_STRUCT(TYPE)* const this);\
/* --- Assignment functions --- */\
static DENSE_HASH_SET_STRUCT(TYPE)* DENSE_HASH_SET_METHOD(TYPE, assign_move_from_dense_hash_set)(DENSE_HASH_SET_STRUCT(TYPE)* const this, DENSE_HASH_SET_STRUCT(TYPE)* const source);\
static DENSE_HASH_SET_STRUCT(TYPE)* DENSE_HASH_SET_METHOD(TYPE, assign_copy_from_dense_hash_set)(DENSE_HASH_SET_STRUCT(TYPE)* const this, DENSE_HASH_SET_STRUCT(TYPE) const* const source);\
static DENSE_HASH_SET_STRUCT(TYPE)* DENSE_HASH_SET_METHOD(TYPE, assign_from_buffer_at)(DENSE_HASH_SET_STRUCT(TYPE)* const this, uint const buffer_size, TYPE const* const buffer);\
/* --- Memory managment functions --- */\
static DENSE_HASH_SET_STRUCT(TYPE)* DENSE_HASH_SET_METHOD(TYPE, reserve)(DENSE_HASH_SET_STRUCT(TYPE)* const this, uint const target_count_of_elements);\
static DENSE_HASH_SET_STRUCT(TYPE)* DENSE_HASH_SET_METHOD(TYPE, rehash)(DENSE_HASH_SET_STRUCT(TYPE)* const this, uint const new_capacity);\
/* --- Getters functions --- */\
/*`load_factor()` returns current ratio of `size() * 1.f / bucket_count()`*/\
static float DENSE_HASH_SET_METHOD(TYPE, load_factor)(DENSE_HASH_SET_STRUCT(TYPE) const* const this);\
/*`get_max_load_factor()` returns max possible ratio of `size() * 1.f / bucket_count()`*/\
static float DENSE_HASH_SET_METHOD(TYPE, get_max_load_factor)(DENSE_HASH_SET_STRUCT(TYPE) const* const this);\
/*`set_max_load_factor(new_max_load_factor)` sets max possible ratio of `size() * 1.f / bucket_count()`*/\
static void DENSE_HASH_SET_METHOD(TYPE, set_max_load_factor)(DENSE_HASH_SET_STRUCT(TYPE)* const this, float new_max_load_factor);\
/*`bucket_count()` returns count of cells*/\
static uint DENSE_HASH_SET_METHOD(TYPE, bucket_count)(DENSE_HASH_SET_STRUCT(TYPE) const* const this);\
/*`size()` returns count of elements*/\
static uint DENSE_HASH_SET_METHOD(TYPE, size)(DENSE_HASH_SET_STRUCT(TYPE) const* const this);\
/*`empty()` returns !size()*/\
static uint DENSE_HASH_SET_METHOD(TYPE, empty)(DENSE_HASH_SET_STRUCT(TYPE) const* const this);\
/*`count(key)` returns count of elements with setted key*/\
static uint DENSE_HASH_SET_METHOD(TYPE, count)(DENSE_HASH_SET_STRUCT(TYPE) const* const this, TYPE const* const key);\
/*`contains(key)` returns `!count(key)`*/\
static uint DENSE_HASH_SET_METHOD(TYPE, contains)(DENSE_HASH_SET_STRUCT(TYPE) const* const this, TYPE const* const key);\
/*dense_hash_map<type>::node::state enum definition*/\
typedef DENSE_HASH_SET_NODE_STATE_ENUM(TYPE) {\
    DENSE_HASH_SET_NODE_STATE_VALUE(TYPE, EMPTY),\
    DENSE_HASH_SET_NODE_STATE_VALUE(TYPE, USED),\
    DENSE_HASH_SET_NODE_STATE_VALUE(TYPE, FILLED)\
} DENSE_HASH_SET_NODE_STATE(TYPE);\
/*dense_hash_map<type>::node struct definition*/\
typedef DENSE_HASH_SET_NODE_STRUCT(TYPE) {\
    TYPE value_;\
    DENSE_HASH_SET_NODE_STATE_ENUM(TYPE) state_;\
} DENSE_HASH_SET_NODE(TYPE);\
/*dense_hash_map<type>::iterator struct definition*/\
typedef DENSE_HASH_SET_ITERATOR_STRUCT(TYPE) {\
    DENSE_HASH_SET(TYPE)* /*const*/ container_;\
    uint index_;\
} DENSE_HASH_SET_ITERATOR(TYPE);\
/*dense_hash_map<type>::const_iterator struct definition*/\
typedef DENSE_HASH_SET_CONST_ITERATOR_STRUCT(TYPE) {\
    DENSE_HASH_SET(TYPE) const* /*const*/ container_;\
    uint index_;\
} DENSE_HASH_SET_CONST_ITERATOR(TYPE);\
/*dense_hash_map<type> struct definition*/\
typedef DENSE_HASH_SET_STRUCT(TYPE) {\
/*private:*/\
    DENSE_HASH_SET_NODE(TYPE)* buffer_;\
    uint capacity_, size_;\
    float max_load_factor_;\
    \
} DENSE_HASH_SET(TYPE);\
/* --- Iterator functions --- */\
static DENSE_HASH_SET_ITERATOR_STRUCT(TYPE)* DENSE_HASH_SET_ITERATOR_METHOD(TYPE, construct_begin_at)(DENSE_HASH_SET_ITERATOR_STRUCT(TYPE)* const this, DENSE_HASH_SET_STRUCT(TYPE)* const container) {\
    this->container_ = container;\
    uint const container_size = DENSE_HASH_SET_METHOD(TYPE, size)(container);\
    for (this->index_ = 0u; this->index_ < container_size; ++this->index_) {\
        if (container->buffer_[this->index_].state_ == DENSE_HASH_SET_NODE_STATE_VALUE(TYPE, FILLED)) {\
            break;\
        }\
    }\
    return this;\
}\
static DENSE_HASH_SET_ITERATOR_STRUCT(TYPE)* DENSE_HASH_SET_ITERATOR_METHOD(TYPE, construct_end_at)(DENSE_HASH_SET_ITERATOR_STRUCT(TYPE)* const this, DENSE_HASH_SET_STRUCT(TYPE)* const container) {\
    this->container_ = container;\
    this->index_ = DENSE_HASH_SET_METHOD(TYPE, size)(container);\
    return this;\
}\
static DENSE_HASH_SET_CONST_ITERATOR_STRUCT(TYPE)* DENSE_HASH_SET_CONST_ITERATOR_METHOD(TYPE, construct_cbegin_at)(DENSE_HASH_SET_CONST_ITERATOR_STRUCT(TYPE)* const this, DENSE_HASH_SET_STRUCT(TYPE) const* const container) {\
    this->container_ = container;\
    uint const container_size = DENSE_HASH_SET_METHOD(TYPE, size)(this->container_);\
    for (this->index_ = 0u; this->index_ < container_size; ++this->index_) {\
        if (this->container_->buffer_[this->index_].state_ == DENSE_HASH_SET_NODE_STATE_VALUE(TYPE, FILLED)) {\
            break;\
        }\
    }\
    return this;\
}\
static DENSE_HASH_SET_CONST_ITERATOR_STRUCT(TYPE)* DENSE_HASH_SET_CONST_ITERATOR_METHOD(TYPE, construct_cend_at)(DENSE_HASH_SET_CONST_ITERATOR_STRUCT(TYPE)* const this, DENSE_HASH_SET_STRUCT(TYPE) const* const container) {\
    this->container_ = container;\
    this->index_ = DENSE_HASH_SET_METHOD(TYPE, size)(container);\
    return this;\
}\
static TYPE const* DENSE_HASH_SET_CONST_ITERATOR_METHOD(TYPE, unwrap)(DENSE_HASH_SET_CONST_ITERATOR_STRUCT(TYPE) const* const this) {\
    return &(this->buffer_[this->index_].value_);\
}\
static TYPE* DENSE_HASH_SET_ITERATOR_METHOD(TYPE, unwrap)(DENSE_HASH_SET_ITERATOR_STRUCT(TYPE) const* const this) {\
    return &(this->buffer_[this->index_].value_);\
}\
static DENSE_HASH_SET_CONST_ITERATOR_STRUCT(TYPE)* DENSE_HASH_SET_CONST_ITERATOR_METHOD(TYPE, pre_increment)(DENSE_HASH_SET_CONST_ITERATOR_STRUCT(TYPE)* const this) {\
    uint const container_size = DENSE_HASH_SET_METHOD(TYPE, size)(this->container_);\
    for (; this->index_ < container_size; ++this->index_) {\
        if (this->container_->buffer_[this->index_].state_ == DENSE_HASH_SET_NODE_STATE_VALUE(TYPE, FILLED)) {\
            break;\
        }\
    }\
    return this;\
}\
static DENSE_HASH_SET_ITERATOR_STRUCT(TYPE)* DENSE_HASH_SET_ITERATOR_METHOD(TYPE, pre_increment)(DENSE_HASH_SET_ITERATOR_STRUCT(TYPE)* const this) {\
    uint const container_size = DENSE_HASH_SET_METHOD(TYPE, size)(this->container_);\
    for (; this->index_ < container_size; ++this->index_) {\
        if (this->container_->buffer_[this->index_].state_ == DENSE_HASH_SET_NODE_STATE_VALUE(TYPE, FILLED)) {\
            break;\
        }\
    }\
    return this;\
}\
static uint FUNCTION_FOR_TYPE2(equals, DENSE_HASH_SET_CONST_ITERATOR(TYPE), DENSE_HASH_SET_CONST_ITERATOR(TYPE))(DENSE_HASH_SET_CONST_ITERATOR(TYPE) const* const iterator1, DENSE_HASH_SET_CONST_ITERATOR(TYPE) const* const iterator2) {\
    return iterator1->container_ == iterator2->container_ && iterator1->index_ == iterator2->index_;\
}\
static uint FUNCTION_FOR_TYPE2(equals, DENSE_HASH_SET_ITERATOR(TYPE), DENSE_HASH_SET_CONST_ITERATOR(TYPE))(DENSE_HASH_SET_ITERATOR(TYPE) const* const iterator1, DENSE_HASH_SET_CONST_ITERATOR(TYPE) const* const iterator2) {\
    return iterator1->container_ == iterator2->container_ && iterator1->index_ == iterator2->index_;\
}\
static uint FUNCTION_FOR_TYPE2(equals, DENSE_HASH_SET_CONST_ITERATOR(TYPE), DENSE_HASH_SET_ITERATOR(TYPE))(DENSE_HASH_SET_ITERATOR(TYPE) const* const iterator1, DENSE_HASH_SET_CONST_ITERATOR(TYPE) const* const iterator2) {\
    return iterator1->container_ == iterator2->container_ && iterator1->index_ == iterator2->index_;\
}\
static uint FUNCTION_FOR_TYPE2(equals, DENSE_HASH_SET_ITERATOR(TYPE), DENSE_HASH_SET_ITERATOR(TYPE))(DENSE_HASH_SET_ITERATOR(TYPE) const* const iterator1, DENSE_HASH_SET_ITERATOR(TYPE) const* const iterator2) {\
    return iterator1->container_ == iterator2->container_ && iterator1->index_ == iterator2->index_;\
}\
/* --- Construction/Destruction functions implementation --- */\
static DENSE_HASH_SET_STRUCT(TYPE)* DENSE_HASH_SET_METHOD(TYPE, construct_at)(DENSE_HASH_SET_STRUCT(TYPE)* const this) {\
    DENSE_HASH_SET_METHOD(TYPE, construct_with_size_at)(this, DENSE_HASH_SET_BUFFER_DEFAULT_SIZE);\
    return this;\
}\
static DENSE_HASH_SET_STRUCT(TYPE)* DENSE_HASH_SET_METHOD(TYPE, construct_copy_at)(DENSE_HASH_SET_STRUCT(TYPE)* const this, DENSE_HASH_SET_STRUCT(TYPE) const* const source) {\
    DENSE_HASH_SET_METHOD(TYPE, construct_at)(this);\
    uint const size = DENSE_HASH_SET_METHOD(TYPE, size)(source);\
    DENSE_HASH_SET_METHOD(TYPE, reserve)(this, size);\
    DENSE_HASH_SET_ITERATOR(TYPE) iterator, cend;\
    DENSE_HASH_SET_CONST_ITERATOR_METHOD(TYPE, construct_cend_at)(&cend, source);\
    for (DENSE_HASH_SET_CONST_ITERATOR_METHOD(TYPE, construct_cbegin_at)(&iterator, source); !FUNCTION_FOR_TYPE2(equals, DENSE_HASH_SET_CONST_ITERATOR(TYPE), DENSE_HASH_SET_CONST_ITERATOR(TYPE))(&iterator, &cend); DENSE_HASH_SET_CONST_ITERATOR_METHOD(TYPE, pre_increment)(&iterator)) {\
        DENSE_HASH_SET_METHOD(TYPE, emplace_copy)(this, DENSE_HASH_SET_CONST_ITERATOR_METHOD(TYPE, unwrap)(&iterator));\
    }\
    return this;\
}\
static DENSE_HASH_SET_STRUCT(TYPE)* DENSE_HASH_SET_METHOD(TYPE, construct_move_at)(DENSE_HASH_SET_STRUCT(TYPE)* const this, DENSE_HASH_SET_STRUCT(TYPE)* const source) {\
    DENSE_HASH_SET_METHOD(TYPE, construct_at)(this);\
    {\
        DENSE_HASH_SET_NODE(TYPE)* temporary_buffer_ = this->buffer_;\
        this->buffer_ = source->buffer_;\
        source->buffer_ = temporary_buffer_;\
    }\
    {\
        uint temporary_capacity_ = this->capacity_;\
        this->capacity_ = source->capacity_;\
        source->capacity_ = temporary_capacity_;\
    }\
    {\
        uint temporary_size_ = this->size_;\
        this->size_ = source->size_;\
        source->size_ = temporary_size_;\
    }\
    {\
        uint temporary_max_load_factor_ = this->max_load_factor_;\
        this->max_load_factor_ = source->max_load_factor_;\
        source->max_load_factor_ = temporary_max_load_factor_;\
    }\
    return this;\
}\
static DENSE_HASH_SET_STRUCT(TYPE)* DENSE_HASH_SET_METHOD(TYPE, construct_with_size_at)(DENSE_HASH_SET_STRUCT(TYPE)* const this, uint const size) {\
    this->buffer_ = NULL;\
    this->size_ = this->capacity_ = 0;\
    this->max_load_factor_ = DENSE_HASH_SET_BUFFER_DEFAULT_MAX_LOAD_FACTOR;\
    DENSE_HASH_SET_METHOD(TYPE, reserve)(this, size);\
    return this;\
}\
static DENSE_HASH_SET_STRUCT(TYPE)* DENSE_HASH_SET_METHOD(TYPE, construct_from_buffer_at)(DENSE_HASH_SET_STRUCT(TYPE)* const this, uint const buffer_size, TYPE const* const buffer) {\
    DENSE_HASH_SET_METHOD(TYPE, construct_at)(this);\
    DENSE_HASH_SET_METHOD(TYPE, reserve)(this, buffer_size);\
    for (uint index = 0u; index < buffer_size; ++index) {\
        DENSE_HASH_SET_METHOD(TYPE, emplace_copy)(this, &buffer[index]);\
    }\
    return this;\
}\
static void DENSE_HASH_SET_METHOD(TYPE, destroy_at)(DENSE_HASH_SET_STRUCT(TYPE)* const this) {\
    DENSE_HASH_SET_ITERATOR(TYPE) iterator, end;\
    DENSE_HASH_SET_ITERATOR_METHOD(TYPE, construct_cend_at)(&cend, this);\
    for (DENSE_HASH_SET_ITERATOR_METHOD(TYPE, construct_cbegin_at)(&iterator, this); !FUNCTION_FOR_TYPE2(equals, DENSE_HASH_SET_ITERATOR(TYPE), DENSE_HASH_SET_ITERATOR(TYPE))(&iterator, &cend); DENSE_HASH_SET_ITERATOR_METHOD(TYPE, pre_increment)(&iterator)) {\
        TYPE_METHOD(TYPE, destroy_at)(DENSE_HASH_SET_ITERATOR_METHOD(TYPE, unwrap)(&iterator));\
    }\
    free(this->buffer_);\
}\
/* --- Memory managment functions implementation --- */\
static DENSE_HASH_SET_STRUCT(TYPE)* DENSE_HASH_SET_METHOD(TYPE, reserve)(DENSE_HASH_SET_STRUCT(TYPE)* const this, uint const target_count_of_elements) {\
    return DENSE_HASH_SET_METHOD(TYPE, rehash)(this, target_count_of_elements * 1.f / DENSE_HASH_SET_METHOD(TYPE, get_max_load_factor)(this));\
}\
static DENSE_HASH_SET_STRUCT(TYPE)* DENSE_HASH_SET_METHOD(TYPE, rehash)(DENSE_HASH_SET_STRUCT(TYPE)* const this, uint const new_capacity) {\
    \
    return this;\
}\

#define DEFINE_DENSE_HASH_SET(TYPE) DEFINE_DENSE_HASH_SET_(TYPE)
