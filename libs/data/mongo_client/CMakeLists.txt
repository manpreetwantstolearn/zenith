find_package(mongoc REQUIRED)
find_package(bson REQUIRED)
find_package(bsoncxx REQUIRED)
find_package(mongocxx REQUIRED)

add_library(mongoclient STATIC
    src/MongoClient.cpp
    src/BsoncxxMongoClient.cpp
)

target_include_directories(mongoclient
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(mongoclient
    PRIVATE
        zenith_sanitizers
        observability
        mongo::mongocxx_static
        mongo::bsoncxx_static
    PUBLIC
        outcome
)

zenith_add_test(
    TARGET mongo_integration_test
    SOURCES tests/mongo_integration_test.cpp
    LIBRARIES mongoclient json
)

zenith_add_test(
    TARGET mongo_mock_test
    SOURCES tests/mongo_mock_test.cpp
    LIBRARIES mongoclient
)
