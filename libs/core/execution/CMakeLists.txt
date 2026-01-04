find_package(Protobuf REQUIRED)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS config/execution.proto)

add_library(zenith_execution
    src/MessageQueue.cpp
    src/AffinityExecutor.cpp
    src/PoolExecutor.cpp
    src/ObservableExecutor.cpp
    ${PROTO_SRCS}
)

target_include_directories(zenith_execution
    PUBLIC
        include
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(zenith_execution
    PRIVATE
        zenith_sanitizers
    PUBLIC
        observability
        protobuf::libprotobuf
)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
