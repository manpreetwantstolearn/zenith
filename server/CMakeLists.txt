cmake_minimum_required(VERSION 3.15)
project(ZenithServer)

add_executable(Zenith_server main.cpp)

target_link_libraries(Zenith_server
    PRIVATE
        httpserver
        logger
        mongoclient
)
