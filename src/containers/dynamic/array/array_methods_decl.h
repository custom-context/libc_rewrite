#pragma once

#include <containers/iterator/iterator.h>
#include <containers/dynamic/common.h>

// dynamic array type method
#define DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, METHOD) TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), METHOD)
#define DYNAMIC_ARRAY_METHOD(TYPE, METHOD) DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE), METHOD)

// dynamic array type iterator method
#define DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_METHOD(TYPE, ALLOCATOR_TYPE, METHOD)\
    ITERATOR_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), METHOD)
#define DYNAMIC_ARRAY_ITERATOR_METHOD(TYPE, METHOD) ITERATOR_METHOD(DYNAMIC_ARRAY_TYPE(TYPE), METHOD)

// dynamic array type const iterator method
#define DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_METHOD(TYPE, ALLOCATOR_TYPE, METHOD)\
    CONST_ITERATOR_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), METHOD)
#define DYNAMIC_ARRAY_CONST_ITERATOR_METHOD(TYPE, METHOD) CONST_ITERATOR_METHOD(DYNAMIC_ARRAY_TYPE(TYPE), METHOD)

// dynamic array type reverse iterator method
#define DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_METHOD(TYPE, ALLOCATOR_TYPE, METHOD)\
    REVERSE_ITERATOR_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), METHOD)
#define DYNAMIC_ARRAY_REVERSE_ITERATOR_METHOD(TYPE, METHOD) REVERSE_ITERATOR_METHOD(DYNAMIC_ARRAY_ITERATOR_TYPE(TYPE), METHOD)

// dynamic array type reverse const iterator method
#define DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_METHOD(TYPE, ALLOCATOR_TYPE, METHOD)\
    REVERSE_ITERATOR_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), METHOD)
#define DYNAMIC_ARRAY_REVERSE_CONST_ITERATOR_METHOD(TYPE, METHOD) REVERSE_ITERATOR_METHOD(DYNAMIC_ARRAY_CONST_ITERATOR_TYPE(TYPE), METHOD)

// construct_by_iterators_*_at method macro helpers
#define DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_CONSTRUCT_BY_ITERATORS(TYPE, ALLOCATOR_TYPE, ITERATOR_TYPE)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, CONCAT5(construct_by_iterators, _, ITERATOR_TYPE, _, at))
#define DYNAMIC_ARRAY_TYPE_CONSTRUCT_BY_ITERATORS(TYPE, TYPE_CONSTRUCTOR) DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_CONSTRUCT_BY_ITERATORS(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE), ITERATOR_TYPE)

// insert_copy_by_*iterator_type* method macro helpers
#define DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_COPY_BY(TYPE, ALLOCATOR_TYPE, ITERATOR_TYPE)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, CONCAT3(insert_copy_by, _, ITERATOR_TYPE))
#define DYNAMIC_ARRAY_TYPE_INSERT_COPY_BY(TYPE, ITERATOR_TYPE) DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_COPY_BY(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE), ITERATOR_TYPE)

// insert_count_copy_by_*iterator_type* method macro helper
#define DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_COUNT_COPY_BY(TYPE, ALLOCATOR_TYPE, ITERATOR_TYPE)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, CONCAT3(insert_count_copy_by, _, ITERATOR_TYPE))
#define DYNAMIC_ARRAY_TYPE_INSERT_COUNT_COPY_BY(TYPE, ITERATOR_TYPE)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_COUNT_COPY_BY(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE), ITERATOR_TYPE)

// insert_move_by_*iterator_type* method macro helpers
#define DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_MOVE_BY(TYPE, ALLOCATOR_TYPE, ITERATOR_TYPE)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, CONCAT3(insert_move_by, _, ITERATOR_TYPE))
#define DYNAMIC_ARRAY_TYPE_INSERT_MOVE_BY(TYPE, ITERATOR_TYPE) DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_MOVE_BY(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE), ITERATOR_TYPE)

// emplace_back method macro helpers
#define DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_EMPLACE_BACK(TYPE, ALLOCATOR_TYPE, TYPE_CONSTRUCTOR)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, CONCAT3(emplace_back_by_using, _, TYPE_CONSTRUCTOR))
#define DYNAMIC_ARRAY_TYPE_EMPLACE_BACK(TYPE, TYPE_CONSTRUCTOR) DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_EMPLACE_BACK(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE), TYPE_CONSTRUCTOR)

