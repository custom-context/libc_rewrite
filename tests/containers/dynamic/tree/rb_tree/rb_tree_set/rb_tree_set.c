#include "rb_tree_set.h"

#include <memory/allocator/proxy_allocator/debug.h>
#include <memory/allocator/allocator.h>

#include <containers/dynamic/tree/rb_tree/rb_tree_set/rb_tree_set.h>
DEFINE_DEFAULT_COMPARATOR_TYPE(greater, int);
DECLARE_RED_BLACK_TREE_SET_NODE_TYPE(int);

// define allocator
DEFINE_DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_SET_NODE_TYPE(int));
DEFINE_DEBUG_PROXY_ALLOCATOR_TYPE(RED_BLACK_TREE_SET_NODE_TYPE(int));

DECLARE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(int, COMPARATOR_TYPE(greater, int), PROXY_ALLOCATOR_TYPE(DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_SET_NODE_TYPE(int)), DebugAllocatorContext));

DEFINE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(static, RED_BLACK_TREE_SET_NODE_TYPE(int))
DECLARE_PROXY_ALLOCATOR_METHODS_WITH_MODIFIER(static, DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_SET_NODE_TYPE(int)), DebugAllocatorContext);
DEFINE_DEBUG_PROXY_ALLOCATOR_METHODS_WITH_MODIFIER(static, RED_BLACK_TREE_SET_NODE_TYPE(int))

DEFINE_GREATER_COMPARATOR_METHODS_WITH_MODIFIER(static, int)

// red-black tree set's methods declaration
DECLARE_RED_BLACK_TREE_SET_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(static, int, COMPARATOR_TYPE(greater, int), PROXY_ALLOCATOR_TYPE(DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_SET_NODE_TYPE(int)), DebugAllocatorContext));

// red-black tree set's methods definition
DEFINE_RED_BLACK_TREE_SET_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(static, int, COMPARATOR_TYPE(greater, int), PROXY_ALLOCATOR_TYPE(DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_SET_NODE_TYPE(int)), DebugAllocatorContext))

// define helper macros
#define RBTREE_SET_ALLOCATOR(TYPE) PROXY_ALLOCATOR_TYPE(DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_SET_NODE_TYPE(TYPE)), DebugAllocatorContext)
#define RBTREE_SET(TYPE) RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR_TYPE(greater, TYPE), PROXY_ALLOCATOR_TYPE(DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_SET_NODE_TYPE(int)), DebugAllocatorContext))
#define RBTREE_SET_CONST_ITERATOR(TYPE) RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR_TYPE(greater, TYPE), PROXY_ALLOCATOR_TYPE(DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_SET_NODE_TYPE(TYPE)), DebugAllocatorContext))
#define RBTREE_SET_ITERATOR(TYPE) RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR_TYPE(greater, TYPE), PROXY_ALLOCATOR_TYPE(DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_SET_NODE_TYPE(TYPE)), DebugAllocatorContext))

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

#define LAST_NON_ZERO_VALUE_OF_ARRAY(TYPE)\
    CONCAT3(last_non_zero_value_of_array, __, TYPE)
#define DEFINE_LAST_NON_ZERO_VALUE_OF_ARRAY(TYPE)\
static usize LAST_NON_ZERO_VALUE_OF_ARRAY(TYPE)(TYPE const* const array, usize const size) {\
    TYPE result;\
    TYPE_METHOD(TYPE, construct_at)(&result);\
    for (usize index = 0u; index < size; ++index) {\
        if (array[size - index - 1u]) {\
            return index;\
        };\
    }\
    return 0u;\
}

#include <construct/data_model_helpers.h>
DEFINE_LAST_NON_ZERO_VALUE_OF_ARRAY(usize)

static void onAllocation(
    DebugAllocatorContext* const context,
    DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_SET_NODE_TYPE(int))* const allocator,
    usize count_of_elements) {
    ASSERT(allocator);
    ++context->count_of_allocations;
    context->count_of_allocated_bytes += count_of_elements * sizeof(RED_BLACK_TREE_SET_NODE_TYPE(int));
}

