set(APP numeric_integration)
enable_language(CUDA)
add_library(kernel kernel.cu kernel.h)
set_target_properties(kernel
                       PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries(container PUBLIC utility)
target_include_directories(container PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/cuda/numeric_integration>"
)

add_executable(${APP} bootstrap.cpp)

# set_property(TARGET ${APP} 
#              PROPERTY CUDA_SEPARABLE_COMPILATION ON)
target_link_libraries(${APP} PUBLIC utility thread container kernel)
target_include_directories(${APP} PUBLIC .)
target_compile_definitions(${APP} PRIVATE PROFILING)