set(APP async-future)
add_executable(${APP} bootstrap.cpp)
target_include_directories(${APP} PUBLIC .)

