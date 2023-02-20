#include "native.h"

#if !defined(WIN32)
    #include <sys/types.h>
    #include <netdb.h>
#endif

int NAMESPACE_NETWORK_NATIVE(get_native_domain)(enum SOCKET_DOMAIN_ENUM() domain) {
    switch (domain) {
    case SOCKET_DOMAIN_ENUM_VALUE(UNSPECIFIED):
        return AF_UNSPEC;
    case SOCKET_DOMAIN_ENUM_VALUE(INTERNAL):
#if defined(WIN32)
        return AF_UNSPEC;
#else
        return AF_LOCAL;
#endif
    case SOCKET_DOMAIN_ENUM_VALUE(IPv4):
        return AF_INET;
    case SOCKET_DOMAIN_ENUM_VALUE(IPv6):
        return AF_INET6;
    case SOCKET_DOMAIN_ENUM_VALUE(BLUETOOTH):
#if defined(WIN32)
        return AF_BTH;
#else
        return AF_BLUETOOTH;
#endif
    }
    return AF_UNSPEC;
}
enum SOCKET_DOMAIN_ENUM() NAMESPACE_NETWORK_NATIVE(get_wrapped_domain)(int native_domain) {
    switch (native_domain) {
        case AF_UNSPEC:
            return SOCKET_DOMAIN_ENUM_VALUE(UNSPECIFIED);
#if !defined(WIN32)
        case AF_LOCAL:
            return SOCKET_DOMAIN_ENUM_VALUE(INTERNAL);
#endif
        case AF_INET:
            return SOCKET_DOMAIN_ENUM_VALUE(IPv4);
        case AF_INET6:
            return SOCKET_DOMAIN_ENUM_VALUE(IPv6);
#if defined(WIN32)
        case AF_BTH:
#else
        case AF_BLUETOOTH:
#endif
            return SOCKET_DOMAIN_ENUM_VALUE(BLUETOOTH);
    }

    return SOCKET_DOMAIN_ENUM_VALUE(UNSPECIFIED);
}

int NAMESPACE_NETWORK_NATIVE(get_native_socket_type)(enum SOCKET_TYPE_ENUM() socket_type) {
    switch (socket_type) {
        case SOCKET_TYPE_ENUM_VALUE(STREAM): return SOCK_STREAM;
        case SOCKET_TYPE_ENUM_VALUE(DATAGRAM): return SOCK_DGRAM;
        case SOCKET_TYPE_ENUM_VALUE(RAW): return SOCK_RAW;
        case SOCKET_TYPE_ENUM_VALUE(RELIABLE_MESSAGE_DATAGRAM): return SOCK_RDM;
        case SOCKET_TYPE_ENUM_VALUE(SEQUENCE_PACKET): return SOCK_SEQPACKET;
    }
    // TODO: change to optional or error socket type
    return SOCK_STREAM;
}
enum SOCKET_TYPE_ENUM() NAMESPACE_NETWORK_NATIVE(get_wrapped_socket_type)(int native_socket_type) {
    switch (native_socket_type) {
        case SOCK_STREAM: return SOCKET_TYPE_ENUM_VALUE(STREAM);
        case SOCK_DGRAM: return SOCKET_TYPE_ENUM_VALUE(DATAGRAM);
        case SOCK_RAW: return SOCKET_TYPE_ENUM_VALUE(RAW);
        case SOCK_RDM: return SOCKET_TYPE_ENUM_VALUE(RELIABLE_MESSAGE_DATAGRAM);
        case SOCK_SEQPACKET: return SOCKET_TYPE_ENUM_VALUE(SEQUENCE_PACKET);
    }

    return SOCKET_TYPE_ENUM_VALUE(STREAM);
}
