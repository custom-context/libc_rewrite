#include "address_info.h"

#include <network/native/native.h>

#if defined(WIN32)
    #include <WS2tcpip.h>
#else
    #include <sys/types.h>
    #include <netdb.h>
    #include <arpa/inet.h>
#endif

// "standard" memset used - it's defined in libc's string.h, but without knowledge of current architecture
// it's hard to correctly implement it
#include <string.h>

struct ADDRESS_INFO_TYPE()* ADDRESS_INFO_METHOD(construct_at)(struct ADDRESS_INFO_TYPE()* const this) {
    this->native_address_info = NULL;
    return this;
}

struct ADDRESS_INFO_TYPE()* ADDRESS_INFO_METHOD(construct_with_fetch_at)(struct ADDRESS_INFO_TYPE()* const this,
    char const* const restrict host,
    char const* const restrict service,
    struct ADDRESS_INFO_CRITERIAS_TYPE() const* const address_info_criterias
) {
    if (!address_info_criterias) {
        getaddrinfo(host, service, NULL, &this->native_address_info);
        return this;
    }

    struct addrinfo native_address_info_criterias;
    memset(&native_address_info_criterias, 0, sizeof(native_address_info_criterias));

    native_address_info_criterias.ai_family = NAMESPACE_NETWORK_NATIVE(get_native_domain)(address_info_criterias->socket_domain);
    native_address_info_criterias.ai_socktype = NAMESPACE_NETWORK_NATIVE(get_native_socket_type)(address_info_criterias->socket_type);
    native_address_info_criterias.ai_protocol = address_info_criterias->socket_protocol.native_protocol;
    native_address_info_criterias.ai_flags = address_info_criterias->native_extra_flags;

    getaddrinfo(host, service, &native_address_info_criterias, &this->native_address_info);

    return this;
}

SOCKET_DOMAIN_ENUM() ADDRESS_INFO_METHOD(get_socket_domain)(struct ADDRESS_INFO_TYPE() const* const this) {
    return NAMESPACE_NETWORK_NATIVE(get_wrapped_domain)(this->native_address_info->ai_family);
}

SOCKET_TYPE_ENUM() ADDRESS_INFO_METHOD(get_socket_type)(struct ADDRESS_INFO_TYPE() const* const this) {
    return NAMESPACE_NETWORK_NATIVE(get_wrapped_socket_type)(this->native_address_info->ai_socktype);
}

SOCKET_PROTOCOL_TYPE() ADDRESS_INFO_METHOD(get_socket_protocol)(struct ADDRESS_INFO_TYPE() const* const this) {
    return (SOCKET_PROTOCOL_TYPE()){this->native_address_info->ai_protocol};
}

int ADDRESS_INFO_METHOD(send)(
    struct ADDRESS_INFO_TYPE() const* const this,
    void const* const buffer,
    size_t buffer_size
) {
    SOCKET_TYPE() socket;

    ADDRESS_INFO_CONST_ITERATOR_TYPE()
        iterator = ADDRESS_INFO_METHOD(cbegin)(this),
        end_iterator = ADDRESS_INFO_METHOD(cend)(this);

    for (; ADDRESS_INFO_CONST_ITERATOR_METHOD(compare)(&iterator, &end_iterator); ADDRESS_INFO_CONST_ITERATOR_METHOD(next)(&iterator)) {
        ADDRESS_INFO_TYPE() const* const current_address_info = ADDRESS_INFO_CONST_ITERATOR_METHOD(value)(&iterator);

        SOCKET_PROTOCOL_TYPE() protocol = ADDRESS_INFO_METHOD(get_socket_protocol)(current_address_info);

        SOCKET_METHOD(construct_at)(&socket,
            ADDRESS_INFO_METHOD(get_socket_domain)(current_address_info),
            ADDRESS_INFO_METHOD(get_socket_type)(current_address_info),
            &protocol
        );
        if (!SOCKET_METHOD(is_valid)(&socket)) {
            continue;
        }

        break;
    }

    // if no connection setup
    if (!ADDRESS_INFO_CONST_ITERATOR_METHOD(compare)(&iterator, &end_iterator)) {
        return 0u;
    }

    int return_value = sendto(socket.native_socket, buffer, (int)buffer_size, 0, 
        this->native_address_info->ai_addr,
        (int)(this->native_address_info->ai_addrlen)
    );

    SOCKET_METHOD(destroy_at)(&socket);

    return return_value;
}

