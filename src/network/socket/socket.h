#pragma once

#include <network/common.h>

#define NAMESPACE_NETWORK_SOCKET(NAME) NAMESPACE_NETWORK(CONCAT3(socket, __, NAME))

// Socket domain enumeration [INTERNAL, IPv4, IPv6, BLUETOOTH]
#define SOCKET_DOMAIN_ENUM() NAMESPACE_NETWORK_SOCKET(ENUM_TYPE(SOCKET_DOMAIN))
#define SOCKET_DOMAIN_ENUM_VALUE(VALUE) ENUM_VALUE(SOCKET_DOMAIN_ENUM(), VALUE)

typedef enum SOCKET_DOMAIN_ENUM() {
    SOCKET_DOMAIN_ENUM_VALUE(UNSPECIFIED),
    SOCKET_DOMAIN_ENUM_VALUE(INTERNAL),
    SOCKET_DOMAIN_ENUM_VALUE(IPv4),
    SOCKET_DOMAIN_ENUM_VALUE(IPv6)
#if !(defined(__APPLE__) && defined(__MACH__))
    ,SOCKET_DOMAIN_ENUM_VALUE(BLUETOOTH)
#endif
} SOCKET_DOMAIN_ENUM();


// Socket type enumeration [STREAM, DATAGRAM, RAW, RELIABLE_MESSAGE_DATAGRAM, SEQUENCE_PACKET]
#define SOCKET_TYPE_ENUM() NAMESPACE_NETWORK_SOCKET(ENUM_TYPE(SOCKET_TYPE))
#define SOCKET_TYPE_ENUM_VALUE(VALUE) ENUM_VALUE(SOCKET_TYPE_ENUM(), VALUE)

typedef enum SOCKET_TYPE_ENUM() {
    SOCKET_TYPE_ENUM_VALUE(STREAM),
    SOCKET_TYPE_ENUM_VALUE(DATAGRAM),
    SOCKET_TYPE_ENUM_VALUE(RAW),
    SOCKET_TYPE_ENUM_VALUE(RELIABLE_MESSAGE_DATAGRAM),
    SOCKET_TYPE_ENUM_VALUE(SEQUENCE_PACKET)
} SOCKET_TYPE_ENUM();


// Socket protocol - wrapper over int (winapi/posix are same)
#define SOCKET_PROTOCOL_TYPE() NAMESPACE_NETWORK_SOCKET(protocol)
typedef struct SOCKET_PROTOCOL_TYPE() {
    int native_protocol;
} SOCKET_PROTOCOL_TYPE();

// Socket
#define SOCKET_TYPE() NAMESPACE_NETWORK_SOCKET(socket)

typedef struct SOCKET_TYPE() {
#if defined(WIN32)
    SOCKET native_socket;
#else
    int native_socket;
#endif
} SOCKET_TYPE();

#define SOCKET_METHOD(METHOD) TYPE_METHOD(SOCKET_TYPE(), METHOD)

struct SOCKET_TYPE()* SOCKET_METHOD(construct_at)(struct SOCKET_TYPE()* const this, enum SOCKET_DOMAIN_ENUM() domain, enum SOCKET_TYPE_ENUM() socket_type, struct SOCKET_PROTOCOL_TYPE() const* const NOT_NULL(protocol));
struct SOCKET_TYPE()* SOCKET_METHOD(construct_move_at)(struct SOCKET_TYPE()* const this, struct SOCKET_TYPE()* const src);
struct SOCKET_TYPE()* SOCKET_METHOD(construct_with_invalidation_at)(struct SOCKET_TYPE()* const this);
void* SOCKET_METHOD(destroy_at)(struct SOCKET_TYPE()* const this);

int SOCKET_METHOD(is_valid)(struct SOCKET_TYPE() const* const this);

