#pragma once

#include "nb_client.h"

int NB_CLIENT_METHOD(VTABLE_MEMBER(on_success_connection))(struct CLIENT_TYPE() const* const base);
void* NB_CLIENT_METHOD(VTABLE_MEMBER(destroy_at))(struct NB_CLIENT_TYPE()* const this);
