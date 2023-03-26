#pragma once

#include <utils/common.h>

#define CONVERT(FROM_TYPE, TO_TYPE)\
    CONCAT3(convert, __, CONCAT5(FROM_TYPE, _, to, _, TO_TYPE))
