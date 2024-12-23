set(APP boost.asio-server)
add_executable(${APP} bootstrap.cpp)
target_compile_definitions(${APP} PUBLIC -DBOOST_ASIO_ENABLE_HANDLER_TRACKING)

target_link_libraries(${APP} PUBLIC Boost::asio)
target_include_directories(${APP} PUBLIC .)