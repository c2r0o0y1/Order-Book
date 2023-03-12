cmake_minimum_required(VERSION 3.0.0)
project(ORDER_BOOK)

add_definitions(-std=c++17)

set(SOURCE_FILES main.cpp)
add_executable(ORDER_BOOK ${SOURCE_FILES})


include_directories(OrderBook)

add_subdirectory(OrderBook)
add_subdirectory(OrderBookTests)

target_link_libraries(ORDER_BOOK OrderBook)
