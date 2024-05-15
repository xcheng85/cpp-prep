set(APP shared_memory)
set(LIB "${APP}_kernel")

enable_language(CUDA)
add_library(${LIB} kernel.cu kernel.h)
set_target_properties(${LIB} PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
target_compile_definitions(${LIB} PUBLIC WARP_OP)


target_link_libraries(${LIB} PUBLIC utility cuda)
target_include_directories(${LIB} PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/cuda/${APP}>"
)

add_executable(${APP} bootstrap.cu)

target_link_libraries(${APP} PUBLIC utility ${APP}_kernel)
target_include_directories(${APP} PUBLIC .)
target_compile_definitions(${APP} PRIVATE PROFILING)