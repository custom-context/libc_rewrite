target_sources(${PROJECT_NAME}
    PRIVATE
        thread.h
        thread.c
)

if(WIN32)
    add_subdirectory(win)
else()
    add_subdirectory(posix)
endif()
