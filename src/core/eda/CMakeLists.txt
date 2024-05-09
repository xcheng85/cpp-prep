set(LIBRARY eda)

add_library(${LIBRARY} event.cpp publisher.cpp)
target_link_libraries(${LIBRARY} PUBLIC utility container)
target_include_directories(${LIBRARY} PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/core/eda>"
)

get_target_property(dirs ${LIBRARY} INTERFACE_INCLUDE_DIRECTORIES)
foreach(dir IN LISTS dirs)
    message(STATUS "dir='${dir}'")
endforeach()