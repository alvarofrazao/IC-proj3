cmake_minimum_required(VERSION 3.16)
project(part2)

find_package(OpenCV REQUIRED)

SET (CMAKE_BUILD_TYPE "Release")
#SET (CMAKE_BUILD_TYPE "Debug")

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17 -pthread")
SET (CMAKE_CXX_FLAGS_RELEASE "-O3")
SET (CMAKE_CXX_FLAGS_DEBUG "-g3 -fsanitize=address")

SET (BASE_DIR ${CMAKE_SOURCE_DIR} )
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASE_DIR}/../part2-bin)

add_executable (lang lang.cpp)
target_link_libraries (lang)

add_executable (findlang findlang.cpp)
target_link_libraries (findlang)

add_executable (locatelang locatelang.cpp)
target_link_libraries (locatelang)

add_executable (lang_model_test lang_model_test.cpp)
target_link_libraries(lang_model_test)


add_executable (multimodelfind multimodelfind.cpp)
target_link_libraries(multimodelfind)

