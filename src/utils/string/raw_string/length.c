#include "length.h"

DEFINE_RAW_STRING_LENGTH_FUNCTION(char)
DEFINE_RAW_STRING_LENGTH_FUNCTION(char8)
DEFINE_RAW_STRING_LENGTH_FUNCTION(char16)
DEFINE_RAW_STRING_LENGTH_FUNCTION(char32)
DEFINE_RAW_STRING_LENGTH_FUNCTION(char64)

DEFINE_RAW_STRING_LENGTH_FUNCTION(wchar)

#if defined(_WIN32)
    DEFINE_RAW_STRING_LENGTH_FUNCTION(winchar)
#endif
