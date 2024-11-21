cmake_minimum_required(VERSION 3.24)
project(lab10)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/Users/benad/Desktop/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio system REQUIRED)


add_library(memer memer.cpp)
target_link_libraries(memer sfml-graphics sfml-audio sfml-system)


add_executable(memeify memeify.cpp)
target_link_libraries(memeify memer sfml-graphics sfml-audio sfml-system)