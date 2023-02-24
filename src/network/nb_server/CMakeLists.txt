add_subdirectory(nb_connection)

target_sources(${PROJECT_NAME}
    PRIVATE
        nb_server.h
        nb_server.c
        nb_server_inheritance.h
        nb_server_inheritance.c
)
