#include "array_storage.h"

#include <containers/dynamic/array_storage/array_storage.h>
#include <memory/allocator/allocator.h>

#define ALLOCATOR_WITH_COUNTER_TYPE(TYPE) CONCAT3(AllocatorWithCounter, __, TYPE)

typedef struct AllocatorCounters {\
    llong count_of_allocations_sub_deallocations;
    llong count_of_not_deallocated_bytes;
    llong count_of_reallocations;
} AllocatorCounters;

static AllocatorCounters static_allocator_counters;

static void flush_static_allocator_counters(void) {
    static_allocator_counters.count_of_allocations_sub_deallocations = 0;
    static_allocator_counters.count_of_not_deallocated_bytes = 0;
    static_allocator_counters.count_of_reallocations = 0;
}

#define DECLARE_ALLOCATOR_WITH_COUNTER_TYPE(TYPE)\
typedef struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE) {\
    llong* count_of_allocations_sub_deallocations;\
    llong* count_of_not_deallocated_bytes;\
    llong* count_of_reallocations;\
} ALLOCATOR_WITH_COUNTER_TYPE(TYPE)

#define DEFINE_ALLOCATOR_WITH_COUNTER_TYPE_STATIC_METHODS(TYPE)\
DECLARE_DEFAULT_LIFECYCLE_METHODS_WITH_MODIFIER(static, ALLOCATOR_WITH_COUNTER_TYPE(TYPE));\
/* --- Construction/Destruction functions implementation --- */\
static ALLOCATOR_WITH_COUNTER_TYPE(TYPE)*\
    TYPE_METHOD(ALLOCATOR_WITH_COUNTER_TYPE(TYPE), construct_at)(\
        struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    this->count_of_allocations_sub_deallocations = &static_allocator_counters.count_of_allocations_sub_deallocations;\
    this->count_of_reallocations = &static_allocator_counters.count_of_not_deallocated_bytes;\
    this->count_of_not_deallocated_bytes = &static_allocator_counters.count_of_reallocations;\
    return this;\
}\
static ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* TYPE_METHOD(ALLOCATOR_WITH_COUNTER_TYPE(TYPE), construct_copy_at)(\
    struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const this,\
    struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->count_of_allocations_sub_deallocations = source->count_of_allocations_sub_deallocations;\
    this->count_of_reallocations = source->count_of_reallocations;\
    this->count_of_not_deallocated_bytes = source->count_of_not_deallocated_bytes;\
    return this;\
}\
static ALLOCATOR_WITH_COUNTER_TYPE(TYPE)*\
    TYPE_METHOD(ALLOCATOR_WITH_COUNTER_TYPE(TYPE), construct_move_at)(\
        struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const this,\
        struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->count_of_allocations_sub_deallocations = source->count_of_allocations_sub_deallocations; source->count_of_allocations_sub_deallocations = NULL;\
    this->count_of_reallocations = source->count_of_reallocations; source->count_of_reallocations = NULL;\
    this->count_of_not_deallocated_bytes = source->count_of_not_deallocated_bytes; source->count_of_not_deallocated_bytes = NULL;\
    return this;\
}\
static ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* TYPE_METHOD(ALLOCATOR_WITH_COUNTER_TYPE(TYPE), assign_copy_at)(\
    struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const this,\
    struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->count_of_allocations_sub_deallocations = source->count_of_allocations_sub_deallocations;\
    this->count_of_reallocations = source->count_of_reallocations;\
    this->count_of_not_deallocated_bytes = source->count_of_not_deallocated_bytes;\
    return this;\
}\
static ALLOCATOR_WITH_COUNTER_TYPE(TYPE)*\
    TYPE_METHOD(ALLOCATOR_WITH_COUNTER_TYPE(TYPE), assign_move_at)(\
        struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const this,\
        struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->count_of_allocations_sub_deallocations = source->count_of_allocations_sub_deallocations; source->count_of_allocations_sub_deallocations = NULL;\
    this->count_of_reallocations = source->count_of_reallocations; source->count_of_reallocations = NULL;\
    this->count_of_not_deallocated_bytes = source->count_of_not_deallocated_bytes; source->count_of_not_deallocated_bytes = NULL;\
    return this;\
}\
static void* TYPE_METHOD(ALLOCATOR_WITH_COUNTER_TYPE(TYPE), destroy_at)(\
    struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const this) {\
    return this;\
}\
static void TYPE_METHOD(ALLOCATOR_WITH_COUNTER_TYPE(TYPE), swap)(\
    struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const this,\
    struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    TYPE_METHOD(voidptr, swap)((voidptr*)&this->count_of_allocations_sub_deallocations, (voidptr*)&source->count_of_allocations_sub_deallocations);\
    TYPE_METHOD(voidptr, swap)((voidptr*)&this->count_of_not_deallocated_bytes, (voidptr*)&source->count_of_not_deallocated_bytes);\
    TYPE_METHOD(voidptr, swap)((voidptr*)&this->count_of_reallocations, (voidptr*)&source->count_of_reallocations);\
}\
/* --- Memory managment functions implementation --- */\
static TYPE* TYPE_METHOD(ALLOCATOR_WITH_COUNTER_TYPE(TYPE), allocate)(\
    struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const this,\
    usize count_of_elements) {\
    ASSERT(this);\
    ASSERT(this->count_of_allocations_sub_deallocations);\
    ASSERT(this->count_of_not_deallocated_bytes);\
    ++*this->count_of_allocations_sub_deallocations;\
    *this->count_of_not_deallocated_bytes += sizeof(TYPE) * count_of_elements;\
    return NAMESPACE_MEMORY_NATIVE(malloc)(sizeof(TYPE) * count_of_elements);\
}\
static void TYPE_METHOD(ALLOCATOR_WITH_COUNTER_TYPE(TYPE), deallocate)(\
    struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const this,\
    TYPE* const elements_buffer,\
    usize count_of_elements) {\
    ASSERT(this);\
    ASSERT(elements_buffer);\
    ASSERT(this->count_of_allocations_sub_deallocations);\
    ASSERT(this->count_of_not_deallocated_bytes);\
    --*this->count_of_allocations_sub_deallocations;\
    *this->count_of_not_deallocated_bytes -= sizeof(TYPE) * count_of_elements;\
    NAMESPACE_MEMORY_NATIVE(free)(elements_buffer);\
}\
static TYPE* TYPE_METHOD(ALLOCATOR_WITH_COUNTER_TYPE(TYPE), reallocate)(\
    struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const this,\
    TYPE* const elements_buffer,\
    usize count_of_elements,\
    usize new_count_of_elements) {\
    ASSERT(this);\
    ASSERT(elements_buffer);\
    ASSERT(this->count_of_reallocations);\
    ASSERT(this->count_of_not_deallocated_bytes);\
    TYPE* buffer = NAMESPACE_MEMORY_NATIVE(realloc)(elements_buffer, new_count_of_elements * sizeof(TYPE));\
    if (buffer != NULL) {\
        ++*this->count_of_reallocations;\
        *this->count_of_not_deallocated_bytes -= (new_count_of_elements - count_of_elements);\
    }\
    return buffer;\
}

