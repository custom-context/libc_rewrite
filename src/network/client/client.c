#include "client_inheritance.h"
#include "client.h"

#include <network/native/native.h>

#if !defined(WIN32)
    #include <errno.h>
    #include <netdb.h>
#endif

DEFINE_RESULT_TYPE_STATIC_METHODS(int, int)

static struct INTERFACE_VTABLE_TYPE(CLIENT_TYPE()) TYPE_MEMBER(CLIENT_TYPE(), INTERFACE_VTABLE_VARIABLE(CLIENT_TYPE())) = {
    .destroy_at = CLIENT_METHOD(VTABLE_MEMBER(destroy_at)),
    .on_success_connection = CLIENT_METHOD(VTABLE_MEMBER(on_success_connection))
};

struct CLIENT_TYPE()* CLIENT_METHOD(construct_at)(struct CLIENT_TYPE()* const this) {
    // boilerplate
    this->INTERFACE_VTABLE_VARIABLE(CLIENT_TYPE()) = &TYPE_MEMBER(CLIENT_TYPE(), INTERFACE_VTABLE_VARIABLE(CLIENT_TYPE()));
    ADDRESS_INFO_METHOD(construct_at)(&this->address_info);
    SOCKET_METHOD(construct_with_invalidation_at)(&this->socket);
    // body
    // ...
    // boilerplate
    return this;
}

int CLIENT_METHOD(is_connection_established)(struct CLIENT_TYPE() const* const this) {
    return SOCKET_METHOD(is_valid)(&this->socket);
}

struct RESULT_TYPE(int, int) CLIENT_METHOD(status)(struct CLIENT_TYPE() const* const this) {
    struct RESULT_TYPE(int, int) result;

    int error_code = 0;
#if defined (WIN32)
    int error_code_size;
#else
    socklen_t error_code_size;
#endif
    error_code_size = sizeof(error_code);
    if (getsockopt(this->socket.native_socket,
        SOL_SOCKET,
        SO_ERROR,
        (void*)(&error_code),
        &error_code_size) == -1) {
        error_code = NAMESPACE_NETWORK(get_last_error)();
        RESULT_METHOD(int, int, construct_move_from_error_at)(&result, &error_code);
        return result;
    }
    RESULT_METHOD(int, int, construct_move_from_value_at)(&result, &error_code);
    return result;
}

struct CLIENT_TYPE()* CLIENT_METHOD(connect)(struct CLIENT_TYPE()* const this,
    char const* const restrict host,
    char const* const restrict service,
    struct ADDRESS_INFO_CRITERIAS_TYPE() const* const address_info_criterias
) {
    ADDRESS_INFO_METHOD(destroy_at)(&this->address_info);

    ADDRESS_INFO_METHOD(construct_with_fetch_at)(&this->address_info,
        host,
        service,
        address_info_criterias
    );

    return CLIENT_METHOD(reconnect)(this);
}

struct CLIENT_TYPE()* CLIENT_METHOD(shutdown)(struct CLIENT_TYPE()* const this) {
    SOCKET_METHOD(destroy_at)(&this->socket);
    SOCKET_METHOD(construct_with_invalidation_at)(&this->socket);

    return this;
}

struct CLIENT_TYPE()* CLIENT_METHOD(reconnect)(struct CLIENT_TYPE()* const this) {
    SOCKET_METHOD(destroy_at)(&this->socket);

    ADDRESS_INFO_CONST_ITERATOR_TYPE()
        iterator = ADDRESS_INFO_METHOD(cbegin)(&this->address_info),
        end_iterator = ADDRESS_INFO_METHOD(cend)(&this->address_info);

    for (; ADDRESS_INFO_CONST_ITERATOR_METHOD(compare)(&iterator, &end_iterator); ADDRESS_INFO_CONST_ITERATOR_METHOD(next)(&iterator)) {
        struct ADDRESS_INFO_TYPE() const* const current_address_info = ADDRESS_INFO_CONST_ITERATOR_METHOD(value)(&iterator);

        SOCKET_PROTOCOL_TYPE() protocol = ADDRESS_INFO_METHOD(get_socket_protocol)(current_address_info);

        SOCKET_METHOD(construct_at)(&this->socket,
            ADDRESS_INFO_METHOD(get_socket_domain)(current_address_info),
            ADDRESS_INFO_METHOD(get_socket_type)(current_address_info),
            &protocol
        );
        if (!SOCKET_METHOD(is_valid)(&this->socket)) {
            continue;
        }

        // TODO: add return value check for errors
        if (connect(this->socket.native_socket,
            current_address_info->native_address_info->ai_addr,
            (int)(current_address_info->native_address_info->ai_addrlen)
        ) == -1) {
            SOCKET_METHOD(destroy_at)(&this->socket);
            continue;
        }

        // TODO: add return value check for errors
        if (CLIENT_METHOD(on_success_connection)(this) == -1) {
            SOCKET_METHOD(destroy_at)(&this->socket);
            continue;
        }

        break;
    }

    // if no connection setted up
    if (!ADDRESS_INFO_CONST_ITERATOR_METHOD(compare)(&iterator, &end_iterator)) {
        SOCKET_METHOD(construct_with_invalidation_at)(&this->socket);
        ADDRESS_INFO_METHOD(destroy_at)(&this->address_info);
        return this;
    }

    return this;
}

int CLIENT_METHOD(send)(struct CLIENT_TYPE() const* const this,
    void const* const buffer,
    usize buffer_size
) {
    ASSERT(CLIENT_METHOD(is_connection_established)(this));

    return send(this->socket.native_socket, buffer, (int)buffer_size, 0);
}

int CLIENT_METHOD(receive)(struct CLIENT_TYPE() const* const this,
    void* const buffer,
    usize buffer_size
) {
    ASSERT(CLIENT_METHOD(is_connection_established)(this));

    return recv(this->socket.native_socket, buffer, (int)buffer_size, 0);
}
