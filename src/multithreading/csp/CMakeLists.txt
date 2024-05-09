set(APP mt-csp)

add_executable(${APP} bootstrap.cpp)
# how to use boost libs
target_link_libraries(${APP} PUBLIC utility thread container eda)
target_include_directories(${APP} PUBLIC .)
target_compile_definitions(${APP} PRIVATE PROFILING)