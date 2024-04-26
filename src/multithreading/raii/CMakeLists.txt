add_executable(mt-raii bootstrap.cpp)
target_link_libraries(mt-raii PUBLIC core)
target_include_directories(mt-raii PUBLIC .)