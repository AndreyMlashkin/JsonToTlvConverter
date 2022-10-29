cmake_minimum_required(VERSION 3.15)
project(json_dictionary_parser CXX)

set(CMAKE_CXX_STANDARD 20)
find_package(RapidJSON CONFIG REQUIRED)

add_executable(json_dictionary_parser
    3rd_party/TLV/cpp/tlv.h
    3rd_party/TLV/cpp/tlv_box.h
    include/jsontotlvconverterinputstrategy/jsontotlvconverterinputstrategyinterface.h
    include/jsontotlvconverterinputstrategy/jsontotlvconverterinputstrategystdio.h
    include/jsontotlvconverterinputstrategy/jsontotlvconverterinputstrategyfileio.h
    include/jsontotlvconverterinputstrategy/jsontotlvconverterinputstrategyfactory.h
    include/jsontotlvconverter.h

    3rd_party/TLV/cpp/tlv.cpp
    3rd_party/TLV/cpp/tlv_box.cpp
    src/jsontotlvconverterinputstrategy/jsontotlvconverterinputstrategystdio.cpp
    src/jsontotlvconverterinputstrategy/jsontotlvconverterinputstrategyfileio.cpp
    src/jsontotlvconverterinputstrategy/jsontotlvconverterinputstrategyfactory.cpp
    src/jsontotlvconverter.cpp
    src/main.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE RapidJSON::RapidJSON)

target_include_directories(json_dictionary_parser PUBLIC include)
install(TARGETS json_dictionary_parser)
