cmake_minimum_required(VERSION 3.15)
project(json_dictionary_parser CXX)

set(CMAKE_CXX_STANDARD 20)
find_package(RapidJSON CONFIG REQUIRED)

add_executable(json_dictionary_parser src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE RapidJSON::RapidJSON)

target_include_directories(json_dictionary_parser PUBLIC include)
install(TARGETS json_dictionary_parser)
