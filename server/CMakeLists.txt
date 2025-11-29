cmake_minimum_required(VERSION 3.15)
project(AstraServer)

add_executable(zenith_server main.cpp)

target_link_libraries(zenith_server
    PRIVATE
        httpserver
        logger
        mongoclient
)
