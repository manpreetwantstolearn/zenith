find_package(redis++ REQUIRED)

add_library(redisclient STATIC
    src/RedisClient.cpp
    src/SwRedisClient.cpp
)

target_include_directories(redisclient
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(redisclient
    PRIVATE
        zenith_sanitizers
        observability
    PUBLIC
        redis++::redis++
)

zenith_add_test(
    TARGET redis_integration_test
    SOURCES tests/redis_integration_test.cpp
    LIBRARIES redisclient
)

zenith_add_test(
    TARGET redis_mock_test
    SOURCES tests/redis_mock_test.cpp
    LIBRARIES redisclient
)
