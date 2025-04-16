project(Monitor.Test.Unit)

add_executable(
        ${PROJECT_NAME}
        src/ConfigTest.cpp
        src/PrintTest.cpp
        src/RangeTest.cpp
        src/MonitorTest.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src ../src)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE Monitor.Lib
        GTest::gtest_main
        GTest::gmock
        rapidcheck
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

