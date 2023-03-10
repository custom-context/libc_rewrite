#pragma once

#include <network/server/server.h>
#include <network/nb_server/nb_connection/nb_connection.h>
#include <network/common.h>

#ifndef NAMESPACE_NETWORK_NB_SERVER
    #define NAMESPACE_NETWORK_NB_SERVER(NAME) NAMESPACE_NETWORK(CONCAT5(non_blocking, _, server, __, NAME))
#endif

#define NB_SERVER_TYPE() NAMESPACE_NETWORK_NB_SERVER(nb_server)

typedef struct NB_SERVER_TYPE() {
    struct SERVER_TYPE() base_server;
} NB_SERVER_TYPE();

#define NB_SERVER_METHOD(METHOD) TYPE_METHOD(NB_SERVER_TYPE(), METHOD)

struct NB_SERVER_TYPE()* NB_SERVER_METHOD(construct_at)(struct NB_SERVER_TYPE()* const this);

struct NB_SERVER_TYPE()* NB_SERVER_METHOD(bind)(struct NB_SERVER_TYPE()* const this,
    char const* const restrict host,
    char const* const restrict service,
    struct ADDRESS_INFO_CRITERIAS_TYPE() const* const address_info_criterias
);

struct NB_SERVER_TYPE()* NB_SERVER_METHOD(rebind)(struct NB_SERVER_TYPE()* const this);

int NB_SERVER_METHOD(is_binded)(struct NB_SERVER_TYPE()* const this);

struct RESULT_TYPE(int, int) NB_SERVER_METHOD(status)(struct NB_SERVER_TYPE() const* const this);

int NB_SERVER_METHOD(listen)(struct NB_SERVER_TYPE()* const this, size_t system_connections_queue_capacity);

struct CONNECTION_TYPE() NB_SERVER_METHOD(accept)(struct NB_SERVER_TYPE()* const this);

struct NB_SERVER_TYPE()* NB_SERVER_METHOD(shutdown)(struct NB_SERVER_TYPE()* const this);

// dynamic methods
inline static int NB_SERVER_METHOD(on_success_bind)(struct NB_SERVER_TYPE() const* const this) {
    return this->base_server.INTERFACE_VTABLE_VARIABLE(SERVER_TYPE())->on_success_bind(&this->base_server);
}
inline static void* NB_SERVER_METHOD(destroy_at)(struct NB_SERVER_TYPE()* const this) {
    return this->base_server.INTERFACE_VTABLE_VARIABLE(SERVER_TYPE())->destroy_at(&this->base_server);
}
