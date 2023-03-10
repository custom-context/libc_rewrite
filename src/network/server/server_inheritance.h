#pragma once

#include "server.h"

int SERVER_METHOD(VTABLE_MEMBER(on_success_bind))(struct SERVER_TYPE() const* const this);
void* SERVER_METHOD(VTABLE_MEMBER(destroy_at))(struct SERVER_TYPE()* const this);
