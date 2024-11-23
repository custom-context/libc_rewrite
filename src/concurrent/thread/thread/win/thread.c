#include <concurrent/thread/thread/thread.h>

#include <process/native.h>
#include <primitives/data_model_types_aliases.h>
#include <construct/bool_helpers.h>
#include <construct/data_model_helpers.h>

// thread methods implementation
struct THREAD_TYPE()* THREAD_METHOD(construct_at)(struct THREAD_TYPE()* const this) {
    ASSERT(this);
    this->native_thread.native_id = GetCurrentThreadId();
    this->native_thread.native_handler = GetCurrentThread();
    this->is_joinable = false;
    return this;
}

void THREAD_METHOD(swap)(struct THREAD_TYPE()* const this, struct THREAD_TYPE()* const source) {
    {
        this->native_thread.native_id ^= source->native_thread.native_id;
        source->native_thread.native_id = this->native_thread.native_id;
        this->native_thread.native_id ^= source->native_thread.native_id;
    }

    STATIC_ASSERT(
        SIZEOF(this->native_thread.native_handler) == SIZEOF(voidptr) &&
        ALIGNOF(this->native_thread.native_handler) == ALIGNOF(voidptr)
    );
    TYPE_METHOD(voidptr, swap)((voidptr*)&this->native_thread.native_handler, (voidptr*)&source->native_thread.native_handler);

    STATIC_ASSERT(sizeof(bool) == sizeof(this->is_joinable));
    TYPE_METHOD(bool, swap)(&this->is_joinable, &source->is_joinable);
}

STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_id_type) THREAD_METHOD(get_id)(struct THREAD_TYPE() const* const this) {
    return this->native_thread.native_id;
}
STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_handler_type) THREAD_METHOD(native_handler)(struct THREAD_TYPE()* const this) {
    return this->native_thread.native_handler;
}
