#include "nb_client_inheritance.h"
#include <network/client/client_inheritance.h>

#if !defined(WIN32)
    #include <fcntl.h>
#endif

#include <stddef.h> // offsetof

int NB_CLIENT_METHOD(on_success_connection)(struct CLIENT_TYPE() const* const base) {
    // boilerplate
    struct NB_CLIENT_TYPE() const* const this = (struct NB_CLIENT_TYPE() const* const)((void*)base - offsetof(struct NB_CLIENT_TYPE(), base_client));
    // body
#if defined(WIN32)
    u_long mode = 1;  // 1 to enable non-blocking socket
    return ioctlsocket(this->base_client.socket.native_socket, FIONBIO, &mode);
#else
    return fcntl(this->base_client.socket.native_socket, F_SETFL, fcntl(this->base_client.socket.native_socket, F_GETFL, 0) | O_NONBLOCK);
#endif
}

void* NB_CLIENT_METHOD(destroy_at)(struct NB_CLIENT_TYPE()* const this) {
    CLIENT_METHOD(destroy_at)(&this->base_client);
    return this;
}
