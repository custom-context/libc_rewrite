target_sources(${PROJECT_NAME}
    PRIVATE
        macros.h
        format_print.h
        format_print.c
        format.h
        format.c
        debug.h
)

add_subdirectory(string)
