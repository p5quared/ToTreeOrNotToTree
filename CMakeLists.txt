cmake_minimum_required(VERSION 3.25)
project(ToTreeOrNotToTree)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(analyze src/main.cpp)

add_library(TextTree include/WordNet.h src/WordNet.cpp)

add_library(FileHandler include/FileHandle.cpp)
file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/data/output/")
target_compile_definitions(FileHandler PRIVATE O_DIR="${CMAKE_SOURCE_DIR}/data/output/")

target_link_libraries(analyze PRIVATE TextTree)
target_link_libraries(analyze PRIVATE FileHandler)

if(WIN32)
    add_definitions("-DCURL_STATICLIB")
endif()
set(CURL_LIBRARY "-lcurl")
include_directories(${CURL_INCLUDE_DIR})
find_package(CURL REQUIRED)
target_link_libraries(analyze PRIVATE CURL::libcurl)



