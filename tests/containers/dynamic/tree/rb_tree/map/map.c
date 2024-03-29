#include "map.h"

#include <memory/allocator/proxy_allocator/debug.h>
#include <memory/allocator/allocator.h>

#include <containers/dynamic/tree/rb_tree/map/map.h>
DEFINE_DEFAULT_COMPARATOR_TYPE(greater, int);
#include <containers/pair/pair.h>
DEFINE_PAIR_TYPE(int, int);
DECLARE_RED_BLACK_TREE_MAP_NODE_TYPE(int, int);

// define allocator
DEFINE_DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_MAP_NODE_TYPE(int, int));
DEFINE_DEBUG_PROXY_ALLOCATOR_TYPE(RED_BLACK_TREE_MAP_NODE_TYPE(int, int));

DECLARE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(
    int, int,
    COMPARATOR_TYPE(greater, int),
    DEBUG_PROXY_ALLOCATOR_TYPE(RED_BLACK_TREE_MAP_NODE_TYPE(int, int))
);

// define default->declare+define debug (proxy) methods
DEFINE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(static, RED_BLACK_TREE_MAP_NODE_TYPE(int, int))
DECLARE_DEBUG_PROXY_ALLOCATOR_METHODS(static, RED_BLACK_TREE_MAP_NODE_TYPE(int, int));
DEFINE_DEBUG_PROXY_ALLOCATOR_METHODS_WITH_MODIFIER(static, RED_BLACK_TREE_MAP_NODE_TYPE(int, int))

// define greater comparator methods
DEFINE_GREATER_COMPARATOR_METHODS_WITH_MODIFIER(static, int)

// red-black tree map's methods declaration
DECLARE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(
    static,
    int, int,
    COMPARATOR_TYPE(greater, int),
    DEBUG_PROXY_ALLOCATOR_TYPE(RED_BLACK_TREE_MAP_NODE_TYPE(int, int))
);

// pair methods declaration + definition
DECLARE_PAIR_METHODS_WITH_MODIFIER(static, int, int);
DEFINE_PAIR_METHODS_WITH_MODIFIER(static, int, int)

// red-black tree map's methods definition
DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(
    static,
    int, int,
    COMPARATOR_TYPE(greater, int),
    DEBUG_PROXY_ALLOCATOR_TYPE(RED_BLACK_TREE_MAP_NODE_TYPE(int, int))
)

// define helper macros
#define RBTREE_MAP_ALLOCATOR(KEY, VALUE) DEBUG_PROXY_ALLOCATOR_TYPE(RED_BLACK_TREE_MAP_NODE_TYPE(int, int))
#define RBTREE_MAP(KEY, VALUE) RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(\
    KEY, VALUE,\
    COMPARATOR_TYPE(greater, KEY),\
    RBTREE_MAP_ALLOCATOR(KEY, VALUE)\
)
#define RBTREE_MAP_CONST_ITERATOR(KEY, VALUE) RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(\
    KEY, VALUE,\
    COMPARATOR_TYPE(greater, KEY),\
    RBTREE_MAP_ALLOCATOR(KEY, VALUE)\
)
#define RBTREE_MAP_ITERATOR(KEY, VALUE) RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(\
    KEY, VALUE,\
    COMPARATOR_TYPE(greater, KEY),\
    RBTREE_MAP_ALLOCATOR(KEY, VALUE)\
)

// define functions helpers
static void onAllocation(
    DebugAllocatorContext* const context,
    DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_MAP_NODE_TYPE(int, int))* const allocator,
    usize count_of_elements) {
    ASSERT(allocator);
    ++context->count_of_allocations;
    context->count_of_allocated_bytes += count_of_elements * sizeof(RED_BLACK_TREE_MAP_NODE_TYPE(int, int));
}

static void onDeallocation(
    DebugAllocatorContext* const context,
    DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_MAP_NODE_TYPE(int, int))* const allocator,
    STRUCT_SUBTYPE(RBTREE_MAP(int, int), node_type)* const buffer,
    usize count_of_elements) {
    ASSERT(allocator);
    ASSERT(buffer);
    ++context->count_of_deallocations;
    context->count_of_deallocated_bytes += count_of_elements * sizeof(STRUCT_SUBTYPE(RBTREE_MAP(int, int), node_type));
}

