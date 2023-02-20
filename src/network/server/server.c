#include "server.h"

DEFINE_RESULT_TYPE_STATIC_METHODS(int, int);

// connection's private method that opened for server class only 
static struct CONNECTION_TYPE()* CONNECTION_METHOD(construct_move_from_socket_at)(struct CONNECTION_TYPE()* const this, struct SOCKET_TYPE()* const socket) {
    SOCKET_METHOD(construct_move_at)(&this->socket, socket);
    return this;
}

// socket's private method that opened for server class only
static struct SOCKET_TYPE()* SOCKET_METHOD(construct_on_acceptance_at)(struct SOCKET_TYPE()* const this, struct SERVER_TYPE() const* const server) {
    int native_address_length = server->address_info.native_address_info->ai_addrlen;
    this->native_socket = accept(server->socket.native_socket,
        server->address_info.native_address_info->ai_addr,
        &native_address_length);

    return this;
}

// server' methods
struct SERVER_TYPE()* SERVER_METHOD(construct_at)(struct SERVER_TYPE()* const this) {
    ADDRESS_INFO_METHOD(construct_at)(&this->address_info);
    SOCKET_METHOD(construct_with_invalidation_at)(&this->socket);
    return this;
}

struct SERVER_TYPE()* SERVER_METHOD(bind)(struct SERVER_TYPE()* const this,
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

    return SERVER_METHOD(rebind)(this);
}

struct SERVER_TYPE()* SERVER_METHOD(rebind)(struct SERVER_TYPE()* const this) {
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

        // allows sockets to be reused for cases, when server could shutdown and be restarted with try to accept packages from same connection
        if (setsockopt(this->socket.native_socket,
            SOL_SOCKET,
            SO_REUSEADDR,
            &(char){'1'}, sizeof(char)
        ) == -1) {
            SOCKET_METHOD(destroy_at)(&this->socket);
            continue;
        }

        // TODO: add return value check for errors
        if (bind(this->socket.native_socket,
            current_address_info->native_address_info->ai_addr,
            current_address_info->native_address_info->ai_addrlen
        ) == -1) {
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

int SERVER_METHOD(is_binded)(struct SERVER_TYPE()* const this) {
    return SOCKET_METHOD(is_valid)(&this->socket);
}

struct RESULT_TYPE(int, int) SERVER_METHOD(status)(struct SERVER_TYPE() const* const this) {
    struct RESULT_TYPE(int, int) result;

    int error_code = 0;
    int error_code_size = sizeof(error_code);
    if (getsockopt(this->socket.native_socket,
        SOL_SOCKET,
        SO_ERROR,
        (void*)(&error_code),
        &error_code_size) == -1) {
#if defined(WIN32)
        error_code = WSAGetLastError();
#else
        error_code = errno;
#endif
        RESULT_METHOD(int, int, construct_move_from_error_at)(&result, &error_code);
        return result;
    }
    RESULT_METHOD(int, int, construct_move_from_value_at)(&result, &error_code);
    return result;
}

int SERVER_METHOD(listen)(struct SERVER_TYPE()* const this, size_t system_connections_queue_capacity) {
    ASSERT(SERVER_METHOD(is_binded)(this));

    return listen(this->socket.native_socket, (int)(system_connections_queue_capacity));
}

struct CONNECTION_TYPE() SERVER_METHOD(accept)(struct SERVER_TYPE()* const this) {
    struct SOCKET_TYPE() socket;
    SOCKET_METHOD(construct_on_acceptance_at)(&socket, this);
    
    struct CONNECTION_TYPE() connection;
    CONNECTION_METHOD(construct_move_from_socket_at)(&connection, &socket);

    SOCKET_METHOD(destroy_at)(&socket);

    return connection;
}

struct SERVER_TYPE()* SERVER_METHOD(shutdown)(struct SERVER_TYPE()* const this) {
    SOCKET_METHOD(destroy_at)(&this->socket);
    SOCKET_METHOD(construct_with_invalidation_at)(&this->socket);

    return this;
}

void* SERVER_METHOD(destroy_at)(struct SERVER_TYPE()* const this) {
    SOCKET_METHOD(destroy_at)(&this->socket);
    ADDRESS_INFO_METHOD(destroy_at)(&this->address_info);

    return this;
}

