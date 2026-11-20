cmake_minimum_required(VERSION 3.28)

project(TowerDefense LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/Zc:__cplusplus)
endif()

include(FetchContent)
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(SFML)

add_executable(TowerDefense
    src/main.cpp
    src/Map.cpp
    src/Enemy.cpp
    src/FastEnemy.cpp
    src/BruiserEnemy.cpp
)


target_include_directories(TowerDefense PRIVATE include)

target_link_libraries(TowerDefense PRIVATE
    SFML::Graphics
)

target_compile_features(TowerDefense PRIVATE cxx_std_20)

add_custom_command(TARGET TowerDefense POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:TowerDefense>/assets"
)
