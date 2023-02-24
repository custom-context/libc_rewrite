#pragma once

#include "server.h"

int SERVER_METHOD(on_success_bind)(struct SERVER_TYPE() const* const this);
void* SERVER_METHOD(destroy_at)(struct SERVER_TYPE()* const this);
