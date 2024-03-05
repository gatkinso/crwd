set(TARGET_NAME file-finder)

include_directories( ${PROJECT_SOURCE_DIR}/include/file-finder)

file(GLOB CPPFILES *.cpp)

add_executable(${TARGET_NAME} ${CPPFILES})
