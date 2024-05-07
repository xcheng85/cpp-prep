set(LIBRARY custom_type_trait)

add_library(${LIBRARY} smartpointer.cpp)

target_include_directories(${LIBRARY} PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/core/custom_type_trait>"
)

get_target_property(dirs ${LIBRARY} INTERFACE_INCLUDE_DIRECTORIES)
foreach(dir IN LISTS dirs)
    message(STATUS "dir='${dir}'")
endforeach()