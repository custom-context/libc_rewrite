add_subdirectory(connection)

target_sources(${PROJECT_NAME}
    PRIVATE
        server.h
        server.c
)