int ADDRESS_INFO_METHOD(receive)(
    struct ADDRESS_INFO_TYPE() const* const this,
    void* const buffer,
    size_t buffer_size
) {
    SOCKET_TYPE() socket;

    ADDRESS_INFO_CONST_ITERATOR_TYPE()
        iterator = ADDRESS_INFO_METHOD(cbegin)(this),
        end_iterator = ADDRESS_INFO_METHOD(cend)(this);

    for (; ADDRESS_INFO_CONST_ITERATOR_METHOD(compare)(&iterator, &end_iterator); ADDRESS_INFO_CONST_ITERATOR_METHOD(next)(&iterator)) {
        ADDRESS_INFO_TYPE() const* const current_address_info = ADDRESS_INFO_CONST_ITERATOR_METHOD(value)(&iterator);

        SOCKET_PROTOCOL_TYPE() protocol = ADDRESS_INFO_METHOD(get_socket_protocol)(current_address_info);

        SOCKET_METHOD(construct_at)(&socket,
            ADDRESS_INFO_METHOD(get_socket_domain)(current_address_info),
            ADDRESS_INFO_METHOD(get_socket_type)(current_address_info),
            &protocol
        );
        if (!SOCKET_METHOD(is_valid)(&socket)) {
            continue;
        }

        break;
    }

    // if no connection setup
    if (!ADDRESS_INFO_CONST_ITERATOR_METHOD(compare)(&iterator, &end_iterator)) {
        SOCKET_METHOD(construct_with_invalidation_at)(&socket);
        return 0u;
    }

#if defined(WIN32)
    int native_sender_address_length = (int)(this->native_address_info->ai_addrlen);
#else
    socklen_t native_sender_address_length = this->native_address_info->ai_addrlen;
#endif
    int return_value = recvfrom(socket.native_socket, buffer, (int)buffer_size, 0, 
        this->native_address_info->ai_addr,
        &native_sender_address_length
    );

    SOCKET_METHOD(destroy_at)(&socket);

    return return_value;
}

void* ADDRESS_INFO_METHOD(destroy_at)(struct ADDRESS_INFO_TYPE()* const this) {
    if (!this->native_address_info) {
        return this;
    }

    freeaddrinfo(this->native_address_info);

    return this;
}

// Address info iterator
// Address info's iterators-related methods
struct ADDRESS_INFO_ITERATOR_TYPE() ADDRESS_INFO_METHOD(begin)(struct ADDRESS_INFO_TYPE()* const this) {
    struct ADDRESS_INFO_ITERATOR_TYPE() result;
    ADDRESS_INFO_ITERATOR_METHOD(construct_at)(&result, this);
    return result;
}

struct ADDRESS_INFO_ITERATOR_TYPE() ADDRESS_INFO_METHOD(end)(struct ADDRESS_INFO_TYPE()* const this) {
    UNUSED(this);
    struct ADDRESS_INFO_ITERATOR_TYPE() result;
    ADDRESS_INFO_ITERATOR_METHOD(construct_at)(&result, &(struct ADDRESS_INFO_TYPE()){NULL});
    return result;
}

struct ADDRESS_INFO_ITERATOR_TYPE()* ADDRESS_INFO_ITERATOR_METHOD(construct_at)(struct ADDRESS_INFO_ITERATOR_TYPE()* const this,
    struct ADDRESS_INFO_TYPE()* const container) {
    this->address_info = *container;
    return this;
}

struct ADDRESS_INFO_TYPE()* ADDRESS_INFO_ITERATOR_METHOD(value)(struct ADDRESS_INFO_ITERATOR_TYPE()* const this) {
    return &this->address_info;
}

// point this to next value & return this-value
struct ADDRESS_INFO_ITERATOR_TYPE() ADDRESS_INFO_ITERATOR_METHOD(next)(struct ADDRESS_INFO_ITERATOR_TYPE()* const this) {
    if (this->address_info.native_address_info) {
        this->address_info.native_address_info = this->address_info.native_address_info->ai_next;
    }

    return *this;
}

// return this-value & point this to next value
struct ADDRESS_INFO_ITERATOR_TYPE() ADDRESS_INFO_ITERATOR_METHOD(pnext)(struct ADDRESS_INFO_ITERATOR_TYPE()* const this) {
    struct ADDRESS_INFO_ITERATOR_TYPE() result = *this;

    if (this->address_info.native_address_info) {
        this->address_info.native_address_info = this->address_info.native_address_info->ai_next;
    }

    return result;
}

// return 0 if equals, !0 either
int ADDRESS_INFO_ITERATOR_METHOD(compare)(struct ADDRESS_INFO_ITERATOR_TYPE() const* const iterator_1, struct ADDRESS_INFO_ITERATOR_TYPE() const* const iterator_2) {
    return !(iterator_1->address_info.native_address_info == iterator_2->address_info.native_address_info);
}

void* ADDRESS_INFO_ITERATOR_METHOD(destroy_at)(struct ADDRESS_INFO_ITERATOR_TYPE()* const this) {
    return this;
}

// Address info const iterator
// Address info's const iterators-related methods
struct ADDRESS_INFO_CONST_ITERATOR_TYPE() ADDRESS_INFO_METHOD(cbegin)(struct ADDRESS_INFO_TYPE() const* const this) {
    struct ADDRESS_INFO_CONST_ITERATOR_TYPE() result;
    ADDRESS_INFO_CONST_ITERATOR_METHOD(construct_at)(&result, this);
    return result;
}

