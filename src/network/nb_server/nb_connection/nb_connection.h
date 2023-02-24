#pragma once

#include <network/server/connection/connection.h>
#include <network/common.h>

#ifndef NAMESPACE_NETWORK_NB_SERVER
    #define NAMESPACE_NETWORK_NB_SERVER(NAME) NAMESPACE_NETWORK(CONCAT5(non_blocking, _, server, __, NAME))
#endif

#define NAMESPACE_NETWORK_NB_SERVER_NB_CONNECTION(NAME) NAMESPACE_NETWORK_NB_SERVER(CONCAT5(non_blocking, _, connection, __, NAME))

int NAMESPACE_NETWORK_NB_SERVER_NB_CONNECTION(make_non_blocking)(struct CONNECTION_TYPE()* const connection);
int NAMESPACE_NETWORK_NB_SERVER_NB_CONNECTION(make_blocking)(struct CONNECTION_TYPE()* const connection);
