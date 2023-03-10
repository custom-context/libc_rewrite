target_sources(${PROJECT_NAME}
    PRIVATE
        common.h
        memory.h
)

add_subdirectory(native)
add_subdirectory(allocator)