struct ADDRESS_INFO_CONST_ITERATOR_TYPE() ADDRESS_INFO_METHOD(cend)(struct ADDRESS_INFO_TYPE() const* const this) {
    UNUSED(this);
    struct ADDRESS_INFO_CONST_ITERATOR_TYPE() result;
    ADDRESS_INFO_CONST_ITERATOR_METHOD(construct_at)(&result, &(struct ADDRESS_INFO_TYPE()){NULL});
    return result;
}

struct ADDRESS_INFO_CONST_ITERATOR_TYPE()* ADDRESS_INFO_CONST_ITERATOR_METHOD(construct_at)(struct ADDRESS_INFO_CONST_ITERATOR_TYPE()* const this, struct ADDRESS_INFO_TYPE() const* const container) {
    this->address_info = *container;
    return this;
}

struct ADDRESS_INFO_TYPE() const* ADDRESS_INFO_CONST_ITERATOR_METHOD(value)(struct ADDRESS_INFO_CONST_ITERATOR_TYPE() const* const this) {
    return &this->address_info;
}

// point this to next value & return this-value
struct ADDRESS_INFO_CONST_ITERATOR_TYPE() ADDRESS_INFO_CONST_ITERATOR_METHOD(next)(struct ADDRESS_INFO_CONST_ITERATOR_TYPE()* const this) {
    if (this->address_info.native_address_info) {
        this->address_info.native_address_info = this->address_info.native_address_info->ai_next;
    }

    return *this;
}

// return this-value & point this to next value
struct ADDRESS_INFO_CONST_ITERATOR_TYPE() ADDRESS_INFO_CONST_ITERATOR_METHOD(pnext)(struct ADDRESS_INFO_CONST_ITERATOR_TYPE()* const this) {
    struct ADDRESS_INFO_CONST_ITERATOR_TYPE() result = *this;

    if (this->address_info.native_address_info) {
        this->address_info.native_address_info = this->address_info.native_address_info->ai_next;
    }

    return result;
}

// return 0 if equals, !0 either
int ADDRESS_INFO_CONST_ITERATOR_METHOD(compare)(struct ADDRESS_INFO_CONST_ITERATOR_TYPE() const* const iterator_1, struct ADDRESS_INFO_CONST_ITERATOR_TYPE() const* const iterator_2) {
    return !(iterator_1->address_info.native_address_info == iterator_2->address_info.native_address_info);
}

void* ADDRESS_INFO_CONST_ITERATOR_METHOD(destroy_at)(struct ADDRESS_INFO_CONST_ITERATOR_TYPE()* const this) {
    return this;
}

// Socket address info
struct SOCKET_ADDRESS_INFO_DESCRIPTOR_TYPE()* SOCKET_ADDRESS_INFO_DESCRIPTOR_METHOD(construct_at)(struct SOCKET_ADDRESS_INFO_DESCRIPTOR_TYPE()* const this,
    struct ADDRESS_INFO_TYPE() const* const address_info 
) {
    this->socket_domain = NAMESPACE_NETWORK_NATIVE(get_wrapped_domain)(address_info->native_address_info->ai_family);
    this->native_socket_address_info = address_info->native_address_info->ai_addr;
    return this;
}

#if defined(WIN32)
    #pragma warning(push)
    #pragma warning(disable: 4101)
#endif
STRING_TYPE() SOCKET_ADDRESS_INFO_DESCRIPTOR_METHOD(get_ip_address)(struct SOCKET_ADDRESS_INFO_DESCRIPTOR_TYPE() const* const this) {
    ASSERT(this->socket_domain == SOCKET_DOMAIN_ENUM_VALUE(IPv4) || this->socket_domain == SOCKET_DOMAIN_ENUM_VALUE(IPv6));

    STRING_TYPE() result;

    void const* variadic_address;
    if (this->socket_domain == SOCKET_DOMAIN_ENUM_VALUE(IPv4)) {
        struct sockaddr_in const* socket_address = (struct sockaddr_in const*)(void*)(this->native_socket_address_info);
        variadic_address = &(socket_address->sin_addr);
    } else if (this->socket_domain == SOCKET_DOMAIN_ENUM_VALUE(IPv6)) {
        struct sockaddr_in6 const* socket_address = (struct sockaddr_in6 const*)(void*)(this->native_socket_address_info);
        variadic_address = &(socket_address->sin6_addr);
    } else { // if assertion turned off
        STRING_METHOD(construct_at)(&result);
        return result;
    }

    char ip_string_buffer[INET6_ADDRSTRLEN];
    inet_ntop(NAMESPACE_NETWORK_NATIVE(get_native_domain)(this->socket_domain), variadic_address, ip_string_buffer, sizeof(ip_string_buffer));

    STRING_METHOD(construct_from_c_string_at)(&result, ip_string_buffer);

    return result;
}
#if defined(WIN32)
    #pragma warning(pop)
#endif

void* SOCKET_ADDRESS_INFO_DESCRIPTOR_METHOD(destroy_at)(struct SOCKET_ADDRESS_INFO_DESCRIPTOR_TYPE()* const this) {
    return this;
}

