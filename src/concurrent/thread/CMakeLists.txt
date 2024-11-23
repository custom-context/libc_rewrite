target_sources(${PROJECT_NAME}
    PRIVATE
        common.h

        thread.h
)

add_subdirectory(native)
add_subdirectory(thread)
