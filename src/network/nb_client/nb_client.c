#include "nb_client_inheritance.h"
#include "nb_client.h"

#include <stddef.h> // offsetof

// client destroy_at overloading
static void* TYPE_METHOD(INTERFACE_VTABLE_TYPE(CLIENT_TYPE()), CLIENT_METHOD(VTABLE_MEMBER(destroy_at)))(struct CLIENT_TYPE()* const base) {
    void* const void_this = (void* const)((char* const)base - offsetof(struct NB_CLIENT_TYPE(), base_client));
    struct NB_CLIENT_TYPE()* const this = (struct NB_CLIENT_TYPE()* const)(void_this);
    return NB_CLIENT_METHOD(VTABLE_MEMBER(destroy_at))(this);
}

static struct INTERFACE_VTABLE_TYPE(CLIENT_TYPE()) TYPE_MEMBER(NB_CLIENT_TYPE(), INTERFACE_VTABLE_VARIABLE(CLIENT_TYPE())) = {
    .destroy_at = TYPE_METHOD(INTERFACE_VTABLE_TYPE(CLIENT_TYPE()), CLIENT_METHOD(VTABLE_MEMBER(destroy_at))),
    .on_success_connection = NB_CLIENT_METHOD(VTABLE_MEMBER(on_success_connection))
};

struct NB_CLIENT_TYPE()* NB_CLIENT_METHOD(construct_at)(struct NB_CLIENT_TYPE()* const this) {
    // boilerplate
    CLIENT_METHOD(construct_at)(&this->base_client);
    this->base_client.INTERFACE_VTABLE_VARIABLE(CLIENT_TYPE()) = &TYPE_MEMBER(NB_CLIENT_TYPE(), INTERFACE_VTABLE_VARIABLE(CLIENT_TYPE()));
    // body
    // ...
    // boilerplate
    return this;
}

int NB_CLIENT_METHOD(is_connection_established)(struct NB_CLIENT_TYPE() const* const this) {
    return CLIENT_METHOD(is_connection_established)(&this->base_client);
}

struct RESULT_TYPE(int, int) NB_CLIENT_METHOD(status)(struct NB_CLIENT_TYPE() const* const this) {
    return CLIENT_METHOD(status)(&this->base_client);
}

struct NB_CLIENT_TYPE()* NB_CLIENT_METHOD(connect)(struct NB_CLIENT_TYPE()* const this,
    char const* const restrict host,
    char const* const restrict service,
    struct ADDRESS_INFO_CRITERIAS_TYPE() const* const address_info_criterias
) {
    CLIENT_METHOD(connect)(&this->base_client, host, service, address_info_criterias);
    return this;
}

struct NB_CLIENT_TYPE()* NB_CLIENT_METHOD(shutdown)(struct NB_CLIENT_TYPE()* const this) {
    CLIENT_METHOD(shutdown)(&this->base_client);
    return this;
}

struct NB_CLIENT_TYPE()* NB_CLIENT_METHOD(reconnect)(struct NB_CLIENT_TYPE()* const this) {
    CLIENT_METHOD(reconnect)(&this->base_client);
    return this;
}

int NB_CLIENT_METHOD(send)(struct NB_CLIENT_TYPE() const* const this,
    void const* const buffer,
    usize buffer_size
) {
    return CLIENT_METHOD(send)(&this->base_client, buffer, buffer_size);
}

int NB_CLIENT_METHOD(receive)(struct NB_CLIENT_TYPE() const* const this,
    void* const buffer,
    usize buffer_size
) {
    return CLIENT_METHOD(receive)(&this->base_client, buffer, buffer_size);
}
