#include "nb_server_inheritance.h"
#include <network/server/server_inheritance.h>

#if !defined(WIN32)
    #include <fcntl.h>
#endif

#include <stddef.h> // offsetof

int NB_SERVER_METHOD(on_success_bind)(struct SERVER_TYPE() const* const base) {
    // boilerplate
    struct NB_SERVER_TYPE() const* const this = (struct NB_SERVER_TYPE() const* const)((void*)base - offsetof(struct NB_SERVER_TYPE(), base_server));
    // body
#if defined(WIN32)
    u_long mode = 1;  // 1 to enable non-blocking socket
    return ioctlsocket(this->base_server.socket.native_socket, FIONBIO, &mode);
#else
    return fcntl(this->base_server.socket.native_socket, F_SETFL, fcntl(this->base_server.socket.native_socket, F_GETFL, 0) | O_NONBLOCK);
#endif
}

void* NB_SERVER_METHOD(destroy_at)(struct NB_SERVER_TYPE()* const this) {
    SERVER_METHOD(destroy_at)(&this->base_server);
    return this;
}
