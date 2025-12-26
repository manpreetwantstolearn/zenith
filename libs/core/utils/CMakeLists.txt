add_library(zenith_utils
    src/StringUtils.cpp
    src/Url.cpp
)

find_package(Boost REQUIRED COMPONENTS url)

target_include_directories(zenith_utils PUBLIC include)
target_link_libraries(zenith_utils PRIVATE Boost::url)

# Tests
if(BUILD_TESTING)
    add_executable(string_utils_test tests/string_utils_test.cpp)
    target_link_libraries(string_utils_test PRIVATE zenith_utils GTest::gtest_main)
    gtest_discover_tests(string_utils_test)

    add_executable(url_test tests/url_test.cpp)
    target_link_libraries(url_test PRIVATE zenith_utils GTest::gtest_main)
    gtest_discover_tests(url_test)
endif()
