#include "socket.h"

#include <network/socket/socket.h>

#if defined(WIN32)
    #include <ws2def.h>
    #include <ws2ipdef.h>
#else
#endif
// #include <stdio.h>
#include <string.h>

IMPLEMENT_TYPE_TESTS(socket) {
    UNUSED(TYPE_NAME);
#if defined(WIN32)
    WSADATA wsa_data;
    ASSERT(!WSAStartup(MAKEWORD(2, 2), &wsa_data));
    ASSERT(LOBYTE(wsa_data.wVersion) == 2 && HIBYTE(wsa_data.wVersion) == 2);
#endif
    TEST_BLOCK("base socket construction/destruction") {
        SOCKET_TYPE() socket;

        SOCKET_PROTOCOL_TYPE() socket_protocol;
        socket_protocol.native_protocol = 0; // constructor & desctructor needed!

        SOCKET_METHOD(construct_at)(&socket, SOCKET_DOMAIN_ENUM_VALUE(INTERNAL), SOCKET_TYPE_ENUM_VALUE(STREAM), &socket_protocol);
        SOCKET_METHOD(destroy_at)(&socket);
    }
#if defined(WIN32)
    WSACleanup();
#endif
}
