#pragma once

#include "client.h"

int CLIENT_METHOD(on_success_connection)(struct CLIENT_TYPE() const* const this);
void* CLIENT_METHOD(destroy_at)(struct CLIENT_TYPE()* const this);
