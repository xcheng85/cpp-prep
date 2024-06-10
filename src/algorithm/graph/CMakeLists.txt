set(CATLOG graph)
set(APP ${CATLOG}-1976_dijaksra)
add_executable(${APP} 1976_dijaksra.cpp)

# how to use boost libs
# target_link_libraries(${APP} PUBLIC utility thread container db)
target_include_directories(${APP} PUBLIC .)
target_compile_definitions(${APP} PRIVATE PROFILING)
