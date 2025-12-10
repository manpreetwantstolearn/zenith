set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

# Add MongoDB Driver
add_subdirectory(mongodriver)

# Create library
add_library(mongoclient STATIC
    src/MongoClient.cpp
)

target_include_directories(mongoclient
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Link libraries
target_link_libraries(mongoclient
   PRIVATE
        zenith_sanitizers
        mongocxx_static
        bsoncxx_static
   PUBLIC
        observability
)

# Test executable
# GTest Integration
zenith_add_test(
    TARGET mongo_integration_test
    SOURCES tests/mongo_integration_test.cpp
    LIBRARIES
        mongoclient
	mongocxx_static
	bsoncxx_static
)

zenith_add_test(
    TARGET mongo_mock_test
    SOURCES tests/mongo_mock_test.cpp
    LIBRARIES
        mongoclient
	mongocxx_static
	bsoncxx_static
)
