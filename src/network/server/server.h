#pragma once

#include <network/socket/socket.h>
#include <network/address_info/address_info.h>
#include <network/server/connection/connection.h>
#include <network/common.h>

#ifndef NAMESPACE_NETWORK_SERVER
    #define NAMESPACE_NETWORK_SERVER(NAME) NAMESPACE_NETWORK(CONCAT3(server, __, NAME))
#endif

#define SERVER_TYPE() NAMESPACE_NETWORK_SERVER(server)

struct SERVER_TYPE();

struct INTERFACE_VTABLE_TYPE(SERVER_TYPE()) {
    int (*on_success_bind)(struct SERVER_TYPE() const* const this);
    void* (*destroy_at)(struct SERVER_TYPE()* const this);
};

typedef struct SERVER_TYPE() {
    DEFINE_INTERFACE_VTABLE_ADAPTER(SERVER_TYPE());
    struct SOCKET_TYPE() socket;
    struct ADDRESS_INFO_TYPE() address_info;
} SERVER_TYPE();

#define SERVER_METHOD(METHOD) TYPE_METHOD(SERVER_TYPE(), METHOD)

struct SERVER_TYPE()* SERVER_METHOD(construct_at)(struct SERVER_TYPE()* const this);

struct SERVER_TYPE()* SERVER_METHOD(bind)(struct SERVER_TYPE()* const this,
    char const* const restrict host,
    char const* const restrict service,
    struct ADDRESS_INFO_CRITERIAS_TYPE() const* const address_info_criterias
);

struct SERVER_TYPE()* SERVER_METHOD(rebind)(struct SERVER_TYPE()* const this);

int SERVER_METHOD(is_binded)(struct SERVER_TYPE()* const this);

struct RESULT_TYPE(int, int) SERVER_METHOD(status)(struct SERVER_TYPE() const* const this);

int SERVER_METHOD(listen)(struct SERVER_TYPE()* const this, usize system_connections_queue_capacity);

struct CONNECTION_TYPE() SERVER_METHOD(accept)(struct SERVER_TYPE()* const this);

struct SERVER_TYPE()* SERVER_METHOD(shutdown)(struct SERVER_TYPE()* const this);

// dynamic methods
inline static int SERVER_METHOD(on_success_bind)(struct SERVER_TYPE() const* const this) {
    return this->INTERFACE_VTABLE_VARIABLE(SERVER_TYPE())->on_success_bind(this);
}
inline static void* SERVER_METHOD(destroy_at)(struct SERVER_TYPE()* const this) {
    return this->INTERFACE_VTABLE_VARIABLE(SERVER_TYPE())->destroy_at(this);
}
