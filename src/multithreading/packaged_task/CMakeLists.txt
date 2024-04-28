set(APP mt-packaged-task)

add_executable(${APP} bootstrap.cpp)
target_link_libraries(${APP} PUBLIC utility thread container db)
target_include_directories(${APP} PUBLIC .)
target_compile_definitions(${APP} PRIVATE PROFILING)