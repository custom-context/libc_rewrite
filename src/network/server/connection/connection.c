#include "connection.h"

#if !defined(WIN32)
    #include <errno.h>
#endif

#include <utils/debug.h>

DEFINE_RESULT_TYPE_STATIC_METHODS(int, int);

int CONNECTION_METHOD(is_established)(struct CONNECTION_TYPE() const* const this) {
    return SOCKET_METHOD(is_valid)(&this->socket);
}

struct RESULT_TYPE(int, int) CONNECTION_METHOD(status)(struct CONNECTION_TYPE() const* const this) {
    struct RESULT_TYPE(int, int) result;

    int error_code = 0;
#if defined (WIN32)
    int error_code_size;
#else
    socklen_t error_code_size;
#endif
    error_code_size = sizeof(error_code);
    if (getsockopt(this->socket.native_socket,
        SOL_SOCKET,
        SO_ERROR,
        (void*)(&error_code),
        &error_code_size) == -1) {
        error_code = NAMESPACE_NETWORK(get_last_error)();
        RESULT_METHOD(int, int, construct_move_from_error_at)(&result, &error_code);
        return result;
    }
    RESULT_METHOD(int, int, construct_move_from_value_at)(&result, &error_code);
    return result;
}

int CONNECTION_METHOD(send)(struct CONNECTION_TYPE() const* const this,
    void* const buffer,
    size_t buffer_size
) {
    ASSERT(CONNECTION_METHOD(is_established)(this));

    return send(this->socket.native_socket, buffer, buffer_size, 0);
}

int CONNECTION_METHOD(receive)(struct CONNECTION_TYPE() const* const this,
    void* const buffer,
    size_t buffer_size
) {
    ASSERT(CONNECTION_METHOD(is_established)(this));

    return recv(this->socket.native_socket, buffer, buffer_size, 0);
}

void* CONNECTION_METHOD(destroy_at)(struct CONNECTION_TYPE()* const this) {
    SOCKET_METHOD(destroy_at)(&this->socket);
    return this;
}
