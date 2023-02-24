#pragma once

#include <network/socket/socket.h>
#include <network/common.h>

#include <containers/dynamic/string/string.h>

#if defined(WIN32)
    #include <ws2def.h>
    #include <ws2ipdef.h>
#else
#endif

#define NAMESPACE_NETWORK_ADDRESS_INFO(NAME) NAMESPACE_NETWORK(CONCAT3(address_info, __, NAME))

// Address info criterias
#define ADDRESS_INFO_CRITERIAS_TYPE() NAMESPACE_NETWORK_ADDRESS_INFO(address_info_criterias)
typedef struct ADDRESS_INFO_CRITERIAS_TYPE() {
    SOCKET_DOMAIN_ENUM() socket_domain;
    SOCKET_TYPE_ENUM() socket_type;
    SOCKET_PROTOCOL_TYPE() socket_protocol;
    int native_extra_flags; 
} ADDRESS_INFO_CRITERIAS_TYPE();

// Address info
#define ADDRESS_INFO_TYPE() NAMESPACE_NETWORK_ADDRESS_INFO(address_info)
typedef struct ADDRESS_INFO_TYPE() {
    struct addrinfo* native_address_info;
} ADDRESS_INFO_TYPE();

#define ADDRESS_INFO_METHOD(METHOD) TYPE_METHOD(ADDRESS_INFO_TYPE(), METHOD)

struct ADDRESS_INFO_TYPE()* ADDRESS_INFO_METHOD(construct_at)(struct ADDRESS_INFO_TYPE()* const this);

// TODO: make return value as pair type: (address_info*, error)
struct ADDRESS_INFO_TYPE()* ADDRESS_INFO_METHOD(construct_with_fetch_at)(struct ADDRESS_INFO_TYPE()* const this,
    char const* const restrict host,
    char const* const restrict service,
    struct ADDRESS_INFO_CRITERIAS_TYPE() const* const address_info_criterias
);

SOCKET_DOMAIN_ENUM() ADDRESS_INFO_METHOD(get_socket_domain)(struct ADDRESS_INFO_TYPE() const* const this);
SOCKET_TYPE_ENUM() ADDRESS_INFO_METHOD(get_socket_type)(struct ADDRESS_INFO_TYPE() const* const this);
SOCKET_PROTOCOL_TYPE() ADDRESS_INFO_METHOD(get_socket_protocol)(struct ADDRESS_INFO_TYPE() const* const this);

int ADDRESS_INFO_METHOD(send)(
    struct ADDRESS_INFO_TYPE() const* const this,
    void* const buffer,
    size_t buffer_size
);

int ADDRESS_INFO_METHOD(receive)(
    struct ADDRESS_INFO_TYPE() const* const this,
    void* const buffer,
    size_t buffer_size
);

void* ADDRESS_INFO_METHOD(destroy_at)(struct ADDRESS_INFO_TYPE()* const this);

// Address info iterator
#define ADDRESS_INFO_ITERATOR_TYPE() NAMESPACE_NETWORK_ADDRESS_INFO(address_info_iterator)
typedef struct ADDRESS_INFO_ITERATOR_TYPE() {
    ADDRESS_INFO_TYPE() address_info;
} ADDRESS_INFO_ITERATOR_TYPE();

// Address info's iterators-related methods
struct ADDRESS_INFO_ITERATOR_TYPE() ADDRESS_INFO_METHOD(begin)(struct ADDRESS_INFO_TYPE()* const this);
struct ADDRESS_INFO_ITERATOR_TYPE() ADDRESS_INFO_METHOD(end)(struct ADDRESS_INFO_TYPE()* const this);

#define ADDRESS_INFO_ITERATOR_METHOD(METHOD) TYPE_METHOD(ADDRESS_INFO_ITERATOR_TYPE(), METHOD)

struct ADDRESS_INFO_ITERATOR_TYPE()* ADDRESS_INFO_ITERATOR_METHOD(construct_at)(struct ADDRESS_INFO_ITERATOR_TYPE()* const this, struct ADDRESS_INFO_TYPE()* const container);
struct ADDRESS_INFO_TYPE()* ADDRESS_INFO_ITERATOR_METHOD(value)(struct ADDRESS_INFO_ITERATOR_TYPE()* const this);
// point this to next value & return this-value
struct ADDRESS_INFO_ITERATOR_TYPE() ADDRESS_INFO_ITERATOR_METHOD(next)(struct ADDRESS_INFO_ITERATOR_TYPE()* const this);
// return this-value & point this to next value
struct ADDRESS_INFO_ITERATOR_TYPE() ADDRESS_INFO_ITERATOR_METHOD(pnext)(struct ADDRESS_INFO_ITERATOR_TYPE()* const this);
// return 0 if equals, !0 either
int ADDRESS_INFO_ITERATOR_METHOD(compare)(struct ADDRESS_INFO_ITERATOR_TYPE() const* const iterator_1, struct ADDRESS_INFO_ITERATOR_TYPE() const* const iterator_2);
void* ADDRESS_INFO_ITERATOR_METHOD(destroy_at)(struct ADDRESS_INFO_ITERATOR_TYPE()* const this);

