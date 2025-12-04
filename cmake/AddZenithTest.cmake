# Macro to add a standard Zenith GTest executable
# Usage:
# zenith_add_test(
#     TARGET <target_name>
#     SOURCES <source_files>...
#     [LIBRARIES <libs>...]
#     [INCLUDE_DIRS <dirs>...]
# )
macro(zenith_add_test)
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs SOURCES LIBRARIES INCLUDE_DIRS)
    cmake_parse_arguments(ZENITH_TEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT ZENITH_TEST_TARGET)
        message(FATAL_ERROR "zenith_add_test: TARGET argument is required")
    endif()

    if(NOT ZENITH_TEST_SOURCES)
        message(FATAL_ERROR "zenith_add_test: SOURCES argument is required")
    endif()

    add_executable(${ZENITH_TEST_TARGET} ${ZENITH_TEST_SOURCES})

    if(ZENITH_TEST_INCLUDE_DIRS)
        target_include_directories(${ZENITH_TEST_TARGET} PRIVATE ${ZENITH_TEST_INCLUDE_DIRS})
    endif()

    target_link_libraries(${ZENITH_TEST_TARGET}
        PRIVATE
            ${ZENITH_TEST_LIBRARIES}
            GTest::gtest_main
            GTest::gmock
    )

    # Enable test discovery
    include(GoogleTest)
    gtest_discover_tests(${ZENITH_TEST_TARGET})
endmacro()
