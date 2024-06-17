set(CATLOG bitmanip)
set(APP ${CATLOG}-maxpow2)
add_executable(${APP} maxpow2.cpp)

# how to use boost libs
# target_link_libraries(${APP} PUBLIC utility thread container db)
target_include_directories(${APP} PUBLIC .)
target_compile_definitions(${APP} PRIVATE PROFILING)