DECLARE_ALLOCATOR_WITH_COUNTER_TYPE(int);
DEFINE_ALLOCATOR_WITH_COUNTER_TYPE_STATIC_METHODS(int)

DECLARE_DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(int, ALLOCATOR_WITH_COUNTER_TYPE(int));
DECLARE_DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_STATIC_METHODS(int, ALLOCATOR_WITH_COUNTER_TYPE(int));
DEFINE_DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_STATIC_METHODS(int, ALLOCATOR_WITH_COUNTER_TYPE(int))

IMPLEMENT_TYPE_TESTS(dynamic_array_storage) {
#define CA_DYNAMIC_STORAGE_ARRAY_TYPE(TYPE) DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR_WITH_COUNTER_TYPE(TYPE))
#define CA_DYNAMIC_ARRAY_STORAGE_METHOD(TYPE, METHOD) DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHOD(TYPE, ALLOCATOR_WITH_COUNTER_TYPE(TYPE), METHOD)
    TEST_BLOCK("[DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(int, ALLOCATOR_WITH_COUNTER_TYPE(int))]: construction/destruction + capacity") {
        flush_static_allocator_counters();
        struct CA_DYNAMIC_STORAGE_ARRAY_TYPE(int) dynamic_storage_array_int;
        CA_DYNAMIC_ARRAY_STORAGE_METHOD(int, construct_at)(&dynamic_storage_array_int);
        
        struct ALLOCATOR_WITH_COUNTER_TYPE(int) const* const allocator = CA_DYNAMIC_ARRAY_STORAGE_METHOD(int, allocator)(&dynamic_storage_array_int);
        
        CHECK(*allocator->count_of_allocations_sub_deallocations == 1); // zero bytes must be allocated
        CHECK(!*allocator->count_of_not_deallocated_bytes);
        CHECK(!CA_DYNAMIC_ARRAY_STORAGE_METHOD(int, capacity)(&dynamic_storage_array_int));

        CA_DYNAMIC_ARRAY_STORAGE_METHOD(int, destroy_at)(&dynamic_storage_array_int);
        CHECK(!*allocator->count_of_allocations_sub_deallocations);
        CHECK(!*allocator->count_of_not_deallocated_bytes);
    }
    TEST_BLOCK("[DYNAMIC_ARRAY_TYPE(int)]: construct with capacity") {
        flush_static_allocator_counters();
        struct CA_DYNAMIC_STORAGE_ARRAY_TYPE(int) dynamic_storage_array_int;
        usize const capacity = 33;
        CA_DYNAMIC_ARRAY_STORAGE_METHOD(int, construct_with_capacity_at)(&dynamic_storage_array_int, capacity);
        struct ALLOCATOR_WITH_COUNTER_TYPE(int) const* const allocator = CA_DYNAMIC_ARRAY_STORAGE_METHOD(int, allocator)(&dynamic_storage_array_int);

        CHECK(*allocator->count_of_allocations_sub_deallocations == 1u);
        CHECK(*allocator->count_of_not_deallocated_bytes);
        CHECK(CA_DYNAMIC_ARRAY_STORAGE_METHOD(int, capacity)(&dynamic_storage_array_int) >= capacity);

        CA_DYNAMIC_ARRAY_STORAGE_METHOD(int, destroy_at)(&dynamic_storage_array_int);
        CHECK(!*allocator->count_of_allocations_sub_deallocations);
        CHECK(!*allocator->count_of_not_deallocated_bytes);
    }
    TEST_BLOCK("[DYNAMIC_ARRAY_TYPE(int)]: multiple constructions and destructions") {
        flush_static_allocator_counters();
        struct CA_DYNAMIC_STORAGE_ARRAY_TYPE(int) dynamic_storage_array_int;
        struct ALLOCATOR_WITH_COUNTER_TYPE(int) const* allocator;

        usize const sizes[] = {0u, 520, 324, 1, 2356, 0u, 23125};
        for (usize i = 0u; i < sizeof(sizes)/ sizeof(*sizes); ++i) {
            usize const new_size = sizes[i];

            CA_DYNAMIC_ARRAY_STORAGE_METHOD(int, construct_with_capacity_at)(&dynamic_storage_array_int, new_size);
            allocator = CA_DYNAMIC_ARRAY_STORAGE_METHOD(int, allocator)(&dynamic_storage_array_int);
            CHECK(*allocator->count_of_allocations_sub_deallocations == 1); // zero bytes must be allocated if capacity set to zero
            CHECK(new_size ? *allocator->count_of_not_deallocated_bytes > 0u : !*allocator->count_of_not_deallocated_bytes);
            
            CHECK((llong)CA_DYNAMIC_ARRAY_STORAGE_METHOD(int, capacity)(&dynamic_storage_array_int) == *allocator->count_of_not_deallocated_bytes / (llong)sizeof(int));
            CHECK(CA_DYNAMIC_ARRAY_STORAGE_METHOD(int, capacity)(&dynamic_storage_array_int) >= new_size);

            CA_DYNAMIC_ARRAY_STORAGE_METHOD(int, destroy_at)(&dynamic_storage_array_int);
            CHECK(!*allocator->count_of_allocations_sub_deallocations);
            CHECK(!*allocator->count_of_not_deallocated_bytes);
        }
    }
#undef CA_DYNAMIC_STORAGE_ARRAY_TYPE
#undef CA_DYNAMIC_ARRAY_STORAGE_METHOD
}
