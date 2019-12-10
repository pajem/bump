cmake_minimum_required(VERSION 3.10)

find_package(Threads REQUIRED) # for gtest

set(TEST_NAME test-${PROJECT_NAME})
add_executable(${TEST_NAME}
    test-bump.cpp
)
target_link_libraries(${TEST_NAME}
    PRIVATE
        ${LIB_NAME}
        gtest
        gtest_main
        ${CMAKE_THREAD_LIBS_INIT}
)

add_test(
    NAME ${TEST_NAME}
    COMMAND $<TARGET_FILE:${TEST_NAME}>
)
