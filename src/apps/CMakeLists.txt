include(CompileOptions)

# client_app
add_executable(client_app)
set_compile_options(client_app)

target_sources(
  client_app
  PRIVATE
    apps/client_app.cpp
)

target_link_libraries(
  client_app
  PRIVATE
    parser
    client_lib
)

#server_app
add_executable(server_app)
set_compile_options(client_app)

target_sources(
  server_app
  PRIVATE
    apps/client_app.cpp
)

target_link_libraries(
  server_app
  PRIVATE
    parser
    server_lib
)