#include "client_inheritance.h"

int CLIENT_METHOD(on_success_connection)(struct CLIENT_TYPE() const* const this) {
    UNUSED(this);
    return 0;
}

void* CLIENT_METHOD(destroy_at)(struct CLIENT_TYPE()* const this) {
    SOCKET_METHOD(destroy_at)(&this->socket);
    ADDRESS_INFO_METHOD(destroy_at)(&this->address_info);
    return this;
}
