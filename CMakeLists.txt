cmake_minimum_required(VERSION 3.0)
project(ParserExample)

set(CMAKE_CXX_STANDARD 17)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(
    HEADERS
    ${ParserExample_SOURCE_DIR}/driver.hh
    ${ParserExample_SOURCE_DIR}/parser.hh
    )

BISON_TARGET(
    MyParser
    parser.y
    ${ParserExample_SOURCE_DIR}/parser.cpp
    COMPILE_FLAGS "-W -Wconflicts-sr -Wconflicts-rr -Wother -Wprecedence --warnings=all --report=all --verbose"
    DEFINES_FILE ${ParserExample_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
    MyScanner
    scanner.l
    ${ParserExample_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

add_executable(
    ParserExample
    main.cpp
    driver.cpp
    ${BISON_MyParser_OUTPUTS}
    ${FLEX_MyScanner_OUTPUTS}
)
target_include_directories(ParserExample PRIVATE ${ParserExample_SOURCE_DIR})



