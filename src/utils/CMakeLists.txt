target_sources(${PROJECT_NAME}
    PRIVATE
        macros.h
        limits.h
        format_print.h
        format_print.c
        format.h
        format.c
        result.h
        debug.h
        convert.h
)

add_subdirectory(string)
add_subdirectory(comparator)
