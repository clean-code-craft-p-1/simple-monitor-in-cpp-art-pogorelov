cmake_minimum_required(VERSION 3.14)
project(Monitor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        CLI11
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
        GIT_TAG v2.5.0
)

FetchContent_MakeAvailable(CLI11)

FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG 0.8.0
)
FetchContent_MakeAvailable(yaml-cpp)

add_library(${PROJECT_NAME}.Lib
        src/Types.h
        src/Config.cpp
        src/Config.h
        src/Monitor.h
        src/Monitor.cpp)

target_link_libraries(${PROJECT_NAME}.Lib
        PUBLIC yaml-cpp::yaml-cpp)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Print.cpp
        src/Print.h)

target_link_libraries(${PROJECT_NAME}
        PRIVATE ${PROJECT_NAME}.Lib CLI11::CLI11)

set(CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/resource/config.yml)
add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/config.yml
        COMMAND ${CMAKE_COMMAND} -E copy ${CONFIG_FILE} ${CMAKE_CURRENT_BINARY_DIR}/config.yml
        DEPENDS ${CONFIG_FILE}
        COMMENT "Copying config.yml"
)

add_custom_target(copy_config ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/config.yml)
add_dependencies(${PROJECT_NAME} copy_config)

enable_testing()
add_subdirectory(test)
