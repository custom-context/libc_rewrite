#pragma once

#include <json/serialize/deserialization_errors.h>
#include <json/value/value.h>
#include <json/common.h>

#include <containers/dynamic/string/string.h>
#include <containers/static/string_view/string_view.h>
#include <utils/result.h>

DEFINE_RESULT_TYPE(JSON_VALUE_TYPE(), JSON_DESERIALIZATION_ERROR_TYPE());
DEFINE_RESULT_STATIC_METHODS(JSON_VALUE_TYPE(), JSON_DESERIALIZATION_ERROR_TYPE())

struct STRING_TYPE() NAMESPACE_JSON(serialize)(struct JSON_VALUE_TYPE() const* const json);
struct RESULT_TYPE(JSON_VALUE_TYPE(), JSON_DESERIALIZATION_ERROR_TYPE()) NAMESPACE_JSON(deserialize)(struct CSTRING_VIEW_TYPE() const string_view);
