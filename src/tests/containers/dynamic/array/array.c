#include "array.h"

#include <containers/dynamic/array/array.h>
#include <memory/allocator/allocator.h>

#define ALLOCATOR_WITH_COUNTER_TYPE(TYPE) CONCAT3(AllocatorWithCounter, __, TYPE)

static llong static_count_of_allocations_sub_deallocations;
static llong static_count_of_not_deallocated_bytes;
static llong static_count_of_reallocations;

typedef struct AllocatorCounters {\
    llong count_of_allocations_sub_deallocations;
    llong count_of_not_deallocated_bytes;
    llong count_of_reallocations;
} AllocatorCounters;

#define DECLARE_ALLOCATOR_WITH_COUNTER_TYPE(TYPE)\
typedef struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE) {\
    llong* count_of_allocations_sub_deallocations;\
    llong* count_of_not_deallocated_bytes;\
    llong* count_of_reallocations;\
} ALLOCATOR_WITH_COUNTER_TYPE(TYPE)

#define DEFINE_ALLOCATOR_WITH_COUNTER_TYPE_STATIC_METHODS(TYPE)\
/* --- Construction/Destruction functions implementation --- */\
static ALLOCATOR_WITH_COUNTER_TYPE(TYPE)*\
    TYPE_METHOD(ALLOCATOR_WITH_COUNTER_TYPE(TYPE), construct_at)(\
        struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const this) {\
    this->count_of_allocations_sub_deallocations = &static_count_of_allocations_sub_deallocations;\
    this->count_of_reallocations = &static_count_of_not_deallocated_bytes;\
    this->count_of_not_deallocated_bytes = &static_count_of_reallocations;\
    return this;\
}\
static ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* TYPE_METHOD(ALLOCATOR_WITH_COUNTER_TYPE(TYPE), construct_copy_at)(\
    struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const this,\
    struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE) const* const source) {\
    this->count_of_allocations_sub_deallocations = source->count_of_allocations_sub_deallocations;\
    this->count_of_reallocations = source->count_of_reallocations;\
    this->count_of_not_deallocated_bytes = source->count_of_not_deallocated_bytes;\
    return this;\
}\
static ALLOCATOR_WITH_COUNTER_TYPE(TYPE)*\
    TYPE_METHOD(ALLOCATOR_WITH_COUNTER_TYPE(TYPE), construct_move_at)(\
        struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const this,\
        struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const source) {\
    this->count_of_allocations_sub_deallocations = source->count_of_allocations_sub_deallocations; source->count_of_allocations_sub_deallocations = NULL;\
    this->count_of_reallocations = source->count_of_reallocations; source->count_of_reallocations = NULL;\
    this->count_of_not_deallocated_bytes = source->count_of_not_deallocated_bytes; source->count_of_not_deallocated_bytes = NULL;\
    return this;\
}\
static ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* TYPE_METHOD(ALLOCATOR_WITH_COUNTER_TYPE(TYPE), assign_copy_at)(\
    struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const this,\
    struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE) const* const source) {\
    this->count_of_allocations_sub_deallocations = source->count_of_allocations_sub_deallocations;\
    this->count_of_reallocations = source->count_of_reallocations;\
    this->count_of_not_deallocated_bytes = source->count_of_not_deallocated_bytes;\
    return this;\
}\
static ALLOCATOR_WITH_COUNTER_TYPE(TYPE)*\
    TYPE_METHOD(ALLOCATOR_WITH_COUNTER_TYPE(TYPE), assign_move_at)(\
        struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const this,\
        struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const source) {\
    this->count_of_allocations_sub_deallocations = source->count_of_allocations_sub_deallocations; source->count_of_allocations_sub_deallocations = NULL;\
    this->count_of_reallocations = source->count_of_reallocations; source->count_of_reallocations = NULL;\
    this->count_of_not_deallocated_bytes = source->count_of_not_deallocated_bytes; source->count_of_not_deallocated_bytes = NULL;\
    return this;\
}\
static void* TYPE_METHOD(ALLOCATOR_WITH_COUNTER_TYPE(TYPE), destroy_at)(\
    struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const this) {\
    return this;\
}\
/* --- Memory managment functions implementation --- */\
static TYPE* TYPE_METHOD(ALLOCATOR_WITH_COUNTER_TYPE(TYPE), allocate)(\
    struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const this,\
    usize count_of_elements) {\
    ++*this->count_of_allocations_sub_deallocations;\
    *this->count_of_not_deallocated_bytes += sizeof(TYPE) * count_of_elements;\
    return NAMESPACE_MEMORY_NATIVE(malloc)(sizeof(TYPE) * count_of_elements);\
}\
static void TYPE_METHOD(ALLOCATOR_WITH_COUNTER_TYPE(TYPE), deallocate)(\
    struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const this,\
    TYPE* const elements_buffer,\
    usize count_of_elements) {\
    if (elements_buffer == NULL) {\
        return;\
    }\
    --*this->count_of_allocations_sub_deallocations;\
    *this->count_of_not_deallocated_bytes -= sizeof(TYPE) * count_of_elements;\
    NAMESPACE_MEMORY_NATIVE(free)(elements_buffer);\
}\
static TYPE* TYPE_METHOD(ALLOCATOR_WITH_COUNTER_TYPE(TYPE), reallocate)(\
    struct ALLOCATOR_WITH_COUNTER_TYPE(TYPE)* const this,\
    TYPE* const elements_buffer,\
    usize count_of_elements,\
    usize new_count_of_elements) {\
    TYPE* buffer = NAMESPACE_MEMORY_NATIVE(realloc)(elements_buffer, new_count_of_elements * sizeof(TYPE));\
    if (buffer != NULL) {\
        ++*this->count_of_reallocations;\
        *this->count_of_not_deallocated_bytes -= (new_count_of_elements - count_of_elements);\
    }\
    return buffer;\
}

