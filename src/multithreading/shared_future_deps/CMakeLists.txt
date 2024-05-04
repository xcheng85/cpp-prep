set(APP mt-shared-future-deps)

add_executable(${APP} bootstrap.cpp)
# how to use boost libs
target_link_libraries(${APP} PUBLIC utility thread container db Boost::uuid Boost::headers Boost::system Boost::filesystem)
target_include_directories(${APP} PUBLIC .)
target_compile_definitions(${APP} PRIVATE PROFILING)