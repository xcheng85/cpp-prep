set(APP moderncpp)
add_executable(${APP} bootstrap.cpp)
target_include_directories(${APP} PUBLIC .)