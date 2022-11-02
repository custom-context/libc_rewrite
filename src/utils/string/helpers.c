#include "helpers.h"

uint utils__string__string_length(char const* const string) {
    uint length = 0u;
    while (string[length] != '\0') {
        ++length;
    }
    return length;
}
