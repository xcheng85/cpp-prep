set(LIB cuda)
enable_language(CUDA)
add_library(${LIB} cuDevice.h cuDevice.cu mathUtils.h mathUtils.cu)
set_target_properties(${LIB}
                       PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries(${LIB} PUBLIC utility)
target_include_directories(${LIB} PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/core/cuda>"
)
