set(target_name client_lib)

add_library(${target_name} STATIC 
    client/client.cpp
    client/client.hpp)

include(CompileOptions)
set_compile_options(${target_name})

target_include_directories(
    ${target_name}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)