// emplace_by_*iterator_type*_using_*type_constructor* method macro helpers
#define DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_EMPLACE_BY(TYPE, ALLOCATOR_TYPE, ITERATOR_TYPE, TYPE_CONSTRUCTOR)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, CONCAT7(emplace_by, _, ITERATOR_TYPE, _, using, _, TYPE_CONSTRUCTOR))
#define DYNAMIC_ARRAY_TYPE_EMPLACE_BY(TYPE, ITERATOR_TYPE, TYPE_CONSTRUCTOR) DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_EMPLACE_BY(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE), ITERATOR_TYPE, TYPE_CONSTRUCTOR)

// erase_by_*iterator_type* method macro helpers
#define DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_ERASE_BY(TYPE, ALLOCATOR_TYPE, ITERATOR_TYPE)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, CONCAT3(erase_by, _, ITERATOR_TYPE))
#define DYNAMIC_ARRAY_TYPE_ERASE_BY(TYPE, ITERATOR_TYPE) DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_ERASE_BY(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE), ITERATOR_TYPE)

// dynamic array methods related declarations
// construct_by_iterators_*_at method macro helpers
#define DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_CONSTRUCT_BY_ITERATORS(TYPE, ALLOCATOR_TYPE, ITERATOR_TYPE)\
struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_CONSTRUCT_BY_ITERATORS(TYPE, ALLOCATOR_TYPE, ITERATOR_TYPE)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
    struct ITERATOR_TYPE begin, struct ITERATOR_TYPE end)
#define DECLARE_DYNAMIC_ARRAY_TYPE_CONSTRUCT_BY_ITERATORS(TYPE, ALLOCATOR_TYPE, ITERATOR_TYPE)\
    DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_CONSTRUCT_BY_ITERATORS(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE), ITERATOR_TYPE)

// insert_move_by_*iterator_type* method macro helpers
#define DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_MOVE_BY(TYPE, ALLOCATOR_TYPE, RETURN_ITERATOR_TYPE, POSITION_ITERATOR_TYPE)\
    struct RETURN_ITERATOR_TYPE DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_MOVE_BY(TYPE, ALLOCATOR_TYPE, POSITION_ITERATOR_TYPE)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct POSITION_ITERATOR_TYPE const position,\
        TYPE* const value\
    )
#define DECLARE_DYNAMIC_ARRAY_TYPE_INSERT_MOVE_BY(TYPE, RETURN_ITERATOR_TYPE, POSITION_ITERATOR_TYPE) DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_MOVE_BY(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE), RETURN_ITERATOR_TYPE, POSITION_ITERATOR_TYPE)

// insert_copy_by_*iterator_type* method macro helpers
#define DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_COPY_BY(TYPE, ALLOCATOR_TYPE, RETURN_ITERATOR_TYPE, POSITION_ITERATOR_TYPE)\
    struct RETURN_ITERATOR_TYPE DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_COPY_BY(TYPE, ALLOCATOR_TYPE, POSITION_ITERATOR_TYPE)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct POSITION_ITERATOR_TYPE const position,\
        TYPE const* const value\
    )
#define DECLARE_DYNAMIC_ARRAY_TYPE_INSERT_COPY_BY(TYPE, RETURN_ITERATOR_TYPE, POSITION_ITERATOR_TYPE) DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_COPY_BY(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE), RETURN_ITERATOR_TYPE, POSITION_ITERATOR_TYPE)

// insert_count_copy_by_*iterator_type* method macro helpers
#define DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_COUNT_COPY_BY(TYPE, ALLOCATOR_TYPE, RETURN_ITERATOR_TYPE, POSITION_ITERATOR_TYPE)\
    struct RETURN_ITERATOR_TYPE DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_COUNT_COPY_BY(TYPE, ALLOCATOR_TYPE, POSITION_ITERATOR_TYPE)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct POSITION_ITERATOR_TYPE const position,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const count,\
        TYPE const* const value\
    )
