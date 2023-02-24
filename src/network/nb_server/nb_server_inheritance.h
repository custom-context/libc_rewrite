#pragma once

#include "nb_server.h"

int NB_SERVER_METHOD(on_success_bind)(struct SERVER_TYPE() const* const base);
void* NB_SERVER_METHOD(destroy_at)(struct NB_SERVER_TYPE()* const this);
