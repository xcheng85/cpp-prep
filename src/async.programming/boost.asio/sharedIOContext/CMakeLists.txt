set(APP boost.asio-shared-iocontext)
add_executable(${APP} bootstrap.cpp)
target_link_libraries(${APP} PUBLIC Boost::asio)
target_include_directories(${APP} PUBLIC .)