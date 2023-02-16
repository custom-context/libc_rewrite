#pragma once

#include <utils/macros.h>

#if defined(WIN32)
    #include <winsock2.h>
#else
#endif

#define NAMESPACE_NETWORK(NAME) CONCAT3(network, __, NAME)
