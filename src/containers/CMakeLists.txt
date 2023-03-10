target_sources(${PROJECT_NAME}
    PRIVATE
        common.h
)

add_subdirectory(iterator)
add_subdirectory(dynamic)
add_subdirectory(static)
