set(CATLOG quickSelect)
set(APP ${CATLOG}-lc_215)
add_executable(${APP} bootstrap.cpp)

# how to use boost libs
# target_link_libraries(${APP} PUBLIC utility thread container db)
target_include_directories(${APP} PUBLIC .)
target_compile_definitions(${APP} PRIVATE PROFILING)

add_executable(${APP}-perf-test benchmark.cpp)
target_include_directories(${APP}-perf-test PUBLIC .) #for include <
target_link_libraries(${APP}-perf-test benchmark::benchmark)
