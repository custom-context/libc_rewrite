target_sources(${PROJECT_NAME}
    PRIVATE
        common.h
)

add_subdirectory(reference_counted)
add_subdirectory(atomically_reference_counted)
add_subdirectory(pair)
add_subdirectory(interface)
add_subdirectory(iterator)
add_subdirectory(dynamic)
add_subdirectory(static)
