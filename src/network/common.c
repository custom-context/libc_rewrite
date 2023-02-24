#include "common.h"

int NAMESPACE_NETWORK(get_last_error)() {
    #if defined(WIN32)
        return WSAGetLastError();
    #else
        return errno
    #endif
}
