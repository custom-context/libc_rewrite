add_subdirectory(raw_string)
target_sources(${PROJECT_NAME}
    PRIVATE
        helpers.h
        convert.h
        convert.c

        compare.h
        compare.c
)
