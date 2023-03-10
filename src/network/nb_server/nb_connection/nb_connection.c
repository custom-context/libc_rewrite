#include "nb_connection.h"

int NAMESPACE_NETWORK_NB_SERVER_NB_CONNECTION(make_non_blocking)(struct CONNECTION_TYPE()* const connection) {
#if defined(WIN32)
    u_long mode = 1;  // 1 to enable non-blocking
    return ioctlsocket(connection->socket.native_socket, (long)FIONBIO, &mode);
#else
    return fcntl(connection->socket.native_socket, F_SETFL, fcntl(connection->socket.native_socket, F_GETFL, 0) ^ O_NONBLOCK);
#endif
}

int NAMESPACE_NETWORK_NB_SERVER_NB_CONNECTION(make_blocking)(struct CONNECTION_TYPE()* const connection) {
#if defined(WIN32)
    u_long mode = 0;  // 0 to disable non-blocking
    return ioctlsocket(connection->socket.native_socket, (long)FIONBIO, &mode);
#else
    return fcntl(connection->socket.native_socket, F_SETFL, fcntl(connection->socket.native_socket, F_GETFL, 0) & ~O_NONBLOCK);
#endif
}
