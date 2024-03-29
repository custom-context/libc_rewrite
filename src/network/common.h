#pragma once

#include <utils/macros.h>

#if defined(WIN32)
    #include <WinSock2.h>
#else
    #include <sys/socket.h>
#endif

#define NAMESPACE_NETWORK(NAME) CONCAT3(network, __, NAME)

#include <utils/result.h>
DEFINE_RESULT_TYPE(int, int);

int NAMESPACE_NETWORK(get_last_error)(void);
