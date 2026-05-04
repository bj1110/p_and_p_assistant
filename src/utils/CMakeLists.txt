target_sources(p_and_p_assistant
    PRIVATE logger.cpp
)

target_compile_options(p_and_p_assistant
    PRIVATE 
        -fmacro-prefix-map=${CMAKE_SOURCE_DIR}/=
)