#define DECLARE_DYNAMIC_ARRAY_TYPE_INSERT_COUNT_COPY_BY(TYPE, RETURN_ITERATOR_TYPE, POSITION_ITERATOR_TYPE) DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_COUNT_COPY_BY(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE), RETURN_ITERATOR_TYPE, POSITION_ITERATOR_TYPE)

// insert_by_*iterator_type1*_from_*iterator_type2*_iterators method macro helpers [customly defined for iterator_type2]
#define DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_FROM_ITERATORS(TYPE, ALLOCATOR_TYPE, RETURN_ITERATOR_TYPE, POSITION_ITERATOR_TYPE, OPEN_ITERATOR_TYPE)\
    struct RETURN_ITERATOR_TYPE DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_COPY_BY(TYPE, ALLOCATOR_TYPE, POSITION_ITERATOR_TYPE)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct POSITION_ITERATOR_TYPE const position,\
        struct OPEN_ITERATOR_TYPE begin,\
        struct OPEN_ITERATOR_TYPE end\
    )
#define DECLARE_DYNAMIC_ARRAY_TYPE_INSERT_FROM_ITERATORS(TYPE, RETURN_ITERATOR_TYPE, POSITION_ITERATOR_TYPE, OPEN_ITERATOR_TYPE) DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_FROM_ITERATORS(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE), RETURN_ITERATOR_TYPE, POSITION_ITERATOR_TYPE, OPEN_ITERATOR_TYPE)

// emplace_back method macro helpers
#define DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_EMPLACE_BACK(TYPE, ALLOCATOR_TYPE, TYPE_CONSTRUCTOR)\
    void DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_EMPLACE_BACK(TYPE, ALLOCATOR_TYPE, TYPE_CONSTRUCTOR)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        ...)
#define DECLARE_DYNAMIC_ARRAY_TYPE_EMPLACE_BACK(TYPE, ALLOCATOR_TYPE, TYPE_CONSTRUCTOR)\
    DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_EMPLACE_BACK(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE), TYPE_CONSTRUCTOR)

// emplace_by_*iterator_type*_using_*type_constructor* method macro helpers [customly defined for type constructor]
#define DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_EMPLACE_BY(TYPE, ALLOCATOR_TYPE, RETURN_ITERATOR_TYPE, POSITION_ITERATOR_TYPE, TYPE_CONSTRUCTOR)\
    struct RETURN_ITERATOR_TYPE DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_EMPLACE_BY(TYPE, ALLOCATOR_TYPE, POSITION_ITERATOR_TYPE, TYPE_CONSTRUCTOR)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct POSITION_ITERATOR_TYPE const position,\
        ...)
#define DECLARE_DYNAMIC_ARRAY_TYPE_EMPLACE_BY(TYPE, RETURN_ITERATOR_TYPE, POSITION_ITERATOR_TYPE, TYPE_CONSTRUCTOR) DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_EMPLACE_BY(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE), RETURN_ITERATOR_TYPE, POSITION_ITERATOR_TYPE, TYPE_CONSTRUCTOR)

// erase_by_*iterator_type* method macro helpers
#define DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_ERASE_BY(TYPE, ALLOCATOR_TYPE, RETURN_ITERATOR_TYPE, POSITION_ITERATOR_TYPE)\
    struct RETURN_ITERATOR_TYPE DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_ERASE_BY(TYPE, ALLOCATOR_TYPE, POSITION_ITERATOR_TYPE)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct POSITION_ITERATOR_TYPE const position)
#define DECLARE_DYNAMIC_ARRAY_TYPE_ERASE_BY(TYPE, ITERATOR_TYPE) DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_ERASE_BY(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE), RETURN_ITERATOR_TYPE, POSITION_ITERATOR_TYPE)