// Address info const iterator
#define ADDRESS_INFO_CONST_ITERATOR_TYPE() NAMESPACE_NETWORK_ADDRESS_INFO(address_info_const_iterator)
typedef struct ADDRESS_INFO_CONST_ITERATOR_TYPE() {
    ADDRESS_INFO_TYPE()/* const*/ address_info;
} ADDRESS_INFO_CONST_ITERATOR_TYPE();

// Address info's const iterators-related methods
struct ADDRESS_INFO_CONST_ITERATOR_TYPE() ADDRESS_INFO_METHOD(cbegin)(struct ADDRESS_INFO_TYPE() const* const this);
struct ADDRESS_INFO_CONST_ITERATOR_TYPE() ADDRESS_INFO_METHOD(cend)(struct ADDRESS_INFO_TYPE() const* const this);

#define ADDRESS_INFO_CONST_ITERATOR_METHOD(METHOD) TYPE_METHOD(ADDRESS_INFO_CONST_ITERATOR_TYPE(), METHOD)

struct ADDRESS_INFO_CONST_ITERATOR_TYPE()* ADDRESS_INFO_CONST_ITERATOR_METHOD(construct_at)(struct ADDRESS_INFO_CONST_ITERATOR_TYPE()* const this, struct ADDRESS_INFO_TYPE() const* const container);
struct ADDRESS_INFO_TYPE() const* ADDRESS_INFO_CONST_ITERATOR_METHOD(value)(struct ADDRESS_INFO_CONST_ITERATOR_TYPE() const* const this);
// point this to next value & return this-value
struct ADDRESS_INFO_CONST_ITERATOR_TYPE() ADDRESS_INFO_CONST_ITERATOR_METHOD(next)(struct ADDRESS_INFO_CONST_ITERATOR_TYPE()* const this);
// return this-value & point this to next value
struct ADDRESS_INFO_CONST_ITERATOR_TYPE() ADDRESS_INFO_CONST_ITERATOR_METHOD(pnext)(struct ADDRESS_INFO_CONST_ITERATOR_TYPE()* const this);
// return 0 if equals, !0 either
int ADDRESS_INFO_CONST_ITERATOR_METHOD(compare)(struct ADDRESS_INFO_CONST_ITERATOR_TYPE() const* const iterator_1, struct ADDRESS_INFO_CONST_ITERATOR_TYPE() const* const iterator_2);
void* ADDRESS_INFO_CONST_ITERATOR_METHOD(destroy_at)(struct ADDRESS_INFO_CONST_ITERATOR_TYPE()* const this);

// Socket address info
#define SOCKET_ADDRESS_INFO_DESCRIPTOR_TYPE() NAMESPACE_NETWORK_ADDRESS_INFO(socket_address_info)
typedef struct SOCKET_ADDRESS_INFO_DESCRIPTOR_TYPE() {
    struct sockaddr* native_socket_address_info;
    SOCKET_DOMAIN_ENUM() socket_domain;
} SOCKET_ADDRESS_INFO_DESCRIPTOR_TYPE();

#define SOCKET_ADDRESS_INFO_DESCRIPTOR_METHOD(METHOD) TYPE_METHOD(SOCKET_ADDRESS_INFO_DESCRIPTOR_TYPE(), METHOD)

struct SOCKET_ADDRESS_INFO_DESCRIPTOR_TYPE()* SOCKET_ADDRESS_INFO_DESCRIPTOR_METHOD(construct_at)(struct SOCKET_ADDRESS_INFO_DESCRIPTOR_TYPE()* const this,
    struct ADDRESS_INFO_TYPE() const* const address_info 
);

STRING_TYPE() SOCKET_ADDRESS_INFO_DESCRIPTOR_METHOD(get_ip_address)(struct SOCKET_ADDRESS_INFO_DESCRIPTOR_TYPE() const* const this);

void* SOCKET_ADDRESS_INFO_DESCRIPTOR_METHOD(destroy_at)(struct SOCKET_ADDRESS_INFO_DESCRIPTOR_TYPE()* const this);

