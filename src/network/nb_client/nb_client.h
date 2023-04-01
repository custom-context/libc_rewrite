#pragma once

#include <network/client/client.h>

#define NAMESPACE_NETWORK_NB_CLIENT(NAME) NAMESPACE_NETWORK(CONCAT5(non_blocking, _, client, __, NAME))

#define NB_CLIENT_TYPE() NAMESPACE_NETWORK_CLIENT(nb_client)

typedef struct NB_CLIENT_TYPE() {
    struct CLIENT_TYPE() base_client;
} NB_CLIENT_TYPE();

#define NB_CLIENT_METHOD(METHOD) TYPE_METHOD(NB_CLIENT_TYPE(), METHOD)

struct NB_CLIENT_TYPE()* NB_CLIENT_METHOD(construct_at)(struct NB_CLIENT_TYPE()* const this);

int NB_CLIENT_METHOD(is_connection_established)(struct NB_CLIENT_TYPE() const* const this);

struct RESULT_TYPE(int, int) NB_CLIENT_METHOD(status)(struct NB_CLIENT_TYPE() const* const this);

struct NB_CLIENT_TYPE()* NB_CLIENT_METHOD(connect)(struct NB_CLIENT_TYPE()* const this,
    char const* const restrict host,
    char const* const restrict service,
    struct ADDRESS_INFO_CRITERIAS_TYPE() const* const address_info_criterias
);

struct NB_CLIENT_TYPE()* NB_CLIENT_METHOD(shutdown)(struct NB_CLIENT_TYPE()* const this);

struct NB_CLIENT_TYPE()* NB_CLIENT_METHOD(reconnect)(struct NB_CLIENT_TYPE()* const this);

int NB_CLIENT_METHOD(send)(struct NB_CLIENT_TYPE() const* const this,
    void const* const buffer,
    usize buffer_size
);

int NB_CLIENT_METHOD(receive)(struct NB_CLIENT_TYPE() const* const this,
    void* const buffer,
    usize buffer_size
);

// dynamic methods
inline static int NB_CLIENT_METHOD(on_success_connection)(struct NB_CLIENT_TYPE() const* const this) {
    return this->base_client.INTERFACE_VTABLE_VARIABLE(CLIENT_TYPE())->on_success_connection(&this->base_client);
}
inline static void* NB_CLIENT_METHOD(destroy_at)(struct NB_CLIENT_TYPE()* const this) {
    return this->base_client.INTERFACE_VTABLE_VARIABLE(CLIENT_TYPE())->destroy_at(&this->base_client);
}