static int generate_hash(int const previous_value, usize const hash_value) {
    usize const hash_value_1 = 173543437;
    usize const hash_value_2 = 15;
    usize const hash_value_3 = 8;
    usize const hash_value_4 = 10602500000;

    return (int)(
        (
            (
                ~(hash_value_1 ^ hash_value)
                << (hash_value_2 ^ hash_value)
            )
            >> (hash_value_3 ^ hash_value)
        )
        ^ (hash_value_4 ^ hash_value)
    ) ^ previous_value;
}

#include <containers/pair/pair.h>
#include <construct/data_model_helpers.h>
DEFINE_PAIR_TYPE(int, usize);
DEFINE_PAIR_METHODS_WITH_MODIFIER(static, int, usize)

#include <memory/allocator/allocator.h>
DEFINE_DEFAULT_ALLOCATOR_TYPE(PAIR_TYPE(int, usize));
DEFINE_DEFAULT_ALLOCATOR_STATIC_METHODS(PAIR_TYPE(int, usize))
#include <containers/dynamic/array/array.h>
DECLARE_DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize));
DECLARE_DYNAMIC_ARRAY_TYPE_STATIC_METHODS(PAIR_TYPE(int, usize));
IMPLEMENT_DYNAMIC_ARRAY_TYPE_STATIC_METHODS(PAIR_TYPE(int, usize))


#define REDUCE_OVER_ARRAY(TYPE)\
    CONCAT3(reduce_over_array, __, TYPE)

#define DEFINE_REDUCE_OVER_ARRAY_WITH_MODIFIER(MODIFIER, TYPE)\
MODIFIER TYPE REDUCE_OVER_ARRAY(TYPE)(void(*callback)(TYPE* const result, TYPE const* const value),\
    TYPE const* const array, usize const size) {\
    ASSERT(array);\
    ASSERT(callback);\
    TYPE result;\
    TYPE_METHOD(TYPE, construct_at)(&result);\
    for (usize index = 0u; index < size; ++index) {\
        callback(&result, &array[index]);\
    }\
    return result;\
}
DEFINE_REDUCE_OVER_ARRAY_WITH_MODIFIER(static, PAIR_TYPE(int, usize))

static void sum_callback(struct PAIR_TYPE(int, usize)* const accumulator, struct PAIR_TYPE(int, usize) const* const value) {
    ASSERT(accumulator);
    ASSERT(value);
    accumulator->second += value->second;
}

#define DEFINE_FIND_ELEMENT_BY_PAIR_FIRST_VALUE_TYPE_WITH_MODIFIER(MODIFIER, TYPE1, TYPE2)\
MODIFIER struct PAIR_TYPE(TYPE1, TYPE2)* TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(TYPE1, TYPE2)), findElementByFirstPairValue)(\
    struct DYNAMIC_ARRAY_TYPE(PAIR_TYPE(TYPE1, TYPE2))* const this,\
    TYPE1 const* const value) {\
    for (usize index = 0u; index < TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(TYPE1, TYPE2)), size)(this); ++index) {\
        if (TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(TYPE1, TYPE2)), at)(this, index)->first == *value) {\
            return TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(TYPE1, TYPE2)), mut_at)(this, index);\
        }\
    }\
    return NULL;\
}

DEFINE_FIND_ELEMENT_BY_PAIR_FIRST_VALUE_TYPE_WITH_MODIFIER(static, int, usize)

