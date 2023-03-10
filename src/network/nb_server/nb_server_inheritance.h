#pragma once

#include "nb_server.h"

int NB_SERVER_METHOD(VTABLE_MEMBER(on_success_bind))(struct SERVER_TYPE() const* const base);
void* NB_SERVER_METHOD(VTABLE_MEMBER(destroy_at))(struct NB_SERVER_TYPE()* const this);
