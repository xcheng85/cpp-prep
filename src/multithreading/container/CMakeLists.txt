add_executable(mt-container bootstrap.cpp)
target_link_libraries(mt-container PUBLIC utility thread container)
target_include_directories(mt-container PUBLIC .)
target_compile_definitions(mt-container PRIVATE PROFILING)