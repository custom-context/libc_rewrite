target_sources(${PROJECT_NAME}
    PRIVATE
        macros.c
        macros.h
)
add_subdirectory(string)
add_subdirectory(result)
add_subdirectory(format)
