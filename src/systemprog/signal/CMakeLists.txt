set(CATLOG signal)
set(APP ${CATLOG}-coredump)
add_executable(${APP} coredump.cpp)

# how to use boost libs
# target_link_libraries(${APP} PUBLIC utility thread container db)
target_include_directories(${APP} PUBLIC .)
target_compile_definitions(${APP} PRIVATE PROFILING)
