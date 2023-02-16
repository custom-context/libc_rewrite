#include "socket.h"

#include <network/native/native.h>

struct SOCKET_TYPE()* SOCKET_METHOD(construct_at)(struct SOCKET_TYPE()* const this,
    enum SOCKET_DOMAIN_ENUM() domain,
    enum SOCKET_TYPE_ENUM() socket_type,
    struct SOCKET_PROTOCOL_TYPE() const* const NOT_NULL(protocol)) {
    ASSERT(NOT_NULL(protocol));
    this->native_socket = socket(NAMESPACE_NETWORK_NATIVE(get_native_domain)(domain), NAMESPACE_NETWORK_NATIVE(get_native_socket_type)(socket_type), NOT_NULL(protocol)->native_protocol);

    return this;
}
struct SOCKET_TYPE()* SOCKET_METHOD(construct_with_invalidation_at)(struct SOCKET_TYPE()* const this) {
#if !defined(WIN32)
    enum {
        INVALID_SOCKET = -1
    };
#endif
    this->native_socket = INVALID_SOCKET;

    return this;
}

void* SOCKET_METHOD(destroy_at)(struct SOCKET_TYPE()* const this) {
    if (!SOCKET_METHOD(is_valid)(this)) {
        return this;
    }

#if defined(WIN32)
    closesocket(this->native_socket);
#else
    close(this->native_socket);
#endif
    return this;
}

int SOCKET_METHOD(is_valid)(struct SOCKET_TYPE() const* const this) {
#if !defined(WIN32)
    enum {
        INVALID_SOCKET = -1
    };
#endif

    return this->native_socket != INVALID_SOCKET;
}
