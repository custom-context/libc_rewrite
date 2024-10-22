target_sources(${PROJECT_NAME}
    PRIVATE
        primitives.h
        unsigned_types_aliases.h
        characters_types_aliases.h
        fixed_size_types_aliases.h
        data_model_types_aliases.h
        bool_type_alias.h

        limits.h

        allocator.h
        allocator.c

        atomic.h
        atomic.c

        optional.h
        optional.c
)
