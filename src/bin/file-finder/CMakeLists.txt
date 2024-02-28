set(TARGET_NAME file-finder)

set(SKYTRANS_INCLUDE_DIR ${SKYTRANS_PREFIX_PATH}/include)

include_directories( ${PROJECT_SOURCE_DIR}/include/file-finder)

file(GLOB CPPFILES *.cpp)

add_executable(${TARGET_NAME} ${CPPFILES})
