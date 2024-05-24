set(CATLOG ipc)
set(APP ${CATLOG}-chat-peer1)
add_executable(${APP} bootstrap.cpp)
target_compile_definitions(${APP} PUBLIC WRITER)

# how to use boost libs
# target_link_libraries(${APP} PUBLIC utility thread container db)
target_include_directories(${APP} PUBLIC .)
target_compile_definitions(${APP} PRIVATE PROFILING)

set(APP ${CATLOG}-chat-peer2)
add_executable(${APP} bootstrap.cpp)
target_compile_definitions(${APP} PUBLIC READER)
target_include_directories(${APP} PUBLIC .)
target_compile_definitions(${APP} PRIVATE PROFILING)