static void onDeallocation(
    DebugAllocatorContext* const context,
    DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_SET_NODE_TYPE(int))* const allocator,
    STRUCT_SUBTYPE(RBTREE_SET(int), node_type)* const buffer,
    usize count_of_elements) {
    ASSERT(allocator);
    ASSERT(buffer);
    ++context->count_of_deallocations;
    context->count_of_deallocated_bytes += count_of_elements * sizeof(STRUCT_SUBTYPE(RBTREE_SET(int), node_type));
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

static void printRBTreeSubtree(STRUCT_SUBTYPE(RBTREE_SET(int), node_type) const * const node, usize const depth) {
    ASSERT(node);
    if (node->child[0u]) {
        printRBTreeSubtree(node->child[0u], depth + 1u);
    }

    for (usize i = 0u; i < depth; ++i) {
        putchar('\t');
    }
    printf("(%i, %s)\n", node->value, node->color == RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(int, RED) ? "RED" : "BLACK");

    if (node->child[1u]) {
        printRBTreeSubtree(node->child[1u], depth + 1u);
    }
}

#include <containers/pair/pair.h>
DEFINE_PAIR_TYPE(int, usize);
DEFINE_PAIR_METHODS_WITH_MODIFIER(static, int, usize)

#include <memory/allocator/allocator.h>
DEFINE_DEFAULT_ALLOCATOR_TYPE(PAIR_TYPE(int, usize));
DEFINE_DEFAULT_ALLOCATOR_STATIC_METHODS(PAIR_TYPE(int, usize))
#include <containers/dynamic/array/array.h>
DECLARE_DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize));
IMPLEMENT_DYNAMIC_ARRAY_TYPE_STATIC_METHODS(PAIR_TYPE(int, usize))

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

