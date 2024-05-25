set(CATLOG io)
set(APP ${CATLOG}-file)
add_executable(${APP} fstream.cpp)

# how to use boost libs
# target_link_libraries(${APP} PUBLIC utility thread container db)
target_include_directories(${APP} PUBLIC .)
target_compile_definitions(${APP} PRIVATE PROFILING)

add_custom_command(
        TARGET ${APP} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/data
                ${CMAKE_BINARY_DIR}/bin/
        COMMENT "Copying to ${CMAKE_BINARY_DIR}"
)

set(APP ${CATLOG}-sstream)
add_executable(${APP} sstream.cpp)

# how to use boost libs
# target_link_libraries(${APP} PUBLIC utility thread container db)
target_include_directories(${APP} PUBLIC .)
target_compile_definitions(${APP} PRIVATE PROFILING)
