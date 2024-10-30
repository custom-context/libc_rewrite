#include "character.h"

bool NAMESPACE_UTILS_CHARACTER(is_char32_digit)(char32 character) {
    return '0' <= character && character <= '9';
}
bool NAMESPACE_UTILS_CHARACTER(is_char16_digit)(char16 character) {
    return '0' <= character && character <= '9';
}
bool NAMESPACE_UTILS_CHARACTER(is_char8_digit)(char8 character) {
    return '0' <= character && character <= '9';
}
bool NAMESPACE_UTILS_CHARACTER(is_char_digit)(char character) {
    return '0' <= character && character <= '9';
}