DECLARE_ALLOCATOR_WITH_COUNTER_TYPE(int);
DEFINE_ALLOCATOR_WITH_COUNTER_TYPE_STATIC_METHODS(int)

DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(int, ALLOCATOR_WITH_COUNTER_TYPE(int));
IMPLEMENT_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_STATIC_METHODS(int, ALLOCATOR_WITH_COUNTER_TYPE(int))

IMPLEMENT_TYPE_TESTS(dynamic_array) {
#define CA_DYNAMIC_ARRAY_TYPE(TYPE) DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_WITH_COUNTER_TYPE(TYPE))
#define CA_DYNAMIC_ARRAY_METHOD(TYPE, METHOD) DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_WITH_COUNTER_TYPE(TYPE), METHOD)
    TEST_BLOCK("[DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(int, ALLOCATOR_WITH_COUNTER_TYPE(int))]: construction/destruction + size/capacity") {
        struct CA_DYNAMIC_ARRAY_TYPE(int) dynamic_array_int;
        CA_DYNAMIC_ARRAY_METHOD(int, construct_at)(&dynamic_array_int);
        
        struct ALLOCATOR_WITH_COUNTER_TYPE(int) const* const allocator = CA_DYNAMIC_ARRAY_METHOD(int, get_allocator)(&dynamic_array_int);
        
        CHECK(!*allocator->count_of_allocations_sub_deallocations);
        CHECK(!CA_DYNAMIC_ARRAY_METHOD(int, size)(&dynamic_array_int));
        CHECK(!CA_DYNAMIC_ARRAY_METHOD(int, capacity)(&dynamic_array_int));

        CA_DYNAMIC_ARRAY_METHOD(int, destroy_at)(&dynamic_array_int);
        CHECK(!*allocator->count_of_allocations_sub_deallocations);
    }
    TEST_BLOCK("[DYNAMIC_ARRAY_TYPE(int)]: reserve") {
        struct CA_DYNAMIC_ARRAY_TYPE(int) dynamic_array_int;
        CA_DYNAMIC_ARRAY_METHOD(int, construct_at)(&dynamic_array_int);
        struct ALLOCATOR_WITH_COUNTER_TYPE(int) const* const allocator = CA_DYNAMIC_ARRAY_METHOD(int, get_allocator)(&dynamic_array_int);
        CHECK(!*allocator->count_of_allocations_sub_deallocations);
        CHECK(!*allocator->count_of_not_deallocated_bytes);

        usize const reserve_capacity = 33;
        CA_DYNAMIC_ARRAY_METHOD(int, reserve)(&dynamic_array_int, reserve_capacity);
        CHECK(*allocator->count_of_allocations_sub_deallocations == 1u);
        CHECK(*allocator->count_of_not_deallocated_bytes);
        CHECK(CA_DYNAMIC_ARRAY_METHOD(int, capacity)(&dynamic_array_int) >= reserve_capacity);

        CA_DYNAMIC_ARRAY_METHOD(int, destroy_at)(&dynamic_array_int);
        CHECK(!*allocator->count_of_allocations_sub_deallocations);
        CHECK(!*allocator->count_of_not_deallocated_bytes);
    }
    TEST_BLOCK("[DYNAMIC_ARRAY_TYPE(int)]: resize") {
        struct CA_DYNAMIC_ARRAY_TYPE(int) dynamic_array_int;
        CA_DYNAMIC_ARRAY_METHOD(int, construct_at)(&dynamic_array_int);
        struct ALLOCATOR_WITH_COUNTER_TYPE(int) const* const allocator = CA_DYNAMIC_ARRAY_METHOD(int, get_allocator)(&dynamic_array_int);
        CHECK(!*allocator->count_of_allocations_sub_deallocations);
        CHECK(!*allocator->count_of_not_deallocated_bytes);

        usize const new_size = 63;
        CA_DYNAMIC_ARRAY_METHOD(int, resize)(&dynamic_array_int, new_size, &(int const){2325});
        CHECK(*allocator->count_of_allocations_sub_deallocations == 1u);
        CHECK(*allocator->count_of_not_deallocated_bytes);
        CHECK(CA_DYNAMIC_ARRAY_METHOD(int, capacity)(&dynamic_array_int) >= new_size);
        CHECK(CA_DYNAMIC_ARRAY_METHOD(int, size)(&dynamic_array_int) == new_size);

        CA_DYNAMIC_ARRAY_METHOD(int, destroy_at)(&dynamic_array_int);
        CHECK(!*allocator->count_of_allocations_sub_deallocations);
        CHECK(!*allocator->count_of_not_deallocated_bytes);
    }
    TEST_BLOCK("[DYNAMIC_ARRAY_TYPE(int)]: push_back_by_copying + at") {
        struct AllocatorCounters allocator_counters_storage = {
            .count_of_allocations_sub_deallocations = 0u,
            .count_of_not_deallocated_bytes = 0u,
            .count_of_reallocations = 0u
        };

        struct ALLOCATOR_WITH_COUNTER_TYPE(int) local_allocator = {
            .count_of_allocations_sub_deallocations = &allocator_counters_storage.count_of_allocations_sub_deallocations,
            .count_of_not_deallocated_bytes = &allocator_counters_storage.count_of_not_deallocated_bytes,
            .count_of_reallocations = &allocator_counters_storage.count_of_reallocations
        };

        struct CA_DYNAMIC_ARRAY_TYPE(int) dynamic_array_int;
        CA_DYNAMIC_ARRAY_METHOD(int, construct_with_allocator_at)(&dynamic_array_int, &local_allocator);

        CHECK(!allocator_counters_storage.count_of_allocations_sub_deallocations);
        CHECK(!allocator_counters_storage.count_of_not_deallocated_bytes);

        usize const new_size = 633;
        for (usize index = 0u; index < new_size; ++index) {
            int const value = (int)index;
            CA_DYNAMIC_ARRAY_METHOD(int, push_back_by_copying)(&dynamic_array_int, &value);
        }
        CHECK(allocator_counters_storage.count_of_allocations_sub_deallocations > 0u);
        CHECK(allocator_counters_storage.count_of_not_deallocated_bytes);
        CHECK((llong)CA_DYNAMIC_ARRAY_METHOD(int, capacity)(&dynamic_array_int) == allocator_counters_storage.count_of_not_deallocated_bytes / (llong)sizeof(int));
        CHECK(CA_DYNAMIC_ARRAY_METHOD(int, capacity)(&dynamic_array_int) >= new_size);
        CHECK(CA_DYNAMIC_ARRAY_METHOD(int, size)(&dynamic_array_int) == new_size);

        for (usize index = 0u; index < new_size; ++index) {
            int const value = (int)index;
            CHECK(*CA_DYNAMIC_ARRAY_METHOD(int, at)(&dynamic_array_int, index) == value);
        }

        CA_DYNAMIC_ARRAY_METHOD(int, destroy_at)(&dynamic_array_int);
        CHECK(!allocator_counters_storage.count_of_allocations_sub_deallocations);
        CHECK(!allocator_counters_storage.count_of_not_deallocated_bytes);
    }
    TEST_BLOCK("[DYNAMIC_ARRAY_TYPE(int)]: reserve + resize") {
        struct CA_DYNAMIC_ARRAY_TYPE(int) dynamic_array_int;
        CA_DYNAMIC_ARRAY_METHOD(int, construct_at)(&dynamic_array_int);

        struct ALLOCATOR_WITH_COUNTER_TYPE(int) const* const allocator = CA_DYNAMIC_ARRAY_METHOD(int, get_allocator)(&dynamic_array_int);
        CHECK(!*allocator->count_of_allocations_sub_deallocations);
        CHECK(!*allocator->count_of_not_deallocated_bytes);

        usize const new_size = 223;
        CA_DYNAMIC_ARRAY_METHOD(int, reserve)(&dynamic_array_int, new_size);
        CHECK(*allocator->count_of_allocations_sub_deallocations == 1);
        CHECK(*allocator->count_of_not_deallocated_bytes > 0u);
        CHECK((llong)CA_DYNAMIC_ARRAY_METHOD(int, capacity)(&dynamic_array_int) == *allocator->count_of_not_deallocated_bytes / (llong)sizeof(int));

        CHECK(CA_DYNAMIC_ARRAY_METHOD(int, capacity)(&dynamic_array_int) >= new_size);
        CHECK(!CA_DYNAMIC_ARRAY_METHOD(int, size)(&dynamic_array_int));

        struct AllocatorCounters allocator_counters_cache = {
            .count_of_allocations_sub_deallocations = *allocator->count_of_allocations_sub_deallocations,
            .count_of_not_deallocated_bytes = *allocator->count_of_not_deallocated_bytes
        };

        CA_DYNAMIC_ARRAY_METHOD(int, resize)(&dynamic_array_int, new_size, &(int){834});
        CHECK(*allocator->count_of_allocations_sub_deallocations == 1);
        CHECK(*allocator->count_of_not_deallocated_bytes == allocator_counters_cache.count_of_not_deallocated_bytes);
        CHECK((llong)CA_DYNAMIC_ARRAY_METHOD(int, capacity)(&dynamic_array_int) == *allocator->count_of_not_deallocated_bytes / (llong)sizeof(int));
        CHECK(CA_DYNAMIC_ARRAY_METHOD(int, size)(&dynamic_array_int) == new_size);

        CA_DYNAMIC_ARRAY_METHOD(int, destroy_at)(&dynamic_array_int);
        CHECK(!*allocator->count_of_allocations_sub_deallocations);
        CHECK(!*allocator->count_of_not_deallocated_bytes);
    }
#undef CA_DYNAMIC_ARRAY_TYPE
#undef CA_DYNAMIC_ARRAY_METHOD
}
