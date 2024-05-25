set(CATLOG ipc)
set(APP ${CATLOG}-chat-messagequeue)
add_executable(${APP} bootstrap.cpp)
target_compile_definitions(${APP} PUBLIC WRITER)

# # /usr/lib/x86_64-linux-gnu/librt.a
# find_library(LIBRT rt)
# message("${LIBRT}")
# target_link_libraries(${APP} ${LIBRT})

# how to use boost libs
# target_link_libraries(${APP} PUBLIC utility thread container db)
target_include_directories(${APP} PUBLIC .)
target_compile_definitions(${APP} PRIVATE PROFILING)