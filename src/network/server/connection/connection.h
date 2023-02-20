#pragma once

#include <network/socket/socket.h>
#include <network/common.h>

#include <construct/numeric_helpers.h>

#ifndef NAMESPACE_NETWORK_SERVER
    #define NAMESPACE_NETWORK_SERVER(NAME) NAMESPACE_NETWORK(CONCAT3(server, __, NAME))
#endif

#define NAMESPACE_NETWORK_SERVER_CONNECTION(NAME) NAMESPACE_NETWORK_SERVER(CONCAT3(connection, __, NAME))

#define CONNECTION_TYPE() NAMESPACE_NETWORK_SERVER_CONNECTION(connection)

typedef struct CONNECTION_TYPE() {
    struct SOCKET_TYPE() socket;
} CONNECTION_TYPE();

#define CONNECTION_METHOD(METHOD) TYPE_METHOD(CONNECTION_TYPE(), METHOD)

int CONNECTION_METHOD(is_established)(struct CONNECTION_TYPE() const* const this);

struct RESULT_TYPE(int, int) CONNECTION_METHOD(status)(struct CONNECTION_TYPE() const* const this);

int CONNECTION_METHOD(send)(struct CONNECTION_TYPE() const* const this,
    void* const buffer,
    size_t buffer_size
);

int CONNECTION_METHOD(receive)(struct CONNECTION_TYPE() const* const this,
    void* const buffer,
    size_t buffer_size
);

void* CONNECTION_METHOD(destroy_at)(struct CONNECTION_TYPE()* const this);
