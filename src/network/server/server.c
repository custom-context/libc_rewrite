#include "server.h"
#include "server_inheritance.h"

#if !defined(WIN32)
    #include <errno.h>
    #include <netdb.h>
#endif

DEFINE_RESULT_STATIC_METHODS(int, int)

// connection's private method that opened for server class only 
static struct CONNECTION_TYPE()* CONNECTION_METHOD(construct_move_from_socket_at)(struct CONNECTION_TYPE()* const this, struct SOCKET_TYPE()* const socket) {
    SOCKET_METHOD(construct_move_at)(&this->socket, socket);
    return this;
}

// socket's private method that opened for server class only
static struct SOCKET_TYPE()* SOCKET_METHOD(construct_on_acceptance_at)(struct SOCKET_TYPE()* const this, struct SERVER_TYPE() const* const server) {
#if defined(WIN32)
    int native_address_length = (int)(server->address_info.native_address_info->ai_addrlen);
#else
    socklen_t native_address_length = server->address_info.native_address_info->ai_addrlen;
#endif
    this->native_socket = accept(server->socket.native_socket,
        server->address_info.native_address_info->ai_addr,
        &native_address_length);

    return this;
}

// server' methods
static struct INTERFACE_VTABLE_TYPE(SERVER_TYPE()) TYPE_MEMBER(SERVER_TYPE(), INTERFACE_VTABLE_VARIABLE(SERVER_TYPE())) = {
    .destroy_at = SERVER_METHOD(VTABLE_MEMBER(destroy_at)),
    .on_success_bind = SERVER_METHOD(VTABLE_MEMBER(on_success_bind))
};

struct SERVER_TYPE()* SERVER_METHOD(construct_at)(struct SERVER_TYPE()* const this) {
    // boilerplate
    this->INTERFACE_VTABLE_VARIABLE(SERVER_TYPE()) = &TYPE_MEMBER(SERVER_TYPE(), INTERFACE_VTABLE_VARIABLE(SERVER_TYPE()));
    ADDRESS_INFO_METHOD(construct_at)(&this->address_info);
    SOCKET_METHOD(construct_with_invalidation_at)(&this->socket);
    // body
    // ...
    // boilerplate
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
#if defined(WIN32)
            &(char){'1'}, sizeof(char)
#else
            &(int){1}, sizeof(int)
#endif
        ) == -1) {
            {
                struct RESULT_TYPE(int, int) status = SERVER_METHOD(status)(this);
                if (RESULT_METHOD(int, int, has_value)(&status)) {
                    LOG_DEBUG_FORMAT("setsockopt status on success: %d\n", errno);
                } else {
                    LOG_DEBUG_FORMAT("setsockopt status on error: %d\n", *RESULT_METHOD(int, int, error)(&status));
                }
                RESULT_METHOD(int, int, destroy_at)(&status);
            }
            SOCKET_METHOD(destroy_at)(&this->socket);
            continue;
        }

        // TODO: add return value check for errors
        if (bind(this->socket.native_socket,
            current_address_info->native_address_info->ai_addr,
            (int)(current_address_info->native_address_info->ai_addrlen)
        ) == -1) {
            /*debug check for error status*/{
                struct RESULT_TYPE(int, int) status = SERVER_METHOD(status)(this);
                if (RESULT_METHOD(int, int, has_value)(&status)) {
                    LOG_DEBUG_FORMAT("bind status on success: %d\n", errno);
                } else {
                    LOG_DEBUG_FORMAT("bind status on error: %d\n", *RESULT_METHOD(int, int, error)(&status));
                }
                RESULT_METHOD(int, int, destroy_at)(&status);
            }
            SOCKET_METHOD(destroy_at)(&this->socket);
            continue;
        }

        if (SERVER_METHOD(on_success_bind)(this) == -1) {
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

int SERVER_METHOD(listen)(struct SERVER_TYPE()* const this, usize system_connections_queue_capacity) {
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
