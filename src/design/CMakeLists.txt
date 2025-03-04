set(APP design)
add_executable(${APP} bootstrap.cpp bridge.cpp)
target_include_directories(${APP} PUBLIC .)