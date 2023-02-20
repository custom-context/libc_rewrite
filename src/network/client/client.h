#pragma once

#include <network/socket/socket.h>
#include <network/address_info/address_info.h>
#include <network/common.h>

#define NAMESPACE_NETWORK_CLIENT(NAME) NAMESPACE_NETWORK(CONCAT3(client, __, NAME))

#define CLIENT_TYPE() NAMESPACE_NETWORK_CLIENT(client)

typedef struct CLIENT_TYPE() {
    struct SOCKET_TYPE() socket;
    struct ADDRESS_INFO_TYPE() address_info;
} CLIENT_TYPE();

#define CLIENT_METHOD(METHOD) TYPE_METHOD(CLIENT_TYPE(), METHOD)

struct CLIENT_TYPE()* CLIENT_METHOD(construct_at)(struct CLIENT_TYPE()* const this);

int CLIENT_METHOD(is_connection_established)(struct CLIENT_TYPE() const* const this);

struct RESULT_TYPE(int, int) CLIENT_METHOD(status)(struct CLIENT_TYPE() const* const this);

struct CLIENT_TYPE()* CLIENT_METHOD(connect)(struct CLIENT_TYPE()* const this,
    char const* const restrict host,
    char const* const restrict service,
    struct ADDRESS_INFO_CRITERIAS_TYPE() const* const address_info_criterias
);

struct CLIENT_TYPE()* CLIENT_METHOD(shutdown)(struct CLIENT_TYPE()* const this);

struct CLIENT_TYPE()* CLIENT_METHOD(reconnect)(struct CLIENT_TYPE()* const this);

int CLIENT_METHOD(send)(struct CLIENT_TYPE() const* const this,
    void* const buffer,
    size_t buffer_size
);

int CLIENT_METHOD(receive)(struct CLIENT_TYPE() const* const this,
    void* const buffer,
    size_t buffer_size
);

void* CLIENT_METHOD(destroy_at)(struct CLIENT_TYPE()* const this);
