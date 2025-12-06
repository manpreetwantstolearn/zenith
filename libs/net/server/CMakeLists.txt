cmake_minimum_required(VERSION 3.25)
project(ZenithServer)

add_executable(zenith_server main.cpp)

target_link_libraries(zenith_server
    PRIVATE
        httpserver
        logger
        mongoclient
)
