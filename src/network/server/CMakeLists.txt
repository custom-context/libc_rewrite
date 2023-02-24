add_subdirectory(connection)

target_sources(${PROJECT_NAME}
    PRIVATE
        server.h
        server.c
        server_inheritance.h
        server_inheritance.c
)
