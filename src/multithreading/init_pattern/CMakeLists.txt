add_executable(mt-init-pattern bootstrap.cpp)
target_link_libraries(mt-init-pattern PUBLIC utility thread container db)
target_include_directories(mt-init-pattern PUBLIC .)
target_compile_definitions(mt-init-pattern PRIVATE PROFILING)