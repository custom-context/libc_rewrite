target_sources(${PROJECT_NAME}
    PRIVATE
        common.h
)

add_subdirectory(native)
add_subdirectory(allocator)
