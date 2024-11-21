target_sources(${PROJECT_NAME}
    PRIVATE
        common.h
)

add_subdirectory(array_storage)
add_subdirectory(string)
add_subdirectory(array)
add_subdirectory(tree)
