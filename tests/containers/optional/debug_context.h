#pragma once

#include <tests/utils/macros.h>
#include <primitives/data_model_types_aliases.h>

typedef struct debug_context {
    usize count_of_construct_at;
    usize count_of_destroy_at;
    usize count_of_construct_copy_at;
    usize count_of_construct_move_at;
    usize count_of_assign_copy_at;
    usize count_of_assign_move_at;
    usize count_of_swap;
} debug_context;

static struct debug_context global_debug_context;

#define DEBUG_CONTEXT() (&global_debug_context)

#define GLOBAL_DEBUG_CONTEXT_FLUSH()\
do {\
    global_debug_context = (struct debug_context){ 0 };\
} while(false)

static struct debug_context* TYPE_METHOD(debug_context, construct_at)(struct debug_context* const this) {
    ASSERT(this);

    ++global_debug_context.count_of_construct_at;

    return this;
}

static struct debug_context* TYPE_METHOD(debug_context, construct_copy_at)(struct debug_context* const this, struct debug_context const* const source) {
    ASSERT(this);
    ASSERT(source);

    ++global_debug_context.count_of_construct_copy_at;

    return this;
}

static struct debug_context* TYPE_METHOD(debug_context, construct_move_at)(struct debug_context* const this, struct debug_context* const source) {
    ASSERT(this);
    ASSERT(source);

    ++global_debug_context.count_of_construct_move_at;

    return this;
}

static struct debug_context* TYPE_METHOD(debug_context, assign_copy_at)(struct debug_context* const this, struct debug_context const* const source) {
    ASSERT(this);
    ASSERT(source);

    ++global_debug_context.count_of_assign_copy_at;

    return this;
}

static struct debug_context* TYPE_METHOD(debug_context, assign_move_at)(struct debug_context* const this, struct debug_context* const source) {
    ASSERT(this);
    ASSERT(source);

    ++global_debug_context.count_of_assign_move_at;

    return this;
}

static void TYPE_METHOD(debug_context, swap)(struct debug_context* const this, struct debug_context* const source) {
    ASSERT(this);
    ASSERT(source);

    ++global_debug_context.count_of_swap;
}


static struct debug_context* TYPE_METHOD(debug_context, destroy_at)(struct debug_context* const this) {
    ASSERT(this);
    ++global_debug_context.count_of_destroy_at;
    return this;
}

#define GLOBAL_DEBUG_CONTEXT_CHECK_EQ()\
CHECK(0u\
    + global_debug_context.count_of_assign_copy_at\
    + global_debug_context.count_of_assign_move_at\
    + global_debug_context.count_of_construct_at\
    + global_debug_context.count_of_construct_copy_at\
    + global_debug_context.count_of_construct_move_at\
    == global_debug_context.count_of_destroy_at\
)

