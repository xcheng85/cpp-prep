set(APP utf_convert_cpp_only)

add_executable(${APP} utf-convert.cpp)
target_link_libraries(${APP} PUBLIC utility)
target_include_directories(${APP} PUBLIC .)
target_compile_definitions(${APP} PRIVATE PROFILING)

set(APP utf_boost)
add_executable(${APP} utf_boost.cpp)
target_link_libraries(${APP} PUBLIC utility Boost::locale)
target_include_directories(${APP} PUBLIC .)
target_compile_definitions(${APP} PRIVATE PROFILING)