// dynamic array methods declarations
#define DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_METHODS_WITH_MODIFIER(COMMON_MODIFIER, TYPE, ALLOCATOR_TYPE)\
struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE);\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this);\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_with_allocator_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct ALLOCATOR_TYPE const* const allocator);\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_copy_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const source);\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_copy_with_allocator_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const source,\
        struct ALLOCATOR_TYPE const* const allocator);\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_move_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const source);\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_move_with_allocator_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const source,\
        struct ALLOCATOR_TYPE const* const allocator);\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_by_value_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const count,\
        TYPE const* const value);\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_by_value_with_allocator_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const count,\
        TYPE const* const value,\
        struct ALLOCATOR_TYPE const* const allocator);\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_by_copying_from_buffer_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        TYPE const* const buffer,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const buffer_size);\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_by_copying_from_buffer_with_allocator_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        TYPE const* const buffer,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const buffer_size,\
        struct ALLOCATOR_TYPE const* const allocator);\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_by_moving_from_buffer_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        TYPE* const buffer,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const buffer_size);\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_by_moving_from_buffer_with_allocator_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        TYPE* const buffer,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const buffer_size,\
        struct ALLOCATOR_TYPE const* const allocator);\
COMMON_MODIFIER void* DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, destroy_at)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this);\
COMMON_MODIFIER void DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, swap)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const source);\
/* --- Assign functions --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, assign_copy_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const source);\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, assign_move_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const source);\
/* --- Memory managment functions --- */\
COMMON_MODIFIER void DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, reserve)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
    STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const new_capacity);\
COMMON_MODIFIER void DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, resize)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
    STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const new_size,\
    TYPE const* const value);\
COMMON_MODIFIER void DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, push_back_by_copying)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
    TYPE const* const value);\
COMMON_MODIFIER void DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, push_back_by_moving)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
    TYPE* const value);\
COMMON_MODIFIER void DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, shrink_to_fit)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this);\
COMMON_MODIFIER void DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, clear)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this);\
COMMON_MODIFIER void DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, pop_back)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this);\
/* --- Getters/Setters functions --- */\
COMMON_MODIFIER struct ALLOCATOR_TYPE const* DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, get_allocator)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, capacity)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, size)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this);\
COMMON_MODIFIER TYPE const* DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, data)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this);\
COMMON_MODIFIER TYPE const* DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, at)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this,\
    STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const position);\
COMMON_MODIFIER TYPE* DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, PRIVATE(unsafe_mut_at))(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
    STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const position);\
COMMON_MODIFIER TYPE* DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, mut_at)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
    STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const position);\
/* --- Mutable iterators' related functions --- */\
COMMON_MODIFIER DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_CONSTRUCT_BY_ITERATORS(TYPE, ALLOCATOR_TYPE, DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE));\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, begin)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this);\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, end)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this);\
DECLARE_RANDOM_ACCESS_ITERATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE));\
/* --- Const iterators' related functions --- */\
COMMON_MODIFIER DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_CONSTRUCT_BY_ITERATORS(TYPE, ALLOCATOR_TYPE,\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE));\
COMMON_MODIFIER DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_MOVE_BY(TYPE, ALLOCATOR_TYPE,\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE),\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE));\
COMMON_MODIFIER DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_COPY_BY(TYPE, ALLOCATOR_TYPE,\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE),\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE));\
COMMON_MODIFIER DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_COUNT_COPY_BY(TYPE, ALLOCATOR_TYPE,\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE),\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE));\
COMMON_MODIFIER DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_ERASE_BY(TYPE, ALLOCATOR_TYPE,\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE),\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE));\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, cbegin)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this);\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, cend)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this);\
DECLARE_RANDOM_ACCESS_ITERATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE));\
/* --- Mutable reverse iterators' related functions --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, rbegin)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this);\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, rend)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this);\
DECLARE_RANDOM_ACCESS_ITERATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE));\
/* --- Reverse const iterators' related functions --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, crbegin)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this);\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, crend)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this);\
DECLARE_RANDOM_ACCESS_ITERATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE))

#define DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_METHODS(TYPE, ALLOCATOR_TYPE) DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_METHODS_WITH_MODIFIER(, TYPE, ALLOCATOR_TYPE)
#define DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_STATIC_METHODS(TYPE, ALLOCATOR_TYPE) DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_METHODS_WITH_MODIFIER(static, TYPE, ALLOCATOR_TYPE)

#define DECLARE_DYNAMIC_ARRAY_TYPE_METHODS(TYPE) DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_METHODS(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE))
#define DECLARE_DYNAMIC_ARRAY_TYPE_STATIC_METHODS(TYPE) DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_STATIC_METHODS(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE))
