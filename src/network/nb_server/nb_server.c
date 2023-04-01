#include "nb_server_inheritance.h"
#include "nb_server.h"

#include <stddef.h>

// server destroy_at overloading
static void* TYPE_METHOD(INTERFACE_VTABLE_TYPE(SERVER_TYPE()), SERVER_METHOD(VTABLE_MEMBER(destroy_at)))(struct SERVER_TYPE()* const base) {
    void* const void_this = (void* const)((char* const)base - offsetof(struct NB_SERVER_TYPE(), base_server));
    struct NB_SERVER_TYPE()* const this = (struct NB_SERVER_TYPE()* const)(void_this);
    return NB_SERVER_METHOD(VTABLE_MEMBER(destroy_at))(this);
}

static struct INTERFACE_VTABLE_TYPE(SERVER_TYPE()) TYPE_MEMBER(NB_SERVER_TYPE(), INTERFACE_VTABLE_VARIABLE(SERVER_TYPE())) = {
    .destroy_at = TYPE_METHOD(INTERFACE_VTABLE_TYPE(SERVER_TYPE()), SERVER_METHOD(VTABLE_MEMBER(destroy_at))),
    .on_success_bind = NB_SERVER_METHOD(VTABLE_MEMBER(on_success_bind))
};

struct NB_SERVER_TYPE()* NB_SERVER_METHOD(construct_at)(struct NB_SERVER_TYPE()* const this) {
    // boilerplate
    SERVER_METHOD(construct_at)(&this->base_server);
    this->base_server.INTERFACE_VTABLE_VARIABLE(SERVER_TYPE()) = &TYPE_MEMBER(NB_SERVER_TYPE(), INTERFACE_VTABLE_VARIABLE(SERVER_TYPE()));
    // body
    // ...
    // boilerplate
    return this;
}

struct NB_SERVER_TYPE()* NB_SERVER_METHOD(bind)(struct NB_SERVER_TYPE()* const this,
    char const* const restrict host,
    char const* const restrict service,
    struct ADDRESS_INFO_CRITERIAS_TYPE() const* const address_info_criterias
) {
    SERVER_METHOD(bind)(&this->base_server,
        host,
        service,
        address_info_criterias
    );
    return this;
}

struct NB_SERVER_TYPE()* NB_SERVER_METHOD(rebind)(struct NB_SERVER_TYPE()* const this) {
    SERVER_METHOD(rebind)(&this->base_server);
    return this;
}

int NB_SERVER_METHOD(is_binded)(struct NB_SERVER_TYPE()* const this) {
    return SERVER_METHOD(is_binded)(&this->base_server);
}

struct RESULT_TYPE(int, int) NB_SERVER_METHOD(status)(struct NB_SERVER_TYPE() const* const this) {
    return SERVER_METHOD(status)(&this->base_server);
}

int NB_SERVER_METHOD(listen)(struct NB_SERVER_TYPE()* const this, usize system_connections_queue_capacity) {
    return SERVER_METHOD(listen)(&this->base_server, system_connections_queue_capacity);
}

struct CONNECTION_TYPE() NB_SERVER_METHOD(accept)(struct NB_SERVER_TYPE()* const this) {
    return SERVER_METHOD(accept)(&this->base_server);
}

struct NB_SERVER_TYPE()* NB_SERVER_METHOD(shutdown)(struct NB_SERVER_TYPE()* const this) {
    SERVER_METHOD(shutdown)(&this->base_server);
    return this;
}
