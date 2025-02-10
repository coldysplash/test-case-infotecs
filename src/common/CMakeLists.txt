set(target_name parser)

add_library(${target_name} SHARED 
    common/parser.cpp
    common/parser.hpp)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
    ${target_name}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)