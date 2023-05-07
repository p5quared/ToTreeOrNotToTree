cmake_minimum_required(VERSION 3.25)
project(ToTreeOrNotToTree)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(Cleanup src/main.cpp)

add_library(TextTree include/WordNet.h src/WordNet.cpp)
add_library(FileHandler include/FileHandle.cpp)

target_link_libraries(Cleanup PRIVATE TextTree)
target_link_libraries(Cleanup PRIVATE FileHandler)


file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/data/output/")
target_compile_definitions(Cleanup PRIVATE O_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data/output/")
