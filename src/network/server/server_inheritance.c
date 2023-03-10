#include "server_inheritance.h"

int SERVER_METHOD(on_success_bind)(struct SERVER_TYPE() const* const this) {
    UNUSED(this);
    return 0;
}

void* SERVER_METHOD(destroy_at)(struct SERVER_TYPE()* const this) {
    SOCKET_METHOD(destroy_at)(&this->socket);
    ADDRESS_INFO_METHOD(destroy_at)(&this->address_info);
    return this;
}
