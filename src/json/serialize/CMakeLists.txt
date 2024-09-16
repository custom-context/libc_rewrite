target_sources(${PROJECT_NAME}
    PRIVATE
        deserialization_errors.h
        deserialization_errors.c

        serialize.h
        serialize.c
)

add_subdirectory(lexer)
add_subdirectory(parser)
