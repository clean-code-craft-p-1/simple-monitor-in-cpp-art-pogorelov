project(Monitor.Test.Unit)

include(FetchContent)

FetchContent_Declare(
        rapidcheck
        GIT_REPOSITORY https://github.com/emil-e/rapidcheck.git
        GIT_TAG master
)
FetchContent_MakeAvailable(rapidcheck)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        DOWNLOAD_EXTRACT_TIMESTAMP true
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
        ${PROJECT_NAME}
        src/ConfigTest.cpp
        src/PrintTest.cpp
        src/RangeTest.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src ../src)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE Monitor.Lib
        GTest::gtest_main
        rapidcheck
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

