#include <concurrent/thread/thread/thread.h>

#include <process/native.h>
#include <pthread.h>
#include <construct/bool_helpers.h>

// thread methods implementation
struct THREAD_TYPE()* THREAD_METHOD(construct_at)(struct THREAD_TYPE()* const this) {
    ASSERT(this);
    this->native_thread.native_handler = pthread_self();
    this->is_joinable = false;
    return this;
}
void THREAD_METHOD(swap)(struct THREAD_TYPE()* const this, struct THREAD_TYPE()* const source) {
    {
        STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_handler_type) temporary =
            this->native_thread.native_handler;
        this->native_thread.native_handler = source->native_thread.native_handler;
        source->native_thread.native_handler = temporary;
    }
    STATIC_ASSERT(sizeof(bool) == sizeof(this->is_joinable));
    TYPE_METHOD(bool, swap)(&this->is_joinable, &source->is_joinable);
}

STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_id_type)
    THREAD_METHOD(get_id)(struct THREAD_TYPE() const* const this) {
    return this->native_thread.native_handler;
}

STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_handler_type)
    THREAD_METHOD(native_handler)(struct THREAD_TYPE()* const this) {
    return this->native_thread.native_handler;
}
