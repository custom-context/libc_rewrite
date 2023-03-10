#pragma once

#include <containers/common.h>
#include <memory/allocator/allocator.h>

#define NAMESPACE_CONTAINERS_DYNAMIC(NAME) NAMESPACE_CONTAINERS(CONCAT3(dynamic, __, NAME))
