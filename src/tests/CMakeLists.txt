set(TARGETNAME file-finder-unit-tests)

include_directories(
                ${PROJECT_SOURCE_DIR}/bin/file-finder
)

add_executable(${TARGETNAME} 
                main.cpp
                file-finder-unit-tests.cpp
)

target_link_libraries(${TARGETNAME} GTest::GTest GTest::Main)

gtest_discover_tests(${TARGETNAME} TEST_PREFIX file-finder-unit-tests:)

add_dependencies(${TARGETNAME} file_finder)