IMPLEMENT_TYPE_TESTS(rb_tree_set) {
    TEST_BLOCK("`size` method on empty red-black tree set") {
        struct RBTREE_SET(int) rbtree_set;
        TYPE_METHOD(RBTREE_SET(int), construct_at)(&rbtree_set);
        CHECK(!TYPE_METHOD(RBTREE_SET(int), size)(&rbtree_set));
        TYPE_METHOD(RBTREE_SET(int), destroy_at)(&rbtree_set);
    }
    TEST_BLOCK("`find` on empty red-black tree set") {
        struct RBTREE_SET_ALLOCATOR(int) allocator;
        TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), construct_at)(&allocator);
        // set callbacks for allocator
        DebugAllocatorContext context = {0};
        allocator.context = &context;
        allocator.on_allocation = &onAllocation;
        allocator.on_deallocation = &onDeallocation;

        struct RBTREE_SET(int) rbtree_set;
        TYPE_METHOD(RBTREE_SET(int), construct_with_allocator_at)(&rbtree_set, &allocator);
        {
            int const value = 534343;
            STRUCT_SUBTYPE(RBTREE_SET(int), const_iterator_type) const iterator = TYPE_METHOD(RBTREE_SET(int), find)(&rbtree_set, &value);
            STRUCT_SUBTYPE(RBTREE_SET(int), const_iterator_type) const end_iterator = TYPE_METHOD(RBTREE_SET(int), cend)(&rbtree_set);
            CHECK(TYPE_METHOD(RBTREE_SET_CONST_ITERATOR(int), compare)(&iterator, &end_iterator));
        }
        CHECK(!TYPE_METHOD(RBTREE_SET(int), size)(&rbtree_set));
        CHECK(!context.count_of_allocated_bytes);
        CHECK(!context.count_of_allocations);

        TYPE_METHOD(RBTREE_SET(int), destroy_at)(&rbtree_set);
        CHECK(!context.count_of_allocated_bytes);
        CHECK(!context.count_of_deallocations);

        TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), destroy_at)(&allocator);
    }
    TEST_BLOCK("`emplace` 1 element + `find` it & try to `find` another value on red-black tree set") {
        struct RBTREE_SET_ALLOCATOR(int) allocator;
        TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), construct_at)(&allocator);
        // set callbacks for allocator
        DebugAllocatorContext context = {0};
        allocator.context = &context;
        allocator.on_allocation = &onAllocation;
        allocator.on_deallocation = &onDeallocation;

        struct RBTREE_SET(int) rbtree_set;
        TYPE_METHOD(RBTREE_SET(int), construct_with_allocator_at)(&rbtree_set, &allocator);

        // insert copy of one value
        {
            int const value = 232992;
            TYPE_METHOD(RBTREE_SET(int), insert_copy)(&rbtree_set, &value);
        }
        CHECK(context.count_of_allocated_bytes == sizeof(STRUCT_SUBTYPE(RBTREE_SET(int), node_type)));
        CHECK(context.count_of_allocations == 1u);

        // try find same value
        {
            int const value = 232992;
            STRUCT_SUBTYPE(RBTREE_SET(int), const_iterator_type) const iterator = TYPE_METHOD(RBTREE_SET(int), find)(&rbtree_set, &value);
            STRUCT_SUBTYPE(RBTREE_SET(int), const_iterator_type) const end_iterator = TYPE_METHOD(RBTREE_SET(int), cend)(&rbtree_set);
            CHECK(!TYPE_METHOD(RBTREE_SET_CONST_ITERATOR(int), compare)(&iterator, &end_iterator));
            CHECK(*TYPE_METHOD(RBTREE_SET_CONST_ITERATOR(int), const_value)(&iterator) == value);
        }
        // try same call function with another value provided
        {
            int const value = 75383;
            STRUCT_SUBTYPE(RBTREE_SET(int), const_iterator_type) const iterator = TYPE_METHOD(RBTREE_SET(int), find)(&rbtree_set, &value);
            STRUCT_SUBTYPE(RBTREE_SET(int), const_iterator_type) const end_iterator = TYPE_METHOD(RBTREE_SET(int), cend)(&rbtree_set);
            CHECK(TYPE_METHOD(RBTREE_SET_CONST_ITERATOR(int), compare)(&iterator, &end_iterator));
        }
        TYPE_METHOD(RBTREE_SET(int), destroy_at)(&rbtree_set);
        CHECK(context.count_of_deallocated_bytes == sizeof(STRUCT_SUBTYPE(RBTREE_SET(int), node_type)));
        CHECK(context.count_of_deallocations == 1u);

        TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), destroy_at)(&allocator);
    }
    TEST_BLOCK("`private(rebalance_after_insertion)` test tree") {
        struct RBTREE_SET_ALLOCATOR(int) allocator;
        TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), construct_at)(&allocator);
        // set callbacks for allocator
        DebugAllocatorContext context = {0};
        allocator.context = &context;
        allocator.on_allocation = &onAllocation;
        allocator.on_deallocation = &onDeallocation;

        struct RBTREE_SET(int) rbtree_set;
        TYPE_METHOD(RBTREE_SET(int), construct_with_allocator_at)(&rbtree_set, &allocator);

        STRUCT_SUBTYPE(RBTREE_SET(int), node_type)* const grandparent = TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), allocate)(&allocator, 1u);
        TYPE_METHOD(RBTREE_SET(int), PRIVATE(construct_node_at))(grandparent); 
        rbtree_set.root = grandparent;

        STRUCT_SUBTYPE(RBTREE_SET(int), node_type)* const parent = TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), allocate)(&allocator, 1u);
        TYPE_METHOD(RBTREE_SET(int), PRIVATE(construct_node_at))(parent);
        grandparent->child[1u] = parent;
        parent->parent = grandparent;

        STRUCT_SUBTYPE(RBTREE_SET(int), node_type)* const sibling = TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), allocate)(&allocator, 1u);
        TYPE_METHOD(RBTREE_SET(int), PRIVATE(construct_node_at))(sibling);
        parent->child[0u] = sibling;
        sibling->parent = parent;

        STRUCT_SUBTYPE(RBTREE_SET(int), node_type)* const node = TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), allocate)(&allocator, 1u);
        TYPE_METHOD(RBTREE_SET(int), PRIVATE(construct_node_at))(node);
        parent->child[1u] = node;
        node->parent = parent;

        CHECK(context.count_of_allocations == 4u);
        CHECK(context.count_of_allocated_bytes == context.count_of_allocations * sizeof(STRUCT_SUBTYPE(RBTREE_SET(int), node_type)));

        TYPE_METHOD(RBTREE_SET(int), PRIVATE(rotate))(&rbtree_set, grandparent, 0u);

        CHECK(grandparent->parent == parent);
        CHECK(grandparent->child[0u] == NULL);
        CHECK(grandparent->child[1u] == sibling);

        CHECK(parent->parent == NULL);
        CHECK(parent->child[0u] == grandparent);
        CHECK(parent->child[1u] == node);

        CHECK(sibling->parent == grandparent);
        CHECK(sibling->child[0u] == NULL);
        CHECK(sibling->child[1u] == NULL);

        CHECK(node->parent == parent);
        CHECK(node->child[0u] == NULL);
        CHECK(node->child[1u] == NULL);

        TYPE_METHOD(RBTREE_SET(int), destroy_at)(&rbtree_set);
        CHECK(context.count_of_deallocations == 4u);
        CHECK(context.count_of_deallocated_bytes == context.count_of_deallocations * sizeof(STRUCT_SUBTYPE(RBTREE_SET(int), node_type)));

        TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), destroy_at)(&allocator);
    }
    TEST_BLOCK("`emplace` many elements + `find` all of them on red-black tree set") {
        struct RBTREE_SET_ALLOCATOR(int) allocator;
        TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), construct_at)(&allocator);
        // set callbacks for allocator
        DebugAllocatorContext context = {0};
        allocator.context = &context;
        allocator.on_allocation = &onAllocation;
        allocator.on_deallocation = &onDeallocation;

        struct RBTREE_SET(int) rbtree_set;
        TYPE_METHOD(RBTREE_SET(int), construct_with_allocator_at)(&rbtree_set, &allocator);
        usize const count_of_insertions = 2000;
        usize count_of_repeated_values = 0u;

        STRUCT_SUBTYPE(RBTREE_SET(int), value_type) const seed = -34345328;
        {
            STRUCT_SUBTYPE(RBTREE_SET(int), const_iterator_type) const end_iterator = TYPE_METHOD(RBTREE_SET(int), cend)(&rbtree_set);
            STRUCT_SUBTYPE(RBTREE_SET(int), value_type) prev_value = seed;
            for (usize i = 0u; i < count_of_insertions; ++i) {
                STRUCT_SUBTYPE(RBTREE_SET(int), value_type) const value = generate_hash(prev_value, i);
                prev_value = value;
                STRUCT_SUBTYPE(RBTREE_SET(int), const_iterator_type) const iterator = TYPE_METHOD(RBTREE_SET(int), find)(&rbtree_set, &value);
                if (!TYPE_METHOD(RBTREE_SET_CONST_ITERATOR(int), compare)(&iterator, &end_iterator)) {
                    ++count_of_repeated_values;
                }
                TYPE_METHOD(RBTREE_SET(int), insert_copy)(&rbtree_set, &value);
            }
        }
        CHECK(TYPE_METHOD(RBTREE_SET(int), size)(&rbtree_set) == (count_of_insertions - count_of_repeated_values));
        CHECK(context.count_of_allocations == (count_of_insertions - count_of_repeated_values));
        CHECK(context.count_of_allocated_bytes == context.count_of_allocations * sizeof(STRUCT_SUBTYPE(RBTREE_SET(int), node_type)));
        {
            STRUCT_SUBTYPE(RBTREE_SET(int), value_type) prev_value = seed;
            STRUCT_SUBTYPE(RBTREE_SET(int), const_iterator_type) const end_iterator = TYPE_METHOD(RBTREE_SET(int), cend)(&rbtree_set);
            for (usize i = 0u; i < count_of_insertions; ++i) {
                STRUCT_SUBTYPE(RBTREE_SET(int), value_type) const value = generate_hash(prev_value, i);
                prev_value = value;
                STRUCT_SUBTYPE(RBTREE_SET(int), const_iterator_type) const iterator = TYPE_METHOD(RBTREE_SET(int), find)(&rbtree_set, &value);
                CHECK(!TYPE_METHOD(RBTREE_SET_CONST_ITERATOR(int), compare)(&iterator, &end_iterator));
                CHECK(*TYPE_METHOD(RBTREE_SET_CONST_ITERATOR(int), const_value)(&iterator) == value);
            }
        }
        TYPE_METHOD(RBTREE_SET(int), destroy_at)(&rbtree_set);
        CHECK(context.count_of_deallocations == (count_of_insertions - count_of_repeated_values));
        CHECK(context.count_of_deallocated_bytes == context.count_of_deallocations * sizeof(STRUCT_SUBTYPE(RBTREE_SET(int), node_type)));

        TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), destroy_at)(&allocator);
    }
    TEST_BLOCK("`private(swap_nodes)` test tree") {
        struct RBTREE_SET_ALLOCATOR(int) allocator;
        TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), construct_at)(&allocator);
        DebugAllocatorContext context = {0};
        allocator.context = &context;
        allocator.on_allocation = &onAllocation;
        allocator.on_deallocation = &onDeallocation;
        {
            struct RBTREE_SET(int) rbtree_set;
            TYPE_METHOD(RBTREE_SET(int), construct_with_allocator_at)(&rbtree_set, &allocator);

            STRUCT_SUBTYPE(RBTREE_SET(int), node_type)* const grandparent = TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), allocate)(&allocator, 1u);
            TYPE_METHOD(RBTREE_SET(int), PRIVATE(construct_node_at))(grandparent); 
            rbtree_set.root = grandparent;

            STRUCT_SUBTYPE(RBTREE_SET(int), node_type)* const parent_sibling =
                TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), allocate)(&allocator, 1u);
            TYPE_METHOD(RBTREE_SET(int), PRIVATE(construct_node_at))(parent_sibling);
            grandparent->child[0u] = parent_sibling;
            parent_sibling->parent = grandparent;

            STRUCT_SUBTYPE(RBTREE_SET(int), node_type)* const parent =
                TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), allocate)(&allocator, 1u);
            TYPE_METHOD(RBTREE_SET(int), PRIVATE(construct_node_at))(parent);
            grandparent->child[1u] = parent;
            parent->parent = grandparent;

            STRUCT_SUBTYPE(RBTREE_SET(int), node_type)* const sibling = TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), allocate)(&allocator, 1u);
            TYPE_METHOD(RBTREE_SET(int), PRIVATE(construct_node_at))(sibling);
            parent->child[0u] = sibling;
            sibling->parent = parent;

            STRUCT_SUBTYPE(RBTREE_SET(int), node_type)* const node = TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), allocate)(&allocator, 1u);
            TYPE_METHOD(RBTREE_SET(int), PRIVATE(construct_node_at))(node);
            parent->child[1u] = node;
            node->parent = parent;

            CHECK(context.count_of_allocations == 5u);
            CHECK(context.count_of_allocated_bytes == context.count_of_allocations * sizeof(STRUCT_SUBTYPE(RBTREE_SET(int), node_type)));

            // swap nodes
            TYPE_METHOD(RBTREE_SET(int), PRIVATE(swap_nodes))(&rbtree_set, parent, grandparent);

            CHECK(rbtree_set.root == parent);

            CHECK(grandparent->parent == parent);
            CHECK(grandparent->child[0u] == sibling);
            CHECK(grandparent->child[1u] == node);

            CHECK(parent_sibling->parent == parent);
            CHECK(parent_sibling->child[0u] == NULL);
            CHECK(parent_sibling->child[1u] == NULL);

            CHECK(parent->parent == NULL);
            CHECK(parent->child[0u] == parent_sibling);
            CHECK(parent->child[1u] == grandparent);

            CHECK(sibling->parent == grandparent);
            CHECK(sibling->child[0u] == NULL);
            CHECK(sibling->child[1u] == NULL);

            CHECK(node->parent == grandparent);
            CHECK(node->child[0u] == NULL);
            CHECK(node->child[1u] == NULL);

            // swap nodes backward
            TYPE_METHOD(RBTREE_SET(int), PRIVATE(swap_nodes))(&rbtree_set, grandparent, parent);

            CHECK(rbtree_set.root == grandparent);

            CHECK(grandparent->parent == NULL);
            CHECK(grandparent->child[0u] == parent_sibling);
            CHECK(grandparent->child[1u] == parent);

            CHECK(parent_sibling->parent == grandparent);
            CHECK(parent_sibling->child[0u] == NULL);
            CHECK(parent_sibling->child[1u] == NULL);

            CHECK(parent->parent == grandparent);
            CHECK(parent->child[0u] == sibling);
            CHECK(parent->child[1u] == node);

            CHECK(sibling->parent == parent);
            CHECK(sibling->child[0u] == NULL);
            CHECK(sibling->child[1u] == NULL);

            CHECK(node->parent == parent);
            CHECK(node->child[0u] == NULL);
            CHECK(node->child[1u] == NULL);

            // destroy tree
            TYPE_METHOD(RBTREE_SET(int), destroy_at)(&rbtree_set);
            CHECK(context.count_of_deallocations == 5u);
            CHECK(context.count_of_deallocated_bytes == context.count_of_deallocations * sizeof(STRUCT_SUBTYPE(RBTREE_SET(int), node_type)));
        }
        TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), destroy_at)(&allocator);
    }
    TEST_BLOCK("`emplace` many elements + `erase` all of them in different order on red-black tree set") {
        usize const max_count_of_insertions = 500u;
        struct DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)) index_to_insert_value_encounter;
        /* construct index_to_insert_value_encounter array with zeroes */{
            TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), construct_at)(&index_to_insert_value_encounter);
            TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), reserve)(&index_to_insert_value_encounter, max_count_of_insertions);
        }
        for (usize count_of_insertions = 1u; count_of_insertions <= max_count_of_insertions; ++count_of_insertions) {
            struct RBTREE_SET_ALLOCATOR(int) allocator;
            TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), construct_at)(&allocator);
            // set callbacks for allocator
            DebugAllocatorContext context = {0};
            allocator.context = &context;
            allocator.on_allocation = &onAllocation;
            allocator.on_deallocation = &onDeallocation;

            struct RBTREE_SET(int) rbtree_set;
            TYPE_METHOD(RBTREE_SET(int), construct_with_allocator_at)(&rbtree_set, &allocator);
            usize count_of_repeated_values = 0u;

            STRUCT_SUBTYPE(RBTREE_SET(int), value_type) const seed = 19834748;
            {
                STRUCT_SUBTYPE(RBTREE_SET(int), value_type) prev_value = seed;
                STRUCT_SUBTYPE(RBTREE_SET(int), const_iterator_type) const end_iterator = TYPE_METHOD(RBTREE_SET(int), cend)(&rbtree_set);
                for (usize i = 0u; i < count_of_insertions; ++i) {
                    STRUCT_SUBTYPE(RBTREE_SET(int), value_type) const value = prev_value = generate_hash(prev_value, i);
                    STRUCT_SUBTYPE(RBTREE_SET(int), const_iterator_type) const iterator = TYPE_METHOD(RBTREE_SET(int), find)(&rbtree_set, &value);
                    if (!TYPE_METHOD(RBTREE_SET_CONST_ITERATOR(int), compare)(&iterator, &end_iterator)) {
                        ++count_of_repeated_values;
                    } else {
                        struct PAIR_TYPE(int, usize)* element = TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), findElementByFirstPairValue)(&index_to_insert_value_encounter, &value);
                        if (!element) {
                            TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), push_back_by_copying)(&index_to_insert_value_encounter, &(struct PAIR_TYPE(int, usize) const){0, 0u});
                            element = TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), mut_at)(&index_to_insert_value_encounter, TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), size)(&index_to_insert_value_encounter) - 1u);
                            element->first = value;
                        }
                        ++element->second;
                    }
                    TYPE_METHOD(RBTREE_SET(int), insert_copy)(&rbtree_set, &value);
                }
            }
            CHECK(TYPE_METHOD(RBTREE_SET(int), size)(&rbtree_set) == (count_of_insertions - count_of_repeated_values));
            CHECK(context.count_of_allocations == (count_of_insertions - count_of_repeated_values));
            CHECK(context.count_of_allocated_bytes == context.count_of_allocations * sizeof(STRUCT_SUBTYPE(RBTREE_SET(int), node_type)));
            {
                STRUCT_SUBTYPE(RBTREE_SET(int), iterator_type) const end_iterator = TYPE_METHOD(RBTREE_SET(int), end)(&rbtree_set);
                usize const erasement_shift = 7u;
                for (usize i = 0u; i < count_of_insertions; ++i) {
                    // 'couse we're using shifting => we need to generate right hash value starting from 0 to shifted index
                    STRUCT_SUBTYPE(RBTREE_SET(int), value_type) value = seed;
                    for (usize shift_i = 0u; shift_i < (i + erasement_shift) % count_of_insertions + 1u; ++shift_i) {
                        value = generate_hash(value, shift_i);                        
                    }

                    STRUCT_SUBTYPE(RBTREE_SET(int), iterator_type) const iterator = TYPE_METHOD(RBTREE_SET(int), mut_find)(&rbtree_set, &value);

                    // check is inserted value still exists and not erased using `index_to_insert_value_encounter`
                    struct PAIR_TYPE(int, usize)* insert_value_encounter_pointer = TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), findElementByFirstPairValue)(&index_to_insert_value_encounter, &value);
                    CHECK(insert_value_encounter_pointer);
                    if (insert_value_encounter_pointer->second) {
                        // if so => check value by iterator...
                        CHECK(!TYPE_METHOD(RBTREE_SET_ITERATOR(int), compare)(&iterator, &end_iterator));
                        CHECK(*TYPE_METHOD(RBTREE_SET_ITERATOR(int), const_value)(&iterator) == value);
                        // erase element by non-end iterator
                        TYPE_METHOD(RBTREE_SET(int), erase_by_iterator)(&rbtree_set, iterator);
                        // decrement counter;
                        --insert_value_encounter_pointer->second;
                    } else {
                        // else iterator must be equal to end-iterator
                        CHECK(TYPE_METHOD(RBTREE_SET_ITERATOR(int), compare)(&iterator, &end_iterator));
                    }

                    // check count of not erased elements with deallocations counters
                    usize const count_of_left_values = REDUCE_OVER_ARRAY(PAIR_TYPE(int, usize))(
                        &sum_callback,
                        TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), data)(&index_to_insert_value_encounter),
                        TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), size)(&index_to_insert_value_encounter)
                    ).second;
                    CHECK(TYPE_METHOD(RBTREE_SET(int), size)(&rbtree_set) == count_of_left_values);
                    CHECK(context.count_of_deallocations == (context.count_of_allocations - count_of_left_values));
                    CHECK(context.count_of_deallocated_bytes == (context.count_of_allocations - count_of_left_values) * sizeof(STRUCT_SUBTYPE(RBTREE_SET(int), node_type)));
                }
            }
            TYPE_METHOD(RBTREE_SET(int), destroy_at)(&rbtree_set);
            CHECK(context.count_of_deallocations == context.count_of_allocations);
            CHECK(context.count_of_deallocated_bytes == context.count_of_allocations * sizeof(STRUCT_SUBTYPE(RBTREE_SET(int), node_type)));
            TYPE_METHOD(RBTREE_SET_ALLOCATOR(int), destroy_at)(&allocator);
            TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), clear)(&index_to_insert_value_encounter);
        }
        TYPE_METHOD(DYNAMIC_ARRAY_TYPE(PAIR_TYPE(int, usize)), destroy_at)(&index_to_insert_value_encounter);
    }
}