IMPLEMENT_TYPE_TESTS(rb_tree_map) {
    UNUSED(TYPE_NAME);
    TEST_BLOCK("`size` method on empty red-black tree map") {
        struct RBTREE_MAP(int, int) rbtree_map;
        TYPE_METHOD(RBTREE_MAP(int, int), construct_at)(&rbtree_map);
        CHECK(!TYPE_METHOD(RBTREE_MAP(int, int), size)(&rbtree_map));
        TYPE_METHOD(RBTREE_MAP(int, int), destroy_at)(&rbtree_map);
    }
    TEST_BLOCK("`find` on empty red-black tree set") {
        struct RBTREE_MAP_ALLOCATOR(int, int) allocator;
        TYPE_METHOD(RBTREE_MAP_ALLOCATOR(int, int), construct_at)(&allocator);
        // set callbacks for allocator
        DebugAllocatorContext context = {0};
        allocator.context = &context;
        allocator.on_allocation = &onAllocation;
        allocator.on_deallocation = &onDeallocation;
        {
            struct RBTREE_MAP(int, int) rbtree_map;
            TYPE_METHOD(RBTREE_MAP(int, int), construct_with_allocator_at)(&rbtree_map, &allocator);
            {
                int const key = 348992;
                STRUCT_SUBTYPE(RBTREE_MAP(int, int), const_iterator_type) const iterator = TYPE_METHOD(RBTREE_MAP(int, int), find)(&rbtree_map, &key);
                STRUCT_SUBTYPE(RBTREE_MAP(int, int), const_iterator_type) const end_iterator = TYPE_METHOD(RBTREE_MAP(int, int), cend)(&rbtree_map);
                CHECK(TYPE_METHOD(RBTREE_MAP_CONST_ITERATOR(int, int), compare)(&iterator, &end_iterator));
            }
            CHECK(!TYPE_METHOD(RBTREE_MAP(int, int), size)(&rbtree_map));
            CHECK(!context.count_of_allocated_bytes);
            CHECK(!context.count_of_allocations);

            TYPE_METHOD(RBTREE_MAP(int, int), destroy_at)(&rbtree_map);
            CHECK(!context.count_of_allocated_bytes);
            CHECK(!context.count_of_deallocations);
        }
        TYPE_METHOD(RBTREE_MAP_ALLOCATOR(int, int), destroy_at)(&allocator);
    }
    TEST_BLOCK("`emplace` 1 element + `find` it & try to `find` another value on red-black tree set") {
        struct RBTREE_MAP_ALLOCATOR(int, int) allocator;
        TYPE_METHOD(RBTREE_MAP_ALLOCATOR(int, int), construct_at)(&allocator);
        // set callbacks for allocator
        DebugAllocatorContext context = {0};
        allocator.context = &context;
        allocator.on_allocation = &onAllocation;
        allocator.on_deallocation = &onDeallocation;
        {
            struct RBTREE_MAP(int, int) rbtree_map;
            TYPE_METHOD(RBTREE_MAP(int, int), construct_with_allocator_at)(&rbtree_map, &allocator);

            // insert copy of one value
            {
                STRUCT_SUBTYPE(RBTREE_MAP(int, int), value_type) const value = {
                    .first = 98544,
                    .second = 23555
                };
                TYPE_METHOD(RBTREE_MAP(int, int), insert_copy)(&rbtree_map, &value);
            }
            CHECK(context.count_of_allocated_bytes == sizeof(STRUCT_SUBTYPE(RBTREE_MAP(int, int), node_type)));
            CHECK(context.count_of_allocations == 1u);

            // try find same value
            {
                int const key = 98544;
                STRUCT_SUBTYPE(RBTREE_MAP(int, int), const_iterator_type) const iterator = TYPE_METHOD(RBTREE_MAP(int, int), find)(&rbtree_map, &key);
                STRUCT_SUBTYPE(RBTREE_MAP(int, int), const_iterator_type) const end_iterator = TYPE_METHOD(RBTREE_MAP(int, int), cend)(&rbtree_map);
                CHECK(!TYPE_METHOD(RBTREE_MAP_CONST_ITERATOR(int, int), compare)(&iterator, &end_iterator));
                CHECK(*TYPE_METHOD(RBTREE_MAP_CONST_ITERATOR(int, int), key)(&iterator) == key);
                CHECK(*TYPE_METHOD(RBTREE_MAP_CONST_ITERATOR(int, int), const_value)(&iterator) == 23555);
            }
            // try same call function with another value provided
            {
                int const key = 75383;
                STRUCT_SUBTYPE(RBTREE_MAP(int, int), const_iterator_type) const iterator = TYPE_METHOD(RBTREE_MAP(int, int), find)(&rbtree_map, &key);
                STRUCT_SUBTYPE(RBTREE_MAP(int, int), const_iterator_type) const end_iterator = TYPE_METHOD(RBTREE_MAP(int, int), cend)(&rbtree_map);
                CHECK(TYPE_METHOD(RBTREE_MAP_CONST_ITERATOR(int, int), compare)(&iterator, &end_iterator));
            }
            TYPE_METHOD(RBTREE_MAP(int, int), destroy_at)(&rbtree_map);
            CHECK(context.count_of_deallocated_bytes == sizeof(STRUCT_SUBTYPE(RBTREE_MAP(int, int), node_type)));
            CHECK(context.count_of_deallocations == 1u);
        }
        TYPE_METHOD(RBTREE_MAP_ALLOCATOR(int, int), destroy_at)(&allocator);
    }
    TEST_BLOCK("`emplace` many elements + `find` all of them on red-black tree set") {
        struct RBTREE_MAP_ALLOCATOR(int, int) allocator;
        TYPE_METHOD(RBTREE_MAP_ALLOCATOR(int, int), construct_at)(&allocator);
        // set callbacks for allocator
        DebugAllocatorContext context = {0};
        allocator.context = &context;
        allocator.on_allocation = &onAllocation;
        allocator.on_deallocation = &onDeallocation;
        {
            struct RBTREE_MAP(int, int) rbtree_map;
            TYPE_METHOD(RBTREE_MAP(int, int), construct_with_allocator_at)(&rbtree_map, &allocator);
            usize const count_of_insertions = 2000;
            usize count_of_repeated_values = 0u;

            STRUCT_SUBTYPE(RBTREE_MAP(int, int), key_type) const seed = -34345328;
            {
                STRUCT_SUBTYPE(RBTREE_MAP(int, int), const_iterator_type) const end_iterator = TYPE_METHOD(RBTREE_MAP(int, int), cend)(&rbtree_map);
                STRUCT_SUBTYPE(RBTREE_MAP(int, int), key_type) prev_key = seed;
                for (usize i = 0u; i < count_of_insertions; ++i) {
                    STRUCT_SUBTYPE(RBTREE_MAP(int, int), key_type) const key = generate_hash(prev_key, i);
                    prev_key = key;
                    STRUCT_SUBTYPE(RBTREE_MAP(int, int), const_iterator_type) const iterator = TYPE_METHOD(RBTREE_MAP(int, int), find)(&rbtree_map, &key);
                    if (!TYPE_METHOD(RBTREE_MAP_CONST_ITERATOR(int, int), compare)(&iterator, &end_iterator)) {
                        ++count_of_repeated_values;
                    }
                    STRUCT_SUBTYPE(RBTREE_MAP(int, int), value_type) const value = {
                        .first = key,
                        .second = generate_hash(key, 39989u)
                    };
                    TYPE_METHOD(RBTREE_MAP(int, int), insert_copy)(&rbtree_map, &value);
                }
            }
            CHECK(TYPE_METHOD(RBTREE_MAP(int, int), size)(&rbtree_map) == (count_of_insertions - count_of_repeated_values));
            CHECK(context.count_of_allocations == (count_of_insertions - count_of_repeated_values));
            CHECK(context.count_of_allocated_bytes == context.count_of_allocations * sizeof(STRUCT_SUBTYPE(RBTREE_MAP(int, int), node_type)));
            {
                STRUCT_SUBTYPE(RBTREE_MAP(int, int), key_type) prev_key = seed;
                STRUCT_SUBTYPE(RBTREE_MAP(int, int), const_iterator_type) const end_iterator = TYPE_METHOD(RBTREE_MAP(int, int), cend)(&rbtree_map);
                for (usize i = 0u; i < count_of_insertions; ++i) {
                    STRUCT_SUBTYPE(RBTREE_MAP(int, int), key_type) const key = generate_hash(prev_key, i);
                    prev_key = key;
                    STRUCT_SUBTYPE(RBTREE_MAP(int, int), const_iterator_type) const iterator = TYPE_METHOD(RBTREE_MAP(int, int), find)(&rbtree_map, &key);
                    CHECK(!TYPE_METHOD(RBTREE_MAP_CONST_ITERATOR(int, int), compare)(&iterator, &end_iterator));
                    CHECK(*TYPE_METHOD(RBTREE_MAP_CONST_ITERATOR(int, int), key)(&iterator) == key);
                    CHECK(*TYPE_METHOD(RBTREE_MAP_CONST_ITERATOR(int, int), const_value)(&iterator) == generate_hash(key, 39989u));
                }
            }
            TYPE_METHOD(RBTREE_MAP(int, int), destroy_at)(&rbtree_map);
            CHECK(context.count_of_deallocations == (count_of_insertions - count_of_repeated_values));
            CHECK(context.count_of_deallocated_bytes == context.count_of_deallocations * sizeof(STRUCT_SUBTYPE(RBTREE_MAP(int, int), node_type)));
        }
        TYPE_METHOD(RBTREE_MAP_ALLOCATOR(int, int), destroy_at)(&allocator);
    }
    TEST_BLOCK("`emplace` many elements + `erase` all of them in different order on red-black tree set") {
        usize const max_count_of_insertions = 500u;
        struct DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)) index_to_insert_value_encounter;
        /* construct index_to_insert_value_encounter array with zeroes */{
            TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), construct_at)(&index_to_insert_value_encounter);
            TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), reserve)(&index_to_insert_value_encounter, max_count_of_insertions);
        }
        for (usize count_of_insertions = 1u; count_of_insertions <= max_count_of_insertions; ++count_of_insertions) {
            struct RBTREE_MAP_ALLOCATOR(int, int) allocator;
            TYPE_METHOD(RBTREE_MAP_ALLOCATOR(int, int), construct_at)(&allocator);
            // set callbacks for allocator
            DebugAllocatorContext context = {0};
            allocator.context = &context;
            allocator.on_allocation = &onAllocation;
            allocator.on_deallocation = &onDeallocation;
            {
                struct RBTREE_MAP(int, int) rbtree_map;
                TYPE_METHOD(RBTREE_MAP(int, int), construct_with_allocator_at)(&rbtree_map, &allocator);
                usize count_of_repeated_values = 0u;

                STRUCT_SUBTYPE(RBTREE_MAP(int, int), key_type) const seed = 19834748;
                {
                    STRUCT_SUBTYPE(RBTREE_MAP(int, int), key_type) prev_key = seed;
                    STRUCT_SUBTYPE(RBTREE_MAP(int, int), const_iterator_type) const end_iterator = TYPE_METHOD(RBTREE_MAP(int, int), cend)(&rbtree_map);
                    for (usize i = 0u; i < count_of_insertions; ++i) {
                        STRUCT_SUBTYPE(RBTREE_MAP(int, int), key_type) const key = prev_key = generate_hash(prev_key, i);
                        STRUCT_SUBTYPE(RBTREE_MAP(int, int), const_iterator_type) const iterator = TYPE_METHOD(RBTREE_MAP(int, int), find)(&rbtree_map, &key);
                        if (!TYPE_METHOD(RBTREE_MAP_CONST_ITERATOR(int, int), compare)(&iterator, &end_iterator)) {
                            ++count_of_repeated_values;
                        } else {
                            struct PAIR_TYPE(int, usize)* element = TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), findElementByFirstPairValue)(&index_to_insert_value_encounter, &key);
                            if (!element) {
                                TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), push_back_by_copying)(&index_to_insert_value_encounter, &(struct PAIR_TYPE(int, usize) const){0, 0u});
                                element = TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), mut_at)(&index_to_insert_value_encounter, TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), size)(&index_to_insert_value_encounter) - 1u);
                                element->first = key;
                            }
                            ++element->second;
                        }
                        STRUCT_SUBTYPE(RBTREE_MAP(int, int), value_type) const value = {
                            .first = key,
                            .second = generate_hash(key, 188293947u)
                        };
                        TYPE_METHOD(RBTREE_MAP(int, int), insert_copy)(&rbtree_map, &value);
                    }
                }
                CHECK(TYPE_METHOD(RBTREE_MAP(int, int), size)(&rbtree_map) == (count_of_insertions - count_of_repeated_values));
                CHECK(context.count_of_allocations == (count_of_insertions - count_of_repeated_values));
                CHECK(context.count_of_allocated_bytes == context.count_of_allocations * sizeof(STRUCT_SUBTYPE(RBTREE_MAP(int, int), node_type)));
                {
                    STRUCT_SUBTYPE(RBTREE_MAP(int, int), iterator_type) const end_iterator = TYPE_METHOD(RBTREE_MAP(int, int), end)(&rbtree_map);
                    usize const erasement_shift = 7u;
                    for (usize i = 0u; i < count_of_insertions; ++i) {
                        // 'couse we're using shifting => we need to generate right hash value starting from 0 to shifted index
                        STRUCT_SUBTYPE(RBTREE_MAP(int, int), key_type) key = seed;
                        for (usize shift_i = 0u; shift_i < (i + erasement_shift) % count_of_insertions + 1u; ++shift_i) {
                            key = generate_hash(key, shift_i);
                        }

                        STRUCT_SUBTYPE(RBTREE_MAP(int, int), iterator_type) const iterator = TYPE_METHOD(RBTREE_MAP(int, int), mut_find)(&rbtree_map, &key);

                        // check is inserted value still exists and not erased using `index_to_insert_value_encounter`
                        struct PAIR_TYPE(int, usize)* insert_value_encounter_pointer = TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), findElementByFirstPairValue)(&index_to_insert_value_encounter, &key);
                        CHECK(insert_value_encounter_pointer);
                        if (insert_value_encounter_pointer->second) {
                            // if so => check value by iterator...
                            CHECK(!TYPE_METHOD(RBTREE_MAP_ITERATOR(int, int), compare)(&iterator, &end_iterator));
                            CHECK(*TYPE_METHOD(RBTREE_MAP_ITERATOR(int, int), key)(&iterator) == key);
                            CHECK(*TYPE_METHOD(RBTREE_MAP_ITERATOR(int, int), const_value)(&iterator) == generate_hash(key, 188293947u));
                            // erase element by non-end iterator
                            TYPE_METHOD(RBTREE_MAP(int, int), erase_by_iterator)(&rbtree_map, iterator);
                            // decrement counter;
                            --insert_value_encounter_pointer->second;
                        } else {
                            // else iterator must be equal to end-iterator
                            CHECK(TYPE_METHOD(RBTREE_MAP_ITERATOR(int, int), compare)(&iterator, &end_iterator));
                        }

                        // check count of not erased elements with deallocations counters
                        usize const count_of_left_values = REDUCE_OVER_ARRAY(PAIR_TYPE(int, usize))(
                            &sum_callback,
                            TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), data)(&index_to_insert_value_encounter),
                            TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), size)(&index_to_insert_value_encounter)
                        ).second;
                        CHECK(TYPE_METHOD(RBTREE_MAP(int, int), size)(&rbtree_map) == count_of_left_values);
                        CHECK(context.count_of_deallocations == (context.count_of_allocations - count_of_left_values));
                        CHECK(context.count_of_deallocated_bytes == (context.count_of_allocations - count_of_left_values) * sizeof(STRUCT_SUBTYPE(RBTREE_MAP(int, int), node_type)));
                    }
                }
                TYPE_METHOD(RBTREE_MAP(int, int), destroy_at)(&rbtree_map);
                CHECK(context.count_of_deallocations == context.count_of_allocations);
                CHECK(context.count_of_deallocated_bytes == context.count_of_allocations * sizeof(STRUCT_SUBTYPE(RBTREE_MAP(int, int), node_type)));
            }
            TYPE_METHOD(RBTREE_MAP_ALLOCATOR(int, int), destroy_at)(&allocator);
            TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), clear)(&index_to_insert_value_encounter);
        }
        TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), destroy_at)(&index_to_insert_value_encounter);
    }
}
