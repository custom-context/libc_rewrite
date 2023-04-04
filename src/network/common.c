#include "common.h"
#include <errno.h>

int NAMESPACE_NETWORK(get_last_error)(void) {
    #if defined(WIN32)
        return WSAGetLastError();
    #else
        return errno;
    #endif
}
