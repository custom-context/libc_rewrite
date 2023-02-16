#pragma once

#include <network/socket/socket.h>
#include <network/common.h>

#define NAMESPACE_NETWORK_NATIVE(NAME) NAMESPACE_NETWORK(CONCAT3(native, __, NAME))

int NAMESPACE_NETWORK_NATIVE(get_native_domain)(enum SOCKET_DOMAIN_ENUM() domain);
enum SOCKET_DOMAIN_ENUM() NAMESPACE_NETWORK_NATIVE(get_wrapped_domain)(int native_domain);

int NAMESPACE_NETWORK_NATIVE(get_native_socket_type)(enum SOCKET_TYPE_ENUM() socket_type);
enum SOCKET_TYPE_ENUM() NAMESPACE_NETWORK_NATIVE(get_wrapped_socket_type)(int native_socket_type);
