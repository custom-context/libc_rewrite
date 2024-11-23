target_sources(${PROJECT_NAME}
    PRIVATE
        common.h

        native.h
)

if(WIN32)
    add_subdirectory(win)
else()
    add_subdirectory(posix)
endif()
