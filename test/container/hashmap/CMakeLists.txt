set(TEST hashmap_test)
add_executable(${TEST} hashmap_test.cpp)
target_link_libraries(${TEST} PRIVATE utility thread container)
AddTests(${TEST})
