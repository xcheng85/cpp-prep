set(CATLOG binarytree)
set(APP ${CATLOG}-quicksort)
add_executable(${APP} quicksort.cpp)

# how to use boost libs
# target_link_libraries(${APP} PUBLIC utility thread container db)
target_include_directories(${APP} PUBLIC .)
target_compile_definitions(${APP} PRIVATE PROFILING)


set(CATLOG binarytree)
set(APP ${CATLOG}-mergesort)
add_executable(${APP} mergesort.cpp)
# how to use boost libs
# target_link_libraries(${APP} PUBLIC utility thread container db)
target_include_directories(${APP} PUBLIC .)
target_compile_definitions(${APP} PRIVATE PROFILING)