target_sources(${PROJECT_NAME}
    PUBLIC
        common.h
        common.c
)

add_subdirectory(native)
add_subdirectory(socket)
add_subdirectory(address_info)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(nb_client)
add_subdirectory(nb_server)
