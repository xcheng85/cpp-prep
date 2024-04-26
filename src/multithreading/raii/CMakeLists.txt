add_executable(mt-raii bootstrap.cpp)
target_link_libraries(mt-raii PUBLIC utility thread db)
target_include_directories(mt-raii PUBLIC .)